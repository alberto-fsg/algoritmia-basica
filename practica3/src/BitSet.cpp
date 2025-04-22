#include <sstream>

#include "BitSet.hpp"

BitSet::BitSet(const unsigned int filas, const unsigned int columnas) : f(filas), c(columnas), size(filas * columnas), bits((filas * columnas + 63) / 64, ~0ULL) {
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
  if (f != otro.f || c != otro.c)
    return false; // descartar si no tienen el mismo tamaño
  unsigned int numero_bloques = (f * c + 63) / 64;
  for (unsigned int i = 0; i < numero_bloques; i++) {
    uint64_t valores_esperados = ~0ULL;
    if (i == numero_bloques - 1) { // adapta los valores esperados para el último bloque, según como de incompleto esté
      unsigned int bits_vacios = f * c % 64;
      if (bits_vacios != 0)
        valores_esperados = (1ULL << bits_vacios) - 1;
    }
    if ((bits[i] ^ otro.bits[i]) != valores_esperados)
      return false;
  }
  return true;
}

std::string BitSet::toString() const {
  std::ostringstream oss;
  for (unsigned int fila = 0; fila < f; ++fila) {
    for (unsigned int columna = 0; columna < c; ++columna) {
      oss << (get(fila, columna) ? '.' : 'x');
    }
    oss << '\n';
  }
  return oss.str();
}

BitSet BitSet::generarComplemento() const {
  BitSet resultado(f, c); // Crear un nuevo BitSet con las mismas dimensiones

  unsigned int numero_bloques = bits.size();
  for (unsigned int i = 0; i < numero_bloques; i++) {
    // Calculars el complemento de cada bloque
    resultado.bits[i] = ~bits[i];
  }

  // Ajustar el último bloque si no está completo
  unsigned int bits_utiles = f * c % 64;
  if (bits_utiles != 0 && numero_bloques > 0) {
    unsigned int ultimo_bloque = numero_bloques - 1;
    uint64_t mascara = (1ULL << bits_utiles) - 1;
    resultado.bits[ultimo_bloque] &= mascara; // Limpiar los bits no utilizados
  }

  return resultado;
}
