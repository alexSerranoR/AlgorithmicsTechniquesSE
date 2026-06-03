/*@ <authors>
 *
 * E86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#include "Matriz.h"
#include "EnterosInf.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Utilizo programación dinámica ascendente con espacio optimizado.

 El problema se resuelve como un problema de cambio de monedas ilimitado, ya que
 cada puntuación de la diana puede utilizarse tantas veces como se quiera.

 Sea puntos[j] el mínimo número de dardos necesario para conseguir puntuación j.
 El caso base es puntos[0] = 0, porque para conseguir puntuación 0 no hace falta
 lanzar ningún dardo. El resto de posiciones se inicializan a Infinito.

 Para cada puntuación disponible, recorro j en orden ascendente, desde esa
 puntuación hasta C. Este orden permite reutilizar varias veces la misma
 puntuación.

 Después, si puntos[C] no es Infinito, reconstruyo una solución óptima usando el
 propio vector calculado.

 El coste temporal es O(S * C), siendo S el número de sectores y C la puntuación
 objetivo. El coste espacial es O(C).

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
vector<int> dianas(vector<int> const& p, int C, int S) {
    vector<int> s;
    vector<EntInf> puntos(C + 1, Infinito);
    puntos[0] = 0;
    for (int i = 1; i <= S; i++) {
        for (int j = p[i - 1]; j <= C; j++) {
            puntos[j] = min(puntos[j], puntos[j - p[i - 1]] + 1);
        }
    }

    if (puntos[C] != Infinito) {
        int i = S, j = C;
        while (j > 0) {
            if (j >= p[i - 1] && puntos[j] == puntos[j - p[i - 1]] + 1) {
                s.push_back(p[i - 1]);
                j -= p[i - 1];
            }
            else i--;

        }
    }

    return s;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int C, S;
    cin >> C >> S;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> pun(S);
    for (int i = 0; i < S; i++) cin >> pun[i];
    // resolver el caso posiblemente llamando a otras funciones
    vector<int> s;
    s = dianas(pun, C, S);
    // escribir la solución
    if (s.size() != 0) {
        cout << s.size() << ": ";
        for (int j = 0; j < s.size(); j++) cout << s[j] << " ";
        cout << endl;
    }
    else cout << "Imposible" << endl;

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
