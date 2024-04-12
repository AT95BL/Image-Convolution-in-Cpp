#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <omp.h>
#pragma warning(disable : 4996)
#include <numeric>                         // Za std::accumulate
#include <chrono>

// Struktura za predstavljanje boje (24-bitni BMP format)
struct Color {

    uint8_t blue, green, red;

    Color() : blue(0), green(0), red(0) {}
    Color(uint8_t b, uint8_t g, uint8_t r) : blue(b), green(g), red(r) {}
};

// Struktura za predstavljanje slike
struct Image {

    int width, height;

    /*
    Korištenje std::vector<Color> za piksele u strukturi Image ima smisla jer omogućava fleksibilno upravljanje pikselima slike.
    Evo nekoliko razloga zašto je std::vector<Color> odabran:
    Dinamička veličina slike: std::vector omogućava jednostavno dodavanje i uklanjanje piksela iz slike.
    To znači da se veličina slike ne mora unaprijed odrediti, već se može prilagoditi prema potrebi.
    Jednostavno pristupanje pikselima: Korištenje vektora olakšava pristupanje pikselima slike pomoću indeksiranja.
    Svaki piksel može se dohvatiti pomoću indeksa, na primjer pixels[i], gdje i predstavlja poziciju piksela u vektoru.
    Optimalno korištenje memorije: Kada se vektor stvori s određenom početnom veličinom (kao u konstruktoru Image(int w, int h)),
    memorija se rezervira unaprijed za sve piksele slike. To može poboljšati performanse i učiniti upravljanje memorijom efikasnijim.
    Jednostavna manipulacija slikom: Korištenje vektora omogućava različite operacije nad slikom, poput kopiranja,
    izmjene boja piksela ili primjene filtera, što olakšava rad s slikama u raznim aplikacijama.
    Korištenje Color strukture u vektoru omogućava pohranjivanje boja svakog piksela na jednom mjestu.
    Svaki element vektora predstavlja jedan piksel s tri komponente boje (crvena, zelena, plava),
    što olakšava manipulaciju i analizu piksela u slici.
*/

    std::vector<Color> pixels;

    Image(int w, int h) : width(w), height(h), pixels(w* h) {}
};



// Funkcija za primenu konvolucije na sliku

/*
    Ova funkcija implementira postupak konvolucije nad slikom koristeći zadani kernel.
    Evo detaljnog objašnjenja koraka koje funkcija izvršava:
    Izračunavanje veličine kernela: Funkcija prvo izračunava veličinu kernela, što je korisno za iteriranje kroz kernel.
    Veličina kernela se određuje kao kvadratni korijen od ukupnog broja elemenata u kernelu.
    Iteriranje kroz sliku: Koristeći dvije ugniježđene petlje, funkcija iterira kroz svaki piksel slike.
    Vanjska petlja prolazi kroz redove slike (y-koordinate), dok unutarnja petlja prolazi kroz piksele u svakom retku (x-koordinate).
    Primjena konvolucije: Za svaki piksel, funkcija primjenjuje konvoluciju koristeći zadani kernel.
    Unutar svakog piksela,
    prolazi se kroz sve elemente kernela i za svaki piksel u blizini trenutnog piksela se primjenjuje odgovarajući element kernela.
    Ovo uključuje računanje ponderirane sume vrijednosti boje piksela susjednih piksela prema kernelu.
    Pohrana rezultata: Nakon primjene konvolucije, rezultat se pohranjuje u odgovarajući piksel izlazne slike.
    Boja svakog piksela izlazne slike se računa kao težinska suma boja susjednih piksela prema kernelu.
    Ograničavanje vrijednosti boja: Kako bi se osiguralo da rezultati ostanu unutar raspona [0, 255],
    vrijednosti boja su ograničene na taj raspon.
    Osim toga, ova funkcija je paralelizirana pomoću #pragma omp parallel for collapse(2),
    što omogućava istovremenu obradu više piksela slike u više niti, poboljšavajući performanse algoritma na višejezgarnim procesorima.
*/
void convolution(const Image& input, const std::vector<float>& kernel, Image& output) {
    int kernelSize = static_cast<int>(std::sqrt(kernel.size()));
    int kernelRadius = kernelSize / 2;

#pragma omp parallel for collapse(2)
    for (int y = 0; y < input.height; ++y) {
        for (int x = 0; x < input.width; ++x) {
            float sumRed = 0, sumGreen = 0, sumBlue = 0;

            for (int ky = -kernelRadius; ky <= kernelRadius; ++ky) {
                for (int kx = -kernelRadius; kx <= kernelRadius; ++kx) {
                    int imgX = std::max(0, std::min(input.width - 1, x + kx));
                    int imgY = std::max(0, std::min(input.height - 1, y + ky));

                    int kernelIndex = (ky + kernelRadius) * kernelSize + (kx + kernelRadius);
                    sumBlue += input.pixels[imgY * input.width + imgX].blue * kernel[kernelIndex];
                    sumGreen += input.pixels[imgY * input.width + imgX].green * kernel[kernelIndex];
                    sumRed += input.pixels[imgY * input.width + imgX].red * kernel[kernelIndex];
                }
            }

            output.pixels[y * input.width + x].blue = static_cast<uint8_t>(std::max(0.0f, std::min(255.0f, sumBlue)));
            output.pixels[y * input.width + x].green = static_cast<uint8_t>(std::max(0.0f, std::min(255.0f, sumGreen)));
            output.pixels[y * input.width + x].red = static_cast<uint8_t>(std::max(0.0f, std::min(255.0f, sumRed)));
        }
    }
}

