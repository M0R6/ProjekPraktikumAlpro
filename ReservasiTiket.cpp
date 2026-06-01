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

struct Teater{
   string namaTeater;
   string lokasi;
   int kapasitas;
   int baris;
   int kolom;
   string layout;
};

struct Pengguna{
   string username;
   string password;
};

struct Pesanan{
   string namaPelanggan;
   string judulFilm;
   string kursi;
};

string toLower(string str){
   for(int i = 0; i < str.length(); i++){
      str[i] = tolower(str[i]);
   }
   return str;
}

// Utility
void ulangi(bool &ulang);
void cariFilm(string keyword, char tipe);

// Admin
void MenuAdmin();
void AdminMenuFilm();
void AdminMenuTeater();
void TambahFilm();
void EditFilm();
void EditJudul(int cari);
void EditGenre(int cari);
void EditHarga(int cari);
void HapusFilm();

void LihatDaftarTeater();
void TambahTeater();
void EditTeater();
void EditNamaTeater(int cari);
void EditLokasi(int cari);
void EditKapasitas(int cari);

// Customer
void RegisterCustomer();
void MenuPengguna();
void TampilDaftarFilmCustomer();
void PesanTiket(int idFilm);

// Film
void TampilDaftarFilm();
void MenuCariFilm();

