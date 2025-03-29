#include "RecorridosYumi.hpp"
#include "BitSet.hpp"
#include <atomic>
#include <cstdlib>
#include <queue>
#include <thread>
#include <unordered_map>

namespace internal {

/**
 * Auxiliar para el predicado 5.
 */
unsigned int manhattan(const int x1, const int y1, const int x2, const int y2) {
  return abs(y2 - y1) + abs(x2 - x1);
}

/**
 * Auxiliar para el predicado 6.
 */
bool sonTodasLasCasillasAlcanzables(const BitSet &b) {
  int filas = b.f, columnas = b.c;
  if (filas == 0)
    return true;
  std::vector<bool> visitadas(filas * columnas, CASILLA_VISITADA);
  int filaInicio = -1, colInicio = -1;

  /**
   * Buscar la primera celda no visitada
   */
  for (int f = 0; f < filas; ++f) {
    for (int c = 0; c < columnas; ++c) {
      if (b.get(f, c)) {
        filaInicio = f;
        colInicio = c;
        break;
      }
    }
    if (filaInicio != -1)
      break;
  }

  /**
   * Si no se encuentra ninguna celda no visitada, se considera que todas son alcanzables
   */
  if (filaInicio == -1) {
    return true;
  }

  std::queue<std::pair<int, int>> cola;
  cola.push({filaInicio, colInicio});
  visitadas[filaInicio * columnas + colInicio] = CASILLA_NO_VISITADA;

  /**
   * BFS
   */
  const int dx[] = {-1, 1, 0, 0}; // Cambio en filas
  const int dy[] = {0, 0, -1, 1}; // Cambio en columnas

  while (!cola.empty()) {
    auto actual = cola.front();
    cola.pop();
    int f = actual.first, c = actual.second;
    for (int i = 0; i < 4; ++i) {
      int nf = f + dx[i], nc = c + dy[i];
      if (nf >= 0 && nf < filas && nc >= 0 && nc < columnas && b.get(nf, nc) &&
          !visitadas[nf * columnas + nc]) {
        visitadas[nf * columnas + nc] = true;
        cola.push({nf, nc});
      }
    }
  }

  /**
   * Verificar que todas las celdas no visitadas hayan sido alcanzadas
   */
  for (int f = 0; f < filas; ++f)
    for (int c = 0; c < columnas; ++c)
      if (b.get(f, c) && !visitadas[f * columnas + c])
        return false;

  return true;
}
} // namespace internal

unsigned int RecorridosYumi::busquedaDirecta(BitSet &b,
                                             const unsigned int regsFila[N],
                                             const unsigned int regsCol[N],
                                             const unsigned int regsPaso[N],
                                             const unsigned int fila,
                                             const unsigned int columna,
                                             const unsigned int paso,
                                             const unsigned int sigReg) {
  /**
   * Predicado 6: comprobar que no hayan casillas aisladas.
   */
  if (!internal::sonTodasLasCasillasAlcanzables(b)) {
    return 0;
  }

  /**
   * Predicado 5: comprobar que es posible llegar al siguiente checkpoint en el número de pasos restante.
   */
  if (internal::manhattan(fila, columna, regsFila[sigReg], regsCol[sigReg]) > regsPaso[sigReg] - paso) {
    return 0;
  }

  /**
   * Predicado 7: comprobar que no se haya pasado de pasos para el siguiente registro
   */
  if (paso > regsPaso[sigReg]) {
    return 0;
  }

  /**
   * Predicado 3: Evitar llegar demasiado pronto a la meta o a un checkpoint.
   */
  for (unsigned int i = 0; i < N; ++i) {
    if (sigReg <= i &&
        fila == regsFila[i] &&
        columna == regsCol[i] &&
        paso != regsPaso[i]) {
      return 0;
    }
  }

  /**
   * Predicado 4: Se debe llegar al checkpoint en el paso exacto.
   */
  if (paso == regsPaso[sigReg] && (fila != regsFila[sigReg] || columna != regsCol[sigReg])) {
    return 0;
  }

  /**
   * Objetivo
   */
  if (fila == 0 && columna == 1 && sigReg == N - 1 && paso == b.size) {
    return 1;
  }

  /**
   * Generar los movimientos válidos a partir de la posición actual.
   * Predicado 1: comprobar que se puede mover a una celda válida
   * Predicado 2: comprobar que se puede mover a uan celda no visitada
   */
  std::vector<movimiento> movimientos;
  if (columna > 0 && b.get(fila, columna - 1)) {
    movimientos.push_back(OESTE);
  }
  if (fila > 0 && b.get(fila - 1, columna)) {
    movimientos.push_back(SUR);
  }
  if (columna < b.c - 1 && b.get(fila, columna + 1)) {
    movimientos.push_back(ESTE);
  }
  if (fila < b.f - 1 && b.get(fila + 1, columna)) {
    movimientos.push_back(NORTE);
  }

  /**
   * Explorar recursivamente cada movimiento posible (backtracking).
   */
  unsigned int caminos = 0;

  for (movimiento m : movimientos) {
    unsigned int nuevaFila = fila;
    unsigned int nuevaCol = columna;
    switch (m) {
    case OESTE:
      nuevaCol = columna - 1;
      break;
    case ESTE:
      nuevaCol = columna + 1;
      break;
    case SUR:
      nuevaFila = fila - 1;
      break;
    case NORTE:
      nuevaFila = fila + 1;
      break;
    }

    b.set(nuevaFila, nuevaCol, CASILLA_VISITADA); // Marcar la celda como visitada
    caminos += busquedaDirecta(b, regsFila, regsCol, regsPaso, nuevaFila, nuevaCol, paso + 1, (paso == regsPaso[sigReg] ? sigReg + 1 : sigReg));
    b.set(nuevaFila, nuevaCol, CASILLA_NO_VISITADA); // Deshacer el movimiento (backtracking)
  }

  return caminos;
}

