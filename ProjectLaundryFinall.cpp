#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>      // Untuk setw dan manipulasi output
#include <limits>       // Untuk clear input buffer
using namespace std;

const int MAX = 100;
const int MAX_JENIS = 5;
const int MAX_PEOPLE = 100;

// Struct untuk daftar jenis pakaian dan harga per kg
struct JenisPakaian {
    string nama;
    int hargaPerKg;
};

// Struct untuk data laundry pelanggan
struct DataLaundry {
    string namaPelanggan;
    string jenisPakaian;
    float berat;
    int totalHarga;
};

// Array daftar jenis pakaian dan harga
JenisPakaian daftarJenis[MAX_JENIS] = {
    {"Baju", 7000},
    {"Celana", 8000},
    {"Jaket", 10000},
    {"Selimut", 12000},
    {"Karpet", 15000}
};

// Data laundry disimpan dalam array 1 dimensi
DataLaundry data[MAX];
int jumlahData = 0;

// Array multi dimensi untuk pengelompokan data berdasarkan jenis pakaian
DataLaundry dataByJenis[MAX_JENIS][MAX_PEOPLE];
int jumlahPerJenis[MAX_JENIS] = {0};

// Fungsi membersihkan input buffer agar tidak terjadi error saat input
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Fungsi mencari indeks jenis pakaian di daftarJenis
int cariIndeksJenis(const string& jenis) {
    for (int i = 0; i < MAX_JENIS; i++) {
        if (jenis == daftarJenis[i].nama) return i;
    }
    return -1;
}

// Fungsi menghitung total harga laundry berdasarkan berat dan jenis pakaian
void hitungTotal(DataLaundry &d) {
    int idx = cariIndeksJenis(d.jenisPakaian);
    if (idx != -1) {
        d.totalHarga = static_cast<int>(daftarJenis[idx].hargaPerKg * d.berat);
    } else {
        d.totalHarga = 0;
    }
}

// Fungsi validasi jenis pakaian (harus salah satu dari daftarJenis)
bool validasiJenisPakaian(const string& jenis) {
    return cariIndeksJenis(jenis) != -1;
}

// Fungsi input data laundry pelanggan (bisa input banyak sekaligus)
void inputData() {
    int jumlahInput;
    cout << "\n--- Input Data Laundry ---\n";
    cout << "Ingin input berapa data laundry? ";
    cin >> jumlahInput;
    clearInputBuffer();

    if (jumlahData + jumlahInput > MAX) {
        cout << "Data melebihi kapasitas maksimum. Sisa slot yang tersedia: " << (MAX - jumlahData) << "\n";
        return;
    }

    for (int i = 0; i < jumlahInput; i++) {
        cout << "\nData ke-" << (jumlahData + 1) << ":\n";
        string nama, jenis;
        float berat;

        cout << "Masukkan nama pelanggan: ";
        getline(cin, nama);

        do {
            cout << "Masukkan jenis cucian (Baju/Celana/Jaket/Selimut/Karpet): ";
            getline(cin, jenis);
            if (!validasiJenisPakaian(jenis)) {
                cout << "Jenis cucian tidak valid. Silakan coba lagi.\n";
            }
        } while (!validasiJenisPakaian(jenis));

        do {
            cout << "Masukkan berat cucian (kg, > 0): ";
            cin >> berat;
            if (berat <= 0) {
                cout << "Berat harus lebih dari 0. Silakan coba lagi.\n";
            }
            clearInputBuffer();
        } while (berat <= 0);

        // Simpan ke array
        data[jumlahData].namaPelanggan = nama;
        data[jumlahData].jenisPakaian = jenis;
        data[jumlahData].berat = berat;
        hitungTotal(data[jumlahData]);
        jumlahData++;

        cout << "Data ke-" << jumlahData << " berhasil ditambahkan!\n";
    }
}

// Fungsi swap untuk struct DataLaundry (pointer versi)
void swapData(DataLaundry *a, DataLaundry *b) {
    DataLaundry temp = *a;
    *a = *b;
    *b = temp;
}

// Fungsi Bubble Sort berdasarkan totalHarga (ascending/descending)
void bubbleSort(bool ascending) {
    for (int i = 0; i < jumlahData - 1; i++) {
        for (int j = 0; j < jumlahData - i - 1; j++) {
            if ((ascending && data[j].totalHarga > data[j + 1].totalHarga) ||
                (!ascending && data[j].totalHarga < data[j + 1].totalHarga)) {
                swapData(&data[j], &data[j + 1]);
            }
        }
    }
}

// Fungsi Selection Sort berdasarkan totalHarga (ascending/descending)
void selectionSort(bool ascending) {
    for (int i = 0; i < jumlahData - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < jumlahData; j++) {
            if ((ascending && data[j].totalHarga < data[idx].totalHarga) ||
                (!ascending && data[j].totalHarga > data[idx].totalHarga)) {
                idx = j;
            }
        }
        swapData(&data[i], &data[idx]);
    }
}

