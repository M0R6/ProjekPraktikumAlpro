#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// ==============================================
// =============== STRUCTURE DATA ===============
// ==============================================
struct Film{
   int id;
   string judul;
   string genre;
   int harga;
};

struct Teater{
   string namaTeater;
   string lokasi;
   int kapasitas;
   int baris;
   int kolom;
};

struct Kursi {
   string nomorKursi;
   bool isBooked;
};

struct JadwalTayang {
   int idJadwal;
   int idFilm;
   string namaTeater;
   string waktuTampil;
   
   Kursi denahKursi[10][10]; 
   int totalBaris;
   int totalKolom;
};

struct Pengguna{
   string username;
   string password;
};

struct Admins{
   string username;
   string password;
};

struct Pesanan{
   string namaPelanggan;
   string judulFilm;
   string jadwalTayang;
   string idkursi; 
};

// ===================================================
// =============== PROTOTYPE FUNCTIONS ===============
// ===================================================

string toLower(string str){
   for(size_t i = 0; i < str.length(); i++){
      str[i] = tolower(str[i]);
   }
   return str;
}

void ulangi(bool *ulang);
void cariFilm(Film film[], int jumlahFilm, string keyword, char tipe);
void MenuAdmin(Film film[], int *jumlahFilm, Pengguna pengguna[], int *jumlahPengguna, Pesanan pesanan[], int *jumlahPesanan, Admins admin[], int *jumlahAdmin, Teater teater[], int *jumlahTeater);
void AdminMenuFilm(Film film[], int *jumlahFilm);
void AdminMenuTeater(Teater teater[], int *jumlahTeater);
void TambahFilm(Film film[], int *jumlahFilm);
void EditFilm(Film film[], int *jumlahFilm);
void HapusFilm(Film film[], int *jumlahFilm);
void LihatDaftarTeater(Teater teater[], int *jumlahTeater);
void TambahTeater(Teater teater[], int *jumlahTeater);
void EditTeater(Teater teater[], int *jumlahTeater);
void HapusTeater(Teater teater[], int *jumlahTeater);
void AdminMenuJadwalTayang(JadwalTayang jadwal[], int *jumlahJadwal, Film film[], int jumlahFilm, Teater teater[], int jumlahTeater);
void LihatDaftarJadwal(JadwalTayang jadwal[], int jumlahJadwal, Film film[], int jumlahFilm);
void TambahJadwal(JadwalTayang jadwal[], int *jumlahJadwal, Film film[], int jumlahFilm, Teater teater[], int jumlahTeater);
void HapusJadwal(JadwalTayang jadwal[], int *jumlahJadwal);
bool isJadwalBentrok(JadwalTayang jadwal[], int jumlahJadwal, string namaTeater, string waktuTampil);
void simpanSemuaJadwal(JadwalTayang jadwal[], int jumlahJadwal);
void RegisterCustomer(Pengguna pengguna[], int *jumlahPengguna);
void MenuPengguna(Film film[], int jumlahFilm, Pengguna pengguna[], int *jumlahPengguna);
void PesanTiket(Film film[], int jumlahFilm, Pengguna inputCustomer, Pesanan pesanan[], int *jumlahPesanan, JadwalTayang jadwal[], int jumlahJadwal);
void BatalPesanTiket(Pesanan pesanan[], int *jumlahPesanan, JadwalTayang jadwal[], int jumlahJadwal, Film film[], int jumlahFilm, Pengguna inputCustomer);
void TampilDaftarFilm(Film film[], int jumlahFilm);
void MenuCariFilm(Film film[], int jumlahFilm);
string cvJadwal(int jadwal);
void loadData(Film film[], int *jumlahFilm, Pengguna pengguna[], int *jumlahPengguna, Pesanan pesanan[], int *jumlahPesanan, Admins admin[], int *jumlahAdmin, Teater teater[], int *jumlahTeater, JadwalTayang jadwal[], int *jumlahJadwal);

// ===============================================
// =============== ADMIN FUNCTIONS ===============
// ===============================================

void MenuAdmin(Film film[], int *jumlahFilm, Pengguna pengguna[], int *jumlahPengguna, Pesanan pesanan[], int *jumlahPesanan, Admins admin[], int *jumlahAdmin, Teater teater[], int *jumlahTeater, JadwalTayang jadwalTayang[], int *jumlahJadwalTayang){
   system("cls"); 
   int pilih;
   char ulang;
   Admins inputAdmin; 
   cout << "\n=== LOGIN ADMIN ===\n";
   cout << "Username: "; cin >> inputAdmin.username;
   cout << "Password: "; cin >> inputAdmin.password;
   
   bool statusLogin = false;
   for(int i = 0; i < *jumlahAdmin; i++){
      if(admin[i].username == inputAdmin.username && admin[i].password == inputAdmin.password){
         statusLogin = true;
         cout << "Login berhasil! Selamat datang, " << inputAdmin.username << "!" << endl;
         system("pause");
         break;
      }
   }

   if(statusLogin){
      int totalTransaksi = 0, totalPendapatan = 0;
      do{
         system("cls");
         cout << "===============================\n";
         cout << "         MENU ADMIN            \n";
         cout << "===============================\n";
         cout << "1. Menu Film\n";
         cout << "2. Menu Teater\n";
         cout << "3. Menu Jadwal Tayang\n";
         cout << "4. Lihat Laporan Transaksi\n";
         cout << "5. Logout\n";
         cout << "Pilih menu (1-5): ";
         cin >> pilih;
         switch(pilih){
            case 1:
               AdminMenuFilm(film, jumlahFilm);
               break;
            case 2:
               AdminMenuTeater(teater, jumlahTeater);
               break;
            case 3:
               AdminMenuJadwalTayang(jadwalTayang, jumlahJadwalTayang, film, *jumlahFilm, teater, *jumlahTeater);
               break;
            case 4:
               system("cls");
               cout << "Laporan Transaksi:\n";
               cout << left << setw(5) << "No" << setw(30) << "Nama Pelanggan" << setw(30) << "Judul Film" << setw(20) << "Jadwal Tayang" << setw(15) << "ID Kursi" << "\n";
               totalTransaksi = 0;
               totalPendapatan = 0;
               
               for(int i = 0; i < *jumlahPesanan; i++){
                  cout << left << setw(5) << i+1 << setw(30) << pesanan[i].namaPelanggan << setw(30) << pesanan[i].judulFilm << setw(20) << pesanan[i].jadwalTayang << setw(15) << pesanan[i].idkursi << "\n";
                  totalTransaksi++;
                  int hargaFilmTerpilih = 0;
                  for(int j = 0; j < *jumlahFilm; j++){
                     if(film[j].judul == pesanan[i].judulFilm){
                        hargaFilmTerpilih = film[j].harga;
                        break;
                     }
                  }
                  totalPendapatan += hargaFilmTerpilih;
               }
               cout << "\nTotal Transaksi: " << totalTransaksi << endl;
               cout << "Total Pendapatan: " << totalPendapatan << endl;
               system("pause");
               break;
            case 5:
               cout << "Logout berhasil!\n";
               system("pause");
               return;
            default:
               cout << "Menu yang anda pilih tidak tersedia!" << endl;
               system("pause");
               break;
         }
         
         if(pilih >= 1 && pilih <= 4){
            cout << "\nApakah Anda ingin kembali ke menu admin? (y/n): ";
            cin >> ulang;
         }
         
      } while(pilih != 5 && (ulang == 'y' || ulang == 'Y'));
   } else {
      cout << "Login gagal! Pastikan username dan password benar." << endl;
      system("pause");
   }
}

