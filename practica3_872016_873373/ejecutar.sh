#!/bin/bash

#-----------------------------------------------------#
# 872016 ->              Jorge Soria Romeo            #
# 873373 -> Alberto Francisco Solaz García            #
#.....................................................#
# Script que automatiza la compilación y ejecución    #
# de los programas entregados con los casos de prueba #
#-----------------------------------------------------#

g++ -o recorridosYumi ./recorridosYumi.cpp -std=c++11
chmod u+x ./recorridosYumi
./recorridosYumi pruebas.txt resultados.txt