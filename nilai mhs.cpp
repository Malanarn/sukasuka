#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_SISWA = 100;
const int MAX_MAPEL = 5;

class Siswa {
public:
    string nama;
    float nilai[MAX_MAPEL];

    void input(int jumlahMapel, string namaMapel[]) {
        cout << "Nama siswa: ";
        cin.ignore();
        getline(cin, nama);

        for (int i = 0; i < jumlahMapel; i++) {
            cout << "Nilai " << namaMapel[i] << ": ";
            cin >> nilai[i];
        }
    }

    void tampil(int jumlahMapel, string namaMapel[]) {
        cout << nama << " : ";
        for (int i = 0; i < jumlahMapel; i++) {
            cout << namaMapel[i] << "=" << nilai[i];
            if (i < jumlahMapel - 1) cout << ", ";
        }
        cout << endl;
    }
};

class SistemNilai {
private:
    Siswa data[MAX_SISWA];
    int jumlahSiswa;
    int jumlahMapel;
    string namaMapel[MAX_MAPEL];

public:
    SistemNilai() {
        jumlahSiswa = 0;
        jumlahMapel = MAX_MAPEL;
        namaMapel[0] = "Matematika";
        namaMapel[1] = "Fisika";
        namaMapel[2] = "Kimia";
        namaMapel[3] = "Biologi";
        namaMapel[4] = "Bahasa";
    }

    void inputData() {
        cout << "Masukkan jumlah siswa: ";
        cin >> jumlahSiswa;

        for (int i = 0; i < jumlahSiswa; i++) {
            cout << "\nData siswa ke-" << i+1 << ":\n";
            data[i].input(jumlahMapel, namaMapel);
        }
    }

    void hitungStatistik() {
        cout << "\n--- Statistik Nilai Per Mata Pelajaran ---\n";
        for (int j = 0; j < jumlahMapel; j++) {
            float total = 0, max = -1, min = 101;
            for (int i = 0; i < jumlahSiswa; i++) {
                float nilai = data[i].nilai[j];
                total += nilai;
                if (nilai > max) max = nilai;
                if (nilai < min) min = nilai;
            }
            float rata = total / jumlahSiswa;
            cout << namaMapel[j] << " | Rata-rata: " << rata
                 << " | Tertinggi: " << max << " | Terendah: " << min << endl;
        }
    }

    void tampilHistogram() {
        cout << "\n--- Histogram Nilai Per Mata Pelajaran ---\n";
        for (int j = 0; j < jumlahMapel; j++) {
            int rentang[5] = {0}; // 0-59, 60-69, 70-79, 80-89, 90-100

            for (int i = 0; i < jumlahSiswa; i++) {
                float n = data[i].nilai[j];
                if (n < 60) rentang[0]++;
                else if (n < 70) rentang[1]++;
                else if (n < 80) rentang[2]++;
                else if (n < 90) rentang[3]++;
                else rentang[4]++;
            }

            cout << namaMapel[j] << ":\n";
            cout << "  0-59 : " << string(rentang[0], '*') << "\n";
            cout << " 60-69 : " << string(rentang[1], '*') << "\n";
            cout << " 70-79 : " << string(rentang[2], '*') << "\n";
            cout << " 80-89 : " << string(rentang[3], '*') << "\n";
            cout << "90-100 : " << string(rentang[4], '*') << "\n";
        }
    }

    void identifikasiNilaiEkstrem() {
        cout << "\n--- Siswa Terbaik & Terburuk Per Mata Pelajaran ---\n";
        for (int j = 0; j < jumlahMapel; j++) {
            float max = -1, min = 101;
            string siswaMax, siswaMin;

            for (int i = 0; i < jumlahSiswa; i++) {
                float nilai = data[i].nilai[j];
                if (nilai > max) {
                    max = nilai;
                    siswaMax = data[i].nama;
                }
                if (nilai < min) {
                    min = nilai;
                    siswaMin = data[i].nama;
                }
            }

            cout << namaMapel[j] << ":\n";
            cout << "  Tertinggi: " << siswaMax << " (" << max << ")\n";
            cout << "  Terendah : " << siswaMin << " (" << min << ")\n";
        }
    }

    void simpanLaporan() {
        ofstream file("laporan_nilai.txt");
        if (!file) {
            cout << "Gagal menyimpan file.\n";
            return;
        }

        file << "LAPORAN NILAI SISWA\n";
        file << "====================\n";

        for (int i = 0; i < jumlahSiswa; i++) {
            file << data[i].nama << " : ";
            for (int j = 0; j < jumlahMapel; j++) {
                file << namaMapel[j] << "=" << data[i].nilai[j];
                if (j < jumlahMapel - 1) file << ", ";
            }
            file << endl;
        }

        file.close();
        cout << "Laporan disimpan ke 'laporan_nilai.txt'\n";
    }
};

int main() {
    SistemNilai sistem;
    int pilihan;

    do {
        cout << "\n=== MENU SISTEM NILAI SISWA ===\n";
        cout << "1. Input Data Nilai\n";
        cout << "2. Statistik Nilai\n";
        cout << "3. Histogram Nilai\n";
        cout << "4. Identifikasi Nilai Ekstrem\n";
        cout << "5. Simpan Laporan ke File\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: sistem.inputData(); break;
            case 2: sistem.hitungStatistik(); break;
            case 3: sistem.tampilHistogram(); break;
            case 4: sistem.identifikasiNilaiEkstrem(); break;
            case 5: sistem.simpanLaporan(); break;
            case 0: cout << "Keluar dari program.\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 0);

    return 0;
}

