#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_PENUMPANG = 100;
const int MAX_TIKET = 100;

class Tiket {
public:
    string nomor_penerbangan;
    string asal;
    string tujuan;
    string tanggal;
    string waktu;
    int harga;
    int kursi_tersedia;

    void tampilInfo() {
        cout << "Penerbangan: " << nomor_penerbangan << endl;
        cout << "Rute: " << asal << " -> " << tujuan << endl;
        cout << "Tanggal: " << tanggal << endl;
        cout << "Waktu: " << waktu << endl;
        cout << "Harga: Rp" << harga << endl;
        cout << "Kursi tersedia: " << kursi_tersedia << endl;
        cout << "-------------------------" << endl;
    }
};

class Penumpang {
public:
    string nama;
    string no_ktp;
    string no_telepon;
    string nomor_penerbangan;

    void tampilInfo() {
        cout << "Nama: " << nama << endl;
        cout << "No. KTP: " << no_ktp << endl;
        cout << "No. Telepon: " << no_telepon << endl;
        cout << "Nomor Penerbangan: " << nomor_penerbangan << endl;
        cout << "-------------------------" << endl;
    }
};

class SistemTiket {
private:
    Tiket daftar_tiket[MAX_TIKET];
    Penumpang daftar_penumpang[MAX_PENUMPANG];
    int jumlah_tiket;
    int jumlah_penumpang;

public:
    SistemTiket() {
        jumlah_tiket = 0;
        jumlah_penumpang = 0;
    }

    void tambahTiket() {
        if (jumlah_tiket >= MAX_TIKET) {
            cout << "Maaf, kapasitas tiket sudah penuh." << endl;
            return;
        }

        cout << "Masukkan data tiket baru:" << endl;
        cout << "Nomor Penerbangan: ";
        cin >> daftar_tiket[jumlah_tiket].nomor_penerbangan;
        cout << "Asal: ";
        cin >> daftar_tiket[jumlah_tiket].asal;
        cout << "Tujuan: ";
        cin >> daftar_tiket[jumlah_tiket].tujuan;
        cout << "Tanggal (DD-MM-YYYY): ";
        cin >> daftar_tiket[jumlah_tiket].tanggal;
        cout << "Waktu (HH:MM): ";
        cin >> daftar_tiket[jumlah_tiket].waktu;
        cout << "Harga: ";
        cin >> daftar_tiket[jumlah_tiket].harga;
        cout << "Jumlah Kursi Tersedia: ";
        cin >> daftar_tiket[jumlah_tiket].kursi_tersedia;

        jumlah_tiket++;
        cout << "Tiket berhasil ditambahkan!" << endl;
    }

    void tampilSemuaTiket() {
        if (jumlah_tiket == 0) {
            cout << "Tidak ada tiket tersedia." << endl;
            return;
        }

        cout << "=== DAFTAR TIKET TERSEDIA ===" << endl;
        for (int i = 0; i < jumlah_tiket; i++) {
            daftar_tiket[i].tampilInfo();
        }
    }

    void cariTiketBerdasarkanHarga() {
        if (jumlah_tiket == 0) {
            cout << "Tidak ada tiket tersedia." << endl;
            return;
        }

        int harga_maks;
        cout << "Masukkan harga maksimal yang diinginkan: ";
        cin >> harga_maks;

        cout << "=== TIKET DENGAN HARGA <= " << harga_maks << " ===" << endl;
        bool ditemukan = false;
        for (int i = 0; i < jumlah_tiket; i++) {
            if (daftar_tiket[i].harga <= harga_maks) {
                daftar_tiket[i].tampilInfo();
                ditemukan = true;
            }
        }

        if (!ditemukan) {
            cout << "Tidak ditemukan tiket dengan harga <= " << harga_maks << endl;
        }
    }

