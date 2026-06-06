#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#include "EnterosInf.h"
#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

EntInf c_c(vector<int> const& C) {
    int m = C.size();
    Matriz<EntInf> cortes(m, m, 0);
    for (int d = 2; d <= m - 1; ++d) {
        for (int i = 0; i + d < m; ++i) {
            int j = i + d;
            cortes[i][j] = Infinito;
            for (int k = i + 1; k <= j - 1; ++k) {
                EntInf temp = cortes[i][k]
                    + cortes[k][j]
                    + EntInf(2 * (C[j] - C[i]));

                if (temp < cortes[i][j]) {
                    cortes[i][j] = temp;
                }
            }
        }
    }

    return cortes[0][m - 1];
}

bool resuelveCaso() {

    int L, N;
    cin >> L >> N;

    if (L == 0 && N == 0)
        return false;

    // resolver el caso posiblemente llamando a otras funciones
    vector<int> C(N+2);
    C[0] = 0;
    for (int i = 1; i <= N; i++)
        cin >> C[i];
    C[N + 1] = L;

    EntInf res = c_c(C);
    cout << res << endl;

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
