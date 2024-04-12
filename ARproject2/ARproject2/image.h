#pragma once

#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>

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

std::vector<Color> loadBMP1(const std::string&, int&, int&);

std::vector<Color> loadBMP2(const std::string&, int&, int&);

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

void saveBMP(const std::string& , const Image& );

#endif // !IMAGE_H