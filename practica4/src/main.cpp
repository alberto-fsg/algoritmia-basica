#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "Transporte.hpp"

using namespace std;

int main(int argc, char **argv) {

  if (argc != 3) {
    cerr << "Uso: transporte <pruebas.txt> <resultados.txt>" << endl;
    return 1;
  }

  string test_file = argv[1];
  ifstream fin(test_file);
  if (!fin.is_open()) {
    cerr << "No se puede abrir el fichero de pruebas: " << test_file << endl;
    return 1;
  }

  string results_file = argv[2];
  ofstream fout(results_file);
  if (!fout.is_open()) {
    cerr << "No se puede abrir el fichero de resultados: " << results_file << endl;
    return 1;
  }

  unsigned int capacity, station, orders;
  while (fin >> capacity >> station >> orders) { // Header of the block
    vector<Request> requests(orders);
    for (auto &r : requests) {
      fin >> r.departure_station_index >> r.arrival_station_index >> r.passengers;
    }

    auto start = chrono::high_resolution_clock::now();

    Transporte t(capacity, station, requests);
    double max_revenue = t.solve();

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration_ms = end - start;

    fout << max_revenue << " " << fixed << setprecision(3) << duration_ms.count() << "\n";
    fout << defaultfloat << setprecision(6); // Reset stream configuration
  }

  return 0;
}