void AdminMenuJadwalTayang(JadwalTayang jadwal[], int *jumlahJadwal, Film film[], int jumlahFilm, Teater teater[], int jumlahTeater) {
   int pilih;
   do {
      system("cls");
      LihatDaftarJadwal(jadwal, *jumlahJadwal, film, jumlahFilm);
      cout << "===============================\n";
      cout << "     MENU JADWAL TAYANG        \n";
      cout << "===============================\n";
      cout << "1. Tambah Jadwal Tayang\n";
      cout << "2. Hapus Jadwal Tayang\n";
      cout << "3. Kembali ke Menu Admin\n";
      cout << "Pilih menu (1-3): ";
      cin >> pilih;
      switch (pilih) {
         case 1:
            TambahJadwal(jadwal, jumlahJadwal, film, jumlahFilm, teater, jumlahTeater);
            break;
         case 2:
            HapusJadwal(jadwal, jumlahJadwal);
            system("pause");
            break;
         case 3:
            return;
         default:
            cout << "Menu yang anda pilih tidak tersedia!" << endl;
            system("pause");
            break;
      }
   } while (pilih != 3);
}

void LihatDaftarJadwal(JadwalTayang jadwal[], int jumlahJadwal, Film film[], int jumlahFilm) {
   system("cls");
   cout << "=== JADWAL FILM ON AIR ===\n";
   if(jumlahJadwal == 0){
      cout << "Belum ada data jadwal tayang." << endl;
      system("pause");
      return;
   }
   cout << left << setw(5) << "ID" << setw(25) << "Judul Film" << setw(20) << "Teater" << setw(15) << "Jam Tayang" << "\n";
   cout << string(65, '=') << endl;
   
   for(int i = 0; i < jumlahJadwal; i++){
      string judulFilm = "Tidak Diketahui";
      for(int j = 0; j < jumlahFilm; j++){
         if(film[j].id == jadwal[i].idFilm){
            judulFilm = film[j].judul;
            break;
         }
      }
      
      cout << left << setw(5) << jadwal[i].idJadwal 
           << setw(25) << judulFilm 
           << setw(20) << jadwal[i].namaTeater 
           << setw(15) << jadwal[i].waktuTampil << endl;
   }
   cout << string(65, '=') << endl;
}

bool isJadwalBentrok(JadwalTayang jadwal[], int jumlahJadwal, string namaTeater, string waktuTampil) {
   for(int i = 0; i < jumlahJadwal; i++){
      if(jadwal[i].namaTeater == namaTeater && jadwal[i].waktuTampil == waktuTampil){
         return true; 
      }
   }
   return false;
}

void TambahJadwal(JadwalTayang jadwal[], int *jumlahJadwal, Film film[], int jumlahFilm, Teater teater[], int jumlahTeater) {
   system("cls");
   if(jumlahFilm == 0 || jumlahTeater == 0){
      cout << "Belum bisa ditambahkan. Pastikan data Film dan Teater sudah terisi terlebih dahulu!" << endl;
      system("pause");
      return;
   }

   JadwalTayang newJadwal;
   newJadwal.idJadwal = *jumlahJadwal + 1;

   int pilihanFilm;
   cout << "=== DAFTAR FILM ===\n";
   for(int i = 0; i < jumlahFilm; i++){
      cout << film[i].id << ". " << film[i].judul << endl;
   }
   cout << "Pilih ID Film: "; cin >> pilihanFilm;
   newJadwal.idFilm = pilihanFilm;

   int pilihanTeater;
   cout << "\n=== DAFTAR TEATER ===\n";
   for(int i = 0; i < jumlahTeater; i++){
      cout << i + 1 << ". " << teater[i].namaTeater << " (" << teater[i].lokasi << ")\n";
   }
   cout << "Pilih ID Teater: "; cin >> pilihanTeater;
   
   Teater teaterTerpilih = teater[pilihanTeater - 1];
   newJadwal.namaTeater = teaterTerpilih.namaTeater;
   newJadwal.totalBaris = teaterTerpilih.baris;
   newJadwal.totalKolom = teaterTerpilih.kolom;

   int jam;
   cout << "\n=== PILIH JAM TAYANG ===\n";
   cout << "1. 10.00 AM\n2. 01.00 PM\n3. 04.00 PM\n4. 07.00 PM\nPilih (1-4): "; cin >> jam;
   
   newJadwal.waktuTampil = cvJadwal(jam);

   if(isJadwalBentrok(jadwal, *jumlahJadwal, newJadwal.namaTeater, newJadwal.waktuTampil)){
      cout << "\n[EROR] Gagal membuat jadwal! " << newJadwal.namaTeater << " sudah digunakan untuk jam " << newJadwal.waktuTampil << ".\n";
      system("pause");
      return;
   }

   for(int i = 0; i < newJadwal.totalBaris; i++){
      char hurufBaris = 'A' + i;
      for(int j = 0; j < newJadwal.totalKolom; j++){
         newJadwal.denahKursi[i][j].nomorKursi = hurufBaris + to_string(j + 1);
         newJadwal.denahKursi[i][j].isBooked = false;
      }
   }

   jadwal[*jumlahJadwal] = newJadwal;
   (*jumlahJadwal)++;
   simpanSemuaJadwal(jadwal, *jumlahJadwal);

   cout << "\nJadwal film berhasil dibuat dan status kursi diinisialisasi!\n";
   system("pause");
}

