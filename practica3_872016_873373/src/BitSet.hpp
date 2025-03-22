#pragma once

#include <vector>
#include <cstdint>

using namespace std;

/*
 * Estructura de datos para manejar eficientemente bits.
 * Tiene tamaño estático.
 * A diferencia de std::bitset, su tamaño se define en tiempo de ejecución.
 */
class BitSet {
    public:
        unsigned int f, c; // filas y columnas (acortados para no ocultar los parámetros de las funciones)
        vector<uint64_t> bits; // bloques de 64 bits
    
        BitSet(const unsigned int filas, const unsigned int columnas);
        bool get(const unsigned int fila, const unsigned int columna) const;
        void set(const unsigned int fila, const unsigned int columna, const bool valor);

        /*
         * Devuelve true si y solo si esta instancia y el BitSet "otro" son complementarios.
         * Dos BitSets se consideran complementarios cuando, para cada posición definida, un BitSet vale 1 y el otro 0.
         */
        bool esComplemento(const BitSet &otro) const;
};
