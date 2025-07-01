#include <iostream>
#include <conio.h>
using namespace std;

class sorting{
	public:
		void input();
		void proses();
		void output();
	private:
		int mhs;
		int nilai[100];
		string nim[15], kelas[5], status[100], nama[30];
		string cari;	
};

void sorting::input(){
	cout <<"Data Mahasiswa ";
	cout << endl;
	for(int i=0; i<5; i++){
		cout << "Mahasiswa ke-"<<i+1;
		cout << endl;
		cout << "Nim      : ";
		cin >> nim[i];
		cout << "Kelas    : ";
		cin >> kelas[i];
		cout << "Nama     : ";
		cin.ignore();
		getline(cin,nama[i]);
		cout << "Nilai    : ";
		cin >> nilai[i];
		cout << "Status   : ";
		cin.ignore();
		getline(cin,status[i]);
		cout << endl;
	}
}
void sorting::proses(){
	cout << "(sebelum di sorting) " ;
	cout << endl;
	cout << "Nim\t\tKelas\tNama\tNilai\tStatus";
	cout << endl;
	for (int i =0; i<5; i++){
		cout << nim[i] << "\t" << kelas[i] << "\t" << nama[i] << "\t" << nilai[i] <<"\t" << status[i] <<endl; 
	}
	for(int i =0; i<5; i++){
		

	for (int j=i+1; j<2; j++){
		if(nilai[i]<nilai[j]){
			nim[i].swap (nim[j]);
			kelas[i].swap (kelas[j]);
			nama[i].swap  (nama[j]);
			status[i].swap (status[j]);
			mhs = nilai[i];
			nilai[i] = nilai[j];
			nilai[j] = mhs;
		}
	}
}
cout << endl;
}

void sorting::output(){
	cout  << "(setelah di sorting)";
	cout << endl;
	cout << "Nim\t\tKelas\tNama\t\tNilai\tStatus";
	cout << endl;
	for (int i =0; i<5; i++){
		cout<< nim[i] << "\t" << kelas[i] << "\t" << nama[i] << "\t" << nilai[i] << "\t" << status[i] << endl;
		
	}
	cout << endl;
	
	cout << "Mencari Data " <<endl;
	cout << "Status Mahasiswa : "; 
	getline(cin,cari);
	
	for(int i =0; i<5; i++){
		if(status[i]==cari){
			cout << "Nim\t\tKelas\tNama\t\tNilai\tStatus"<< endl;
			cout << nim[i] << "\t" << kelas[i] << "\t" << nama[i] << "\t\t" << nilai[i] << "\t" << status[i] << endl;
		}
		
	}
	cout << endl;
}
int main(){
	sorting cek;
	cek.input();
	cek.proses();
	cek.output();
	getch();
}
