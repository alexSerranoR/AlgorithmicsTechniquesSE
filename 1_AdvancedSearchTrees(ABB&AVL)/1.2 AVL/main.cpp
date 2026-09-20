
/*@ <authors>
 *
 * F14 Gabriel Fuertes
 * F43 Alejandro Serrano
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "TreeSet_AVL.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
    Set<int> treeSet;
    int N, M;
    cin >> N;
    // leer los datos de la entrada

    if (N == 0)
        return false;
    int aux;
    for (int i = 0; i < N; i++) {
        cin >> aux;
        treeSet.insert(aux);
    }

    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> aux;
        if (aux > treeSet.size()) cout << "??";
        else  cout << treeSet.kesimo(aux);

        cout << endl;
    }

    cout << "---" << endl;



    // resolver el caso posiblemente llamando a otras funciones

    // escribir la solución

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open())
        cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
