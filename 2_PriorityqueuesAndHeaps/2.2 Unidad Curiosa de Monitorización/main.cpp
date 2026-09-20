
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

 Se utiliza una cola de prioridad que almacena, para cada usuario,
su identificador, su periodo y el instante en el que debe realizarse
su próximo envío.

La prioridad viene determinada por el instante del próximo envío:
tiene mayor prioridad el usuario cuyo envío deba realizarse antes.
En caso de empate, se da prioridad al usuario con menor identificador,
tal y como indica el enunciado.

Inicialmente, el momento del primer envío de cada usuario coincide
con su periodo. Para cada uno de los K envíos, se extrae de la cola
el usuario más prioritario, se escribe su identificador y se actualiza
el instante de su siguiente envío sumándole su periodo. Después se
vuelve a insertar en la cola.

Si N es el número de usuarios y K el número de envíos, insertar
inicialmente los N usuarios tiene coste O(N log N). Cada uno de los
K envíos realiza una extracción y una inserción en la cola, ambas
de coste O(log N). Por tanto, el coste total es O((N + K) log N).

El espacio utilizado es O(N).

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct registro {
    int momento;
    int id;
    int periodo;
};

bool operator<(registro const& a, registro const& b) {
    return b.momento < a.momento || (a.momento == b.momento && b.id < a.id);
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    cin >> N;
    if (N == 0)
        return false;

    // resolver el caso posiblemente llamando a otras funciones
    priority_queue<registro> cola;

    for (int i = 0; i < N; i++) {
        int id_usu, periodo;
        cin >> id_usu >> periodo;
        cola.push({ periodo, id_usu, periodo });
    }

    int envios;
    cin >> envios;

    while (envios--) {
        auto e = cola.top(); cola.pop();
        cout << e.id << endl;
        e.momento += e.periodo;
        cola.push(e);
    }
    cout << "---" << endl;

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
