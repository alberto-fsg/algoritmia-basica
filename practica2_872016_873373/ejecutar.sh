#!/bin/bash

if [ ! -e costuras ]; then
    ./clean.sh > /dev/null 2>&1
    ./compile.sh
fi

DIR_PRUEBAS='pruebas'
OUTPUT_DIR="/tmp/${DIR_PRUEBAS}/resultados"

# Crear directorio de salida si no existe
mkdir -p "$OUTPUT_DIR"

# Ejecutar el comando
./costuras "${DIR_PRUEBAS}/profile.jpg" 150 "$OUTPUT_DIR"