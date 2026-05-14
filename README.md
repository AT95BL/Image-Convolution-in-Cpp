##  Optimization of Multimedia Content Processing Algorithm

Within this project task, the aim is to implement an optimized algorithm for processing multimedia content, focusing on either sound or image using the convolution operation. The implementation should adhere to the principles of object-oriented programming (OOP), SOLID principles, as well as principles of writing readable code and conventions of the used programming languages.

### Program Features:

- **Parallelizability**: The algorithm should be parallelizable to leverage the capabilities of multi-core processors for faster processing.
- **Configurability**: Users should have the ability to manually specify the convolutional kernel when running the algorithm.
- **Command Line Interface**: The program should accept paths to input and output files, as well as algorithm parameter values via the command-line argument.
- **Default Values**: Provide meaningful default values for all command-line arguments for user convenience.
- **Performance Optimization**: Implement algorithm optimization to achieve high performance, with a focus on efficient cache memory usage and the use of SIMD instructions for acceleration.

### Documentation and Performance Analysis:

- **Testing**: Validate the correctness of the algorithm through unit tests to ensure its functionality.
- **Performance Measurement**: Conduct runtime measurements of the algorithm for different input sizes and various input data scenarios.
- **Optimization**: Graphically represent measurement results before and after applying optimizations and parallelization.
- **Report**: Prepare a report containing a problem description, description of the basic algorithm, description of optimized algorithm variants, details of performance measurement, hardware used for measurements, graphical analysis of results, and conclusion.
- **Automation**: Include a script that automatically runs all measurements mentioned in the report and saves the results to a file for easier reproduction.

### Github Project Description:

This repository contains an implementation of an optimized algorithm for processing multimedia content, along with its accompanying report documenting the optimization process and performance analysis. The implementation is done following OOP principles and SOLID principles, using language-specific programming conventions. Additionally, a script for automated performance measurement of the algorithm and result storage is provided. Unit tests are included with the implementation to ensure algorithm correctness.

## Screenshots

> Convolution Example : BoxBlur-Kernel vs EdgeDetection-Kernel

![Example](screenshots/convolutionExample.jpeg)


---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
## 👤 Author

**Andrej Trožić** *Software Developer specializing in Backend Systems & Infrastructure*

[![LinkedIn](https://img.shields.io/badge/LinkedIn-Andrej_Trožić-blue?logo=linkedin)](https://www.linkedin.com/in/andrej-tro%C5%BEi%C4%87-57957122b/)  
[![GitHub](https://img.shields.io/badge/GitHub-AT95BL-black?logo=github)](https://github.com/AT95BL)  
[![Portfolio](https://img.shields.io/badge/Portfolio-andrejtrozic.com-green)](https://andrejtrozic.com)

---

## 📄 License

MIT License

Copyright (c) 2026 Andrej Trožić

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
