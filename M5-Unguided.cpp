#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Struktur Data Untuk Setiap Node
struct Student {
    string nim;
    string name;
    int nilai;
    Student(string nim, string name, int nilai) : nim(nim), name(name), nilai(nilai) {}
};

// Class HashMap
class HashMap {
private:
    static const int TABLE_SIZE = 10; // Ukuran tabel hash
    vector<Student*> table[TABLE_SIZE];

public:
    // Fungsi Hash Sederhana
    int hashFunc(string key) {
        int hash_val = 0;
        for (char c : key) {
            hash_val += c;
        }
        return hash_val % TABLE_SIZE;
    }

    // Tambah data mahasiswa baru
    void insert(string nim, string name, int nilai) {
        int hash_val = hashFunc(nim);
        table[hash_val].push_back(new Student(nim, name, nilai));
    }

    // Hapus data mahasiswa
    void remove(string nim) {
        int hash_val = hashFunc(nim);
        for (auto it = table[hash_val].begin(); it != table[hash_val].end(); it++) {
            if ((*it)->nim == nim) {
                table[hash_val].erase(it);
                return;
            }
        }
    }

    // Cari data mahasiswa berdasarkan NIM
    Student* searchByNIM(string nim) {
        int hash_val = hashFunc(nim);
        for (auto student : table[hash_val]) {
            if (student->nim == nim) {
                return student;
            }
        }
        return nullptr; // Mengembalikan nullptr jika tidak ditemukan
    }

    // Cari data mahasiswa berdasarkan rentang nilai (80-90)
    vector<Student*> searchByRange(int min, int max) {
        vector<Student*> result;
        for (int i = 0; i < TABLE_SIZE; i++) {
            for (auto student : table[i]) {
                if (student->nilai >= min && student->nilai <= max) {
                    result.push_back(student);
                }
            }
        }
        return result;
    }
};

int main() {
    HashMap mahasiswa_map;
    int choice;
    string nim, name;
    int nilai;
    while (true) {
        cout << "Menu:\n";
        cout << "1. Tambah data mahasiswa\n";
        cout << "2. Hapus data mahasiswa\n";
        cout << "3. Cari data mahasiswa berdasarkan NIM\n";
        cout << "4. Cari data mahasiswa berdasarkan rentang nilai (80-90)\n";
        cout << "5. Keluar\n";
        cout << "Pilih: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Masukkan NIM: ";
                cin >> nim;
                cout << "Masukkan nama: ";
                cin.ignore(); // Clear input buffer
                getline(cin, name);
                cout << "Masukkan nilai: ";
                cin >> nilai;
                mahasiswa_map.insert(nim, name, nilai);
                break;
            case 2:
                cout << "Masukkan NIM yang akan dihapus: ";
                cin >> nim;
                mahasiswa_map.remove(nim);
                break;
            case 3:
                cout << "Masukkan NIM yang dicari: ";
                cin >> nim;
                {
                    Student* student = mahasiswa_map.searchByNIM(nim);
                    if (student != nullptr) {
                        cout << "Nama: " << student->name << ", NIM: " << student->nim << ", Nilai: " << student->nilai << endl;
                    } else {
                        cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan.\n";
                    }
                }
                break;
            case 4:
                cout << "Mahasiswa dengan nilai antara 80 - 90:\n";
                {
                    vector<Student*> students = mahasiswa_map.searchByRange(80, 90);
                    if (students.empty()) {
                        cout << "Tidak ada mahasiswa dengan nilai dalam rentang tersebut.\n";
                    } else {
                        for (const auto& student : students) {
                            cout << "Nama: " << student->name << ", NIM: " << student->nim << ", Nilai: " << student->nilai << endl;
                        }
                    }
                }
                break;
            case 5:
                cout << "Terima kasih!\n";
                return 0;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    }
}