#include "kernel.h"

namespace Kernel {

    std::vector<float> kernelIdentity = { 0, -1, 0, -1, 5, -1, 0, -1, 0 };

    std::vector<float> kernelGaussianBlur = {
        0.0625, 0.125, 0.0625,
        0.125, 0.25, 0.125,
        0.0625, 0.125, 0.0625 };

    std::vector<float> kernelEdgeDetection = {
        -1, -1, -1,
        -1, 8, -1,
        -1, -1, -1 };

    std::vector<float> kernelBoxBlur = {
        0.1111, 0.1111, 0.1111,
        0.1111, 0.1111, 0.1111,
        0.1111, 0.1111, 0.1111 };

    std::vector<float> kernelSharpen = {
        0, -1, 0,
        -1, 5, -1,
        0, -1, 0
    };

    std::vector<float> parseKernelValues(const char* kernelArg) {
        std::vector<float> kernelValues;

        const char delimiter = ',';
        char* token = strtok(const_cast<char*>(kernelArg), &delimiter);

        while (token != nullptr) {
            double value = atof(token);
            kernelValues.push_back(value);
            token = strtok(nullptr, &delimiter);
        }

        return kernelValues;
    }
}
