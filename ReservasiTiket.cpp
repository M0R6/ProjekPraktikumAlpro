#include <iostream>
#include <vector>
using namespace std;

struct Film{
   int id;
   string judul;
   string genre;
   int harga;
};

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
   cout << "Daftar Film Tersedia:\n";
   cout << "ID\tJudul\t\tGenre\t\tHarga\n";
   for(int i = 0; i < daftarFilm.size(); i++){
      cout << daftarFilm[i].id << "\t" << daftarFilm[i].judul << "\t" << daftarFilm[i].genre << "\t" << daftarFilm[i].harga << endl;
   }
}

void searchFilm(string keyword){
   cout << "Hasil Pencarian untuk '" << keyword << "':\n";
   cout << "ID\tJudul\t\tGenre\t\tHarga\n";
   for(int i = 0; i < daftarFilm.size(); i++){
      string lowerJudul = toLower(daftarFilm[i].judul);
      string lowerGenre = toLower(daftarFilm[i].genre);
      if(lowerJudul.find(keyword) != string::npos || lowerGenre.find(keyword) != string::npos){
         cout << daftarFilm[i].id << "\t" << daftarFilm[i].judul << "\t" << daftarFilm[i].genre << "\t" << daftarFilm[i].harga << endl;
      }
   }  
}

void menuCariFilm(){
   int pilih;
   do {
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
               cout << "Masukkan judul film: ";
               cin.ignore();
               getline(cin, keyword);
               searchFilm(keyword);
            }
            break;
         case 2:
            {
               string keyword;
               cout << "Masukkan genre film: ";
               cin.ignore();
               getline(cin, keyword);
               searchFilm(keyword);
            }
            break;
         case 3:
         break;
         default:
         break;
      }
   } while (pilih != 3);
}

int main(){
   int pilih;
   do{
      cout << "==================================================\n";
      cout << "          SYSTEM RESERVASI TIKET BIOSKOP          \n";
      cout << "==================================================\n";
      cout << " [1] Lihat Daftar Film                            \n";
      cout << " [2] Cari Film                                    \n";
      cout << " [3] Pesan Tiket & Pilih Kursi                    \n";
      cout << " [4] Lihat Laporan Riwayat Transaksi              \n";
      cout << " [5] Keluar Aplikasi                              \n";
      cout << "==================================================\n";
      cout << " Pilih menu (1-5): ";
      cin >> pilih;
      switch(pilih){
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
            cout << "Keluar dari aplikasi. Terima kasih!" << endl;
         break;
         default:
            cout << "Menu yang anda pilih tidak tersedia!" << endl;
         break;
      }
   } while (pilih != 5);

   return 0;
}