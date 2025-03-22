#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <thread>
#include <atomic>
#include <algorithm>
#include <cstdint>

#include "recorridosYumi.hpp"

/**
 * Auxiliar para calcular distancia manhattan entre dos celdas
 * Para el Predicado 5
 */
unsigned int manhattan(const int x1, const int y1, const int x2, const int y2) {
    return abs(y2 - y1) + abs(x2 - x1);
}

/**
 * Auxiliar para el Predicado 6
 */
bool sonTodasLasCasillasAlcanzables(const BitSet &b) {
    int rows = b.f, cols = b.c;
    if (rows == 0) return true;
    vector<bool> visited(rows * cols, false);
    int startRow = -1, startCol = -1;

    // Encontrar la 1ª casilla no visitada de la matriz
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (b.get(r, c)) {
                startRow = r;
                startCol = c;
                break;
            }
        }
        if (startRow != -1) break;
    }

    // Si no existe ninguna casilla no visitada, todas las casillas son trivialmnete alcanzables
    if (startRow == -1)
        return true;
    
    queue<pair<int, int>> q;
    q.push({startRow, startCol});
    visited[startRow * cols + startCol] = true;

    // Auxiliares durante la búsqueda, representan (arriba, abajo, izquierda, derecha)
    const int dx[] = {-1, 1, 0, 0}; // cambio en el índice de las filas al moverte
    const int dy[] = {0, 0, -1, 1}; // cambio en el índice de las columnas al moverte
    
    // Verificar que todas las casillas no visitadas se han explorado en el BFS
    while (!q.empty()){
        auto current = q.front();
        q.pop();
        int x = current.first, y = current.second;
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && 
                b.get(nx, ny) && !visited[nx * cols + ny]) {
                visited[nx * cols + ny] = true;
                q.push({nx, ny});
            }
        }
    }
    
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            if (b.get(r, c) && !visited[r * cols + c])
                return false; // Si alguna casilla no se ha visitado, todas las casillas no son alcanzables
    
    // Si todas las casillas se han visitado, entonces son alcanzables
    return true;
}

/**
 * Búsqueda directa
 */
 unsigned int nRecorridos_YuMi_Directa(
    BitSet &cuadricula, // vector fila registros
    const unsigned int regsRow[3], // vector columna registros
    const unsigned int regsCol[3], // número de pasos hasta cada registro
    const unsigned int regsPaso[3], // índice de registro que es la meta
    unsigned int row = 0, // fila actual
    unsigned int col = 0, // columna actual
    unsigned int paso = 1, // número de pasos actuales
    unsigned int sigReg = 0  // siguiente índice del vector de registros al que llegar
) {
    // Predicado 6: Dado el recorrido actual Yumi no puede completarlo porque hay casillas "no alcanzables"
    if (!sonTodasLasCasillasAlcanzables(cuadricula)) return 0;
    
    // Objetivo
    if (row == 0 && col == 1 && sigReg >= 3 &&
        paso == cuadricula.f * cuadricula.c) {
            return 1;
    }
    
    if (sigReg < 3) {
        // Predicado 5: YuMi no puede llegar al checkpoint en el número de pasos indicado
        if (manhattan(row, col, regsRow[sigReg], regsCol[sigReg]) > regsPaso[sigReg] - paso) {
            return 0;
        }
        // Predicado 4: YuMi no llega al checkpoint en el paso establecido
        if (paso == regsPaso[sigReg] && (row != regsRow[sigReg] || col != regsCol[sigReg])) {
            return 0;
        }
        // Predicado 3: YuMi llega pronto a un checkpoint
        if (row == regsRow[sigReg] && col == regsCol[sigReg] && paso != regsPaso[sigReg]) {
            return 0;
        }
    }
    
    // Predicado 1 y 2: Movimiento válido en cuadrícula y celda no ocupada
    vector<movimiento> movimientos;
    if (col > 0 && cuadricula.get(row, col - 1))
        movimientos.push_back(OESTE);
    if (row > 0 && cuadricula.get(row - 1, col))
        movimientos.push_back(SUR);
    if (col < cuadricula.c - 1 && cuadricula.get(row, col + 1))
        movimientos.push_back(ESTE);
    if (row < cuadricula.f - 1 && cuadricula.get(row + 1, col))
        movimientos.push_back(NORTE);
    
    unsigned int caminos = 0;
    
    for (movimiento m : movimientos) {
        unsigned int nuevaRow = row;
        unsigned int nuevaCol = col;
        switch(m) {
            case OESTE:
                nuevaCol = col - 1; break;
            case ESTE:
                nuevaCol = col + 1; break;
            case SUR:
                nuevaRow = row - 1; break;
            case NORTE:
                nuevaRow = row + 1; break;
        }
        
        cuadricula.set(nuevaRow, nuevaCol, false);
        
        caminos += nRecorridos_YuMi_Directa(
            cuadricula,
            regsRow,
            regsCol,
            regsPaso,
            nuevaRow,
            nuevaCol,
            paso + 1,
            (paso == regsPaso[sigReg] ? sigReg + 1 : sigReg)
        );
        
        cuadricula.set(nuevaRow, nuevaCol, true);
    }
    
    return caminos;
}

/**
 * Búsqueda meet in the middle
 */
