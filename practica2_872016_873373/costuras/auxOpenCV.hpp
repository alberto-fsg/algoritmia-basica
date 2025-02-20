#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

// Struct representing a single pixel in RGB format
struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

// Struct representing an image as a 2D vector of Pixels
struct Image {
    int width;
    int height;
    std::vector<std::vector<Pixel>> pixels;
};

// Function to convert an OpenCV Mat to an Image struct
Image matToImage(const cv::Mat& mat);

// Function to convert an Image struct to an OpenCV Mat
cv::Mat imageToMat(const Image& img);
