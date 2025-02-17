#include <iostream>
#include <string>

using namespace std;
struct Cucian {
    int id;
    string nama_pelanggan;
    string jenis_pakaian;
    float berat;
    float total_harga;
};
int main() {
   
    Cucian laundry[100]; 
    cout << " === SELAMAT DATANG DI LAUNDRY CIHUY === " << endl;
    for (int i = 0; i < 100; i++) {
        cout << "Masukkan ID Cucian: ";
        cin >> laundry[i].id; 
        cin.ignore();

        cout << "Masukkan Nama Pelanggan: ";
        getline(cin, laundry[i].nama_pelanggan);

        cout << "Masukkan Jenis Pakaian: ";
        getline(cin, laundry[i].jenis_pakaian);
        
        do {

            cout << "Masukkan Berat Pakaian (kg): ";
            cin >> laundry[i].berat;
            cin.ignore();
            
            if (laundry[i].berat >= 1 || laundry[i].berat <= 10 ){
                laundry[i].total_harga = laundry[i].berat * 1000;
            } else {
                cout << "\nMaaf kami hanya bisa melayani cucian dengan berat pakian 1 - 10 Kg saja";
            }
        } while (laundry[i].berat > 10);

    }
    cout << "\nData Cucian:\n";
    for (int i = 0; i < 2; i++) {
        cout << "ID: " << laundry[i].id << endl;
        cout << "Nama Pelanggan: " << laundry[i].nama_pelanggan << endl;
        cout << "Jenis Pakaian: " << laundry[i].jenis_pakaian << endl;
        cout << "Berat: " << laundry[i].berat << " kg" << endl;
        cout << "Total harga: " << laundry[i].total_harga << endl;
        cout << "-------------------------" << endl;
    }

    return 0;
}