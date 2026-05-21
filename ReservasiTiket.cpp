#include <iostream>
#include <fstream>
using namespace std;

void tampilDaftarFilm(), menuCariFilm(), tambahFilm(), menuAdmin(), registerCustomer(), menuPengguna(), ulangi(bool &ulang);

struct Film{
   int id;
   string judul;
   string genre;
   int harga;
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

void tampilDaftarFilm(){
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

void searchFilm(string keyword, char tipe){
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

void menuCariFilm(){
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
               searchFilm(keyword, tipe);
            }
            break;
         case 2:
            {
               string keyword;
               char tipe = 'g';
               cout << "Masukkan genre film: ";
               cin.ignore();
               getline(cin, keyword);
               searchFilm(keyword, tipe);
            }
            break;
         case 3:
         break;
         default:
         break;
      }
   } while (pilih != 3);
}

void tambahFilm(){
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

void editJudul(int cari){
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

void editGenre(int cari){
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

void editHarga(int cari){
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

void editFilm(){
   fstream file("films.txt", ios::in);
   string id, judul, genre, harga;
   int cari, pilih;

   tampilDaftarFilm();

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
         editJudul(cari);
         break;
      case 2:
         file.close();
         editGenre(cari);
         break;
      case 3:
         file.close();
         editHarga(cari);
         break;
      default:
         cout << "Pilihan tidak valid!" << endl;
         return;
   }
}

void menuAdmin() {
   system("cls"); 
   int pilih;
   char ulang;
   Pengguna inputAdmin; 
   cout << "\n=== LOGIN ADMIN ===\n";
   cout << "Username: "; cin >> inputAdmin.username;
   cout << "Password: "; cin >> inputAdmin.password;
   ifstream fileAdmin("admins.txt");
   
   Pengguna tempAdmin;
   bool statusLogin = false;
   while (getline(fileAdmin, tempAdmin.username, ':')) {
       getline(fileAdmin, tempAdmin.password); 
       
       if (tempAdmin.username == inputAdmin.username && tempAdmin.password == inputAdmin.password) {
           statusLogin = true;
           cout << "Login berhasil! Selamat datang, " << inputAdmin.username << "!" << endl;
           break; 
       }
   }
   fileAdmin.close();
   if (statusLogin){
      do{
         cout << "===============================\n";
         cout << "         MENU ADMIN            \n";
         cout << "===============================\n";
         cout << "1. Tambah Film\n";
         cout << "2. Edit Film\n";
         cout << "3. Hapus Film\n";
         cout << "4. Lihat Laporan Transaksi\n";
         cout << "5. Logout\n";
         cout << "Pilih menu (1-5): ";
         cin >> pilih;
         switch (pilih){
            case 1:
               tambahFilm();
               cout << "Kembali ke menu admin? (y/n): ";
               cin >> ulang;
               break;
            case 2:
               editFilm();
               cout << "Kembali ke menu admin? (y/n): ";
               cin >> ulang;
               break;
            case 3:
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
      }while(pilih != 5 && (ulang == 'y' || ulang == 'Y'));
   }else{
       cout << "Login gagal! Pastikan username dan password benar." << endl;
   }
}

void registerCustomer() {
   system("cls");
   Pengguna newCustomer;
   cout << "\n=== REGISTER CUSTOMER ===\n";
   cout << "Username: "; cin >> newCustomer.username;
   cout << "Password: "; cin >> newCustomer.password;

   ofstream File("customers.txt", ios::app);
   File << newCustomer.username << ":" << newCustomer.password << "\n";
   File.close();
}

void menuPengguna(){  
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
   bool statusLogin = false;
   while (getline(fileCustomer, tempCust.username, ':')){
      getline(fileCustomer, tempCust.password); 

      if (tempCust.username == inputCustomer.username && tempCust.password == inputCustomer.password){
         statusLogin = true;
         cout << "Login berhasil! Selamat datang, " << inputCustomer.username << "!" << endl;
         break;
      }
   }
   fileCustomer.close();
   if(statusLogin){
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
         switch (pilih){
         case 1:
            tampilDaftarFilm();
            system("pause");
            break;
         case 2:
            menuCariFilm();
            system("pause");
            break;
         case 3:
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
            menuAdmin();
            ulangi(ulang);
            break;
         case 2:
            registerCustomer();
            ulangi(ulang);
            break;
         case 3:
             menuPengguna();
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