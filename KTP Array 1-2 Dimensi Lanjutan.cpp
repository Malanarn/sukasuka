#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const int JUMLAH_WILAYAH = 40;
string wilayah[JUMLAH_WILAYAH][2] = {
    {"Wirobrajan", "Yogyakarta"}, {"Mantrijeron", "Yogyakarta"},
    {"Kraton", "Yogyakarta"}, {"Gondomanan", "Yogyakarta"},
    {"Pakualaman", "Yogyakarta"}, {"Danurejan", "Yogyakarta"},
    {"Gedongtengen", "Yogyakarta"}, {"Jetis", "Yogyakarta"},
    {"Tegalrejo", "Yogyakarta"}, {"Umbulharjo", "Yogyakarta"},
    {"Kotagede", "Yogyakarta"}, {"Depok", "Sleman"},
    {"Ngaglik", "Sleman"}, {"Ngemplak", "Sleman"},
    {"Mlati", "Sleman"}, {"Gamping", "Sleman"},
    {"Godean", "Sleman"}, {"Seyegan", "Sleman"},
    {"Kalasan", "Sleman"}, {"Berbah", "Sleman"},
    {"Banguntapan", "Bantul"}, {"Pleret", "Bantul"},
    {"Jetis", "Bantul"}, {"Imogiri", "Bantul"},
    {"Pajangan", "Bantul"}, {"Pundong", "Bantul"},
    {"Kasihan", "Bantul"}, {"Srandakan", "Bantul"},
    {"Sanden", "Bantul"}, {"Bambanglipuro", "Bantul"},
    {"Kokap", "Kulon Progo"}, {"Wates", "Kulon Progo"},
    {"Sentolo", "Kulon Progo"}, {"Panjatan", "Kulon Progo"},
    {"Lendah", "Kulon Progo"}, {"Temon", "Kulon Progo"},
    {"Pengasih", "Kulon Progo"}, {"Galur", "Kulon Progo"},
    {"Playen", "Gunungkidul"}, {"Wonosari", "Gunungkidul"}
};

string formatTanggal(const string& input) {
    stringstream ss(input);
    string hariStr, bulanStr, tahunStr;
    ss >> hariStr >> bulanStr >> tahunStr;

    string bulanAngka;
    if (bulanStr == "Januari" || bulanStr == "januari" || bulanStr == "JANUARI") bulanAngka = "01";
    else if (bulanStr == "Februari" || bulanStr == "februari" || bulanStr == "FEBRUARI") bulanAngka = "02";
    else if (bulanStr == "Maret" || bulanStr == "maret" || bulanStr == "MARET") bulanAngka = "03";
    else if (bulanStr == "April" || bulanStr == "april" || bulanStr == "APRIL") bulanAngka = "04";
    else if (bulanStr == "Mei" || bulanStr == "mei" || bulanStr == "MEI") bulanAngka = "05";
    else if (bulanStr == "Juni" || bulanStr == "juni" || bulanStr == "JUNI") bulanAngka = "06";
    else if (bulanStr == "Juli" || bulanStr == "juli" || bulanStr == "JULI") bulanAngka = "07";
    else if (bulanStr == "Agustus" || bulanStr == "agustus" || bulanStr == "AGUSTUS") bulanAngka = "08";
    else if (bulanStr == "September" || bulanStr == "september" || bulanStr == "SEPTEMBER") bulanAngka = "09";
    else if (bulanStr == "Oktober" || bulanStr == "oktober" || bulanStr == "OKTOBER") bulanAngka = "10";
    else if (bulanStr == "November" || bulanStr == "november" || bulanStr == "NOVEMBER") bulanAngka = "11";
    else if (bulanStr == "Desember" || bulanStr == "desember" || bulanStr == "DESEMBER") bulanAngka = "12";
    else bulanAngka = "00";

    if (hariStr.length() == 1) hariStr = "0" + hariStr;
    return hariStr + "-" + bulanAngka + "-" + tahunStr;
}

class KTP {
public:
    char nik[20];
    string nama, tempat_lahir, tanggal_lahir, jenis_kelamin, gol_darah,
           alamat, rt_rw, kel_desa, kecamatan, agama,
           status_perkawinan, pekerjaan, kewarganegaraan, berlaku_hingga;
};

void pilihKelamin(string &kelamin) {
    int pilihan;
    cout << "1. Laki-Laki\n2. Perempuan\nPilih Jenis Kelamin: ";
    cin >> pilihan; cin.ignore();
    kelamin = (pilihan == 1) ? "Laki-laki" : (pilihan == 2) ? "Perempuan" : "Tidak Diketahui";
}

