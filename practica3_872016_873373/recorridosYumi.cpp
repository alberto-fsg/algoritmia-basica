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

unsigned int manhattan(int x1, int y1, int x2, int y2) {
    return abs(y2 - y1) + abs(x2 - x1);
}

/**
 * Implementa
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

unsigned int nRecorridos_YuMi(
    vector<vector<bool>>& cuadricula,
    const unsigned int  regsRow[3],
    const unsigned int  regsCol[3],
    const unsigned int regsPaso[3],
    unsigned int  row   = 0,
    unsigned int  col   = 0,
    unsigned int paso   = 1,
    unsigned int sigReg = 0
) {

    // Predicado 6: Dado el recorrido actual Yumi no puede completarlo porque hay casillas "no alcanzables"
    if (!sonTodasLasCasillasAlcanzables(cuadricula)) return 0;
    
    if (row == 0 && col == 1 && sigReg >= 3 &&
        paso == cuadricula.size() * cuadricula[0].size()) {
            return 1;
    }

    if(sigReg < 3) {
        if(manhattan(row, col, regsRow[sigReg], regsCol[sigReg]) > regsPaso[sigReg] - paso) {
            return 0;
        }
        if(paso == regsPaso[sigReg] && (row != regsRow[sigReg] || col != regsCol[sigReg])) {
            return 0;
        }
        if(row == regsRow[sigReg] && col == regsCol[sigReg] && paso != regsPaso[sigReg]) {
            return 0;
        }
    }

    vector<movimiento> movimientos;                                         // Predicado 1: Movimiento válido en cuadrícula
    if (col > 0 && cuadricula[row][col - 1])                                // Predicado 2: Celda ya visitada
        movimientos.push_back(OESTE);
    if (row > 0 && cuadricula[row - 1][col])
        movimientos.push_back(SUR);
    if (col < cuadricula[0].size() - 1 && cuadricula[row][col + 1])
        movimientos.push_back(ESTE);
    if (row < cuadricula.size() - 1 && cuadricula[row + 1][col])
        movimientos.push_back(NORTE);

    unsigned int caminos = 0;
    
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

        caminos += nRecorridos_YuMi(
            cuadricula,
            regsRow,
            regsCol,
            regsPaso,
            nuevaRow,
            nuevaCol,
            paso + 1,
            paso == regsPaso[sigReg] ? sigReg + 1 : sigReg
        );

        cuadricula[nuevaRow][nuevaCol] = true;   
    }

    return caminos;
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
    unsigned int regsRow[3], regsCol[3], regsPaso[3];
    while(fin >> filas >> columnas >> regsRow[0] >> regsCol[0] >> regsRow[1] >> regsCol[1] >> regsRow[2] >> regsCol[2]) {
        auto ini = chrono::high_resolution_clock::now();
        vector<vector<bool>> cuadricula(filas, vector<bool>(columnas, true));
        cuadricula[0][0] = false;
        regsPaso[0] = filas * columnas / 4;
        regsPaso[1] = 2 * filas * columnas / 4;
        regsPaso[2] = 3 * filas * columnas / 4;
        fout << nRecorridos_YuMi(
            cuadricula,
            regsRow,
            regsCol,
            regsPaso
        );
        fout << ' ';
        auto fin = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> duracion = fin - ini;
        fout << fixed << setprecision(5) << duracion.count() << endl;
    }

    fin.close();
    fout.close();
}
