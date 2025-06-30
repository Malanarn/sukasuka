#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

using namespace std;

// Class Pasien menu utama dengan login dan daftar pasien baru

class Pasien {
public:
  string nama, idPasien, jenisKelamin, alamat, password;
  int umur;

  void tampilkan();
  void simpanKeFile();
  static string buatIDBaru();
  static bool loginPasien(const string &idInput, const string &passInput, Pasien &hasil);
  static void tampilkanSemua();
  static void editPasien(const string &idEdit);
  static void hapusPasien(const string &idHapus);
  static void cariPasien();
  static void urutkanPasien(int mode, bool ascending);
};

void Pasien::tampilkan() {
  cout << "Nama          : " << nama << endl;
  cout << "ID Pasien     : " << idPasien << endl;
  cout << "Umur          : " << umur << endl;
  cout << "Jenis Kelamin : " << jenisKelamin << endl;
  cout << "Alamat        : " << alamat << endl;
}

void Pasien::simpanKeFile() {
  ofstream file("pasien.txt", ios::app);
  file << nama << ";" << idPasien << ";" << umur << ";" << jenisKelamin << ";"
       << alamat << ";" << password << "\n";
  file.close();
}

string Pasien::buatIDBaru() {
  ifstream file("pasien.txt");
  string baris, idTerakhir = "RM0000";

  while (getline(file, baris)) {
    stringstream ss(baris);
    string tempNama, tempId;
    getline(ss, tempNama, ';');
    getline(ss, tempId, ';');
    idTerakhir = tempId;
  }
  file.close();

  int nomor = 0;
  if (idTerakhir.size() >= 2) {
    string angkaStr = idTerakhir.substr(2);
    stringstream(angkaStr) >> nomor;
  }
  nomor++;

  stringstream ss;
  ss << "RM" << setfill('0') << setw(4) << nomor;
  return ss.str();
}

bool Pasien::loginPasien(const string &idInput, const string &passInput, Pasien &hasil) {
  ifstream file("pasien.txt");
  string baris;
  while (getline(file, baris)) {
    stringstream ss(baris);
    string umurStr;
    getline(ss, hasil.nama, ';');
    getline(ss, hasil.idPasien, ';');
    getline(ss, umurStr, ';');
    stringstream(umurStr) >> hasil.umur;
    getline(ss, hasil.jenisKelamin, ';');
    getline(ss, hasil.alamat, ';');
    getline(ss, hasil.password, ';');
    if (hasil.idPasien == idInput && hasil.password == passInput) {
      return true;
    }
  }
  return false;
}

void Pasien::tampilkanSemua() {
  ifstream file("pasien.txt");
  string baris;
  int no = 1;
  while (getline(file, baris)) {
    stringstream ss(baris);
    Pasien p;
    string umurStr;
    getline(ss, p.nama, ';');
    getline(ss, p.idPasien, ';');
    getline(ss, umurStr, ';');
    stringstream(umurStr) >> p.umur;
    getline(ss, p.jenisKelamin, ';');
    getline(ss, p.alamat, ';');
    getline(ss, p.password, ';');

    cout << "\nPasien ke- " << no++ << " : \n";
    p.tampilkan();
  }
}

void Pasien::editPasien(const string &idEdit) {
  ifstream file("pasien.txt");
  ofstream temp("temp.txt");
  string baris;

  bool ditemukan = false;

  while (getline(file, baris)) {
    stringstream ss(baris);
    Pasien p;
    string umurStr;
    getline(ss, p.nama, ';');
    getline(ss, p.idPasien, ';');
    getline(ss, umurStr, ';');
    stringstream(umurStr) >> p.umur;
    getline(ss, p.jenisKelamin, ';');
    getline(ss, p.alamat, ';');
    getline(ss, p.password, ';');

    if (p.idPasien == idEdit) {
      ditemukan = true;
      cout << "---------Data baru untuk ID " << idEdit << "----------\n";
      cout << "Nama          : ";
      getline(cin, p.nama);
      cout << "Umur          : ";
      cin >> p.umur;
      cin.ignore();
      cout << "Jenis Kelamin : ";
      getline(cin, p.jenisKelamin);
      cout << "Alamat        : ";
      getline(cin, p.alamat);
      cout << "Password      : ";
      getline(cin, p.password);
    }

    temp << p.nama << ";" << p.idPasien << ";" << p.umur << ";"
         << p.jenisKelamin << ";" << p.alamat << ";" << p.password << "\n";
  }
  file.close();
  temp.close();
  remove("pasien.txt");
  rename("temp.txt", "pasien.txt");

  if (ditemukan)
    cout << "Data berhasil diedit.\n";
  else
    cout << "ID tidak ditemukan.\n";
}

void Pasien::hapusPasien(const string &idHapus) {
  ifstream file("pasien.txt");
  ofstream temp("temp.txt");
  string baris;

  bool ditemukan = false;

  while (getline(file, baris)) {
    stringstream ss(baris);
    string nama, idPasien;
    getline(ss, nama, ';');
    getline(ss, idPasien, ';');
    if (idPasien == idHapus) {
      ditemukan = true;
      continue;
    }
    temp << baris << "\n";
  }
  file.close();
  temp.close();
  remove("pasien.txt");
  rename("temp.txt", "pasien.txt");

  if (ditemukan)
    cout << "Pasien berhasil dihapus.\n";
  else
    cout << "ID tidak ditemukan.\n";
}

void Pasien::cariPasien() {
  Pasien data[100];
  int jumlah = 0;
  ifstream file("pasien.txt");
  string baris;

  while (getline(file, baris) && jumlah < 100) {
    stringstream ss(baris);
    string umurStr;
    getline(ss, data[jumlah].nama, ';');
    getline(ss, data[jumlah].idPasien, ';');
    getline(ss, umurStr, ';');
    stringstream(umurStr) >> data[jumlah].umur;
    getline(ss, data[jumlah].jenisKelamin, ';');
    getline(ss, data[jumlah].alamat, ';');
    getline(ss, data[jumlah].password, ';');
    jumlah++;
  }
  file.close();

  int cari;
  cout << "\n=== MENU PENCARIAN PASIEN ===\n";
  cout << "1. Cari Berdasarkan ID Pasien\n";
  cout << "2. Cari Berdasarkan Nama Pasien\n";
  cout << "3. Cari Berdasarkan Umur Pasien\n";
  cout << "Masukkan Pilihan : ";
  cin >> cari;
  cin.ignore();

  bool ditemukan = false;

  if (cari == 1) {
    string cariID;
    cout << "\nMasukkan ID pasien (contohnya RM0001): ";
    getline(cin, cariID);
    for (int i = 0; i < jumlah; i++) {
      if (data[i].idPasien == cariID) {
        cout << "\nData Pasien ditemukan:\n";
        data[i].tampilkan();
        ditemukan = true;
      }
    }
  } else if (cari == 2) {
    string cariNama;
    cout << "\nMasukkan nama pasien (boleh sebagian): ";
    getline(cin, cariNama);
    for (int i = 0; i < jumlah; i++) {
      if (data[i].nama.find(cariNama) != string::npos) {
        cout << "\n Data Pasien ditemukan:\n";
        data[i].tampilkan();
        ditemukan = true; 
      }
    }
  } else if (cari == 3) {
    int cariUmur;
    cout << "Masukkan umur pasien: ";
    cin >> cariUmur;
    for (int i = 0; i < jumlah; i++) {
      if (data[i].umur == cariUmur) {
        cout << "\nData Pasien ditemukan:\n";
        data[i].tampilkan();
        ditemukan = true;
      }
    }
  } else {
    cout << "Pilihan tidak valid.\n";
    return;
  }

  if (!ditemukan)
    cout << "Data pasien tidak ditemukan.\n";
}

void Pasien::urutkanPasien(int urut, bool ascending) {
  Pasien data[100];
  int jumlah = 0;

  ifstream file("pasien.txt");
  string baris;
  while (getline(file, baris) && jumlah < 100) {
    stringstream ss(baris);
    string umurStr;
    getline(ss, data[jumlah].nama, ';');
    getline(ss, data[jumlah].idPasien, ';');
    getline(ss, umurStr, ';');
    stringstream(umurStr) >> data[jumlah].umur;
    getline(ss, data[jumlah].jenisKelamin, ';');
    getline(ss, data[jumlah].alamat, ';');
    getline(ss, data[jumlah].password, ';');
    jumlah++;
  }
  file.close();

  for (int i = 0; i < jumlah - 1; i++) {
    for (int j = 0; j < jumlah - 1 - i; j++) {

      bool tukar = false;

      if (urut == 1) { // ID Pasien
        if ((ascending && data[j].idPasien > data[j + 1].idPasien) ||
            (!ascending && data[j].idPasien < data[j + 1].idPasien)) {
          tukar = true;
        }
      } else if (urut == 2) { // Nama Pasien
        if ((ascending && data[j].nama > data[j + 1].nama) ||
            (!ascending && data[j].nama < data[j + 1].nama)) {
          tukar = true;
        }
      } else if (urut == 3) { // Umur
        if ((ascending && data[j].umur > data[j + 1].umur) ||
            (!ascending && data[j].umur < data[j + 1].umur)) {
          tukar = true;
        }
      }

      if (tukar) {
        Pasien temp = data[j];
        data[j] = data[j + 1];
        data[j + 1] = temp;
      }
    }
  }

  cout << "\nData setelah diurutkan : \n";
  for (int i = 0; i < jumlah; i++) {
    cout << "\nPasien ke-" << i + 1 << ":\n";
    data[i].tampilkan();
  }
}

// Menu Admin
bool loginAdmin(const string &user, const string &pass) {
  return user == "admin" && pass == "admin123";
}

void menuAdmin() {
  string user, pass;
  cout << "Username : ";
  getline(cin, user);
  cout << "Password : ";
  getline(cin, pass);
  if (loginAdmin(user, pass)) {
    cout << "\nLogin admin berhasil.\n";

    int menu;
    do {
      cout << "\n===========================================\n";
      cout << "                   MENU ADMIN                \n";
      cout << "=============================================\n";
      cout << "1. Tambah Pasien\n";
      cout << "2. Tampilkan Semua\n";
      cout << "3. Edit Pasien\n";
      cout << "4. Hapus Pasien\n";
      cout << "5. Cari Pasien\n";
      cout << "6. Urutkan Data Pasien\n";
      cout << "7. Logout\n";
      cout << "\n===========================================\n";
      cout << "Pilih: ";
      cin >> menu;
      cin.ignore();

      switch (menu) {
      case 1: {
        Pasien p;
        cout << "Nama          : ";
        getline(cin, p.nama);
        p.idPasien = Pasien::buatIDBaru();
        cout << "Umur          : ";
        cin >> p.umur;
        cin.ignore();
        cout << "Jenis Kelamin : ";
        getline(cin, p.jenisKelamin);
        cout << "Alamat        : ";
        getline(cin, p.alamat);
        cout << "Password      : ";
        getline(cin, p.password);
        p.simpanKeFile();
        cout << "Data berhasil disimpan dengan ID : " << p.idPasien << "\n";
        break;
      }
      case 2:
        Pasien::tampilkanSemua();
        break;
      case 3: {
        string id;
        cout << "Masukkan ID pasien: ";
        getline(cin, id);
        Pasien::editPasien(id);
        break;
      }
      case 4: {
        string id;
        cout << "Masukkan ID pasien: ";
        getline(cin, id);
        Pasien::hapusPasien(id);
        break;
      }
      case 5: {
        Pasien::cariPasien();
        break;
      }
      case 6: {
        char ulangi;
        do {
        int kriteria, urutan;
      	
		cout << "\n===========================================\n";
        cout << "           MENU SORTING DATA PASIEN               \n";
        cout << "=============================================\n";
        cout << "Urutkan Data Pasien berdasarkan \n";
        cout << "1. ID Pasien\n";
        cout << "2. Nama Pasien\n";
        cout << "3. Umur Pasien\n";
        cout << "Masukkan Pilihan Anda : ";
        cin >> kriteria;
		cout << "=============================================\n";
        cout << "Urutakan secara : \n";
        cout << "1. Ascending\n";
        cout << "2. Descending\n";
        cout << "Masukkan Pilihan Anda : ";
        cin >> urutan;
        cin.ignore();

        bool ascending = (urutan == 1);

        // Penjelasan tambahan berdasarkan pilihan
        cout << "\nPenjelasan Urutan:\n";
          if (kriteria == 1) {
            cout << "Anda memilih urut berdasarkan ID Pasien.\n";
            if (ascending)
              cout << "Urutannya dari ID terkecil (RM0001) ke terbesar "
                      "(RM9999).\n";
            else
              cout << "Urutannya dari ID terbesar (RM9999) ke terkecil "
                      "(RM0001).\n";
          } else if (kriteria == 2) {
            cout << "Anda memilih urut berdasarkan Nama Pasien.\n";
            if (ascending)
              cout << "Urutannya dari A ke Z (alfabet naik).\n";
            else
              cout << "Urutannya dari Z ke A (alfabet turun).\n";
          } else if (kriteria == 3) {
            cout << "Anda memilih urut berdasarkan Umur Pasien.\n";
            if (ascending)
              cout << "Urutannya dari umur termuda ke tertua.\n";
            else
              cout << "Urutannya dari umur tertua ke termuda.\n";
          } else {
            cout << "Pilihan tidak valid. Kembali ke menu.\n";
            break;
          }

          // Proses Pengurutan
          Pasien::urutkanPasien(kriteria, ascending);

          cout << "\nIngin mengurutkan lagi? (y/n): ";
          cin >> ulangi;
          cin.ignore();

        } while (ulangi == 'y' || ulangi == 'Y');
        break;
      }

      default:
        if (menu != 7)
          cout << "Pilihan tidak valid.\n";
      }
    } while (menu != 7);

  } else {
    cout << "Login gagal.\n";
  }
}

