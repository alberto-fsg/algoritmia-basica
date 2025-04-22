#!/bin/bash

echo "Compiling sources..."
./build.sh || exit 1

echo "Executing tests..."
bin/transporte tests/pruebas.txt tests/resultados.txt

echo "Cleaning executable..."
./clean.sh
