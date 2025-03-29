/**
 * @file BitSet.hpp
 * @brief Implementa una estructura de datos para manejar eficientemente bits.
 */

#pragma once

#include <cstdint>
#include <string>
#include <vector>

/**
 * @brief Estructura de datos para manejar eficientemente bits.
 *
 * Tiene tamaño estático. A diferencia de std::bitset, su tamaño se define en tiempo de ejecución.
 */
class BitSet {
public:
  unsigned int f;             ///< Número de filas
  unsigned int c;             ///< Número de columnas
  unsigned int size;          ///< Tamaño total de posiciones (filas * columnas)
  std::vector<uint64_t> bits; ///< Bloques de 64 bits que almacenan la información

  /**
   * @brief Constructor de la clase BitSet
   * @param filas Número de filas del BitSet
   * @param columnas Número de columnas del BitSet
   */
  BitSet(const unsigned int filas, const unsigned int columnas);

  /**
   * @brief Obtiene el valor de un bit en la posición especificada
   * @param fila Fila del bit a consultar
   * @param columna Columna del bit a consultar
   * @return Valor del bit en la posición (fila, columna)
   * @note Es responsabilidad del usuario no acceder a una posición fuera del rango definido
   */
  bool get(const unsigned int fila, const unsigned int columna) const;

  /**
   * @brief Establece el valor de un bit en la posición especificada
   * @param fila Fila del bit a modificar
   * @param columna Columna del bit a modificar
   * @param valor Nuevo valor para el bit
   * @note Es responsabilidad del usuario no modificar una posición fuera del rango definido
   */
  void set(const unsigned int fila, const unsigned int columna, const bool valor);

  /**
   * @brief Comprueba si este BitSet es complementario con otro
   * @param otro BitSet con el que comparar
   * @return true sii para cada posición definida, un BitSet vale 1 y el otro 0
   */
  bool esComplemento(const BitSet &otro) const;

  /**
   * @brief Genera una representación en formato string del BitSet
   * @return String que representa el contenido del BitSet
   */
  std::string toString() const;

  /**
   * @brief Genera un BitSet complementario a esta instancia
   * @return Nuevo BitSet donde cada bit es el complementario del original
   * @note Para cada posición definida, un BitSet vale 1 y el otro 0
   */
  BitSet generarComplemento() const;
};
