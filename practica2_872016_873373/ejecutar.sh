#!/bin/bash

if [ ! -e costuras ]; then
    ./clean.sh > /dev/null 2>&1
    ./compile.sh
fi

DIR_PRUEBAS='./pruebas'

./costuras ${DIR_PRUEBAS}/profile.jpg 0   ${DIR_PRUEBAS}/resultados
./costuras ${DIR_PRUEBAS}/profile.jpg 50  ${DIR_PRUEBAS}/resultados
./costuras ${DIR_PRUEBAS}/profile.jpg 150 ${DIR_PRUEBAS}/resultados
./costuras ${DIR_PRUEBAS}/profile.jpg 450 ${DIR_PRUEBAS}/resultados