/*
    Ovaj sljedeci code snippet definira strukturu BMPHeader koja predstavlja zaglavlje BMP (Bitmap) datoteke.

    Evo objašnjenja svake od svojstava u ovoj strukturi:
    uint16_t signature: Ovo je 2-bajtno polje koje sadrži potpis BMP formata.
    Uobičajeno je da ima vrijednost 0x4D42 (ili "BM" u ASCII formatu) kako bi označilo da je datoteka BMP formatirana.

    uint32_t fileSize: Ovo je 4-bajtno polje koje sadrži veličinu cijele BMP datoteke u bajtovima.

    uint32_t reserved: Ovo je 4-bajtno polje koje se obično ne koristi. Obično se postavlja na nulu.

    uint32_t dataOffset: Ovo je 4-bajtno polje koje sadrži pomak (offset) od početka datoteke do početka pikselskih podataka.

    Ono označava gdje započinju podaci slike u datoteci.

    uint32_t headerSize: Ovo je 4-bajtno polje koje sadrži veličinu zaglavlja BMP datoteke.
    Uobičajeno je da ima vrijednost 40 bajtova.

    int32_t width: Ovo je 4-bajtno polje koje sadrži širinu slike u pikselima.

    int32_t height: Ovo je 4-bajtno polje koje sadrži visinu slike u pikselima.

    uint16_t planes: Ovo je 2-bajtno polje koje označava broj ravni slike. 

    Uobičajeno je da ima vrijednost 1.

    uint16_t bitsPerPixel: 
    Ovo je 2-bajtno polje koje označava broj bitova po pikselu. 
    Obično se koristi 24 za 24-bitnu sliku (RGB).

    uint32_t compression: 
    Ovo je 4-bajtno polje koje označava način kompresije slike. 
    Obično je postavljeno na 0 za nekompresiranu sliku.

    uint32_t imageSize: 
    Ovo je 4-bajtno polje koje označava veličinu pikselskih podataka slike. 
    Ako je slika nekompresirana, ovo obično ima vrijednost 0.

    int32_t xPixelsPerMeter i int32_t yPixelsPerMeter: 
    Ovo su 4-bajtna polja koja označavaju broj piksela po metru u horizontalnom i vertikalnom smjeru. 
    Obično se postavljaju na 0.

    uint32_t colorsUsed: 
    Ovo je 4-bajtno polje koje označava broj boja u paleti. 
    Ako se koristi cijela paleta, obično je postavljeno na 0.

    uint32_t colorsImportant: 
    Ovo je 4-bajtno polje koje označava broj bitova koji su važni za prikaz boja. 
    Ako su svi bitovi važni, obično je postavljeno na 0.

    #pragma pack(push, 1) i #pragma pack(pop) su direktive preprocesora koje kontroliraju poravnanje struktura u memoriji. 
    U ovom slučaju, #pragma pack(push, 1) govori kompilatoru da koristi poravnanje od 1 bajta za strukture koje slijede,
    što znači da se svaki član strukture pohranjuje bez dodatnih praznina između članova. 
    Ovo se obično koristi kako bi se osiguralo da struktura ima istu veličinu u memoriji kao što se očekuje, 
    što može biti važno prilikom čitanja ili pisanja binarnih datoteka.
    #pragma pack(pop) vraća originalne postavke poravnanja nakon što je definicija strukture završena.
*/
#pragma pack(push, 1)  // Isključivanje poravnanja bajtova u strukturi
struct BMPHeader {
    uint16_t signature;
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t dataOffset;
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};
#pragma pack(pop)

