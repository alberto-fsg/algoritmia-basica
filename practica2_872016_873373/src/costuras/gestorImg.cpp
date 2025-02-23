#include "gestorImg.hpp"

using namespace std;

/**
 * Convierte un objeto CImg a la estructura Image
 */
Image cImgToImage(const CImg<unsigned char>& cimg) {
    Image img;
    img.width = cimg.width();
    img.height = cimg.height();
    img.pixels.resize(img.height, vector<Pixel>(img.width));
    for(int y = 0; y < img.height; ++y) {
        for(int x = 0; x < img.width; ++x) {
            img.pixels[y][x].red = cimg(x, y, 0, 0);
            img.pixels[y][x].green = cimg(x, y, 0, 1);
            img.pixels[y][x].blue = cimg(x, y, 0, 2);
        }
    }
    return img;
}

/**
 * Convierte estructura Image a un objeto CImg
 */
CImg<unsigned char> imageToCImg(const Image& img) {
    CImg<unsigned char> cimg(img.width, img.height, 1, 3);
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            cimg(x, y, 0, 0) = img.pixels[y][x].red;
            cimg(x, y, 0, 1) = img.pixels[y][x].green;
            cimg(x, y, 0, 2) = img.pixels[y][x].blue;
        }
    }
    return cimg;
}