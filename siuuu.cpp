#include <iostream>
using namespace std;

#define maks 5

struct Mahasiswa {
    string nama;
    int nim;
    double ipk;
};

class Stack {
    friend ostream& operator<<(ostream&, const Stack&);
    
public:
    Stack();
    bool penuh();
    bool kosong();      
    void push(Mahasiswa);
    Mahasiswa pop();

private:
    Mahasiswa A[maks];
    int banyak;
};

ostream& operator<<(ostream& out, const Stack& s){
    out << "\n=== Daftar Mahasiswa (LIFO) ===\n";

    if (s.banyak == 0){
        out << "Stack kosong\n";
        return out;
    }

    for (int i = s.banyak - 1; i >= 0; i--){
        out << "Posisi[" << i << "]";
        if (i == s.banyak - 1) out << " <--- TOP";
        out << "\n";

        out << "  NIM  : " << s.A[i].nim  << "\n";
        out << "  Nama : " << s.A[i].nama << "\n";
        out << "  IPK  : " << s.A[i].ipk  << "\n\n";
    }

    return out;
}

Stack::Stack() {
    banyak = 0;
}

bool Stack::penuh() {
    return banyak == maks;
}

bool Stack::kosong() {
    return banyak == 0;
}

void Stack::push(Mahasiswa m){
    if(penuh()) {
        cout << "\nStack penuh!\n";
        return;
    }
    A[banyak] = m;
    banyak++;
    cout << "\nMahasiswa berhasil ditambah!\n";
}

Mahasiswa Stack::pop(){
    if(kosong()){
        cout << "\nStack kosong!\n";
        return {"", 0, 0};
    }
    banyak--;
    cout << "\nMahasiswa dihapus dari stack!\n";
    return A[banyak];
}

int main (){
    Stack s;
    int pil;

    do {
        cout << "\n=== DATA MAHASISWA ===\n";
        cout << "1. Tambah mahasiswa\n";
        cout << "2. Hapus mahasiswa \n";
        cout << "3. Tampilkan mahasiswa\n";
        cout << "4. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pil;

        switch(pil){
            case 1: {
                if (s.penuh()) {
                    cout << "Stack penuh!\n";
                    break;
                }

                Mahasiswa m;
                cout << "Masukkan nama : ";
                cin >> m.nama;
                cout << "Masukkan NIM  : ";
                cin >> m.nim;
                cout << "Masukkan IPK  : ";
                cin >> m.ipk;

                s.push(m);
                break;
            }

            case 2: {
                s.pop();
                break;
            }

            case 3: {
                cout << s;
                break;
            }

            case 4:
                cout << "Keluar...\n";
                break;

            default:
                cout << "Menu tidak valid!\n";
        }

    } while(pil != 4);

    return 0;
}

