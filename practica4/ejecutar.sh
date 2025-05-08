#!/bin/bash

# Para poder ejecutar en lab000
rm -rf env
/usr/bin/python3 -m venv --without-pip env
source env/bin/activate
curl https://bootstrap.pypa.io/pip/3.6/get-pip.py -o get-pip.py; python get-pip.py
pip install pulp

# Compilar
echo "Compiling sources..."
./build.sh || exit 1

# Ejecutar
echo "Executing tests..."
bin/transporte tests/pruebas.txt tests/resultados.txt
python src/transporte.py tests/pruebas.txt tests/resultados_lineal_programming.txt

bin/transporte tests_adicionales/pruebas.txt tests_adicionales/resultados.txt
python src/transporte.py tests_adicionales/pruebas.txt tests_adicionales/resultados_lineal_programming.txt

echo "Cleaning executable..."
./clean.sh