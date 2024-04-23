#include "convolution_tester.h"

void ConvolutionTester::runTest1(const std::string& inputPath, const std::string& outputPath, const std::vector<float>& kernel){
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

void ConvolutionTester::runTests1(   const std::vector<std::string>& inputPaths, 
                                    const std::vector<std::string>& outputPaths, 
                                    const std::vector<float>& kernel){

    for (size_t i = 0; i < inputPaths.size(); ++i) {
        runTest1(inputPaths[i], outputPaths[i], kernel);
    }
}


void ConvolutionTester::runTest2(const std::string& inputPath, const std::string& outputPath, const std::vector<float>& kernel) {
    int width = 0, height = 0;
    std::vector<Color> pixels = loadBMP2(inputPath, width, height);

    Image inputImage(width, height);
    inputImage.pixels = pixels;

    // Start measuring time
    auto start = std::chrono::steady_clock::now();

    cv::Mat inputMat = cv::imread(inputPath, cv::IMREAD_COLOR);
    cv::Mat outputMat;

    cv::Mat kernelMat = cv::Mat(kernel).reshape(1, static_cast<int>(std::sqrt(kernel.size())));
    cv::filter2D(inputMat, outputMat, -1, kernelMat);

    // Stop measuring time
    auto end = std::chrono::steady_clock::now();

    // Calculate execution time in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Output execution time to console
    std::cout << "OpenCV Convolution operation took " << duration << " milliseconds." << std::endl;

    cv::imwrite(outputPath, outputMat);
}

void ConvolutionTester::runTests2(const std::vector<std::string>& inputPaths,
    const std::vector<std::string>& outputPaths,
    const std::vector<float>& kernel) {

    for (size_t i = 0; i < inputPaths.size(); ++i) {
        runTest2(inputPaths[i], outputPaths[i], kernel);
    }
}

void ConvolutionTester::runTest3(const std::string& inputPath, const std::string& outputPath, const std::vector<float>& kernel) {
    int width = 0, height = 0;
    std::vector<Color> pixels = loadBMP2(inputPath, width, height);

    Image inputImage(width, height);
    inputImage.pixels = pixels;

    // Convert kernel to cv::Mat
    cv::Mat kernelMat = cv::Mat(kernel).reshape(1, static_cast<int>(std::sqrt(kernel.size())));

    // Start measuring time
    auto start = std::chrono::steady_clock::now();

    // Prepare input data
    cv::Mat inputMat(height, width, CV_8UC3, inputImage.pixels.data());

    // Prepare output data
    cv::Mat outputMat(height, width, CV_8UC3);

    // Perform convolution using SIMD optimization
    cv::filter2D(inputMat, outputMat, -1, kernelMat, cv::Point(-1, -1), 0, cv::BORDER_CONSTANT);

    // Stop measuring time
    auto end = std::chrono::steady_clock::now();

    // Calculate execution time in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Output execution time to console
    std::cout << "OpenCV Convolution operation (with SIMD optimization) took " << duration << " milliseconds." << std::endl;

    // Save output image
    cv::imwrite(outputPath, outputMat);
}

void ConvolutionTester::runTests3(const std::vector<std::string>& inputPaths,
    const std::vector<std::string>& outputPaths,
    const std::vector<float>& kernel) {

    for (size_t i = 0; i < inputPaths.size(); ++i) {
        runTest3(inputPaths[i], outputPaths[i], kernel);
    }
}
