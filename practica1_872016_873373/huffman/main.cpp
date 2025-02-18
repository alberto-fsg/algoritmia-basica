#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>

#include "abb.hpp"

using namespace std;

/**
 * Reorganizar frecuencias para codificacion Huffman con longitud limitada
 */
void limitar(unordered_map<char, int> &frecuencia, int lim) {
    vector<pair<char, int>> items;
    for(auto& kv : frecuencia)
        items.push_back({kv.first, kv.second});

    // Ordenamos de mayor a menor frecuencia
    sort(items.begin(), items.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });

    // Paso 1: Limitar los que exceden lim
    for(auto& p : items)
        p.second = min(p.second, lim);

    // Paso 2: Incrementar mientras desigualdad Kraft se cumpla
    double sumKraft = 0.0;
    for(auto& i : items)
        sumKraft += pow(2.0, -i.second);

    for(auto& i : items) {
        while(i.second < lim) {
            double _old = pow(2.0, -i.second);
            double _new = pow(2.0, -(i.second + 1));
            double newSumKraft = sumKraft - _old + _new;
            if(newSumKraft <= 1.0) {
                i.second++;
                sumKraft = newSumKraft;
            } else {
                break;
            }
        }
    }

    // Paso 3: Reducir (de menor a mayor) mientras se cumpla desigualdad
    sort(items.begin(), items.end(), [](auto &a, auto &b) {
        return a.second < b.second;
    });

    for(auto& i : items) {
        while(i.second > 1) {
            double _old = pow(2.0, -i.second);
            double _new = pow(2.0, -(i.second - 1));
            double newSumKraft = sumKraft - _old + _new;
            if(newSumKraft <= 1.0) {
                i.second--;
                sumKraft = newSumKraft;
            } else {
                break;
            }
        }
    }

    // Editamos valores del diccionario de frecuencias
    for(auto& i : items) {
        frecuencia[i.first] = lim - i.second;
    }
}

/**
 * Pone en diccionario 'frecuencia' pares {caracter, nº de apariciones} de
 * los caracteres que aparecen en el fichero de nombre 'fich'. Si toda va
 * bien devuelve, true. En caso contrario false.
 */
bool extraerFrecuenciaCaracteres(string fich, unordered_map<char, int>& frecuencia) {
    ifstream in(fich);
    if(!in.is_open()) return false;

    const size_t BUF_SIZE = 4096;
    vector<char> buffer(BUF_SIZE);

    while(in.read(buffer.data(), BUF_SIZE) || in.gcount() > 0) {
        size_t bytesLeidos = in.gcount();
        for(size_t i = 0; i < bytesLeidos; ++i) {
            frecuencia[buffer[i]]++;
        }
    }
    in.close();
    return true;
}

/**
 * Crea árbol de codificación óptimo y lo devuelve.
 */
Arbol* obtenerCodificacion(unordered_map<char, int> frecuencia) {
    // Creamos árbol óptimo de codificación
    priority_queue<Arbol*, vector<Arbol*>, ComparaArbol> monticulo;
    for(const auto& par : frecuencia)
        monticulo.push(new Hoja(par.second, par.first));

    // Si en el texto ha codificar solo aparece un caracter
    if(monticulo.size() == 1) {
        Arbol* x = monticulo.top();
        monticulo.pop();
        Hoja* duplicada = new Hoja(
            static_cast<Hoja*>(x)->getFrecuencia(),
            static_cast<Hoja*>(x)->getValor()
        );
        Arbol* raiz = new Arbol(x, duplicada);
        return raiz;
    }

    // Iniciamos algoritmo
    while(monticulo.size() > 1) {
        Arbol* x = monticulo.top();
        monticulo.pop();
        Arbol* y = monticulo.top();
        monticulo.pop();
        Arbol* z = new Arbol(x, y);
        monticulo.push(z);
    }

    // La raiz de la cola con prioridad es el árbol óptimo
    Arbol* optimo = monticulo.top();
    monticulo.pop();

    // Limpiar montículo eliminando punteros a árboles no necesarios
    while(!monticulo.empty()) {
        delete monticulo.top();
        monticulo.pop();
    }

    return optimo;
}

