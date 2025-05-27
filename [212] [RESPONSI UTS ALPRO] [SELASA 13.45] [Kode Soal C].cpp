#include<iostream> 
#include<fstream>
#include<iomanip>
using namespace std;
//Kode soal c
//D212 Mal'an Airin
//Shopee
void tambah_saldo(int topup, long &saldo) {
	char pil;
	cout<<"Kamu memiliki saldo: RP."<<saldo<<endl;
	cout<<"Apakah ingin menambah saldo? (Y/N): "; cin>>pil;
	if (pil == 'y' || pil == 'Y') {
		int topup;
		cout<<"Masukkan nominal topup: "; cin>>topup;
		saldo += topup; 
		cout<<"Saldo kamu sekarang: Rp."<<saldo<<endl;
	}
	system("pause");
	system("cls");
}

int main () {
	string us;
	string pw;
	long saldo = 0;
	
	do{
		cout << "Masukkan User: "; 
		cin>>us;
		cout << "Masukkan Password: "; 
		cin>>pw;
		if(us != "Mal'an" || pw != "212") {
			cout<<"User atau Password salah"<<endl;
		} else {
			cout<<"Berhasil Login"<<endl;
		}
		system("pause");
		system("cls");
	} while(us != "Mal'an" && pw != "212");
	
	system("cls");

	tambah_saldo(0, saldo);	
	int harga_total = 0;
	int harga[7] = {900000, 700000, 500000, 200000, 150000, 93000, 20000 };
	string nama[7] = {"Cincin", "Sepatu", "Tas", "Baju", "Topi", "Kalung", "Gelang"};
	int jumBar[7] = {0};
	int pilihan, no;
	char PIL;
	int jumlah;
	int hapus;
	bool check = true;
	do{
		cout<<"LIST BARANG"<<endl;
		cout<<left<<setw(20)<<"1.Cincin "<<"RP.900.000"<<endl;
		cout<<left<<setw(20)<<"2. Sepatu"<<"RP. 700.000"<<endl;
		cout<<left<<setw(20)<<"3. Tas"<<"RP. 500.000"<<endl;
		cout<<left<<setw(20)<<"4. Baju"<<"RP. 200.000"<<endl;
		cout<<left<<setw(20)<<"5. Topi"<<"RP. 150.000"<<endl;
		cout<<left<<setw(20)<<"6. Kalung"<<"RP. 93.000"<<endl;
		cout<<left<<setw(20)<<"7. Gelang"<<"RP. 20.000"<<endl;
		cout<<"8. Lihat pesanan"<<endl;
		cout<<"9. Tambah Saldo"<<endl;
		cout<<"0. Selesai"<<endl; 
		cout<<"Saldo saat ini: Rp."<<saldo<<endl;
		cout<<endl;
		
		cout<<"Pilihan: "; cin>>pilihan;
		if(pilihan == 0) {
			if(harga_total > saldo) {
			cout<<"Saldo tidak mencukupi"<<endl;
			system("pause");
			}
			else {
			check = false;
			break;
			}
		} else if(pilihan == 8) {
			for(int i = 0; i < 7; i++){
				if(jumBar[i] != 0) {
					long harBar = harga[i]*jumBar[i];
					cout<<nama[i]<<" "<<harga[i]<<" x "<<jumBar[i]<<" = Rp. "<<harBar<<endl;
				}
			}
			cout<<"Harga Total: Rp. "<<harga_total<<endl;
			cout<<"Ingin menghapus barang? (y/n): "; cin>>PIL;
			if (PIL == 'y' || PIL == 'Y') {
				cout<<"Masukkan no barang: "; cin>>no;
				if(jumBar[no-1] != 0) {
					cout<<"Jumlah barang yang dihapus: "; cin>>hapus;
					jumBar[no-1] -= hapus; 
					harga_total -= harga[no-1]*hapus;
				}
			}
			system("pause");
		} else if(pilihan == 8) {
			tambah_saldo(0, saldo);
		} else {
			cout<<"Jumlah: "; cin>>jumlah;
			harga_total += harga[pilihan-1] * jumlah;
			jumBar[pilihan-1] += jumlah;  
		}
			system("cls");
	} while(check == true);
	
	string alamat;
	cin.ignore();
	cout<<"Masukkan Alamat Penerima: "; getline(cin, alamat);
	system("pause");
	system("cls");
	
	double diskon;
	
		cout<<"VOUCHER"<<endl;
		cout<<"1. 5% Untuk Pembelian >= Rp. 5.000"<<endl;
		cout<<"2. 10% Untuk Pembelian >= Rp. 10.000"<<endl;
		cout<<"3. 20% Untuk Pembelian >= Rp. 20.000"<<endl;
		cout<<"0. Next"<<endl;
		cout<<"Pilihan: "; cin>>pilihan;
		
		switch (pilihan) {
			case 1:
				if(harga_total < 5000) {
					cout<<"Syarat tidak memenuhi"<<endl;
				} else {
					cout<<"Menggunakan Voucher 5%"<<endl;
					diskon = harga_total*1.05 - harga_total;
					cout<<"Diskon: Rp. "<<diskon<<endl;
					harga_total -= diskon; 
					cout<<"Harga Total: Rp. "<<harga_total<<endl;
				}
				break;
			case 2:
				if(harga_total < 10000) {
					cout<<"Syarat tidak memenuhi"<<endl;
				} else {
					cout<<"Menggunakan Voucher 10%"<<endl;
					diskon = harga_total*1.1 - harga_total;
					cout<<"Diskon: Rp. "<<diskon<<endl;
					harga_total -= diskon; 
					cout<<"Harga Total: Rp. "<<harga_total<<endl;
				}
				break;
			case 3:
				if(harga_total < 20000) {
					cout<<"Syarat tidak memenuhi"<<endl;
				} else {
					cout<<"Menggunakan Voucher 20%"<<endl;
					diskon =harga_total*1.2 - harga_total;
					cout<<"Diskon: Rp. "<<diskon<<endl;
					harga_total -= diskon; 
					cout<<"Harga Total: Rp. "<<harga_total<<endl;
				}
				break;
			default:
				cout<<"Input tidak valid!"<<endl;
		}
	cout<<endl;
	
	int asuransi = 0;
	int jumpro = 0;
	cout<<"PROTEKSI PRODUK"<<endl;
	cout<<"1. Gunakan (Rp. 5000 per produk)"<<endl;
	cout<<"2. Next"<<endl;
	cout<<"Pilihan: "; cin>>pilihan;
	
	if(pilihan == 1) {
		for(int i = 0; i < 7; i++){
				if(jumBar[i] != 0) {
					jumpro += jumBar[i]*5000;
				}
			}
		harga_total += jumpro;
		cout<<"Biaya Asuransi: Rp. "<<jumpro<<endl;
		cout<<"Harga Total: Rp. "<<harga_total<<endl;
	}
	
	cout<<endl;
	
	do{
		cout<<"EKSPEDISI PENGIRIMAN PRODUK"<<endl;
		cout<<"1. JNE"<<endl;
		cout<<"2. JNT"<<endl;
		cout<<"3. Express"<<endl;
		cout<<"Pilihan: "; cin>>pilihan;
		
		string ekspedisi;
		switch (pilihan) {
			case 1: ekspedisi = "JNE"; break;
			case 2: ekspedisi = "JNT"; break;
			case 3: ekspedisi = "Express"; break;
			default: cout<<"Input tidak valid"<<endl;	
		}
	} while(pilihan > 3 || pilihan < 1);
	
	cout<<endl;
	
	cout<<"Struk.txt berhasil dibuat "<<endl;
	ofstream file;
	file.open("struk.txt");
	for(int i = 0; i < 7; i++){
				if(jumBar[i] != 0) {
					long harBar = harga[i]*jumBar[i];
					file<<nama[i]<<" "<<harga[i]<<" x "<<jumBar[i]<<" = Rp. "<<harBar<<endl;
				}
			}
	file<<"Alamat Penerima: "<<alamat<<endl;
	file<<"Diskon: Rp. "<<diskon<<endl;
	file<<"Biaya Asuransi: Rp. "<<jumpro<<endl;
	file<<"Total harga: Rp. "<<harga_total<<endl;
	file.close();

	
	return 0;
}