void HapusJadwal(JadwalTayang jadwal[], int *jumlahJadwal) {
   int cari;
   if(jumlahJadwal == nullptr || *jumlahJadwal <= 0){
      cout << "Belum ada data jadwal tayang." << endl;
      return;
   }
   cout << "ID jadwal yang ingin dihapus: "; cin >> cari;

   bool found = false;
   int index = 0;
   for(int i = 0; i < *jumlahJadwal; i++){
      if(jadwal[i].idJadwal == cari){
         found = true;
         continue;
      }
      jadwal[index] = jadwal[i];
      index++;
   }

   if(!found){
      cout << "Jadwal dengan ID " << cari << " tidak ditemukan." << endl;
      return;
   }

   (*jumlahJadwal)--;
   simpanSemuaJadwal(jadwal, *jumlahJadwal);
   cout << "Jadwal tayang berhasil dihapus!" << endl;
}

void simpanSemuaJadwal(JadwalTayang jadwal[], int jumlahJadwal) {
   ofstream fileJadwal("jadwals.txt", ios::out);
   for(int i = 0; i < jumlahJadwal; i++){
      fileJadwal << jadwal[i].idJadwal << ":"
                 << jadwal[i].idFilm << ":"
                 << jadwal[i].namaTeater << ":"
                 << jadwal[i].waktuTampil << ":"
                 << jadwal[i].totalBaris << ":"
                 << jadwal[i].totalKolom << ":";

      for(int baris = 0; baris < jadwal[i].totalBaris; baris++){
         for(int kolom = 0; kolom < jadwal[i].totalKolom; kolom++){
            fileJadwal << (jadwal[i].denahKursi[baris][kolom].isBooked ? "1" : "0");
            if(!(baris == jadwal[i].totalBaris - 1 && kolom == jadwal[i].totalKolom - 1)){
               fileJadwal << ",";
            }
         }
      }
      fileJadwal << "\n";
   }
   fileJadwal.close();
}

void AdminMenuTeater(Teater teater[], int *jumlahTeater){
   system("cls");
   LihatDaftarTeater(teater, jumlahTeater);
   int pilih;
   cout << "===============================\n";
   cout << "         MENU TEATER           \n";
   cout << "===============================\n";
   cout << "1. Tambah Teater\n";
   cout << "2. Edit Teater\n";
   cout << "3. Hapus Teater\n";
   cout << "4. Kembali ke Menu Admin\n";
   cout << "Pilih menu (1-4): ";
   cin >> pilih;
   switch(pilih){
      case 1:
         TambahTeater(teater, jumlahTeater);
         break;
      case 2:
         EditTeater(teater, jumlahTeater);
         break;
      case 3:
      {
         HapusTeater(teater, jumlahTeater);
         system("pause");
      }
      case 4:
         break;
      default:
         cout << "Menu yang anda pilih tidak tersedia!" << endl;
         break;
   }
}

void LihatDaftarTeater(Teater teater[], int *jumlahTeater){
   system("cls");
   cout << "Daftar Teater Tersedia:\n";
   cout << left << setw(5) << "ID" << setw(25) << "Nama Teater" << setw(20) << "Lokasi" << setw(15) << "Kapasitas" << setw(10) << "Baris" << setw(10) << "Kolom" << "\n";
   cout << string(80, '=') << endl;
   if(jumlahTeater != nullptr && *jumlahTeater > 0){
      for(int i = 0; i < *jumlahTeater; i++){
         cout << left << setw(5) << i+1 << setw(25) << teater[i].namaTeater << setw(20) << teater[i].lokasi << setw(15) << teater[i].kapasitas << setw(10) << teater[i].baris << setw(10) << teater[i].kolom << endl;
      }
   } else {
      cout << "(Tidak ada data teater)" << endl;
   }
   cout << string(80, '=') << endl;
}

void TambahTeater(Teater teater[], int *jumlahTeater){
   ofstream fileTeater("teaters.txt", ios::app);
   Teater newTeater;

   cout << "Masukkan Nama Teater: ";
   cin.ignore();
   getline(cin, newTeater.namaTeater);
   cout << "Masukkan Lokasi Teater: ";
   getline(cin, newTeater.lokasi);
   cout << "Masukkan Jumlah Baris: ";
   cin >> newTeater.baris;
   cout << "Masukkan Jumlah Kolom: ";
   cin >> newTeater.kolom;

   newTeater.kapasitas = newTeater.baris * newTeater.kolom;

   if(teater != nullptr && jumlahTeater != nullptr){
      teater[*jumlahTeater] = newTeater;
      (*jumlahTeater)++;
   }

   fileTeater << newTeater.namaTeater << ":" 
              << newTeater.lokasi << ":" 
              << newTeater.kapasitas << ":" 
              << newTeater.baris << ":" 
              << newTeater.kolom << "\n";
              
   fileTeater.close();
   cout << "\nTeater berhasil ditambahkan!\n";
}

void EditTeater(Teater teater[], int *jumlahTeater){
   int cari, pilih;
   cout << "ID teater yang ingin diubah datanya: ";
   cin >> cari;

   cout << "Data Teater yang ingin diubah:\n";
   for(int i = 0; i < *jumlahTeater; i++){
      if(i == cari - 1){
         cout << "Nama Teater: " << teater[i].namaTeater << endl;
         cout << "Lokasi: " << teater[i].lokasi << endl;
         cout << "Kapasitas: " << teater[i].kapasitas << " (baris: " << teater[i].baris << ", kolom: " << teater[i].kolom << ")" << endl;
         break;
      }
   }

   cout << "Pilihan edit:\n";
   cout << "1. Nama Teater\n";
   cout << "2. Lokasi\n";
   cout << "3. Kapasitas\n";
   cout << "Pilih data yang ingin diubah (1-3): ";
   cin >> pilih;
   if(pilih == 1){
      cout << "Masukkan nama baru: "; 
      cin.ignore(); 
      getline(cin, teater[cari - 1].namaTeater);
   } else if(pilih == 2){
      cout << "Masukkan lokasi baru: ";
      cin.ignore();
      getline(cin, teater[cari - 1].lokasi);
   } else if(pilih == 3){
      int b, k;
      cout << "Baris baru: "; cin >> b;
      cout << "Kolom baru: "; cin >> k;
      teater[cari - 1].baris = b; teater[cari - 1].kolom = k;
      teater[cari - 1].kapasitas = b * k;
   }
   
   ofstream fileTeater("teaters.txt", ios::out);
   for(int i = 0; i < *jumlahTeater; i++){
      fileTeater << teater[i].namaTeater << ":" << teater[i].lokasi << ":" << teater[i].kapasitas << ":" << teater[i].baris << ":" << teater[i].kolom << "\n";
   }
   fileTeater.close();
   cout << "Data teater berhasil diubah!" << endl;
   system("pause");
}

