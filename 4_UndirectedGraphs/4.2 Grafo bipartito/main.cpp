#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

  Para decidir si un grafo no dirigido es bipartito intentamos colorear sus
 vértices con dos colores, de forma que los extremos de cada arista tengan
 siempre colores distintos.

 Usamos un vector color, donde color[v] vale -1 si el vértice todavía no ha
 sido visitado, y 0 o 1 si ya ha recibido uno de los dos colores. Recorremos
 todas las componentes conexas del grafo, porque el grafo puede no ser conexo.
 Para cada componente aún no visitada, damos color 0 a un vértice inicial y
 hacemos un recorrido en profundidad. Cuando desde un vértice v llegamos a un
 adyacente w, si w no está coloreado le damos el color contrario a v. Si w ya
 estaba coloreado y tiene el mismo color que v, entonces existe una arista que
 une dos vértices del mismo conjunto y el grafo no es bipartito.

 El coste de la solución es O(V + A), donde V es el número de vértices y A el
 número de aristas, ya que cada vértice se visita una vez y cada arista se
 examina como mucho dos veces. El coste en memoria adicional es O(V), por el
 vector de colores.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Bipartito {
private:
    vector<int> color;
    bool correcto;
    void dfs(Grafo const& g, int v) {
        for (int w : g.ady(v)) {
            if (!correcto) return;

            if (color[w] == -1) {
                color[w] = 1 - color[v];
                dfs(g, w);
            }
            else if (color[w] == color[v]) {
                correcto = false;
            }
        }
    }
public:
    Bipartito(Grafo const& g) : color(g.V(), -1), correcto(true) {
        for (int i = 0; i < g.V(); i++) {
            if (color[i] == -1) {
                color[i] = 0;
                dfs(g, i);
            }
        }
    }

    bool esBipartito() const {
        return correcto;
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
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

    Bipartito b(g);
    cout << (b.esBipartito() ? "SI" : "NO") << endl;

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
