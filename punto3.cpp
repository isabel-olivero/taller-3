#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

const int NUM_CILINDROS = 80;
const int NUM_SOLICITUDES = 20;

vector<int> generarSolicitudes() {
    vector<int> solicitudes;
    for (int i = 0; i < NUM_SOLICITUDES; i++) {
        solicitudes.push_back(rand() % NUM_CILINDROS);
    }
    return solicitudes;
}

int fcfs(const vector<int>& requests, int head, vector<int>& recorrido) {
    int movimientos = 0;
    recorrido.push_back(head);
    for (int req : requests) {
        movimientos += abs(req - head);
        head = req;
        recorrido.push_back(head);
    }
    return movimientos;
}

int scan(vector<int> requests, int head, vector<int>& recorrido) {
    int movimientos = 0;
    recorrido.push_back(head);
    requests.push_back(head);
    sort(requests.begin(), requests.end());

    auto it = find(requests.begin(), requests.end(), head);
    for (auto i = it; i != requests.end(); ++i) {
        movimientos += abs(*i - head);
        head = *i;
        recorrido.push_back(head);
    }
    for (auto i = it - 1; i >= requests.begin(); --i) {
        movimientos += abs(*i - head);
        head = *i;
        recorrido.push_back(head);
    }

    return movimientos;
}

int cscan(vector<int> requests, int head, vector<int>& recorrido) {
    int movimientos = 0;
    recorrido.push_back(head);
    requests.push_back(head);
    sort(requests.begin(), requests.end());

    auto it = find(requests.begin(), requests.end(), head);

    for (auto i = it + 1; i != requests.end(); ++i) {
        movimientos += abs(*i - head);
        head = *i;
        recorrido.push_back(head);
    }

    if (head != NUM_CILINDROS - 1) {
        movimientos += (NUM_CILINDROS - 1 - head);
        recorrido.push_back(NUM_CILINDROS - 1);
        movimientos += NUM_CILINDROS - 1;
        head = 0;
        recorrido.push_back(0);
    }

    for (auto i = requests.begin(); i < it; ++i) {
        movimientos += abs(*i - head);
        head = *i;
        recorrido.push_back(head);
    }

    return movimientos;
}

void visualizarRecorrido(const vector<int>& recorrido, const string& nombre) {
    cout << "\n==== " << nombre << " ====\n";
    for (int pos : recorrido) {
        for (int i = 0; i < NUM_CILINDROS; i++) {
            cout << (i == pos ? "*" : "-");
        }
        cout << " (" << pos << ")\n";
    }
}

void compararMovimientos(int fcfs, int scan, int cscan) {
    cout << "\n==== Comparacion de Movimientos ====\n";
    cout << left << setw(10) << "Algoritmo" << setw(15) << "Movimientos" << "\n";
    cout << left << setw(10) << "FCFS" << setw(15) << fcfs << "\n";
    cout << left << setw(10) << "SCAN" << setw(15) << scan << "\n";
    cout << left << setw(10) << "C-SCAN" << setw(15) << cscan << "\n";
}

int main() {
    int cabeza;

    cout << "Ingrese la posicion inicial del cabezal (0 - " << NUM_CILINDROS - 1 << "): ";
    cin >> cabeza;

    if (cin.fail() || cabeza < 0 || cabeza >= NUM_CILINDROS) {
        cerr << "Posicion inválida. Debe estar entre 0 y " << NUM_CILINDROS - 1 << ".\n";
        return 1;
    }

    srand(time(nullptr));
    vector<int> solicitudes = generarSolicitudes();

    cout << "Solicitudes generadas:\n";
    for (int s : solicitudes) cout << s << " ";
    cout << "\n";

    vector<int> recorridoFCFS, recorridoSCAN, recorridoCSCAN;
    int movFCFS = fcfs(solicitudes, cabeza, recorridoFCFS);
    int movSCAN = scan(solicitudes, cabeza, recorridoSCAN);
    int movCSCAN = cscan(solicitudes, cabeza, recorridoCSCAN);

    visualizarRecorrido(recorridoFCFS, "FCFS");
    visualizarRecorrido(recorridoSCAN, "SCAN");
    visualizarRecorrido(recorridoCSCAN, "C-SCAN");

    compararMovimientos(movFCFS, movSCAN, movCSCAN);

    return 0;
}