void HapusTeater(Teater teater[], int *jumlahTeater) {
   int cari;
   cout << "ID teater yang ingin dihapus: "; cin >> cari;
   int index = 0;
   bool found = false;
   for(int i = 0; i < *jumlahTeater; i++){
      if(i == cari - 1){ 
         found = true;
         continue;
      }
      teater[index] = teater[i]; index++;
   }
   if(found){
      (*jumlahTeater)--;
      ofstream fileTeater("teaters.txt", ios::out);
      for(int i = 0; i < index; i++){
         fileTeater << teater[i].namaTeater << ":" << teater[i].lokasi << ":" << teater[i].kapasitas << ":" << teater[i].baris << ":" << teater[i].kolom << "\n";
      }
      fileTeater.close();
      cout << "Teater berhasil dihapus!" << endl;
   } else {
      cout << "Teater tidak ditemukan!" << endl;
   }
}

void AdminMenuFilm(Film film[], int *jumlahFilm) {
   system("cls");
   int pilih;
   cout << "===============================\n";
   cout << "         MENU FILM             \n";
   cout << "===============================\n";
   cout << "Daftar Film:\n";
   cout << left << setw(5) << "ID" << setw(30) << "Judul" << setw(20) << "Genre" << setw(10) << "Harga" << "\n";
   cout << string(65, '-') << endl;
   for(int i = 0; i < *jumlahFilm; i++){
      cout << left << setw(5) << film[i].id << setw(30) << film[i].judul << setw(20) << film[i].genre << setw(10) << film[i].harga << "\n";
   }
   cout << "===============================\n";
   cout << "1. Tambah Film\n";
   cout << "2. Edit Film\n";
   cout << "3. Hapus Film\n";
   cout << "4. Kembali ke Menu Admin\n";
   cout << "Pilih menu (1-4): "; 
   cin >> pilih;
   switch(pilih){
      case 1: 
         TambahFilm(film, jumlahFilm);
         break;
      case 2:
         EditFilm(film, jumlahFilm);
         break;
      case 3:
         HapusFilm(film, jumlahFilm);
         system("pause");
         break;
      case 4:
         return;
   }
}

void TampilDaftarFilm(Film filmAsli[], int jumlahFilm){
   system("cls");
   int pilih, pilihUrut;
   Film film[100];
   for(int i = 0; i < jumlahFilm; i++){
      film[i] = filmAsli[i];
   }
   
   cout << "Menu Tampil Daftar Film\n";
   cout << "========================\n";
   cout << "1. Lihat (Unsorted)\n";
   cout << "2. Lihat (Sorted by ID)\n";
   cout << "3. Lihat (Sorted by Judul)\n";
   cout << "4. Lihat (Sorted by Genre)\n";
   cout << "5. Lihat (Sorted by Harga)\n";
   cout << "Pilih menu (1-5): ";
   cin >> pilih;
   
   if(pilih == 2){
      cout << "1. Ascending\n2. Descending\nPilih urutan (1-2): "; cin >> pilihUrut;
      for(int i = 0; i < jumlahFilm-1; i++){
         for(int j = 0; j < jumlahFilm-i-1; j++){
            if((pilihUrut == 1 && film[j].id > film[j+1].id) || (pilihUrut == 2 && film[j].id < film[j+1].id)){
               swap(film[j], film[j+1]);
            }
         }
      }
   } else if(pilih == 3){
      cout << "1. Ascending\n2. Descending\nPilih urutan (1-2): "; cin >> pilihUrut;
      for(int i = 0; i < jumlahFilm-1; i++){
         for(int j = 0; j < jumlahFilm-i-1; j++){
            if((pilihUrut == 1 && toLower(film[j].judul) > toLower(film[j+1].judul)) || (pilihUrut == 2 && toLower(film[j].judul) < toLower(film[j+1].judul))){
               swap(film[j], film[j+1]);
            }
         }
      }
   } else if(pilih == 4){
      cout << "1. Ascending\n2. Descending\nPilih urutan (1-2): "; cin >> pilihUrut;
      for(int i = 0; i < jumlahFilm-1; i++){
         for(int j = 0; j < jumlahFilm-i-1; j++){
            if((pilihUrut == 1 && toLower(film[j].genre) > toLower(film[j+1].genre)) || (pilihUrut == 2 && toLower(film[j].genre) < toLower(film[j+1].genre))){
               swap(film[j], film[j+1]);
            }
         }
      }
   } else if(pilih == 5){
      cout << "1. Ascending\n2. Descending\nPilih urutan (1-2): "; cin >> pilihUrut;
      for(int i = 0; i < jumlahFilm-1; i++){
         for(int j = 0; j < jumlahFilm-i-1; j++){
            if((pilihUrut == 1 && film[j].harga > film[j+1].harga) || (pilihUrut == 2 && film[j].harga < film[j+1].harga)){
               swap(film[j], film[j+1]);
            }
         }
      }
   } else if(pilih != 1){
      cout << "Menu yang anda pilih tidak tersedia!" << endl;
      return;
   }

   system("cls");
   cout << "Daftar Film Tersedia:\n";
   cout << left << setw(5) << "ID" << setw(30) << "Judul" << setw(20) << "Genre" << setw(10) << "Harga" << "\n";
   cout << string(65, '-') << endl;
   for(int i = 0; i < jumlahFilm; i++){
      cout << left << setw(5) << film[i].id << setw(30) << film[i].judul << setw(20) << film[i].genre << setw(10) << film[i].harga << "\n";
   }
   system("pause");
}

void TambahFilm(Film film[], int *jumlahFilm){
   ofstream fileFilm("films.txt", ios::app);
   if(!fileFilm.is_open()){
      cout << "Gagal membuka file!" << endl;
      return;
   }
   int index = *jumlahFilm;
   int inputBanyak;
   cout << "Input berapa film? : ";
   cin >> inputBanyak;
   cin.ignore();
   int nomor = 1;
   int lastID = film[*jumlahFilm-1].id + 1;
   for(int i = index; i < (*jumlahFilm + inputBanyak); i++){
      cout << "-----------------------------" << endl;
      cout << "No. " << nomor++ << endl;
      film[i].id = lastID;
      lastID++;
      cout << "Masukkan Judul Film: ";
      getline(cin, film[i].judul);
      cout << "Masukkan Genre Film: ";
      getline(cin, film[i].genre);
      cout << "Masukkan Harga Tiket: ";
      cin >> film[i].harga;
      cin.ignore();
      fileFilm << film[i].id << ":" << film[i].judul << ":" << film[i].genre << ":" << film[i].harga << "\n";
   }
   fileFilm.close();
   *jumlahFilm += inputBanyak;
   cout << "Film berhasil ditambahkan!" << endl;
}

