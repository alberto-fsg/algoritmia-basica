#include "BitSet.hpp"

BitSet::BitSet(const unsigned int filas, const unsigned int columnas) : f(filas), c(columnas), bits((filas * columnas + 63) / 64, ~0ULL) {
}

bool BitSet::get(const unsigned int fila, const unsigned int columna) const {
    unsigned int indice = fila * c + columna; // posición del bit dentro del vector "bits"
    unsigned int bloque = indice / 64;
    unsigned int bit = indice % 64; // posición del bit dentro del bloque
    return (bits[bloque] >> bit) & 1ULL;
}

void BitSet::set(const unsigned int fila, const unsigned int columna, const bool valor) {
    unsigned int indice = fila * c + columna; // posición del bit dentro del vector "bits"
    unsigned int bloque = indice / 64;
    unsigned int bit = indice % 64; // posición del bit dentro del bloque
    if (valor)
        bits[bloque] |= (1ULL << bit); // set bit a 1
    else
        bits[bloque] &= ~(1ULL << bit); // set bit a 0
}

bool BitSet::esComplemento(const BitSet &otro) const {
    if (f != otro.f || c != otro.c) return false; // descartar si no tienen el mismo tamaño
    unsigned int numero_bloques = (f * c + 63) / 64;
    for (unsigned int i = 0; i < numero_bloques; i++) {
        uint64_t valores_esperados = ~0ULL;
        if (i == numero_bloques - 1) { // adapta los valores esperados para el último bloque, según como de incompleto esté
            unsigned int bits_vacios = f * c % 64;
            if (bits_vacios != 0) valores_esperados = (1ULL << bits_vacios) - 1;
        }
        if ((bits[i] ^ otro.bits[i]) != valores_esperados) return false;
    }
    return true;
}
