#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class MataKuliah {
public:
    string kode;
    string nama;
    int sks;
    float nilai;

    void input() {
        cout << "Kode Mata Kuliah: ";
        cin >> kode;
        cout << "Nama Mata Kuliah: ";
        cin.ignore(); getline(cin, nama);
        cout << "SKS: ";
        cin >> sks;
        cout << "Nilai: ";
        cin >> nilai;
    }

    void tampil() {
        cout << kode << " | " << nama << " | " << sks << " SKS | Nilai: " << nilai << endl;
    }
};

class PortalMahasiswa {
private:
    MataKuliah matkul[50]; // Maksimal 50 mata kuliah
    int jumlah;            // Banyak matkul yang didaftarkan
    const int biayaPerSKS = 150000;

public:
    PortalMahasiswa() {
        jumlah = 0;
    }

    void daftarMatkul() {
        if (jumlah >= 50) {
            cout << "Kapasitas mata kuliah penuh.\n";
            return;
        }
        cout << "\nMasukkan data mata kuliah ke-" << (jumlah + 1) << ":\n";
        matkul[jumlah].input();
        jumlah++;
    }

    void hitungSPP() {
        int totalSKS = 0;
        for (int i = 0; i < jumlah; i++)
            totalSKS += matkul[i].sks;

        int totalBiaya = totalSKS * biayaPerSKS;
        cout << "Total SKS: " << totalSKS << endl;
        cout << "Total SPP: Rp " << totalBiaya << endl;
    }

    void sortNilai(bool ascending) {
        for (int i = 0; i < jumlah - 1; i++) {
            for (int j = 0; j < jumlah - i - 1; j++) {
                if ((ascending && matkul[j].nilai > matkul[j + 1].nilai) ||
                    (!ascending && matkul[j].nilai < matkul[j + 1].nilai)) {
                    MataKuliah temp = matkul[j];
                    matkul[j] = matkul[j + 1];
                    matkul[j + 1] = temp;
                }
            }
        }

        cout << "\nHasil sorting nilai:\n";
        for (int i = 0; i < jumlah; i++) {
            matkul[i].tampil();
        }
    }

    void cariMatkul(const string& keyword) {
        bool ditemukan = false;
        for (int i = 0; i < jumlah; i++) {
            if (matkul[i].nama.find(keyword) != string::npos || matkul[i].kode == keyword) {
                matkul[i].tampil();
                ditemukan = true;
            }
        }
        if (!ditemukan)
            cout << "Mata kuliah tidak ditemukan.\n";
    }

    void simpanKRSKeFile() {
        ofstream file("KRS.txt");
        if (!file) {
            cout << "Gagal membuka file untuk disimpan.\n";
            return;
        }
        for (int i = 0; i < jumlah; i++) {
            file << matkul[i].kode << "," << matkul[i].nama << "," << matkul[i].sks << "," << matkul[i].nilai << endl;
        }
        file.close();
        cout << "KRS berhasil disimpan ke KRS.txt\n";
    }

    void bacaKRSdariFile() {
        ifstream file("KRS.txt");
        if (!file) {
            cout << "File KRS.txt tidak ditemukan.\n";
            return;
        }

        string kode, nama;
        int sks;
        float nilai;

        cout << "\nIsi file KRS.txt:\n";
        while (getline(file, kode, ',')) {
            getline(file, nama, ',');
            file >> sks;
            file.ignore(1); // skip comma
            file >> nilai;
            file.ignore(1); // skip newline

            cout << kode << " | " << nama << " | " << sks << " SKS | Nilai: " << nilai << endl;
        }
        file.close();
    }
};

int main() {
    PortalMahasiswa portal;
    int pilihan;
    string cari;

    do {
        cout << "\n=== MENU PORTAL MAHASISWA ===\n";
        cout << "1. Daftar Mata Kuliah\n";
        cout << "2. Hitung SPP\n";
        cout << "3. Cek Nilai (Sorting)\n";
        cout << "4. Cari Mata Kuliah\n";
        cout << "5. Simpan KRS ke File\n";
        cout << "6. Baca KRS dari File\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            portal.daftarMatkul();
            break;
        case 2:
            portal.hitungSPP();
            break;
        case 3:
            int urut;
            cout << "Urutkan nilai (1: kecil ke besar, 2: besar ke kecil): ";
            cin >> urut;
            portal.sortNilai(urut == 1);
            break;
        case 4:
            cout << "Masukkan nama/kode matkul: ";
            cin.ignore();
            getline(cin, cari);
            portal.cariMatkul(cari);
            break;
        case 5:
            portal.simpanKRSKeFile();
            break;
        case 6:
            portal.bacaKRSdariFile();
            break;
        case 0:
            cout << "Keluar dari program.\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    return 0;
}
