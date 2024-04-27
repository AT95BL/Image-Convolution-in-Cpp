#include "imageFolder.h"

// Funkcija koja čuva sliku u odgovarajući folder
void saveImageToFolder(const Image& outputImage, const std::string& folderPath, const std::string& imageName) {
    // Formirajte putanju do foldera
    fs::path folder(folderPath);

    // Proverite da li folder postoji, ako ne, kreirajte ga
    if (!fs::exists(folder))
        fs::create_directory(folder);

    // Formirajte putanju do slike
    fs::path imagePath = folder / imageName;

    // Čuvanje slike u BMP formatu
    saveBMP(imagePath.string(), outputImage);
}