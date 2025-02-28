#include "costuras.hpp"
#include <iostream>
#include <string>
#include <CImg.h>

using namespace std;
using namespace cimg_library;

int main(int argc, char** argv) {
    if (argc < 4) {
        cerr << "Uso: " << argv[0] << " <ruta_imagen> <n_columnas> <directorio_resultado>" << endl;
        return -1;
    }

    // Obtener parámetros
    string nom = argv[1];
    string dir = argv[3];
    if(dir.back() != '/') 
        dir += '/';
    int columnas = stoi(argv[2]);
    const int SAVE_RATIO = 1; // Guardar cada imagen intermedia

    // Cargar imagen
    CImg<unsigned char> cimg(nom.c_str());
    if(cimg.is_empty()) {
        cerr << "Error: no se pudo cargar la imagen." << endl;
        return -1;
    }

    // Convertir en estructura Image
    Image img = cImgToImage(cimg);

    // Procesar y guardar imágenes intermedias
    size_t pos = nom.find_last_of("/\\");
    string nombreArchivo = (pos == string::npos) ? nom : nom.substr(pos + 1);
    algoritmo(img, columnas, dir, nombreArchivo, SAVE_RATIO);

    // Guardar resultado final
    CImg<unsigned char> cimgConvertida = imageToCImg(img);
    string nom_nuevo = dir + "minus" + to_string(columnas) + "_" + nombreArchivo;
    cimgConvertida.save(nom_nuevo.c_str());

    return 0;
}
