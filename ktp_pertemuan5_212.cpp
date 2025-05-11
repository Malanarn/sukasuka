#include <iostream>
#include <string>

using namespace std;

struct KTP {
    char nik[20];
    string nama;
    string tempat_lahir;
    string tgl_lahir;
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

void pilihKelamin(string &kelamin){
	int pilihan;
	do{
		cout << "Pilih Kelamin :\n";
		cout << "1.Laki Laki\n";
		cout << "2.Perempuan\n";
		cout << "Pilihan Anda: ";
    	cin >> pilihan;
		cin.ignore();
	
	switch (pilihan) {
		case 1: 
			kelamin = "Laki laki"; 
			break;
		case 2: 
			kelamin = "Perempuan"; 
			break;
		default:
			cout << "Pilihan jenis kelamin tidak valid. Ulangi\n";
			kelamin = "Tidak Valid";
			break;
		}
	} while (kelamin == "Tidak Valid" );
}

void pilihAgama(string &agama) {
    int pilihan;
    do {
    cout << "Pilih Agama :\n";
    cout << "1. Islam\n";
    cout << "2. Kristen\n";
    cout << "3. Katolik\n";
    cout << "4. Hindu\n";
    cout << "5. Buddha\n";
    cout << "6. Konghucu\n";
    cout << "Pilihan Anda: ";
    cin >> pilihan;
    cin.ignore();

    switch (pilihan) {
        case 1: 
			agama = "Islam"; 
			break;
        case 2: 
			agama = "Kristen"; 
			break;
        case 3: 
			agama = "Katolik"; 
			break;
        case 4: 
			agama = "Hindu"; 
			break;
        case 5: 
			agama = "Buddha"; 
			break;
        case 6: 
			agama = "Konghucu"; 
			break;
        default:
            cout << "Pilihan agama tidak valid. Ulangi\n";
            agama = "Tidak Valid";
            break;
    	}
	} while (agama == "Tidak Valid");
}

void inputKTP(KTP &ktp) {
    cout << "Masukkan NIK : "; 
	cin >> ktp.nik; cin.ignore();
    cout << "Masukkan Nama : "; 
	getline(cin, ktp.nama);
    cout << "Masukkan Tempat Lahir : "; 
	getline(cin, ktp.tempat_lahir);
    cout << "Masukkan Tanggal Lahir (DD-MM-YYYY) : "; 
	getline(cin, ktp.tgl_lahir);
   
    pilihKelamin(ktp.jenis_kelamin);
    cout << "Masukkan Golongan Darah (A/B/AB/O) : "; 
	cin >> ktp.gol_darah; cin.ignore();
    cout << "Masukkan Alamat : "; 
	getline(cin, ktp.alamat);
    cout << "Masukkan RT/RW : "; 
	getline(cin, ktp.rt_rw);
    cout << "Masukkan Kelurahan/Desa : "; 
	getline(cin, ktp.kel_desa);
    cout << "Masukkan Kecamatan : "; 
	getline(cin, ktp.kecamatan);
    pilihAgama(ktp.agama);
    cout << "Masukkan Status Perkawinan : "; 
	getline(cin, ktp.status_perkawinan);
    cout << "Masukkan Pekerjaan : "; 
	getline(cin, ktp.pekerjaan);
    cout << "Masukkan Kewarganegaraan : "; 
	getline(cin, ktp.kewarganegaraan);
    cout << "Masukkan Berlaku Hingga : "; 
	getline(cin, ktp.berlaku_hingga);
}

void displayKTP(const KTP &ktp) {
    cout << "\n================= KARTU TANDA PENDUDUK =================\n";
    cout << "NIK                : " << ktp.nik << endl;
    cout << "Nama               : " << ktp.nama << endl;
    cout << "Tempat Lahir       : " << ktp.tempat_lahir << endl;
    cout << "Tanggal Lahir      : " << ktp.tgl_lahir << endl;
    cout << "Jenis Kelamin      : " << ktp.jenis_kelamin << "        Gol. Darah : " << ktp.gol_darah << endl;
    cout << "Alamat             : " << ktp.alamat << endl;
    cout << "   RT/RW           : " << ktp.rt_rw << endl;
    cout << "   Kel/Desa        : " << ktp.kel_desa << endl;
    cout << "   Kecamatan       : " << ktp.kecamatan << endl;
    cout << "Agama              : " << ktp.agama << endl;
    cout << "Status Perkawinan  : " << ktp.status_perkawinan << endl;
    cout << "Pekerjaan          : " << ktp.pekerjaan << endl;
    cout << "Kewarganegaraan    : " << ktp.kewarganegaraan << endl;
    cout << "Berlaku Hingga     : " << ktp.berlaku_hingga << endl;

    cout << "=========================================================\n";
}

void editKTP(KTP &ktp) {
    int pilihan;
    do {
        cout << "\n=== MENU EDIT DATA KTP ===\n";
        cout << "1. Nama" << endl;
        cout << "2. Tempat Lahir" << endl;
        cout << "3. Tanggal Lahir" << endl;
        cout << "4. Jenis Kelamin" << endl;
        cout << "5. Golongan Darah" << endl;
        cout << "6. Alamat" << endl;
        cout << "7. RT/RW" << endl;
        cout << "8. Kelurahan/Desa" << endl;
        cout << "9. Kecamatan" << endl;
        cout << "10. Agama" << endl;
        cout << "11. Status Perkawinan" << endl;
        cout << "12. Pekerjaan" << endl;
        cout << "13. Kewarganegaraan" << endl;
        cout << "14. Berlaku Hingga" << endl;
        cout << "0. Selesai Edit" << endl;
        cout << "Pilihan Anda : ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: 
				cout << "Nama baru : "; 
				getline(cin, ktp.nama); 
				break;
            case 2: 
				cout << "Tempat Lahir: "; 
				getline(cin, ktp.tempat_lahir); 
				break;
            case 3: 
				cout << "Tanggal Lahir baru: "; 
				cin>>ktp.tgl_lahir; 
				break;
            case 4: 
				pilihKelamin(ktp.jenis_kelamin); 
				break;
            case 5: 
				cout << "Golongan Darah baru (A/B/AB/O): "; 
				getline(cin, ktp.gol_darah); 
				break;
            case 6: 
				cout << "Alamat baru: "; 
				getline(cin, ktp.alamat); 
				break;
            case 7: 
				cout << "RT/RW baru: "; 
				getline(cin, ktp.rt_rw); 
				break;
            case 8: 
				cout << "Kelurahan/Desa baru: "; 
				getline(cin, ktp.kel_desa); 
				break;
            case 9: 
				cout << "Kecamatan baru: "; 
				getline(cin, ktp.kecamatan); 
				break;
            case 10: 
				pilihAgama(ktp.agama); 
				break;
            case 11: 
				cout << "Status Perkawinan baru: "; 
				getline(cin, ktp.status_perkawinan); 
				break;
            case 12: 
				cout << "Pekerjaan baru: "; 
				getline(cin, ktp.pekerjaan); 
				break;
            case 13: 
				cout << "Kewarganegaraan baru: "; 
				getline(cin, ktp.kewarganegaraan); 
				break;
            case 14: 
				cout << "Berlaku Hingga baru: "; 
				getline(cin, ktp.berlaku_hingga); 
				break;
            default: 
				cout << "Pilihan data tidak valid.\n"; 
				break;
        }
    } while (pilihan != 0);
}

bool mintaEdit() {
    char edit;
    cout << "\nApakah Anda ingin mengedit data? (y/n): ";
    cin >> edit;
    cin.ignore();
    return (edit == 'y' || edit == 'Y');
}

int main() {
    int jumlah;
    cout << "Masukkan jumlah penduduk : ";
    cin >> jumlah;
    cin.ignore();

    KTP*daftarKTP = new KTP[jumlah];

    for (int i = 0; i < jumlah; ++i) {
        cout << "\n=== Input Data KTP ke-" << i + 1 << " ===\n";
        inputKTP(daftarKTP[i]);
		displayKTP(daftarKTP[i]);

    	if (mintaEdit()) {
       		editKTP(daftarKTP[i]);
			displayKTP(daftarKTP[i]);
    	} else {
        	cout << "Tidak melakukan edit data.\n";
    	}
    }
    
    delete[] daftarKTP;
    return 0;
}
