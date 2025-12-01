#include "convolution.h"

// Function for applying convolution to an image

/*
This function implements the process of convolution on an image using a given kernel.
Here is a detailed explanation of the steps the function performs:

**Calculating the kernel size:**
The function first calculates the size of the kernel, which is useful for iterating through it.
The size of the kernel is determined as the square root of the total number of elements in the kernel.

**Iterating through the image:**
Using two nested loops, the function iterates through every pixel of the image.
The outer loop goes through the rows of the image (y-coordinates), while the inner loop goes through the pixels in each row (x-coordinates).

**Applying convolution:**
For each pixel, the function applies convolution using the given kernel.
Within each pixel, it loops through all the elements of the kernel, and for each pixel near the current pixel, it applies the corresponding kernel value.
This includes computing the weighted sum of the color values of the neighboring pixels according to the kernel.

**Storing the result:**
After applying convolution, the result is stored in the appropriate pixel of the output image.
The color of each pixel in the output image is calculated as the weighted sum of the colors of the neighboring pixels according to the kernel.

**Clamping color values:**
To ensure that the results stay within the range [0, 255],
the color values are clamped to that range.

In addition, this function is parallelized using `#pragma omp parallel for collapse(2)`,
which allows multiple pixels of the image to be processed simultaneously across several threads, improving performance on multi-core processors.
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