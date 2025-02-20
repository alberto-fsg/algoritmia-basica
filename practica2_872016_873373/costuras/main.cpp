#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;



int energia () {
    return 0;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Uso: " << argv[0] << " <ruta_de_la_imagen>" << endl;
        return -1;
    }

    // Leer imagen
    Mat imagen = imread(argv[1]);

    // Verificar si la imagen se cargó correctamente
    if (imagen.empty()) {
        cout << "Error: No se pudo cargar la imagen." << endl;
        return -1;
    }

    // Mostrar la imagen en una ventana
    imshow("Imagen Cargada", imagen);

    // Esperar una tecla para cerrar la ventana
    waitKey(0);

    return 0;
}
