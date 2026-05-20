#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

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

// Ini nanti dianuin, diambil dari file txt.. sementara hardcode
vector<Film> daftarFilm = {
   {1, "Inception", "Sci-Fi", 45000},
   {2, "The Dark Knight", "Action", 50000},
   {3, "Interstellar", "Sci-Fi", 45000},
   {4, "Conjuring", "Horror", 40000},
   {5, "La La Land", "Romance", 35000},
   {6, "Spirited Away", "Animation", 40000},
   {7, "Parasite", "Thriller", 45000},
   {8, "Avengers: Endgame", "Action", 55000},
   {9, "Coco", "Animation", 35000},
   {10, "The Hangover", "Comedy", 35000}
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
   for(int i = 0; i < daftarFilm.size(); i++){
      cout << daftarFilm[i].id << "\t" << daftarFilm[i].judul << "\t" << daftarFilm[i].genre << "\t" << daftarFilm[i].harga << endl;
   }
}

void searchFilm(string keyword, char tipe){
   system("cls");
   cout << "Hasil Pencarian untuk '" << keyword << "':\n";
   cout << "ID\tJudul\t\tGenre\t\tHarga\n";
   bool ditemukan = false;
   if(tipe == 'j'){
      for(int i = 0; i < daftarFilm.size(); i++){
         string lowerJudul = toLower(daftarFilm[i].judul);
         if(lowerJudul.find(keyword) != string::npos){
            cout << daftarFilm[i].id << "\t" << daftarFilm[i].judul << "\t" << daftarFilm[i].genre << "\t" << daftarFilm[i].harga << endl;
            ditemukan = true;
         }
      }
      if(!ditemukan){
         cout << "Film dengan judul '" << keyword << "' tidak ditemukan." << endl;
      }
   } else if(tipe == 'g'){
      for(int i = 0; i < daftarFilm.size(); i++){
         string lowerGenre = toLower(daftarFilm[i].genre);
         if(lowerGenre.find(keyword) != string::npos){
            cout << daftarFilm[i].id << "\t" << daftarFilm[i].judul << "\t" << daftarFilm[i].genre << "\t" << daftarFilm[i].harga << endl;
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

bool menuAdmin() {
   system("cls"); 
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
   return statusLogin;
}

void registerCustomer() {
   system("cls");
   Pengguna newCustomer;
   cout << "\n=== REGISTER CUSTOMER ===\n";
   cout << "Username: "; cin >> newCustomer.username;
   cout << "Password: "; cin >> newCustomer.password;

   ofstream buatFile("customers.txt", ios::app);
   buatFile << newCustomer.username << ":" << newCustomer.password << "\n";
   buatFile.close();
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