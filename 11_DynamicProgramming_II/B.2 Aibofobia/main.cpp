#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 El problema se resuelve mediante programacion dinamica sobre subcadenas.
 Definimos s_rec(i, j) como el minimo numero de letras que hay que anadir
 para convertir en palindromo la subcadena s[i..j].

 Si i >= j, la subcadena ya es palindroma y no hay que anadir ninguna letra.
 Si s[i] == s[j], ambos caracteres pueden formar parte del palindromo final
 y el problema se reduce a resolver la subcadena interior s[i+1..j-1].
 Si s[i] != s[j], tenemos dos opciones: anadir una copia de s[i] al final,
 resolviendo s[i+1..j], o anadir una copia de s[j] al principio, resolviendo
 s[i..j-1]. Se escoge la opcion que requiera menos inserciones.

 Los valores se guardan en una matriz para no recalcular subproblemas. Despues,
 con la matriz ya calculada, se reconstruye un palindromo optimo siguiendo las
 decisiones que dan lugar al minimo.

 Sea n la longitud de la palabra. Hay O(n^2) subproblemas distintos, uno por
 cada pareja de indices i, j. Cada uno se calcula en tiempo constante, por lo
 que el coste temporal es O(n^2). La memoria adicional utilizada es O(n^2) por
 la matriz, mas O(n) para el palindromo reconstruido.


 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int s_rec(string const& s, int i, int j, Matriz<int>& ms) {
    int& res = ms[i][j];
    if(res == -1){
        if (i > j) res = 0;
        else if (i == j) res = 0;
        else if (s[i] == s[j]) res = s_rec(s, i + 1, j - 1, ms);
        else
            res = min(s_rec(s, i + 1, j, ms) + 1, s_rec(s, i, j - 1, ms) + 1);
    }

    return res;
}

void reconstruir(string const& s, Matriz<int> const& ms, int i, int j, string& sol) {
    if (i > j) return;
    if (i == j) sol.push_back(s[i]);
    else if (s[i] == s[j]) {
        sol.push_back(s[i]);
        reconstruir(s, ms, i + 1, j - 1, sol);
        sol.push_back(s[i]);
    }else if (ms[i + 1][j] <= ms[i][j - 1]) { 
        sol.push_back(s[i]); 
        reconstruir(s, ms, i + 1, j, sol); 
        sol.push_back(s[i]); 
    } else { 
        sol.push_back(s[j]); 
        reconstruir(s, ms, i, j - 1, sol); 
        sol.push_back(s[j]); 
    }
}

bool resuelveCaso() {

    // leer los datos de la entrada
    string s;
    cin >> s;

    if (!std::cin)  // fin de la entrada
        return false;

    // resolver el caso posiblemente llamando a otras funciones
    int n = s.length();
    Matriz<int> ms(n, n, -1);
    cout << s_rec(s, 0, n - 1, ms) << " ";
    string sol;
    reconstruir(s, ms, 0, n - 1, sol);
    cout << sol << endl;



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
