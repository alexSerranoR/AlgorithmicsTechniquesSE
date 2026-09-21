
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

Se utiliza una cola de prioridad que almacena los pacientes que están
esperando para ser atendidos. Para cada paciente se guarda su nombre,
su gravedad y el orden en el que llegó.

La prioridad viene determinada en primer lugar por la gravedad, de forma
que los pacientes con mayor gravedad son atendidos antes. En caso de
tener la misma gravedad, tiene mayor prioridad el paciente que llegó
antes, es decir, el que tiene un número de orden menor.

Cuando se produce un evento de ingreso se inserta el nuevo paciente en
la cola de prioridad. Cuando se produce un evento de atención, se obtiene
el paciente más prioritario, se escribe su nombre y se elimina de la cola.

Si N es el número de eventos, cada inserción y cada eliminación tiene
coste O(log N). Por tanto, el coste total en el peor caso es O(N log N).

El espacio utilizado es O(N).

 @ </answer> */


 // ================================================================
 // Escribe el c?digo completo de tu soluci?n aqu? debajo
 // ================================================================
 //@ <answer>

struct Paciente {
    string nombre;
    int gravedad;
    int orden;
};


bool operator<(Paciente const& a, Paciente const& b) {
    return a.gravedad < b.gravedad || (a.gravedad == b.gravedad && a.orden > b.orden);
}


bool resuelveCaso() {

    int N;
    cin >> N;

    if (N == 0)
        return false;

    priority_queue<Paciente> cola;

    int orden = 0;

    for (int i = 0; i < N; i++) {

        char evento;
        cin >> evento;

        if (evento == 'I') {

            string nombre;
            int gravedad;

            cin >> nombre >> gravedad;

            cola.push({ nombre, gravedad, orden });

            orden++;
        }
        else { // evento == 'A'

            Paciente p = cola.top();
            cola.pop();

            cout << p.nombre << '\n';
        }
    }

    cout << "---" << '\n';

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta l?nea ya no forma parte de la soluci?n.

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
