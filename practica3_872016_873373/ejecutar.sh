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

g++ -o $OUTPUT_DIR/recorridosYumi $SRC_DIR/main.cpp $SRC_DIR/BitSet.cpp $SRC_DIR/recorridosYumi.cpp -std=c++11 -O3
chmod u+x $OUTPUT_DIR/recorridosYumi
$OUTPUT_DIR/recorridosYumi $TESTS_DIR/pruebas.txt $TESTS_DIR/resultados-directa.txt -m directa
$OUTPUT_DIR/recorridosYumi $TESTS_DIR/pruebas.txt $TESTS_DIR/resultados-meet-in-the-middle.txt -m meet-in-the-middle
rm $OUTPUT_DIR/*
