
/*@ <authors>
 *
 * E86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;


/*@ <answer>

Se utiliza una cola de prioridad de mínimos que contiene todos los
sumandos disponibles.

Mientras haya más de un elemento, se extraen los dos valores mínimos,
se suman y se añade dicha suma al coste total. El resultado de la suma
se introduce de nuevo en la cola, ya que deberá participar en sumas
posteriores.

Elegir siempre los dos elementos menores minimiza el coste total,
ya que los resultados intermedios pueden volver a ser utilizados
en sumas posteriores.

Si N es el número de elementos, se realizan N-1 sumas. Cada operación
sobre la cola de prioridad tiene coste O(log N), por lo que el coste
total es O(N log N).


 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

    int n;
    cin >> n;

    if (n == 0)
        return false;

    priority_queue<long long, vector<long long>, greater<long long>> cola;

    for (int i = 0; i < n; ++i) {
        long long num;
        cin >> num;
        cola.push(num);
    }

    long long coste = 0;

    while (cola.size() > 1) {

        long long a = cola.top();
        cola.pop();
        long long b = cola.top();
        cola.pop();

        long long suma = a + b;

        coste += suma;

        cola.push(suma);
    }

    cout << coste << '\n';

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