/**
 * Codificar y escribir en fichero el árbol de codificación en binario (sin
 * guardar las frecuencias, no son necesarias para la decodificación)
 */
void guardarArbol(Arbol* raiz, ofstream& out) {
    if(raiz == nullptr)
        return;
    Hoja* hoja = dynamic_cast<Hoja*>(raiz);
    if(hoja) {
        out.put((char)1); //1 para hoja
        out.put(hoja->getValor());
    } else {
        out.put((char)0); //0 para nodos internos
        guardarArbol(raiz->subarbolIzq(), out); // Lo guardamos en
        guardarArbol(raiz->subarbolDer(), out); // preorden.
    }
}

/**
 * Lee el árbol Huffman desde el archivo binario
 */
Arbol* leerArbol(ifstream& in) {
    char flag;
    if (!in.get(flag)) return nullptr;

    if (flag == 1) {  // Nodo hoja
        char valor;
        if (in.get(valor))
            return new Hoja(0, valor);
    } else {  // Nodo interno
        Arbol* izq = leerArbol(in);
        Arbol* der = leerArbol(in);
        return new Arbol(izq, der);
    }
    return nullptr;
}

/**
 * Devuelve tamaño en bytes del fichero
 */
long getFileSize(const string &filename) {
    ifstream in(filename, ios::binary | ios::ate);
    long tamagno = 0;
    if(in.is_open()) {
            tamagno = in.tellg();
            in.close();
    }
    return tamagno;
}

/**
 * Muestra estadísticas de compresión: tamaño original, comprimido y reducción porcentual.
 */
void mostrarEstadisticas(string original, string comprimido) {
    long tamagno_original   = getFileSize(original);
    long tamagno_compactado = getFileSize(comprimido);
    
    long reducido = tamagno_original - tamagno_compactado;

    cout << "📊 Estadísticas: 📊\n"
         << "-- Archivo original  : " << tamagno_original   << " bytes\n"
         << "-- Archivo comprimido: " << tamagno_compactado << " bytes\n"
         << "-- Decremento total  : " << reducido << " bytes\n" << endl;
}

/**
 * Compacta fichero.
 * Devuelve -1 si error. En caso contrario devuelve 0.
 */
int compactar(string fich, bool limitado = false, int lim = 0) {
    // Extraemos frecuencias
    unordered_map<char, int> frecuencia;
    if(!extraerFrecuenciaCaracteres(fich, frecuencia))
        return -1;

    // Si se pide codificación de longitud limitada, limitamos
    // frecuencias
    if(limitado && lim > 0) {
        limitar(frecuencia, lim);
    }

    // Construimos árbol de codificación óptimo de Huffman
    Arbol* arbolOptimo = obtenerCodificacion(frecuencia);
    unordered_map<char, string> codificacion;
    arbolOptimo->getCodificacion(codificacion);
    
    // Codifico/compacto fichero
    ifstream in(fich);
    if(!in.is_open()) {
        delete arbolOptimo;
        return -1;
    }

    ofstream out(fich + ".huf", ios::binary);
    if(!out.is_open()) {
        in.close();
        delete arbolOptimo;
        return -1;
    }
    
    guardarArbol(arbolOptimo, out);

    char c;
    unsigned char miByte = 0;
    int bitCount = 0;
    while(in.get(c)) {
        string codigo = codificacion[c];
        for(char bit : codigo) {
            if(bit == '1') {
                miByte |= (1 << (7 - bitCount));
            }
            bitCount++;
            if(bitCount == 8) {
                // si llenamos un byte, lo escribimos
                out.put((char)miByte);
                miByte = 0;
                bitCount = 0;
            }
        }
    }
    if(bitCount > 0) {
        out.put((char)miByte);
    }
    unsigned char usedBits = (bitCount == 0 ? 8 : bitCount);
    out.put((char)usedBits);

    in.close();
    out.close();
    mostrarEstadisticas(fich, fich + ".huf");
    delete arbolOptimo;
    return 0;

}