void EditFilm(Film film[], int *jumlahFilm){
   int cari, pilih;
   cout << "ID film yang ingin diubah datanya: "; cin >> cari;

   int idx = -1;
   for(int i = 0; i < *jumlahFilm; i++){
      if(film[i].id == cari){
         idx = i;
         cout << "Judul: " << film[i].judul << "\nGenre: " << film[i].genre << "\nHarga: " << film[i].harga << endl;
         break;
      }
   }
   if(idx == -1) { cout << "Film tidak ditemukan!\n"; return; }

   cout << "Pilihan edit:\n1. Judul\n2. Genre\n3. Harga\nPilih (1-3): "; cin >> pilih;
   cin.ignore();

   if(pilih == 1){
      cout << "Masukkan judul baru: "; getline(cin, film[idx].judul);
   } else if(pilih == 2){
      cout << "Masukkan genre baru: "; getline(cin, film[idx].genre);
   } else if(pilih == 3){
      cout << "Masukkan harga baru: "; cin >> film[idx].harga;
   } else {
      cout << "Pilihan tidak valid!" << endl; return;
   }

   ofstream temp("temp.txt");
   for(int i = 0; i < *jumlahFilm; i++){
      temp << film[i].id << ":" << film[i].judul << ":" << film[i].genre << ":" << film[i].harga << "\n";
   }
   temp.close();
   remove("films.txt");
   rename("temp.txt", "films.txt");
   cout << "Data film berhasil diubah!" << endl;
}

void HapusFilm(Film film[], int *jumlahFilm){
   string id, judul, genre, harga;
   int cari;

   cout << "ID film yang ingin dihapus: ";
   cin >> cari;

   ofstream temp("temp.txt");
   bool ditemukan = false;

   if (!temp.is_open()) {
       cout << "Gagal membuka file!" << endl;
       return;
   }

   bool found = false;

   int index = 0;
   for (int i = 0; i < *jumlahFilm; ++i){
      if (film[i].id == cari) {
          found = true;
          continue;
      }
      film[index] = film[i];

      index++;

   }

   if (found) {
       for (int i = 0; i < index; ++i) {
           temp << film[i].id << ":" << film[i].judul << ":" << film[i].genre << ":" << film[i].harga << "\n";
       }
       ditemukan = true;
   } else {
       ditemukan = false;
   }

   temp.close();

   if(ditemukan){
      remove("films.txt");
      rename("temp.txt", "films.txt");
      cout << "Film berhasil dihapus!" << endl;
      (*jumlahFilm)--;
   } else {
      cout << "Film dengan ID " << cari << " tidak ditemukan." << endl;
      remove("temp.txt"); 
   }
}

// ==================================================
// =============== CUSTOMER FUNCTIONS ===============
// ==================================================

void RegisterCustomer(Pengguna pengguna[], int *jumlahPengguna){
   system("cls");
   Pengguna newCustomer;
   cout << "\n=== REGISTER CUSTOMER ===\n";
   cout << "Username: "; cin >> newCustomer.username;
   cout << "Password: "; cin >> newCustomer.password;

   ofstream File("customers.txt", ios::app);
   pengguna[*jumlahPengguna] = newCustomer;
   (*jumlahPengguna)++;
   File << newCustomer.username << ":" << newCustomer.password << "\n";
   File.close();
}

void MenuPengguna(Film film[], int jumlahFilm, Pengguna pengguna[], int jumlahPengguna, Pesanan pesanan[], int *jumlahPesanan, Teater teater[], int *jumlahTeater, JadwalTayang jadwal[], int *jumlahJadwal){  
   system("cls");
   int pilih;
   Pengguna inputCustomer; 
   cout << "\n=== LOGIN CUSTOMER ===\n";
   cout << "Username: ";
   cin >> inputCustomer.username;
   cout << "Password: ";
   cin >> inputCustomer.password;
   ifstream fileCustomer("customers.txt");

   bool statusLogin = false;

   for(int i = 0; i < jumlahPengguna; i++){
      if(pengguna[i].username == inputCustomer.username && pengguna[i].password == inputCustomer.password){
         statusLogin = true;
         cout << "Login berhasil! Selamat datang, " << inputCustomer.username << "!" << endl;
         system("pause");
         break;
      }
   }

   if(statusLogin){
      bool ulang = false;
      do{
         system("cls"); 
         cout << "==================================================\n";
         cout << "                    MENU PENGGUNA                 \n";
         cout << "==================================================\n";
         cout << " [1] Lihat Daftar Film                            \n";
         cout << " [2] Cari Film                                    \n";
         cout << " [3] Pesan Tiket & Pilih Kursi                    \n";
         cout << " [4] Lihat Laporan Riwayat Transaksi              \n";
         cout << " [5] Batal Reservasi Tiket                        \n";
         cout << " [6] Logout                                       \n";
         cout << "==================================================\n";
         cout << " Pilih menu (1-6): ";
         cin >> pilih;
         cin.ignore();
         string konfirmasi;
         switch(pilih){
         case 1:
            TampilDaftarFilm(film, jumlahFilm);
            break;
         case 2:
            MenuCariFilm(film, jumlahFilm);
            break;
         case 3:
            PesanTiket(film, jumlahFilm, inputCustomer, pesanan, jumlahPesanan, jadwal, *jumlahJadwal);
            break;
         case 4:
            cout << "Riwayat Transaksi Anda:\n";
            cout << left << setw(5) << "No" << setw(30) << "Nama Pelanggan" << setw(30) << "Judul Film" << setw(20) << "Jadwal Tayang" << setw(15) << "ID Kursi" << "\n";
            for(int i = 0; i < *jumlahPesanan; i++){
               if(pesanan[i].namaPelanggan == inputCustomer.username){
                  cout << left << setw(5) << i+1 << setw(30) << pesanan[i].namaPelanggan << setw(30) << pesanan[i].judulFilm << setw(20) << pesanan[i].jadwalTayang << setw(15) << pesanan[i].idkursi << "\n";
               }
            }
            break;
         case 5:
            BatalPesanTiket(pesanan, jumlahPesanan, jadwal, *jumlahJadwal, film, jumlahFilm, inputCustomer);
            break;
         case 6:
            cout << "Logout berhasil!" << endl;
            break;
         default:
            cout << "Menu yang anda pilih tidak tersedia!" << endl;
            break;
         }
         if(pilih != 6){
            cout << "Apakah Anda ingin kembali ke menu pengguna? (y/n): ";
            cin >> konfirmasi;
            cin.ignore();
            if(konfirmasi == "y" || konfirmasi == "Y"){
               ulang = true;
            }else{
               ulang = false;
            }
         }
      }while(pilih != 6 && ulang);
      } else {
         cout << "Login gagal! Pastikan username dan password benar." << endl;
      }
}

