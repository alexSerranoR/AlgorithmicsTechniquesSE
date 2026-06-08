#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Para decidir si el grafo no dirigido es un árbol libre usamos que, al no haber
 autoaristas ni aristas paralelas, un grafo es árbol libre si y solo si es conexo
 y tiene exactamente V - 1 aristas.

 Primero leemos el grafo. Si el número de aristas no es V - 1, entonces no puede
 ser árbol libre. En caso contrario, comprobamos si todos los vértices son
 alcanzables desde el vértice 0 mediante un recorrido en profundidad.

 La clase ArbolLibre guarda un vector de visitados y cuenta cuántos vértices se
 alcanzan desde el origen. El grafo será conexo si ese número coincide con V.

 El coste de construir el grafo es O(V + A), donde V es el número de vértices y A
 el número de aristas. El DFS también cuesta O(V + A), porque cada vértice se
 visita una vez y cada arista se examina como mucho dos veces. Por tanto, el
 coste total por caso es O(V + A). El coste en memoria es O(V + A) por la
 representación del grafo y el vector de visitados.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class arbolLibre {
private:
    vector<bool> visit;
    int alcanzados;

    void DFS(Grafo const& g, int v) {
        visit[v] = true;
        alcanzados++;
        for (int w : g.ady(v)) {
            if(!visit[w])
                DFS(g, w);
        }
    }
public:
    arbolLibre(Grafo const& g) : visit(g.V(), false), alcanzados(0) {
        if(g.V() > 0)
            DFS(g, 0);
    }

    bool esConexo(Grafo const& g) const {
        return g.V() == alcanzados;
    }

};

bool resuelveCaso() {

    int V;
    cin >> V;

    if (!std::cin)  // fin de la entrada
        return false;
    
    int A;
    cin >> A;
    Grafo g(V);
    int v, w;
    for (int i = 0; i < A; i++) {
        cin >> v >> w;
        g.ponArista(v, w);
    }
        
    bool libre = false;

    if (A == V - 1) {
        arbolLibre arbol(g);
        libre = arbol.esConexo(g);
    }

    cout << (libre ? "SI" : "NO") << endl;

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
