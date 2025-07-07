#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_BARANG = 100;

class Barang {
public:
    string nama;
    string kategori;
    float harga;
    int stok;

    void input() {
        cout << "Nama Barang   : "; cin.ignore(); getline(cin, nama);
        cout << "Kategori      : "; getline(cin, kategori);
        cout << "Harga         : "; cin >> harga;
        cout << "Jumlah Stok   : "; cin >> stok;
    }

    void tampil() {
        cout << left << setw(20) << nama
             << setw(15) << kategori
             << setw(10) << harga
             << setw(8) << stok << endl;
    }
};

class Inventaris {
private:
    Barang data[MAX_BARANG];
    int jumlah;

public:
    Inventaris() { jumlah = 0; }

    void tambahBarang() {
        if (jumlah >= MAX_BARANG) {
            cout << "Kapasitas penuh!\n";
            return;
        }
        cout << "\nData barang ke-" << jumlah + 1 << ":\n";
        data[jumlah].input();
        jumlah++;
    }

    void tampilSemua() {
        cout << "\n--- DAFTAR BARANG ---\n";
        cout << left << setw(20) << "Nama" 
             << setw(15) << "Kategori" 
             << setw(10) << "Harga"
             << setw(8) << "Stok" << endl;

        for (int i = 0; i < jumlah; i++) {
            data[i].tampil();
        }
    }

    void cariBarang(string keyword) {
        cout << "\nHasil pencarian \"" << keyword << "\":\n";
        bool ketemu = false;
        for (int i = 0; i < jumlah; i++) {
            if (data[i].nama.find(keyword) != string::npos ||
                data[i].kategori.find(keyword) != string::npos) {
                data[i].tampil();
                ketemu = true;
            }
        }
        if (!ketemu) cout << "Tidak ditemukan.\n";
    }

    void urutkan(string kriteria) {
        for (int i = 0; i < jumlah - 1; i++) {
            for (int j = i + 1; j < jumlah; j++) {
                bool tukar = false;
                if (kriteria == "nama" && data[i].nama > data[j].nama) tukar = true;
                else if (kriteria == "kategori" && data[i].kategori > data[j].kategori) tukar = true;
                else if (kriteria == "harga" && data[i].harga > data[j].harga) tukar = true;

                if (tukar) {
                    Barang temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                }
            }
        }
        cout << "Data telah diurutkan berdasarkan " << kriteria << ".\n";
    }

    void perbaruiBarang(string namaCari) {
        for (int i = 0; i < jumlah; i++) {
            if (data[i].nama == namaCari) {
                cout << "\nPerbarui data barang \"" << namaCari << "\":\n";
                data[i].input();
                return;
            }
        }
        cout << "Barang tidak ditemukan.\n";
    }

    void hapusBarang(string namaCari) {
        for (int i = 0; i < jumlah; i++) {
            if (data[i].nama == namaCari) {
                for (int j = i; j < jumlah - 1; j++) {
                    data[j] = data[j + 1];
                }
                jumlah--;
                cout << "Barang \"" << namaCari << "\" berhasil dihapus.\n";
                return;
            }
        }
        cout << "Barang tidak ditemukan.\n";
    }

    void simpanLaporan() {
        ofstream file("laporan_barang.txt");
        if (!file) {
            cout << "Gagal menyimpan file.\n";
            return;
        }

        file << "LAPORAN PERSEDIAAN BARANG\n";
        file << "===========================\n";
        for (int i = 0; i < jumlah; i++) {
            file << data[i].nama << "," << data[i].kategori << ","
                 << data[i].harga << "," << data[i].stok << endl;
        }

        file.close();
        cout << "Laporan disimpan ke 'laporan_barang.txt'\n";
    }
};

int main() {
    Inventaris toko;
    int pilihan;
    string input;

    do {
        cout << "\n=== MENU INVENTARIS TOKO ONLINE ===\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Semua Barang\n";
        cout << "3. Cari Barang\n";
        cout << "4. Urutkan Barang\n";
        cout << "5. Perbarui Barang\n";
        cout << "6. Hapus Barang\n";
        cout << "7. Simpan Laporan ke File\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            toko.tambahBarang(); break;
        case 2:
            toko.tampilSemua(); break;
        case 3:
            cout << "Masukkan nama/kategori: ";
            cin.ignore(); getline(cin, input);
            toko.cariBarang(input); break;
        case 4:
            cout << "Urutkan berdasarkan (nama/harga/kategori): ";
            cin >> input;
            toko.urutkan(input); break;
        case 5:
            cout << "Masukkan nama barang yang akan diperbarui: ";
            cin.ignore(); getline(cin, input);
            toko.perbaruiBarang(input); break;
        case 6:
            cout << "Masukkan nama barang yang akan dihapus: ";
            cin.ignore(); getline(cin, input);
            toko.hapusBarang(input); break;
        case 7:
            toko.simpanLaporan(); break;
        case 0:
            cout << "Keluar dari program.\n"; break;
        default:
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    return 0;
}