    void tambahPenumpang() {
        if (jumlah_penumpang >= MAX_PENUMPANG) {
            cout << "Maaf, kapasitas penumpang sudah penuh." << endl;
            return;
        }

        cout << "Masukkan data penumpang baru:" << endl;
        cout << "Nama: ";
        cin.ignore();
        getline(cin, daftar_penumpang[jumlah_penumpang].nama);
        cout << "No. KTP: ";
        cin >> daftar_penumpang[jumlah_penumpang].no_ktp;
        cout << "No. Telepon: ";
        cin >> daftar_penumpang[jumlah_penumpang].no_telepon;
        cout << "Nomor Penerbangan: ";
        cin >> daftar_penumpang[jumlah_penumpang].nomor_penerbangan;

        // Cek apakah penerbangan ada dan kurangi kursi tersedia
        bool penerbangan_ditemukan = false;
        for (int i = 0; i < jumlah_tiket; i++) {
            if (daftar_tiket[i].nomor_penerbangan == daftar_penumpang[jumlah_penumpang].nomor_penerbangan) {
                if (daftar_tiket[i].kursi_tersedia > 0) {
                    daftar_tiket[i].kursi_tersedia--;
                    penerbangan_ditemukan = true;
                    break;
                } else {
                    cout << "Maaf, kursi untuk penerbangan ini sudah habis." << endl;
                    return;
                }
            }
        }

        if (!penerbangan_ditemukan) {
            cout << "Nomor penerbangan tidak ditemukan." << endl;
            return;
        }

        jumlah_penumpang++;
        cout << "Penumpang berhasil ditambahkan!" << endl;
    }

    void tampilSemuaPenumpang() {
        if (jumlah_penumpang == 0) {
            cout << "Tidak ada penumpang terdaftar." << endl;
            return;
        }

        cout << "=== DAFTAR PENUMPANG ===" << endl;
        for (int i = 0; i < jumlah_penumpang; i++) {
            daftar_penumpang[i].tampilInfo();
        }
    }

    void updatePenumpang() {
        if (jumlah_penumpang == 0) {
            cout << "Tidak ada penumpang terdaftar." << endl;
            return;
        }

        string no_ktp;
        cout << "Masukkan No. KTP penumpang yang akan diupdate: ";
        cin >> no_ktp;

        for (int i = 0; i < jumlah_penumpang; i++) {
            if (daftar_penumpang[i].no_ktp == no_ktp) {
                cout << "Masukkan data baru:" << endl;
                cout << "Nama (" << daftar_penumpang[i].nama << "): ";
                cin.ignore();
                getline(cin, daftar_penumpang[i].nama);
                cout << "No. Telepon (" << daftar_penumpang[i].no_telepon << "): ";
                cin >> daftar_penumpang[i].no_telepon;
                cout << "Nomor Penerbangan (" << daftar_penumpang[i].nomor_penerbangan << "): ";
                cin >> daftar_penumpang[i].nomor_penerbangan;
                cout << "Data penumpang berhasil diupdate!" << endl;
                return;
            }
        }

        cout << "Penumpang dengan No. KTP " << no_ktp << " tidak ditemukan." << endl;
    }

    void hapusPenumpang() {
        if (jumlah_penumpang == 0) {
            cout << "Tidak ada penumpang terdaftar." << endl;
            return;
        }

        string no_ktp;
        cout << "Masukkan No. KTP penumpang yang akan dihapus: ";
        cin >> no_ktp;

        for (int i = 0; i < jumlah_penumpang; i++) {
            if (daftar_penumpang[i].no_ktp == no_ktp) {
                // Kembalikan kursi tersedia
                for (int j = 0; j < jumlah_tiket; j++) {
                    if (daftar_tiket[j].nomor_penerbangan == daftar_penumpang[i].nomor_penerbangan) {
                        daftar_tiket[j].kursi_tersedia++;
                        break;
                    }
                }

                // Geser semua elemen setelahnya ke kiri
                for (int j = i; j < jumlah_penumpang - 1; j++) {
                    daftar_penumpang[j] = daftar_penumpang[j + 1];
                }

                jumlah_penumpang--;
                cout << "Penumpang berhasil dihapus!" << endl;
                return;
            }
        }

        cout << "Penumpang dengan No. KTP " << no_ktp << " tidak ditemukan." << endl;
    }

