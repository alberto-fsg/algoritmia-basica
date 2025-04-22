#!/bin/bash

mkdir -p bin
if ! g++ -std=c++11 -O3 -Wall src/main.cpp src/Transporte.cpp -o bin/transporte; then
  echo "Compilation failed" >&2
  exit 1
fi