// Funkcija za učitavanje BMP slike
std::vector<Color> loadBMP1(const std::string& filename, int& width, int& height) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Nije moguće otvoriti fajl: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    BMPHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));

    if (header.signature != 0x4D42) {  // "BM" u little-endian formatu
        std::cerr << "Nevažeći BMP format: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    if (header.bitsPerPixel != 24) {
        std::cerr << "Očekuje se 24-bitni BMP format, ali datoteka ima " << header.bitsPerPixel << " bita po pikselu." << std::endl;
        exit(EXIT_FAILURE);
    }

    width = header.width;
    height = header.height;

    std::vector<Color> pixels(width * height);
    file.seekg(header.dataOffset);

    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            Color pixel;
            file.read(reinterpret_cast<char*>(&pixel), sizeof(Color));
            pixels[y * width + x] = pixel;
        }

        // Preskakanje eventualnih bajtova poravnanja na kraju reda
        int padding = (4 - (width * sizeof(Color)) % 4) % 4;
        file.seekg(padding, std::ios::cur);
    }

    return pixels;
}

/*
* Ovo je funkcija za učitavanje BMP slike iz datoteke. 
  Evo objašnjenja koraka u funkciji:

    1. `std::vector<Color> loadBMP1(const std::string& filename, int& width, int& height)
        {`: Ova funkcija prima ime datoteke BMP slike (`filename`) i reference na varijable `width` i `height`
        koje će se ažurirati s dimenzijama učitane slike. 
        Vraća vektor piksela slike.

    2. `std::ifstream file(filename, std::ios::binary);`: 
        Otvara se ulazni tok datoteke u binarnom modu koristeći `std::ifstream`.
        Ako nije moguće otvoriti datoteku, ispisuje se odgovarajuća greška i program se završava.

    3. `BMPHeader header;`: Deklarira se promjenjiva `header` tipa `BMPHeader` koja će sadržavati zaglavlje BMP datoteke.

    4. `file.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));`: Učitava se zaglavlje datoteke u promjenjivu `header`.

    5. `if (header.signature != 0x4D42) {`: Provjerava se potpis BMP formata. 
    Ako potpis nije "BM" (0x4D42), ispisuje se greška i program se završava.

    6. `if (header.bitsPerPixel != 24) {`: Provjerava se broj bitova po pikselu. 
        Ako nije 24, što bi ukazivalo na 24-bitni RGB format slike, ispisuje se greška i program se završava.

    7. `width = header.width; height = header.height;`: 
    Postavljaju se širina i visina slike na osnovu vrijednosti iz zaglavlja.

    8. `std::vector<Color> pixels(width * height);`:
    Stvara se vektor `pixels` koji će sadržavati piksele slike. Veličina vektora se postavlja na `width * height`.

    9. `file.seekg(header.dataOffset);`: 
    Pomakne se čitač datoteke na početak pikselskih podataka, kako je određeno u zaglavlju.

    10. `for (int y = height - 1; y >= 0; --y) { for (int x = 0; x < width; ++x) { ... } }`:
    U petlji se čitaju pikseli slike iz datoteke. Prolazi se kroz svaki red od zadnjeg prema prvom, 
    zbog načina na koji su pikseli pohranjeni u BMP formatu.

    11. `file.read(reinterpret_cast<char*>(&pixel), sizeof(Color));`: 
    Učitava se piksel iz datoteke i smješta u promjenjivu `pixel`.

    12. `pixels[y * width + x] = pixel;`: 
    Piksel se dodaje u vektor piksela na odgovarajuću poziciju.

    13. `int padding = (4 - (width * sizeof(Color)) % 4) % 4;`:
    Izračunava se broj bajtova poravnanja na kraju svakog reda. 
    To je neophodno jer su retci u BMP datoteci poravnati na riječnu granicu (obično 4 bajta).

    14. `file.seekg(padding, std::ios::cur);`:
    Čitač se pomjera prema naprijed za broj bajtova poravnanja, preskačući eventualne praznine na kraju reda.

    15. `return pixels;`: Vraća se vektor piksela koji sadrži učitane piksele slike.
*/

// Funkcija za učitavanje BMP slike
std::vector<Color> loadBMP2(const std::string& filename, int& width, int& height) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Nije moguće otvoriti fajl: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    BMPHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));

    if (header.signature != 0x4D42) {  // "BM" u little-endian formatu
        std::cerr << "Nevažeći BMP format: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    if (header.bitsPerPixel != 24) {
        std::cerr << "Očekuje se 24-bitni BMP format, ali datoteka ima " << header.bitsPerPixel << " bita po pikselu." << std::endl;
        exit(EXIT_FAILURE);
    }

    width = header.width;
    height = header.height;

    std::vector<Color> pixels(width * height);
    file.seekg(header.dataOffset);

    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            Color pixel;
            file.read(reinterpret_cast<char*>(&pixel), sizeof(Color));
            pixels[y * width + x] = pixel;
        }

        // Preskakanje eventualnih bajtova poravnanja na kraju reda
        int padding = (4 - (width * sizeof(Color)) % 4) % 4;
        file.seekg(padding, std::ios::cur);
    }

    return pixels;
}