    void hapusTiket() {
        if (jumlah_tiket == 0) {
            cout << "Tidak ada tiket tersedia." << endl;
            return;
        }

        string nomor_penerbangan;
        cout << "Masukkan nomor penerbangan tiket yang akan dihapus: ";
        cin >> nomor_penerbangan;

        for (int i = 0; i < jumlah_tiket; i++) {
            if (daftar_tiket[i].nomor_penerbangan == nomor_penerbangan) {
                // Geser semua elemen setelahnya ke kiri
                for (int j = i; j < jumlah_tiket - 1; j++) {
                    daftar_tiket[j] = daftar_tiket[j + 1];
                }

                jumlah_tiket--;
                cout << "Tiket berhasil dihapus!" << endl;
                return;
            }
        }

        cout << "Tiket dengan nomor penerbangan " << nomor_penerbangan << " tidak ditemukan." << endl;
    }

    void cetakTiketKeFile() {
        if (jumlah_penumpang == 0) {
            cout << "Tidak ada penumpang terdaftar." << endl;
            return;
        }

        string no_ktp;
        cout << "Masukkan No. KTP penumpang yang akan dicetak tiketnya: ";
        cin >> no_ktp;

        for (int i = 0; i < jumlah_penumpang; i++) {
            if (daftar_penumpang[i].no_ktp == no_ktp) {
                string nama_file = "tiket_" + no_ktp + ".txt";
                ofstream file(nama_file);

                if (file.is_open()) {
                    file << "=== TIKET PESAWAT ===" << endl;
                    file << "Nama: " << daftar_penumpang[i].nama << endl;
                    file << "No. KTP: " << daftar_penumpang[i].no_ktp << endl;
                    file << "No. Telepon: " << daftar_penumpang[i].no_telepon << endl;
                    file << "Nomor Penerbangan: " << daftar_penumpang[i].nomor_penerbangan << endl;

                    // Cari info penerbangan
                    for (int j = 0; j < jumlah_tiket; j++) {
                        if (daftar_tiket[j].nomor_penerbangan == daftar_penumpang[i].nomor_penerbangan) {
                            file << "Rute: " << daftar_tiket[j].asal << " -> " << daftar_tiket[j].tujuan << endl;
                            file << "Tanggal: " << daftar_tiket[j].tanggal << endl;
                            file << "Waktu: " << daftar_tiket[j].waktu << endl;
                            file << "Harga: Rp" << daftar_tiket[j].harga << endl;
                            break;
                        }
                    }

                    file.close();
                    cout << "Tiket berhasil dicetak ke file " << nama_file << endl;
                } else {
                    cout << "Gagal membuka file untuk ditulis." << endl;
                }
                return;
            }
        }

        cout << "Penumpang dengan No. KTP " << no_ktp << " tidak ditemukan." << endl;
    }
};

void tampilMenu() {
    cout << "\n=== SISTEM PEMESANAN TIKET PESAWAT ===" << endl;
    cout << "1. Tambah Tiket" << endl;
    cout << "2. Tampilkan Semua Tiket" << endl;
    cout << "3. Cari Tiket Berdasarkan Harga" << endl;
    cout << "4. Tambah Penumpang" << endl;
    cout << "5. Tampilkan Semua Penumpang" << endl;
    cout << "6. Update Data Penumpang" << endl;
    cout << "7. Hapus Penumpang" << endl;
    cout << "8. Hapus Tiket" << endl;
    cout << "9. Cetak Tiket ke File" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilihan: ";
}

int main() {
    SistemTiket sistem;
    int pilihan;

    do {
        tampilMenu();
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                sistem.tambahTiket();
                break;
            case 2:
                sistem.tampilSemuaTiket();
                break;
            case 3:
                sistem.cariTiketBerdasarkanHarga();
                break;
            case 4:
                sistem.tambahPenumpang();
                break;
            case 5:
                sistem.tampilSemuaPenumpang();
                break;
            case 6:
                sistem.updatePenumpang();
                break;
            case 7:
                sistem.hapusPenumpang();
                break;
            case 8:
                sistem.hapusTiket();
                break;
            case 9:
                sistem.cetakTiketKeFile();
                break;
            case 0:
                cout << "Terima kasih telah menggunakan sistem kami." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != 0);

    return 0;
}
