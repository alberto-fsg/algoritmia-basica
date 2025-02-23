#ifndef GESTOR_IMG_
#define GESTOR_IMG_

#define cimg_use_jpeg
#define cimg_use_png
#define cimg_display 0

#include "CImg.h"
using namespace cimg_library;

#include <vector>

/**
 * Estructura que representa un píxel y sus
 * valores RGB
 */
struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

/**
 * Estructura que representa imagen como array
 * bidimensional de píxeles
 */
struct Image {
    int width;
    int height;
    std::vector<std::vector<Pixel>> pixels;
};

/**
 * Convierte un objeto CImg a la estructura Image
 */
Image cImgToImage(const CImg<unsigned char>& cimg);

/**
 * Convierte estructura Image a un objeto CImg
 */
CImg<unsigned char> imageToCImg(const Image& img);

#endif