// Class IGD
class PasienIGD {
private:
  string nama;
  string alamat;
  string keluhan;
  string idPasien;
  string jenisKelamin;
  string tingkatKedaruratan;
  string dokterMenangani;
  int umur;

public:
  void setDataDariPasien(const Pasien &p);
  string getidPasien();
  string getNama();
  void setIDPasien(const string &id);
  void inputTambahanIGD();
  void inputData();
  void tampilkanData();
  void simpanKeFile(ofstream &file);
};

const int MAX_PASIEN = 100;
const int JUMLAH_DOKTER = 5;

string daftarDokter[JUMLAH_DOKTER] = {
    "dr. Devalya Lameysha Manurung, Sp.EM","dr. Ega Ardiyanti, Sp.BTKV",
    "dr. Armondha Ayesha Shakila, Sp.JP", "dr. Lestari Dewi, Sp.EM",
    "dr. Bagas Wicaksono, Sp.EM"};

void PasienIGD::setDataDariPasien(const Pasien &p) {
  nama = p.nama;
  idPasien = p.idPasien;
  jenisKelamin = p.jenisKelamin;
  alamat = p.alamat;
  umur = p.umur;
}

void PasienIGD::setIDPasien(const string &id) {
  idPasien = id;
}

void PasienIGD::inputData() {
  cout << "\nMasukkan ID Pasien     : ";
  getline(cin, idPasien);
  cout << "Masukkan Nama Pasien     : ";
  getline(cin, nama);
  cout << "Masukkan Umur            : ";
  cin >> umur;
  cin.ignore();
  cout << "Masukkan Alamat          : ";
  getline(cin, alamat);
  cout << "Masukkan Keluhan         : ";
  getline(cin, keluhan);

  // Pilih tingkat kedaruratan
  int pilihKedaruratan;
  bool inputValid = false;

  do {
    cout << "\n===========================================\n";
    cout << "Pilih Tingkat Kedaruratan:\n";
    cout << "1. Ringan\n";
    cout << "2. Sedang\n";
    cout << "3. Berat\n";
    cout << "Masukkan pilihan (1-3): ";
    cin >> pilihKedaruratan;
    cin.ignore();

    switch (pilihKedaruratan) {
    case 1:
      tingkatKedaruratan = "Ringan";
      inputValid = true;
      break;
    case 2:
      tingkatKedaruratan = "Sedang";
      inputValid = true;
      break;
    case 3:
      tingkatKedaruratan = "Berat";
      inputValid = true;
      break;
    default:
      cout << "Pilihan tidak valid. Silakan masukkan angka 1-3.\n";
    }
  } while (!inputValid);

  // Pilih dokter
  cout << "\nPilih Dokter yang Menangani:\n";
  for (int i = 0; i < JUMLAH_DOKTER; i++) {
    cout << i + 1 << ". " << daftarDokter[i] << endl;
  }
  int pilihan;
  cout << "Masukkan nomor pilihan dokter (1-" << JUMLAH_DOKTER << "): ";
  cin >> pilihan;
  cin.ignore();

  if (pilihan >= 1 && pilihan <= JUMLAH_DOKTER) {
    dokterMenangani = daftarDokter[pilihan - 1];
  } else {
    dokterMenangani = "Tidak diketahui";
  }
}

void PasienIGD::tampilkanData() {
  cout << "\n===========================================\n";
  cout << "                Data Pasien IGD              \n";
  cout << "=============================================\n";
  cout << "ID Pasien        : " << idPasien << endl;
  cout << "Nama             : " << nama << endl;
  cout << "Umur             : " << umur << endl;
  cout << "Alamat           : " << alamat << endl;
  cout << "Keluhan          : " << keluhan << endl;
  cout << "Kedaruratan      : " << tingkatKedaruratan << endl;
  cout << "Dokter Menangani : " << dokterMenangani << endl;
  cout << "=============================================\n";
}

void PasienIGD::simpanKeFile(ofstream &file) {
  file << idPasien << ";" << nama << ";" << umur << ";" << jenisKelamin << ";"
       << alamat << ";" << keluhan << ";" << tingkatKedaruratan << ";"
       << dokterMenangani << "\n";
}

string PasienIGD::getidPasien() { return idPasien; }

string PasienIGD::getNama() { return nama; }

// Class Sistem IGD
class SistemIGD {
private:
  PasienIGD daftarPasien[MAX_PASIEN];
  int jumlahPasien;

public:
  SistemIGD() : jumlahPasien(0) {}
  void tambahPasien();
  void tampilkanSemuaPasien();
  void cariPasien();
  void bubbleSortByNama();
  void bubbleSortByidPasien();
  void menu();
  
};

void SistemIGD::tambahPasien() {
  if (jumlahPasien < MAX_PASIEN) {
    cout << "\n===========================================\n";
    cout << "            Pendaftaran Pasien IGD           \n";
    cout << "===========================================\n";
    cin.ignore();
    daftarPasien[jumlahPasien].inputData();

    ofstream myfile("data_pasien_igd.txt", ios::app);
    if (!myfile) {
      cout << "Gagal membuka file untuk menyimpan data.\n";
      return;
    }

    daftarPasien[jumlahPasien].simpanKeFile(myfile);
    myfile.close();

    jumlahPasien++;
    cout << "\nPasien berhasil didaftarkan.\n";
  } else {
    cout << "\nData pasien sudah penuh!\n";
  }
}

void SistemIGD::tampilkanSemuaPasien() {
  if (jumlahPasien == 0) {
    cout << "\nBelum ada pasien yang terdaftar.\n";
  } else {
    for (int i = 0; i < jumlahPasien; i++) {
      daftarPasien[i].tampilkanData();
    }
  }
}

void SistemIGD::cariPasien() {
  string idPasien;
  char ulangi;
  bool ditemukan = false;

  do {
    cout << "\nMasukkan ID Pasien yang dicari: ";
    cin.ignore();
    getline(cin, idPasien);

    ditemukan = false;

    for (int i = 0; i < jumlahPasien; i++) {
      if (daftarPasien[i].getidPasien() == idPasien) {
        cout << "\nPasien ditemukan!";
        daftarPasien[i].tampilkanData();
        ditemukan = true;
        break;
      }
    }

    if (!ditemukan) {
      cout << "\nPasien dengan ID tersebut tidak ditemukan.\n";
      cout << "Apakah ingin mencari lagi? (y/n): ";
      cin >> ulangi;
      cin.ignore();
    } else {
      break;
    }

  } while (ulangi == 'y' || ulangi == 'Y');

  if (!ditemukan) {
    cout << "\nPasien belum melakukan pendaftaran atau bukan pasien rumah "
            "sakit.\n";
  }
}

void SistemIGD::bubbleSortByNama() {
  for (int i = 0; i < jumlahPasien - 1; i++) {
    for (int j = 0; j < jumlahPasien - i - 1; j++) {
      if (daftarPasien[j].getNama() > daftarPasien[j + 1].getNama()) {
        PasienIGD temp = daftarPasien[j];
        daftarPasien[j] = daftarPasien[j + 1];
        daftarPasien[j + 1] = temp;
      }
    }
  }
  cout << "\nData berhasil diurutkan berdasarkan nama.\n";
}

void SistemIGD::bubbleSortByidPasien() {
  for (int i = 0; i < jumlahPasien - 1; i++) {
    for (int j = 0; j < jumlahPasien - i - 1; j++) {
      if (daftarPasien[j].getidPasien() > daftarPasien[j + 1].getidPasien()) {
        PasienIGD temp = daftarPasien[j];
        daftarPasien[j] = daftarPasien[j + 1];
        daftarPasien[j + 1] = temp;
      }
    }
  }
  cout << "\nData berhasil diurutkan berdasarkan ID Pasien.\n";
}

void SistemIGD::menu() {
  int pilihan;

  do {
    cout << "===========================================\n";
    cout << "             Sistem Manajemen IGD          \n";
    cout << "===========================================\n";
    cout << "1. Daftar Pasien IGD\n";
    cout << "2. Tampilkan Data Semua Pasien\n";
    cout << "3. Cari Data Pasien\n";
    cout << "4. Urutkan Data Pasien\n";
    cout << "5. Keluar\n";
    cout << "=============================================\n";
    cout << "Pilih menu (1-5): ";
    cin >> pilihan;

    switch (pilihan) {
    case 1:
      tambahPasien();
      break;
    case 2:
      tampilkanSemuaPasien();
      break;
    case 3:
      cariPasien();
      break;
    case 4: {
      int pilih;
	  cout << "\n===========================================\n";
	  cout << "           MENU SORTING DATA PASIEN               \n";
	  cout << "=============================================\n";
	  cout << "Urutkan Data Pasien berdasarkan : \n";
	  cout << "1. ID Pasien\n";
	  cout << "2. Nama\n";
	  cout << "Masukkan Pilihan : ";
	  cin >> pilih;

      if (pilih == 1)
        bubbleSortByidPasien();
      else if (pilih == 2)
        bubbleSortByNama();
      else
        cout << "Pilihan tidak valid.\n";
      break;
    }
    case 5:
      cout << "\nTerima kasih telah menggunkan Sistem IGD\n";
      cout << "Program selesai.\n";
      break;
    default:
      cout << "\nPilihan tidak valid. Coba lagi.\n";
    }

  } while (pilihan != 5);
}

// Class Rawat Inap
class Rawatinap {
private:
 int biayaRawatInap;
  const int biayaAdmin = 20000;
  int jumlahBayar;
  int jumlahHari;
  string kelas;
  string ruangan;
  
public:
  void prosesPembayaran();
  void rincian();
  void struk();
  void setJumlahBayar(int bayar) { jumlahBayar = bayar; }
  void setJumlahHari(int hari) { jumlahHari = hari; }
};

