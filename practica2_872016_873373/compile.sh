#!/bin/bash
raiz=$(pwd)

spinner() {
    local delay=0.25
    local frames=(">  " ">> " ">>>" " >>" "  >" "   ")
    local num_frames=${#frames[@]}
    while true; do
        for (( i=0; i<num_frames; i++ )); do
            echo -ne "\rCompilando ${frames[i]}"
            sleep $delay
        done
    done
}

spinner &
spinner_pid=$!

cd ${raiz}/libs/dependencias/zlib
./configure --prefix=${raiz}/libs > /dev/null 2>&1
make > /dev/null 2>&1
make install > /dev/null 2>&1

kill "$spinner_pid" > /dev/null 2>&1
wait "$spinner_pid" > /dev/null 2>&1
echo -ne "\rBiblioteca para la compresión de archivos compilada  ✅\n"
spinner &
spinner_pid=$!

cd ${raiz}/libs/dependencias/libpng
CPPFLAGS="-I${raiz}/libs/include" ./configure --prefix=${raiz}/libs --disable-shared > /dev/null 2>&1
make > /dev/null 2>&1
make install > /dev/null 2>&1

kill "$spinner_pid" > /dev/null 2>&1
wait "$spinner_pid" > /dev/null 2>&1
echo -ne "\rBiblioteca de gestión de imágenes PNG compilada      ✅\n"
spinner &
spinner_pid=$!

cd ${raiz}/libs/dependencias/libjpeg
cmake -G"Unix Makefiles" -DCMAKE_INSTALL_PREFIX=${raiz}/libs -DENABLE_SHARED=OFF -DWITH_SIMD=0 . > /dev/null 2>&1
make > /dev/null 2>&1
make install > /dev/null 2>&1

kill "$spinner_pid" > /dev/null 2>&1
wait "$spinner_pid" > /dev/null 2>&1
echo -ne "\rBiblioteca de gestión de imágenes JPG/JPEG compilada ✅\n"
spinner &
spinner_pid=$!

cd ${raiz}
g++ -O2 -std=c++11 -Iinclude \
    -Ilibs/include \
    -o costuras \
    src/costuras/main.cpp \
    src/costuras/gestorImg.cpp \
    src/costuras/costuras.cpp \
    -Llibs/lib \
    -Wl,-rpath=libs/lib \
    -lpng -ljpeg -lz

kill "$spinner_pid" > /dev/null 2>&1
wait "$spinner_pid" > /dev/null 2>&1
echo -ne "\rPROGRAMA COMPILADO :)\n"
