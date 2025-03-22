#include <iostream>
#include <utility>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>
#include <queue>
#include <cmath>
#include <tuple>

using namespace std;

enum movimiento {NORTE, SUR, ESTE, OESTE};

/**
 * Auxiliar para calcular distancia manhattan entre dos celdas
 */
unsigned int manhattan(int x1, int y1, int x2, int y2) {
    return abs(y2 - y1) + abs(x2 - x1);
}

/**
 * Auxiliar para el Predicado 6
 */
bool sonTodasLasCasillasAlcanzables(vector<vector<bool>>& matrix) {
    int rows = matrix.size();
    if (rows == 0) return true;
    int cols = matrix[0].size();

    // Auxiliares durante la búsqueda, representan (arriba, abajo, izquierda, derecha)
    const int dx[] = {-1, 1, 0, 0}; // cambio en el índice de las filas al moverte
    const int dy[] = {0, 0, -1, 1}; // cambio en el índice de las columnas al moverte

    // Encontrar la 1ª casilla no visitada de la matriz
    int startX = -1, startY = -1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j]) {
                startX = i;
                startY = j;
                break;
            }
        }
        if (startX != -1) break;
    }

    // Si no existe ninguna casilla no visitada, todas las casillas son trivialmnete alcanzables
    if (startX == -1) return true;

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    queue<pair<int, int>> q;
    q.push({startX, startY});
    visited[startX][startY] = true;

    // BFS para explorar todas las casillas no visitadas
    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        int x = current.first, y = current.second;

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && 
                matrix[nx][ny] && !visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }

    // Verificar que todas las casillas no visitadas se han explorado en el BFS
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] && !visited[i][j]) {
                return false; // Si alguna casilla no se ha visitado, todas las casillas no son alcanzables
            }
        }
    }

    // Si todas las casillas se han visitado, entonces son alcanzables
    return true;
}

vector<vector<vector<bool>>> nRecorridos_YuMi(
    vector<vector<bool>>& cuadricula,
    const unsigned int  regsRow[4], // vector fila registros
    const unsigned int  regsCol[4], // vector columna registros
    const unsigned int regsPaso[4], // número de pasos hasta cada registro
    const unsigned int meta, // indice de registro que es la meta

    unsigned int  row   = 0, // fila actual
    unsigned int  col   = 0, // columna actual
    unsigned int paso   = 1, // número de pasos actuales
    unsigned int sigReg = 0  // siguiente índice del vector de registros al que llegar
) {

    // Predicado 6: Dado el recorrido actual Yumi no puede completarlo porque hay casillas "no alcanzables"
    if (!sonTodasLasCasillasAlcanzables(cuadricula)) return {};

    
    // Objetivo
    if (row == regsRow[meta] && col == regsCol[meta] && sigReg >= meta &&
        paso == regsPaso[meta]) {
            vector<vector<bool>> path = cuadricula;
            return {path};
    }

    //if(sigReg < meta) {
        // Predicado 5: YuMi no puede llegar al checkpoint en el número de pasos indicado
        if(manhattan(row, col, regsRow[sigReg], regsCol[sigReg]) > regsPaso[sigReg] - paso) {
            return {};
        }
        // Predicado 4: YuMi no llega al checkpoint en el paso establecido
        if(paso == regsPaso[sigReg] && (row != regsRow[sigReg] || col != regsCol[sigReg])) {
            return {};
        }
        // Predicado 3: YuMi llega pronto a un checkpoint
        if(row == regsRow[sigReg] && col == regsCol[sigReg] && paso != regsPaso[sigReg]) {
            return {};
        }
    //}

    // Predicado 1 y 2: Movimiento válido en cuadrícula y celda no ocupada
    vector<movimiento> movimientos;
    if (col > 0 && cuadricula[row][col - 1])
        movimientos.push_back(OESTE);
    if (row > 0 && cuadricula[row - 1][col])
        movimientos.push_back(SUR);
    if (col < cuadricula[0].size() - 1 && cuadricula[row][col + 1])
        movimientos.push_back(ESTE);
    if (row < cuadricula.size() - 1 && cuadricula[row + 1][col])
        movimientos.push_back(NORTE);

    vector<vector<vector<bool>>> caminos;

    for(movimiento m : movimientos) {
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

        cuadricula[nuevaRow][nuevaCol] = false;

        auto childPaths = nRecorridos_YuMi(
            cuadricula,
            regsRow,
            regsCol,
            regsPaso,
            meta,
            nuevaRow,
            nuevaCol,
            paso + 1,
            paso == regsPaso[sigReg] ? sigReg + 1 : sigReg
        );

        caminos.insert(caminos.end(), childPaths.begin(), childPaths.end());

        cuadricula[nuevaRow][nuevaCol] = true;   
    }

    return caminos;
}

