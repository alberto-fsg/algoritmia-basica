#pragma once

#include "BitSet.hpp"

using namespace std;

/**
 * Movimientos permitidos para YuMi.
 * No puede moverse en diagonal.
 */
enum movimiento {NORTE, SUR, ESTE, OESTE};

/**
 * Modos permitidos para la búsqueda.
 */
enum modo {DIRECTA, MEET_IN_THE_MIDDLE};

unsigned int nRecorridos_YuMi(
    const unsigned int filas,
    const unsigned int columnas,
    const unsigned int  regsRow[3],
    const unsigned int  regsCol[3],
    modo m = DIRECTA
);
