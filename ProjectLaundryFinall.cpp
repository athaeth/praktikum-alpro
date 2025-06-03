#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>      
#include <limits>      
#include <vector>
#include <algorithm>   
using namespace std;

const int MAX = 100;
const int MAX_JENIS = 10;
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
    string tanggal; // 
};


// Array daftar jenis pakaian dan harga
JenisPakaian daftarJenis[MAX_JENIS] = {
    {"Baju", 7000},
    {"Celana", 8000},
    {"Jaket", 10000},
    {"Selimut", 12000},
    {"Karpet", 15000},
    {"Sprei", 11000},     
    {"Handuk", 9000},     
    {"Boneka", 13000},     
    {"Sepatu", 20000}     
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


string toLowerCase(string str) {
    for (char &c : str) {
        c = tolower(c);
    }
    return str;
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

int countExistingPelanggan() {
    int count = 0;
    vector<string> sudahAda;

    for (int i = 0; i < jumlahData; i++) {
        string lowerNama = toLowerCase(data[i].namaPelanggan);
        if (find(sudahAda.begin(), sudahAda.end(), lowerNama) == sudahAda.end()) {
            sudahAda.push_back(lowerNama);
            count++;
        }
    }

    return count;
}

// Fungsi input data laundry pelanggan (bisa input banyak sekaligus)
void simpanFile();
void inputData() {
ifstream file("dataLaundry.txt");
if (file.is_open()) {
    string line;
    jumlahData = 0;
    while (getline(file, line) && jumlahData < MAX) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);
        size_t pos4 = line.find(';', pos3 + 1);

        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos || pos4 == string::npos) {
            continue;
        }

        data[jumlahData].namaPelanggan = line.substr(0, pos1);
        data[jumlahData].jenisPakaian = line.substr(pos1 + 1, pos2 - pos1 - 1);
        data[jumlahData].berat = stof(line.substr(pos2 + 1, pos3 - pos2 - 1));
        data[jumlahData].totalHarga = stoi(line.substr(pos3 + 1, pos4 - pos3 - 1));
        data[jumlahData].tanggal = line.substr(pos4 + 1);
        jumlahData++;
    }
    file.close();
}
    int jumlahInput;
    cout << "\n--- Input Data Laundry ---\n";
    cout << "Ingin input berapa pelanggan? ";
    cin >> jumlahInput;
    clearInputBuffer();

    if (jumlahData + jumlahInput > MAX) {
        cout << "Data melebihi kapasitas maksimum. Sisa slot: " << (MAX - jumlahData) << "\n";
        return;
    }

    for (int i = 0; i < jumlahInput; i++) {
    cout << "\nPelanggan ke-" << (countExistingPelanggan() + i + 1) << ":\n";
        string nama, tanggal;
        cout << "Masukkan nama pelanggan: ";
        getline(cin, nama);
        cout << "Masukkan tanggal laundry (dd/mm/yyyy): ";
        getline(cin, tanggal);

        char lanjut;
        do {
            string jenis;
            float berat;

            do {
                cout << "Masukkan jenis cucian (Baju/Celana/Jaket/Selimut/Karpet/Sprei/Handuk/Boneka/Sepatu): ";
                getline(cin, jenis);
                if (!validasiJenisPakaian(jenis)) cout << "Jenis tidak valid.\n";
            } while (!validasiJenisPakaian(jenis));

            do {
                cout << "Masukkan berat cucian (kg, > 0): ";
                cin >> berat;
                clearInputBuffer();
            } while (berat <= 0);

            data[jumlahData].namaPelanggan = nama;
            data[jumlahData].jenisPakaian = jenis;
            data[jumlahData].berat = berat;
            data[jumlahData].tanggal = tanggal;
            hitungTotal(data[jumlahData]);
            jumlahData++;

            cout << "\nJenis cucian berhasil ditambahkan!\n";

            if (jumlahData >= MAX) {
                cout << "Slot data penuh. Tidak bisa menambahkan lagi.\n";
                break;
            }

            cout << "\nTambah jenis cucian lain untuk pelanggan ini? (Y/N): \n";
            cin >> lanjut;
            clearInputBuffer();

        } while (lanjut == 'Y' || lanjut == 'y');
    }

    simpanFile();
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
    int pivot = data[high].berat;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if ((ascending && data[j].berat <= pivot) ||
            (!ascending && data[j].berat >= pivot)) {
            i++;
            swapData(&data[i], &data[j]);
        }
    }
    swapData(&data[i + 1], &data[high]);
    return i + 1;
}