void MenuCariFilm(Film film[], int jumlahFilm){
   int pilih;
   do {
      system("cls");
      cout << "Cari Film Berdasarkan:\n";
      cout << "1. Judul\n";
      cout << "2. Genre\n";
      cout << "3. Kembali ke Menu Utama\n";
      cout << "Pilih (1-3): ";
      cin >> pilih;
      cin.ignore();
      switch(pilih){
         case 1:
            {
               string keyword;
               char tipe = 'j';
               cout << "Masukkan judul film: ";
               getline(cin, keyword);
               cariFilm(film, jumlahFilm, keyword, tipe);
            }
            break;
         case 2:
            {
               string keyword;
               char tipe = 'g';
               cout << "Masukkan genre film: ";
               getline(cin, keyword);
               cariFilm(film, jumlahFilm, keyword, tipe);
            }
            break;
         case 3:
         break;
         default:
         break;
      }
   } while (pilih != 3);
}

void cariFilm(Film film[], int jumlahFilm, string keyword, char tipe){
   system("cls");
   cout << "Hasil Pencarian untuk '" << keyword << "':\n";
   cout << left << setw(5) << "ID" << setw(30) << "Judul" << setw(20) << "Genre" << setw(10) << "Harga" << "\n";
   bool ditemukan = false;
   
   for(int i = 0; i < jumlahFilm; i++){
      string target = (tipe == 'j') ? toLower(film[i].judul) : toLower(film[i].genre);
      
      if(target.find(toLower(keyword)) != string::npos){
         cout << left << setw(5) << film[i].id << setw(30) << film[i].judul << setw(20) << film[i].genre << setw(10) << film[i].harga << "\n";
         ditemukan = true;
      }
   }
   if(!ditemukan){
      cout << "Film tidak ditemukan." << endl;
   }
   system("pause"); 
}

void PesanTiket(Film film[], int jumlahFilm, Pengguna inputCustomer, Pesanan pesanan[], int *jumlahPesanan, JadwalTayang jadwal[], int jumlahJadwal) {
   system("cls");
   if (jumlahJadwal == 0) {
      cout << "Maaf, saat ini tidak ada jadwal film yang tersedia." << endl;
      system("pause");
      return;
   }

   LihatDaftarJadwal(jadwal, jumlahJadwal, film, jumlahFilm);
   
   int pilihJadwal;
   cout << "Masukkan ID Jadwal yang ingin ditonton: ";
   cin >> pilihJadwal;

   int idxJadwal = -1;
   for (int i = 0; i < jumlahJadwal; i++) {
      if (jadwal[i].idJadwal == pilihJadwal) {
         idxJadwal = i;
         break;
      }
   }

   if (idxJadwal == -1) {
      cout << "ID Jadwal tidak ditemukan!" << endl;
      system("pause");
      return;
   }

   string judulFilm = "Tidak Diketahui";
   int hargaTiket = 0;
   for (int j = 0; j < jumlahFilm; j++) {
      if (film[j].id == jadwal[idxJadwal].idFilm) {
         judulFilm = film[j].judul;
         hargaTiket = film[j].harga;
         break;
      }
   }

   system("cls");
   cout << "==================================================\n";
   cout << "  FILM   : " << judulFilm << "\n";
   cout << "  TEATER : " << jadwal[idxJadwal].namaTeater << "\n";
   cout << "  JAM    : " << jadwal[idxJadwal].waktuTampil << "\n";
   cout << "  HARGA  : Rp. " << hargaTiket << "\n";
   cout << "==================================================\n\n";

   string teksLayar = "[--- LAYAR BIOSKOP ---]";
   int lebarDenah = jadwal[idxJadwal].totalKolom * 6;
   
   if (lebarDenah > teksLayar.length()) {
      int padding = (lebarDenah - teksLayar.length()) / 2;
      cout << string(padding, ' ') << teksLayar << "\n\n";
   } else {
      cout << teksLayar << "\n\n";
   }

   for (int i = 0; i < jadwal[idxJadwal].totalBaris; i++) {
      for (int j = 0; j < jadwal[idxJadwal].totalKolom; j++) {
         if (jadwal[idxJadwal].denahKursi[i][j].isBooked) {
            cout << left << setw(6) << "[ X ]"; 
         } else {
            cout << left << setw(6) << "[" + jadwal[idxJadwal].denahKursi[i][j].nomorKursi + "]";
         }
      }
      cout << "\n\n";
   }
   cout << "Keterangan: [ X ] = Sudah Dipesan\n";
   cout << "==================================================\n";

   string pilihKursi;
   cout << "Masukkan Nomor Kursi yang ingin dipesan (Contoh: A1): ";
   cin >> pilihKursi;

   bool kursiDitemukan = false;
   int barisTerpilih = -1, kolomTerpilih = -1;

   for (int i = 0; i < jadwal[idxJadwal].totalBaris; i++) {
      for (int j = 0; j < jadwal[idxJadwal].totalKolom; j++) {
         if (toLower(jadwal[idxJadwal].denahKursi[i][j].nomorKursi) == toLower(pilihKursi)) {
            kursiDitemukan = true;
            barisTerpilih = i;
            kolomTerpilih = j;
            break;
         }
      }
      if(kursiDitemukan) break;
   }

   if (!kursiDitemukan) {
      cout << "\n[EROR] Nomor kursi tidak valid atau di luar kapasitas teater!\n";
      system("pause");
      return;
   }

   if (jadwal[idxJadwal].denahKursi[barisTerpilih][kolomTerpilih].isBooked) {
      cout << "\n[EROR] Maaf, kursi " << pilihKursi << " sudah dipesan orang lain!\n";
      system("pause");
      return;
   }

   jadwal[idxJadwal].denahKursi[barisTerpilih][kolomTerpilih].isBooked = true;
   string namaKursiResmi = jadwal[idxJadwal].denahKursi[barisTerpilih][kolomTerpilih].nomorKursi;

   int idxPesanan = *jumlahPesanan;
   pesanan[idxPesanan].namaPelanggan = inputCustomer.username;
   pesanan[idxPesanan].judulFilm = judulFilm;
   pesanan[idxPesanan].jadwalTayang = jadwal[idxJadwal].waktuTampil;
   pesanan[idxPesanan].idkursi = namaKursiResmi;
   (*jumlahPesanan)++;

   simpanSemuaJadwal(jadwal, jumlahJadwal);

   ofstream filePesanan("orders.txt", ios::app);
   filePesanan << pesanan[idxPesanan].namaPelanggan << ":"
              << pesanan[idxPesanan].judulFilm << ":"
              << pesanan[idxPesanan].jadwalTayang << ":"
              << pesanan[idxPesanan].idkursi << "\n";
   filePesanan.close();

   cout << "\n==================================================\n";
   cout << "   PEMESANAN TIKET BERHASIL!\n";
   cout << "   Kursi Anda: " << namaKursiResmi << "\n";
   cout << "   Silakan lakukan pembayaran di kasir sebesar Rp. " << hargaTiket << "\n";
   cout << "==================================================\n";
   system("pause");
}

