#include <fstream>
#include <iostream>
#include <cstdlib>
#include <limits>
using namespace std;

/**
 * Genera un caso de prueba para el programa
 * Transporte con numPedidos 
 */
void generar_caso_de_prueba(
    unsigned int numPedidos,
    string fich,
    unsigned int maxCapacidad = 100U
) {
    ofstream f = ofstream(fich);
    
    if(!f.is_open()) {
        cerr << "Error al abrir el fichero \"" + fich + "\".";
        return;
    }

    int capacidad = rand() % maxCapacidad + 1, estacionFinal = rand() % 8;
    f << capacidad << ' ' << estacionFinal << ' ' << numPedidos << '\n';
    
    for(int i = 0; i < numPedidos; ++i) {
        int estacionLlegada  = rand() % estacionFinal + 1;
        int estacionSalida = rand() % estacionLlegada;
        int numPasajeros = rand() % capacidad + 2;
        f << estacionSalida << ' ' << estacionLlegada << ' ' << numPasajeros << "\n";
    }

    f.close();
}

int main() {
    generar_caso_de_prueba(200, "fichPrueba");
}