#include "image.h"

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