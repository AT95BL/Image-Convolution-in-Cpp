#include "image.h"
#include "convolution.h"
#include "kernel.h"
#include "convolution_tester.h"

#include <fstream>

using namespace Kernel;

int main(int argc, char* argv[]) {

    int result = system("python imageGeneratorScript.py");

    // Proverava da li je sistemski poziv uspešno izvršen
    if (result == 0) {
        std::cout << "Skripta je uspešno izvršena." << std::endl;
    }
    else {
        std::cout << "Greška prilikom izvršavanja skripte." << std::endl;
    }

    // Čitanje broja test slika iz datoteke
    std::ifstream file("num_images.txt");
    int num_images;
    file >> num_images;
    file.close();

    std::vector<std::string> inputPaths;
    std::vector<std::string> outputPaths;

    for (int i = 1; i <= num_images; i++) {
        inputPaths.push_back("input" + std::to_string(i) + ".bmp");
        outputPaths.push_back("output" + std::to_string(i) + ".bmp");
    }

    int n_for_kernel_choice;
    ConvolutionTester tester;
    bool loop = true;
    bool testing;

    std::cout << "Zelite li da izvrsite testiranje: " << std::endl
        << "1 za Da" << std::endl
        << "0 za Ne" << std::endl;
    std::cin >> testing;

    if (testing) {

        while (loop) {

            std::cout << "\n\n-Odaberite Sebi Odgovarajuci Kernel-" << std::endl
                << "1 za Identity Kernel " << std::endl
                << "2 za Gaussian Blur Kernel" << std::endl
                << "3 za Edge Detection Kernel" << std::endl
                << "4 za Box Blur Kernel" << std::endl
                << "5 za Sharpen Kernel " << std::endl
                << "0.za izlaz" << std::endl;
            do {
                std::cin >> n_for_kernel_choice;
            } while (n_for_kernel_choice < 0 || n_for_kernel_choice > 5);

            switch (n_for_kernel_choice) {

            case 1:
                std::cout << "Konvolucija slike koristenjem korisnicki definisane funkcije: " << std::endl;
                tester.runTests1(inputPaths, outputPaths, kernelIdentity);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv biblioteke: " << std::endl;
                tester.runTests2(inputPaths, outputPaths, kernelIdentity);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv(SIMD optimized) biblioteke: " << std::endl;
                tester.runTests3(inputPaths, outputPaths, kernelIdentity);
                break;

            case 2:
                std::cout << "Konvolucija slike koristenjem korisnicki definisane funkcije: " << std::endl;
                tester.runTests1(inputPaths, outputPaths, kernelGaussianBlur);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv biblioteke: " << std::endl;
                tester.runTests2(inputPaths, outputPaths, kernelGaussianBlur);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv(SIMD optimized) biblioteke: " << std::endl;
                tester.runTests3(inputPaths, outputPaths, kernelGaussianBlur);
                break;

            case 3:
                std::cout << "Konvolucija slike koristenjem korisnicki definisane funkcije: " << std::endl;
                tester.runTests1(inputPaths, outputPaths, kernelEdgeDetection);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv biblioteke: " << std::endl;
                tester.runTests2(inputPaths, outputPaths, kernelEdgeDetection);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv(SIMD optimized) biblioteke: " << std::endl;
                tester.runTests3(inputPaths, outputPaths, kernelEdgeDetection);
                break;

            case 4:
                std::cout << "Konvolucija slike koristenjem korisnicki definisane funkcije: " << std::endl;
                tester.runTests1(inputPaths, outputPaths, kernelBoxBlur);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv biblioteke: " << std::endl;
                tester.runTests2(inputPaths, outputPaths, kernelBoxBlur);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv(SIMD optimized) biblioteke: " << std::endl;
                tester.runTests3(inputPaths, outputPaths, kernelBoxBlur);
                break;

            case 5:
                std::cout << "Konvolucija slike koristenjem korisnicki definisane funkcije: " << std::endl;
                tester.runTests1(inputPaths, outputPaths, kernelSharpen);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv biblioteke: " << std::endl;
                tester.runTests2(inputPaths, outputPaths, kernelSharpen);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv(SIMD optimized) biblioteke: " << std::endl;
                tester.runTests3(inputPaths, outputPaths, kernelSharpen);
                break;

            case 0:
                loop = false;
                break;
            }
        }
    }

    return 0;
}


/*
int main(){

    // Učitavanje slike iz BMP fajla (pretpostavljamo 24-bitni nekompresovani BMP format)
    int width = 0, height = 0;
    std::vector<Color> pixels = loadBMP2("ulaznaSlika.bmp", width, height);

    Image inputImage(width, height);
    inputImage.pixels = pixels;

    Kernel::kernelIdentity;
    Kernel::kernelGaussianBlur;
    Kernel::kernelEdgeDetection;
    Kernel::kernelBoxBlur;
    Kernel::kernelSharpen;

    int n;
    std::cout << "-Odaberite Sebi Odgovarajuci Kernel-" << std::endl
        << "1 za Identity Kernel " << std::endl
        << "2 za Gaussian Blur Kernel" << std::endl
        << "3 za Edge Detection Kernel" << std::endl
        << "4 za Box Blur Kernel" << std::endl
        << "5 za Sharpen Kernel " << std::endl;
    do {
        std::cin >> n;
    } while (0 < n || n > 5);

    // Primena konvolucije
    Image outputImage(width, height);
    convolution(inputImage, Kernel::kernelEdgeDetection, outputImage);

    // Čuvanje rezultata slike u BMP fajl
    saveBMP("izlaznaSlika.bmp", outputImage);

}
*/