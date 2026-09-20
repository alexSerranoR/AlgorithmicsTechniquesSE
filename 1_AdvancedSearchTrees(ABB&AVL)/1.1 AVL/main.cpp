#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

#include "bintree.h"
// propios o los de las estructuras de datos de clase

/*@ <answer>

Resolvemos por recursivo (AVL, altura, maximo, minimo)


1. Caso base: arbol vacio (AVL)
2. Caso recursivo: saber si ramas son AVLs, que el nodo cumpla: que este bien colocado y que este equilibrado (altura)
 - comparamos avls y altura (restamos y >1)

 Buscar si es de busqueda: menor que izq y mayor que derecha. Izq: (x > maximo) pero solo si no viene de un arbol vacio.
  - lo mismo con la derecha

 Nuevo maximo: si tiene hijo derecho, es su maximo. Sino es la raiz.    


 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename T>
struct sol {
    bool avl;
    int altura;
    T menor, mayor;
};


template <typename T>
sol<T> es_avl_rec(BinTree<T> const& arbol) {

    if (arbol.empty()) {
        // El árbol vacío es AVL y tiene altura 0.
        // No tiene menor ni mayor, pero ponemos T() como valor auxiliar.
        return { true, 0, T(), T() };
    }

    else {

        auto iz = es_avl_rec(arbol.left());
        auto dr = es_avl_rec(arbol.right());

        int alt = max(iz.altura, dr.altura) + 1;

        // Si no hay hijo izquierdo, la raíz es el menor
        T menor = arbol.left().empty()
            ? arbol.root()
            : iz.menor;

        // Si no hay hijo derecho, la raíz es el mayor
        T mayor = arbol.right().empty()
            ? arbol.root()
            : dr.mayor;


        bool ordenado =
            (arbol.left().empty() || iz.mayor < arbol.root()) &&
            (arbol.right().empty() || arbol.root() < dr.menor);


        bool esAVL =
            ordenado &&
            iz.avl &&
            dr.avl &&
            abs(iz.altura - dr.altura) < 2;


        return { esAVL, alt, menor, mayor };
    }
}


template <typename T>
bool es_avl(BinTree<T> const& arbol) {
    return es_avl_rec(arbol).avl;
}


bool resuelveCaso() {

    char tipo;
    cin >> tipo;

    if (!cin)
        return false;


    if (tipo == 'N') {

        BinTree<int> arbol = read_tree<int>(cin);

        cout << (es_avl(arbol) ? "SI" : "NO") << '\n';
    }

    else if (tipo == 'P') {

        BinTree<string> arbol = read_tree<string>(cin);

        cout << (es_avl(arbol) ? "SI" : "NO") << '\n';
    }


    return true;
}


int main() {

#ifndef DOMJUDGE

    ifstream in("casos.txt");

    if (!in.is_open()) {
        cout << "Error: no se ha podido abrir casos.txt\n";
        return 1;
    }

    auto cinbuf = cin.rdbuf(in.rdbuf());

#endif


    while (resuelveCaso());


#ifndef DOMJUDGE

    cin.rdbuf(cinbuf);

#endif

    return 0;
}