void pilihAgama(string &agama) {
    int pilihan;
    cout << "Pilih Agama:\n1. Islam\n2. Kristen\n3. Katolik\n4. Hindu\n5. Buddha\n6. Konghucu\nPilihan: ";
    cin >> pilihan; cin.ignore();
    switch (pilihan) {
        case 1: agama = "Islam"; break;
        case 2: agama = "Kristen"; break;
        case 3: agama = "Katolik"; break;
        case 4: agama = "Hindu"; break;
        case 5: agama = "Buddha"; break;
        case 6: agama = "Konghucu"; break;
        default: agama = "Tidak Diketahui"; break;
    }
}

void inputKTP(KTP &ktp) {
    cout << "Masukkan NIK: "; cin >> ktp.nik; cin.ignore();
    cout << "Masukkan Nama: "; getline(cin, ktp.nama);
    cout << "Masukkan Tempat Lahir: "; getline(cin, ktp.tempat_lahir);
    string tanggal_input;
    cout << "Masukkan Tanggal Lahir (contoh: 7 Juni 2002): "; getline(cin, tanggal_input);
    ktp.tanggal_lahir = formatTanggal(tanggal_input);
    pilihKelamin(ktp.jenis_kelamin);
    cout << "Masukkan Golongan Darah (A/B/AB/O): "; cin >> ktp.gol_darah; cin.ignore();
    cout << "Masukkan Alamat: "; getline(cin, ktp.alamat);
    cout << "Masukkan RT/RW: "; getline(cin, ktp.rt_rw);
    cout << "Pilih Wilayah:\n";
    for (int i = 0; i < JUMLAH_WILAYAH; ++i) {
        cout << i + 1 << ". " << wilayah[i][0] << " / " << wilayah[i][1] << endl;
    }
    int pilihanWilayah;
    cout << "Pilihan Anda: "; cin >> pilihanWilayah; cin.ignore();
    if (pilihanWilayah >= 1 && pilihanWilayah <= JUMLAH_WILAYAH) {
        ktp.kel_desa = wilayah[pilihanWilayah - 1][0];
        ktp.kecamatan = wilayah[pilihanWilayah - 1][1];
    } else {
        ktp.kel_desa = "Tidak Diketahui";
        ktp.kecamatan = "Tidak Diketahui";
    }
    pilihAgama(ktp.agama);
    cout << "Masukkan Status Perkawinan: "; getline(cin, ktp.status_perkawinan);
    cout << "Masukkan Pekerjaan: "; getline(cin, ktp.pekerjaan);
    cout << "Masukkan Kewarganegaraan: "; getline(cin, ktp.kewarganegaraan);
    cout << "Masukkan Berlaku Hingga: "; getline(cin, ktp.berlaku_hingga);
}

void tampilKTP(const KTP &ktp) {
    cout << "\n========== DATA KTP ==========\n";
    cout << "NIK                 : " << ktp.nik << endl;
    cout << "Nama                : " << ktp.nama << endl;
    cout << "Tempat/Tgl Lahir    : " << ktp.tempat_lahir << ", " << ktp.tanggal_lahir << endl;
    cout << "Jenis Kelamin       : " << ktp.jenis_kelamin << "   Gol Darah: " << ktp.gol_darah << endl;
    cout << "Alamat              : " << ktp.alamat << endl;
    cout << "RT/RW               : " << ktp.rt_rw << endl;
    cout << "Kelurahan/Desa      : " << ktp.kel_desa << endl;
    cout << "Kecamatan           : " << ktp.kecamatan << endl;
    cout << "Agama               : " << ktp.agama << endl;
    cout << "Status Perkawinan   : " << ktp.status_perkawinan << endl;
    cout << "Pekerjaan           : " << ktp.pekerjaan << endl;
    cout << "Kewarganegaraan     : " << ktp.kewarganegaraan << endl;
    cout << "Berlaku Hingga      : " << ktp.berlaku_hingga << endl;
    cout << "==============================\n";
}

void tampilkanSemuaData(KTP data[], int jumlah) {
    for (int i = 0; i < jumlah; ++i) {
        tampilKTP(data[i]);
    }
}

