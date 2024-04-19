#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "image.h"
#include "convolution.h"
#include "kernel.h"

class ConvolutionTester {
public:
    ConvolutionTester() {}

    void runTest(const std::string&, const std::string&, const std::vector<float>&);

    void runTests(const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<float>&);
};