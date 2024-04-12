#include "convolution.h"

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