// Fungsi Quick Sort berdasarkan berat (ascending/descending)
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
    ifstream file("dataLaundry.txt");
    if (!file.is_open()) {
        cout << "File dataLaundry.txt tidak ditemukan.\n";
        return;
    }

    jumlahData = 0;
    string line;
    while (getline(file, line) && jumlahData < MAX) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);
        size_t pos4 = line.find(';', pos3 + 1);

        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos || pos4 == string::npos) {
            cout << "Format data salah. Baris dilewati.\n";
            continue;
        }

        data[jumlahData].namaPelanggan = line.substr(0, pos1);
        data[jumlahData].jenisPakaian = line.substr(pos1 + 1, pos2 - pos1 - 1);
        data[jumlahData].berat = stof(line.substr(pos2 + 1, pos3 - pos2 - 1));
        data[jumlahData].totalHarga = stoi(line.substr(pos3 + 1, pos4 - pos3 - 1));
        data[jumlahData].tanggal = line.substr(pos4 + 1);
        jumlahData++;
    }
    file.close();

    if (jumlahData == 0) {
        cout << "Tidak ada data untuk ditampilkan.\n";
        return;
    }

    char pilih;
    cout << "Apakah data ingin diurutkan? (Y/N): ";
    cin >> pilih;
    if (pilih == 'Y' || pilih == 'y') {
        int metode;
        cout << "Pilih metode sorting:\n1. Bubble\n2. Selection\n3. Quick\nPilihan: ";
        cin >> metode;
        int order;
        cout << "Urutan:\n1. Ascending\n2. Descending\nPilihan: ";
        cin >> order;
        bool ascending = (order == 1);

        switch (metode) {
            case 1: bubbleSort(ascending); break;
            case 2: selectionSort(ascending); break;
            case 3: quickSort(0, jumlahData - 1, ascending); break;
            default: cout << "Metode tidak valid.\n"; break;
        }
    }

    cout << "\n--- Data Laundry ---\n";
    cout << left << setw(20) << "Nama Pelanggan"
         << setw(12) << "Jenis"
         << setw(8) << "Berat"
         << " Rp " << setw(10) << "Total" 
         << "  Tanggal\n";
    cout << string(70, '=') << endl;

    for (int i = 0; i < jumlahData; i++) {
        cout << left << setw(20) << data[i].namaPelanggan
             << setw(12) << data[i].jenisPakaian
             << setw(8) << fixed << setprecision(2) << data[i].berat
             << " Rp " << setw(10) << data[i].totalHarga
             << "  " << data[i].tanggal << endl;
    }

    cout << string(70, '=') << endl;
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

    vector<int> hasil;
    for (int i = 0; i < jumlahData; i++) {
        if (toLowerCase(data[i].namaPelanggan) == toLowerCase(cari)) {
            hasil.push_back(i);
        }
    }

    if (!hasil.empty()) {
        cout << "\nData ditemukan (" << hasil.size() << " hasil):\n";
        cetakHeaderTabel();
        for (int idx : hasil) {
            cout << left << setw(20) << data[idx].namaPelanggan
                 << setw(12) << data[idx].jenisPakaian
                 << setw(8) << fixed << setprecision(2) << data[idx].berat
                 << " Rp " << setw(10) << right << data[idx].totalHarga
                 << "  " << data[idx].tanggal << endl;
        }
        cout << string(86, '=') << endl;
    } else {
        cout << "Data tidak ditemukan.\n";
    }
}