/*
*    Ova funkcija `saveBMP` koristi se za spremanje slike u BMP formatu u datoteku. 
    Evo detaljnog objašnjenja koraka u funkciji:

    1. `void saveBMP(const std::string& filename, const Image& image) 
        {`: Ova funkcija prima ime datoteke u koju će se spremiti slika (`filename`) 
        i konstantnu referencu na objekt `Image` koji sadrži sliku koja se sprema.

    2. `std::ofstream file(filename, std::ios::binary);`: 
        Otvaramo izlazni tok datoteke u binarnom modu koristeći `std::ofstream`. 
           Ako nije moguće otvoriti datoteku, ispisuje se odgovarajuća greška i program se završava.

    3. `BMPHeader header;`: 
        Stvara se zaglavlje BMP datoteke koje će se koristiti za postavljanje metapodataka slike.

    4. Postavljanje vrijednosti zaglavlja BMP datoteke na odgovarajuće vrijednosti. Ovdje se postavljaju:
        - `signature`: Potpis BMP formata ("BM" u little-endian formatu).
        - `fileSize`: Veličina datoteke, uključujući zaglavlje i piksele slike.
        - `reserved`: Rezervirano, obično 0.
        - `dataOffset`: Pomak do početka pikselskih podataka u datoteci.
        - `headerSize`: Veličina zaglavlja, obično 40 bajta.
        - `width` i `height`: Širina i visina slike.
        - `planes`: Broj ravni u BMP datoteci, obično 1.
        - `bitsPerPixel`: Broj bitova po pikselu, u ovom slučaju 24 jer se koristi 24-bitni RGB format.
        - `compression`: Metoda kompresije, obično 0 za nekomprimirane slike.
        - `imageSize`: Veličina podataka slike, uključujući piksele.
        - `xPixelsPerMeter` i `yPixelsPerMeter`: Broj piksela po metru, obično 0.
        - `colorsUsed` i `colorsImportant`: Broj boja koje se koriste i koje su bitne za prikaz, obično 0 za 24-bitne slike.

    5. `file.write(reinterpret_cast<char*>(&header), sizeof(BMPHeader));`: 
        Zaglavlje se zapisuje u datoteku.

    6. Nakon zaglavlja, pikseli slike se zapisuju u datoteku. 
       Prolazi se kroz svaki red slike, od zadnjeg prema prvom, zbog načina na koji su pikseli pohranjeni u BMP formatu.

    7. Svaki piksel se zapisuje u datoteku koristeći `file.write` metodu. 
       Pristupamo pikselu u vektoru piksela pomoću indeksiranja po koordinatama (x, y) i koristimo `reinterpret_cast` kako bismo 
       dobili pokazivač na bajtove piksela.

    8. Nakon što su svi pikseli zapisani za red, dodaje se odgovarajući broj bajtova poravnanja na kraju reda. 
       To je neophodno jer su retci u BMP datoteci poravnati na riječnu granicu (obično 4 bajta).

    Ovim koracima se osigurava da se slika ispravno spremi u BMP formatu u datoteku.
*/
// Funkcija za čuvanje BMP slike
void saveBMP(const std::string& filename, const Image& image) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Nije moguće otvoriti fajl za čuvanje: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    // Header za BMP fajl
    BMPHeader header;
    header.signature = 0x4D42;  // "BM" u little-endian formatu
    header.fileSize = sizeof(BMPHeader) + image.width * image.height * sizeof(Color) + image.height * (4 - (image.width * sizeof(Color)) % 4) % 4;
    header.reserved = 0;
    header.dataOffset = sizeof(BMPHeader);
    header.headerSize = 40;
    header.width = image.width;
    header.height = image.height;
    header.planes = 1;
    header.bitsPerPixel = 24;
    header.compression = 0;
    header.imageSize = image.width * image.height * sizeof(Color);
    header.xPixelsPerMeter = 0;
    header.yPixelsPerMeter = 0;
    header.colorsUsed = 0;
    header.colorsImportant = 0;

    file.write(reinterpret_cast<char*>(&header), sizeof(BMPHeader));

    // Upisivanje piksela slike
    for (int y = image.height - 1; y >= 0; --y) {
        for (int x = 0; x < image.width; ++x) {
            file.write(reinterpret_cast<char*>(const_cast<Color*>(&image.pixels[y * image.width + x])), sizeof(Color));
        }

        // Dodavanje bajtova poravnanja na kraju reda
        int padding = (4 - (image.width * sizeof(Color)) % 4) % 4;
        for (int i = 0; i < padding; ++i) {
            file.put(0);
        }
    }
}

