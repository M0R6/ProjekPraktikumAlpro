#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
struct Film{
   int id;
   string judul;
   string genre;
   int harga;
};

struct Kursi{
   string nomorKursi;
   bool isBooked;
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

string toLower(string str){
   for(size_t i = 0; i < str.length(); i++){
      str[i] = tolower(str[i]);
   }
   return str;
}

void ulangi(bool *ulang);
void cariFilm(Film film[], int jumlahFilm, string keyword, char tipe);
void MenuAdmin(Film film[], int *jumlahFilm, Pengguna pengguna[], int *jumlahPengguna, Pesanan pesanan[], int *jumlahPesanan, Admins admin[], int *jumlahAdmin, Kursi kursi[], int *jumlahKursi);
void AdminMenuFilm(Film film[], int *jumlahFilm);
void TambahFilm(Film film[], int *jumlahFilm);
void EditFilm(Film film[], int *jumlahFilm);
void EditJudul(Film film[], int *jumlahFilm, int cari);
void EditGenre(Film film[], int *jumlahFilm, int cari);
void EditHarga(Film film[], int *jumlahFilm, int cari);
void HapusFilm(Film film[], int *jumlahFilm);
void MenuKursi(Kursi kursi[], int *jumlahKursi);
void RegisterCustomer();
void MenuPengguna(Film film[], int jumlahFilm, Pengguna pengguna[], int *jumlahPengguna);
void PesanTiket(Film film[], int jumlahFilm, Pengguna inputCustomer, Pesanan pesanan[], int *jumlahPesanan, Kursi kursi[], int *jumlahKursi);
void TampilDaftarFilm(Film film[], int jumlahFilm);
void MenuCariFilm(Film film[], int jumlahFilm);
void TampilDataFilm(Film film[], int jumlahFilm);

void ulangAdmin(char *ulang){
   cout << "Apakah Anda ingin kembali ke menu admin? (y/n): ";
   cin >> *ulang;
}

void MenuKursi(Kursi kursi[], int *jumlahKursi){
   system("cls");
   char ulang = 'n';
   int indexDihapus = 0;
   do{
      cout << "=================================\n";
      cout << "         MENU KURSI             \n";
      cout << "=================================\n";
      cout << "1. Tambah Kursi\n";
      cout << "2. Hapus Kursi\n";
      cout << "3. Kembali ke Menu Admin\n";
      cout << "Pilih menu (1-3): ";
      int pilih;
      cin >> pilih;
      switch(pilih){
         case 1:
            {
               ofstream fileKursi("kursi.txt", ios::app);
               if(!fileKursi.is_open()){
                  cout << "Gagal membuka file!" << endl;
                  return;
               }
               string nomorKursi;
               cout << "Berapa kursi yang ingin ditambahkan? : ";
               int index = *jumlahKursi;
               int inputBanyak;
               cin >> inputBanyak;
               cin.ignore();
               int nomor = 1;
               for(int i = index; i < (*jumlahKursi + inputBanyak); i++){
                  cout << "Masukkan nomor kursi ke-" << nomor++ << ": ";
                  cin >> kursi[i].nomorKursi;
                  cin.ignore();
                  for(int j = 0; j < i; j++){
                     if(kursi[i].nomorKursi == kursi[j].nomorKursi){
                        cout << "Nomor kursi sudah ada, silakan masukkan nomor lain." << endl;
                        cout << "Masukkan nomor kursi ke-" << nomor-1 << ": ";
                        cin >> kursi[i].nomorKursi;
                        cin.ignore();
                        j = -1; // reset loop untuk cek ulang
                     }
                  }
                  kursi[i].isBooked = false;
                  fileKursi << kursi[i].nomorKursi << ":" << "0" << "\n";
               }
               fileKursi.close();
               *jumlahKursi += inputBanyak;
               cout << "Kursi berhasil ditambahkan!" << endl;
            }
            break;
         case 2:
            {  
               cout << "Daftar Kursi:\n";
               cout << left << setw(15) << "Nomor Kursi" << setw(10) << "Status" << "\n";
               for(int i = 0; i < *jumlahKursi; i++){
                  cout << left << setw(15) << kursi[i].nomorKursi << setw(10) << (kursi[i].isBooked ? "Booked" : "Available") << "\n";
               }
               string cari;
               cout << "Masukkan nomor kursi yang ingin dihapus: ";
               cin >> cari;

               ofstream temp("temp.txt");
               bool ditemukan = false;

               if (!temp.is_open()) {
                   cout << "Gagal membuka file!" << endl;
                   return;
               }

               for (int i = 0; i < *jumlahKursi; ++i){
                  if (kursi[i].nomorKursi == cari) {
                      ditemukan = true;
                      indexDihapus = i;
                      continue;
                  }
                  kursi[i] = kursi[i];
                  temp << kursi[i].nomorKursi << ":" << (kursi[i].isBooked ? "1" : "0") << "\n";
               }

               temp.close();

               if(ditemukan){
                  remove("kursi.txt");
                  rename("temp.txt", "kursi.txt");
                  for(int i = indexDihapus; i < (*jumlahKursi - 1); i++){
                     kursi[i] = kursi[i + 1];
                  }
                  (*jumlahKursi)--;
                  cout << "Kursi berhasil dihapus!" << endl;
               } else {
                  cout << "Kursi dengan nomor " << cari << " tidak ditemukan." << endl;
                  remove("temp.txt"); 
               }
            }
            break;
         case 3:
            ulang = 'n';
            break;
         default:
            cout << "Menu yang anda pilih tidak tersedia!" << endl;
            break;
      }
      if(pilih != 3){
         cout << "Apakah Anda ingin kembali ke menu kursi? (y/n): ";
         cin >> ulang;
      }
   }while(ulang == 'y' || ulang == 'Y');
}

void MenuAdmin(Film film[], int *jumlahFilm, Pengguna pengguna[], int *jumlahPengguna, Pesanan pesanan[], int *jumlahPesanan, Admins admin[], int *jumlahAdmin, Kursi kursi[], int *jumlahKursi){
   system("cls"); 
   int pilih;
   char ulang;
   Admins inputAdmin; 
   cout << "\n=== LOGIN ADMIN ===\n";
   cout << "Username: "; 
   cin >> inputAdmin.username;
   cout << "Password: "; 
   cin >> inputAdmin.password;
   
   bool statusLogin = false;
   for(int i = 0; i < *jumlahAdmin; i++){
      if(admin[i].username == inputAdmin.username && admin[i].password == inputAdmin.password){
         statusLogin = true;
         cout << "Login berhasil! Selamat datang, " << inputAdmin.username << "!" << endl;
         system("pause");
         break;
      }
   }

   if (statusLogin){
      int totalTransaksi = 0;
      int totalPendapatan = 0;
      do{
         system("cls");
         cout << "===============================\n";
         cout << "         MENU ADMIN            \n";
         cout << "===============================\n";
         cout << "1. Menu Film\n";
         cout << "2. Menu Kursi\n";
         cout << "3. Lihat Laporan Transaksi\n";
         cout << "4. Logout\n";
         cout << "Pilih menu (1-4): ";
         cin >> pilih;
         switch (pilih){
            case 1:
               AdminMenuFilm(film, jumlahFilm);
               ulangAdmin(&ulang);
               break;
            case 2:
               // AdminMenuTeater();
               MenuKursi(kursi, jumlahKursi);
               ulangAdmin(&ulang);
               break;
            case 3:
               system("cls");
               cout << "Laporan Transaksi:\n";
               cout << left << setw(5) << "No" << setw(30) << "Nama Pelanggan" << setw(30) << "Judul Film" << setw(20) << "Jadwal Tayang" << setw(15) << "ID Kursi" << "\n";
               for(int i = 0; i < *jumlahPesanan; i++){
                  cout << left << setw(5) << i+1 << setw(30) << pesanan[i].namaPelanggan << setw(30) << pesanan[i].judulFilm << setw(20) << pesanan[i].jadwalTayang << setw(15) << pesanan[i].idkursi << "\n";
                  totalTransaksi++;
                  totalPendapatan += film[i].harga;
               }
               cout << "\nTotal Transaksi: " << totalTransaksi << endl;
               cout << "Total Pendapatan: " << totalPendapatan << endl;
               ulangAdmin(&ulang);
               break;
            case 4:
               ulang = 'n';
               break;
            default:
               cout << "Menu yang anda pilih tidak tersedia!" << endl;
               break;
         }
      }while(pilih != 4 && (ulang == 'y' || ulang == 'Y'));
   }else{
       cout << "Login gagal! Pastikan username dan password benar." << endl;
   }
}

void AdminMenuFilm(Film film[], int *jumlahFilm){
   system("cls");
   int pilih;
   cout << "===============================\n";
   cout << "         MENU FILM             \n";
   cout << "===============================\n";
   cout << "Daftar Film:\n";
   TampilDataFilm(film, *jumlahFilm);
   cout << "===============================\n";
   cout << "1. Tambah Film\n";
   cout << "2. Edit Film\n";
   cout << "3. Hapus Film\n";
   cout << "4. Kembali ke Menu Admin\n";
   cout << "Pilih menu (1-4): ";
   cin >> pilih;
   switch (pilih){
      case 1:
         TambahFilm(film, jumlahFilm);
         break;
      case 2:
         EditFilm(film, jumlahFilm);
         break;
      case 3:
         HapusFilm(film, jumlahFilm);
         break;
      case 4:
         break;
      default:
         cout << "Menu yang anda pilih tidak tersedia!" << endl;
         break;
   }
}

void TampilDaftarFilm(Film filmAsli[], int jumlahFilm){
   system("cls");
   int pilih, pilihUrut;
   Film film[jumlahFilm];
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
   switch(pilih){
      case 1:
         break;
      case 2:
         cout << "1. Ascending\n";
         cout << "2. Descending\n";
         cout << "Pilih urutan (1-2): ";
         cin >> pilihUrut;
         if(pilihUrut == 1){
            for(int i = 0; i < jumlahFilm-1; i++){
               for(int j = 0; j < jumlahFilm-i-1; j++){
                  if(film[j].id > film[j+1].id){
                     swap(film[j], film[j+1]);
                  }
               }
            }
         }else if(pilihUrut == 2){
            for(int i = 0; i < jumlahFilm-1; i++){
               for(int j = 0; j < jumlahFilm-i-1; j++){
                  if(film[j].id < film[j+1].id){
                     swap(film[j], film[j+1]);
                  }
               }
            }
         }
         break;
      case 3:
         cout << "1. Ascending\n";
         cout << "2. Descending\n";
         cout << "Pilih urutan (1-2): ";
         cin >> pilihUrut;
         if(pilihUrut == 1){
            for(int i = 0; i < jumlahFilm-1; i++){
               for(int j = 0; j < jumlahFilm-i-1; j++){
                  if(toLower(film[j].judul) > toLower(film[j+1].judul)){
                     swap(film[j], film[j+1]);
                  }
               }
            }
         }else if(pilihUrut == 2){
            for(int i = 0; i < jumlahFilm-1; i++){
               for(int j = 0; j < jumlahFilm-i-1; j++){
                  if(toLower(film[j].judul) < toLower(film[j+1].judul)){
                     swap(film[j], film[j+1]);
                  }
               }
            }
         }
         break;
      case 4:
         cout << "1. Ascending\n";
         cout << "2. Descending\n";
         cout << "Pilih urutan (1-2): ";
         cin >> pilihUrut;
         if(pilihUrut == 1){
            for(int i = 0; i < jumlahFilm-1; i++){
               for(int j = 0; j < jumlahFilm-i-1; j++){
                  if(toLower(film[j].genre) > toLower(film[j+1].genre)){
                     swap(film[j], film[j+1]);
                  }
               }
            }
         }else if(pilihUrut == 2){
            for(int i = 0; i < jumlahFilm-1; i++){
               for(int j = 0; j < jumlahFilm-i-1; j++){
                  if(toLower(film[j].genre) < toLower(film[j+1].genre)){
                     swap(film[j], film[j+1]);
                  }
               }
            }
         }
         break;
      case 5:
         cout << "1. Ascending\n";
         cout << "2. Descending\n";
         cout << "Pilih urutan (1-2): ";
         cin >> pilihUrut;
         if(pilihUrut == 1){
            for(int i = 0; i < jumlahFilm-1; i++){
               for(int j = 0; j < jumlahFilm-i-1; j++){
                  if(film[j].harga > film[j+1].harga){
                     swap(film[j], film[j+1]);
                  }
               }
            }
         }else if(pilihUrut == 2){
            for(int i = 0; i < jumlahFilm-1; i++){
               for(int j = 0; j < jumlahFilm-i-1; j++){
                  if(film[j].harga < film[j+1].harga){
                     swap(film[j], film[j+1]);
                  }
               }
            }
         }
         break;
      default:
         cout << "Menu yang anda pilih tidak tersedia!" << endl;
         return;
   }
   cout << "Daftar Film Tersedia:\n";
   cout << left
   << setw(5) << "ID"
   << setw(30) << "Judul"
   << setw(20) << "Genre"
   << setw(10) << "Harga" << "\n";
   string id, judul, genre, harga;
   for(int i = 0; i < jumlahFilm; i++){
      cout << left
      << setw(5) << film[i].id
      << setw(30) << film[i].judul
      << setw(20) << film[i].genre
      << setw(10) << film[i].harga << "\n";
   }
}

void TampilDataFilm(Film filmData[], int jumlahFilm){
   system("cls");
   Film film[jumlahFilm];
   for(int i = 0; i < jumlahFilm; i++){
      film[i] = filmData[i];
   }
   cout << "Daftar Film Tersedia:\n";
   cout << left
   << setw(5) << "ID"
   << setw(30) << "Judul"
   << setw(20) << "Genre"
   << setw(10) << "Harga" << "\n";
   string id, judul, genre, harga;
   for(int i = 0; i < jumlahFilm; i++){
      cout << left
      << setw(5) << film[i].id
      << setw(30) << film[i].judul
      << setw(20) << film[i].genre
      << setw(10) << film[i].harga << "\n";
   }
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
   string id, judul, genre, harga;
   int cari, pilih;

   cout << "ID film yang ingin diubah datanya: ";
   cin >> cari;

   cout << "Data Film yang ingin diubah:\n";
   for(int i = 0; i < *jumlahFilm; i++){
      if(film[i].id == cari){
         cout << "Judul: " << film[i].judul << endl;
         cout << "Genre: " << film[i].genre << endl;
         cout << "Harga: " << film[i].harga << endl;
      }
   }

   cout << "Pilihan edit:\n";
   cout << "1. Judul\n";
   cout << "2. Genre\n";
   cout << "3. Harga\n";
   cout << "Pilih data yang ingin diubah (1-3): ";
   cin >> pilih;

   switch(pilih){
      case 1:
         EditJudul(film, jumlahFilm, cari);
         break;
      case 2:
         EditGenre(film, jumlahFilm, cari);
         break;
      case 3:
         EditHarga(film, jumlahFilm, cari);
         break;
      default:
         cout << "Pilihan tidak valid!" << endl;
         return;
   }
}

void EditJudul(Film film[], int *jumlahFilm, int cari){
   string id, judul, genre, harga, ganti;
   cout << "Masukkan judul baru: ";
   cin.ignore();
   getline(cin, ganti);

   ofstream temp("temp.txt");

   if (!temp.is_open()) {
       cout << "Gagal membuka file!" << endl;
       return;
   }
   for(int i = 0; i < *jumlahFilm; i++){
      if(film[i].id == cari){
         film[i].judul = ganti;
         temp << film[i].id << ":" << film[i].judul << ":" << film[i].genre << ":" << film[i].harga << "\n";
      }else{
         temp << film[i].id << ":" << film[i].judul << ":" << film[i].genre << ":" << film[i].harga << "\n";
      }
   }
   temp.close();
   remove("films.txt");
   rename("temp.txt", "films.txt");
   cout << "Judul film berhasil diubah!" << endl;
}

void EditGenre(Film film[], int *jumlahFilm, int cari){
   string id, judul, genre, harga, ganti;
   cout << "Masukkan genre baru: ";
   cin.ignore();
   getline(cin, ganti);

   ofstream temp("temp.txt");

   if (!temp.is_open()) {
       cout << "Gagal membuka file!" << endl;
       return;
   }
   for(int i = 0; i < *jumlahFilm; i++){
      if(film[i].id == cari){
         film[i].genre = ganti;
         temp << film[i].id << ":" << film[i].judul << ":" << film[i].genre << ":" << film[i].harga << "\n";
      }else{
         temp << film[i].id << ":" << film[i].judul << ":" << film[i].genre << ":" << film[i].harga << "\n";
      }
   }
   temp.close();
   remove("films.txt");
   rename("temp.txt", "films.txt");
   cout << "Judul film berhasil diubah!" << endl;
}

void EditHarga(Film film[], int *jumlahFilm, int cari){
   string id, judul, genre, harga;
   int ganti;
   cout << "Masukkan harga baru: ";
   cin.ignore();
   cin >> ganti;

   ofstream temp("temp.txt");

   if (!temp.is_open()) {
       cout << "Gagal membuka file!" << endl;
       return;
   }
   for(int i = 0; i < *jumlahFilm; i++){
      if(film[i].id == cari){
         film[i].harga = ganti;
         temp << film[i].id << ":" << film[i].judul << ":" << film[i].genre << ":" << film[i].harga << "\n";
      }else{
         temp << film[i].id << ":" << film[i].judul << ":" << film[i].genre << ":" << film[i].harga << "\n";
      }
   }
   temp.close();
   remove("films.txt");
   rename("temp.txt", "films.txt");
   cout << "Harga film berhasil diubah!" << endl;
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

void RegisterCustomer() {
   system("cls");
   Pengguna newCustomer;
   cout << "\n=== REGISTER CUSTOMER ===\n";
   cout << "Username: "; cin >> newCustomer.username;
   cout << "Password: "; cin >> newCustomer.password;

   ofstream File("customers.txt", ios::app);
   File << newCustomer.username << ":" << newCustomer.password << "\n";
   File.close();
}

void MenuPengguna(Film film[], int jumlahFilm, Pengguna pengguna[], int jumlahPengguna, Pesanan pesanan[], int *jumlahPesanan, Kursi kursi[], int *jumlahKursi){  
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
         cout << " [5] Logout                                       \n";
         cout << "==================================================\n";
         cout << " Pilih menu (1-5): ";
         cin >> pilih;
         cin.ignore();
         string konfirmasi;
         switch(pilih){
         case 1:
            TampilDaftarFilm(film, jumlahFilm);
            cout << "Pesan tiket sekarang? (y/n): ";
            cin >> konfirmasi;
            cin.ignore();
            if (konfirmasi == "y" || konfirmasi == "Y") {
               PesanTiket(film, jumlahFilm, inputCustomer, pesanan, jumlahPesanan, kursi, jumlahKursi);
            }
            break;
         case 2:
            MenuCariFilm(film, jumlahFilm);
            break;
         case 3:
            TampilDataFilm(film, jumlahFilm);
            PesanTiket(film, jumlahFilm, inputCustomer, pesanan, jumlahPesanan, kursi, jumlahKursi);
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
             cout << "Logout berhasil!" << endl;
            break;
         default:
            cout << "Menu yang anda pilih tidak tersedia!" << endl;
            break;
         }
         if(pilih != 5){
            cout << "Apakah Anda ingin kembali ke menu pengguna? (y/n): ";
            cin >> konfirmasi;
            cin.ignore();
            if(konfirmasi == "y" || konfirmasi == "Y"){
               ulang = true;
            }else{
               ulang = false;
            }
         }
      }while(pilih != 5 && ulang);
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

string cvJadwal(int jadwal){
   switch(jadwal){
      case 1:
         return "10.00 AM";
      case 2:
         return "01.00 PM";
      case 3:
         return "04.00 PM";
      case 4:
         return "07.00 PM";
      default:
         return "Jadwal tidak valid";
   }
}

void PesanTiket(Film film[], int jumlahFilm, Pengguna inputCustomer, Pesanan pesanan[], int *jumlahPesanan, Kursi kursi[], int *jumlahKursi){
   int idFilm;
   bool found = false;
   ifstream fileKursi("kursi.txt");
   if(!fileKursi.is_open()){
      cout << "Gagal membuka file!" << endl;
      return;
   }
   ofstream temp("temp.txt");
   if(!temp.is_open()){
      cout << "Gagal membuka file!" << endl;
      return;
   }
   ofstream filePesanan("pesanan.txt", ios::app);
   if(!filePesanan.is_open()){
      cout << "Gagal membuka file!" << endl;
      return;
   }
   cout << "Masukkan ID film yang ingin dipesan: ";
   cin >> idFilm;
   cin.ignore();
   int indexChoosen = -1;
   for(int i = 0; i < jumlahFilm; i++){
      if(film[i].id == idFilm){
         cout << "Film yang dipilih: " << film[i].judul << endl;
         cout << "Harga tiket: " << film[i].harga << endl;
         cout << "Pilih jadwal tayang: " << endl;
         cout << "1. 10:00 AM\n";
         cout << "2. 1:00 PM\n";
         cout << "3. 4:00 PM\n";
         cout << "4. 7:00 PM\n";
         cout << "Pilih jadwal (1-4): ";
         int jadwal;
         cin >> jadwal;
         cout << "Kursi Tersedia:" << endl;
         Kursi tempKursi[*jumlahKursi];
         int jumlahTersedia = 0;
         for(int j = 0; j < *jumlahKursi; j++){
            if(!kursi[j].isBooked){
               tempKursi[jumlahTersedia] = kursi[j];
               jumlahTersedia++;
            }
         }
         for(int j = 0; j < jumlahTersedia - 1; j++){
            for(int k = 0; k < jumlahTersedia - 1 - j; k++){
               if(tempKursi[k].nomorKursi > tempKursi[k+1].nomorKursi){
                  Kursi temp = tempKursi[k];
                  tempKursi[k] = tempKursi[k+1];
                  tempKursi[k+1] = temp;
               }
            }
         }
         int kolom = 0;
         for(int j = 0; j < jumlahTersedia; j++){
            cout << "[" << tempKursi[j].nomorKursi << "]\t";
            kolom++;
            if(kolom % 5 == 0){
               cout << endl;
            }
         }
         string nomorKursi;
         do{
            cout << "\nMasukkan nomor kursi yang ingin dipesan ('0' untuk membatalkan): ";
            cin >> nomorKursi;
            bool valid = false;
            for(int k = 0; k < *jumlahKursi; k++){
               if(kursi[k].nomorKursi == nomorKursi && !kursi[k].isBooked){
                  valid = true;
                  indexChoosen = k;
               }
            }
            if(valid){
               break;
            }else{
               if(nomorKursi == "0"){
                  cout << "Pemesanan dibatalkan." << endl;
                  return;
               }
               cout << "Nomor kursi tidak valid atau sudah dipesan. Silakan pilih nomor lain. Ketik '0' untuk membatalkan pemesanan." << endl;
            }
         }while(true);
         pesanan[*jumlahPesanan].namaPelanggan = inputCustomer.username;
         pesanan[*jumlahPesanan].judulFilm = film[i].judul;
         pesanan[*jumlahPesanan].jadwalTayang = cvJadwal(jadwal);
         pesanan[*jumlahPesanan].idkursi = nomorKursi;
         filePesanan << inputCustomer.username << ":" << film[i].judul << ":" << cvJadwal(jadwal) << ":" << nomorKursi << "\n";
         (*jumlahPesanan)++;
         cout << "Tiket berhasil dipesan!" << endl;
         found = true;
         break;
      }else{
         found = false;
      }
   }
   kursi[indexChoosen].isBooked = true;
   for(int k = 0; k < *jumlahKursi; k++){
       temp << kursi[k].nomorKursi << ":" << (kursi[k].isBooked ? "1" : "0") << "\n";
   }
   if(!found){
      cout << "Film dengan ID " << idFilm << " tidak ditemukan." << endl;
   }
   filePesanan.close();
   temp.close();
   fileKursi.close();
   remove("kursi.txt");
   rename("temp.txt", "kursi.txt");
   cout << "Ingin melakukan pemesanan lagi? (y/n): ";
   char konfirmasi;
   cin >> konfirmasi;
   if(konfirmasi == 'y' || konfirmasi == 'Y'){
      PesanTiket(film, jumlahFilm, inputCustomer, pesanan, jumlahPesanan, kursi, jumlahKursi);
   }
}

void loadData(Film film[], int *jumlahFilm, Pengguna pengguna[], int *jumlahPengguna, Pesanan pesanan[], int *jumlahPesanan, Admins admin[], int *jumlahAdmin, Kursi kursi[], int *jumlahKursi){
   ifstream fileFilm("films.txt");
   if(!fileFilm.is_open()){
      ofstream createFile("films.txt");
      createFile.close();
      *jumlahFilm = 0;
      return;
   }else if(fileFilm.is_open()){
      string id, judul, genre, harga;
      *jumlahAdmin = 0;
      while(getline(fileFilm, id, ':') && getline(fileFilm, judul, ':') && getline(fileFilm, genre, ':') && getline(fileFilm, harga)){
         film[*jumlahFilm].id = stoi(id);
         film[*jumlahFilm].judul = judul;
         film[*jumlahFilm].genre = genre;
         film[*jumlahFilm].harga = stoi(harga);
         (*jumlahFilm)++;
      }
   }
   ifstream filePengguna("customers.txt");
   if(!filePengguna.is_open()){
      ofstream createFile("customers.txt");
      createFile.close();
      *jumlahPengguna = 0;
      return;
   }else if(filePengguna.is_open()){
      string username, password;
      *jumlahAdmin = 0;
      while(getline(filePengguna, username, ':') && getline(filePengguna, password)){
         pengguna[*jumlahPengguna].username = username;
         pengguna[*jumlahPengguna].password = password;
         (*jumlahPengguna)++;
      }
   }
   ifstream filePesanan("pesanan.txt");
   if(!filePesanan.is_open()){
      ofstream createFile("pesanan.txt");
      createFile.close();
      *jumlahPesanan = 0;
      return;
   }else if(filePesanan.is_open()){
      string namaPelanggan, judulFilm, jadwalTayang, idkursi;
      *jumlahAdmin = 0;
      while(getline(filePesanan, namaPelanggan, ':') && getline(filePesanan, judulFilm, ':') && getline(filePesanan, jadwalTayang, ':') && getline(filePesanan, idkursi)){
         pesanan[*jumlahPesanan].namaPelanggan = namaPelanggan;
         pesanan[*jumlahPesanan].judulFilm = judulFilm;
         pesanan[*jumlahPesanan].jadwalTayang = jadwalTayang;
         pesanan[*jumlahPesanan].idkursi = idkursi;
         (*jumlahPesanan)++;
      }
   }

   ifstream fileAdmin("admins.txt");
   if(!fileAdmin.is_open()){
      ofstream createFile("admins.txt");
      createFile << "admin:admin" << endl;
      createFile.close();
      *jumlahAdmin = 1;
      return;
   }else if(fileAdmin.is_open()){
      string username, password;
      *jumlahAdmin = 0;
      while(getline(fileAdmin, username, ':') && getline(fileAdmin, password)){
         admin[*jumlahAdmin].username = username;
         admin[*jumlahAdmin].password = password;
         (*jumlahAdmin)++;
      }
   }
   
   ifstream fileKursi("kursi.txt");
   if(!fileKursi.is_open()){
      ofstream createFile("kursi.txt");
      createFile.close();
      return;
   }else if(fileKursi.is_open()){
      string nomorKursi, isBooked;
      while(getline(fileKursi, nomorKursi, ':') && getline(fileKursi, isBooked)){
         kursi[*jumlahKursi].nomorKursi = nomorKursi;
         kursi[*jumlahKursi].isBooked = (isBooked == "1") ? true : false;
         (*jumlahKursi)++;
      }
   }
}

int main(){
   int pilih;
   bool ulang = true;
   Film film[100];
   int jumlahFilm = 0;
   Pengguna pengguna[100];
   int jumlahPengguna = 0;
   Pesanan pesanan[100];
   int jumlahPesanan = 0;
   Admins admin[100];
   int jumlahAdmin = 0;
   Kursi kursi[500];
   int jumlahKursi = 0;
   loadData(film, &jumlahFilm, pengguna, &jumlahPengguna, pesanan, &jumlahPesanan, admin, &jumlahAdmin, kursi, &jumlahKursi);
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
            MenuAdmin(film, &jumlahFilm, pengguna, &jumlahPengguna, pesanan, &jumlahPesanan, admin, &jumlahAdmin, kursi, &jumlahKursi);
            ulangi(&ulang);
            break;
         case 2:
            RegisterCustomer();
            ulangi(&ulang);
            break;
         case 3:
             MenuPengguna(film, jumlahFilm, pengguna, jumlahPengguna, pesanan, &jumlahPesanan, kursi, &jumlahKursi);
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

void cariFilm(Film film[], int jumlahFilm, string keyword, char tipe){
   system("cls");
   ifstream fileFilm("films.txt");
   string id, judul, genre, harga;
   cout << "Hasil Pencarian untuk '" << keyword << "':\n";
   cout << left
   << setw(5) << "ID" 
   << setw(30) << "Judul" 
   << setw(20) << "Genre" 
   << setw(10) << "Harga" << "\n";
   bool ditemukan = false;
   if(tipe == 'j'){
      for(int i = 0; i < jumlahFilm; i++){
         string lowerJudul = toLower(film[i].judul);
         if(lowerJudul.find(toLower(keyword)) != string::npos){
            cout << left
            << setw(5) << film[i].id
            << setw(30) << film[i].judul
            << setw(20) << film[i].genre
            << setw(10) << film[i].harga << "\n";
            ditemukan = true;
         }
      }
      if(!ditemukan){
         cout << "Film dengan judul '" << keyword << "' tidak ditemukan." << endl;
      }
   }else if(tipe == 'g'){
      for(int i = 0; i < jumlahFilm; i++){
         string lowerGenre = toLower(film[i].genre);
         if(lowerGenre.find(toLower(keyword)) != string::npos){
            cout << left
            << setw(5) << film[i].id
            << setw(30) << film[i].judul
            << setw(20) << film[i].genre
            << setw(10) << film[i].harga << "\n";
            ditemukan = true;
         }
      }
      if(!ditemukan){
         cout << "Film dengan genre '" << keyword << "' tidak ditemukan." << endl;
      }
   } 
   system("pause"); 
}