bool areComplementary(const vector<vector<bool>>& path1, const vector<vector<bool>>& path2) {
    int filas = path1.size();
    int columnas = path1[0].size();

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if ((path1[i][j] ^ path2[i][j]) != true) {
                return false; // ¡Oh no! Un "false" se coló en la fiesta
            }
        }
    }

    return true; // ¡Alegría! Todos los XOR dieron true 🎉
}

void printPath(const vector<vector<bool>>& matrix) {
    for (const auto& row : matrix) {
        for (bool cell : row) {
            // Assuming true = unvisited (.), false = visited (X)
            cout << (cell ? "." : "X") << " ";
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]) {

    if(argc != 3) {
        cerr << "Error: número de parámetros incorrecto.";
        return -1;
    }

    string fichIn  = argv[1];
    string fichOut = argv[2];

    ifstream fin; fin.open(fichIn);
    if(!fin.is_open()) {
        cerr << "Error: no se puede acceder a \"" + fichIn + "\".";
        return -1;
    }

    ofstream fout; fout.open(fichOut);
    if(!fout.is_open()) {
        cerr << "Error: no se puede abrir/crear \"" + fichOut + "\".";
        return -1;
    }

    unsigned int filas, columnas;
    unsigned int regsRow[4], regsCol[4], regsPaso[4];
    while(fin >> filas >> columnas >> regsRow[0] >> regsCol[0] >> regsRow[1] >> regsCol[1] >> regsRow[2] >> regsCol[2]) {
        auto ini = chrono::high_resolution_clock::now();
        vector<vector<bool>> cuadricula1(filas, vector<bool>(columnas, true));
        vector<vector<bool>> cuadricula2(filas, vector<bool>(columnas, true));
        cuadricula1[0][0] = false;
        //cuadricula2[regsRow[1]][regsCol[1]] = false;
        regsPaso[0] = filas * columnas / 4;
        regsPaso[1] = 2 * filas * columnas / 4;
        regsPaso[2] = 3 * filas * columnas / 4;
        regsPaso[3] = filas * columnas;
        regsRow[3] = 0;
        regsCol[3] = 1;

        /*
        vector<vector<bool>>& cuadricula,
        const unsigned int  regsRow[3], // vector fila registros
        const unsigned int  regsCol[3], // vector columna registros
        const unsigned int regsPaso[3], // número de pasos hasta cada registro
        const unsigned int meta, // indice de registro que es la meta

        unsigned int  row   = 0, // fila actual
        unsigned int  col   = 0, // columna actual
        unsigned int paso   = 1, // número de pasos actuales
        unsigned int sigReg = 0  // siguiente índice del vector de registros al que llegar
        */

        auto result1 = nRecorridos_YuMi(
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

        auto result2 = nRecorridos_YuMi(
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

        int count = 0;

        for (size_t i = 0; i < result1.size(); ++i) {
            for (size_t j = 0; j < result2.size(); ++j) {
                if (areComplementary(result1[i], result2[j])) {
                    ++count;
                }
            }
        }

        auto fin_tiempo = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion = fin_tiempo - ini;
        fout << count << ' ' << fixed << setprecision(5) << duracion.count() << endl;
    }

    fin.close();
    fout.close();
}