// Funkcija za analizu i obradu vrednosti kernela iz argumenata komandne linije
std::vector<float> parseKernelValues(const char* kernelArg) {
    std::vector<float> kernelValues;

    const char delimiter = ',';
    char* token = strtok(const_cast<char*>(kernelArg), &delimiter);

    while (token != nullptr) {
        float value = atof(token);  // Konvertujte string u float
        kernelValues.push_back(value);
        token = strtok(nullptr, &delimiter);
    }

    return kernelValues;
}


int main(int argc, char* argv[]) {

    if (argc != 3) {
        std::cerr << "Upotreba: " << argv[0] << " <ulazna_datoteka.bmp> <izlazna_datoteka.bmp>" << std::endl;
        return EXIT_FAILURE;
    }

    // Učitavanje putanja iz argumenata komandne linije
    std::string ulaznaPutanja = argv[1];
    std::string izlaznaPutanja = argv[2];


    // Učitavanje slike iz BMP fajla (pretpostavljamo 24-bitni nekompresovani BMP format)
    int width = 0, height = 0;
    std::vector<Color> pixels = loadBMP2("ulaznaSlika.bmp", width, height);

    Image inputImage(width, height);
    inputImage.pixels = pixels;

    // Definisanje kernela za konvoluciju 
    std::vector<float> kernelIdentity = { 0, -1, 0, -1, 5, -1, 0, -1, 0 };  

    std::vector<float> kernelGaussianBlur = {
        0.0625, 0.125, 0.0625,
        0.125, 0.25, 0.125,
        0.0625, 0.125, 0.0625 };

    std::vector<float> kernelEdgeDetection = {
        -1, -1, -1,
        -1, 8, -1,
        -1, -1, -1 };

    std::vector<float> kernelBoxBlur = {
        0.1111, 0.1111, 0.1111,
        0.1111, 0.1111, 0.1111,
        0.1111, 0.1111, 0.1111
    };

    std::vector<float> kernelSharpen = { 
        0, -1, 0,
        -1, 5, -1,
        0, -1, 0
    };


    // Primena konvolucije
    Image outputImage(width, height);
    convolution(inputImage, kernelEdgeDetection, outputImage);

    // Čuvanje rezultata slike u BMP fajl
    saveBMP("izlaznaSlika.bmp", outputImage);

    return 0;
}


/*
int main(int argc, char* argv[]) {

    auto startTimeProgram = std::chrono::high_resolution_clock::now();

    if (argc != 5) {
        std::cerr << "Upotreba: " << argv[0] << " <ulazna_datoteka.bmp> <izlazna_datoteka.bmp>" << std::endl;
        return EXIT_FAILURE;
    }

    // Učitavanje putanja iz argumenata komandne linije
    std::string ulaznaPutanja = argv[1];
    std::string izlaznaPutanja = argv[2];

    // Učitavanje vrednosti kernela iz argumenata komandne linije
    std::vector<float> kernel = parseKernelValues(argc > 3 ? argv[4] : nullptr);

    // Učitavanje slike iz BMP fajla (pretpostavljamo 24-bitni nekompresovani BMP format)
    int width = 0, height = 0;
    std::vector<Color> pixels = loadBMP2(argv[1], width, height);

    Image inputImage(width, height);
    inputImage.pixels = pixels;

    // Definisanje kernela za konvoluciju (primer: identity kernel ako nije zadat)
    int kernelSize = 3;
    if (kernel.empty()) {
        kernel = { 0, -1, 0, -1, 5, -1, 0, -1, 0 };  // Podrazumevani identity kernel
    }

    // Primena konvolucije
    Image outputImage(width, height);

    // Merenje vremena izvršavanja
    const int num_trials = 10;  // Broj ponavljanja za svaki ulaz

    // Čuvanje rezultata slike u BMP fajl
    saveBMP(izlaznaPutanja.c_str(), outputImage);

    auto stopTimeProgram = std::chrono::high_resolution_clock::now();
    auto durationProgram = std::chrono::duration_cast<std::chrono::microseconds>(stopTimeProgram - startTimeProgram);
    std::cout << "Ukupno vreme izvrsavanja programa: " << durationProgram.count() << " mikrosekundi" << std::endl;

    return 0;
}
*/