void Rawatinap::prosesPembayaran() {
  cout << "\n===========================================\n";
  cout << "           PEMILIHAN KELAS RUANGAN         \n";
  cout << "===========================================\n";
  cout << "1. VIP     - Rp 200.000/hari (Anggrek 01)\n";
  cout << "2. Kelas 1 - Rp 150.000/hari (Mawar 02)\n";
  cout << "3. Kelas 2 - Rp 100.000/hari (Melati 03)\n";
  cout << "4. Kelas 3 - Rp  50.000/hari (Kenanga 04)\n";
  cout << "Masukkan pilihan kelas (1-4): ";

  int pilih;
  while (!(cin >> pilih) || pilih < 1 || pilih > 4) {
    cout << "Pilihan tidak valid (1-4): ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  switch (pilih) {
    case 1:
      kelas = "VIP";
      ruangan = "Anggrek 01";
      biayaRawatInap = 200000;
      break;
    case 2:
      kelas = "Kelas 1";
      ruangan = "Mawar 02";
      biayaRawatInap = 150000;
      break;
    case 3:
      kelas = "Kelas 2";
      ruangan = "Melati 03";
      biayaRawatInap = 100000;
      break;
    case 4:
      kelas = "Kelas 3";
      ruangan = "Kenanga 04";
      biayaRawatInap = 50000;
      break;
    default:
      kelas = "Tidak diketahui";
      ruangan = "-";
      biayaRawatInap = 0;
      break;
  }

  cout << "\nMasukkan jumlah hari perawatan: ";
  while (!(cin >> jumlahHari) || jumlahHari <= 0) {
    cout << "Mohon masukkan angka hari yang valid (>0): ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  int total = (biayaRawatInap * jumlahHari) + biayaAdmin;
  cout << "Total biaya: Rp " << total << endl;

  int bayar;
  cout << "Masukkan jumlah pembayaran Anda: Rp ";
  while (!(cin >> bayar) || bayar < 0) {
    cout << "Mohon masukkan angka pembayaran yang valid (>=0): ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  setJumlahBayar(bayar);
  setJumlahHari(jumlahHari);
  rincian();
}

void Rawatinap::rincian() {
  int total = (biayaRawatInap * jumlahHari) + biayaAdmin;
  int kembalian = jumlahBayar - total;

  cout << "\n========== RINCIAN PEMBAYARAN RAWAT INAP ==========\n";
  cout << "Kelas         : " << kelas << endl;
  cout << "Ruangan       : " << ruangan << endl;
  cout << "Hari Inap     : " << jumlahHari << " hari\n";
  cout << "Biaya Harian  : Rp " << biayaRawatInap << endl;
  cout << "Biaya Admin   : Rp " << biayaAdmin << endl;
  cout << "Total         : Rp " << total << endl;
  cout << "Dibayar       : Rp " << jumlahBayar << endl;
  cout << "Kembalian     : Rp " << kembalian << endl;
  cout << "===================================================\n";

  int pilihan;
  do {
    cout << "\n1. Cetak Struk\n2. Kembali ke Menu Pasien\n3. Keluar\n";
    cout << "Masukkan pilihan: ";
    cin >> pilihan;

    switch (pilihan) {
      case 1: struk(); break;
      case 2: return;
      case 3: cout << "Terima kasih.\n"; break;
      default: cout << "Pilihan tidak valid.\n";
    }
  } while (pilihan != 3);
}

void Rawatinap::struk() {
  time_t now = time(0);
  int total = (biayaRawatInap * jumlahHari) + biayaAdmin;
  int kembalian = jumlahBayar - total;

  cout << "\n================= STRUK RAWAT INAP =================\n";
  cout << "Tanggal/Waktu : " << ctime(&now);
  cout << "Kelas         : " << kelas << endl;
  cout << "Ruangan       : " << ruangan << endl;
  cout << "Hari Inap     : " << jumlahHari << " hari\n";
  cout << "Biaya Inap    : Rp " << biayaRawatInap << " x " << jumlahHari << endl;
  cout << "Admin         : Rp " << biayaAdmin << endl;
  cout << "Total         : Rp " << total << endl;
  cout << "Bayar         : Rp " << jumlahBayar << endl;
  cout << "Kembalian     : Rp " << kembalian << endl;
  cout << "====================================================\n";
}

// Class Rawat Jalan
class Rawatjalan {
private:
  int biayaRawatJalan;
  const int biayaAdmin2 = 15000;
  int jumlahBayar2;
  int jumlahHari2;
  string kelasJalan;
  string ruanganJalan;

public:
  void prosesPembayaran();
  void rincian2();
  void struk2();
  void setJumlahBayar2(int bayar2) { jumlahBayar2 = bayar2; }
  void setJumlahHari2(int hari2) { jumlahHari2 = hari2; }
};

void Rawatjalan::prosesPembayaran() {
  cout << "\n===========================================\n";
  cout << "         PEMILIHAN KELAS RAWAT JALAN       \n";
  cout << "===========================================\n";
  cout << "1. VIP     - Rp 100.000/hari (Flamboyan RJ01)\n";
  cout << "2. Kelas 1 - Rp  75.000/hari (Dahlia RJ02)\n";
  cout << "3. Kelas 2 - Rp  50.000/hari (Teratai RJ03)\n";
  cout << "4. Kelas 3 - Rp  30.000/hari (Soka RJ04)\n";
  cout << "Masukkan pilihan kelas (1-4): ";

  int pilih;
  while (!(cin >> pilih) || pilih < 1 || pilih > 4) {
    cout << "Pilihan tidak valid (1-4): ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  switch (pilih) {
    case 1:
      kelasJalan = "VIP";
      ruanganJalan = "Flamboyan RJ01";
      biayaRawatJalan = 100000;
      break;
    case 2:
      kelasJalan = "Kelas 1";
      ruanganJalan = "Dahlia RJ02";
      biayaRawatJalan = 75000;
      break;
    case 3:
      kelasJalan = "Kelas 2";
      ruanganJalan = "Teratai RJ03";
      biayaRawatJalan = 50000;
      break;
    case 4:
      kelasJalan = "Kelas 3";
      ruanganJalan = "Soka RJ04";
      biayaRawatJalan = 30000;
      break;
    default:
      kelasJalan = "Tidak diketahui";
      ruanganJalan = "-";
      biayaRawatJalan = 0;
      break;
  }

  cout << "Masukkan jumlah hari kunjungan: ";
  while (!(cin >> jumlahHari2) || jumlahHari2 <= 0) {
    cout << "Mohon masukkan angka hari yang valid (>0): ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  int total2 = (biayaRawatJalan * jumlahHari2) + biayaAdmin2;
  cout << "Total                      : Rp " << total2 << endl;

  int bayar2;
  cout << "Masukkan jumlah pembayaran Anda: Rp ";
  while (!(cin >> bayar2) || bayar2 < 0) {
    cout << "Mohon masukkan angka pembayaran yang valid (>=0): ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  setJumlahBayar2(bayar2);
  setJumlahHari2(jumlahHari2);
  rincian2();
}

void Rawatjalan::rincian2() {
  int total2 = (biayaRawatJalan * jumlahHari2) + biayaAdmin2;
  int kembalian2 = jumlahBayar2 - total2;

  cout << "\n========== RINCIAN PEMBAYARAN RAWAT JALAN ==========\n";
  cout << "Kelas            : " << kelasJalan << endl;
  cout << "Ruangan          : " << ruanganJalan << endl;
  cout << "Jumlah Hari      : " << jumlahHari2 << " hari\n";
  cout << "Biaya Rawat Jalan: Rp " << biayaRawatJalan << " x " << jumlahHari2 << endl;
  cout << "Biaya Admin      : Rp " << biayaAdmin2 << endl;
  cout << "Total            : Rp " << total2 << endl;
  cout << "Jumlah Bayar     : Rp " << jumlahBayar2 << endl;
  cout << "Kembalian        : Rp " << kembalian2 << endl;
  cout << "====================================================\n";

  int pil;
  do {
    cout << "\n1. Cetak Struk\n2. Kembali ke Menu Pasien\n3. Keluar\n";
    cout << "Masukkan Pilihan Anda : ";
    cin >> pil;

    switch (pil) {
    case 1: struk2(); break;
    case 2: return;
    case 3: cout << "Terima kasih, program selesai.\n"; break;
    default: cout << "Pilihan tidak valid.\n";
    }
  } while (pil != 3);
}

void Rawatjalan::struk2() {
  time_t waktu;
  time(&waktu);
  int total2 = (biayaRawatJalan * jumlahHari2) + biayaAdmin2;
  int kembalian2 = jumlahBayar2 - total2;

  cout << "\n================= STRUK RAWAT JALAN =================\n";
  cout << "Tanggal/Waktu : " << ctime(&waktu);
  cout << "Kelas         : " << kelasJalan << endl;
  cout << "Ruangan       : " << ruanganJalan << endl;
  cout << "Jumlah Hari   : " << jumlahHari2 << " hari\n";
  cout << "Biaya Jalan   : Rp " << biayaRawatJalan << " x " << jumlahHari2 << endl;
  cout << "Admin         : Rp " << biayaAdmin2 << endl;
  cout << "Total         : Rp " << total2 << endl;
  cout << "Bayar         : Rp " << jumlahBayar2 << endl;
  cout << "Kembalian     : Rp " << kembalian2 << endl;
  cout << "======================================================\n";
}

// Class  dan Sistem Laboratorium
const int MAKS_PASIEN = 100;

class PasienLab {
private:
  string nama;
  string jenisKelamin;
  string rekamMedis;
  string jenisLab;
  string keluhan;
  string tanggalTes;
  string hasilTes;

public:
  string getRekamMedis() { return rekamMedis; }
  string getJenisLab() { return jenisLab; }
  string getHasilTes() { return hasilTes; }
  string getNama() { return nama; }
  string getTanggalTes() { return tanggalTes; }

  void inputData();
  void tampilkanData();
};

void PasienLab::inputData() {
  cout << "Nama Pasien                  : ";
  getline(cin, nama);
  cout << "Jenis Kelamin                : ";
  getline(cin, nama);
  cout << "Nomor Rekam Medis            : ";
  getline(cin, rekamMedis);
  cout << "Tanggal Tes (dd-mm-yyyy)     : ";
  getline(cin, tanggalTes);

  int pilihanLab;
  bool inputValid2 = false;
  do {
    cout << "Pilih Jenis Laboratorium:\n";
    cout << "1. Patologi Klinik\n";
    cout << "2. Mikrobiologi\n";
    cout << "3. Patologi Anatomi\n";
    cout << "Masukkan Pilihan Anda (1-3) : ";
    cin >> pilihanLab;
    cin.ignore();

    switch (pilihanLab) {
    case 1:
      jenisLab = "Patologi Klinik";
      inputValid2 = true;
      break;
    case 2:
      jenisLab = "Mikrobiologi";
      inputValid2 = true;
      break;
    case 3:
      jenisLab = "Patologi Anatomi";
      inputValid2 = true;
      break;
    default:
      cout << "Pilihan tidak valid. Silakan masukkan angka (1-3)!!" << endl;
    }
  } while (!inputValid2);

  cout << "Keluhan atau Keterangan Tambahan : ";
  getline(cin, keluhan);
  cout << "Hasil Tes                        : ";
  getline(cin, hasilTes);

  cout << "Pendaftaran berhasil.\n";
  cout << "-------------------------------\n";
}

void PasienLab::tampilkanData() {
  cout << "\n===========================================\n";
  cout << "Nama Pasien       : " << nama << endl;
  cout << "No. Rekam Medis   : " << rekamMedis << endl;
  cout << "Tanggal Tes       : " << tanggalTes << endl;
  cout << "Jenis Lab         : " << jenisLab << endl;
  cout << "Keluhan           : " << keluhan << endl;
  cout << "Hasil Tes         : " << hasilTes << endl;
  cout << "===========================================\n";
}

class SistemLaboratorium {
private:
  PasienLab daftarPasien[MAKS_PASIEN];
  int jumlahPasien;

public:
  SistemLaboratorium() : jumlahPasien(0) {}

  void daftarPasienLab();
  void tampilkanPasienPerLab();
  void tampilkanSemuaPasien();
  void cariDataPasien();
  void tampilkanHasilTes();
  void menu();
  void menumenu();
};

void SistemLaboratorium::daftarPasienLab() {
  if (jumlahPasien < MAKS_PASIEN) {
    cin.ignore();
    cout << "===========================================\n";
    cout << "        Input Data Pasien Laboratorium     \n";
    cout << "===========================================\n";
    daftarPasien[jumlahPasien].inputData();
    jumlahPasien++;
    cout << "Data pasien berhasil ditambahkan.\n";
  } else {
    cout << "Kapasitas penuh, tidak dapat menambah data pasien.\n";
  }
}

void SistemLaboratorium::tampilkanPasienPerLab() {
  string jenisLab;
  int pilihan;
  cout << "===========================================\n";
  cout << "Pilih Jenis Laboratorium untuk ditampilkan:\n";
  cout << "1. Patologi Klinik\n";
  cout << "2. Mikrobiologi\n";
  cout << "3. Patologi Anatomi\n";
  cout << "===========================================\n";
  cout << "Masukkan Pilihan Anda: ";
  cin >> pilihan;
  cin.ignore();

  switch (pilihan) {
  case 1:
    jenisLab = "Patologi Klinik";
    break;
  case 2:
    jenisLab = "Mikrobiologi";
    break;
  case 3:
    jenisLab = "Patologi Anatomi";
    break;
  default:
    cout << "Pilihan tidak valid!\n";
    return;
  }
  cout << "\n===========================================\n";
  cout << "      Daftar Pasien di Laboratorium " << jenisLab << "    \n";
  cout << "===========================================\n";
  bool ditemukan = false;
  for (int i = 0; i < jumlahPasien; i++) {
    if (daftarPasien[i].getJenisLab() == jenisLab) {
      daftarPasien[i].tampilkanData();
      ditemukan = true;
    }
  }
  if (!ditemukan) {
    cout << "Belum ada pasien di jenis lab ini.\n";
  }
}

void SistemLaboratorium::tampilkanSemuaPasien() {
  if (jumlahPasien == 0) {
    cout << "Belum ada data pasien.\n";
    return;
  }
  cout << "\n===========================================\n";
  cout << "    Daftar Seluruh Pasien Laboratorium:    \n";
  cout << "===========================================\n";
  for (int i = 0; i < jumlahPasien; i++) {
    daftarPasien[i].tampilkanData();
  }
}

void SistemLaboratorium::cariDataPasien() {
  if (jumlahPasien == 0) {
    cout << "Belum ada data pasien.\n";
    return;
  }
  string cariRekamMedis;
  cin.ignore();
  cout << "Masukkan Nomor Rekam Medis yang dicari: ";
  getline(cin, cariRekamMedis);

  bool ditemukan = false;
  for (int i = 0; i < jumlahPasien; i++) {
    if (cariRekamMedis == daftarPasien[i].getRekamMedis()) {
      daftarPasien[i].tampilkanData();
      ditemukan = true;
      return;
    }
  }
  if (!ditemukan) {
    cout << "Data pasien dengan nomor rekam medis tersebut tidak ditemukan.\n";
  }
}

void SistemLaboratorium::tampilkanHasilTes() {
  if (jumlahPasien == 0) {
    cout << "Belum ada data pasien.\n";
    return;
  }
  cout << "\n===========================================\n";
  cout << "    Daftar Hasil Tes Laboratorium Pasien   \n";
  cout << "===========================================\n";
  for (int i = 0; i < jumlahPasien; i++) {
    cout << "Nama Pasien       : " << daftarPasien[i].getNama() << endl;
    cout << "Nomor Rekam Medis : " << daftarPasien[i].getRekamMedis() << endl;
    cout << "Tanggal Tes       : " << daftarPasien[i].getTanggalTes() << endl;
    cout << "Jenis Lab         : " << daftarPasien[i].getJenisLab() << endl;
    cout << "Hasil Tes         : " << daftarPasien[i].getHasilTes() << endl;
    cout << "===========================================\n";
  }
}

void SistemLaboratorium::menu() {
  int pilihan;

  do {
    cout << "\n===========================================\n";
    cout << "      Sistem Rumah Sakit - Laboratorium    \n";
    cout << "===========================================\n";
    cout << "1. Daftar Pasien Laboratorium\n";
    cout << "2. Tampilkan Pasien per Jenis Lab\n";
    cout << "3. Tampilkan Daftar Semua Pasien\n";
    cout << "4. Cari Data Pasien\n";
    cout << "5. Tampilkan Hasil Tes Pasien\n";
    cout << "6. Keluar\n";
    cout << "===========================================\n";
    cout << "Pilihan Anda (1-6): ";
    cin >> pilihan;

    switch (pilihan) {
    case 1:
      daftarPasienLab();
      break;
    case 2:
      tampilkanPasienPerLab();
      break;
    case 3:
      tampilkanSemuaPasien();
      break;
    case 4:
      cariDataPasien();
      break;
    case 5:
      tampilkanHasilTes();
      break;
    case 6:
      cout << "Terima kasih telah menggunakan sistem.\n";
      break;
    default:
      cout << "Pilihan tidak valid. Coba lagi.\n";
    }
  } while (pilihan != 6);
}

const int MAX_OBAT = 100;
const int MAX_PESANAN = 100;

class Obat {
private:
  int kodeObat;
  int stokObat;
  int hargaObat;
  int idPesanan;
  string namaObat;

public:
  Obat() {}
  Obat(int k, string n, int s, int h)
      : kodeObat(k), namaObat(n), stokObat(s), hargaObat(h) {}

  void inputObat();
  void tampilkanObat();
  string getNama();
  int getStok();
  int getHarga();
  int getKode();
  void kurangiStok(int jumlah);
  void setStok(int s);
  void setHarga(int h);
};

void Obat::inputObat() {
  cout << "Masukkan kode obat   : ";
  cin >> kodeObat;
  cin.ignore();
  cout << "Masukkan nama obat   : ";
  getline(cin, namaObat);
  cout << "Masukkan stok obat   : ";
  cin >> stokObat;
  cout << "Masukkan harga obat  : ";
  cin >> hargaObat;
}

void Obat::tampilkanObat() {
  cout << "===========================================\n";
  cout << "Kode   : " << kodeObat << endl;
  cout << "Nama   : " << namaObat << endl;
  cout << "Stok   : " << stokObat << endl;
  cout << "Harga  : Rp" << hargaObat << endl;
  cout << "===========================================\n";
}

string Obat::getNama() { return namaObat; }
int Obat::getStok() { return stokObat; }
int Obat::getHarga() { return hargaObat; }
int Obat::getKode() { return kodeObat; }

void Obat::kurangiStok(int jumlah) {
  if (jumlah <= stokObat)
    stokObat -= jumlah;
}

void Obat::setStok(int s) { stokObat = s; }

void Obat::setHarga(int h) { hargaObat = h; }

// Struct pesanan
struct Pesanan {
  string idPasien, namaPasien, namaObat;
  int jumlah, harga, total, kodeObat;
  bool sudahDibayar;
  int bayar, kembali;
};

class SistemFarmasi {
private:
  Obat daftarObat[MAX_OBAT];
  int jumlahObat;
  int totalPenjualan;

  Pesanan daftarPesanan[MAX_PESANAN];
  int jumlahPesanan;

  int bayar;
  int kembali;
  double totalTerakhir;

public:
  SistemFarmasi();

  void dataObat();
  void tampilkanObat();
  void pengambilanObat();
  void cetakResi();
  void pembayaran();
  void tambahObat();
  void hapusPesananObat();
  void ubahPesananObat();
  void cetakStruk();
  void simpanDataObatKeFile();
  void bacaDataObatDariFile();
  void bacaPesananDariFile();
  void simpanPesananKeFile();
  void tampilkanTotalPenjualan();
  void cariPesananBerdasarkanNama();
  void cariPesananBerdasarkanIDPasien();
  void urutkanPesananBerdasarkanNama();
  void urutkanPesananBerdasarkanIDPasien();
  void tampilkanSemuaPesanan();
  void menu();
};

SistemFarmasi::SistemFarmasi() {
  jumlahObat = 0;
  totalPenjualan = 0;
  jumlahPesanan = 0;

  bacaDataObatDariFile();
  if (jumlahObat == 0) {
    dataObat();
    simpanDataObatKeFile();
  }
}

void SistemFarmasi::dataObat() {
  // =================== Analgesik & Antiinflamasi ===================
  daftarObat[jumlahObat++] = Obat(101, "Paracetamol", 100, 1000);
  daftarObat[jumlahObat++] = Obat(131, "Ibuprofen", 90, 3000);
  daftarObat[jumlahObat++] = Obat(132, "Mefenamic Acid", 60, 3000);
  daftarObat[jumlahObat++] = Obat(133, "Aspirin", 80, 2500);
  daftarObat[jumlahObat++] = Obat(134, "Naproxen", 70, 4000);
  daftarObat[jumlahObat++] = Obat(135, "Ketorolac", 50, 5000);
  daftarObat[jumlahObat++] = Obat(136, "Diclofenac", 60, 3500);
  daftarObat[jumlahObat++] = Obat(137, "Celecoxib", 40, 8000);
  daftarObat[jumlahObat++] = Obat(138, "Piroxicam", 55, 3200);
  daftarObat[jumlahObat++] = Obat(139, "Tramadol", 30, 10000);

  // =================== Antibiotik ===================
  daftarObat[jumlahObat++] = Obat(102, "Amoksisilin", 80, 5000);
  daftarObat[jumlahObat++] = Obat(140, "Ceftriaxone", 40, 50000);
  daftarObat[jumlahObat++] = Obat(141, "Ampicillin", 70, 4000);
  daftarObat[jumlahObat++] = Obat(142, "Azithromycin", 50, 15000);
  daftarObat[jumlahObat++] = Obat(143, "Ciprofloxacin", 60, 10000);
  daftarObat[jumlahObat++] = Obat(144, "Doxycycline", 55, 8000);
  daftarObat[jumlahObat++] = Obat(145, "Gentamicin", 35, 12000);
  daftarObat[jumlahObat++] = Obat(146, "Levofloxacin", 45, 11000);
  daftarObat[jumlahObat++] = Obat(147, "Metronidazole", 60, 5000);
  daftarObat[jumlahObat++] = Obat(148, "Ketoconazole", 35, 8500);

  // =================== Antidiabetik ===================
  daftarObat[jumlahObat++] = Obat(103, "Metformin", 90, 3000);
  daftarObat[jumlahObat++] = Obat(106, "Insulin", 40, 150000);
  daftarObat[jumlahObat++] = Obat(149, "Glimepiride", 60, 5500);
  daftarObat[jumlahObat++] = Obat(150, "Gliclazide", 70, 6000);
  daftarObat[jumlahObat++] = Obat(151, "Pioglitazone", 50, 7000);
  daftarObat[jumlahObat++] = Obat(152, "Acarbose", 40, 4000);
  daftarObat[jumlahObat++] = Obat(153, "Liraglutide", 25, 200000);
  daftarObat[jumlahObat++] = Obat(154, "Dulaglutide", 20, 250000);
  daftarObat[jumlahObat++] = Obat(155, "Sitagliptin", 35, 15000);
  daftarObat[jumlahObat++] = Obat(156, "Empagliflozin", 30, 18000);

  // =================== Obat Saluran Pernapasan ===================
  daftarObat[jumlahObat++] = Obat(104, "Salbutamol Inhaler", 50, 50000);
  daftarObat[jumlahObat++] = Obat(120, "Cetirizine", 100, 2000);
  daftarObat[jumlahObat++] = Obat(128, "Loratadine", 70, 2500);
  daftarObat[jumlahObat++] = Obat(157, "Ambroxol", 80, 3000);
  daftarObat[jumlahObat++] = Obat(158, "Dextromethorphan", 90, 1500);
  daftarObat[jumlahObat++] = Obat(159, "Bromhexine", 60, 2500);
  daftarObat[jumlahObat++] = Obat(160, "Theophylline", 50, 4000);
  daftarObat[jumlahObat++] = Obat(161, "Prednisone", 70, 6000);
  daftarObat[jumlahObat++] = Obat(162, "Montelukast", 40, 5000);
  daftarObat[jumlahObat++] = Obat(163, "Fluticasone Inhaler", 30, 90000);

  // =================== Obat Saluran Pencernaan ===================
  daftarObat[jumlahObat++] = Obat(111, "Amlodipin", 75, 4000);
  daftarObat[jumlahObat++] = Obat(116, "Atorvastatin", 70, 6000);
  daftarObat[jumlahObat++] = Obat(124, "Bisoprolol", 45, 6000);
  daftarObat[jumlahObat++] = Obat(125, "Captopril", 80, 3000);
  daftarObat[jumlahObat++] = Obat(126, "Nifedipine", 50, 5000);
  daftarObat[jumlahObat++] = Obat(164, "Furosemide", 65, 6000);
  daftarObat[jumlahObat++] = Obat(165, "Digoxin", 30, 10000);

  // =================== Obat Kardiovaskular ===================
  daftarObat[jumlahObat++] = Obat(111, "Amlodipin", 75, 4000);
  daftarObat[jumlahObat++] = Obat(115, "Losartan", 80, 5000);
  daftarObat[jumlahObat++] = Obat(116, "Atorvastatin", 70, 6000);
  daftarObat[jumlahObat++] = Obat(124, "Bisoprolol", 45, 6000);
  daftarObat[jumlahObat++] = Obat(125, "Captopril", 80, 3000);
  daftarObat[jumlahObat++] = Obat(126, "Nifedipine", 50, 5000);

  // =================== Diuretik ===================
  daftarObat[jumlahObat++] = Obat(109, "Furosemid", 65, 6000);
  daftarObat[jumlahObat++] = Obat(121, "Hydrochlorothiazide", 50, 3500);
  daftarObat[jumlahObat++] = Obat(122, "Spironolactone", 40, 7000);

  // =================== Psikotropika / CNS ===================
  daftarObat[jumlahObat++] = Obat(107, "Diazepam", 60, 7000);

  // =================== Vitamin dan Suplemen ===================
  daftarObat[jumlahObat++] = Obat(110, "Vitamin C", 120, 2000);

  // =================== Obat Kulit ===================
  daftarObat[jumlahObat++] = Obat(130, "Salicylic Acid", 40, 4000);
}

void SistemFarmasi::tampilkanObat() {
  cout << "=============================================\n";
  cout << "         DATA OBAT TERSEDIA SAAT INI         \n";
  cout << "=============================================\n";
  cout << left << setw(4) << "No" << setw(10) << "Kode"
       << "| " << setw(20) << "Nama Obat"
       << "| " << setw(7) << "Stok"
       << "| "
       << "Harga\n";
  cout << "=============================================\n";

  for (int i = 0; i < jumlahObat; i++) {
    cout << left << setw(4) << (i + 1) << setw(10) << daftarObat[i].getKode()
         << "| " << setw(20) << daftarObat[i].getNama() << "| " << setw(7)
         << daftarObat[i].getStok() << "| Rp" << daftarObat[i].getHarga()
         << endl;
  }

  cout << "=============================================\n";
}

void SistemFarmasi::tambahObat() {
  char pilihTambah = 'y';
  while (pilihTambah == 'y' || pilihTambah == 'Y') {

    if (jumlahObat < MAX_OBAT) {
      cout << "=============================================\n";
      cout << "                  Tambah Obat                \n";
      cout << "=============================================\n";
      daftarObat[jumlahObat].inputObat();
      jumlahObat++;
      simpanDataObatKeFile();
      cout << "Data Obat telah ditambahkan.\n";
    } else {
      cout << "Data obat penuh. Tidak bisa menambahkan lebih banyak.\n";
      break;
    }

    cout << "\nApakah Anda ingin menambahkan obat baru? (y/n): ";
    cin >> pilihTambah;
  }
  cout << "=============================================\n";
  cout << "         DAFTAR OBAT SETELAH PENAMBAHAN      \n";
  cout << "=============================================\n";
  cout << left << setw(4) << "No" << setw(10) << "Kode"
       << "| " << setw(20) << "Nama Obat"
       << "| " << setw(7) << "Stok"
       << "| Harga\n";
  cout << "=============================================\n";

  for (int i = 0; i < jumlahObat; i++) {
    cout << left << setw(4) << (i + 1) << setw(10) << daftarObat[i].getKode()
         << "| " << setw(20) << daftarObat[i].getNama() << "| " << setw(7)
         << daftarObat[i].getStok() << "| Rp" << daftarObat[i].getHarga()
         << endl;
  }
  cout << "=============================================\n";
}

void SistemFarmasi::pengambilanObat() {
  string namaObat;
  string namaPasien;
  string idPasien;
  int jumlah;
  cin.ignore();
  cout << "=============================================\n";
  cout << "Masukkan ID Pasien        : ";
  cin >> idPasien;
  cin.ignore();
  cout << "Masukkan Nama Pasien      : ";
  getline(cin, namaPasien);
  cout << "Masukkan Nama Obat        : ";
  getline(cin, namaObat);
  cout << "Masukkan Jumlah Pesanan   : ";
  cin >> jumlah;
  cout << "=============================================\n";

  for (int i = 0; i < jumlahObat; i++) {
    if (daftarObat[i].getNama() == namaObat) {
      if (daftarObat[i].getStok() >= jumlah) {
        daftarObat[i].kurangiStok(jumlah);
        Pesanan p;
        p.idPasien = idPasien;
        p.namaPasien = namaPasien;
        p.namaObat = namaObat;
        p.jumlah = jumlah;
        p.kodeObat = daftarObat[i].getKode();
        p.harga = daftarObat[i].getHarga();
        p.total = p.harga * jumlah;
        p.sudahDibayar = false;
        daftarPesanan[jumlahPesanan++] = p;
        simpanPesananKeFile();
        cout << "Pesanan berhasil ditambahkan.\n";
        return;
      } else {
        cout << "Stok tidak mencukupi.\n";
        return;
      }
    }
  }
  cout << "Obat tidak ditemukan.\n";
}

void SistemFarmasi::cetakResi() {
  if (totalTerakhir == 0) {
    cout << "Belum ada transaksi" << endl;
    return;
  }

  Pesanan &p = daftarPesanan[jumlahPesanan - 1];
  cout << "\n===========================================\n";
  cout << "              RESI PESANAN OBAT            \n";
  cout << "===========================================\n";
  cout << "ID Pasien   : " << p.idPasien << endl;
  cout << "Nama Pasien : " << p.namaPasien << endl;
  cout << "Nama Obat   : " << p.namaObat << endl;
  cout << "Jumlah      : " << p.jumlah << endl;
  cout << "Harga       : Rp" << p.harga << endl;
  cout << "Total       : Rp" << p.total << endl;
  cout << "=============================================\n";
}

void SistemFarmasi::pembayaran() {
  if (totalTerakhir == 0) {
    cout << "Belum ada transaksi.\n";
    return;
  }

  Pesanan &p = daftarPesanan[jumlahPesanan - 1];
  if (p.sudahDibayar) {
    cout << "Pesanan sudah dibayar.\n";
    return;
  }

  int bayar;
  cout << "Total bayar   : Rp" << p.total << endl;
  cout << "Masukkan uang : Rp";
  cin >> bayar;

  while (bayar < p.total) {
    cout << "Uang tidak cukup. Masukkan ulang: Rp";
    cin >> bayar;
  }

  p.bayar = bayar;
  p.kembali = bayar - p.total;
  p.sudahDibayar = true;
  totalPenjualan += p.total;
  cout << "\nPembayaran berhasil" << endl;
  cout << "Kembalian      : Rp" << p.kembali << endl;
}

void SistemFarmasi::cetakStruk() {
  if (jumlahPesanan == 0) {
    cout << "Belum ada pesanan.\n";
    return;
  }

  Pesanan &p = daftarPesanan[jumlahPesanan - 1];
  if (!p.sudahDibayar) {
    cout << "Pembayaran belum dilakukan.\n";
    return;
  }

  cout << "\n===========================================\n";
  cout << "              STRUK PEMBAYARAN             \n";
  cout << "===========================================\n";
  cout << "ID Pasien   : " << p.idPasien << endl;
  cout << "Nama Pasien : " << p.namaPasien << endl;
  cout << "Obat        : " << p.namaObat << endl;
  cout << "Jumlah      : " << p.jumlah << endl;
  cout << "Total       : Rp" << p.total << endl;
  cout << "Dibayar     : Rp" << p.bayar << endl;
  cout << "Kembalian   : Rp" << p.kembali << endl;
  cout << "Status      : LUNAS\n";
  cout << "=============================================\n";
}

void SistemFarmasi::hapusPesananObat() {
  if (jumlahPesanan == 0) {
    cout << "Belum ada pesanan.\n";
    return;
  }

  string nama;
  cin.ignore();
  cout << "Masukkan nama obat yang ingin dihapus: ";
  getline(cin, nama);

  for (int i = 0; i < jumlahPesanan; i++) {
    if (daftarPesanan[i].namaObat == nama) {
      for (int j = i; j < jumlahPesanan - 1; j++) {
        daftarPesanan[j] = daftarPesanan[j + 1];
      }
      jumlahPesanan--;
      cout << "Pesanan berhasil dihapus.\n";
      return;
    }
  }
  cout << "Pesanan tidak ditemukan.\n";
}

void SistemFarmasi::ubahPesananObat() {
  string nama;
  int jumlahBaru;
  cin.ignore();

  cout << "Masukkan nama obat yang ingin diubah jumlahnya: ";
  getline(cin, nama);

  for (int i = 0; i < jumlahPesanan; i++) {
    if (daftarPesanan[i].namaObat == nama) {
      cout << "Jumlah baru: ";
      cin >> jumlahBaru;
      daftarPesanan[i].jumlah = jumlahBaru;
      daftarPesanan[i].total = daftarPesanan[i].harga * jumlahBaru;
      cout << "Pesanan berhasil diperbarui.\n";
      simpanPesananKeFile();
      return;
    }
  }
  cout << "Pesanan tidak ditemukan.\n";
}

void SistemFarmasi::cariPesananBerdasarkanNama() {
  string cari;
  cin.ignore();
  cout << "Masukkan nama obat yang dicari: ";
  getline(cin, cari);
  bool ketemu = false;

  for (int i = 0; i < jumlahPesanan; i++) {
    if (daftarPesanan[i].namaObat == cari) {
      cout << "Pasien: " << daftarPesanan[i].namaPasien
           << ", Jumlah: " << daftarPesanan[i].jumlah << ", Total: Rp"
           << daftarPesanan[i].total << endl;
      ketemu = true;
    }
  }
  if (!ketemu) {
    cout << "Pesanan tidak ditemukan.\n";
  }
}

void SistemFarmasi::urutkanPesananBerdasarkanNama() {
  for (int i = 0; i < jumlahPesanan - 1; i++) {
    for (int j = 0; j < jumlahPesanan - i - 1; j++) {
      if (daftarPesanan[j].namaObat > daftarPesanan[j + 1].namaObat) {
        Pesanan temp = daftarPesanan[j];
        daftarPesanan[j] = daftarPesanan[j + 1];
        daftarPesanan[j + 1] = temp;
      }
    }
  }
  cout << "Pesanan berhasil diurutkan berdasarkan nama obat.\n";

  for (int i = 0; i < jumlahPesanan; i++) {
    cout << "=============================================\n";
    cout << "\nPesanan ke-" << i + 1 << ":\n";
    cout << "Nama Obat    : " << daftarPesanan[i].namaObat << endl;
    cout << "ID Pasien    : " << daftarPesanan[i].idPasien << endl;
    cout << "Nama Pasien  : " << daftarPesanan[i].namaPasien << endl;
    cout << "Jumlah       : " << daftarPesanan[i].jumlah << endl;
    cout << "Harga        : " << daftarPesanan[i].harga << endl;
    cout << "=============================================\n";
  }
}

void SistemFarmasi::cariPesananBerdasarkanIDPasien() {
  string id;
  cin.ignore();
  cout << "Masukkan ID Pasien yang dicari: ";
  getline(cin, id);
  bool ketemu = false;

  for (int i = 0; i < jumlahPesanan; i++) {
    if (daftarPesanan[i].idPasien == id) {
    cout << "=============================================\n";
      cout << "\nPesanan ke-" << i + 1 << ":\n";
      cout << "ID Pasien    : " << daftarPesanan[i].idPasien << endl;
      cout << "Nama Pasien  : " << daftarPesanan[i].namaPasien << endl;
      cout << "Kode Obat    : " << daftarPesanan[i].kodeObat << endl;
      cout << "Nama Obat    : " << daftarPesanan[i].namaObat << endl;
      cout << "Jumlah       : " << daftarPesanan[i].jumlah << endl;
      cout << "Harga        : Rp" << daftarPesanan[i].harga << endl;
      cout << "Total        : Rp" << daftarPesanan[i].total << endl;
      cout << "=============================================\n";
      ketemu = true;
    }
  }
  if (!ketemu)
    cout << "Pesanan dengan ID tersebut tidak ditemukan.\n";
}

void SistemFarmasi::urutkanPesananBerdasarkanIDPasien() {
  for (int i = 0; i < jumlahPesanan - 1; i++) {
    for (int j = 0; j < jumlahPesanan - i - 1; j++) {
      if (daftarPesanan[j].idPasien > daftarPesanan[j + 1].idPasien) {
        Pesanan temp = daftarPesanan[j];
        daftarPesanan[j] = daftarPesanan[j + 1];
        daftarPesanan[j + 1] = temp;
      }
    }
  }
  cout << "Pesanan berhasil diurutkan berdasarkan ID pasien.\n";
  for (int i = 0; i < jumlahPesanan; i++) {
    cout << "=============================================\n";
    cout << "\nPesanan ke-" << i + 1 << ":\n";
    cout << "ID Pasien    : " << daftarPesanan[i].idPasien << endl;
    cout << "Nama Pasien  : " << daftarPesanan[i].namaPasien << endl;
    cout << "Kode Obat    : " << daftarPesanan[i].kodeObat << endl;
    cout << "Nama Obat    : " << daftarPesanan[i].namaObat << endl;
    cout << "Jumlah       : " << daftarPesanan[i].jumlah << endl;
    cout << "Harga        : Rp" << daftarPesanan[i].harga << endl;
    cout << "=============================================\n";
  }
}

void SistemFarmasi::tampilkanTotalPenjualan() {
  int totalSemua = 0;
  cout << "=============================================\n";
  cout << "             RINCIAN SEMUA PESANAN           \n";
  cout << "=============================================\n";
  for (int i = 0; i < jumlahPesanan; i++) {
    cout << "Pesanan ke-" << i + 1 << ":\n";
    cout << "ID Pasien    : " << daftarPesanan[i].idPasien << endl;
    cout << "Nama Pasien  : " << daftarPesanan[i].namaPasien << endl;
    cout << "Kode Obat    : " << daftarPesanan[i].kodeObat << endl;
    cout << "Nama Obat    : " << daftarPesanan[i].namaObat << endl;
    cout << "Jumlah       : " << daftarPesanan[i].jumlah << endl;
    cout << "Harga        : Rp" << daftarPesanan[i].harga << endl;
    cout << "Total        : Rp" << daftarPesanan[i].total << endl;
    cout << "Status       : "
         << (daftarPesanan[i].sudahDibayar ? "LUNAS" : "BELUM DIBAYAR") << endl;
    cout << "=============================================\n";

    totalSemua += daftarPesanan[i].total;
  }

  cout << "\n>>> Total keseluruhan penjualan obat: Rp" << totalSemua << "\n";
}

void SistemFarmasi::tampilkanSemuaPesanan() {
  cout << "\n===========================================\n";
  cout << "             DAFTAR SEMUA PESANAN         \n";
  cout << "===========================================\n";

  for (int i = 0; i < jumlahPesanan; i++) {
    cout << "\nID Pasien   : " << daftarPesanan[i].idPasien << endl;
    cout << "Nama Pasien : " << daftarPesanan[i].namaPasien << endl;
    cout << "Kode Obat   : " << daftarPesanan[i].kodeObat << endl;
    cout << "Nama Obat   : " << daftarPesanan[i].namaObat << endl;
    cout << "Jumlah      : " << daftarPesanan[i].jumlah << endl;
    cout << "Harga       : Rp" << daftarPesanan[i].harga << endl;
    cout << "Total       : Rp" << daftarPesanan[i].total << endl;
    cout << "Status      : "
         << (daftarPesanan[i].sudahDibayar ? "Lunas" : "Belum") << endl;
    cout << "=============================================\n";
  }
}

void SistemFarmasi::simpanDataObatKeFile() {
  ofstream file("obat.txt");
  for (int i = 0; i < jumlahObat; i++) {
    file << daftarObat[i].getKode() << "|" << daftarObat[i].getNama() << "|"
         << daftarObat[i].getStok() << "|" << daftarObat[i].getHarga() << "\n";
  }
  file.close();
}

void SistemFarmasi::simpanPesananKeFile() {
  ofstream file("pesanan.txt");
  for (int i = 0; i < jumlahPesanan; i++) {
    file << daftarPesanan[i].idPasien << "|" << daftarPesanan[i].namaPasien
         << "|" << daftarPesanan[i].kodeObat << "|" << daftarPesanan[i].namaObat
         << "|" << daftarPesanan[i].jumlah << "|" << daftarPesanan[i].harga
         << "|" << daftarPesanan[i].total << "|"
         << daftarPesanan[i].sudahDibayar << "|" << daftarPesanan[i].bayar
         << "|" << daftarPesanan[i].kembali << "\n";
  }
  file.close();
}

void SistemFarmasi::bacaDataObatDariFile() {
  ifstream file("obat.txt");
  if (!file)
    return;
  int kode, stok, harga;
  string nama;
  jumlahObat = 0;
  while (file >> kode) {
    file.ignore();
    getline(file, nama, '|');
    file >> stok;
    file.ignore();
    file >> harga;
    file.ignore();
    daftarObat[jumlahObat++] = Obat(kode, nama, stok, harga);
  }
  file.close();
}

void SistemFarmasi::bacaPesananDariFile() {
  ifstream file("pesanan.txt");
  if (!file)
    return;
  jumlahPesanan = 0;
  while (!file.eof()) {
    Pesanan p;
    getline(file, p.idPasien, '|');
    getline(file, p.namaPasien, '|');
    file >> p.kodeObat;
    file.ignore();
    getline(file, p.namaObat, '|');
    file >> p.jumlah;
    file.ignore();
    file >> p.harga;
    file.ignore();
    file >> p.total;
    file.ignore();
    file >> p.sudahDibayar;
    file.ignore();
    file >> p.bayar;
    file.ignore();
    file >> p.kembali;
    file.ignore();
    if (!p.idPasien.empty()) {
      daftarPesanan[jumlahPesanan++] = p;
    }
  }
  file.close();
}

void SistemFarmasi::menu() {
  int opsi;
  do {
    system("cls");
    cout << "\n===========================================\n";
    cout << "       MENU SISTEM FARMASI RUMAH SAKIT     \n";
    cout << "===========================================\n";
    cout << "1. Tampilkan Daftar Obat" << endl;
    cout << "2. Tambah Daftar Obat" << endl;
    cout << "3. Buat Pesanan Obat" << endl;
    cout << "4. Ubah Pesanan Obat" << endl;
    cout << "5. Hapus Pesanan Obat" << endl;
    cout << "6. Cetak Resi Pesanan" << endl;
    cout << "7. Lakukan Pembayaran" << endl;
    cout << "8. Cetak Struk" << endl;
    cout << "9. Total Penjualan" << endl;
    cout << "10. Urutkan Pesanan Berdasarkan Nama" << endl;
    cout << "11. Urutkan Pesanan Berdasarkan ID Pasien" << endl;
    cout << "12. Cari Pesanan Berdasarkan Nama obat" << endl;
    cout << "13. Cari Pesanan Berdasarkan ID Pasien" << endl;
    cout << "14. Tampilkan semua Pesanan" << endl;
    cout << "15. Keluar" << endl;
    cout << "===========================================\n";
    cout << "Masukkan Pilihan Anda : ";
    cin >> opsi;

    switch (opsi) {
    case 1:
      tampilkanObat();
      break;
    case 2:
      tambahObat();
      break;
    case 3:
      pengambilanObat();
      break;
    case 4:
      ubahPesananObat();
      break;
    case 5:
      hapusPesananObat();
      break;
    case 6:
      cetakResi();
      break;
    case 7:
      pembayaran();
      break;
    case 8:
      cetakStruk();
      break;
    case 9:
      tampilkanTotalPenjualan();
      break;
    case 10:
      urutkanPesananBerdasarkanNama();
      break;
    case 11:
      urutkanPesananBerdasarkanIDPasien();
      break;
    case 12:
      cariPesananBerdasarkanNama();
      break;
    case 13:
      cariPesananBerdasarkanIDPasien();
      break;
    case 14:
      tampilkanSemuaPesanan();
      break;
    case 15:
      simpanDataObatKeFile();
      simpanPesananKeFile();
      cout << "Keluar dari sistem. Terima Kasih\n";
      break;
    default:
      cout << "Pilihan tidak valid.\n";
    }
    if (opsi != 15)
      system("pause");
  } while (opsi != 15);
}

void menumenu() {
  SistemFarmasi sistem;
  sistem.menu();
}

// Struktur data Pasien Umum
struct PasienUmum {
  string nama;
  int umur;
  char jenis_kelamin;
  string telp;
  string alamat;
  string keluhan;
  string poli;
  string jenis_rawat_umum;
};

// Class untuk pasien umum 
class PasienUmumMenu {
private:
  PasienUmum pasien_umum;
  bool memilikiJenisRawat = false;

public:
  void pendaftaran_umum();
  void daftar_poli_umum();
  void input_keluhan_umum();
  bool pilih_jenis_rawat_umum();
  void simpan_data_umum();
  void cari_data_umum();
  void proses_pembayaran_umum();
  void menu();
};

void PasienUmumMenu::pendaftaran_umum() {
  cout << "===========================================\n";
  cout << "          Pendaftaran Pasien Umum          \n";
  cout << "===========================================\n";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "Nama\t\t: ";
  getline(cin, pasien_umum.nama);
  cout << "Umur\t\t: ";
  while (!(cin >> pasien_umum.umur) || pasien_umum.umur < 0 ||
         pasien_umum.umur > 150) {
    cout << "Masukkan umur valid (0-150): ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  cout << "Jenis Kelamin (L/P)\t: ";
  cin >> pasien_umum.jenis_kelamin;
  pasien_umum.jenis_kelamin = toupper(pasien_umum.jenis_kelamin);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "Alamat\t\t: ";
  getline(cin, pasien_umum.alamat);
  cout << "No.Telepon\t\t: ";
  getline(cin, pasien_umum.telp);
  memilikiJenisRawat = false; // reset jenis rawat if you newly register
}

void PasienUmumMenu::daftar_poli_umum() {
  if (pasien_umum.nama.empty()) {
    cout << "Silakan lakukan pendaftaran terlebih dahulu.\n";
    return;
  }
  cout << "===========================================\n";
  cout << "            Pilih Poli Pasien Umum         \n";
  cout << "===========================================\n";
  cout << " 1. Klinik Anak\n";
  cout << " 2. Klinik Kebidanan & Kandungan\n";
  cout << " 3. Klinik Penyakit Dalam\n";
  cout << " 4. Klinik Bedah\n";
  cout << " 5. Klinik Konsultan Bedah Digestif\n";
  cout << " 6. Klinik Konsultan Bedah Onkologi\n";
  cout << " 7. Klinik Orthopedi\n";
  cout << " 8. Klinik Urologi\n";
  cout << " 9. Klinik Syaraf\n";
  cout << "10. Klinik Kulit & Kelamin\n";
  cout << "11. Klinik Mata\n";
  cout << "12. Klinik Telinga, Hidung & Tenggorokan\n";
  cout << "13. Klinik Jiwa\n";
  cout << "14. Klinik Jantung & Pembuluh Darah\n";
  cout << "15. Klinik Gigi & Mulut\n";
  cout << "===========================================\n";
  cout << "Masukkan pilihan (1-15): ";

  int pilihan;
  cin >> pilihan;

  switch (pilihan) {
  case 1:
    pasien_umum.poli = "Klinik Anak";
    break;
  case 2:
    pasien_umum.poli = "Klinik Kebidanan & Kandungan";
    break;
  case 3:
    pasien_umum.poli = "Klinik Penyakit Dalam";
    break;
  case 4:
    pasien_umum.poli = "Klinik Bedah";
    break;
  case 5:
    pasien_umum.poli = "Klinik Konsultan Bedah Digestif";
    break;
  case 6:
    pasien_umum.poli = "Klinik Konsultan Bedah Onkologi";
    break;
  case 7:
    pasien_umum.poli = "Klinik Orthopedi";
    break;
  case 8:
    pasien_umum.poli = "Klinik Urologi";
    break;
  case 9:
    pasien_umum.poli = "Klinik Syaraf";
    break;
  case 10:
    pasien_umum.poli = "Klinik Kulit & Kelamin";
    break;
  case 11:
    pasien_umum.poli = "Klinik Mata";
    break;
  case 12:
    pasien_umum.poli = "Klinik Telinga, Hidung & Tenggorokan";
    break;
  case 13:
    pasien_umum.poli = "Klinik Jiwa";
    break;
  case 14:
    pasien_umum.poli = "Klinik Jantung & Pembuluh Darah";
    break;
  case 15:
    pasien_umum.poli = "Klinik Gigi & Mulut";
    break;
  default:
    cout << "Pilihan tidak valid.\n";
    pasien_umum.poli = "";
    return;
  }

  cout << "\nPoli berhasil dipilih : " << pasien_umum.poli << "\n";
}

void PasienUmumMenu::input_keluhan_umum() {
  if (pasien_umum.nama.empty()) {
    cout << "Silakan lakukan pendaftaran terlebih dahulu.\n";
    return;
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "Masukkan Keluhan Anda: ";
  getline(cin, pasien_umum.keluhan);
}

bool PasienUmumMenu::pilih_jenis_rawat_umum() {
  if (pasien_umum.nama.empty()) {
    cout << "Silakan lakukan pendaftaran terlebih dahulu.\n";
    return false;
  }
  int jenis_rawat_umum;
  do {
    cout << "===========================================\n";
    cout << "          Pilih Jenis Layanan Rawat:       \n";
    cout << "===========================================\n";
    cout << "1. Rawat Jalan\n";
    cout << "2. Rawat Inap\n";
    cout << "3. Lewati / Kembali\n";
    cout << "===========================================\n";
    cout << "Masukkan pilihan: ";
    cin >> jenis_rawat_umum;

    switch (jenis_rawat_umum) {
    case 1:
      pasien_umum.jenis_rawat_umum = "Rawat Jalan";
      memilikiJenisRawat = true;
      return true;
    case 2:
      pasien_umum.jenis_rawat_umum = "Rawat Inap";
      memilikiJenisRawat = true;
      return true;
    case 3:
      pasien_umum.jenis_rawat_umum = "";
      memilikiJenisRawat = false;
      return false;
    default:
      cout << "Pilihan tidak valid.\n";
    }
  } while (true);
}

void PasienUmumMenu::simpan_data_umum() {
  if (pasien_umum.nama.empty()) {
    cout
        << "Data belum lengkap. Silakan lakukan pendaftaran terlebih dahulu.\n";
    return;
  }
  ofstream file("data_pasien_umum.txt", ios::app);
  if (file.is_open()) {
    file << pasien_umum.nama << endl;
    file << pasien_umum.umur << endl;
    file << pasien_umum.jenis_kelamin << endl;
    file << pasien_umum.alamat << endl;
    file << pasien_umum.telp << endl;
    file << pasien_umum.keluhan << endl;
    file << pasien_umum.poli << endl;
    file << pasien_umum.jenis_rawat_umum << endl;
    file << "===\n";
    file.close();
    cout << "Data berhasil disimpan.\n";
  } else {
    cout << "Gagal membuka file.\n";
  }
}

void PasienUmumMenu::cari_data_umum() {
  ifstream file("data_pasien_umum.txt");
  if (!file) {
    cout << "File tidak ditemukan.\n";
    return;
  }

  string nama_cari;
  cout << "Masukkan nama pasien yang dicari: ";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  getline(cin, nama_cari);

  string line;
  bool found = false;
  while (getline(file, line)) {
    if (line == nama_cari) {
      found = true;
      cout << "===========================================\n";
      cout << "        Data Ditemukan Pasien Umum:        \n";
      cout << "===========================================\n";
      cout << "Nama: " << line << endl;
      string umur, jenisKelamin, alamat, telp, keluhan, poli, jenis_rawat_umum;
      getline(file, umur);
      getline(file, jenisKelamin);
      getline(file, alamat);
      getline(file, telp);
      getline(file, keluhan);
      getline(file, poli);
      getline(file, jenis_rawat_umum);
      cout << "Umur: " << umur << endl;
      cout << "Jenis Kelamin: " << jenisKelamin << endl;
      cout << "Alamat: " << alamat << endl;
      cout << "Telepon: " << telp << endl;
      cout << "Keluhan: " << keluhan << endl;
      cout << "Poli: " << poli << endl;
      cout << "Jenis Layanan Rawat : " << jenis_rawat_umum << endl;
      cout << "===========================================\n";
      break;
    }
  }
  if (!found) {
    cout << "Data tidak ditemukan.\n";
  }
  file.close();
}

void PasienUmumMenu::proses_pembayaran_umum() {
  if (!memilikiJenisRawat) {
    cout << "Silakan pilih jenis layanan rawat terlebih dahulu pada menu 4.\n";
    return;
  }
  if (pasien_umum.jenis_rawat_umum == "Rawat Jalan") {
    Rawatjalan rj;
    rj.prosesPembayaran();
  } else if (pasien_umum.jenis_rawat_umum == "Rawat Inap") {
    Rawatinap ri;
    ri.prosesPembayaran();
  } else {
    cout << "Jenis layanan rawat tidak valid.\n";
  }
}

void PasienUmumMenu::menu() {
  int pilihan;
  do {
    cout << "===========================================\n";
    cout << "               MENU PASIEN UMUM            \n";
    cout << "===========================================\n";
    cout << "1. Pendaftaran\n";
    cout << "2. Pilih Poli\n";
    cout << "3. Masukkan Keluhan\n";
    cout << "4. Pilih Jenis Layanan Rawat\n";
    cout << "5. Proses Pembayaran\n";
    cout << "6. Simpan Data\n";
    cout << "7. Cari Data\n";
    cout << "8. Kembali ke Menu Utama\n";
    cout << "===========================================\n";
    cout << "Pilih menu: ";
    cin >> pilihan;

    switch (pilihan) {
    case 1:
      pendaftaran_umum();
      break;
    case 2:
      daftar_poli_umum();
      break;
    case 3:
      input_keluhan_umum();
      break;
    case 4:
      pilih_jenis_rawat_umum();
      break;
    case 5:
      proses_pembayaran_umum();
      break;
    case 6:
      simpan_data_umum();
      break;
    case 7:
      cari_data_umum();
      break;
    case 8:
      cout << "Kembali ke menu utama...\n";
      break;
    default:
      cout << "Pilihan tidak valid.\n";
    }
  } while (pilihan != 8);
}

// Struktur data Pasien BPJS
struct PasienBpjs {
  string namaBpjs;
  int umurBpjs;
  char jenis_kelamin_Bpjs;
  string tel_Bpjs;
  string alamatBpjs;
  string keluhanBpjs;
  string poliBpjs;
  string jenis_rawat_bpjs;
};

// Class untuk pasien BPJS dengan menu terintegrasi
class PasienBPJSMenu {
private:
  PasienBpjs pasien_bpjs;
  bool memilikiJenisRawat = false;

public:
  void pendaftaran();
  void daftar_poli_bpjs();
  void input_keluhan_bpjs();
  bool pilih_jenis_rawat_bpjs();
  void simpan_data();
  void tampilkan_data();
  void cari_data();
  void proses_pembayaran_bpjs();
  void menu();
};

void PasienBPJSMenu::pendaftaran() {
  cout << "===========================================\n";
  cout << "          Pendaftaran Pasien BPJS          \n";
  cout << "===========================================\n";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "Nama\t\t: ";
  getline(cin, pasien_bpjs.namaBpjs);
  cout << "Umur\t\t: ";
  while (!(cin >> pasien_bpjs.umurBpjs) || pasien_bpjs.umurBpjs < 0 ||
         pasien_bpjs.umurBpjs > 150) {
    cout << "Masukkan umur valid (0-150): ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  cout << "Jenis Kelamin (L/P)\t: ";
  cin >> pasien_bpjs.jenis_kelamin_Bpjs;
  pasien_bpjs.jenis_kelamin_Bpjs = toupper(pasien_bpjs.jenis_kelamin_Bpjs);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "Alamat\t\t: ";
  getline(cin, pasien_bpjs.alamatBpjs);
  cout << "No.Telepon\t\t: ";
  getline(cin, pasien_bpjs.tel_Bpjs);
  memilikiJenisRawat = false;
}

void PasienBPJSMenu::daftar_poli_bpjs() {
  if (pasien_bpjs.namaBpjs.empty()) {
    cout << "Silakan lakukan pendaftaran terlebih dahulu.\n";
    return;
  }
  cout << "===========================================\n";
  cout << "           Pilih Poli Pasien BPJS          \n";
  cout << "===========================================\n";
  cout << " 1. Klinik Anak\n";
  cout << " 2. Klinik Kebidanan & Kandungan\n";
  cout << " 3. Klinik Penyakit Dalam\n";
  cout << " 4. Klinik Bedah\n";
  cout << " 5. Klinik Konsultan Bedah Digestif\n";
  cout << " 6. Klinik Konsultan Bedah Onkologi\n";
  cout << " 7. Klinik Orthopedi\n";
  cout << " 8. Klinik Urologi\n";
  cout << " 9. Klinik Syaraf\n";
  cout << "10. Klinik Kulit & Kelamin\n";
  cout << "11. Klinik Mata\n";
  cout << "12. Klinik Telinga, Hidung & Tenggorokan\n";
  cout << "13. Klinik Jiwa\n";
  cout << "14. Klinik Jantung & Pembuluh Darah\n";
  cout << "15. Klinik Gigi & Mulut\n";
  cout << "===========================================\n";
  cout << "Masukkan pilihan (1-15): ";

  int pilihan;
  cin >> pilihan;

  switch (pilihan) {
  case 1:
    pasien_bpjs.poliBpjs = "Klinik Anak";
    break;
  case 2:
    pasien_bpjs.poliBpjs = "Klinik Kebidanan & Kandungan";
    break;
  case 3:
    pasien_bpjs.poliBpjs = "Klinik Penyakit Dalam";
    break;
  case 4:
    pasien_bpjs.poliBpjs = "Klinik Bedah";
    break;
  case 5:
    pasien_bpjs.poliBpjs = "Klinik Konsultan Bedah Digestif";
    break;
  case 6:
    pasien_bpjs.poliBpjs = "Klinik Konsultan Bedah Onkologi";
    break;
  case 7:
    pasien_bpjs.poliBpjs = "Klinik Orthopedi";
    break;
  case 8:
    pasien_bpjs.poliBpjs = "Klinik Urologi";
    break;
  case 9:
    pasien_bpjs.poliBpjs = "Klinik Syaraf";
    break;
  case 10:
    pasien_bpjs.poliBpjs = "Klinik Kulit & Kelamin";
    break;
  case 11:
    pasien_bpjs.poliBpjs = "Klinik Mata";
    break;
  case 12:
    pasien_bpjs.poliBpjs = "Klinik Telinga, Hidung & Tenggorokan";
    break;
  case 13:
    pasien_bpjs.poliBpjs = "Klinik Jiwa";
    break;
  case 14:
    pasien_bpjs.poliBpjs = "Klinik Jantung & Pembuluh Darah";
    break;
  case 15:
    pasien_bpjs.poliBpjs = "Klinik Gigi & Mulut";
    break;
  default:
    cout << "Pilihan tidak valid.\n";
    pasien_bpjs.poliBpjs = "";
    return;
  }

  cout << "\nPoli berhasil dipilih : " << pasien_bpjs.poliBpjs << "\n";
}

void PasienBPJSMenu::input_keluhan_bpjs() {
  if (pasien_bpjs.namaBpjs.empty()) {
    cout << "Silakan lakukan pendaftaran terlebih dahulu.\n";
    return;
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "Masukkan Keluhan Anda: ";
  getline(cin, pasien_bpjs.keluhanBpjs);
}

bool PasienBPJSMenu::pilih_jenis_rawat_bpjs() {
  if (pasien_bpjs.namaBpjs.empty()) {
    cout << "Silakan lakukan pendaftaran terlebih dahulu.\n";
    return false;
  }
  int rawat_bpjs;
  do {
    cout << "===========================================\n";
    cout << "   Pilih Jenis Layanan Rawat Pasien BPJS:  \n";
    cout << "===========================================\n";
    cout << "1. Rawat Jalan\n";
    cout << "2. Rawat Inap\n";
    cout << "3. Lewati / Kembali\n";
    cout << "===========================================\n";
    cout << "Masukkan pilihan Anda : ";
    cin >> rawat_bpjs;

    switch (rawat_bpjs) {
    case 1:
      pasien_bpjs.jenis_rawat_bpjs = "Rawat Jalan";
      memilikiJenisRawat = true;
      return true;
    case 2:
      pasien_bpjs.jenis_rawat_bpjs = "Rawat Inap";
      memilikiJenisRawat = true;
      return true;
    case 3:
      pasien_bpjs.jenis_rawat_bpjs = "";
      memilikiJenisRawat = false;
      return false;
    default:
      cout << "Pilihan tidak valid.\n";
    }
  } while (true);
}

void PasienBPJSMenu::simpan_data() {
  if (pasien_bpjs.namaBpjs.empty()) {
    cout
        << "Data belum lengkap. Silakan lakukan pendaftaran terlebih dahulu.\n";
    return;
  }
  ofstream data("data_pasien_bpjs.txt", ios::app);
  if (data.is_open()) {
    data << pasien_bpjs.namaBpjs << endl;
    data << pasien_bpjs.umurBpjs << endl;
    data << pasien_bpjs.jenis_kelamin_Bpjs << endl;
    data << pasien_bpjs.alamatBpjs << endl;
    data << pasien_bpjs.tel_Bpjs << endl;
    data << pasien_bpjs.keluhanBpjs << endl;
    data << pasien_bpjs.poliBpjs << endl;
    data << pasien_bpjs.jenis_rawat_bpjs << endl;
    data << "===\n";
    data.close();
    cout << "Data berhasil disimpan.\n";
  } else {
    cout << "Gagal membuka file.\n";
  }
}

void PasienBPJSMenu::tampilkan_data() {
  ifstream data("data_pasien_bpjs.txt");
  string baris;

  if (!data.is_open()) {
    cout << "File data tidak ditemukan.\n";
    return;
  }
  cout << "===========================================\n";
  cout << "            Daftar Pasien BPJS             \n";
  cout << "===========================================\n";
  while (getline(data, baris)) {
    cout << baris << endl;
  }
  data.close();
}

void PasienBPJSMenu::cari_data() {
  ifstream data("data_pasien_bpjs.txt");
  if (!data) {
    cout << "File tidak ditemukan.\n";
    return;
  }

  string cari_nama;
  cout << "Masukkan nama pasien yang dicari: ";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  getline(cin, cari_nama);

  string baris;
  bool ditemukan = false;
  while (getline(data, baris)) {
    if (baris == cari_nama) {
      ditemukan = true;
      cout << "===========================================\n";
      cout << "          Data Ditemukan Pasien BPJS:      \n";
      cout << "===========================================\n";
      cout << "Nama: " << baris << endl;
      string umurBpjs, jenis_kelamin_bpjs, alamatBpjs, telpBpjs, keluhanBpjs,
          poliBpjs, jenis_rawat_bpjs;
      getline(data, umurBpjs);
      getline(data, jenis_kelamin_bpjs);
      getline(data, alamatBpjs);
      getline(data, telpBpjs);
      getline(data, keluhanBpjs);
      getline(data, poliBpjs);
      getline(data, jenis_rawat_bpjs);
      cout << "Umur                : " << umurBpjs << endl;
      cout << "Jenis Kelamin       : " << jenis_kelamin_bpjs << endl;
      cout << "Alamat              : " << alamatBpjs << endl;
      cout << "Telepon             : " << telpBpjs << endl;
      cout << "Keluhan             : " << keluhanBpjs << endl;
      cout << "Poli                : " << poliBpjs << endl;
      cout << "Jenis Layanan Rawat : " << jenis_rawat_bpjs << endl;
      cout << "===========================================\n";
      break;
    }
  }

  if (!ditemukan) {
    cout << "Data pasien tidak ditemukan.\n";
  }

  data.close();
}

void PasienBPJSMenu::proses_pembayaran_bpjs() {
  if (!memilikiJenisRawat) {
    cout << "Silakan pilih jenis layanan rawat terlebih dahulu pada menu 4.\n";
    return;
  }
  if (pasien_bpjs.jenis_rawat_bpjs == "Rawat Jalan") {
    Rawatjalan rj;
    rj.prosesPembayaran();
  } else if (pasien_bpjs.jenis_rawat_bpjs == "Rawat Inap") {
    Rawatinap ri;
    ri.prosesPembayaran();
  } else {
    cout << "Jenis layanan rawat tidak valid.\n";
  }
}

void PasienBPJSMenu::menu() {
  int pilihan;
  do {
    cout << "===========================================\n";
    cout << "              MENU PASIEN BPJS             \n";
    cout << "===========================================\n";
    cout << "1. Pendaftaran\n";
    cout << "2. Daftar Poli\n";
    cout << "3. Masukkan Keluhan\n";
    cout << "4. Pilih Jenis Layanan Rawat\n";
    cout << "5. Proses Pembayaran\n";
    cout << "6. Simpan Data\n";
    cout << "7. Tampilkan Semua Data\n";
    cout << "8. Cari Data\n";
    cout << "9. Kembali ke Menu Utama\n";
    cout << "===========================================\n";
    cout << "Masukkan Pilihan : ";
    cin >> pilihan;

    switch (pilihan) {
    case 1:
      pendaftaran();
      break;
    case 2:
      daftar_poli_bpjs();
      break;
    case 3:
      input_keluhan_bpjs();
      break;
    case 4:
      pilih_jenis_rawat_bpjs();
      break;
    case 5:
      proses_pembayaran_bpjs();
      break;
    case 6:
      simpan_data();
      break;
    case 7:
      tampilkan_data();
      break;
    case 8:
      cari_data();
      break;
    case 9:
      cout << "Kembali ke menu utama...\n";
      break;
    default:
      cout << "Pilihan tidak valid.\n";
    }
  } while (pilihan != 9);
}

// class kasir
class Kasir {
  Rawatinap inap;
  Rawatjalan jalan;
  SistemFarmasi farmasi;

public:
  void menuKasir() {
    int pilihan;
    do {
      cout << "=============================================\n";
      cout << "                  MENU KASIR                 \n";
      cout << "=============================================\n";
      cout << "1. Rawat Inap\n";
      cout << "2. Rawat Jalan\n";
      cout << "3. Farmasi\n";
      cout << "4. Keluar\n";
      cout << "=============================================\n";
      cout << "Pilih: ";
      cin >> pilihan;

      switch (pilihan) {
      case 1:
        inap.struk();
        break;
      case 2:
        jalan.struk2();
        break;
      case 3:
        farmasi.cetakStruk();
        break;
      case 4:
        cout << "Keluar dari menu kasir\n";
        break;
      default:
        cout << "Pilihan tidak valid\n";
        break;
      }
    } while (pilihan != 4);
  }
};

void informasi() {
  cout << "===========================================\n";
  cout << "            INFORMASI RUMAH SAKIT          \n";
  cout << "===========================================\n";
  cout << "Alamat    : Jl. Wirosaban No.1 Yogyakarta 55162\n";
  cout << "Telepon   : (0274) 123-4567\n";
  cout << "Layanan   : Gawat Darurat, Rawat Inap, \n"
       << "            Rawat Jalan, oratorium, Apotek\n";
  cout << "-------------------------------------------\n";
  cout << "             PENDAFTARAN LOKET\n";
  cout << "-------------------------------------------\n";
  cout << "  Layanan Pagi:\n";
  cout << "    Senin - Kamis    : 07.15 - 11.00\n";
  cout << "    Jum'at - Sabtu   : 07.15 - 10.00\n";
  cout << "  Layanan Sore:\n";
  cout << "    Senin - Kamis    : 12.00 - 16.00\n";
  cout << "    Jum'at           : 13.00 - 16.00\n";
  cout << "    Sabtu            : 11.00 - 14.00\n";
  cout << "-------------------------------------------\n";
  cout << "         PERATURAN KUNJUNGAN PASIEN:\n";
  cout << "-------------------------------------------\n";
  cout << "  1. Pengunjung berusia 12 tahun ke atas\n";
  cout << "  2. Pengunjung dalam kondisi sehat\n";
  cout << "  3. Tetap menerapkan protokol kesehatan\n"
       << "     (menggunakan masker dan cuci tangan)\n";
  cout << "  4. Pengunjung masuk ke ruang pasien secara\n"
       << "     terbatas dan bergantian\n";
  cout << "===========================================\n";
}

void menuPasien() {
  int opsi;
  do {
    cout << "===========================================\n";
    cout << "                 MENU PASIEN               \n";
    cout << "===========================================\n";
    cout << "1. Login Pasien\n";
    cout << "2. Daftar Pasien Baru\n";
    cout << "3. Kembali\n";
    cout << "Masukkan Pilihan : ";
    cin >> opsi;
    cin.ignore();

    switch (opsi) {
    case 1: {
      Pasien p;
      string id, pass;
      cout << "ID Pasien : ";
      getline(cin, id);
      cout << "Password  : ";
      getline(cin, pass);
      if (Pasien::loginPasien(id, pass, p)) {
        cout << "\nLogin berhasil.\n";
        cout << "--- Data Anda ---\n";
        p.tampilkan();

        int layanan;
        do {
          cout << "===========================================\n";
          cout << "                Sistem Layanan             \n";
          cout << "===========================================\n";
          cout << "1. IGD\n";
          cout << "2. UMUM\n";
          cout << "3. BPJS\n";
          cout << "4. Laboratorium\n";
          cout << "5. Farmasi\n";
          cout << "6. Kasir\n";
          cout << "7. Keluar\n";
          cout << "Masukkan Pilihan : ";
          cin >> layanan;
          cin.ignore();
          switch (layanan) {
          case 1: {
            SistemIGD igd;
            igd.menu();
            break;
          }
          case 2: {
            PasienUmumMenu pasien_umum;
            pasien_umum.menu();
            break;
          }
          case 3: {
            PasienBPJSMenu pasien_bpjs;
            pasien_bpjs.menu();
            break;
          }
          case 4: {
            SistemLaboratorium lab;
            lab.menu();
            break;
          }
          case 5: {
            SistemFarmasi farmasi;
            farmasi.menu();
            break;
          }
          case 6: {
            Kasir kasir;
            kasir.menuKasir();
            break;
          }
          case 7:
            cout << "Terima kasih telah menggunakan sistem.\n";
            break;
          default:
            cout << "Pilihan tidak valid.\n";
          }
        } while (layanan != 7);
      } else {
        cout << "Login gagal. ID atau password salah.\n";
      }
      break;
    }
    case 2: {
      Pasien p;
      cout << "===========================================\n";
      cout << "           Pendaftaran Pasien Baru         \n";
      cout << "===========================================\n";
      cout << "Nama          : ";
      getline(cin, p.nama);
      p.idPasien = Pasien::buatIDBaru();
      cout << "Umur          : ";
      cin >> p.umur;
      cin.ignore();
      cout << "Jenis Kelamin : ";
      getline(cin, p.jenisKelamin);
      cout << "Alamat        : ";
      getline(cin, p.alamat);
      cout << "Password      : ";
      getline(cin, p.password);
      p.simpanKeFile();
      cout << "Pendaftaran berhasil. ID Anda: " << p.idPasien << "\n";
      break;
    }
    case 3:
      cout << "Kembali ke menu utama.\n";
      break;
    default:
      cout << "Pilihan tidak valid.\n";
    }
  } while (opsi != 3);
}

int main() {
  int pilihan;
  do {
    cout << "=============================================\n";
    cout << "                 MENU UTAMA                  \n";
    cout << "=============================================\n";
    cout << "1. Login Admin\n";
    cout << "2. Menu Pasien\n";
    cout << "3. Informasi Rumah Sakit\n";
    cout << "4. Keluar\n";
    cout << "=============================================\n";
    cout << "Pilih menu: ";
    cin >> pilihan;
    cin.ignore();

    switch (pilihan) {
    case 1:
      menuAdmin();
      break;
    case 2:
      menuPasien();
      break;
    case 3:
      informasi();
      break;
    case 4:
      cout << "Terima kasih.\n";
      break;
    default:
      cout << "Pilihan tidak valid.\n";
    }
  } while (pilihan != 4);

  return 0;
}