vector<int> binarySearch(const string& key) {
    vector<int> hasil;
    int low = 0, high = jumlahData - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (toLowerCase(data[mid].jenisPakaian) == toLowerCase(key)) {
            // Temukan semua kiri dan kanan dari mid
            hasil.push_back(mid);

            // Cek ke kiri
            int kiri = mid - 1;
            while (kiri >= 0 && data[kiri].jenisPakaian == key) {
                hasil.push_back(kiri);
                kiri--;
            }

            // Cek ke kanan
            int kanan = mid + 1;
            while (kanan < jumlahData && data[kanan].jenisPakaian == key) {
                hasil.push_back(kanan);
                kanan++;
            }

            break;  // Selesai
        } else if (toLowerCase(data[mid].jenisPakaian) < toLowerCase(key)){
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return hasil;
}


// Wrapper binary search dengan sorting dulu berdasarkan jenis pakaian
void binarySearchCucian() {
    if (jumlahData == 0) {
        cout << "Data kosong, tidak bisa melakukan pencarian.\n";
        return;
    }

    // Urutkan data berdasarkan jenis pakaian (Ascending)
    for (int i = 0; i < jumlahData - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < jumlahData; j++) {
            if (toLowerCase(data[j].jenisPakaian) < toLowerCase(data[idx].jenisPakaian)){
                idx = j;
            }
        }
        swapData(&data[i], &data[idx]);
    }

    clearInputBuffer();
    string cari;
    cout << "Masukkan jenis pakaian yang dicari: ";
    getline(cin, cari);

    vector<int> hasil = binarySearch(cari);

    if (!hasil.empty()) {
        cout << "\nData ditemukan (" << hasil.size() << " hasil):\n";
        cetakHeaderTabel();
        for (int idx : hasil) {
            cout << left << setw(20) << data[idx].namaPelanggan
                 << setw(12) << data[idx].jenisPakaian
                 << setw(8) << fixed << setprecision(2) << data[idx].berat
                 << " Rp " << setw(10) << right << data[idx].totalHarga << endl;
        }
        cout << string(54, '=') << endl;
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

    for (int i = 0; i < jumlahData; i++) {
        file << data[i].namaPelanggan << ';'
             << data[i].jenisPakaian << ';'
             << data[i].berat << ';'
             << data[i].totalHarga << ';'
             << data[i].tanggal << '\n';
    }

    file.close();
}



// Fungsi membaca data laundry dari file dan langsung menampilkannya
void bacaFile() {
    ifstream file("dataLaundry.txt");
    if (!file.is_open()) {
        cout << "File dataLaundry.txt tidak ditemukan.\n";
        return;
    }

    string line;
    jumlahData = 0;
    while (getline(file, line) && jumlahData < MAX) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);

        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos) {
            cout << "Format data baris ke-" << jumlahData + 1 << " salah. Lewati.\n";
            continue;
        }

        data[jumlahData].namaPelanggan = line.substr(0, pos1);
        data[jumlahData].jenisPakaian = line.substr(pos1 + 1, pos2 - pos1 - 1);
        data[jumlahData].berat = stof(line.substr(pos2 + 1, pos3 - pos2 - 1));
        data[jumlahData].totalHarga = stoi(line.substr(pos3 + 1));
        jumlahData++;
    }

    file.close();

    if (jumlahData == 0) {
        cout << "Tidak ada data valid dalam file.\n";
        return;
    }

    cout << "\n--- Data Laundry dari File ---\n";
    cetakHeaderTabel();
    for (int i = 0; i < jumlahData; i++) {
        cout << left << setw(20) << data[i].namaPelanggan
             << setw(12) << data[i].jenisPakaian
             << setw(8) << fixed << setprecision(2) << data[i].berat
             << " Rp " << setw(10) << right << data[i].totalHarga << endl;
    }
    cout << string(54, '=') << endl;
}

