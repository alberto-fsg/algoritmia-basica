#!/bin/bash

# Si no existe el ejecutable "costuras", se limpian y compilan los archivos
if [ ! -e costuras ]; then
    ./clean.sh > /dev/null 2>&1
    ./compile.sh
fi

DIR_PRUEBAS='pruebas'
OUTPUT_DIR="/tmp/${DIR_PRUEBAS}/resultados"

# Crear directorio principal de salida si no existe
mkdir -p "$OUTPUT_DIR"

# Procesar profile.jpg
profile_width=$(identify -format "%w" "${DIR_PRUEBAS}/profile.jpg")
profile_arg=$((profile_width - 1))
OUTPUT_PROFILE="${OUTPUT_DIR}/profile"
mkdir -p "$OUTPUT_PROFILE"

# Medir el tiempo de procesamiento para profile.jpg
start_profile=$(date +%s.%N)
./costuras "${DIR_PRUEBAS}/profile.jpg" "$profile_arg" "$OUTPUT_PROFILE"
end_profile=$(date +%s.%N)
elapsed_profile=$(echo "$end_profile - $start_profile" | bc)
echo "El procesamiento de profile.jpg tomó ${elapsed_profile} segundos."

# Procesar ejemplo-enunciado.jpg
ejemplo_width=$(identify -format "%w" "${DIR_PRUEBAS}/ejemplo-enunciado.jpg")
ejemplo_arg=$((ejemplo_width - 1))
OUTPUT_EJEMPLO="${OUTPUT_DIR}/ejemplo-enunciado"
mkdir -p "$OUTPUT_EJEMPLO"

# Medir el tiempo de procesamiento para ejemplo-enunciado.jpg
start_ejemplo=$(date +%s.%N)
./costuras "${DIR_PRUEBAS}/ejemplo-enunciado.jpg" "$ejemplo_arg" "$OUTPUT_EJEMPLO"
end_ejemplo=$(date +%s.%N)
elapsed_ejemplo=$(echo "$end_ejemplo - $start_ejemplo" | bc)
echo "El procesamiento de ejemplo-enunciado.jpg tomó ${elapsed_ejemplo} segundos."
