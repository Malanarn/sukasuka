#include <iostream>
using namespace std;

int main() {
    int data[5] = {2, 4, 6, 8, 10};  // Inisialisasi array
    int pengali;

    cout << "Isi array awal:\n";
    for (int i = 0; i <= 4; i++) {
        cout << "data[" << i << "] = " << data[i] << endl;
    }

    cout << "\nMasukkan bilangan untuk mengalikan setiap elemen array: ";
    cin >> pengali;

    // Melakukan perkalian setiap elemen dengan bilangan pengali
    for (int i = 0; i <= 4; i++) {
        data[i] = data[i] * pengali;  // atau data[i] *= pengali;
    }

    // Menampilkan hasil setelah dikalikan
    cout << "\nIsi array setelah dikalikan dengan " << pengali << ":\n";
    for (int i = 0; i <= 4; i++) {
        cout << "data[" << i << "] = " << data[i] << endl;
    }

    return 0;
}

