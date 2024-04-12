#include "image.h"
#include "convolution.h"
#include "kernel.h"


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

    Kernel::kernelIdentity;
    Kernel::kernelGaussianBlur;
    Kernel::kernelEdgeDetection;
    Kernel::kernelBoxBlur;
    Kernel::kernelSharpen;

    // Primena konvolucije
    Image outputImage(width, height);
    convolution(inputImage, Kernel::kernelEdgeDetection, outputImage);

    // Čuvanje rezultata slike u BMP fajl
    saveBMP("izlaznaSlika.bmp", outputImage);

    return 0;
}
