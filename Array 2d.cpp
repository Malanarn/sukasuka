#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const int JUMLAH_WILAYAH = 20;
string wilayah[JUMLAH_WILAYAH][2] = {
    {"Pleret", "Pleret"},
    {"Wonokromo", "Pleret"},
    {"Timbulharjo", "Sewon"},
    {"Panjangrejo", "Pundong"},
    {"Bangunjiwo", "Kasihan"},
    {"Ngestiharjo", "Kasihan"},
    {"Gilangharjo", "Pandak"},
    {"Wijirejo", "Pandak"},
    {"Sumbermulyo", "Bambanglipuro"},
    {"Sidomulyo", "Bambanglipuro"},
    {"Srihardono", "Pundong"},
    {"Murtigading", "Sanden"},
    {"Trimurti", "Srandakan"},
    {"Poncosari", "Srandakan"},
    {"Guwosari", "Pajangan"},
    {"Sendangsari", "Pajangan"},
    {"Seloharjo", "Pundong"},
    {"Sriharjo", "Imogiri"},
    {"Karangtalun", "Imogiri"},
    {"Wukirsari", "Imogiri"}
};

class KTP {
public:
    char nik[20];
    string nama;
    string tempat_lahir;
    string tanggal_lahir;
    string jenis_kelamin;
    string gol_darah;
    string alamat;
    string rt_rw;
    string kel_desa;
    string kecamatan;
    string agama;
    string status_perkawinan;
    string pekerjaan;
    string kewarganegaraan;
    string berlaku_hingga;
};

class KTPSorter {
public:
    static void sortByName(KTP data[], int jumlah) {
        for (int i = 0; i < jumlah - 1; ++i) {
            for (int j = 0; j < jumlah - i - 1; ++j) {
                if (data[j].nama > data[j + 1].nama) {
                    swap(data[j], data[j + 1]);
                }
            }
        }
    }

    static void sortByTanggalLahir(KTP data[], int jumlah) {
        for (int i = 0; i < jumlah - 1; ++i) {
            for (int j = 0; j < jumlah - i - 1; ++j) {
                if (data[j].tanggal_lahir > data[j + 1].tanggal_lahir) {
                    swap(data[j], data[j + 1]);
                }
            }
        }
    }
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

void pilihKelamin(string &kelamin) {
    int pilihan;
    cout << "1. Laki-Laki\n2. Perempuan\nPilih Jenis Kelamin: ";
    cin >> pilihan;
    cin.ignore();

    kelamin = (pilihan == 1) ? "Laki-laki" : (pilihan == 2) ? "Perempuan" : "Tidak Diketahui";
}

void pilihAgama(string &agama) {
    int pilihan;
    cout << "Pilih Agama:\n1. Islam\n2. Kristen\n3. Katolik\n4. Hindu\n5. Buddha\n6. Konghucu\nPilihan: ";
    cin >> pilihan;
    cin.ignore();

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
    cout << "Masukkan NIK: "; 
	cin >> ktp.nik; cin.ignore();
    cout << "Masukkan Nama: "; 
	getline(cin, ktp.nama);
    cout << "Masukkan Tempat Lahir: "; 
	getline(cin, ktp.tempat_lahir);
	
    string tanggal_input;
    cout << "Masukkan Tanggal Lahir (contoh: 7 Juni 2002): ";
    getline(cin, tanggal_input);
    ktp.tanggal_lahir = formatTanggal(tanggal_input);
    pilihKelamin(ktp.jenis_kelamin);
    cout << "Masukkan Golongan Darah (A/B/AB/O): "; 
	cin >> ktp.gol_darah; cin.ignore();
    cout << "Masukkan Alamat: "; 
	getline(cin, ktp.alamat);
    cout << "Masukkan RT/RW: "; 
	getline(cin, ktp.rt_rw);
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
    cout << "Masukkan Status Perkawinan: "; 
	getline(cin, ktp.status_perkawinan);
    cout << "Masukkan Pekerjaan: "; 
	getline(cin, ktp.pekerjaan);
    cout << "Masukkan Kewarganegaraan: "; 
	getline(cin, ktp.kewarganegaraan);
    cout << "Masukkan Berlaku Hingga: "; 
	getline(cin, ktp.berlaku_hingga);
}

void displayKTP(const KTP &ktp) {
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

void cariKTP(KTP data[], int jumlah) {
    char cari_nik[20];
    cout << "Masukkan NIK yang dicari: ";
    cin >> cari_nik;
    for (int i = 0; i < jumlah; ++i) {
        if (string(data[i].nik) == string(cari_nik)) {
            displayKTP(data[i]);
            return;
        }
    }
    cout << "Data tidak ditemukan.\n";
}

void cariNama(KTP data[], int jumlah) {
    string nama;
    cout << "Masukkan Nama yang dicari: ";
    cin.ignore();
    getline(cin, nama);
    bool ditemukan = false;
    for (int i = 0; i < jumlah; ++i) {
        if (data[i].nama.find(nama) != string::npos) {
            displayKTP(data[i]);
            ditemukan = true;
        }
    }
    if (!ditemukan) cout << "Data tidak ditemukan.\n";
}

int main() {
    int jumlah;
    cout << "Berapa banyak data KTP jumlah penduduk yang ingin Anda inputkan? ";
    cin >> jumlah;
    cin.ignore();

    KTP daftarKTP[100];

    for (int i = 0; i < jumlah; ++i) {
        cout << "\n=== Input Data KTP ke-" << i + 1 << " ===\n";
        inputKTP(daftarKTP[i]);
    }

    int pilihan;
    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Tampilkan Semua Data\n";
        cout << "2. Cari Berdasarkan NIK\n";
        cout << "3. Cari Berdasarkan Nama\n";
        cout << "4. Urutkan Berdasarkan Nama\n";
        cout << "5. Urutkan Berdasarkan Tanggal Lahir\n";
        cout << "0. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                for (int i = 0; i < jumlah; ++i) displayKTP(daftarKTP[i]);
                break;
            case 2:
                cariKTP(daftarKTP, jumlah);
                break;
            case 3:
                cariNama(daftarKTP, jumlah);
                break;
            case 4:
                KTPSorter::sortByName(daftarKTP, jumlah);
                cout << "Data telah diurutkan berdasarkan nama.\n";
                break;
            case 5:
                KTPSorter::sortByTanggalLahir(daftarKTP, jumlah);
                cout << "Data telah diurutkan berdasarkan tanggal lahir.\n";
                break;
            case 0:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                break;
        }
    } while (pilihan != 0);

    return 0;
}
