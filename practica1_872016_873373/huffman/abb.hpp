#ifndef ABB
#define ABB

#include <string>
#include <unordered_map>
using namespace std;

class Arbol {
    private:
        unsigned frecuencia;
        Arbol *izq, *der;
    public:
        virtual ~Arbol();
        /**
         * Crear árbol con un solo elemento
         */
        Arbol(unsigned frecuencia);
        /**
         * Crear árbol con hijos izq y der, cuya raíz tiene
         * como frecuencia la suma de sus hijos más próximos.  
         */
        Arbol(Arbol* izq, Arbol* der);
        /**
         * Devuelve hijo izquierdo si existe, en caso contrario
         * nullptr.
         */
        Arbol* subarbolIzq() const;
        /**
         * Devuelve hijo derecho si existe, en caso contrario
         * nullptr.
         */
        Arbol* subarbolDer() const;
        /**
         * Getter frecuencia
         */
        unsigned getFrecuencia() const;
        /**
         * Crea diccionario con pares {carácter, codificar(carácter)}
         * recorriendo árbol en pre-orden
         */
        void getCodificacion(unordered_map<char, string>& dic, string cadena = "");
        /**
         * Sobrecarga de operadores <
         * Menor frecuencia tiene mayor prioridad
         */
        bool operator<(const Arbol& otro) const;

};

class Hoja : public Arbol {
    private:
        char valor;
    public:
        /**
         * Constructor de clase Hoja
         */
        Hoja(int frecuencia, char valor);
        /**
         * Devuelve el valor de la hoja
         */
        char getValor();
};

struct ComparaArbol {
    bool operator()(Arbol* a, Arbol* b) const {
        // "a" debe ir antes que "b" si su frecuencia es mayor
        // (min-heap en frecuencias => top tendrá menor frecuencia)
        return a->getFrecuencia() > b->getFrecuencia();
    }
};

#endif
