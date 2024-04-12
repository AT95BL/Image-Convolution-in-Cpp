#ifndef KERNEL_H
#define KERNEL_H

#include <vector>

#pragma warning(disable : 4996)

namespace Kernel {
    extern std::vector<float> kernelIdentity;
    extern std::vector<float> kernelGaussianBlur;
    extern std::vector<float> kernelEdgeDetection;
    extern std::vector<float> kernelBoxBlur;
    extern std::vector<float> kernelSharpen;

    std::vector<float> parseKernelValues(const char*);
}

#endif // KERNEL_H