void BatalPesanTiket(Pesanan pesanan[], int *jumlahPesanan, JadwalTayang jadwal[], int jumlahJadwal, Film film[], int jumlahFilm, Pengguna inputCustomer) {
   system("cls");
   cout << "==================================================\n";
   cout << "               BATALKAN RESERVASI TIKET           \n";
   cout << "==================================================\n";

   int pesananUser[100];
   int counterUser = 0;

   cout << left << setw(5) << "No" << setw(30) << "Judul Film" << setw(20) << "Jadwal Tayang" << setw(15) << "ID Kursi" << "\n";
   cout << string(70, '-') << endl;

   for(int i = 0; i < *jumlahPesanan; i++){
      if(pesanan[i].namaPelanggan == inputCustomer.username){
         pesananUser[counterUser] = i;
         counterUser++;
         cout << left << setw(5) << counterUser 
              << setw(30) << pesanan[i].judulFilm 
              << setw(20) << pesanan[i].jadwalTayang 
              << setw(15) << pesanan[i].idkursi << "\n";
      }
   }

   if(counterUser == 0) {
      cout << "Anda belum memiliki riwayat pemesanan tiket aktif.\n";
      system("pause");
      return;
   }

   int pilihan;
   cout << "\nPilih nomor pesanan yang ingin dibatalkan (1-" << counterUser << "): ";
   cin >> pilihan;

   if(pilihan < 1 || pilihan > counterUser) {
      cout << "[EROR] Pilihan tidak valid!\n";
      system("pause");
      return;
   }

   int indeksTarget = pesananUser[pilihan - 1];
   Pesanan targetBatal = pesanan[indeksTarget];

   bool kursiBerhasilDilepas = false;
   for(int i = 0; i < jumlahJadwal; i++) {
      string judulFilmJadwal = "";
      for(int f = 0; f < jumlahFilm; f++) {
         if(film[f].id == jadwal[i].idFilm) {
            judulFilmJadwal = film[f].judul;
            break;
         }
      }

      if(jadwal[i].waktuTampil == targetBatal.jadwalTayang && judulFilmJadwal == targetBatal.judulFilm) {
         for(int b = 0; b < jadwal[i].totalBaris; b++) {
            for(int k = 0; k < jadwal[i].totalKolom; k++) {
               if(toLower(jadwal[i].denahKursi[b][k].nomorKursi) == toLower(targetBatal.idkursi)) {
                  jadwal[i].denahKursi[b][k].isBooked = false;
                  kursiBerhasilDilepas = true;
                  break;
               }
            }
            if(kursiBerhasilDilepas) break;
         }
      }
      if(kursiBerhasilDilepas) break;
   }

   for(int i = indeksTarget; i < (*jumlahPesanan) - 1; i++) {
      pesanan[i] = pesanan[i + 1];
   }
   (*jumlahPesanan)--;

   ofstream filePesanan("orders.txt", ios::out);
   for(int i = 0; i < *jumlahPesanan; i++) {
      filePesanan << pesanan[i].namaPelanggan << ":"
                  << pesanan[i].judulFilm << ":"
                  << pesanan[i].jadwalTayang << ":"
                  << pesanan[i].idkursi << "\n";
   }
   filePesanan.close();

   simpanSemuaJadwal(jadwal, jumlahJadwal);

   cout << "\n==================================================\n";
   cout << "            PEMBATALAN RESERVASI BERHASIL!          \n";
   cout << "==================================================\n";
   system("pause");
}

string cvJadwal(int jadwal) {
   if (jadwal == 1) return "10.00 AM";
   if (jadwal == 2) return "01.00 PM";
   if (jadwal == 3) return "04.00 PM";
   if (jadwal == 4) return "07.00 PM";
   return "Jadwal tidak valid";
}

