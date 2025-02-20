#include <utility>
#include <cmath>
#include <list>
#include "costuras.hpp"
#include "auxOpenCV.hpp"

using namespace std;

int brillo(int i, int j, const image& img) {
    if (i < 0 || j < 0 || img.width <= i || img.height <= j)
        return 0;
    return img.pixels[j][i].red + img.pixels[j][i].blue + img.pixels[j][i].green;
}

int obtenerEnergia(int i, int j, const image& img) {
    int energiax = 0, energiay = 0;

    // Cálculo en la dirección horizontal
    energiax = brillo(i - 1, j - 1, img) + 2 * brillo(i - 1, j, img) + brillo(i - 1, j + 1, img)
             - brillo(i + 1, j - 1, img) - 2 * brillo(i + 1, j, img) - brillo(i + 1, j + 1, img);

    // Cálculo en la dirección vertical
    energiay = brillo(i - 1, j - 1, img) + 2 * brillo(i, j - 1, img) + brillo(i + 1, j - 1, img)
             - brillo(i - 1, j + 1, img) - 2 * brillo(i, j + 1, img) - brillo(i + 1, j + 1, img);

    return static_cast<int>(sqrt(energiax * energiax + energiay * energiay));
}

int obtenerCosturaRecursiva(int i, int j, const image& img, vector<vector<int>>& tablaCostes, vector<vector<bool>>& costesCalculados) {
    if(costesCalculados[j][i])
        return tablaCostes[j][i];
    
    int coste = obtenerEnergia(i, j, img);
    if(j < img.height - 1) {
        if(i == 0)
            coste += min(obtenerCosturaRecursiva(i, j + 1, img, tablaCostes, costesCalculados),
                         obtenerCosturaRecursiva(i + 1, j + 1, img, tablaCostes, costesCalculados));
        else if(i == img.width - 1)
            coste += min(obtenerCosturaRecursiva(i, j + 1, img, tablaCostes, costesCalculados),
                         obtenerCosturaRecursiva(i - 1, j + 1, img, tablaCostes, costesCalculados));
        else
            coste += min(obtenerCosturaRecursiva(i - 1, j + 1, img, tablaCostes, costesCalculados),
                     min(obtenerCosturaRecursiva(i, j + 1, img, tablaCostes, costesCalculados),
                         obtenerCosturaRecursiva(i + 1, j + 1, img, tablaCostes, costesCalculados)));
    }
    tablaCostes[j][i] = coste;
    costesCalculados[j][i] = true;
    return coste;
}

pair<int, int> obtenerSiguientePixel(const image& img, int fila, int col) {
    if (fila >= img.height - 1)
        return {-1, -1};

    int nuevaCol = col;
    int minCoste = brillo(col, fila + 1, img);

    if (col > 0) {
        int costeIzq = brillo(col - 1, fila + 1, img);
        if (costeIzq < minCoste) {
            minCoste = costeIzq;
            nuevaCol = col - 1;
        }
    }

    if (col < img.width - 1) {
        int costeDer = brillo(col + 1, fila + 1, img);
        if (costeDer < minCoste) {
            minCoste = costeDer;
            nuevaCol = col + 1;
        }
    }

    return {fila + 1, nuevaCol};
}

vector<int> obtenerCostura(image& img) {
    vector<vector<int>> tablaCostes(img.height, vector<int>(img.width, 0));
    vector<vector<bool>> costesCalculados(img.height, vector<bool>(img.width, false));

    int minCoste = obtenerCosturaRecursiva(0, 0, img, tablaCostes, costesCalculados);
    int minCol = 0;

    for (int i = 1; i < img.width; ++i) {
        int coste = obtenerCosturaRecursiva(i, 0, img, tablaCostes, costesCalculados);
        if (coste < minCoste) {
            minCoste = coste;
            minCol = i;
        }
    }

    vector<int> costura(img.height);
    pair<int, int> posicionActual = {0, minCol};
    for (int fila = 0; fila < img.height; ++fila) {
        costura[fila] = posicionActual.second;
        posicionActual = obtenerSiguientePixel(img, posicionActual.first, posicionActual.second);
        if (posicionActual.first == -1) break;
    }
    return costura;
}

void eliminarCostura(Image& img, const vector<int>& costura) {
    for (int j = 0; j < img.height; ++j) {
        int col = costura[j];
        for (int i = col; i < img.width - 1; ++i) {
            img.pixels[j][i] = img.pixels[j][i + 1];
        }
    }
    img.width--;
}

void algoritmo(Image& img, int n_columnas) {
    while (n_columnas != 0) {
        vector<int> costura = obtenerCostura(img);
        eliminarCostura(img, costura);
        n_columnas--;
    }
}
