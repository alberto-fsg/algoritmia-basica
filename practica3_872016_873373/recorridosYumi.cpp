#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

enum movimiento {NORTE, SUR, ESTE, OESTE};

unsigned int nRecorridos_YuMi(
    vector<vector<bool>>& cuadricula,
    const unsigned int  regsRow[3],
    const unsigned int  regsCol[3],
    const unsigned int regsPaso[3],
    unsigned int  row   = 0,
    unsigned int  col   = 0,
    unsigned int paso   = 1,
    unsigned int sigReg = 0
) {
    if(row == 0 && col == 1 && sigReg >= 3 &&
        paso == cuadricula.size() * cuadricula[0].size()) {
            return 1;
    }

    vector<movimiento> movimientos;
    if (col > 0 && cuadricula[row][col - 1])
        movimientos.push_back(OESTE);
    if (row > 0 && cuadricula[row - 1][col])
        movimientos.push_back(SUR);
    if (col < cuadricula[0].size() - 1 && cuadricula[row][col + 1])
        movimientos.push_back(ESTE);
    if (row < cuadricula.size() - 1 && cuadricula[row + 1][col])
        movimientos.push_back(NORTE);

    unsigned int caminos = 0;
    
    for(movimiento m : movimientos) {
        unsigned int nuevaRow = row;
        unsigned int nuevaCol = col;
        switch(m) {
            case OESTE:
                nuevaCol = col - 1; break;

            case ESTE:
                nuevaCol = col + 1; break;

            case SUR:
                nuevaRow = row - 1; break;

            case NORTE:
                nuevaRow = row + 1; break;
        }

        if(sigReg < 3 && paso == regsPaso[sigReg] && 
            (col != regsCol[sigReg] || row != regsRow[sigReg])) {
                //NADA
        } else {

            cuadricula[nuevaRow][nuevaCol] = false;

            caminos += nRecorridos_YuMi(
                cuadricula,
                regsRow,
                regsCol,
                regsPaso,
                nuevaRow,
                nuevaCol,
                paso + 1,
                paso == regsPaso[sigReg] ? sigReg + 1 : sigReg
            );

            cuadricula[nuevaRow][nuevaCol] = true;   
        }
    }

    return caminos;
}

int main(int argc, char* argv[]) {

    if(argc != 3) {
        cerr << "Error: número de parámetros incorrecto.";
        return -1;
    }

    string fichIn  = argv[1];
    string fichOut = argv[2];

    ifstream fin; fin.open(fichIn);
    if(!fin.is_open()) {
        cerr << "Error: no se puede acceder a \"" + fichIn + "\".";
        return -1;
    }

    ofstream fout; fout.open(fichOut);
    if(!fout.is_open()) {
        cerr << "Error: no se puede abrir/crear \"" + fichOut + "\".";
        return -1;
    }

    unsigned int filas, columnas;
    unsigned int regsRow[3], regsCol[3], regsPaso[3];
    while(fin >> filas >> columnas >> regsRow[0] >> regsCol[0] >> regsRow[1] >> regsCol[1] >> regsRow[2] >> regsCol[2]) {
        vector<vector<bool>> cuadricula(filas, vector<bool>(columnas, true));
        cuadricula[0][0] = false;
        regsPaso[0] = filas * columnas / 4;
        regsPaso[1] = 2 * filas * columnas / 4;
        regsPaso[2] = 3 * filas * columnas / 4;
        fout << nRecorridos_YuMi(
            cuadricula,
            regsRow,
            regsCol,
            regsPaso
        ) << endl;
    }

    fin.close();
    fout.close();
}