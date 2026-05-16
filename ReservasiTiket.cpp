#include <iostream>
using namespace std;

struct Film{
   int id;
   string judul;
   string genre;
   int harga;
};

struct Pesanan{
   string namaPelanggan;
   string judulFilm;
   string kursi;
};

int main(){
   cout << "==================================================\n";
   cout << "          SYSTEM RESERVASI TIKET BIOSKOP          \n";
   cout << "==================================================\n";
   cout << " [1] Lihat Daftar Film                            \n";
   cout << " [2] Cari Film Berdasarkan ID/Judul               \n";
   cout << " [3] Pesan Tiket & Pilih Kursi                    \n";
   cout << " [4] Lihat Laporan Riwayat Transaksi              \n";
   cout << " [5] Keluar Aplikasi                              \n";
   cout << "==================================================\n";
   cout << " Pilih menu (1-5): ";
}