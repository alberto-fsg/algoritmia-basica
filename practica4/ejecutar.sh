#!/bin/bash

echo "Compiling sources..."
./build.sh || exit 1

echo "Executing tests..."
bin/transporte tests/pruebas.txt tests/resultados.txt
python src/transporte.py tests/pruebas.txt tests/resultados_lineal_programming.txt

bin/transporte tests_adicionales/pruebas.txt tests_adicionales/resultados.txt
python src/transporte.py tests_adicionales/pruebas.txt tests_adicionales/resultados_lineal_programming.txt

echo "Cleaning executable..."
./clean.sh