void tampilkanPerWilayah(KTP data[], int jumlah) {
    cout << "\n=========== DAFTAR WILAYAH ===========\n";
    for (int i = 0; i < JUMLAH_WILAYAH; ++i) {
        cout << i + 1 << ". " << wilayah[i][0] << " / " << wilayah[i][1] << endl;
    }

    int pilihanWilayah;
    cout << "Masukkan nomor wilayah yang ingin ditampilkan: ";
    cin >> pilihanWilayah; cin.ignore();

    if (pilihanWilayah < 1 || pilihanWilayah > JUMLAH_WILAYAH) {
        cout << "Nomor wilayah tidak valid.\n";
        return;
    }

    string kelurahan = wilayah[pilihanWilayah - 1][0];
    string kecamatan = wilayah[pilihanWilayah - 1][1];
    bool ada = false;

    cout << "\nMenampilkan data untuk wilayah: " << kelurahan << " / " << kecamatan << endl;
    for (int i = 0; i < jumlah; ++i) {
        if (data[i].kel_desa == kelurahan && data[i].kecamatan == kecamatan) {
            tampilKTP(data[i]);
            ada = true;
        }
    }

    if (!ada) {
        cout << "Tidak ada data penduduk pada wilayah ini.\n";
    }
}

void cariByNIK(KTP data[], int jumlah, const string& target) {
    for (int i = 0; i < jumlah; ++i) {
        if (data[i].nik == target) {
            tampilKTP(data[i]);
            return;
        }
    }
    cout << "Data dengan NIK tersebut tidak ditemukan.\n";
}

void cariByNama(KTP data[], int jumlah, const string& nama) {
    bool ditemukan = false;
    for (int i = 0; i < jumlah; ++i) {
        if (data[i].nama.find(nama) != string::npos) {
            tampilKTP(data[i]);
            ditemukan = true;
        }
    }
    if (!ditemukan) cout << "Data dengan nama tersebut tidak ditemukan.\n";
}

void bubbleSortByNama(KTP data[], int jumlah, bool ascending) {
    for (int i = 0; i < jumlah - 1; ++i) {
        for (int j = 0; j < jumlah - i - 1; ++j) {
            if ((ascending && data[j].nama > data[j + 1].nama) ||
                (!ascending && data[j].nama < data[j + 1].nama)) {
                swap(data[j], data[j + 1]);
            }
        }
    }
}

void bubbleSortByNIK(KTP data[], int jumlah, bool ascending) {
    for (int i = 0; i < jumlah - 1; ++i) {
        for (int j = 0; j < jumlah - i - 1; ++j) {
            if ((ascending && string(data[j].nik) > string(data[j + 1].nik)) ||
                (!ascending && string(data[j].nik) < string(data[j + 1].nik))) {
                swap(data[j], data[j + 1]);
            }
        }
    }
}

int main() {
    int jumlah;
    cout << "Berapa banyak data KTP jumlah penduduk yang ingin Anda inputkan? ";
    cin >> jumlah; cin.ignore();

    KTP data[100];
    for (int i = 0; i < jumlah; ++i) {
        cout << "\nInput Data ke-" << i + 1 << ":\n";
        inputKTP(data[i]);
    }

    int pilihan;
    do {
        cout << "\n============== MENU ==============\n";
        cout << "1. Tampilkan Semua Data\n";
        cout << "2. Tampilkan Data per Wilayah\n";
        cout << "3. Cari Berdasarkan NIK\n";
        cout << "4. Cari Berdasarkan Nama\n";
        cout << "5. Urutkan Berdasarkan NIK\n";
        cout << "6. Urutkan Berdasarkan Nama\n";
        cout << "0. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan; cin.ignore();

        if (pilihan == 1) {
            tampilkanSemuaData(data, jumlah);
        } else if (pilihan == 2) {
            tampilkanPerWilayah(data, jumlah);
        } else if (pilihan == 3) {
            string nik;
            cout << "Masukkan NIK: ";
            getline(cin, nik);
            cariByNIK(data, jumlah, nik);
        } else if (pilihan == 4) {
            string nama;
            cout << "Masukkan Nama: ";
            getline(cin, nama);
            cariByNama(data, jumlah, nama);
        } else if (pilihan == 5 || pilihan == 6) {
            int urutan;
            cout << "Pilih urutan:\n1. Ascending\n2. Descending\nPilihan: ";
            cin >> urutan; cin.ignore();
            bool ascending = (urutan == 1);
            if (pilihan == 5) {
            	bubbleSortByNIK(data, jumlah, ascending);
                cout << "Data diurutkan berdasarkan NIK.\n";
            } else if (pilihan == 6) {
                bubbleSortByNama(data, jumlah, ascending);
                cout << "Data diurutkan berdasarkan nama.\n";
            }
        } else if (pilihan == 0) {
            cout << "Keluar dari program.\n";
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    return 0;
}

