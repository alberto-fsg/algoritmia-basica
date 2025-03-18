#include <utility>
#include <cmath>
#include <vector>

typedef std::pair<unsigned int, unsigned int> Coord;

/**
 * Dice si dos puntos son iguales
 */
bool iguales(const Coord& c1, const Coord& c2) {
    return c1.first == c2.first && c1.second == c2.second;
}

/**
 * Distancia Manhattan
 */
unsigned int manhattan(const Coord& c1, const Coord& c2) {
    return abs((int)c1.first - (int)c2.first) + abs((int)c1.second - (int)c2.second);
}

/**
 * Posibles movimientos del robot YuMi
 */
enum movimiento {IZQIERDA, DERECHA, ARRIBA, ABAJO};

/**
 * Algoritmo de búsqueda con retroceso (RECURSIVO) para calcular
 * cuántos recorridos diferentes puede hacer YuMi en una zona a
 * reforestar dado su tamaño y los tres puntos de registro.
 */
unsigned int nRecorridos_YuMi(bool** cuadricula, unsigned int filas, unsigned int columnas,
        unsigned int casillasEntreReg, const Coord* reg, unsigned int sigReg, Coord pos) {

    if(pos.first == 0 && pos.second == 1) {
        return 1;
    }

    // Movimientos posibles
    std::vector<movimiento> movimientos;
    if(pos.second > 0 && cuadricula[pos.first][pos.second - 1]) 
        movimientos.push_back(IZQIERDA);
    if(pos.second < columnas - 1 && cuadricula[pos.first][pos.second + 1])
        movimientos.push_back(DERECHA);
    if(pos.first > 0 && cuadricula[pos.first - 1][pos.second])
        movimientos.push_back(ABAJO);
    if(pos.first < filas - 1 && cuadricula[pos.first + 1][pos.second])
        movimientos.push_back(ARRIBA);

    unsigned int caminos = 0;

    for(movimiento m : movimientos) {
        Coord nuevaPos = pos;
        switch (m) {
            case IZQIERDA:
                nuevaPos.second--; break;
            case DERECHA:
                nuevaPos.second++; break;
            case ABAJO:
                nuevaPos.first--;  break;
            case ARRIBA:
                nuevaPos.first++;  break;
        }

        cuadricula[nuevaPos.first][nuevaPos.second] = false;
        if(sigReg >= 3 || manhattan(nuevaPos, reg[sigReg]) > casillasEntreReg) {
            caminos += nRecorridos_YuMi(
                cuadricula,
                filas, columnas, casillasEntreReg,
                reg,
                (sigReg < 3 && iguales(nuevaPos, reg[sigReg])) ? sigReg + 1 : sigReg,
                nuevaPos
            );
        }
        cuadricula[nuevaPos.first][nuevaPos.second] = true;
    }

    return caminos;
}


/**
 * Programa principal
 */
int main(int argc, char *argv[]) {

}