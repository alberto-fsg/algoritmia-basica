#include "abb.hpp"

/**
 * Destructor árbol
 */
Arbol::~Arbol() {
    delete this->izq;
    delete this->der;
}

/**
 * Crear árbol con solo un elemento
 */
Arbol::Arbol(unsigned frecuencia)
    : frecuencia(frecuencia), izq(nullptr), der(nullptr) {}

/**
 * Crea árbol con hijos izq y der, cuya raíz tiene
 * como frecuencia la suma de sus hijos más próximos.
 */
Arbol::Arbol(Arbol* izq, Arbol* der)
    : izq(izq), der(der) {
        this->frecuencia = izq->getFrecuencia() + der->getFrecuencia();
}

/**
 * Devuelve hijo izquierdo si existe, en caso contrario
 * nullptr.
 */
Arbol* Arbol::subarbolIzq() const {
    return this->izq;
}

/**
 * Devuelve hijo derecho si existe, en caso contrario
 * nullptr.
 */
Arbol* Arbol::subarbolDer() const {
    return this->der;
}

/**
 * Getter frecuencia
 */
unsigned Arbol::getFrecuencia() const {
    return this->frecuencia;
}

/**
 * Crea diccionario con pares {carácter, codificar(carácter)}
 * recorriendo árbol en pre-orden
 */
void Arbol::getCodificacion(unordered_map<char, string>& dic, string cadena) {
    if(this->izq == nullptr && this->der == nullptr) {
        Hoja* hoja = dynamic_cast<Hoja*>(this);
        dic[hoja->getValor()] = cadena;
    } else {
        this->izq->getCodificacion(dic, cadena + "0");
        this->der->getCodificacion(dic, cadena + "1");
    }
}

/**
 * Sobrecarga de operadores <
 * Menor frecuencia tiene mayor prioridad
 */
bool Arbol::operator<(const Arbol& otro) const {
    return this->frecuencia < otro.frecuencia;
}

/**
 * Constructor de clase Hoja
 */
Hoja::Hoja(int frecuencia, char valor)
    : Arbol(frecuencia), valor(valor) {}

/**
 * Devuelve el valor de la hoja
 */
char Hoja::getValor() {
    return this->valor;
}