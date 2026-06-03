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

#include "EnterosInf.h"
#include "Matriz.h"// propios o los de las estructuras de datos de clase

/*@ <answer>

 Utilizo programación dinámica ascendente con espacio optimizado.

 El problema se resuelve como un problema limitado de tipo 0/1, ya que cada
 cordel concreto puede utilizarse como mucho una vez. Para cada longitud j
 entre 0 y L calculo tres valores:

 - formas[j]: número de formas distintas de conseguir longitud j.
 - minCuerdas[j]: mínimo número de cordeles necesario para conseguir longitud j.
 - minCoste[j]: mínimo coste necesario para conseguir longitud j.

 El caso base es la longitud 0: hay una forma de conseguirla, usando 0 cordeles
 y con coste 0.

 Para cada cordel, recorro las longitudes de derecha a izquierda, desde L hasta
 la longitud del cordel. Este orden evita utilizar el mismo cordel más de una vez.

 El coste temporal es O(N * L), siendo N el número de cordeles y L la longitud
 objetivo. El coste espacial es O(L), ya que solo se utilizan vectores de tamaño
 L + 1.
 
 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

struct sol {
    long long numP = 0;
    EntInf minCuerdas = Infinito;
    EntInf minCoste = Infinito;
};

sol devolver_cambio(vector<int> const& longitudes, vector<int> const& costes, int L, int n) {
    sol s;

    vector<long long> formas(L + 1, 0);
    vector<EntInf> minCue(L+1, Infinito);
    vector<EntInf> minCos(L + 1, Infinito);
    
    formas[0] = 1;
    minCue[0] = 0;
    minCos[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = L; j >= longitudes[i-1]; j--) {

            formas[j] += formas[j - longitudes[i - 1]];

            minCue[j] = min(minCue[j], minCue[j - longitudes[i - 1]] + 1);

            minCos[j] = min(minCos[j], minCos[j - longitudes[i - 1]] + costes[i-1]);

        }
    }

    s.numP = formas[L];
    s.minCuerdas = minCue[L];
    s.minCoste = minCos[L];

    return s;
}

bool resuelveCaso() {

    int n, L;
    cin >> n >> L;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> longitudes(n);
    vector<int> costes(n);
    for (int i = 0; i < n; i++) {
        cin >> longitudes[i] >> costes[i];
    }

    sol s = devolver_cambio(longitudes, costes, L, n);

    if (s.numP > 0) cout << "SI" << " " << s.numP << " " << s.minCuerdas << " " << s.minCoste << endl;
    else cout << "NO" << endl;
    // escribir la soluci�n

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta l�nea ya no forma parte de la soluci�n.

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