void loadData(Film film[], int *jumlahFilm, Pengguna pengguna[], int *jumlahPengguna, Pesanan pesanan[], int *jumlahPesanan, Admins admin[], int *jumlahAdmin, Teater teater[], int *jumlahTeater, JadwalTayang jadwal[], int *jumlahJadwal){
   ifstream fileFilm("films.txt");
   if(fileFilm.is_open()){
      string id, judul, genre, harga;
      *jumlahFilm = 0;
      while(getline(fileFilm, id, ':') && getline(fileFilm, judul, ':') && getline(fileFilm, genre, ':') && getline(fileFilm, harga)){
         film[*jumlahFilm].id = stoi(id);
         film[*jumlahFilm].judul = judul;
         film[*jumlahFilm].genre = genre;
         film[*jumlahFilm].harga = stoi(harga);
         (*jumlahFilm)++;
      }
      fileFilm.close();
   }

   ifstream filePengguna("penggunas.txt");
   if(filePengguna.is_open()){
      string username, password;
      *jumlahPengguna = 0;
      while(getline(filePengguna, username, ':') && getline(filePengguna, password)){
         pengguna[*jumlahPengguna].username = username;
         pengguna[*jumlahPengguna].password = password;
         (*jumlahPengguna)++;
      }
      filePengguna.close();
   }

   ifstream filePesanan("orders.txt");
   if(filePesanan.is_open()){
      string namaPelanggan, judulFilm, jadwalTayang, idkursi;
      *jumlahPesanan = 0;
      while(getline(filePesanan, namaPelanggan, ':') && getline(filePesanan, judulFilm, ':') && getline(filePesanan, jadwalTayang, ':') && getline(filePesanan, idkursi)){
         pesanan[*jumlahPesanan].namaPelanggan = namaPelanggan;
         pesanan[*jumlahPesanan].judulFilm = judulFilm;
         pesanan[*jumlahPesanan].jadwalTayang = jadwalTayang;
         pesanan[*jumlahPesanan].idkursi = idkursi;
         (*jumlahPesanan)++;
      }
      filePesanan.close();
   }

   ifstream fileAdmin("admins.txt");
   if(fileAdmin.is_open()){
      string username, password;
      *jumlahAdmin = 0;
      while(getline(fileAdmin, username, ':') && getline(fileAdmin, password)){
         admin[*jumlahAdmin].username = username;
         admin[*jumlahAdmin].password = password;
         (*jumlahAdmin)++;
      }
      fileAdmin.close();
   }

   ifstream fileTeater("teaters.txt");
   if(fileTeater.is_open()){
      string namaTeater, lokasi, kapasitas, baris, kolom;
      *jumlahTeater = 0;
      while(getline(fileTeater, namaTeater, ':') && 
            getline(fileTeater, lokasi, ':') && 
            getline(fileTeater, kapasitas, ':') && 
            getline(fileTeater, baris, ':') && 
            getline(fileTeater, kolom)){
            
         teater[*jumlahTeater].namaTeater = namaTeater;
         teater[*jumlahTeater].lokasi = lokasi;
         teater[*jumlahTeater].kapasitas = stoi(kapasitas);
         teater[*jumlahTeater].baris = stoi(baris);
         teater[*jumlahTeater].kolom = stoi(kolom);
         (*jumlahTeater)++;
      }
      fileTeater.close();
   }

   ifstream fileJadwal("jadwals.txt");
   if (!fileJadwal.is_open()) {
      ofstream createFile("jadwals.txt");
      createFile.close();
      *jumlahJadwal = 0;
   } else {
      string idJadwal, idFilm, namaTeater, waktuTampil, totalBaris, totalKolom, statusKursiAll;
      *jumlahJadwal = 0;

      while (getline(fileJadwal, idJadwal, ':') &&
             getline(fileJadwal, idFilm, ':') &&
             getline(fileJadwal, namaTeater, ':') &&
             getline(fileJadwal, waktuTampil, ':') &&
             getline(fileJadwal, totalBaris, ':') &&
             getline(fileJadwal, totalKolom, ':') &&
             getline(fileJadwal, statusKursiAll)) {

         int idx = *jumlahJadwal;
         jadwal[idx].idJadwal = stoi(idJadwal);
         jadwal[idx].idFilm = stoi(idFilm);
         jadwal[idx].namaTeater = namaTeater;
         jadwal[idx].waktuTampil = waktuTampil;
         jadwal[idx].totalBaris = stoi(totalBaris);
         jadwal[idx].totalKolom = stoi(totalKolom);

         // Parsing menjadi 2D array denah kursi
         stringstream ss(statusKursiAll);
         string statusTunggal;
         
         for (int i = 0; i < jadwal[idx].totalBaris; i++) {
            char hurufBaris = 'A' + i;
            for (int j = 0; j < jadwal[idx].totalKolom; j++) {
               jadwal[idx].denahKursi[i][j].nomorKursi = hurufBaris + to_string(j + 1);
               
               if (getline(ss, statusTunggal, ',')) {
                  if (statusTunggal == "1") {
                     jadwal[idx].denahKursi[i][j].isBooked = true;
                  } else {
                     jadwal[idx].denahKursi[i][j].isBooked = false;
                  }
               }
            }
         }
         (*jumlahJadwal)++;
      }
      fileJadwal.close();
   }
}

// =============================================
// =============== MAIN FUNCTION ===============
// =============================================

int main(){
   int pilih;
   bool ulang = true;
   Film film[100]; int jumlahFilm = 0;
   Pengguna pengguna[100]; int jumlahPengguna = 0;
   Pesanan pesanan[100]; int jumlahPesanan = 0;
   Admins admin[100]; int jumlahAdmin = 0;
   Teater teater[100]; int jumlahTeater = 0;
   JadwalTayang jadwalTayang[100]; int jumlahJadwalTayang = 0;
   loadData(film, &jumlahFilm, pengguna, &jumlahPengguna, pesanan, &jumlahPesanan, admin, &jumlahAdmin, teater, &jumlahTeater, jadwalTayang, &jumlahJadwalTayang);
   do{
      system("cls"); 
      cout << "=======================================\n";
      cout << "     WELCOME TO CINEMA TICKET SYSTEM   \n";
      cout << "=======================================\n";
      cout << " 1. Masuk sebagai Admin                \n";
      cout << " 2. Register sebagai Customer          \n";
      cout << " 3. Masuk sebagai Customer             \n";
      cout << " 4. Keluar Aplikasi                    \n";
      cout << "=======================================\n";
      cout << " Pilih akses (1-4): ";
      cin >> pilih;
      switch(pilih){
         case 1:
            MenuAdmin(film, &jumlahFilm, pengguna, &jumlahPengguna, pesanan, &jumlahPesanan, admin, &jumlahAdmin, teater, &jumlahTeater, jadwalTayang, &jumlahJadwalTayang);
            ulangi(&ulang);
            break;
         case 2:
            RegisterCustomer(pengguna, &jumlahPengguna);
            ulangi(&ulang);
            break;
         case 3:
             MenuPengguna(film, jumlahFilm, pengguna, jumlahPengguna, pesanan, &jumlahPesanan, teater, &jumlahTeater, jadwalTayang, &jumlahJadwalTayang);
             ulangi(&ulang);
            break;
         case 4:
            cout << "Keluar dari aplikasi. Terima kasih!" << endl;
            break;
         default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
      }
   } while (ulang && pilih != 4);

   return 0;
}

void ulangi(bool *ulang){
   char pilihan;
   cout << "Apakah Anda ingin kembali ke menu utama? (y/n): ";
   cin >> pilihan;
   if(pilihan == 'y' || pilihan == 'Y'){
      *ulang = true;
   } else {
      *ulang = false;
      cout << "Keluar dari aplikasi. Terima kasih!" << endl;
   }
}