void MenuAdmin() {
   system("cls"); 
   int pilih;
   char ulang;
   Pengguna inputAdmin; 
   cout << "\n=== LOGIN ADMIN ===\n";
   cout << "Username: "; cin >> inputAdmin.username;
   cout << "Password: "; cin >> inputAdmin.password;
   ifstream fileAdmin("admins.txt");
   
   Pengguna tempAdmin;
   bool statusLogin = true;
   // while (getline(fileAdmin, tempAdmin.username, ':')) {
   //     getline(fileAdmin, tempAdmin.password); 
       
   //     if (tempAdmin.username == inputAdmin.username && tempAdmin.password == inputAdmin.password) {
   //         statusLogin = true;
   //         cout << "Login berhasil! Selamat datang, " << inputAdmin.username << "!" << endl;
   //         break; 
   //     }
   // }
   // fileAdmin.close();
   if (statusLogin){
      do{
         cout << "===============================\n";
         cout << "         MENU ADMIN            \n";
         cout << "===============================\n";
         cout << "1. Menu Film\n";
         cout << "2. Menu Teater\n";
         cout << "3. Lihat Laporan Transaksi\n";
         cout << "4. Logout\n";
         cout << "Pilih menu (1-4): ";
         cin >> pilih;
         switch (pilih){
            case 1:
               AdminMenuFilm();
               cout << "Kembali ke menu admin? (y/n): ";
               cin >> ulang;
               break;
            case 2:
               AdminMenuTeater();
               cout << "Kembali ke menu admin? (y/n): ";
               cin >> ulang;
               break;
            case 3:
               cout << "Masih dalam pengembangan..." << endl;
               cout << "Kembali ke menu admin? (y/n): ";
               cin >> ulang;
               break;
            case 4:
               cout << "Logout berhasil!" << endl;
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

void AdminMenuFilm(){
   system("cls");
   int pilih;
   cout << "===============================\n";
   cout << "         MENU FILM             \n";
   cout << "===============================\n";
   cout << "Daftar Film:\n";
   TampilDaftarFilm();
   cout << "===============================\n";
   cout << "1. Tambah Film\n";
   cout << "2. Edit Film\n";
   cout << "3. Hapus Film\n";
   cout << "4. Kembali ke Menu Admin\n";
   cout << "Pilih menu (1-4): ";
   cin >> pilih;
   switch (pilih){
      case 1:
         TambahFilm();
         break;
      case 2:
         EditFilm();
         break;
      case 3:
         HapusFilm();
         break;
      case 4:
         break;
      default:
         cout << "Menu yang anda pilih tidak tersedia!" << endl;
         break;
   }
}

void TampilDaftarFilm(){
   system("cls");
   cout << "Daftar Film Tersedia:\n";
   cout << "ID\tJudul\t\tGenre\t\tHarga\n";
   ifstream fileFilm("films.txt");
   if(fileFilm.is_open()){
      string id, judul, genre, harga;
      while(getline(fileFilm, id, ':') && getline(fileFilm, judul, ':') && getline(fileFilm, genre, ':') && getline(fileFilm, harga)){
         Film film;
         film.id = stoi(id);
         film.judul = judul;
         film.genre = genre;
         film.harga = stoi(harga);
         cout << film.id << "\t" << film.judul << "\t" << film.genre << "\t" << film.harga << endl;
      }
      
   }
}

void TambahFilm(){
   ofstream fileFilm("films.txt", ios::app);
   Film newFilm;
   cout << "Masukkan ID Film: ";
   cin >> newFilm.id;
   cout << "Masukkan Judul Film: ";
   cin.ignore();
   getline(cin, newFilm.judul);
   cout << "Masukkan Genre Film: ";
   getline(cin, newFilm.genre);
   cout << "Masukkan Harga Tiket: ";
   cin >> newFilm.harga;
   fileFilm << newFilm.id << ":" << newFilm.judul << ":" << newFilm.genre << ":" << newFilm.harga << "\n";
   fileFilm.close();
   cout << "Film berhasil ditambahkan!" << endl;
}

void EditFilm(){
   fstream file("films.txt", ios::in);
   string id, judul, genre, harga;
   int cari, pilih;

   //TampilDaftarFilm();

   cout << "ID film yang ingin diubah datanya: ";
   cin >> cari;

   cout << "Data Film yang ingin diubah:\n";
   while(getline(file, id, ':') && getline(file, judul, ':') && getline(file, genre, ':') && getline(file, harga)){
      if(stoi(id) == cari){
         cout << "ID: " << id << endl;
         cout << "Judul: " << judul << endl;
         cout << "Genre: " << genre << endl;
         cout << "Harga: " << harga << endl;
         break;
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
         file.close();
         EditJudul(cari);
         break;
      case 2:
         file.close();
         EditGenre(cari);
         break;
      case 3:
         file.close();
         EditHarga(cari);
         break;
      default:
         cout << "Pilihan tidak valid!" << endl;
         return;
   }
}

void EditJudul(int cari){
   string id, judul, genre, harga, ganti;
   cout << "Masukkan judul baru: ";
   cin.ignore();
   getline(cin, ganti);

   ifstream file("films.txt");
   ofstream temp("temp.txt");

   if (!file || !temp) {
       cout << "Gagal membuka file!" << endl;
       return;
   }
   while(getline(file, id, ':') && getline(file, judul, ':') && getline(file, genre, ':') && getline(file, harga)){
      if(stoi(id) == cari){
         temp << id << ":" << ganti << ":" << genre << ":" << harga << "\n";
      }else{
         temp << id << ":" << judul << ":" << genre << ":" << harga << "\n";
      }
   }
   file.close();
   temp.close();
   remove("films.txt");
   rename("temp.txt", "films.txt");
   cout << "Judul film berhasil diubah!" << endl;
}

void EditGenre(int cari){
   string id, judul, genre, harga, ganti;
   cout << "Masukkan genre baru: ";
   cin.ignore();
   getline(cin, ganti);

   ifstream file("films.txt");
   ofstream temp("temp.txt");

   if (!file || !temp) {
       cout << "Gagal membuka file!" << endl;
       return;
   }
   while(getline(file, id, ':') && getline(file, judul, ':') && getline(file, genre, ':') && getline(file, harga)){
      if(stoi(id) == cari){
         temp << id << ":" << judul << ":" << ganti << ":" << harga << "\n";
      }else{
         temp << id << ":" << judul << ":" << genre << ":" << harga << "\n";
      }
   }
   file.close();
   temp.close();
   remove("films.txt");
   rename("temp.txt", "films.txt");
   cout << "Genre film berhasil diubah!" << endl;
}

void EditHarga(int cari){
   string id, judul, genre, harga, ganti;
   cout << "Masukkan harga baru: ";
   cin >> ganti;

   ifstream file("films.txt");
   ofstream temp("temp.txt");

   if (!file || !temp) {
       cout << "Gagal membuka file!" << endl;
       return;
   }
   while(getline(file, id, ':') && getline(file, judul, ':') && getline(file, genre, ':') && getline(file, harga)){
      if(stoi(id) == cari){
         temp << id << ":" << judul << ":" << genre << ":" << ganti << "\n";
      }else{
         temp << id << ":" << judul << ":" << genre << ":" << harga << "\n";
      }
   }
   file.close();
   temp.close();
   remove("films.txt");
   rename("temp.txt", "films.txt");
   cout << "Harga film berhasil diubah!" << endl;
}

void HapusFilm(){
   fstream file("films.txt", ios::in);
   string id, judul, genre, harga;
   int cari;

   //tampilDaftarFilm();

   cout << "ID film yang ingin dihapus: ";
   cin >> cari;

   ofstream temp("temp.txt");
   bool ditemukan = false;

   while(getline(file, id, ':') && getline(file, judul, ':') && getline(file, genre, ':') && getline(file, harga)){
      if(stoi(id) == cari){
         ditemukan = true;
         continue; 
      }
      temp << id << ":" << judul << ":" << genre << ":" << harga << "\n";
   }

   file.close();
   temp.close();

   if(ditemukan){
      remove("films.txt");
      rename("temp.txt", "films.txt");
      cout << "Film berhasil dihapus!" << endl;
   } else {
      cout << "Film dengan ID " << cari << " tidak ditemukan." << endl;
      remove("temp.txt"); 
   }
}

void AdminMenuTeater(){
   system("cls");
   int pilih;
   cout << "===============================\n";
   cout << "         MENU TEATER           \n";
   cout << "===============================\n";
   cout << "1. Lihat Daftar Teater\n";
   cout << "2. Tambah Teater\n";
   cout << "3. Edit Teater\n";
   cout << "4. Hapus Teater\n";
   cout << "5. Kembali ke Menu Admin\n";
   cout << "Pilih menu (1-5): ";
   cin >> pilih;
   switch (pilih){
      case 1:
         LihatDaftarTeater();
         break;
      case 2:
         TambahTeater();
         break;
      case 3:
         EditTeater();
         break;
      case 4:
         break;
      case 5:
         break;
      default:
         cout << "Menu yang anda pilih tidak tersedia!" << endl;
         break;
   }
}

void LihatDaftarTeater(){
   system("cls");
   cout << "Daftar Teater Tersedia:\n";
   cout << left << setw(30) << "Nama Teater" << setw(20) << "Lokasi" << setw(10) << "Kapasitas" << setw(10) << "Baris" << setw(10) << "Kolom" << "\n";
   ifstream fileTeater("teaters.txt");
   if(fileTeater.is_open()){
      string namaTeater, lokasi, kapasitas, baris, kolom, layout;
      cout << string(80, '=') << endl;
      while(getline(fileTeater, namaTeater, ':') && getline(fileTeater, lokasi, ':') && getline(fileTeater, kapasitas, ':') && getline(fileTeater, baris, ':') && getline(fileTeater, kolom, ':') && getline(fileTeater, layout)){
         Teater teater;
         teater.namaTeater = namaTeater;
         teater.lokasi = lokasi;
         teater.kapasitas = stoi(kapasitas);
         teater.baris = stoi(baris);
         teater.kolom = stoi(kolom);
         teater.layout = layout;
         cout << left << setw(30) << teater.namaTeater << setw(20) << teater.lokasi << setw(10) << teater.kapasitas << setw(10) << teater.baris << setw(10) << teater.kolom << endl;
      }
      cout << string(80, '=') << endl;
   }
}

void TambahTeater(){
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

   string layout = "";
   for (int i = 0; i < newTeater.baris; i++) {
      char hurufBaris = 'A' + i;
      for (int j = 1; j <= newTeater.kolom; j++) {
         layout += hurufBaris + to_string(j);
         if (j != newTeater.kolom) {
               layout += ",";
         }
      }
      if (i != newTeater.baris - 1) {
         layout += "|";
      }
   }
   newTeater.kapasitas = newTeater.baris * newTeater.kolom;

   fileTeater << newTeater.namaTeater << ":" << newTeater.lokasi << ":" << newTeater.kapasitas << ":" << newTeater.baris << ":" << newTeater.kolom << ":" << layout << "\n";
   fileTeater.close();
   cout << "\nTeater berhasil ditambahkan!\n";
}

void EditTeater(){
   fstream file("teaters.txt", ios::in);
   string namaTeater, lokasi, kapasitas, baris, kolom, layout;
   int cari, pilih;
   cout << "ID teater yang ingin diubah datanya: ";
   cin >> cari;

   cout << "Data Teater yang ingin diubah:\n";
   while(getline(file, namaTeater, ':') && getline(file, lokasi, ':') && getline(file, kapasitas, ':') && getline(file, baris, ':') && getline(file, kolom, ':') && getline(file, layout)){
      if(stoi(kapasitas) == cari){
         cout << "Nama Teater: " << namaTeater << endl;
         cout << "Lokasi: " << lokasi << endl;
         cout << "Kapasitas: " << kapasitas << endl;
         cout << "Baris: " << baris << endl;
         cout << "Kolom: " << kolom << endl;
         break;
      }
   }

   cout << "Pilihan edit:\n";
   cout << "1. Nama Teater\n";
   cout << "2. Lokasi\n";
   cout << "3. Kapasitas\n";
   cout << "Pilih data yang ingin diubah (1-3): ";
   cin >> pilih;

   switch(pilih){
      case 1:
         file.close();
         EditNamaTeater(cari);
         break;
      case 2:
         file.close();
         EditLokasi(cari);
         break;
      case 3:
         file.close();
         EditKapasitas(cari);
         break;
      default:
         cout << "Pilihan tidak valid!" << endl;
         return;
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

void MenuPengguna(){  
   system("cls");
   int pilih;
   Pengguna inputCustomer; 
   cout << "\n=== LOGIN CUSTOMER ===\n";
   cout << "Username: ";
   cin >> inputCustomer.username;
   cout << "Password: ";
   cin >> inputCustomer.password;
   ifstream fileCustomer("customers.txt");

   Pengguna tempCust; 
   bool statusLogin = true;
   // while (getline(fileCustomer, tempCust.username, ':')){
   //    getline(fileCustomer, tempCust.password); 

   //    if (tempCust.username == inputCustomer.username && tempCust.password == inputCustomer.password){
   //       statusLogin = true;
   //       cout << "Login berhasil! Selamat datang, " << inputCustomer.username << "!" << endl;
   //       break;
   //    }
   // }
   // fileCustomer.close();
   if(statusLogin){
      bool ulang = true;
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
         string konfirmasi;
         switch (pilih){
         case 1:
            TampilDaftarFilmCustomer();
            cout << "Pesan tiket sekarang? (y/n): ";
            cin >> konfirmasi;
            if (konfirmasi == "y" || konfirmasi == "Y") {
               PesanTiket(0);
            }
            break;
         case 2:
            MenuCariFilm();
            ulangi(ulang);
            break;
         case 3:
            PesanTiket(0);
            break;
         case 4:
            break;
         case 5:
            cout << "Logout berhasil!" << endl;
            break;
         default:
            cout << "Menu yang anda pilih tidak tersedia!" << endl;
            break;
         }
      }while(pilih != 5);
      } else {
         cout << "Login gagal! Pastikan username dan password benar." << endl;
      }
}

void TampilDaftarFilmCustomer(){
   system("cls");
   cout << "Daftar Film Tersedia:\n";
   cout << "No\tJudul\t\tGenre\t\tHarga\n";
   ifstream fileFilm("films.txt");
   if(fileFilm.is_open()){
      string id, judul, genre, harga;
      int no = 1;
      while(getline(fileFilm, id, ':') && getline(fileFilm, judul, ':') && getline(fileFilm, genre, ':') && getline(fileFilm, harga)){
         Film film;
         film.id = no++;
         film.judul = judul;
         film.genre = genre;
         film.harga = stoi(harga);
         cout << film.id << "\t" << film.judul << "\t" << film.genre << "\t" << film.harga << endl;
      }
      
   }
}

void MenuCariFilm(){
   int pilih;
   do {
      system("cls");
      cout << "Cari Film Berdasarkan:\n";
      cout << "1. Judul\n";
      cout << "2. Genre\n";
      cout << "3. Kembali ke Menu Utama\n";
      cout << "Pilih (1-3): ";
      cin >> pilih;
      switch(pilih){
         case 1:
            {
               string keyword;
               char tipe = 'j';
               cout << "Masukkan judul film: ";
               cin.ignore();
               getline(cin, keyword);
               cariFilm(keyword, tipe);
            }
            break;
         case 2:
            {
               string keyword;
               char tipe = 'g';
               cout << "Masukkan genre film: ";
               cin.ignore();
               getline(cin, keyword);
               cariFilm(keyword, tipe);
            }
            break;
         case 3:
         break;
         default:
         break;
      }
   } while (pilih != 3);
}

void PesanTiket(int idFilm){
   system("cls");
   if(idFilm == 0){
      TampilDaftarFilmCustomer();
      cout << "Masukkan ID film yang ingin dipesan: ";
      cin >> idFilm;
   }
}

int main(){
   int pilih;
   bool ulang = true;
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
            MenuAdmin();
            ulangi(ulang);
            break;
         case 2:
            RegisterCustomer();
            ulangi(ulang);
            break;
         case 3:
             MenuPengguna();
             ulangi(ulang);
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

void ulangi(bool &ulang){
   char pilihan;
   cout << "Apakah Anda ingin kembali ke menu utama? (y/n): ";
   cin >> pilihan;
   if(pilihan == 'y' || pilihan == 'Y'){
      ulang = true;
   } else {
      ulang = false;
      cout << "Keluar dari aplikasi. Terima kasih!" << endl;
   }
}

void cariFilm(string keyword, char tipe){
   system("cls");
   ifstream fileFilm("films.txt");
   string id, judul, genre, harga;
   cout << "Hasil Pencarian untuk '" << keyword << "':\n";
   cout << "ID\tJudul\t\tGenre\t\tHarga\n";
   bool ditemukan = false;
   if(tipe == 'j'){
      while(getline(fileFilm, id, ':') && getline(fileFilm, judul, ':') && getline(fileFilm, genre, ':') && getline(fileFilm, harga)){
         Film film;
         film.id = stoi(id);
         film.judul = judul;
         film.genre = genre;
         film.harga = stoi(harga);
         string lowerJudul = toLower(film.judul);
         if(lowerJudul.find(toLower(keyword)) != string::npos){
            cout << film.id << "\t" << film.judul << "\t" << film.genre << "\t" << film.harga << endl;
            ditemukan = true;
         }
      }
      if(!ditemukan){
         cout << "Film dengan judul '" << keyword << "' tidak ditemukan." << endl;
      }
   } else if(tipe == 'g'){
      while(getline(fileFilm, id, ':') && getline(fileFilm, judul, ':') && getline(fileFilm, genre, ':') && getline(fileFilm, harga)){
         Film film;
         film.id = stoi(id);
         film.judul = judul;
         film.genre = genre;
         film.harga = stoi(harga);
         string lowerGenre = toLower(film.genre);
         if(lowerGenre.find(toLower(keyword)) != string::npos){
            cout << film.id << "\t" << film.judul << "\t" << film.genre << "\t" << film.harga << endl;
            ditemukan = true;
         }
      }
      if(!ditemukan){
         cout << "Film dengan genre '" << keyword << "' tidak ditemukan." << endl;
      }
   } 
   system("pause"); 
}