vector<BitSet> nRecorridos_YuMi_Meet_in_the_Middle(
    BitSet &cuadricula,
    const unsigned int regsRow[4], // vector fila registros
    const unsigned int regsCol[4], // vector columna registros
    const unsigned int regsPaso[4], // número de pasos hasta cada registro
    const unsigned int meta, // índice de registro que es la meta
    unsigned int row = 0, // fila actual
    unsigned int col = 0, // columna actual
    unsigned int paso = 1, // número de pasos actuales
    unsigned int sigReg = 0  // siguiente índice del vector de registros al que llegar
) {
    // Predicado 6: Si el recorrido actual no es alcanzable, descartar la rama
    if (!sonTodasLasCasillasAlcanzables(cuadricula)) return {};

    // Objetivo: se ha llegado al registro meta en el número exacto de pasos
    if (row == regsRow[meta] && col == regsCol[meta] && sigReg >= meta &&
        paso == regsPaso[meta])
        return {cuadricula};

    // Predicado 5: YuMi no puede llegar al checkpoint en el número de pasos indicado
    if (manhattan(row, col, regsRow[sigReg], regsCol[sigReg]) > regsPaso[sigReg] - paso)
        return {};
    // Predicado 4: Llegó al checkpoint en el paso equivocado
    if (paso == regsPaso[sigReg] && (row != regsRow[sigReg] || col != regsCol[sigReg]))
        return {};
    // Predicado 3: Llegó demasiado pronto a un checkpoint
    if (row == regsRow[sigReg] && col == regsCol[sigReg] && paso != regsPaso[sigReg])
        return {};

    // Predicado 1 y 2: Movimiento válido en cuadrícula y celda no ocupada
    vector<movimiento> movimientos;
    if (col > 0 && cuadricula.get(row, col - 1))
        movimientos.push_back(OESTE);
    if (row > 0 && cuadricula.get(row - 1, col))
        movimientos.push_back(SUR);
    if (col < cuadricula.c - 1 && cuadricula.get(row, col + 1))
        movimientos.push_back(ESTE);
    if (row < cuadricula.f - 1 && cuadricula.get(row + 1, col))
        movimientos.push_back(NORTE);

    vector<BitSet> caminos;
    for (movimiento m : movimientos) {
        unsigned int nuevaRow = row;
        unsigned int nuevaCol = col;
        switch (m) {
            case OESTE:
                nuevaCol = col - 1;
                break;
            case ESTE:
                nuevaCol = col + 1;
                break;
            case SUR:
                nuevaRow = row - 1;
                break;
            case NORTE:
                nuevaRow = row + 1;
                break;
        }
        cuadricula.set(nuevaRow, nuevaCol, false);
        auto childPaths = nRecorridos_YuMi_Meet_in_the_Middle(
            cuadricula,
            regsRow,
            regsCol,
            regsPaso,
            meta,
            nuevaRow,
            nuevaCol,
            paso + 1,
            (paso == regsPaso[sigReg] ? sigReg + 1 : sigReg)
        );
        caminos.insert(caminos.end(), childPaths.begin(), childPaths.end());
        cuadricula.set(nuevaRow, nuevaCol, true);
    }

    return caminos;
}

unsigned int nRecorridos_YuMi(
    const unsigned int filas,
    const unsigned int columnas,
    const unsigned int regsRow[4],
    const unsigned int regsCol[4],
    modo m
) {
    unsigned int regsPaso[4];
    regsPaso[0] = filas * columnas / 4;
    regsPaso[1] = 2 * filas * columnas / 4;
    regsPaso[2] = 3 * filas * columnas / 4;
    regsPaso[3] = filas * columnas;
    switch (m) {
        case (DIRECTA): {
            BitSet cuadricula(filas, columnas);
            cuadricula.set(0, 0, false);
            return nRecorridos_YuMi_Directa (cuadricula, regsRow, regsCol, regsPaso);
        }
        case (MEET_IN_THE_MIDDLE): {
            BitSet cuadricula1(filas, columnas);
            BitSet cuadricula2(filas, columnas);
            cuadricula1.set(0, 0, false);
            vector<BitSet> result1, result2;

            // Búsqueda en paralelo de las mitades de caminos
            thread t1([&]() {
                result1 = nRecorridos_YuMi_Meet_in_the_Middle(
                    cuadricula1,
                    regsRow,
                    regsCol,
                    regsPaso,
                    1,
                    0,
                    0,
                    1,
                    0
                );
            });
            thread t2([&]() {
                result2 = nRecorridos_YuMi_Meet_in_the_Middle(
                    cuadricula2,
                    regsRow,
                    regsCol,
                    regsPaso,
                    3,
                    regsRow[1],
                    regsCol[1],
                    regsPaso[1],
                    2
                );
            });
            t1.join();
            t2.join();

            // Búsqueda en paralelo de permutaciones válidas
            atomic<int> countAtomic(0);
            vector<thread> threads;
            unsigned int num_threads = thread::hardware_concurrency();
            if (num_threads == 0) num_threads = 2;
            size_t block_size = (result1.size() + num_threads - 1) / num_threads;

            for (unsigned int t = 0; t < num_threads; t++) {
                size_t start = t * block_size;
                size_t end = min(start + block_size, result1.size());
                threads.push_back(thread([start, end, &result1, &result2, &countAtomic]() {
                    int local_count = 0;
                    for (size_t i = start; i < end; ++i) {
                        for (size_t j = 0; j < result2.size(); ++j) {
                            if (result1[i].esComplemento(result2[j])) {
                                local_count++;
                            }
                        }
                    }
                    countAtomic += local_count;
                }));
            }
            for (auto &t : threads) {
                t.join();
            }
            return countAtomic.load();
        }
    }
    return 0;
}
