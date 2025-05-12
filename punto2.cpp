#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

const int NUM_CILINDROS = 5000;
const int NUM_SOLICITUDES = 1000;

vector<int> generarSolicitudes() {
    vector<int> solicitudes;
    for (int i = 0; i < NUM_SOLICITUDES; i++) {
        solicitudes.push_back(rand() % NUM_CILINDROS);
    }
    return solicitudes;
}

int fcfs(const vector<int>& requests, int head) {
    int movimientos = 0;
    for (int req : requests) {
        movimientos += abs(req - head);
        head = req;
    }
    return movimientos;
}

int scan(vector<int> requests, int head) {
    int movimientos = 0;
    requests.push_back(head);
    sort(requests.begin(), requests.end());
    auto it = find(requests.begin(), requests.end(), head);

    for (auto i = it; i != requests.begin();) {
        --i;
        movimientos += abs(*i - head);
        head = *i;
    }

    if (head != 0) {
        movimientos += head;
        head = 0;
    }

    for (auto i = it + 1; i != requests.end(); ++i) {
        movimientos += abs(*i - head);
        head = *i;
    }

    return movimientos;
}

int cscan(vector<int> requests, int head) {
    int movimientos = 0;
    requests.push_back(head);
    sort(requests.begin(), requests.end());
    auto it = find(requests.begin(), requests.end(), head);

   
    for (auto i = it; i != requests.begin();) {
        --i;
        movimientos += abs(*i - head);
        head = *i;
    }

    if (head != 0) {
        movimientos += head;
    }

    movimientos += NUM_CILINDROS - 1;
    head = NUM_CILINDROS - 1;

    
    for (auto i = requests.end() - 1; i > it; --i) {
        movimientos += abs(*i - head);
        head = *i;
    }

    return movimientos;
}
void compararMovimientos(int movFCFS, int movSCAN, int movCSCAN) {
    cout << "\n==== Comparacion de Movimientos ====\n";
    cout << left << setw(10) << "Algoritmo" << setw(15) << "Movimientos" << "\n";
    cout << left << setw(10) << "FCFS" << setw(15) << movFCFS << "\n";
    cout << left << setw(10) << "SCAN" << setw(15) << movSCAN << "\n";
    cout << left << setw(10) << "C-SCAN" << setw(15) << movCSCAN << "\n";
}

int main() {
    int cabeza;

    cout << "Ingrese la posicion inicial del cabezal (0 - " << NUM_CILINDROS - 1 << "): ";
    cin >> cabeza;

    if (cin.fail() || cabeza < 0 || cabeza >= NUM_CILINDROS) {
        cerr << "Posicion invalida. Debe estar entre 0 y " << NUM_CILINDROS - 1 << ".\n";
        return 1;
    }

    srand(time(nullptr));
    vector<int> solicitudes = generarSolicitudes();

    cout << "\nSe generaron " << NUM_SOLICITUDES << " solicitudes aleatorias.\n";

    int movFCFS = fcfs(solicitudes, cabeza);
    int movSCAN = scan(solicitudes, cabeza);
    int movCSCAN = cscan(solicitudes, cabeza);

    compararMovimientos(movFCFS, movSCAN, movCSCAN);

    return 0;
}
