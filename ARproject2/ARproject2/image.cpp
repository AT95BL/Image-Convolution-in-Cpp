#include "image.h"
/*
This is a function for loading a BMP image from a file.
Here is an explanation of the steps in the function:

1. std::vector<Color> loadBMP1(const std::string& filename, int& width, int& height) {
   This function takes the BMP file name (`filename`) and references to the variables `width` and `height`,
   which will be updated with the dimensions of the loaded image.
   It returns a vector of the image’s pixels.

2. std::ifstream file(filename, std::ios::binary);
   Opens an input file stream in binary mode using `std::ifstream`.
   If the file cannot be opened, an appropriate error is printed and the program terminates.

3. BMPHeader header;
   Declares a variable `header` of type `BMPHeader` which will hold the BMP file header.

4. file.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
   Reads the file header into the `header` variable.

5. if (header.signature != 0x4D42) {
   Checks the BMP signature.
   If the signature is not "BM" (0x4D42), an error is printed and the program terminates.

6. if (header.bitsPerPixel != 24) {
   Checks the number of bits per pixel.
   If it is not 24, which would indicate a 24-bit RGB image format, an error is printed and the program terminates.

7. width = header.width; height = header.height;
   Sets the image width and height based on the values from the header.

8. std::vector<Color> pixels(width * height);
   Creates a `pixels` vector that will hold the image pixels.
   The size of the vector is set to `width * height`.

9. file.seekg(header.dataOffset);
   Moves the file's read cursor to the start of the pixel data, as indicated in the header.

10. for (int y = height - 1; y >= 0; --y) { for (int x = 0; x < width; ++x) { ... } }
    Loops through the image pixels being read from the file.
    It processes each row from bottom to top because BMP stores rows in reverse order.

11. file.read(reinterpret_cast<char*>(&pixel), sizeof(Color));
    Reads a pixel from the file and stores it in the variable `pixel`.

12. pixels[y * width + x] = pixel;
    Stores the pixel in the appropriate position inside the pixel vector.

13. int padding = (4 - (width * sizeof(Color)) % 4) % 4;
    Calculates the padding bytes at the end of each row.
    This is necessary because rows in a BMP file are aligned to 4-byte boundaries.

14. file.seekg(padding, std::ios::cur);
    Moves the read cursor forward by the number of padding bytes, skipping any empty space at the end of the row.

15. return pixels;
    Returns the pixel vector containing the loaded image pixels.


/*

// Function for loading a BMP image
std::vector<Color> loadBMP1(const std::string& filename, int& width, int& height) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    BMPHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));

    if (header.signature != 0x4D42) {  // "BM" in little-endian format
        std::cerr << "Invalid BMP format: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    if (header.bitsPerPixel != 24) {
        std::cerr << "Expected a 24-bit BMP format, but the file has " << header.bitsPerPixel << " bits per pixel." << std::endl;
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

        // Skipping any padding bytes at the end of the row
        int padding = (4 - (width * sizeof(Color)) % 4) % 4;
        file.seekg(padding, std::ios::cur);
    }

    return pixels;
}

// Function for loading a BMP image
std::vector<Color> loadBMP2(const std::string& filename, int& width, int& height) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open the file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    BMPHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));

    if (header.signature != 0x4D42) {  // "BM" in little-endian format
        std::cerr << "Nevažeći BMP format: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    if (header.bitsPerPixel != 24) {
        std::cerr << "Expected a 24-bit BMP format, but the file has " << header.bitsPerPixel << " bits per pixel." << std::endl;
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

        // Skipping any potential padding bytes at the end of the row
        int padding = (4 - (width * sizeof(Color)) % 4) % 4;
        file.seekg(padding, std::ios::cur);
    }

    return pixels;
}

/*
*    This function `saveBMP` is used to save an image in BMP format to a file.
     Here is a detailed explanation of the steps in the function:

    1. `void saveBMP(const std::string& filename, const Image& image)
        {`: This function takes the name of the file in which the image will be saved (`filename`)
         a constant reference to an `Image` object that contains the image to be saved.

    2. `std::ofstream file(filename, std::ios::binary);`:
        We open an output file stream in binary mode using std::ofstream.
        If the file cannot be opened, an appropriate error is printed and the program terminates.

    3. `BMPHeader header;`:
        A BMP file header is created, which will be used to set the image metadata.

    4. Setting the values of the BMP file header to the appropriate values. Here we set:
         signature: BMP format signature ("BM" in little-endian format).
         fileSize: The size of the file, including the header and image pixels.
         reserved: Reserved, usually 0.
         dataOffset: Offset to the start of the pixel data in the file.
         headerSize: Size of the header, usually 40 bytes.
         width and height: Width and height of the image.
         planes: Number of planes in the BMP file, usually 1.
         bitsPerPixel: Number of bits per pixel, in this case 24, as 24-bit RGB format is used.
         compression: Compression method, usually 0 for uncompressed images.
         imageSize: Size of the image data, including the pixels.
         xPixelsPerMeter and yPixelsPerMeter: Number of pixels per meter, usually 0.
         colorsUsed and colorsImportant: Number of colors used and important for display, usually 0 for 24-bit images.
 

    5. `file.write(reinterpret_cast<char*>(&header), sizeof(BMPHeader));`:
        The header is written to the file.

    6. After the header, the image pixels are written to the file.
       Each row of the image is processed from the last to the first, due to the way pixels are stored in the BMP format.

    7. Each pixel is written to the file using the `file.write` method.
       We access a pixel in the pixel vector using (x, y) coordinate indexing and use `reinterpret_cast` to obtain a pointer to the pixel bytes.

    8. After all pixels for a row are written, the corresponding number of padding bytes is added at the end of the row.
This is necessary because rows in a BMP file are aligned to a word boundary (usually 4 bytes).

    These steps ensure that the image is correctly saved in BMP format to the file.
*/

// Function for saving a BMP image

void saveBMP(const std::string& filename, const Image& image) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Nije moguće otvoriti fajl za čuvanje: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    // Header for BMP file
    BMPHeader header;
    header.signature = 0x4D42;  // "BM" in little-endian format
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

    // Writing the image pixels
    for (int y = image.height - 1; y >= 0; --y) {
        for (int x = 0; x < image.width; ++x) {
            file.write(reinterpret_cast<char*>(const_cast<Color*>(&image.pixels[y * image.width + x])), sizeof(Color));
        }

        // Adding padding bytes at the end of the row
        int padding = (4 - (image.width * sizeof(Color)) % 4) % 4;
        for (int i = 0; i < padding; ++i) {
            file.put(0);
        }
    }
}