void editData() {
    clearInputBuffer();
    string nama;
    cout << "Masukkan nama pelanggan yang ingin diedit: ";
    getline(cin, nama);

    vector<int> indeksDitemukan;
    for (int i = 0; i < jumlahData; i++) {
        if (toLowerCase(data[i].namaPelanggan) == toLowerCase(nama)) {
            indeksDitemukan.push_back(i);
        }
    }

    if (indeksDitemukan.empty()) {
        cout << "Data tidak ditemukan.\n";
        return;
    }

    cout << "\nData ditemukan:\n";
    cetakHeaderTabel();
    for (int i = 0; i < indeksDitemukan.size(); i++) {
        int idx = indeksDitemukan[i];
        cout << "[" << i + 1 << "] "
             << left << setw(20) << data[idx].namaPelanggan
             << setw(12) << data[idx].jenisPakaian
             << setw(8) << fixed << setprecision(2) << data[idx].berat
             << " Rp " << setw(10) << right << data[idx].totalHarga
             << "  " << data[idx].tanggal << endl;
    }

    int pilihan;
    cout << "\nPilih nomor data yang ingin diedit (1-" << indeksDitemukan.size() << "): ";
    cin >> pilihan;
    clearInputBuffer();

    if (pilihan < 1 || pilihan > indeksDitemukan.size()) {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    int idxEdit = indeksDitemukan[pilihan - 1];

    cout << "Masukkan jenis cucian baru (Baju/Celana/Jaket/Selimut/Karpet/Sprei/Handuk/Boneka/Sepatu): ";
    getline(cin, data[idxEdit].jenisPakaian);

    cout << "Masukkan berat cucian baru (kg): ";
    cin >> data[idxEdit].berat;
    clearInputBuffer();

    cout << "Masukkan tanggal baru (dd/mm/yyyy): ";
    getline(cin, data[idxEdit].tanggal);

    hitungTotal(data[idxEdit]);
    simpanFile();
    cout << "Data berhasil diedit.\n";
}

void hapusData() {
    clearInputBuffer();
    string nama;
    cout << "Masukkan nama pelanggan yang ingin dihapus: ";
    getline(cin, nama);

    vector<int> indeksDitemukan;
    for (int i = 0; i < jumlahData; i++) {
        if (toLowerCase(data[i].namaPelanggan) == toLowerCase(nama)) {
            indeksDitemukan.push_back(i);
        }
    }

    if (indeksDitemukan.empty()) {
        cout << "Data tidak ditemukan.\n";
        return;
    }

    cout << "\nData ditemukan (" << indeksDitemukan.size() << " hasil):\n";
    cetakHeaderTabel();
    for (int i = 0; i < indeksDitemukan.size(); i++) {
        int idx = indeksDitemukan[i];
        cout << "[" << i + 1 << "] "
             << left << setw(20) << data[idx].namaPelanggan
             << setw(12) << data[idx].jenisPakaian
             << setw(8) << fixed << setprecision(2) << data[idx].berat
             << " Rp " << setw(10) << right << data[idx].totalHarga
             << "  " << data[idx].tanggal << endl;
    }

    int pilihan;
    if (indeksDitemukan.size() == 1) {
        cout << "Hanya ada satu data. Hapus? (1 = Ya, 0 = Batal): ";
        cin >> pilihan;
        if (pilihan == 1) {
            int idxHapus = indeksDitemukan[0];
            for (int i = idxHapus; i < jumlahData - 1; i++) {
                data[i] = data[i + 1];
            }
            jumlahData--;
            simpanFile();
            cout << "Data berhasil dihapus.\n";
        } else {
            cout << "Penghapusan dibatalkan.\n";
        }
    } else {
        cout << "\nIngin menghapus:\n";
        cout << "1. Salah satu data\n";
        cout << "2. Semua data milik \"" << nama << "\"\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        clearInputBuffer();

        if (pilihan == 1) {
            int pilihNomor;
            cout << "Masukkan nomor data yang ingin dihapus (1 - " << indeksDitemukan.size() << "): ";
            cin >> pilihNomor;
            clearInputBuffer();

            if (pilihNomor >= 1 && pilihNomor <= indeksDitemukan.size()) {
                int idxHapus = indeksDitemukan[pilihNomor - 1];
                for (int i = idxHapus; i < jumlahData - 1; i++) {
                    data[i] = data[i + 1];
                }
                jumlahData--;
                simpanFile();
                cout << "Data berhasil dihapus.\n";
            } else {
                cout << "Pilihan nomor tidak valid.\n";
            }

        } else if (pilihan == 2) {
            // Hapus semua dari belakang supaya indeks tidak rusak
            for (int i = indeksDitemukan.size() - 1; i >= 0; i--) {
                int idxHapus = indeksDitemukan[i];
                for (int j = idxHapus; j < jumlahData - 1; j++) {
                    data[j] = data[j + 1];
                }
                jumlahData--;
            }
            simpanFile();
            cout << "Semua data atas nama \"" << nama << "\" berhasil dihapus.\n";
        } else {
            cout << "Pilihan tidak valid.\n";
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
     binarySearchCucian();
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
        cout << "4. Edit Data\n";
        cout << "5. Hapus Data\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        switch (pilihan) {
            case 1: inputData(); break;
            case 2: tampilkanData(); break;
            case 3: searchingmenu(); break;
            case 4: editData(); break;
            case 5: hapusData(); break;
            case 0: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid.\n"; break;
        }
    } while (pilihan != 0);
}

int main() {
    cout << "Selamat datang di program Laundry\n";
    menu();
    return 0;
}
