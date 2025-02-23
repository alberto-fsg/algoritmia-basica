#include "costuras.hpp"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    if (argc < 4) {
        cerr << "Uso: " << argv[0] << " <ruta_imagen> <n_columnas> <directorio_resultado>" << endl;
        return -1;
    }

    // Obtener parámetros: nombre de la imagen y nº
    // de columnas que se desea reducir
    string nom = argv[1];
    string dir = argv[3];
    if(dir[dir.size() - 1] != '/') dir += '/';
    int columnas = stoi(argv[2]);

    // Cargar la imagen
    CImg<unsigned char> cimg(nom.c_str());
    if(cimg.is_empty()) {
        cerr << "Error: no se pudo cargar la imagen." << endl;
        return -1;
    }

    // Convertir en estructura Image
    Image img = cImgToImage(cimg);

    // Aplicar algoritmo de costura
    algoritmo(img, columnas);

    // Convertir de Image a CImg
    CImg<unsigned char> cimgConvertida = imageToCImg(img);

    // Guardar resultado
    size_t pos = nom.find_last_of("/\\");
    string nombreArchivo = (pos == string::npos) ? nom : nom.substr(pos + 1);
    string nom_nuevo = dir + "minus" + to_string(columnas) + "_" + nombreArchivo;
    cimgConvertida.save(nom_nuevo.c_str());

    return 0;
}
