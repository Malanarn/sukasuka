#include <iostream>
#include <iomanip>
using namespace std;

class Vektor {
    friend ostream& operator<<(ostream&, const Vektor&);
    friend istream& operator>>(istream&, Vektor&);
public:
    Vektor();
    void penjumlahan_vektor(const Vektor&, const Vektor&);
    void perkalian_vektor(float, const Vektor&);
    void beri_nilaiBanyak(int);
private:
    int elemen[100];
    int banyak;
};

// Konstruktor
Vektor::Vektor() {
    banyak = 3;
    for (int i = 0; i < banyak; i++)
        elemen[i] = 0;
}

void Vektor::beri_nilaiBanyak(int i) {
    banyak = i;
}

istream& operator>>(istream& in, Vektor& A) {
    cout << "\nBanyak elemen : ";
    in >> A.banyak;
    cout << "Masukkan data vektor\n";
    for (int i = 0; i < A.banyak; i++) {
        cout << "Data [" << i + 1 << "] : ";
        in >> A.elemen[i];
    }
    return in;
}

ostream& operator<<(ostream& out, const Vektor& A) {
    cout << endl;
    for (int i = 0; i < A.banyak; i++)
        cout << "S[" << i + 1 << "] = " << setw(5) << A.elemen[i] << "\n";
    return out;
}

void Vektor::penjumlahan_vektor(const Vektor& A, const Vektor& B) {
    banyak = min(A.banyak, B.banyak); // Hindari akses di luar batas array
    for (int i = 0; i < banyak; i++)
        elemen[i] = A.elemen[i] + B.elemen[i];
}

void Vektor::perkalian_vektor(float k, const Vektor& A) {
    banyak = A.banyak;
    for (int i = 0; i < banyak; i++)
        elemen[i] = k * A.elemen[i];
}