// Fungsi partition untuk Quick Sort (ascending/descending)
int partition(int low, int high, bool ascending) {
    int pivot = data[high].totalHarga;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if ((ascending && data[j].totalHarga <= pivot) ||
            (!ascending && data[j].totalHarga >= pivot)) {
            i++;
            swapData(&data[i], &data[j]);
        }
    }
    swapData(&data[i + 1], &data[high]);
    return i + 1;
}

// Fungsi Quick Sort berdasarkan totalHarga (ascending/descending)
void quickSort(int low, int high, bool ascending) {
    if (low < high) {
        int pi = partition(low, high, ascending);
        quickSort(low, pi - 1, ascending);
        quickSort(pi + 1, high, ascending);
    }
}

// Fungsi rekursif untuk menampilkan data mulai dari index tertentu
void tampilkanDataRekursif(int index) {
    if (index >= jumlahData) return;
    cout << left << setw(20) << data[index].namaPelanggan
         << setw(12) << data[index].jenisPakaian
         << setw(8) << fixed << setprecision(2) << data[index].berat
         << " Rp " << setw(10) << right << data[index].totalHarga << endl;
    tampilkanDataRekursif(index + 1);
}

// Fungsi cetak header tabel data laundry
void cetakHeaderTabel() {
    cout << left << setw(20) << "Nama Pelanggan"
         << setw(12) << "Jenis"
         << setw(8) << "Berat"
         << "   " << setw(12) << "Total Harga" << endl;
    cout << string(54, '=') << endl;
}

// Fungsi menampilkan seluruh data dengan opsi sorting
void tampilkanData() {
    if (jumlahData == 0) {
        cout << "Data kosong, silakan input terlebih dahulu.\n";
        return;
    }
    char pilih;
    cout << "Apakah data ingin diurutkan? (Y/N): ";
    cin >> pilih;
    if (pilih == 'Y' || pilih == 'y') {
        int metode;
        cout << "Pilih metode sorting:\n1. Bubble Sort\n2. Selection Sort\n3. Quick Sort\nPilihan: ";
        cin >> metode;
        int order;
        cout << "Urutan:\n1. Ascending\n2. Descending\nPilihan: ";
        cin >> order;
        bool ascending = (order == 1);

        switch (metode) {
            case 1: bubbleSort(ascending); break;
            case 2: selectionSort(ascending); break;
            case 3: quickSort(0, jumlahData - 1, ascending); break;
            default:
                cout << "Metode tidak valid, data tidak diurutkan.\n";
                break;
        }
    }
    cout << "\n--- Data Laundry Pelanggan ---\n";
    cetakHeaderTabel();
    tampilkanDataRekursif(0);
    cout << string(54, '=') << endl;

    // Tambahan summary total harga semua laundry
    int totalKeseluruhan = 0;
    for (int i = 0; i < jumlahData; i++) {
        totalKeseluruhan += data[i].totalHarga;
    }
    cout << "Total pendapatan laundry: Rp " << totalKeseluruhan << endl;
}

