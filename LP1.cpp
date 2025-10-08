#include <iostream>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    char kelas;
    float nilaiAkhir;
};

class Bilangan {
public:
    void tampilData(int x, float y) {
        cout << "Bagian integer : " << x << endl;
        cout << "Bagian float   : " << y << endl;
    }

    void tambah(int x1, float y1, int x2, float y2) {
        cout << "Hasil penjumlahan integer : " << x1 + x2 << endl;
        cout << "Hasil penjumlahan float   : " << y1 + y2 << endl;
    }

    void banding(int x1, int x2) {
        if (x1 > x2)
            cout << x1 << " lebih besar dari " << x2 << endl;
        else if (x1 < x2)
            cout << x1 << " lebih kecil dari " << x2 << endl;
        else
            cout << x1 << " sama dengan " << x2 << endl;
    }
};

class Rekursi {
public:
    int jumlahRekursi(int x, int y) {
        if (x > y)
            return 0;
        cout << x;
        if (x < y) cout << " + ";
        return x + jumlahRekursi(x + 1, y);
    }

    void tampilRekursi(int x, int y) {
        cout << "\nProses penjumlahan rekursif dari " << x
             << " sampai " << y << ":\n";
        int hasil = jumlahRekursi(x, y);
        cout << " = " << hasil << endl;
    }
};

int main() {
	Bilangan bil;
    Rekursi rek;
    int x1 = 5, x2 = 3;
    float y1 = 2.5, y2 = 1.5;
    
    Mahasiswa mhs1 = {"Andi", "230001", 'A', 88.5};
    Mahasiswa mhs2 = {"Budi", "230002", 'B', 91.0};

    cout << "=== DATA MAHASISWA ===" << endl;
    cout << "Nama  : " << mhs1.nama << endl;
    cout << "NIM   : " << mhs1.nim << endl;
    cout << "Kelas : " << mhs1.kelas << endl;
    cout << "Nilai : " << mhs1.nilaiAkhir << endl << endl;

    cout << "Nama  : " << mhs2.nama << endl;
    cout << "NIM   : " << mhs2.nim << endl;
    cout << "Kelas : " << mhs2.kelas << endl;
    cout << "Nilai : " << mhs2.nilaiAkhir << endl;

    cout << "\n=== DATA BILANGAN ===" << endl;
    cout << "Bilangan X:" << endl; bil.tampilData(x1, y1);
    cout << "Bilangan Y:" << endl; bil.tampilData(x2, y2);

    cout << "\nHasil penjumlahan X + Y:" << endl;
    bil.tambah(x1, y1, x2, y2);

    cout << "\nPerbandingan nilai integer X dan Y:" << endl;
    bil.banding(x1, x2);

    cout << "\n=== FUNGSI REKURSI ===" << endl;
    rek.tampilRekursi(3, 7);

    return 0;
}