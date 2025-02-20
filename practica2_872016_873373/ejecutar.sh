#!/bin/bash

g++ costuras/main.cpp -o main `pkg-config --cflags --libs opencv4`
./main profile.jpg
