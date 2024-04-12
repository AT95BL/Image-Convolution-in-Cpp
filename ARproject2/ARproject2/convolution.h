#pragma once

#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include <cmath>

#include "image.h"

void convolution(const Image& , const std::vector<float>& , Image& );

#endif // !CONVOLUTION_H
