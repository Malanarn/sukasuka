#include <iostream>
#include <string>
using namespace std;

class Array{
	friend ostream& operator<<(ostream&, const Array&);
	friend istream& operator>>(istream&, Array&);
		public:
			Array();
			void cetak();
			void geser_kiri();
			void geser_kanan();
			
			private:
				char A[5];
				int posisi;		
};

Array::Array(){
	for(int i=0; i<5; i++)
	A[i]='o';		
}

void Array::cetak(){
	for(int i=0; i<5; i++)
	cout<<A[i]<<" ";
	
}

ostream& operator<<(ostream& out, const Array& x){
	for(int i=0; i<5; i++)
	out<<x.A[i]<<" ";
	out<<endl;
	return out;
}

istream& operator>>(istream& in, Array& x){
	int posisi;
	for(int posisi =1; posisi<=5; posisi++){
		cout<<"\nMasukkan Nilai Array posisi ke- :";
		in>>x.posisi;
		if(posisi >=0 && posisi <=5){cout<<"<Masukkan Elemen Array :" ;
		in>>x.A[posisi-1];
		}
	}
		return in;
}

void Array::geser_kanan(){
	int n=5;
	int temp=A[n-1];
	for(int i=n-1; i>=0; i--)
	A[i+1]=A[i];
	A[0]=temp;
}

void Array::geser_kiri(){
	int n=5;
	int temp =A[0];
	for(int i=0; i<n; i++)
	A[i]=A[i+1];
	A[n-1]=temp;
}

int main(int argc, char *argv[]){
	Array x;
	cin>>x;
	cout<<"\nIsi Array saat ini :";
	x.geser_kiri();
	cout<<"Isi Array setelah di geser kiri :"<<x;
	x.geser_kanan();
	cout<<"Isi Array Setelah di Geser kanan :"<<x;
	cout<<"\nUrutan Elemen pada indeksnya saat ini :"<<x;
	
	return 0;
	
}


