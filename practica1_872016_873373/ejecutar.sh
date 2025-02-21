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
compare_hashes "${DIR_FICHERO}/test_corto01.txt" \
    "Fichero .txt corto 1" \
    "./huf -c ${DIR_FICHERO}/test_corto01.txt"

compare_hashes "${DIR_FICHERO}/test_corto02.txt" \
    "Fichero .txt corto 2" \
    "./huf -c ${DIR_FICHERO}/test_corto02.txt"

compare_hashes "${DIR_FICHERO}/test_largo01.txt" \
    "Fichero .txt largo: Biblia en inglés" \
    "./huf -c ${DIR_FICHERO}/test_largo01.txt"

compare_hashes "${DIR_FICHERO}/test_largo02.txt" \
    "Fichero .txt largo: El Quijote en español" \
    "./huf -c ${DIR_FICHERO}/test_largo02.txt"

compare_hashes "${DIR_FICHERO}/test_caracterEsFrecuente.txt" \
    "Fichero .txt en el que un carácter tiene más frecuencia de aparición que el resto" \
    "./huf -c ${DIR_FICHERO}/test_caracterEsFrecuente.txt"

compare_hashes "${DIR_FICHERO}/test_caracterEsFrecuente.txt" \
    "Fichero .txt en el que un carácter tiene más frecuencia de aparición que el resto (con profundidad limitada)" \
    "./huf -l 3 -c ${DIR_FICHERO}/test_caracterEsFrecuente.txt"

compare_hashes "${DIR_FICHERO}/test_caracterNoFrecuente.txt" \
    "Fichero .txt en el que un carácter tiene menos frecuencia de aparición que el resto" \
    "./huf -c ${DIR_FICHERO}/test_caracterNoFrecuente.txt"

compare_hashes "${DIR_FICHERO}/test_caracterNoFrecuente.txt" \
    "Fichero .txt en el que un carácter tiene menos frecuencia de aparición que el resto (con profundidad limitada)" \
    "./huf -l 3 -c ${DIR_FICHERO}/test_caracterNoFrecuente.txt"

compare_hashes "${DIR_FICHERO}/test_numAparicionesParecidas.txt" \
    "Fichero .txt en el que todos los carácteres tienen misma frecuencia" \
    "./huf -c ${DIR_FICHERO}/test_numAparicionesParecidas.txt"

compare_hashes "${DIR_FICHERO}/test_numAparicionesParecidas.txt" \
    "Fichero .txt en el que todos los carácteres tienen misma frecuencia (con profundidad limitada)" \
    "./huf -l 3 -c ${DIR_FICHERO}/test_numAparicionesParecidas.txt"

compare_hashes "${DIR_FICHERO}/test_binario01.bin" \
    "Fichero binario .bin" \
    "./huf -c ${DIR_FICHERO}/test_binario01.bin"

compare_hashes "${DIR_FICHERO}/test_binario02.exe" \
    "Fichero binario .exe de programa ¡Hola, mundo! en C++" \
    "./huf -c ${DIR_FICHERO}/test_binario02.exe"

# Limpiar .huf
echo
echo "Limpiando binarios y archivos generados ..."
./clean.sh
