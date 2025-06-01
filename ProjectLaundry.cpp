#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Cucian {
    int id;
    string nama_pelanggan;
    string jenis_pakaian;
    float berat;
    float total_harga;
};

const float HARGA_PER_KG = 7000.0;

void inputData(Cucian *laundry, int jumlah, int idxAwal) {
    for (int i = 0; i < jumlah; i++) {
        laundry[i + idxAwal].id = idxAwal + i + 1;
        cout << "Data ke-" << i + 1 << endl;
        cout << "Nama Pelanggan: ";
        cin.ignore();
        getline(cin, laundry[i + idxAwal].nama_pelanggan);
        cout << "Jenis Pakaian: ";
        getline(cin, laundry[i + idxAwal].jenis_pakaian);
        cout << "Berat (kg): ";
        cin >> laundry[i + idxAwal].berat;
        laundry[i + idxAwal].total_harga = laundry[i + idxAwal].berat * HARGA_PER_KG;
    }
}

void tampilkanData(Cucian *laundry, int jumlah) {
    if (jumlah == 0) {
        cout << "Belum ada data cucian.\n";
        return;
    }

    cout << "\n=== DATA CUCIAN ===\n";
    for (int i = 0; i < jumlah; i++) {
        cout << "ID: " << laundry[i].id << endl;
        cout << "Nama: " << laundry[i].nama_pelanggan << endl;
        cout << "Jenis Pakaian: " << laundry[i].jenis_pakaian << endl;
        cout << "Berat: " << laundry[i].berat << " kg" << endl;
        cout << "Total Harga: Rp" << laundry[i].total_harga << endl;
        cout << "--------------------------\n";
    }
}

int sequentialSearch(Cucian *laundry, int jumlah, string keyword) {
    for (int i = 0; i < jumlah; i++) {
        if (laundry[i].nama_pelanggan == keyword) {
            return i;
        }
    }
    return -1;
}

int binarySearch(Cucian *laundry, int kiri, int kanan, string keyword) {
    while (kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;
        if (laundry[tengah].nama_pelanggan == keyword)
            return tengah;
        else if (laundry[tengah].nama_pelanggan < keyword)
            kiri = tengah + 1;
        else
            kanan = tengah - 1;
    }
    return -1;
}

void bubbleSort(Cucian *laundry, int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (laundry[j].nama_pelanggan > laundry[j + 1].nama_pelanggan) {
                swap(laundry[j], laundry[j + 1]);
            }
        }
    }
}

void selectionSort(Cucian *laundry, int jumlah) {
    for (int i = 0; i < jumlah - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < jumlah; j++) {
            if (laundry[j].nama_pelanggan < laundry[minIdx].nama_pelanggan) {
                minIdx = j;
            }
        }
        swap(laundry[i], laundry[minIdx]);
    }
}

void insertionSort(Cucian *laundry, int jumlah) {
    for (int i = 1; i < jumlah; i++) {
        Cucian key = laundry[i];
        int j = i - 1;
        while (j >= 0 && laundry[j].nama_pelanggan > key.nama_pelanggan) {
            laundry[j + 1] = laundry[j];
            j--;
        }
        laundry[j + 1] = key;
    }
}

void merge(Cucian *laundry, int kiri, int tengah, int kanan) {
    int n1 = tengah - kiri + 1;
    int n2 = kanan - tengah;

    Cucian *L = new Cucian[n1];
    Cucian *R = new Cucian[n2];

    for (int i = 0; i < n1; i++)
        L[i] = laundry[kiri + i];
    for (int j = 0; j < n2; j++)
        R[j] = laundry[tengah + 1 + j];

    int i = 0, j = 0, k = kiri;
    while (i < n1 && j < n2) {
        if (L[i].nama_pelanggan <= R[j].nama_pelanggan)
            laundry[k++] = L[i++];
        else
            laundry[k++] = R[j++];
    }

    while (i < n1)
        laundry[k++] = L[i++];
    while (j < n2)
        laundry[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(Cucian *laundry, int kiri, int kanan) {
    if (kiri < kanan) {
        int tengah = (kiri + kanan) / 2;
        mergeSort(laundry, kiri, tengah);
        mergeSort(laundry, tengah + 1, kanan);
        merge(laundry, kiri, tengah, kanan);
    }
}

int partition(Cucian *laundry, int low, int high) {
    string pivot = laundry[high].nama_pelanggan;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (laundry[j].nama_pelanggan <= pivot) {
            i++;
            swap(laundry[i], laundry[j]);
        }
    }
    swap(laundry[i + 1], laundry[high]);
    return i + 1;
}

void quickSort(Cucian *laundry, int low, int high) {
    if (low < high) {
        int pi = partition(laundry, low, high);
        quickSort(laundry, low, pi - 1);
        quickSort(laundry, pi + 1, high);
    }
}

void shellSort(Cucian *laundry, int jumlah) {
    for (int gap = jumlah / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < jumlah; i++) {
            Cucian temp = laundry[i];
            int j;
            for (j = i; j >= gap && laundry[j - gap].nama_pelanggan > temp.nama_pelanggan; j -= gap)
                laundry[j] = laundry[j - gap];
            laundry[j] = temp;
        }
    }
}

