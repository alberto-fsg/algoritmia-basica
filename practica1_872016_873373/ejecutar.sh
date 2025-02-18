#!/bin/bash

# -----------------------------------------------------------#
# Autores: Jorge Soria Romeo, Alberto Solaz García           #
# Fecha  : febrero, 2025                                     #
#                                                            #
# Shellscript que automatiza la compilación y ejecución de   #
# los programas entregados con los casos de prueba.          #
# -----------------------------------------------------------#

# Colores ANSI
YELLOW='\033[33m'
RESET='\033[0m'

# Constantes
DIR_FUENTES='./huffman'
DIR_FICHERO='./pruebas'

# Función para calcular hash SHA256 de un archivo
calculate_hash() {
    local fich="$1"
    if [ -f "$fich" ]; then
        sha256sum "$fich" | awk '{print $1}'
    else
        echo "El archivo '$fich' no existe."
        exit 1
    fi
}

# Función para comparar dos hashes
compare_hashes() {
    local file="$1"
    local test_name="$2"
    local test_command="$3"
    local initial_hash=$(calculate_hash "$file")
    
    echo; echo -e "${YELLOW}Prueba ${test_name}: ${RESET}"

    eval "$test_command"
    if [ $? -eq 0 ]; then
        ./huf -d ${file}.huf
        local final_hash=$(calculate_hash "$file")

        if [ "$initial_hash" == "$final_hash" ]; then
            echo "Los archivos son idénticos. Hashes coinciden."
        else
            echo "Los archivos han cambiado. Hashes no coinciden."
        fi
    else
        echo "Error: El comando de compresión falló. No se ejecutará la descomprensión."
    fi
}

# Programa principal: Compila nuestro programa y lanza tests
echo 'Compilando programa...'
g++ "${DIR_FUENTES}/main.cpp" "${DIR_FUENTES}/abb.cpp" -o huf

# Tests
compare_hashes "${DIR_FICHERO}/quijote.txt" "1 - [pruebas/quijote.txt] Fichero .txt largo en castellano" "./huf -c ${DIR_FICHERO}/quijote.txt"
compare_hashes "${DIR_FICHERO}/bible.txt" "2 - [pruebas/bible.txt] Fichero .txt largo en inglés" "./huf -c ${DIR_FICHERO}/bible.txt"
compare_hashes "${DIR_FICHERO}/test_low_freq.txt" "3 - [pruebas/low_freq] Fichero .txt pequeño con número significativo de símbolos de baja frecuencia" "./huf -c ${DIR_FICHERO}/low_freq.txt"
compare_hashes "${DIR_FICHERO}/test_low_freq.txt" "4 - [pruebas/low_freq] Fichero .txt pequeño con número significativo de símbolos de baja frecuencia con límite de profundidad apropiado" "./huf -l 3 -c ${DIR_FICHERO}/low_freq.txt"
compare_hashes "${DIR_FICHERO}/test_low_freq.txt" "5 - [huf] Fichero binario" "./huf -c ${DIR_FICHERO}/../huf"

# Limpiar .huf
echo
echo "Limpiando binarios y archivos generados ..."
./clean.sh
