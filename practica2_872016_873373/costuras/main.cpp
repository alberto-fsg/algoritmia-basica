#include <opencv2/opencv.hpp>
#include <iostream>
#include "auxOpenCV.hpp"
#include "costuras.hpp"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Uso: " << argv[0] << " <ruta_imagen> <n_columnas>" << std::endl;
        return -1;
    }

    std::string nombre_archivo = argv[1];
    int n_columnas = std::stoi(argv[2]);

    cv::Mat mat = cv::imread(nombre_archivo);

    if (mat.empty()) {
        std::cerr << "Error: No se pudo abrir o encontrar la imagen!" << std::endl;
        return -1;
    }

    // Convertir Mat a Image
    Image img = matToImage(mat);

    // Aplicar algoritmo
    algoritmo(img, n_columnas);

    // Convertir Image a Mat
    cv::Mat matConvertida = imageToMat(img);

    // Mostrar la imagen convertida
    cv::imshow("Imagen Convertida", matConvertida);
    cv::waitKey(0);

    return 0;
}