void simpanKeFile(Cucian *laundry, int jumlah) {
    ofstream file("laundry.txt");
    for (int i = 0; i < jumlah; i++) {
        file << laundry[i].id << "," << laundry[i].nama_pelanggan << ","
             << laundry[i].jenis_pakaian << "," << laundry[i].berat << ","
             << laundry[i].total_harga << endl;
    }
    file.close();
    cout << "Data berhasil disimpan ke file.\n";
}

int loadDataDariFile(Cucian *laundry, int maxData) {
    ifstream file("laundry.txt");
    string line;
    int count = 0;

    while (getline(file, line) && count < maxData) {
        stringstream ss(line);
        string token;

        getline(ss, token, ',');
        laundry[count].id = stoi(token);

        getline(ss, laundry[count].nama_pelanggan, ',');

        getline(ss, laundry[count].jenis_pakaian, ',');

        getline(ss, token, ',');
        laundry[count].berat = stof(token);

        getline(ss, token, ',');
        laundry[count].total_harga = stof(token);

        count++;
    }

    file.close();
    cout << "Data berhasil dibaca dari file.\n";
    return count;
}
int main() {
    const int MAX = 100;
    Cucian laundry[MAX];
    int jumlahData = 0;

    int pilihan;
    do {
        cout << "\n==== MENU LAUNDRY ====\n";
        cout << "1. Input Data Cucian\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Cari Data\n";
        cout << "4. Sorting Data\n";
        cout << "5. Simpan Data ke File\n";
        cout << "6. Baca Data dari File\n";
        cout << "7. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                int n;
                cout << "Jumlah data yang ingin ditambahkan: ";
                cin >> n;
                if (jumlahData + n > MAX) {
                    cout << "Kapasitas penuh!\n";
                } else {
                    inputData(laundry, n, jumlahData);
                    jumlahData += n;
                }
                break;
            }
            case 2:
                tampilkanData(laundry, jumlahData);
                break;
            case 3: {
                string keyword;
                cout << "Masukkan nama pelanggan yang dicari: ";
                cin.ignore();
                getline(cin, keyword);

                int hasil = sequentialSearch(laundry, jumlahData, keyword);
                if (hasil != -1) {
                    cout << "Data ditemukan:\n";
                    cout << "Nama: " << laundry[hasil].nama_pelanggan << ", Jenis: " << laundry[hasil].jenis_pakaian
                         << ", Berat: " << laundry[hasil].berat << " kg, Total: Rp" << laundry[hasil].total_harga << endl;
                } else {
                    cout << "Data tidak ditemukan.\n";
                }
                break;
            }
            case 4: {
                int metodeSort;
                cout << "Metode sorting:\n1. Bubble\n2. Selection\n3. Insertion\n4. Merge\n5. Quick\n6. Shell\nPilihan: ";
                cin >> metodeSort;

                switch (metodeSort) {
                    case 1: bubbleSort(laundry, jumlahData); break;
                    case 2: selectionSort(laundry, jumlahData); break;
                    case 3: insertionSort(laundry, jumlahData); break;
                    case 4: mergeSort(laundry, 0, jumlahData - 1); break;
                    case 5: quickSort(laundry, 0, jumlahData - 1); break;
                    case 6: shellSort(laundry, jumlahData); break;
                    default: cout << "Pilihan tidak valid!\n";
                }
                cout << "Data berhasil disorting.\n";
                break;
            }
            case 5:
                simpanKeFile(laundry, jumlahData);
                break;
            case 6:
                jumlahData = loadDataDariFile(laundry, MAX);
                break;
            case 7:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 7);

    return 0;
}

