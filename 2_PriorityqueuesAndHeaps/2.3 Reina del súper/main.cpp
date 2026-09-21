
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

Simulamos la fila única con una cola de prioridad que mantiene, para cada
una de las N cajas, el momento en que quedará libre. En la cola se guardan
registros < momento en que queda libre, número de caja >, ordenados por
la primera componente y, en caso de empate, por la segunda.

Al principio comenzamos con N cajas vacías (libres en el momento 0).
Cuando hay que tratar a un nuevo cliente se le asigna a la caja que antes
quede libre, y se avanza el tiempo de esa caja sumándole el tiempo de
atención del cliente. Tras haber colocado a los C clientes que están
delante, la cima de la cola es la primera caja que quedará libre: esa es
la caja que le toca a Isabel, y es lo que hay que escribir.

Coste en tiempo: O(N + C log N) donde N es el número de cajas y C el número
                 de clientes que esperan en la fila.
El llenado inicial cuesta O(N), y no O(N log N): las cajas
se insertan en orden creciente de número y todas con el
mismo momento (el 0), así que cada caja que se añade es
menos prioritaria que su padre en el montículo y se queda
donde cae, sin reflotar ninguna vez; cada inserción es O(1).
Después, cada uno de los C clientes provoca una extracción
del mínimo y una inserción, y esas sí cuestan O(log N) cada
una porque la cola tiene siempre N elementos.

Coste en espacio adicional: O(N) por la cola de prioridad

@ </answer> */


struct Caja {
    int libre;
    int id;
};

bool operator<(Caja const& a, Caja const& b) {
    return b.libre < a.libre || (a.libre == b.libre && b.id < a.id);
}

bool resuelveCaso() {

    int N, C;
    cin >> N >> C;

    if (N == 0)
        return false;

    // resolver el caso posiblemente llamando a otras funciones
    priority_queue<Caja> cajas;
    for (int i = 1; i <= N; i++) cajas.push({ 0,i });

    for (int i = 0; i < C; i++) {
        int tiempo;
        cin >> tiempo;
        auto caja = cajas.top(); cajas.pop();
        caja.libre += tiempo;
        cajas.push(caja);
    }

    cout << cajas.top().id << endl;

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
