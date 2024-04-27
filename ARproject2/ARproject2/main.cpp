#include "image.h"
#include "convolution.h"
#include "kernel.h"
#include "convolution_tester.h"
#include "imageFolder.h"

#include <fstream>

using namespace Kernel;

int main(int argc, char* argv[]) {

    bool loop = true;
    bool testing;

    if (argc == 3) {
        
        // Učitavanje putanja iz argumenata komandne linije
        std::string ulaznaPutanja = argv[1];
        std::string izlaznaPutanja = argv[2];

        int n_for_command_line_arguments;

        std::cout << "Zelite li da izvrsite testiranje rada kernela nad ulaznim argumentima: " << std::endl
            << "1 za Da" << std::endl
            << "0 za Ne" << std::endl;
        std::cin >> testing;

        if (testing) {

            // Učitavanje slike iz BMP fajla (pretpostavljamo 24-bitni nekompresovani BMP format)
            int width = 0, height = 0;
            std::vector<Color> pixels = loadBMP2(ulaznaPutanja, width, height);

            Image inputImage(width, height);
            Image outputImage(width, height);

            inputImage.pixels = pixels;

            loop = true;

            while (loop)
            {
                std::cout << "-Odaberite Sebi Odgovarajuci Kernel-" << std::endl
                    << "1 za Identity Kernel " << std::endl
                    << "2 za Gaussian Blur Kernel" << std::endl
                    << "3 za Edge Detection Kernel" << std::endl
                    << "4 za Box Blur Kernel" << std::endl
                    << "5 za Sharpen Kernel " << std::endl
                    << "0 za Izlaz " << std::endl;
                do {
                    std::cin >> n_for_command_line_arguments;
                } while (n_for_command_line_arguments < 0 || n_for_command_line_arguments > 5);

                switch (n_for_command_line_arguments) {

                case 1: {
                    convolution(inputImage, Kernel::kernelIdentity, outputImage);

                    // Konvolucija koristeći OpenCV kernel
                    cv::Mat inputMat1(height, width, CV_8UC3, inputImage.pixels.data());
                    cv::Mat outputMat1;
                    cv::Mat kernelMat1 = cv::Mat(Kernel::kernelIdentity).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelIdentity.size())));
                    cv::filter2D(inputMat1, outputMat1, -1, kernelMat1);
                    // Čuvanje rezultata slike koristeći OpenCV kernel
                    cv::imwrite("izlaznaSlika_Identity_Kernel_opencv.bmp", outputMat1);

                    // Konvolucija koristeći optimizovanu funkciju sa SIMD instrukcijama
                    cv::Mat inputMatSimd(height, width, CV_8UC3, inputImage.pixels.data());
                    cv::Mat outputMatSimd;
                    cv::Mat kernelMatSimd = cv::Mat(Kernel::kernelIdentity).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelIdentity.size())));
                    cv::filter2D(inputMatSimd, outputMatSimd, -1, kernelMatSimd, cv::Point(-1, -1), 0, cv::BORDER_CONSTANT);
                    // Čuvanje rezultata slike koristeći optimizovanu funkciju sa SIMD instrukcijama
                    cv::imwrite("izlaznaSlika_Identity_Kernel_simd.bmp", outputMatSimd);

                    // Čuvanje rezultata slike u BMP fajl
                    saveBMP(izlaznaPutanja.c_str(), outputImage);

                    break;
                }

                case 2: {
                    convolution(inputImage, Kernel::kernelGaussianBlur, outputImage);

                    // Konvolucija koristeći OpenCV kernel
                    cv::Mat inputMat1(height, width, CV_8UC3, inputImage.pixels.data());
                    cv::Mat outputMat1;
                    cv::Mat kernelMat1 = cv::Mat(Kernel::kernelGaussianBlur).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelGaussianBlur.size())));
                    cv::filter2D(inputMat1, outputMat1, -1, kernelMat1);
                    // Čuvanje rezultata slike koristeći OpenCV kernel
                    cv::imwrite("izlaznaSlika_Gaussian_Blur_Kernel_opencv.bmp", outputMat1);

                    // Konvolucija koristeći optimizovanu funkciju sa SIMD instrukcijama
                    cv::Mat inputMatSimd(height, width, CV_8UC3, inputImage.pixels.data());
                    cv::Mat outputMatSimd;
                    cv::Mat kernelMatSimd = cv::Mat(Kernel::kernelGaussianBlur).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelGaussianBlur.size())));
                    cv::filter2D(inputMatSimd, outputMatSimd, -1, kernelMatSimd, cv::Point(-1, -1), 0, cv::BORDER_CONSTANT);
                    // Čuvanje rezultata slike koristeći optimizovanu funkciju sa SIMD instrukcijama
                    cv::imwrite("izlaznaSlika_Sharpen_Kernel_simd.bmp", outputMatSimd);

                    // Čuvanje rezultata slike u BMP fajl
                    saveBMP(izlaznaPutanja.c_str(), outputImage);

                    break;
                }

                case 3: {
                    convolution(inputImage, Kernel::kernelEdgeDetection, outputImage);

                    // Konvolucija koristeći OpenCV kernel
                    cv::Mat inputMat1(height, width, CV_8UC3, inputImage.pixels.data());
                    cv::Mat outputMat1;
                    cv::Mat kernelMat1 = cv::Mat(Kernel::kernelEdgeDetection).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelEdgeDetection.size())));
                    cv::filter2D(inputMat1, outputMat1, -1, kernelMat1);
                    // Čuvanje rezultata slike koristeći OpenCV kernel
                    cv::imwrite("izlaznaSlika_Edge_Detection_Kernel_opencv.bmp", outputMat1);

                    // Konvolucija koristeći optimizovanu funkciju sa SIMD instrukcijama
                    cv::Mat inputMatSimd(height, width, CV_8UC3, inputImage.pixels.data());
                    cv::Mat outputMatSimd;
                    cv::Mat kernelMatSimd = cv::Mat(Kernel::kernelEdgeDetection).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelEdgeDetection.size())));
                    cv::filter2D(inputMatSimd, outputMatSimd, -1, kernelMatSimd, cv::Point(-1, -1), 0, cv::BORDER_CONSTANT);
                    // Čuvanje rezultata slike koristeći optimizovanu funkciju sa SIMD instrukcijama
                    cv::imwrite("izlaznaSlika_Edge_Detection_Kernel_simd.bmp", outputMatSimd);

                    // Čuvanje rezultata slike u BMP fajl
                    saveBMP(izlaznaPutanja.c_str(), outputImage);

                    break;
                }

                case 4: {
                    convolution(inputImage, Kernel::kernelBoxBlur, outputImage);

                    // Konvolucija koristeći OpenCV kernel
                    cv::Mat inputMat1(height, width, CV_8UC3, inputImage.pixels.data());
                    cv::Mat outputMat1;
                    cv::Mat kernelMat1 = cv::Mat(Kernel::kernelBoxBlur).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelBoxBlur.size())));
                    cv::filter2D(inputMat1, outputMat1, -1, kernelMat1);
                    // Čuvanje rezultata slike koristeći OpenCV kernel
                    cv::imwrite("izlaznaSlika_Box_Blur_Kernel_opencv.bmp", outputMat1);

                    // Konvolucija koristeći optimizovanu funkciju sa SIMD instrukcijama
                    cv::Mat inputMatSimd(height, width, CV_8UC3, inputImage.pixels.data());
                    cv::Mat outputMatSimd;
                    cv::Mat kernelMatSimd = cv::Mat(Kernel::kernelBoxBlur).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelBoxBlur.size())));
                    cv::filter2D(inputMatSimd, outputMatSimd, -1, kernelMatSimd, cv::Point(-1, -1), 0, cv::BORDER_CONSTANT);
                    // Čuvanje rezultata slike koristeći optimizovanu funkciju sa SIMD instrukcijama
                    cv::imwrite("izlaznaSlika_Box_Blur_Kernel_simd.bmp", outputMatSimd);

                    // Čuvanje rezultata slike u BMP fajl
                    saveBMP(izlaznaPutanja.c_str(), outputImage);

                    break;
                }

                case 5: {
                    convolution(inputImage, Kernel::kernelSharpen, outputImage);

                    // Konvolucija koristeći OpenCV kernel
                    cv::Mat inputMat1(height, width, CV_8UC3, inputImage.pixels.data());
                    cv::Mat outputMat1;
                    cv::Mat kernelMat1 = cv::Mat(Kernel::kernelSharpen).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelSharpen.size())));
                    cv::filter2D(inputMat1, outputMat1, -1, kernelMat1);
                    // Čuvanje rezultata slike koristeći OpenCV kernel
                    cv::imwrite("izlaznaSlika_Sharpen_Kernel_opencv.bmp", outputMat1);

                    // Konvolucija koristeći optimizovanu funkciju sa SIMD instrukcijama
                    cv::Mat inputMatSimd(height, width, CV_8UC3, inputImage.pixels.data());
                    cv::Mat outputMatSimd;
                    cv::Mat kernelMatSimd = cv::Mat(Kernel::kernelSharpen).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelSharpen.size())));
                    cv::filter2D(inputMatSimd, outputMatSimd, -1, kernelMatSimd, cv::Point(-1, -1), 0, cv::BORDER_CONSTANT);
                    // Čuvanje rezultata slike koristeći optimizovanu funkciju sa SIMD instrukcijama
                    cv::imwrite("izlaznaSlika_Sharpen_Kernel_simd.bmp", outputMatSimd);

                    // Čuvanje rezultata slike u BMP fajl
                    saveBMP(izlaznaPutanja.c_str(), outputImage);

                    break;
                }
                case 0: {
                    loop = false;
                    break;
                }

                default:
                    break;

                }
            }
        }
    }

    loop = true;    

    std::cout << "Zelite li da izvrsite testiranje performansi: " << std::endl
        << "1 za Da" << std::endl
        << "0 za Ne" << std::endl;
    std::cin >> testing;

    
    if (testing) {

        int result = system("python imageGeneratorScript.py");

        // Proverava da li je sistemski poziv uspešno izvršen
        if (result == 0) {
            std::cout << "Skripta je uspešno izvršena." << std::endl;
        }
        else {
            std::cout << "Greška prilikom izvršavanja skripte." << std::endl;
        }

        // Čitanje broja test slika iz datoteke
        std::ifstream file("num_images.txt");
        int num_images;
        file >> num_images;
        file.close();

        std::vector<std::string> inputPaths;
        std::vector<std::string> outputPaths;

        for (int i = 1; i <= num_images; i++) {
            inputPaths.push_back("input" + std::to_string(i) + ".bmp");
            outputPaths.push_back("output" + std::to_string(i) + ".bmp");
        }

        int n_for_kernel_choice;
        ConvolutionTester tester;

        while (loop) {

            std::cout << "\n\n-Odaberite Sebi Odgovarajuci Kernel-" << std::endl
                << "1 za Identity Kernel " << std::endl
                << "2 za Gaussian Blur Kernel" << std::endl
                << "3 za Edge Detection Kernel" << std::endl
                << "4 za Box Blur Kernel" << std::endl
                << "5 za Sharpen Kernel " << std::endl
                << "0.za izlaz" << std::endl;
            do {
                std::cin >> n_for_kernel_choice;
            } while (n_for_kernel_choice < 0 || n_for_kernel_choice > 5);

            switch (n_for_kernel_choice) {

            case 1:
                std::cout << "Konvolucija slike koristenjem korisnicki definisane funkcije: " << std::endl;
                tester.runTests1(inputPaths, outputPaths, kernelIdentity);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv biblioteke: " << std::endl;
                tester.runTests2(inputPaths, outputPaths, kernelIdentity);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv(SIMD optimized) biblioteke: " << std::endl;
                tester.runTests3(inputPaths, outputPaths, kernelIdentity);
                break;

            case 2:
                std::cout << "Konvolucija slike koristenjem korisnicki definisane funkcije: " << std::endl;
                tester.runTests1(inputPaths, outputPaths, kernelGaussianBlur);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv biblioteke: " << std::endl;
                tester.runTests2(inputPaths, outputPaths, kernelGaussianBlur);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv(SIMD optimized) biblioteke: " << std::endl;
                tester.runTests3(inputPaths, outputPaths, kernelGaussianBlur);
                break;

            case 3:
                std::cout << "Konvolucija slike koristenjem korisnicki definisane funkcije: " << std::endl;
                tester.runTests1(inputPaths, outputPaths, kernelEdgeDetection);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv biblioteke: " << std::endl;
                tester.runTests2(inputPaths, outputPaths, kernelEdgeDetection);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv(SIMD optimized) biblioteke: " << std::endl;
                tester.runTests3(inputPaths, outputPaths, kernelEdgeDetection);
                break;

            case 4:
                std::cout << "Konvolucija slike koristenjem korisnicki definisane funkcije: " << std::endl;
                tester.runTests1(inputPaths, outputPaths, kernelBoxBlur);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv biblioteke: " << std::endl;
                tester.runTests2(inputPaths, outputPaths, kernelBoxBlur);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv(SIMD optimized) biblioteke: " << std::endl;
                tester.runTests3(inputPaths, outputPaths, kernelBoxBlur);
                break;

            case 5:
                std::cout << "Konvolucija slike koristenjem korisnicki definisane funkcije: " << std::endl;
                tester.runTests1(inputPaths, outputPaths, kernelSharpen);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv biblioteke: " << std::endl;
                tester.runTests2(inputPaths, outputPaths, kernelSharpen);
                std::cout << "Konvolucija slike koristenjem funkcije iz opecv(SIMD optimized) biblioteke: " << std::endl;
                tester.runTests3(inputPaths, outputPaths, kernelSharpen);
                break;

            case 0:
                loop = false;
                break;
            }
        }
    }

    int n_for_kernel_testing;
    
    std::string folder1 = "my_identity_kernel";
    std::string folder2 = "opencv_identity_kernel";
    std::string folder3 = "simd_opencv_identity_kernel";

    std::string folder4 = "my_gaussian_blur_kernel";
    std::string folder5 = "opencv_gaussian_blur_kernel";
    std::string folder6 = "simd_opencv_gaussian_blur_kernel";

    std::string folder7 = "my_edge_detection_kernel";
    std::string folder8 = "opencv_edge_detection_kernel";
    std::string folder9 = "simd_opencv_edge_detection_kernel";

    std::string folder10 = "my_box_blur_kernel";
    std::string folder11 = "opencv_box_blur_kernel";
    std::string folder12 = "simd_opencv_box_blur_kernel";

    std::string folder13 = "my_sharpen_kernel";
    std::string folder14 = "opencv_sharpen_kernel";
    std::string folder15 = "simd_opencv_sharpen_kernel";

    std::cout << "Zelite li da izvrsite testiranje rada kernela: " << std::endl
        << "1 za Da" << std::endl
        << "0 za Ne" << std::endl;
    std::cin >> testing;

    if (testing) {

        // Učitavanje slike iz BMP fajla (pretpostavljamo 24-bitni nekompresovani BMP format)
        int width = 0, height = 0;
        std::vector<Color> pixels = loadBMP2("ulaznaSlika.bmp", width, height);

        Image inputImage(width, height);
        Image outputImage(width, height);

        inputImage.pixels = pixels;

        loop = true;
        
        while (loop)
        {
            std::cout << "-Odaberite Sebi Odgovarajuci Kernel-" << std::endl
                << "1 za Identity Kernel " << std::endl
                << "2 za Gaussian Blur Kernel" << std::endl
                << "3 za Edge Detection Kernel" << std::endl
                << "4 za Box Blur Kernel" << std::endl
                << "5 za Sharpen Kernel " << std::endl
                << "0 za Izlaz " << std::endl;
            do {
                std::cin >> n_for_kernel_testing;
            } while (n_for_kernel_testing < 0 || n_for_kernel_testing > 5);

            switch (n_for_kernel_testing){

            case 1: {
                convolution(inputImage, Kernel::kernelIdentity, outputImage);
                // Čuvanje rezultata slike u BMP fajl
                saveBMP("izlaznaSlika_Identity_Kernel_my.bmp", outputImage);
                saveImageToFolder(outputImage, folder1, "output_image_my.bmp");

                // Konvolucija koristeći OpenCV kernel
                cv::Mat inputMat1(height, width, CV_8UC3, inputImage.pixels.data());
                cv::Mat outputMat1;
                cv::Mat kernelMat1 = cv::Mat(Kernel::kernelIdentity).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelIdentity.size())));
                cv::filter2D(inputMat1, outputMat1, -1, kernelMat1);
                // Čuvanje rezultata slike koristeći OpenCV kernel
                cv::imwrite("izlaznaSlika_Identity_Kernel_opencv.bmp", outputMat1);
                saveImageToFolder(outputImage, folder2, "output_image_opencv.bmp");

                // Konvolucija koristeći optimizovanu funkciju sa SIMD instrukcijama
                cv::Mat inputMatSimd(height, width, CV_8UC3, inputImage.pixels.data());
                cv::Mat outputMatSimd;
                cv::Mat kernelMatSimd = cv::Mat(Kernel::kernelIdentity).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelIdentity.size())));
                cv::filter2D(inputMatSimd, outputMatSimd, -1, kernelMatSimd, cv::Point(-1, -1), 0, cv::BORDER_CONSTANT);
                // Čuvanje rezultata slike koristeći optimizovanu funkciju sa SIMD instrukcijama
                cv::imwrite("izlaznaSlika_Identity_Kernel_simd.bmp", outputMatSimd);
                saveImageToFolder(outputImage, folder3, "output_image_opencv_simd.bmp");

                break;
            }

            case 2: {
                convolution(inputImage, Kernel::kernelGaussianBlur, outputImage);
                // Čuvanje rezultata slike u BMP fajl
                saveBMP("izlaznaSlika_Gaussian_Blur_Kernel_my.bmp", outputImage);
                saveImageToFolder(outputImage, folder4, "output_image_my.bmp");

                // Konvolucija koristeći OpenCV kernel
                cv::Mat inputMat1(height, width, CV_8UC3, inputImage.pixels.data());
                cv::Mat outputMat1;
                cv::Mat kernelMat1 = cv::Mat(Kernel::kernelGaussianBlur).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelGaussianBlur.size())));
                cv::filter2D(inputMat1, outputMat1, -1, kernelMat1);
                // Čuvanje rezultata slike koristeći OpenCV kernel
                cv::imwrite("izlaznaSlika_Gaussian_Blur_Kernel_opencv.bmp", outputMat1);
                saveImageToFolder(outputImage, folder5, "output_image_opencv.bmp");

                // Konvolucija koristeći optimizovanu funkciju sa SIMD instrukcijama
                cv::Mat inputMatSimd(height, width, CV_8UC3, inputImage.pixels.data());
                cv::Mat outputMatSimd;
                cv::Mat kernelMatSimd = cv::Mat(Kernel::kernelGaussianBlur).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelGaussianBlur.size())));
                cv::filter2D(inputMatSimd, outputMatSimd, -1, kernelMatSimd, cv::Point(-1, -1), 0, cv::BORDER_CONSTANT);
                // Čuvanje rezultata slike koristeći optimizovanu funkciju sa SIMD instrukcijama
                cv::imwrite("izlaznaSlika_Sharpen_Kernel_simd.bmp", outputMatSimd);
                saveImageToFolder(outputImage, folder6, "output_image_opencv_simd.bmp");

                break;
            }
            
            case 3: {
                convolution(inputImage, Kernel::kernelEdgeDetection, outputImage);
                // Čuvanje rezultata slike u BMP fajl
                saveBMP("izlaznaSlika_Edge_Detection_Kernel_my.bmp", outputImage);
                saveImageToFolder(outputImage, folder7, "output_image_my.bmp");

                // Konvolucija koristeći OpenCV kernel
                cv::Mat inputMat1(height, width, CV_8UC3, inputImage.pixels.data());
                cv::Mat outputMat1;
                cv::Mat kernelMat1 = cv::Mat(Kernel::kernelEdgeDetection).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelEdgeDetection.size())));
                cv::filter2D(inputMat1, outputMat1, -1, kernelMat1);
                // Čuvanje rezultata slike koristeći OpenCV kernel
                cv::imwrite("izlaznaSlika_Edge_Detection_Kernel_opencv.bmp", outputMat1);
                saveImageToFolder(outputImage, folder8, "output_image_opencv.bmp");

                // Konvolucija koristeći optimizovanu funkciju sa SIMD instrukcijama
                cv::Mat inputMatSimd(height, width, CV_8UC3, inputImage.pixels.data());
                cv::Mat outputMatSimd;
                cv::Mat kernelMatSimd = cv::Mat(Kernel::kernelEdgeDetection).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelEdgeDetection.size())));
                cv::filter2D(inputMatSimd, outputMatSimd, -1, kernelMatSimd, cv::Point(-1, -1), 0, cv::BORDER_CONSTANT);
                // Čuvanje rezultata slike koristeći optimizovanu funkciju sa SIMD instrukcijama
                cv::imwrite("izlaznaSlika_Edge_Detection_Kernel_simd.bmp", outputMatSimd);
                saveImageToFolder(outputImage, folder9, "output_image_opencv_simd.bmp");

                break;
            }

            case 4: {
                convolution(inputImage, Kernel::kernelBoxBlur, outputImage);
                // Čuvanje rezultata slike u BMP fajl
                saveBMP("izlaznaSlika_Box_Blur_kernel_my.bmp", outputImage);
                saveImageToFolder(outputImage, folder10, "output_image_my.bmp");

                // Konvolucija koristeći OpenCV kernel
                cv::Mat inputMat1(height, width, CV_8UC3, inputImage.pixels.data());
                cv::Mat outputMat1;
                cv::Mat kernelMat1 = cv::Mat(Kernel::kernelBoxBlur).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelBoxBlur.size())));
                cv::filter2D(inputMat1, outputMat1, -1, kernelMat1);
                // Čuvanje rezultata slike koristeći OpenCV kernel
                cv::imwrite("izlaznaSlika_Box_Blur_Kernel_opencv.bmp", outputMat1);
                saveImageToFolder(outputImage, folder11, "output_image_opencv.bmp");

                // Konvolucija koristeći optimizovanu funkciju sa SIMD instrukcijama
                cv::Mat inputMatSimd(height, width, CV_8UC3, inputImage.pixels.data());
                cv::Mat outputMatSimd;
                cv::Mat kernelMatSimd = cv::Mat(Kernel::kernelBoxBlur).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelBoxBlur.size())));
                cv::filter2D(inputMatSimd, outputMatSimd, -1, kernelMatSimd, cv::Point(-1, -1), 0, cv::BORDER_CONSTANT);
                // Čuvanje rezultata slike koristeći optimizovanu funkciju sa SIMD instrukcijama
                cv::imwrite("izlaznaSlika_Box_Blur_Kernel_simd.bmp", outputMatSimd);
                saveImageToFolder(outputImage, folder12, "output_image_opencv_simd.bmp");

                break;
            }

            case 5: {
                convolution(inputImage, Kernel::kernelSharpen, outputImage);
                // Čuvanje rezultata slike u BMP fajl
                saveBMP("izlaznaSlika_Sharpen_Kernel_my.bmp", outputImage);
                saveImageToFolder(outputImage, folder13, "output_image_my.bmp");

                // Konvolucija koristeći OpenCV kernel
                cv::Mat inputMat1(height, width, CV_8UC3, inputImage.pixels.data());
                cv::Mat outputMat1;
                cv::Mat kernelMat1 = cv::Mat(Kernel::kernelSharpen).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelSharpen.size())));
                cv::filter2D(inputMat1, outputMat1, -1, kernelMat1);
                // Čuvanje rezultata slike koristeći OpenCV kernel
                cv::imwrite("izlaznaSlika_Sharpen_Kernel_opencv.bmp", outputMat1);
                saveImageToFolder(outputImage, folder14, "output_image_opencv.bmp");

                // Konvolucija koristeći optimizovanu funkciju sa SIMD instrukcijama
                cv::Mat inputMatSimd(height, width, CV_8UC3, inputImage.pixels.data());
                cv::Mat outputMatSimd;
                cv::Mat kernelMatSimd = cv::Mat(Kernel::kernelSharpen).reshape(1, static_cast<int>(std::sqrt(Kernel::kernelSharpen.size())));
                cv::filter2D(inputMatSimd, outputMatSimd, -1, kernelMatSimd, cv::Point(-1, -1), 0, cv::BORDER_CONSTANT);
                // Čuvanje rezultata slike koristeći optimizovanu funkciju sa SIMD instrukcijama
                cv::imwrite("izlaznaSlika_Sharpen_Kernel_simd.bmp", outputMatSimd);
                saveImageToFolder(outputImage, folder15, "output_image_opencv_simd.bmp");

                break;
            }
            case 0: {
                loop = false;
                break;
            }
              
            default:
               break;
            
            }

        }
    }

    return 0;
}