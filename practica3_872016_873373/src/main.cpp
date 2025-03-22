#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <chrono>
#include <queue>
#include <cmath>
#include <vector>
#include <tuple>

#include "BitSet.hpp"
#include "recorridosYumi.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    // Verificar parámetros mínimos requeridos y mostrar uso
    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " <entrada> <salida> [-m <modo>]" << endl;
        cerr << "Modos disponibles: directa, meet-in-the-middle" << endl;
        return -1;
    }

    string fichIn = argv[1];
    string fichOut = argv[2];
    modo mode = DIRECTA;

    // Procesar parámetros opcionales
    int i = 3;
    while (i < argc) {
        string currentArg = argv[i];
        
        if (currentArg == "-m") {
            // Verificar que existe el parámetro de modo
            if (i + 1 >= argc) {
                cerr << "Error: '-m' requiere un parámetro de modo" << endl;
                return -1;
            }
            
            string modeParam = argv[i + 1];
            if (modeParam == "directa") {
                mode = DIRECTA;
            } else if (modeParam == "meet-in-the-middle") {
                mode = MEET_IN_THE_MIDDLE;
            } else {
                cerr << "Error: Modo inválido '" << modeParam << "'" << endl;
                return -1;
            }
            i += 2; // Saltar parámetro y su valor
        } else {
            // Manejar parámetros desconocidos
            cerr << "Error: Parámetro desconocido '" << currentArg << "'" << endl;
            return -1;
        }
    }
    
    ifstream fin(fichIn);
    if (!fin.is_open()) {
        cerr << "Error: no se puede acceder a \"" << fichIn << "\".";
        return -1;
    }
    
    ofstream fout(fichOut);
    if (!fout.is_open()) {
        cerr << "Error: no se puede abrir/crear \"" << fichOut << "\".";
        return -1;
    }
    
    unsigned int filas, columnas;
    unsigned int regsRow[4], regsCol[4];
    while (fin >> filas >> columnas  >> regsRow[0] >> regsCol[0] >> regsRow[1] >> regsCol[1] >> regsRow[2] >> regsCol[2]) {
        auto ini = chrono::high_resolution_clock::now();

        regsRow[3] = 0;
        regsCol[3] = 1;

        fout << nRecorridos_YuMi(filas, columnas, regsRow, regsCol, MEET_IN_THE_MIDDLE) << ' ';

        auto fin_time = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion = fin_time - ini;

        fout << fixed << setprecision(5) << duracion.count() << endl;
    }
    
    fin.close();
    fout.close();
    return 0;
}