std::vector<BitSet> RecorridosYumi::busquedaMeetInTheMiddleAux(BitSet &b,
                                                               const unsigned int regsFila[N],
                                                               const unsigned int regsCol[N],
                                                               const unsigned int regsPaso[N],
                                                               const unsigned int meta,
                                                               const unsigned int fila,
                                                               const unsigned int columna,
                                                               const unsigned int paso,
                                                               const unsigned int sigReg) {
  /**
   * Si es la 1ª mitad, no puede pisar ningún checkpoint pasada su meta
   */
  if (meta != N - 1) {
    for (unsigned int i = meta + 1; i < N - 1; i++) {
      if (fila == regsFila[i] && columna == regsCol[i]) {
        return {};
      }
    }
  }

  /**
   * Si es la 2ª mitad, no puede pisar ningún checkpoint pasada antes de meta
   */
  else {
    for (unsigned int i = 0; i < (N - 1) / 2 - 1; i++) {
      if (fila == regsFila[i] && columna == regsCol[i]) {
        return {};
      }
    }
  }

  /**
   * Predicado 6: comprobar que no hayan casillas aisladas.
   */
  if (!internal::sonTodasLasCasillasAlcanzables(b)) {
    return {};
  }

  /**
   * Predicado 5: comprobar que es posible llegar al siguiente checkpoint en el número de pasos restante.
   */
  if (internal::manhattan(fila, columna, regsFila[sigReg], regsCol[sigReg]) > regsPaso[sigReg] - paso) {
    return {};
  }

  /**
   * Predicado 7: comprobar que no se haya pasado de pasos para el siguiente registro
   */
  if (paso > regsPaso[sigReg]) {
    return {};
  }

  /**
   * Predicado 3: Evitar llegar demasiado pronto a la meta o a un checkpoint. meta -1
   */
  for (unsigned int i = 0; i < N; ++i) {
    if (sigReg <= i && fila == regsFila[i] && columna == regsCol[i] && paso != regsPaso[i]) {
      return {};
    }
  }

  /**
   * Predicado 4: Se debe llegar al checkpoint en el paso exacto.
   */
  if (paso == regsPaso[sigReg] && (fila != regsFila[sigReg] || columna != regsCol[sigReg])) {
    return {};
  }

  /**
   * Objetivo
   */
  if (fila == regsFila[meta] && columna == regsCol[meta] && sigReg == meta && paso == regsPaso[meta]) {
    return {b};
  }

  /**
   * Generar los movimientos válidos a partir de la posición actual.
   * Predicado 1: comprobar que se puede mover a una celda válida
   * Predicado 2: comprobar que se puede mover a uan celda no visitada
   */
  std::vector<movimiento> movimientos;
  if (columna > 0 && b.get(fila, columna - 1)) {
    movimientos.push_back(OESTE);
  }
  if (fila > 0 && b.get(fila - 1, columna)) {
    movimientos.push_back(SUR);
  }
  if (columna < b.c - 1 && b.get(fila, columna + 1)) {
    movimientos.push_back(ESTE);
  }
  if (fila < b.f - 1 && b.get(fila + 1, columna)) {
    movimientos.push_back(NORTE);
  }

  /**
   * Explorar recursivamente cada movimiento posible (backtracking).
   */
  std::vector<BitSet> caminos;

  for (movimiento m : movimientos) {
    unsigned int nuevaFila = fila;
    unsigned int nuevaCol = columna;
    switch (m) {
    case OESTE:
      nuevaCol = columna - 1;
      break;
    case ESTE:
      nuevaCol = columna + 1;
      break;
    case SUR:
      nuevaFila = fila - 1;
      break;
    case NORTE:
      nuevaFila = fila + 1;
      break;
    }

    b.set(nuevaFila, nuevaCol, CASILLA_VISITADA); // Marcar la celda como visitada
    auto caminosHijo = busquedaMeetInTheMiddleAux(b,
                                                  regsFila,
                                                  regsCol,
                                                  regsPaso,
                                                  meta,
                                                  nuevaFila,
                                                  nuevaCol,
                                                  paso + 1,
                                                  (paso == regsPaso[sigReg] ? sigReg + 1 : sigReg));
    caminos.insert(caminos.end(), caminosHijo.begin(), caminosHijo.end());
    b.set(nuevaFila, nuevaCol, CASILLA_NO_VISITADA); // Deshacer el movimiento (backtracking)
  }

  return caminos;
}

