#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>


// Structure for representing color (24-bit BMP format)
struct Color {

    uint8_t blue, green, red;

    Color() : blue(0), green(0), red(0) {}
    Color(uint8_t b, uint8_t g, uint8_t r) : blue(b), green(g), red(r) {}
};

// Structure for representing an image
struct Image {

    int width, height;

    /*
    Using `std::vector<Color>` for pixels in the `Image` structure makes sense because it allows flexible management of image pixels.
    Here are several reasons why `std::vector<Color>` was chosen:

    * Dynamic image size: `std::vector` allows easy addition and removal of pixels from the image.
      This means that the image size does not need to be predetermined and can be adjusted as needed.

    * Easy access to pixels: Using a vector simplifies access to the image pixels via indexing.
      Each pixel can be retrieved using an index, for example `pixels[i]`, where `i` represents the pixel’s position in the vector.

    * Optimal memory usage: When a vector is created with a specific initial size (as in the constructor `Image(int w, int h)`),
      memory is reserved in advance for all image pixels. This can improve performance and make memory management more efficient.

    * Easy image manipulation: Using a vector allows various operations on the image, such as copying,
      changing pixel colors, or applying filters, which simplifies working with images in different applications.

    * Color structure integration: Using the `Color` structure in the vector allows storing the color of each pixel in one place.
      Each element of the vector represents a single pixel with three color components (red, green, blue),
      making it easier to manipulate and analyze pixels in the image.
     */

        std::vector<Color> pixels;

        Image(int w, int h) : width(w), height(h), pixels(w* h) {}
    };

    std::vector<Color> loadBMP1(const std::string&, int&, int&);

    std::vector<Color> loadBMP2(const std::string&, int&, int&);

    /*
    The following code snippet defines the `BMPHeader` structure, which represents the header of a BMP (Bitmap) file.

    Here is an explanation of each property in this structure:

    * `uint16_t signature`: This is a 2-byte field that contains the BMP format signature.
      It is usually set to `0x4D42` (or "BM" in ASCII) to indicate that the file is in BMP format.

    * `uint32_t fileSize`: A 4-byte field containing the size of the entire BMP file in bytes.

    * `uint32_t reserved`: A 4-byte field that is usually unused. It is typically set to zero.

    * `uint32_t dataOffset`: A 4-byte field indicating the offset from the start of the file to the beginning of the pixel data.
      It shows where the image data begins in the file.

    * `uint32_t headerSize`: A 4-byte field containing the size of the BMP header.
      It is usually 40 bytes.

    * `int32_t width`: A 4-byte field representing the width of the image in pixels.

    * `int32_t height`: A 4-byte field representing the height of the image in pixels.

    * `uint16_t planes`: A 2-byte field indicating the number of image planes.
      It is usually set to 1.

    * `uint16_t bitsPerPixel`: A 2-byte field representing the number of bits per pixel.
      Typically 24 for a 24-bit image (RGB).

    * `uint32_t compression`: A 4-byte field indicating the compression method used for the image.
      Usually 0 for uncompressed images.

    * `uint32_t imageSize`: A 4-byte field representing the size of the pixel data.
      For uncompressed images, this is usually 0.

    * `int32_t xPixelsPerMeter` and `int32_t yPixelsPerMeter`: 4-byte fields indicating the number of pixels per meter in horizontal and vertical directions.
      Usually set to 0.

    * `uint32_t colorsUsed`: A 4-byte field representing the number of colors in the palette.
      If the entire palette is used, it is usually set to 0.

    * `uint32_t colorsImportant`: A 4-byte field indicating the number of bits important for color display.
      If all bits are important, it is usually set to 0.

    * `#pragma pack(push, 1)` and `#pragma pack(pop)` are preprocessor directives that control structure alignment in memory.
      In this case, `#pragma pack(push, 1)` tells the compiler to use 1-byte alignment for the following structures,
      meaning each member of the structure is stored without additional padding between members.
      This is often used to ensure the structure has the exact size in memory as expected,
      which is important when reading or writing binary files.
      `#pragma pack(pop)` restores the original alignment settings after the structure definition.
    */

#pragma pack(push, 1)  // Disabling byte alignment in the structure
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

void saveBMP(const std::string&, const Image&);

