#!/bin/bash

DIR_FUENTES='./costuras'
g++ ${DIR_FUENTES}/main.cpp ${DIR_FUENTES}/auxOpenCV.cpp ${DIR_FUENTES}/costuras.cpp -o main `pkg-config --cflags --libs opencv4`

DIR_PRUEBAS='./pruebas'
# PRESIONAR CUALQUIER TECLA PARA SALTAR IMAGENES
./main ${DIR_PRUEBAS}/profile.jpg 0
./main ${DIR_PRUEBAS}/profile.jpg 50
./main ${DIR_PRUEBAS}/profile.jpg 150
./main ${DIR_PRUEBAS}/profile.jpg 450

./clean.sh
