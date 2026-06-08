#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 El problema se modela mediante un grafo no dirigido en el que cada persona
 es un vértice y cada relación de amistad es una arista. Por la propiedad de
 que los amigos de mis amigos son mis amigos, cada grupo de amigos corresponde
 a una componente conexa del grafo.

 Para encontrar el mayor grupo, recorremos todas las componentes conexas del
 grafo. Usamos un vector de visitados y, cada vez que encontramos un vértice
 no visitado, lanzamos un recorrido en profundidad desde él, contando cuántos
 vértices tiene esa componente. Guardamos el máximo de todos los tamaños
 obtenidos.

 El coste de la solución es O(N + M), donde N es el número de personas y M el
 número de relaciones de amistad, porque cada vértice se visita una vez y cada
 arista se examina como mucho dos veces. El coste adicional en memoria es O(N)
 por el vector de visitados, además del espacio ocupado por el grafo.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class amigos {
private:
    vector<bool> visit;
    int maxin;

    int dfs(Grafo const& g, int v) {
        visit[v] = true;
        int tam = 1;
        for (int w : g.ady(v)) {
            if(!visit[w])
               tam += dfs(g, w);
        }

        return tam;
    }
public:
    amigos(Grafo const& g) : visit(g.V(), false), maxin(0) {
        for (int v = 0; v < g.V(); v++) {
            if (!visit[v]) {
                int tam = dfs(g, v);
                maxin = max(tam, maxin);
            }
        }
    }

    int maxi() const { return maxin; }
};

void resuelveCaso() {

    int N, M;
    cin >> N >> M;

    Grafo a(N);
    int v, w;
    for (int i = 0; i < M; i++) {
        cin >> v >> w;
        a.ponArista(v-1, w-1);
    }

    amigos ami(a);
    cout << ami.maxi() << endl;

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

    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}

