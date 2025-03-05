#!/bin/bash

# Si no existe el ejecutable "costuras", se limpian y compilan los archivos
if [ ! -e costuras ]; then
    ./clean.sh > /dev/null 2>&1
    ./compile.sh
fi

DIR_PRUEBAS='pruebas'
BASE_OUTPUT="/tmp"
ALGO_DIR="${BASE_OUTPUT}/algoritmia-basica"
OUTPUT_DIR="${ALGO_DIR}/resultados"

# Crear los directorios uno por uno
if [ ! -d "$BASE_OUTPUT" ]; then
    mkdir "$BASE_OUTPUT"
fi

if [ ! -d "$ALGO_DIR" ]; then
    mkdir "$ALGO_DIR"
fi

if [ ! -d "$OUTPUT_DIR" ]; then
    mkdir "$OUTPUT_DIR"
fi

process_image() {
    local image_name="$1"
    local image_path="${DIR_PRUEBAS}/${image_name}"
    # Nombre sin extensión para crear la carpeta de salida
    local base_name="${image_name%.*}"
    local output_folder="${OUTPUT_DIR}/${base_name}"

    # Crear el subdirectorio de salida si no existe
    if [ ! -d "$output_folder" ]; then
        mkdir "$output_folder"
    fi
    
    # Obtener el ancho de la imagen y restarle 1
    local width=$(identify -format "%w" "$image_path")
    local width_arg=$((width - 1))
    
    # Medir el tiempo de procesamiento
    local start_time=$(date +%s.%N)
    ./costuras "$image_path" "$width_arg" "$output_folder"
    local end_time=$(date +%s.%N)
    local elapsed=$(echo "$end_time - $start_time" | bc)
    echo "Procesar ${image_name} ha costado ${elapsed} segundos."
}

# Llamar a las nuevas imágenes
process_image "prueba1.jpg"
process_image "prueba2.jpg"
process_image "prueba3.jpg"
process_image "prueba4.png"
process_image "prueba5.png"
