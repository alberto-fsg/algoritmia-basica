#!/bin/bash

#-----------------------------------------------------#
# 872016 ->              Jorge Soria Romeo            #
# 873373 -> Alberto Francisco Solaz García            #
#.....................................................#
# Script que automatiza la compilación y ejecución    #
# de los programas entregados con los casos de prueba #
#-----------------------------------------------------#

SRC_DIR="src"
TESTS_DIR="tests"
OUTPUT_DIR="bin"

# Flags épicos para reducir el tiempo de ejecución del binario:
# -O3
# -flto: optimizaciones durante el linkado
# -march=native: utilizar todas las intrucciones necesarias de la CPU objetivo
# -funroll-loops: desenrollar agresivamente bucles
# -fno-exceptions: mejora de rendimiento a cambio de no tener excepciones
# -fno-rtti descativa: RTII (necesario para polimorfismo, dynamic_cast, ...)

# -lpthread para que se pueda compilar correctamente la librería <thread> en lab000
g++ -o $OUTPUT_DIR/recorridosYumi $SRC_DIR/main.cpp $SRC_DIR/BitSet.cpp $SRC_DIR/RecorridosYumi.cpp -std=c++11 -O3 -flto -march=native -funroll-loops -fno-exceptions -fno-rtti -lpthread
chmod u+x $OUTPUT_DIR/recorridosYumi
$OUTPUT_DIR/recorridosYumi -m DIRECTA $TESTS_DIR/pruebas.txt $TESTS_DIR/resultados-directa.txt
$OUTPUT_DIR/recorridosYumi -m MEET_IN_THE_MIDDLE $TESTS_DIR/pruebas.txt $TESTS_DIR/resultados-meet-in-the-middle.txt

read -p "¿Quieres ejecutar las otras pruebas? (ADVERTENCIA: Esto tardará mucho tiempo) [y/N] " respuesta
if [[ "$respuesta" =~ ^[Yy]$ ]]; then
    $OUTPUT_DIR/recorridosYumi -m DIRECTA $TESTS_DIR/otras-pruebas.txt $TESTS_DIR/otros-resultados-directa.txt
    $OUTPUT_DIR/recorridosYumi -m MEET_IN_THE_MIDDLE $TESTS_DIR/otras-pruebas.txt $TESTS_DIR/otros-resultados-meet-in-the-middle.txt
fi

rm $OUTPUT_DIR/*
