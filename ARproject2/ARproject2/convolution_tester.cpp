#include "convolution_tester.h"

void ConvolutionTester::runTest(const std::string& inputPath, const std::string& outputPath, const std::vector<float>& kernel){
    int width = 0, height = 0;
    std::vector<Color> pixels = loadBMP2(inputPath, width, height);

    Image inputImage(width, height);
    inputImage.pixels = pixels;

    // Start measuring time
    auto start = std::chrono::steady_clock::now();

    Image outputImage(width, height);

    convolution(inputImage, kernel, outputImage);

    // Stop measuring time
    auto end = std::chrono::steady_clock::now();

    // Calculate execution time in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Output execution time to console
    std::cout << "Convolution operation took " << duration << " milliseconds." << std::endl;

    saveBMP(outputPath, outputImage);
}

void ConvolutionTester::runTests(   const std::vector<std::string>& inputPaths, 
                                    const std::vector<std::string>& outputPaths, 
                                    const std::vector<float>& kernel){

    for (size_t i = 0; i < inputPaths.size(); ++i) {
        runTest(inputPaths[i], outputPaths[i], kernel);
    }
}