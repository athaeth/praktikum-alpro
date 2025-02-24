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

float hitungHarga(string jenis, float berat) {
    if (jenis == "Baju") return berat * 10000;
    if (jenis == "Celana") return berat * 12000;
    if (jenis == "Jaket") return berat * 15000;
    return berat * 8000;
}

void inputData(Cucian laundry[], int &jumlah, int index) {
    if (index >= jumlah) return;

    cout << "\nData Cucian ke-" << index + 1 << endl;
    cout << "Masukkan ID Cucian: ";
    cin >> laundry[index].id;
    cin.ignore();

    cout << "Masukkan Nama Pelanggan: ";
    getline(cin, laundry[index].nama_pelanggan);

    cout << "Masukkan Jenis Pakaian (Baju/Celana/Jaket/Lainnya): ";
    getline(cin, laundry[index].jenis_pakaian);

    do {
        cout << "Masukkan Berat Pakaian (kg): ";
        cin >> laundry[index].berat;
        cin.ignore();

        if (laundry[index].berat >= 1 && laundry[index].berat <= 10) {
            laundry[index].total_harga = hitungHarga(laundry[index].jenis_pakaian, laundry[index].berat);
        } else {
            cout << "\nMaaf, berat harus antara 1 - 10 kg!\n";
        }
    } while (laundry[index].berat < 1 || laundry[index].berat > 10);

    inputData(laundry, jumlah, index + 1);
}

void tampilkanData(Cucian laundry[], int jumlah, int index = 0) {
    if (jumlah == 0) {
        cout << "\nBelum ada data cucian.\n";
        return;
    }
    if (index >= jumlah) return;

    cout << "ID: " << laundry[index].id << endl;
    cout << "Nama Pelanggan: " << laundry[index].nama_pelanggan << endl;
    cout << "Jenis Pakaian: " << laundry[index].jenis_pakaian << endl;
    cout << "Berat: " << laundry[index].berat << " kg" << endl;
    cout << "Total Harga: Rp " << laundry[index].total_harga << endl;
    cout << "-------------------------" << endl;

    tampilkanData(laundry, jumlah, index + 1);
}

int main() {
    Cucian laundry[100]; 
    int jumlah = 0;
    int pilihan;

    do {
        cout << "\n=== MENU LAUNDRY CIHUY ===\n";
        cout << "1. Input Data\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                cout << "Masukkan jumlah cucian: ";
                cin >> jumlah;
                cin.ignore();
                inputData(laundry, jumlah, 0);
                tampilkanData(laundry, jumlah);
                break;
            case 2:
                tampilkanData(laundry, jumlah);
                break;
            case 3:
                cout << "Terima kasih telah menggunakan Laundry Cihuy!\n";
                break;
            default:
                cout << "Pilihan tidak valid, silakan coba lagi.\n";
        }
    } while (pilihan != 3);

    return 0;
}
