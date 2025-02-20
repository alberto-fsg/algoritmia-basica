#include "auxOpenCV.hpp"

Image matToImage(const cv::Mat& mat) {
    Image img;
    img.width = mat.cols;
    img.height = mat.rows;
    img.pixels.resize(img.height, std::vector<Pixel>(img.width));

    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            cv::Vec3b intensity = mat.at<cv::Vec3b>(i, j);
            img.pixels[i][j].blue  = intensity[0];
            img.pixels[i][j].green = intensity[1];
            img.pixels[i][j].red   = intensity[2];
        }
    }
    return img;
}

cv::Mat imageToMat(const Image& img) {
    cv::Mat mat(img.height, img.width, CV_8UC3);
    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            const Pixel &p = img.pixels[i][j];
            mat.at<cv::Vec3b>(i, j) = cv::Vec3b(p.blue, p.green, p.red);
        }
    }
    return mat;
}
