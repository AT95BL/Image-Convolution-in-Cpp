#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "image.h"
#include "convolution.h"
#include "kernel.h"

#include <opencv2/opencv.hpp>

class ConvolutionTester {
public:
    ConvolutionTester() {}

    void runTest1(const std::string&, const std::string&, const std::vector<float>&);

    void runTests1(const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<float>&);

    void runTest2(const std::string&, const std::string&, const std::vector<float>&);

    void runTests2(const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<float>&);

    void runTest3(const std::string&, const std::string&, const std::vector<float>&);

    void runTests3(const std::vector<std::string>&, const std::vector<std::string>&, const std::vector<float>&);

};

