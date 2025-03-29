/**
 * @file RecorrdisoYumi.hpp
 * @brief Implementa métodos estáticos para resovler los problemas de la práctica 3 de Algoritmia Básica.
 */

#pragma once

#include "BitSet.hpp"

#define N 4                                    ///< Número de checkpoints + 1 (la posición final se trata como un checkpoint).
#define ES_INICIO(a, b) ((a) == 0 && (b) == 0) ///< Macro para verificar si una posición es el inicio (0,0).
#define CASILLA_VISITADA false
#define CASILLA_NO_VISITADA true

/**
 * @brief Clase que implementa métodos estáticos para resolver los problemas de la práctica 3 de Algoritmia Básica.
 *
 * Proporciona algoritmos recursivos de búsqueda por backtracking para recorridos en una matriz rectangular.
 *
 * Los predicados utilizados son (en orden de evaluación durante la ejecución):
 * - Predicado 6: comprobar que no hayan casillas aisladas.
 * - Predicado 5: comprobar que es posible llegar al siguiente checkpoint en el número de pasos restante.
 * - Predicado 7: comprobar que no se haya pasado de pasos para el siguiente registro
 * - Predicado 3: Evitar llegar demasiado pronto a la meta o a un checkpoint.
 * - Predicado 4: Se debe llegar al checkpoint en el paso exacto.
 * (Evaluar si se ha llegado al objetivo).
 * - Predicado 1 y 2: Comprobar que se puede mover a una celda válida y que se puede mover a uan celda no visitada.
 */
class RecorridosYumi {
public:
  /**
   * @brief Resuelve el problema mediante búsqueda directa con backtracking.
   *
   * @param b BitSet que representa el estado actual del tablero.
   * @param regsFila[N] Array con la fila de cada checkpoint del tablero.
   * @param regsCol[N] Array con la columna de cada checkpoint del tablero.
   * @param regsPaso[N] Array con restricción de en cada checkpoint cuantos pasos hay que llevar.
   * @param fila Fila actual (default: 0).
   * @param columna Columna actual (default: 0).
   * @param paso Paso actual en el recorrido (default: 1).
   * @param sigReg Índice del siguiente checkpoint que hay que visitar (default: 0).
   * @return unsigned int Número de soluciones encontradas.
   */
  static unsigned int busquedaDirecta(
      BitSet &b,
      const unsigned int regsFila[N],
      const unsigned int regsCol[N],
      const unsigned int regsPaso[N],
      const unsigned int fila = 0,
      const unsigned int columna = 0,
      const unsigned int paso = 1,
      const unsigned int sigReg = 0);

  /**
   * @brief Resuelve el problema mediante búsqueda meet-in-the-middle con backtracking.
   *
   * @param b1 BitSet para la primera mitad del recorrido.
   * @param b2 BitSet para la segunda mitad del recorrido.
   * @param regsFila[N] Array con la fila de cada checkpoint del tablero.
   * @param regsCol[N] Array con la columna de cada checkpoint del tablero.
   * @param regsPaso[N] Array con restricción de en cada checkpoint cuantos pasos hay que llevar.
   * @return unsigned int Número de soluciones encontradas.
   */
  static unsigned int busquedaMeetInTheMiddle(
      BitSet &b1,
      BitSet &b2,
      const unsigned int regsFila[N],
      const unsigned int regsCol[N],
      const unsigned int regsPaso[N]);

private:
  /**
   * @brief Movimientos permitidos para YuMi (sin diagonales).
   * @private
   */
  enum movimiento {
    NORTE, ///< Movimiento hacia arriba.
    SUR,   ///< Movimiento hacia abajo.
    ESTE,  ///< Movimiento hacia la derecha.
    OESTE  ///< Movimiento hacia la izquierda.
  };

  /**
   * @brief Función auxiliar para busquedaMeetInTheMiddle.
   *
   * @param b BitSet para almacenar caminos.
   * @param regsFila[N] Array con la fila de cada checkpoint del tablero.
   * @param regsCol[N] Array con la columna de cada checkpoint del tablero.
   * @param regsPaso[N] Array con restricción de en cada checkpoint cuantos pasos hay que llevar.
   * @param meta Paso objetivo a alcanzar.
   * @param fila Fila actual (default: 0).
   * @param columna Columna actual (default: 0).
   * @param paso Paso actual (default: 1).
   * @param sigReg Índice del siguiente checkpoint que hay que visitar (default: 0).
   * @return std::vector<BitSet> Vector de caminos válidos encontrados.
   * @private
   */
  static std::vector<BitSet> busquedaMeetInTheMiddleAux(
      BitSet &b,
      const unsigned int regsFila[N],
      const unsigned int regsCol[N],
      const unsigned int regsPaso[N],
      const unsigned int meta,
      const unsigned int fila = 0,
      const unsigned int columna = 0,
      const unsigned int paso = 1,
      const unsigned int sigReg = 0);
};
