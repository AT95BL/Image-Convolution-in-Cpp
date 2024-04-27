#pragma once

#include <filesystem>

#include "image.h"

namespace fs = std::filesystem;

void saveImageToFolder(const Image&, const std::string&, const std::string&);