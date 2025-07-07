#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAKS_TIKET = 100;
const int MAKS_PENUMPANG = 100;

class Tiket {
public:
    string kode;
    string tujuan;
    int harga;
    bool tersedia;

    void input() {
        cout << "Kode Tiket: ";
        cin >> kode;
        cout << "Tujuan     : ";
        cin >> tujuan;
        cout << "Harga      : ";
        cin >> harga;
        tersedia = true;
    }

    void tampil() {
        if (tersedia) {
            cout << "Kode: " << kode << ", Tujuan: " << tujuan << ", Harga: " << harga << endl;
        }
    }
};

class Penumpang {
public:
    string nama;
    string kodeTiket;

    void input() {
        cout << "Nama Penumpang: ";
        cin >> nama;
        cout << "Kode Tiket    : ";
        cin >> kodeTiket;
    }

    void tampil() {
        cout << "Nama: " << nama << ", Tiket: " << kodeTiket << endl;
    }
};

class SistemTiketPesawat {
private:
    Tiket daftarTiket[MAKS_TIKET];
    Penumpang daftarPenumpang[MAKS_PENUMPANG];
    int jumlahTiket = 0;
    int jumlahPenumpang = 0;

public:
    void tambahTiket() {
        if (jumlahTiket < MAKS_TIKET) {
            cout << "\n--- Tambah Tiket Baru ---\n";
            daftarTiket[jumlahTiket].input();
            jumlahTiket++;
        } else {
            cout << "Kapasitas tiket penuh!\n";
        }
    }

    void tampilkanTiket() {
        cout << "\n--- Daftar Tiket Tersedia ---\n";
        for (int i = 0; i < jumlahTiket; i++) {
            daftarTiket[i].tampil();
        }
    }

    void cariTiketByHarga(int hargaCari) {
        cout << "\n--- Tiket dengan Harga " << hargaCari << " ---\n";
        bool ditemukan = false;
        for (int i = 0; i < jumlahTiket; i++) {
            if (daftarTiket[i].harga == hargaCari && daftarTiket[i].tersedia) {
                daftarTiket[i].tampil();
                ditemukan = true;
            }
        }
        if (!ditemukan) {
            cout << "Tidak ditemukan tiket dengan harga tersebut.\n";
        }
    }

    void pesanTiket() {
        if (jumlahPenumpang < MAKS_PENUMPANG) {
            cout << "\n--- Pemesanan Tiket ---\n";
            Penumpang p;
            p.input();

            // Validasi tiket
            bool valid = false;
            for (int i = 0; i < jumlahTiket; i++) {
                if (daftarTiket[i].kode == p.kodeTiket && daftarTiket[i].tersedia) {
                    valid = true;
                    daftarPenumpang[jumlahPenumpang++] = p;
                    daftarTiket[i].tersedia = false;
                    cout << "Tiket berhasil dipesan!\n";
                    break;
                }
            }
            if (!valid) {
                cout << "Tiket tidak ditemukan atau tidak tersedia!\n";
            }
        } else {
            cout << "Kapasitas penumpang penuh!\n";
        }
    }

    void hapusTiket(string kode) {
        for (int i = 0; i < jumlahTiket; i++) {
            if (daftarTiket[i].kode == kode) {
                daftarTiket[i].tersedia = false;
                cout << "Tiket berhasil dihapus (tidak tersedia).\n";
                return;
            }
        }
        cout << "Tiket tidak ditemukan.\n";
    }

    void simpanPesananKeFile() {
        ofstream file("pesanan_tiket.txt");
        if (file.is_open()) {
            file << "--- Daftar Pesanan Tiket ---\n";
            for (int i = 0; i < jumlahPenumpang; i++) {
                file << "Nama: " << daftarPenumpang[i].nama
                     << ", Tiket: " << daftarPenumpang[i].kodeTiket << endl;
            }
            file.close();
            cout << "Data pesanan berhasil disimpan ke pesanan_tiket.txt\n";
        } else {
            cout << "Gagal menyimpan ke file.\n";
        }
    }

    void menu() {
        int pilihan;
        do {
            cout << "\n===== MENU SISTEM TIKET PESAWAT =====\n";
            cout << "1. Tambah Tiket\n";
            cout << "2. Tampilkan Tiket\n";
            cout << "3. Cari Tiket Berdasarkan Harga\n";
            cout << "4. Pesan Tiket\n";
            cout << "5. Hapus Tiket\n";
            cout << "6. Simpan Pesanan ke File\n";
            cout << "0. Keluar\n";
            cout << "Pilih: ";
            cin >> pilihan;

            switch (pilihan) {
                case 1: tambahTiket(); break;
                case 2: tampilkanTiket(); break;
                case 3: {
                    int harga;
                    cout << "Masukkan harga yang dicari: ";
                    cin >> harga;
                    cariTiketByHarga(harga);
                    break;
                }
                case 4: pesanTiket(); break;
                case 5: {
                    string kode;
                    cout << "Masukkan kode tiket yang ingin dihapus: ";
                    cin >> kode;
                    hapusTiket(kode);
                    break;
                }
                case 6: simpanPesananKeFile(); break;
                case 0: cout << "Keluar dari program.\n"; break;
                default: cout << "Pilihan tidak valid.\n";
            }
        } while (pilihan != 0);
    }
};

int main() {
    SistemTiketPesawat sistem;
    sistem.menu();
	return 0;
	}
