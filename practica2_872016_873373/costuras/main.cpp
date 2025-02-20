#include <opencv2/opencv.hpp>
#include <iostream>
#include "auxOpenCV.hpp"
#include "costuras.hpp"

int main() {
    cv::Mat mat = cv::imread("profile.jpg");

    if (mat.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return -1;
    }

    // Convertir Mat a Image
    Image img = matToImage(mat);

    // Algoritmo
    algoritmo(img, 10);

    // Convertir Image a Mat
    cv::Mat convertedMat = imageToMat(img);

    // Mostrar Mat convertida
    cv::imshow("Converted Image", convertedMat);
    cv::waitKey(0);

    return 0;
}
