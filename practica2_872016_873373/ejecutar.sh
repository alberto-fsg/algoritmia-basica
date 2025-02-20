#!/bin/bash

g++ costuras/main.cpp costuras/auxOpenCV.cpp costuras/costuras.cpp -o main `pkg-config --cflags --libs opencv4`
./main profile.jpg
./clean.sh
