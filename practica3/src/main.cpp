/**
 * @file main.cpp
 * @brief Programa principal para probar nuestro algoritmo de resolución de recorridos YuMi con distintos métodos.
 */

#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "BitSet.hpp"
#include "RecorridosYumi.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  /**
   * Verificar parámetros
   */
  if (argc < 4) {
    cerr << "Uso: " << argv[0] << " -m <DIRECTA|MEET_IN_THE_MIDDLE> <entrada> <salida>" << endl;
    return -1;
  }

  /**
   * Procesar parámetro -m
   */
  string metodo = "";
  string fichIn, fichOut;

  if (string(argv[1]) == "-m") {
    metodo = argv[2];
    if (metodo != "DIRECTA" && metodo != "MEET_IN_THE_MIDDLE") {
      cerr << "Error: método debe ser DIRECTA o MEET_IN_THE_MIDDLE" << endl;
      return -1;
    }
    fichIn = argv[3];
    fichOut = argv[4];
  } else {
    cerr << "Error: parámetro -m no encontrado" << endl;
    cerr << "Uso: " << argv[0] << " -m <DIRECTA|MEET_IN_THE_MIDDLE> <entrada> <salida>" << endl;
    return -1;
  }

  /**
   * Abrir ficheros
   */
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

  /**
   * Llamar al algoritmo con cada prueba en el fichero de entrada
   */
  unsigned int filas, columnas;
  unsigned int regsRow[N], regsCol[N], regsPaso[N];
  while (fin >> filas >> columnas >> regsRow[0] >> regsCol[0] >> regsRow[1] >>
         regsCol[1] >> regsRow[2] >> regsCol[2]) {

    /**
     * Iniciar medición de tiempo
     */
    auto ini = chrono::high_resolution_clock::now();

    /**
     * La casilla final se trata como un checkpoint
     */
    regsRow[3] = 0;
    regsCol[3] = 1;

    /**
     * Inicializar el número de pasos que hay que tener en cada checkpoint según el enunciado de la práctica
     */
    regsPaso[0] = filas * columnas / 4;
    regsPaso[1] = 2 * filas * columnas / 4;
    regsPaso[2] = 3 * filas * columnas / 4;
    regsPaso[3] = filas * columnas;

    unsigned int result;
    if (metodo == "DIRECTA") {
      unsigned int nodosGenerados = 0;
      BitSet b(filas, columnas);
      result = RecorridosYumi::busquedaDirecta(b,
                                               regsRow,
                                               regsCol,
                                               regsPaso,
                                               nodosGenerados
                                              );
      cout << "Nodos generados: " << nodosGenerados << endl;
    } else { // MEET_IN_THE_MIDDLE
      BitSet b1(filas, columnas);
      BitSet b2(filas, columnas);
      result = RecorridosYumi::busquedaMeetInTheMiddle(b1,
                                                       b2,
                                                       regsRow,
                                                       regsCol,
                                                       regsPaso);
    }

    fout << result << ' ';

    /**
     * Terminar medición de tiempo y calcular diferencia
     */
    auto fin_time = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = fin_time - ini;

    /**
     * Imprimir resultado
     */
    fout << fixed << setprecision(5) << duracion.count() << endl;
  }

  fin.close();
  fout.close();
  return 0;
}
