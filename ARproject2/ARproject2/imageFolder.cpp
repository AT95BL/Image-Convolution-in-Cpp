#include "imageFolder.h"

// Function that saves the image to the appropriate folder
void saveImageToFolder(const Image& outputImage, const std::string& folderPath, const std::string& imageName) {
    // Form the path to the folder
    fs::path folder(folderPath);

    // Check if the folder exists, and if not, create it
    if (!fs::exists(folder))
        fs::create_directory(folder);

    // Form the path to the image
    fs::path imagePath = folder / imageName;

    // Saving the image in BMP format
    saveBMP(imagePath.string(), outputImage);
}