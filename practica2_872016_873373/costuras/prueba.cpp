
#include <utilty>
#include <cmath>
#include <list>

using namespace std;

int brillo(int i, int j, const image& img) {
    if(i < 0 || j < 0 || img.width <= i || img.height <= j)
        return 0;
    else
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

    return static_cast<int>(sqrt(energiax * energiax + energiay * energiay)); // sqrt devuelve un double
}


// Declaraciones anticipadas de funciones
pair<int, int> obtenerSiguientePixel(const image& img, int fila, int col);
int obtenerCosturaRecursiva(int i, int j, const image& img, 
                            vector<vector<int>>& tablaCostes, vector<vector<bool>>& costesCalculados);

int obtenerCostura(const image& img) {
    // Inicializar tablas con dimensiones de la imagen
    vector<vector<int>> tablaCostes(img.height, vector<int>(img.width, 0));
    vector<vector<bool>> costesCalculados(img.height, vector<bool>(img.width, false));

    // Buscar el píxel de la primera fila con el mínimo camino
    int minCoste = obtenerCosturaRecursiva(0, 0, img, tablaCostes, costesCalculados);
    int minPixel = brillo(0, 0, img);
    pair<int, int> minPosicion = {0, 0};

    for (int i = 1; i < img.width; ++i) {
        int coste = obtenerCosturaRecursiva(i, 0, img, tablaCostes, costesCalculados);
        if (coste < minCoste) {
            minCoste = coste;
            minPixel = brillo(i, 0, img);
            minPosicion = {0, i};
        }
    }

    // Ejemplo de cómo utilizar obtenerSiguientePixel para recorrer la costura
    // (Se asume que se desea recorrer desde la primera fila hasta la última)
    pair<int, int> posicionActual = minPosicion;
    for (int fila = 1; fila < img.height; ++fila) {
        posicionActual = obtenerSiguientePixel(img, posicionActual.first, posicionActual.second);
        if (posicionActual.first == -1) break;
        // Aquí se podrían mover o procesar los píxeles de la fila fila - 1
    }

    return minCoste; // O devolver otro valor según la lógica deseada
}

pair<int, int> obtenerSiguientePixel(const image& img, int fila, int col) {
    int filas = img.height;
    int columnas = img.width;

    // Comprobar que no estamos en la última fila
    if (fila >= filas - 1) {
        return {-1, -1};
    }

    int nuevaCol = col;
    int minCoste = brillo(col, fila + 1, img);

    // Comprobar vecino en la diagonal izquierda
    if (col > 0) {
        int costeIzq = brillo(col - 1, fila + 1, img);
        if (costeIzq < minCoste) {
            minCoste = costeIzq;
            nuevaCol = col - 1;
        }
    }

    // Comprobar vecino en la diagonal derecha
    if (col < columnas - 1) {
        int costeDer = brillo(col + 1, fila + 1, img);
        if (costeDer < minCoste) {
            minCoste = costeDer;
            nuevaCol = col + 1;
        }
    }

    return {fila + 1, nuevaCol};
}

int obtenerCosturaRecursiva(int i, int j, const image& img, int** tablaCostes, bool** costesCalculados) {
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
                         obtenerCosturaRecursiva(i, j + 1, img, tablaCostes, costesCalculados),
                         obtenerCosturaRecursiva(i + 1, j + 1, img, tablaCostes, costesCalculados));
    }
    tablaCostes[j][i] = coste;
    costesCalculados[j][i] = true;
    return coste;
}




-------------





int obtenerCosturaRecursiva(int i, int j, const image& img, 
                            vector<vector<int>>& tablaCostes, vector<vector<bool>>& costesCalculados) {
    // Comprobar límites de la imagen
    if (i < 0 || i >= img.width || j < 0 || j >= img.height)
        return 1000000; // Valor grande para penalizar caminos fuera de rango

    if (costesCalculados[j][i])
        return tablaCostes[j][i];

    int coste = obtenerEnergia(i, j, img);
    if (j < img.height - 1) {
        if (i == 0)
            coste += min(obtenerCosturaRecursiva(i, j + 1, img, tablaCostes, costesCalculados),
                         obtenerCosturaRecursiva(i + 1, j + 1, img, tablaCostes, costesCalculados));
        else if (i == img.width - 1)
            coste += min(obtenerCosturaRecursiva(i - 1, j + 1, img, tablaCostes, costesCalculados),
                         obtenerCosturaRecursiva(i, j + 1, img, tablaCostes, costesCalculados));
        else {
            int a = obtenerCosturaRecursiva(i - 1, j + 1, img, tablaCostes, costesCalculados);
            int b = obtenerCosturaRecursiva(i, j + 1, img, tablaCostes, costesCalculados);
            int c = obtenerCosturaRecursiva(i + 1, j + 1, img, tablaCostes, costesCalculados);
            coste += min({a, b, c});
        }
    }

    tablaCostes[j][i] = coste;
    costesCalculados[j][i] = true;
    return coste;
}