/**
 * Descompactar fichero
 * Devuelve -1 si error. En caso contrario devuelve 0.
 */
int descompactar(string fich) {
    ifstream in(fich, ios::binary);
    if(!in.is_open()) return -1;

    // Leer el árbol óptimo Huffman
    Arbol* arbolOptimo = leerArbol(in);
    if(arbolOptimo == nullptr) {
        in.close();
        return -1;
    }

    // Archivo de salida
    ofstream out(fich.substr(0, fich.size() - 4), ios::binary);
    if(!out.is_open()) {
        in.close();
        delete arbolOptimo;
        return -1;
    }

    // Guardamos posición actual (ya hemos leído árbol) y posición final
    streamoff iniDatos = static_cast<streamoff>(in.tellg());
    in.seekg(0, ios::end);
    streamoff finDatos = static_cast<streamoff>(in.tellg());

    if(finDatos <= iniDatos) {
        in.close();
        out.close();
        delete arbolOptimo;
        return -1;
    }

    in.seekg(finDatos - 1, ios::beg);
    unsigned char bitsUsados;
    in.read(reinterpret_cast<char*>(&bitsUsados), 1);
    if(bitsUsados == 0) bitsUsados = 8;

    // Volver a donde empiezan los datos comprimidos
    in.seekg(iniDatos, ios::beg);
    long totalBytes = static_cast<long>((finDatos - 1) - iniDatos);

    // Leer bytes y decodificar bit a bit usando árbol
    Arbol* nodoActual = arbolOptimo;
    for(long i = 0; i < totalBytes; ++i) {
        unsigned char b;
        if(!in.read(reinterpret_cast<char*>(&b), 1)) {
            break;
        }
        int bitsEnEsteByte = 8;
        if(i == totalBytes - 1) {
            bitsEnEsteByte = (int)bitsUsados;
        }
        for(int bit = 7; bit >= 8 - bitsEnEsteByte; --bit) {
            if((b >> bit) & 1) {
                nodoActual = nodoActual->subarbolDer();
            } else {
                nodoActual = nodoActual->subarbolIzq();
            }
            if(Hoja* h = dynamic_cast<Hoja*>(nodoActual)) {
                out.put(h->getValor());
                nodoActual = arbolOptimo;
            }
        }
    }

    in.close();
    out.close();
    delete arbolOptimo;
    return 0;
}

/**
 * Devuelve -1 y muestra la correcta forma de uso del programa
 */
int mostrarError() {
    cerr << "Orden no reconocida. Uso:\n"
         << " >  huf -c <nom_fichero>\n"
         << " >  huf -l <num> -c <nom_fichero>\n"
         << " >  huf -d <nom_fichero>"
         << endl;
    return -1;
}

/**
 * Programa principal. Codifica o decodifica texto dado usando
 * codificación de Huffman
 */
int main(int argc, char** argv) {
    if(argc < 3)
        return mostrarError();

    string comando = argv[1];
    if(comando.compare("-d") == 0) {
        descompactar(argv[2]);
    } else if(comando.compare("-c") == 0) {
        compactar(argv[2]);
    } else if(comando.compare("-l") == 0) {
        if(argc < 5)
            return mostrarError();

        int lim = 0;
        try {
            lim = stoi(argv[2]);
        } catch(...) {
            return mostrarError();
        }
        if(string(argv[3]).compare("-c") == 0) {
            compactar(argv[4], true, lim);
        } else {
            return mostrarError();
        }
    } else {
        return mostrarError();
    }
}