unsigned int RecorridosYumi::busquedaMeetInTheMiddle(BitSet &b1,
                                                     BitSet &b2,
                                                     const unsigned int regsFila[N],
                                                     const unsigned int regsCol[N],
                                                     const unsigned int regsPaso[N]) {
  std::vector<BitSet> resultado1, resultado2;
  b1.set(0, 0, CASILLA_VISITADA);

  /**
   * Buscar cada mitad en paralelo.
   */
  std::thread t1([&]() {
    resultado1 = busquedaMeetInTheMiddleAux(b1, regsFila, regsCol, regsPaso, 1, 0, 0, 1, 0);
  });
  std::thread t2([&]() {
    resultado2 = busquedaMeetInTheMiddleAux(b2, regsFila, regsCol, regsPaso, 3, regsFila[1], regsCol[1], regsPaso[1], 2);
  });
  t1.join();
  t2.join();

  /**
   * Buscar mitadas compatibles con todos los cores disponibles.
   */

  // Almacenar caminos de resultado2 en un hashmap
  std::unordered_map<std::string, int> frecuenciaResultado2;
  for (const auto &bs : resultado2) {
    std::string clave = bs.toString();
    frecuenciaResultado2[clave]++;
  }

  // Contador atómico (la concurrencia da miedo)
  std::atomic<int> cuentaAtomica(0);
  std::vector<std::thread> hilos;
  unsigned int num_hilos = std::thread::hardware_concurrency();
  if (num_hilos == 0)
    num_hilos = 2;
  size_t tamBloque = (resultado1.size() + num_hilos - 1) / num_hilos;

  for (unsigned int t = 0; t < num_hilos; t++) {
    size_t inicio = t * tamBloque;
    size_t fin = std::min(inicio + tamBloque, resultado1.size());

    // Crear el hilo con una función lambda (la función que ejeecuta)
    hilos.emplace_back([inicio, fin, &resultado1, &frecuenciaResultado2, &cuentaAtomica]() {
      int cuentaLocal = 0;
      for (size_t i = inicio; i < fin; ++i) {
        BitSet complemento = resultado1[i].generarComplemento();
        std::string clave = complemento.toString();

        auto it = frecuenciaResultado2.find(clave);
        if (it != frecuenciaResultado2.end()) {
          cuentaLocal += it->second; // Sumar el número de caminos complementarios (mismo hash)
        }
      }
      cuentaAtomica += cuentaLocal;
    });
  }

  for (auto &t : hilos)
    t.join();
  return cuentaAtomica.load();
}
