#include <iostream>
#include <limits>
using namespace std;

class KTP {
private:
    string nik, prov, kab, nama, tgl, jenis, alamat, kel, kec, agama, status, pekerjaan, kewarganegaraan;
    char gol;
    int rt, rw;
public:
    void tulisKTP() {
        cout << "Masukan NIK anda \t\t : ";
        cin >> nik;
        cin.ignore();
        cout << "Masukan Provinsi Anda \t\t : ";
        getline(cin, prov);
        cout << "Masukan Kabupaten/Kecamatan Anda : ";
        getline(cin, kab);
        cout << "Masukan Nama Anda \t\t : ";
        getline(cin, nama);
        cout << "Masukan Tempat/Tgl Lahir Anda \t : ";
        getline(cin, tgl);
        cout << "Masukan Jenis Kelamin Anda \t : ";
        getline(cin, jenis);
        cout << "Masukan Golongan Darah Anda \t : ";
        cin >> gol;
        cin.ignore();
        cout << "Masukan Alamat Anda \t\t : ";
        getline(cin, alamat);
        cout << "Masukan RT Anda \t\t : ";
        cin >> rt;
        cout << "Masukan RW Anda \t\t : ";
        cin >> rw;
        cin.ignore();
        cout << "Masukan Kelurahan/Desa Anda \t : ";
        getline(cin, kel);
        cout << "Masukan Kecamatan Anda \t\t : ";
        getline(cin, kec);
        cout << "Masukan Agama Anda \t\t : ";
        getline(cin, agama);
        cout << "Masukan Status Perkawinan Anda\t : ";
        getline(cin, status);
        cout << "Masukan Pekerjaan Anda \t\t : ";
        getline(cin, pekerjaan);
        cout << "Masukan Kewarganegaraan Anda\t : ";
        getline(cin, kewarganegaraan);
        cout << endl << endl;
}

    void tampilkanHasil() const {
        cout << "+=======================================================+\n";
        cout << "\t\t  PROVINSI " << prov << "\n";
        cout << "\t\t  KABUPATEN " << kab << "\n";
        cout << "+=======================================================+\n";
        cout << "NIK\t\t\t: " << nik << endl;
        cout << "Nama\t\t\t: " << nama << endl;
        cout << "Tempat/Tgl Lahir\t: " << tgl << endl;
        cout << "Jenis Kelamin\t\t: " << jenis << "\t Gol. Darah: " << gol << endl;
        cout << "Alamat\t\t\t: " << alamat << endl;
        cout << "\t RT/RW \t\t: " << rt << "/" << rw << endl;
        cout << "\t Kel/Desa \t: " << kel << endl;
        cout << "\t Kecamatan \t: " << kec << endl;
        cout << "Agama\t\t\t: " << agama << endl;
        cout << "Status Perkawinan\t: " << status << endl;
        cout << "Pekerjaan\t\t: " << pekerjaan << endl;
        cout << "Kewarganegaraan\t\t: " << kewarganegaraan << endl;
        cout << "Berlaku Hingga\t\t: SEUMUR HIDUP" << endl;
        cout << "+=======================================================+\n";
    }

    string getNama() const { return nama; }
    string getNIK() const { return nik; }

    void swap(KTP &other) {
        KTP temp = *this;
        *this = other;
        other = temp;
    }
};

// Bubble sort berdasarkan nama
void sortByName(KTP arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j].getNama() > arr[j + 1].getNama()) {
                arr[j].swap(arr[j + 1]);
            }
        }
    }
}

// Pencarian berdasarkan NIK
int cariByNIK(KTP arr[], int n, string targetNIK) {
    for (int i = 0; i < n; ++i) {
        if (arr[i].getNIK() == targetNIK) {
            return i;
        }
    }
    return -1;
}

int main() {
    const int MAX = 100;
    KTP data[MAX];
    int jumlah = 0;
    int pilihan;

    do {
    	cout << "======================================\n";
        cout << "|             MENU UTAMA             |\n";
        cout << "======================================\n";
        cout << "1. Tambah Data KTP\n";
        cout << "2. Cari Data KTP (berdasarkan NIK)\n";
        cout << "3. Tampilkan Semua Data (terurut nama)\n";
        cout << "4. Keluar\n";
        cout << "======================================\n";
        cout << "Pilih menu (1-4): ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
        case 1:
            if (jumlah < MAX) {
                cout << "\n[Tambah Data ke-" << jumlah + 1 << "]\n";
                data[jumlah].tulisKTP();
                jumlah++;
            } else {
                cout << "Kapasitas data sudah penuh!\n";
            }
            break;

        case 2: {
            string cariNIK;
            cout << "Masukkan NIK yang ingin dicari: ";
            getline(cin, cariNIK);
            int index = cariByNIK(data, jumlah, cariNIK);
            if (index != -1) {
                cout << "\nData ditemukan:\n";
                data[index].tampilkanHasil();
            } else {
                cout << "Data dengan NIK tersebut tidak ditemukan.\n";
            }
            break;
        }

        case 3:
            if (jumlah == 0) {
                cout << "Belum ada data yang dimasukkan.\n";
            } else {
                sortByName(data, jumlah);
                cout << "\n=== Data KTP Terurut Berdasarkan Nama ===\n";
                for (int i = 0; i < jumlah; ++i) {
                    data[i].tampilkanHasil();
                }
            }
            break;

        case 4:
            cout << "Terima kasih telah menggunakan program ini!\n";
            break;

        default:
            cout << "Pilihan tidak valid. Silakan pilih antara 1-4.\n";
        }

    } while (pilihan != 4);

    return 0;
}

