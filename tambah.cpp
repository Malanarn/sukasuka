#include <iostream>
using namespace std;

int main() {
    int data[5] = {10, 20, 30, 40, 50}; // Inisialisasi array
    int total = 0;

    // Menampilkan isi array
    cout << "Isi array awal:\n";
    for (int i = 0; i <= 4; i++) {
        cout << "data[" << i << "] = " << data[i] << endl;
    }

    // Menambah setiap elemen dengan 3
    for (int i = 0; i <= 4; i++) {
        data[i] = data[i] + 3; // atau data[i] += 3;
    }

    // Menampilkan isi array setelah ditambah 3
    cout << "\nIsi array setelah ditambah 3:\n";
    for (int i = 0; i <= 4; i++) {
        cout << "data[" << i << "] = " << data[i] << endl;
    }

    // Menghitung total nilai array
    total = 0;
    for (int i = 0; i <= 4; i++) {
        total = total + data[i]; // atau total += data[i];
    }

    cout << "\nTotal nilai seluruh elemen array: " << total << endl;

    return 0;
}

