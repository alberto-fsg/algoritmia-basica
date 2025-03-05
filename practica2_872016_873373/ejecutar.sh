#!/bin/bash

# Si no existe el ejecutable "costuras", se limpian y compilan los archivos
if [ ! -e costuras ]; then
    ./clean.sh > /dev/null 2>&1
    ./compile.sh
fi

DIR_PRUEBAS='pruebas'
BASE_OUTPUT="/tmp"
USERNAME=$(whoami)  # Obtener el nombre de usuario
ALGO_DIR="${BASE_OUTPUT}/algoritmia_basica_${USERNAME}"
OUTPUT_DIR="${ALGO_DIR}/resultados"

# Crear los directorios de una sola vez
mkdir -p "$OUTPUT_DIR"

# Imprimir mensaje con el directorio donde se guardarán las imágenes generadas
echo "Las imágenes generadas se guardarán en: $OUTPUT_DIR"

process_image() {
    local image_name="$1"
    local image_path="${DIR_PRUEBAS}/${image_name}"
    # Nombre sin extensión para crear la carpeta de salida
    local base_name="${image_name%.*}"
    local output_folder="${OUTPUT_DIR}/${base_name}"

    # Crear el subdirectorio de salida si no existe
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

# Llamar a las nuevas imágenes
process_image "prueba1.jpg"
process_image "prueba2.jpg"
process_image "prueba3.jpg"
process_image "prueba4.png"

