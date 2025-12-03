#include <iostream>
#include <string>
using namespace std;

struct KTP {
    string NIK;
    string nama;
    string ttl;
    KTP* next;
};

KTP* front = nullptr;
KTP* rear = nullptr;


bool isEmpty() {
    return (front == nullptr);
}


void enqueue(KTP* ktpBaru) {
    if (isEmpty()) {
        front = rear = ktpBaru;
        rear->next = front; 
    } else {
        rear->next = ktpBaru;
        rear = ktpBaru;
        rear->next = front; 
    }
    cout << "Data KTP berhasil ditambahkan ke antrian.\n";
}


void dequeue() {
    if (isEmpty()) {
        cout << "Antrian kosong, tidak ada KTP untuk dilayani.\n";
        return;
    }

    KTP* temp = front;

    cout << "\nMelayani KTP berikut:\n";
    cout << "NIK   : " << front->NIK << endl;
    cout << "Nama  : " << front->nama << endl;
    cout << "TTL   : " << front->ttl << endl;
    cout << "-------------------------\n";

    if (front == rear) {
        
        front = rear = nullptr;
    } else {
        front = front->next;
        rear->next = front;
    }

    delete temp;
}


void tampilkanAntrian() {
    if (isEmpty()) {
        cout << "Antrian kosong.\n";
        return;
    }

    cout << "\nDaftar KTP dalam antrian:\n";

    KTP* current = front;
    do {
        cout << "NIK   : " << current->NIK << endl;
        cout << "Nama  : " << current->nama << endl;
        cout << "TTL   : " << current->ttl << endl;
        cout << "-------------------------\n";
        current = current->next;
    } while (current != front);
}

int main() {
    int pilihan;

    do {
        cout << "\n Program Antrian KTP \n";
        cout << "1. Tambah KTP\n";
        cout << "2. Layani KTP\n";
        cout << "3. Lihat Daftar KTP\n";
        cout << "4. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            KTP* ktpBaru = new KTP;
            cout << "Masukkan NIK   : ";
            getline(cin, ktpBaru->NIK);
            cout << "Masukkan Nama  : ";
            getline(cin, ktpBaru->nama);
            cout << "Masukkan TTL   : ";
            getline(cin, ktpBaru->ttl);
            ktpBaru->next = nullptr;

            enqueue(ktpBaru);

        } else if (pilihan == 2) {
            dequeue();

        } else if (pilihan == 3) {
            tampilkanAntrian();

        } else if (pilihan == 4) {
            cout << "Keluar dari program...\n";

        } else {
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilihan != 4);

    return 0;
}

