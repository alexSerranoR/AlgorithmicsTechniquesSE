#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


/*@ <answer>

 El problema se modela como un grafo implícito sobre el bitmap. Cada píxel negro
 representa un vértice y dos píxeles negros están conectados si son adyacentes
 horizontal o verticalmente. Por tanto, cada mancha negra corresponde a una
 componente conexa de ese grafo implícito.

 Recorremos todas las posiciones del mapa. Cuando encontramos un píxel negro
 que todavía no ha sido visitado, hemos encontrado una nueva mancha. Entonces
 lanzamos un recorrido en profundidad desde ese píxel, visitando todos los
 píxeles negros conectados con él y contando cuántos forman la mancha. Vamos
 actualizando el número total de manchas y el tamaño máximo encontrado.

 El coste de la solución es O(F*C), donde F es el número de filas y C el número
 de columnas, porque cada celda se procesa como mucho una vez y para cada una
 se comprueban sus cuatro vecinos. El coste en memoria adicional es O(F*C) por
 el vector de visitados.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

using mapa = vector<string>;
class Manchas {
private:
    int F, C;
    vector<vector<bool>> visit;
    int num;
    int maxim;

    bool correcta(int i, int j) const {
        return 0 <= i && i < F && 0 <= j && j < C;
    }

    const vector<pair<int, int>> dirs{ {1,0},{0,1},{-1,0},{0,-1} };

    int dfs(mapa const& M, int i, int j) {
        visit[i][j] = true;
        int tam = 1;
        for (auto d : dirs) {
            int ni = i + d.first, nj = j + d.second;
            if (correcta(ni, nj) && M[ni][nj] == '#' && !visit[ni][nj]) {
                tam += dfs(M, ni, nj);
            }
        }

        return tam;
    }
public:
    Manchas(mapa const& M) : F(M.size()), C(M[0].size()), visit(F, vector<bool>(C, false)), num(0), maxim(0) {
        for (int i = 0; i < F; i++) {
            for (int j = 0; j < C; j++) {
                if (!visit[i][j] && M[i][j] == '#') {
                    ++num;
                    int tam = dfs(M, i, j);
                    maxim = max(tam, maxim);
                }
            }
        }
    }

    int numero() const { return num; }
    int maximo() const { return maxim; }

};


bool resuelveCaso() {
    int F, C;
    cin >> F >> C;

    if (!cin) return false;
    
    mapa mapa(F);
    for (string& linea : mapa)
        cin >> linea;

    Manchas manchas(mapa);
    cout << manchas.numero() << ' ' << manchas.maximo() << '\n';
    
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
