#!/bin/bash

if [ ! -e costuras ]; then
    ./clean.sh > /dev/null 2>&1
    ./compile.sh
fi

DIR_PRUEBAS='pruebas'
OUTPUT_DIR="/tmp/${DIR_PRUEBAS}/resultados"

# Crear directorio de salida principal si no existe
mkdir -p "$OUTPUT_DIR"

# Process profile.jpg
profile_width=$(identify -format "%w" "${DIR_PRUEBAS}/profile.jpg")
profile_arg=$((profile_width - 1))
OUTPUT_PROFILE="${OUTPUT_DIR}/profile"
mkdir -p "$OUTPUT_PROFILE"
./costuras "${DIR_PRUEBAS}/profile.jpg" "$profile_arg" "$OUTPUT_PROFILE"

# Process ejemplo-enunciado.jpg
ejemplo_width=$(identify -format "%w" "${DIR_PRUEBAS}/ejemplo-enunciado.jpg")
ejemplo_arg=$((ejemplo_width - 1))
OUTPUT_EJEMPLO="${OUTPUT_DIR}/ejemplo-enunciado"
mkdir -p "$OUTPUT_EJEMPLO"
./costuras "${DIR_PRUEBAS}/ejemplo-enunciado.jpg" "$ejemplo_arg" "$OUTPUT_EJEMPLO"