// Fungsi sequential search berdasarkan nama pelanggan
void sequentialSearch() {
    if (jumlahData == 0) {
        cout << "Data kosong, tidak bisa melakukan pencarian.\n";
        return;
    }
    clearInputBuffer();
    string cari;
    cout << "Masukkan nama pelanggan: ";
    getline(cin, cari);
    bool ditemukan = false;
    for (int i = 0; i < jumlahData; i++) {
        if (data[i].namaPelanggan == cari) {
            cout << "\nData ditemukan:\n";
            cetakHeaderTabel();
            cout << left << setw(20) << data[i].namaPelanggan
                 << setw(12) << data[i].jenisPakaian
                 << setw(8) << fixed << setprecision(2) << data[i].berat
                 << " Rp " << setw(10) << right << data[i].totalHarga << endl;
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) {
        cout << "Data tidak ditemukan.\n";
    }
}

// Fungsi binary search, mengasumsikan data sudah diurutkan ascending berdasarkan nama pelanggan
int binarySearch(const string& key) {
    int low = 0, high = jumlahData - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (data[mid].namaPelanggan == key) return mid;
        else if (data[mid].namaPelanggan < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// Wrapper binary search dengan sorting dulu berdasarkan nama pelanggan
void binarySearchWrapper() {
    if (jumlahData == 0) {
        cout << "Data kosong, tidak bisa melakukan pencarian.\n";
        return;
    }
    
    // Urutkan data ascending berdasarkan nama pelanggan menggunakan selection sort
    for (int i = 0; i < jumlahData - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < jumlahData; j++) {
            if (data[j].namaPelanggan < data[idx].namaPelanggan) {
                idx = j;
            }
        }
        swapData(&data[i], &data[idx]);
    }

    clearInputBuffer();
    string cari;
    cout << "Masukkan nama pelanggan (binary search): ";
    getline(cin, cari);

    int hasil = binarySearch(cari);
    if (hasil != -1) {
        cout << "\nData ditemukan:\n";
        cetakHeaderTabel();
        cout << left << setw(20) << data[hasil].namaPelanggan
             << setw(12) << data[hasil].jenisPakaian
             << setw(8) << fixed << setprecision(2) << data[hasil].berat
             << " Rp " << setw(10) << right << data[hasil].totalHarga << endl;
    } else {
        cout << "Data tidak ditemukan.\n";
    }
}

// Fungsi menyimpan data laundry ke file dengan format terstruktur
void simpanFile() {
    ofstream file("dataLaundry.txt");
    if (!file.is_open()) {
        cout << "Gagal membuka file untuk menyimpan data.\n";
        return;
    }
    file << "DATA_LAUNDRY\n"; // Header file
    file << jumlahData << endl;
    for (int i = 0; i < jumlahData; i++) {
        file << data[i].namaPelanggan << ';'
             << data[i].jenisPakaian << ';'
             << data[i].berat << ';'
             << data[i].totalHarga << '\n';
    }
    file << "END_DATA\n"; // Footer file
    file.close();
    cout << "Data berhasil disimpan ke file 'dataLaundry.txt'.\n";
}

// Fungsi membaca data laundry dari file dan langsung menampilkannya
void bacaFile() {
    ifstream file("dataLaundry.txt");
    if (!file.is_open()) {
        cout << "File dataLaundry.txt tidak ditemukan.\n";
        return;
    }

    string line;
    getline(file, line);
    if (line != "DATA_LAUNDRY") {
        cout << "Format file tidak sesuai.\n";
        file.close();
        return;
    }

    file >> jumlahData;
    clearInputBuffer();

    if (jumlahData > MAX) {
        cout << "Jumlah data dalam file melebihi kapasitas.\n";
        file.close();
        jumlahData = 0;
        return;
    }

    for (int i = 0; i < jumlahData; i++) {
        getline(file, line); // untuk menghapus newline sisa
        getline(file, line);
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);

        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos) {
            cout << "Format data baris ke-" << i + 1 << " salah.\n";
            jumlahData = i;
            break;
        }

        data[i].namaPelanggan = line.substr(0, pos1);
        data[i].jenisPakaian = line.substr(pos1 + 1, pos2 - pos1 - 1);
        data[i].berat = stof(line.substr(pos2 + 1, pos3 - pos2 - 1));
        data[i].totalHarga = stoi(line.substr(pos3 + 1));
    }

    getline(file, line);
    if (line != "END_DATA") {
        cout << "File tidak memiliki footer data yang valid.\n";
    }

    file.close();
    cout << "Data berhasil dibaca dari file.\n";

    // Langsung tampilkan data di terminal
    if (jumlahData > 0) {
        cout << "\n--- Data Laundry dari File ---\n";
        cetakHeaderTabel();
        for (int i = 0; i < jumlahData; i++) {
            cout << left << setw(20) << data[i].namaPelanggan
                 << setw(12) << data[i].jenisPakaian
                 << setw(8) << fixed << setprecision(2) << data[i].berat
                 << " Rp " << setw(10) << right << data[i].totalHarga << endl;
        }
        cout << string(54, '=') << endl;
    } else {
        cout << "Tidak ada data yang ditampilkan.\n";
    }
}


// Fungsi mengelompokkan data ke array 2D berdasarkan jenis pakaian
void kelompokkanData() {
    
    // Reset jumlah per jenis
    for (int i = 0; i < MAX_JENIS; i++) {
        jumlahPerJenis[i] = 0;
    }
    // Masukkan data ke array 2D berdasarkan indeks jenis pakaian
    for (int i = 0; i < jumlahData; i++) {
        int idx = cariIndeksJenis(data[i].jenisPakaian);
        if (idx != -1) {
            dataByJenis[idx][jumlahPerJenis[idx]] = data[i];
            jumlahPerJenis[idx]++;
        }
    }
}

void searchingmenu() {
    int pil;
    cout << "\n Mau Searching pakai metode apa?" << endl;
    cout << " 1. Sequential Search" << endl;
    cout << " 2. Binary Search" << endl;
    cout << " Pilihan : "; cin >> pil;

    switch (pil)
    {
    case 1:
        sequentialSearch();
        break;
    
    case 2:
        binarySearchWrapper();
        break;

    default:
        break;
    }
}

// Fungsi menu utama
void menu() {
    int pilihan;
    do {
        cout << "\n=== PROGRAM LAUNDRY ===\n";
        cout << "1. Input Data Laundry\n";
        cout << "2. Tampilkan Data Laundry\n";
        cout << "3. Searching\n";
        cout << "4. Simpan Data ke File\n";
        cout << "5. Baca Data dari File\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        switch (pilihan) {
            case 1: inputData(); 
            break;

            case 2: tampilkanData(); 
            break;

            case 3: searchingmenu(); 
            break;

            case 4: simpanFile(); 
            break;

            case 5: bacaFile(); 
            break;

            case 0: cout << "Terima kasih sudah menggunakan program ini.\n"; 
            break;

            default: cout << "Pilihan tidak valid, silakan coba lagi.\n"; 
            break;

        }
    } while (pilihan != 0);
}

int main() {
    cout << "Selamat datang di program Laundry\n";
    menu();
    return 0;
}
