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

process_image() {
    local image_name="$1"
    local image_path="${DIR_PRUEBAS}/${image_name}"
    # Nombre sin extensión para crear la carpeta de salida
    local base_name="${image_name%.*}"
    local output_folder="${OUTPUT_DIR}/${base_name}"
    mkdir -p "$output_folder"
    
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

process_image "profile.jpg"
process_image "ejemplo-enunciado.jpg"
