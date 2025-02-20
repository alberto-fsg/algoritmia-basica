struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

struct image {
    int width;
    int height;
    std::vector<std::vector<Pixel>> pixels;
};

image matToImage(const cv::Mat& mat) {
    image img;
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

cv::Mat imageToMat(const image& img) {
    cv::Mat mat(img.height, img.width, CV_8UC3);
    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            const Pixel &p = img.pixels[i][j];
            // OpenCV uses BGR order.
            mat.at<cv::Vec3b>(i, j) = cv::Vec3b(p.blue, p.green, p.red);
        }
    }
    return mat;
}
