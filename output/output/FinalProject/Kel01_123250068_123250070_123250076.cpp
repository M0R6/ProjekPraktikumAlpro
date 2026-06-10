// Kelompok 1 - 123250068, 123250070, 123250076
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct Warga{
   long long NIK;
   string nama;
   string alamat;
};

Warga dataWarga[10];
int banyakData = 0;

void input(), tampil(), search(), sort(), seqsearch(), binsearch(), bubblesort(), selectsort(), insertsort(), shellsort(), quicksort(), mergesort(), OperasiFile(), mergingSambung(), mergingUrutNIK();

void mergingUrutNIK() {
    int jumlahFile;
    string namaFile, line;

    Warga temp[100];
    int index = 0;

    cout << "MERGE URUT (BERDASARKAN NIK)\n";
    cout << "-----------------------------\n";
    cout << "Banyaknya file (max 4): ";
    cin >> jumlahFile;

    if (jumlahFile < 1 || jumlahFile > 4) {
        cout << "Jumlah file tidak valid!\n";
        return;
    }

    for (int i = 0; i < jumlahFile; i++) {
        cout << "Masukkan nama file ke-" << i+1 << ": ";
        cin >> namaFile;

        ifstream file(namaFile);
        if (!file.is_open()) {
            cout << "File tidak ditemukan!\n";
            continue;
        }

        while (getline(file, line)) {
            string nikStr, nama, alamat;

            int pos1 = line.find(':');
            int pos2 = line.find(':', pos1 + 1);

            nikStr = line.substr(0, pos1);
            nama = line.substr(pos1 + 1, pos2 - pos1 - 1);
            alamat = line.substr(pos2 + 1);

            temp[index].NIK = stoll(nikStr);
            temp[index].nama = nama;
            temp[index].alamat = alamat;

            index++;
        }

        file.close();
    }

    for (int i = 0; i < index - 1; i++) {
        for (int j = 0; j < index - i - 1; j++) {
            if (temp[j].NIK > temp[j + 1].NIK) {
                swap(temp[j], temp[j + 1]);
            }
        }
    }

    string fileHasil;
    cout << "Masukkan nama file hasil: ";
    cin >> fileHasil;

    ofstream out(fileHasil);

    for (int i = 0; i < index; i++) {
        out << temp[i].NIK << ":"
            << temp[i].nama << ":"
            << temp[i].alamat << endl;
    }

    out.close();

    cout << "Merge urut berdasarkan NIK berhasil!\n";
}

void hapusData() {
   string namaFile, cariNIK, tempNIK, tempNama, tempAlamat;
   cout << "Data yang tersedia:\n";
   ifstream readFile("daftarFile.txt");
   string fileName;
   while (readFile >> fileName) {
       cout << "- " << fileName << endl;
   }
   readFile.close();
   cout << "HAPUS DATA\n";
   cout << "==========\n";
   cout << "Masukkan nama file: ";
   cin >> namaFile;
   cout << "Masukkan NIK yang ingin dihapus: ";
   cin >> cariNIK;
   ifstream file(namaFile);
   if (!file.is_open()) {
       cout << "File tidak ditemukan!\n";
       return;
   }
   ofstream temp("temp.txt");
   bool found = false;
   while (getline(file, tempNIK, ':') && getline(file, tempNama, ':') && getline(file, tempAlamat)) {
       if (tempNIK != cariNIK) {
           temp << tempNIK << ":" << tempNama << ":" << tempAlamat << endl;
       } else {
           found = true;
       }
   }
   file.close();
   temp.close();
   if(found){
       remove(namaFile.c_str());
       rename("temp.txt", namaFile.c_str());
       cout << "Data berhasil dihapus!\n";
   }else{
       cout << "NIK tidak ditemukan!\n";
       remove("temp.txt");
   }
}

void OperasiFile() {
int pilih;
system("cls");
string text;
ifstream readFile("daftarfile.txt");
while (readFile >> text) {
    cout << text << "\n";
}
cout << "Daftar File yang tersedia\n";
system("pause");
system("cls");

do {
        cout << "MENU OPERASI FILE:" << endl;
        cout << "=========================" << endl;
        cout << "1. MERGING SAMBUNG" << endl;
        cout << "2. MERGING URUT" << endl;
        cout << "3. SPLITTING" << endl;
        cout << "4. UPDATING DATA" << endl;
        cout << "5. HAPUS DATA" << endl;
        cout << "6. Kembali ke MENU UTAMA" << endl;
        cout << "=========================" << endl;
        cout << "Pilih : ";
        cin >> pilih;

        cout << endl;
        system("cls");
        switch(pilih) {
            case 1:
                mergingSambung();
                break;
            case 2:
                mergingUrutNIK();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                hapusData();
                break;
            case 6:
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }

        cout << endl;

    } while (pilih != 6);

}

void mergingSambung() {
    string file1, file2, fileHasil;
    string line;
    string text;
    ifstream readFile("daftarfile.txt");
    while (readFile >> text) {
    cout << text << "/n";
    }
    cout << endl;
    cout << "Masukkan nama file pertama: ";
    cin >> file1;
    cout << "Masukkan nama file kedua: ";
    cin >> file2;
    cout << "Masukkan nama file hasil: ";
    cin >> fileHasil;

    ifstream f1(file1);
    ifstream f2(file2);
    ofstream fout(fileHasil);

    if (!f1.is_open() || !f2.is_open()) {
        cout << "Salah satu file tidak ditemukan!" << endl;
        return;
    }

    // copy file 1
    while (getline(f1, line)) {
        fout << line << endl;
    }

    // copy file 2
    while (getline(f2, line)) {
        fout << line << endl;
    }

    cout << "Merging sambung berhasil ke file: " << fileHasil << endl;

    f1.close();
    f2.close();
    fout.close();
}

void input(){
   string namaFile, namaFileInput;
   bool fileExists = false;
   ofstream makeFile("daftarFile.txt", ios::app);
   ifstream readFile("daftarFile.txt");

   system("cls");
   cout << "== Menu Input ==" << endl;
   cout << "Banyak data (maks. 10): ";
   cin >> banyakData;
   cout << "Disimpan di file: ";
   cin >> namaFileInput;
   while(getline(readFile, namaFile)){
      if(namaFile == namaFileInput){
         fileExists = true;
         break;
      }
   }

   if(!fileExists){
      makeFile << namaFileInput << "\n";
   }

   ofstream file(namaFileInput, ios::app);
   
   if(banyakData > 0 && banyakData <= 10 && !cin.fail()){
      for(int i = 0; i < banyakData; i++){
         cout << "Data ke-" << i+1 << ":" << endl;
         cout << "  NIK: ";
         cin >> dataWarga[i].NIK;
         cout << "  Nama: ";
         cin.ignore(999, '\n');
         getline(cin, dataWarga[i].nama);
         cout << "  Alamat: ";
         getline(cin, dataWarga[i].alamat);
         file << dataWarga[i].NIK << ":" << dataWarga[i].nama << ":" << dataWarga[i].alamat << "\n";
      }
   }else{
      cout << "Input yang anda masukkan tidak valid, input angka 1-10 saja!" << endl;
      cin.clear();
      cin.ignore(999, '\n');
   }

}

void tampil(){
   ifstream file("daftarFile.txt");
   string namaFile;
   cout << "Data yang tersedia:\n";
   while(getline(file, namaFile)){
      cout << "- " << namaFile << endl;
   }
   file.close();
   cout << "================================================================================" << endl;
   cout << "File yang dipilih: ";
   string fileDipilih, tempNIK, tempNama, tempAlamat;
   cin >> fileDipilih;
   ifstream fileData(fileDipilih);
   if(!fileData.is_open()){
      cout << "File tidak ditemukan!" << endl;
      return;
   }
   cout << setfill(' ');
   cout << left << setw(4) << "No." <<
   setw(20) << "NIK" <<
   setw(36) << "Nama" <<
   setw(36) << "Alamat" << endl;
   cout << setfill(' ');
   int nomor = 1;
   while(getline(fileData, tempNIK, ':') && getline(fileData, tempNama, ':') && getline(fileData, tempAlamat)){
      cout << left << setw(4) << nomor++ << setw(20) << tempNIK << setw(36) << tempNama << setw(36) << tempAlamat << endl;
   }
}

void search(){
   int pilih;
   char ulangi;
   do{
      system("cls");
      cout << "=== Menu Searching ===" << endl;
      cout << "1. Sequencial Search" << endl
      << "2. Binary Search" << endl
      << "3. Kembali ke menu utama" << endl
      << "Pilih: ";
      cin >> pilih;
      switch(pilih){
         case 1:
            seqsearch();
         break;
         case 2:
            binsearch();
         break;
         case 3:
            ulangi = 't';
         break;
      default:
         cout << "Menu yang anda pilih tidak tersedia!" << endl
         << "=============================="<< endl;
      break;
      }
      if(pilih != 3){
         cout << "Kembali ke menu searching? (y/n):";
         cin >> ulangi;
      }
      
   }while(ulangi == 'y' || ulangi == 'Y');
}

void seqsearch(){
   fstream file("daftarFile.txt");
   string namaFile;
   bool cek = true;
   long long NilaiCari;
   string fileDipilih, tempNIK, tempNama, tempAlamat;
   char Opsi;
   cout << "Data yang tersedia:\n";
   while(getline(file, namaFile)){
      cout << "- " << namaFile << endl;
   }
   file.close();
   cout << "================================================================================" << endl;
   cout << "File yang dipilih: ";
   cin >> fileDipilih;
   ifstream fileData(fileDipilih);
   if(!fileData.is_open()){
      cout << "File tidak ditemukan!" << endl;
      return;
   }
   do {
   cout << "\n\nSEQUENSIAL SEARCH\n";
   cout << "==================\n\n";
   cout << "NIK yang dicari\n"; 
   cin >> NilaiCari;
   while(getline(fileData, tempNIK, ':') && getline(fileData, tempNama, ':') && getline(fileData, tempAlamat)){
      if (stoll(tempNIK) == NilaiCari) {
         cout << "Data ditemukan\n" << "==========================\nNIK      : " << tempNIK << "\nNama     : " << tempNama << "\nAlamat   : " << tempAlamat
         << "\n==========================";
         cek = false;
         break;
      }else{
         cek = true;
      }
   }
   if (cek) {
      cout << NilaiCari << " tidak ditemukan";
   }
   cout << "\nUlangi sequence search? (y/t) :"; 
   cin >> Opsi;
   } while (Opsi == 'y');
}

void binsearch() {
   fstream file("daftarFile.txt");
   string namaFile;
   string fileDipilih, tempNIK, tempNama, tempAlamat;
   int dataCount = 0;
   cout << "Data yang tersedia:\n";
   while(getline(file, namaFile)){
      cout << "- " << namaFile << endl;
   }
   file.close();
   cout << "================================================================================" << endl;
   cout << "File yang dipilih: ";
   cin >> fileDipilih;

   ifstream fileData(fileDipilih);
   if(!fileData.is_open()){
      cout << "File tidak ditemukan!" << endl;
      return;
   }
   while(getline(fileData, tempNIK, ':') && getline(fileData, tempNama, ':') && getline(fileData, tempAlamat)){
      dataCount++;
   }
   fileData.close();
   ifstream fileDataBaru(fileDipilih);
   Warga dataWargaBin[dataCount];
   int index = 0;
   while(getline(fileDataBaru, tempNIK, ':') && getline(fileDataBaru, tempNama, ':') && getline(fileDataBaru, tempAlamat)){
      dataWargaBin[index].NIK = stoll(tempNIK);
      dataWargaBin[index].nama = tempNama;
      dataWargaBin[index].alamat = tempAlamat;
      index++;
   }
   fileDataBaru.close();

   for (int i = 0; i < dataCount - 1; i++) {
      for (int j = 0; j < dataCount - 1 - i; j++) {
         if (dataWargaBin[j].NIK > dataWargaBin[j + 1].NIK) {
            Warga swap = dataWargaBin[j];
            dataWargaBin[j] = dataWargaBin[j + 1];
            dataWargaBin[j + 1] = swap;
         }
      }
   }
     
   int low = 0;
   int high = dataCount - 1;
   long long NilaiCari;

   cout << "\n\nBINARY SEARCH\n";
   cout << "==================\n\n";
   cout << "NIK yang dicari: ";
   cin >> NilaiCari;

   bool cek = true;

   while (low <= high) {
      int mid = (low + high) / 2;

      if (dataWargaBin[mid].NIK == NilaiCari) {
      cout << "Data ditemukan\n" << "==========================\nNIK      : " << dataWargaBin[mid].NIK << "\nNama     : " << dataWargaBin[mid].nama << "\nAlamat   : " << dataWargaBin[mid].alamat
      << "\n==========================\n";
      cek = false;
      break;
      }
      else if (NilaiCari < dataWargaBin[mid].NIK) {
         high = mid - 1; 
      }
      else {
         low = mid + 1;  
      }
   }

   if (cek) {
      cout << "Data tidak ditemukan\n";
   }
}

void sort(){
   int pilih;
   char ulangi;
   do{
      system("cls");
      cout << "=== Menu Sort ===" << endl;
      cout << "1. Bubble Sort" << endl
      << "2. Selection Sort" << endl
      << "3. Insertion Sort" << endl
      << "4. Shell Sort" << endl
      << "5. Quick Sort" << endl
      << "6. Merge Sort" << endl
      << "7. kembali ke menu utama" << endl
      << "Pilih: ";
      cin >> pilih;
      switch(pilih){
         case 1:
            bubblesort();
         break;
         case 2:
            selectsort();
         break;
         case 3:
            insertsort();
         break;
         case 4:
            shellsort();
         break;
         case 5:
            quicksort();
         break;
         case 6:
            mergesort();
         break;
         case 7:
            ulangi = 't';
         break;
      default:
         cout << "Menu yang anda pilih tidak tersedia!" << endl
         << "=============================="<< endl;
      break;
      }
      if(pilih != 7){
         cout << "Ulangi? (y/n):";
         cin >> ulangi;
      }
      
   }while(ulangi == 'y' || ulangi == 'Y');
}

void bubblesort() {
   ifstream file("daftarFile.txt");
   cout << "Data yang tersedia:\n";
   string fileDipilih, namaFile, tempNIK, tempNama, tempAlamat;
   int dataCount = 0;
   while(getline(file, namaFile)){
      cout << "- " << namaFile << endl;
   }
   file.close();

   cout << "Pilih file: ";
   cin >> fileDipilih;

   ifstream fileData(fileDipilih);
   if(!fileData.is_open()){
      cout << "File tidak ditemukan!" << endl;
      return;
   }
   while(getline(fileData, tempNIK, ':') && getline(fileData, tempNama, ':') && getline(fileData, tempAlamat)){
      dataCount++;
   }

   fileData.clear();
   fileData.seekg(0, ios::beg);
   Warga temp[dataCount];
   int index = 0;
   cout << "\nData sebelum diurutkan\n";
   cout << "====================================\n";
   cout << setfill(' ');
   cout << left << setw(4) << "No." <<
   setw(20) << "NIK" <<
   setw(36) << "Nama" <<
   setw(36) << "Alamat" << endl;
   cout << setfill(' ');
   int nomor = 1;
   while(getline(fileData, tempNIK, ':') && getline(fileData, tempNama, ':') && getline(fileData, tempAlamat)){
      temp[index].NIK = stoll(tempNIK);
      temp[index].nama = tempNama;
      temp[index].alamat = tempAlamat;
      cout << left << setw(4) << nomor++ << setw(20) << tempNIK << setw(36) << tempNama << setw(36) << tempAlamat << endl;
      index++;
   }
   fileData.close();
   
   for (int i = 0; i < dataCount - 1; i++) {
       for (int j = 0; j < dataCount - 1 - i; j++) {
           if (temp[j].NIK > temp[j + 1].NIK) {
               Warga swap = temp[j];
               temp[j] = temp[j + 1];
               temp[j + 1] = swap;
           }
       }
   }
   cout << "\nData (Sorted by NIK):\n";
   cout << "====================================\n";
   nomor = 1;
   cout << setfill(' ') << left << setw(4) << "No." << setw(20) << "NIK" << setw(36) << "Nama" << setw(36) << "Alamat" << endl;
   cout << setfill(' ');
   int nomorIndex = 1;
   for (int i = 0; i < dataCount; i++) {
     if (temp[i].NIK != 0) {
       cout << left << setw(4) << nomorIndex++ << setw(20) << temp[i].NIK << setw(36) << temp[i].nama << setw(36) << temp[i].alamat << endl;
     }
   }
   cout << "====================================\n";
   cout << "Apakah ingin menyimpan hasil sort ke file? (y/n): ";
   char simpan;
   cin >> simpan;
   if (simpan == 'y' || simpan == 'Y') {
      string namaFileHasil;
      cout << "Masukkan nama file hasil: ";
      cin >> namaFileHasil;
      ofstream outFile(namaFileHasil);
      for (int i = 0; i < dataCount; i++) {
         if (temp[i].NIK != 0) {
            outFile << temp[i].NIK << ":" << temp[i].nama << ":" << temp[i].alamat << endl;
         }
      }
      outFile.close();
      cout << "Hasil sort berhasil disimpan ke file: " << namaFileHasil << endl;
      ofstream listFile("daftarFile.txt", ios::app);
      listFile << namaFileHasil << endl;
      listFile.close();
   }
}

void selectsort(){
   ifstream file("daftarFile.txt");
   cout << "Data yang tersedia:\n";
   string fileDipilih, namaFile, tempNIK, tempNama, tempAlamat;
   int dataCount = 0;
   while(getline(file, namaFile)){
      cout << "- " << namaFile << endl;
   }
   file.close();

   cout << "Pilih file: ";
   cin >> fileDipilih;

   ifstream fileData(fileDipilih);
   if(!fileData.is_open()){
      cout << "File tidak ditemukan!" << endl;
      return;
   }
   while(getline(fileData, tempNIK, ':') && getline(fileData, tempNama, ':') && getline(fileData, tempAlamat)){
      dataCount++;
   }

   fileData.clear();
   fileData.seekg(0, ios::beg);
   Warga temp[dataCount];
   int index = 0;
   cout << "\nData sebelum diurutkan\n";
   cout << "====================================\n";
   cout << setfill(' ');
   cout << left << setw(4) << "No." <<
   setw(20) << "NIK" <<
   setw(36) << "Nama" <<
   setw(36) << "Alamat" << endl;
   cout << setfill(' ');
   int nomor = 1;
   while(getline(fileData, tempNIK, ':') && getline(fileData, tempNama, ':') && getline(fileData, tempAlamat)){
      temp[index].NIK = stoll(tempNIK);
      temp[index].nama = tempNama;
      temp[index].alamat = tempAlamat;
      cout << left << setw(4) << nomor++ << setw(20) << tempNIK << setw(36) << tempNama << setw(36) << tempAlamat << endl;
      index++;
   }
   fileData.close();
   //


    for (int i = 0; i < dataCount - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < dataCount; j++) {
            if (temp[j].nama < temp[minIndex].nama) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            Warga swap = temp[i];
            temp[i] = temp[minIndex];
            temp[minIndex] = swap;
        }
    }

   cout << "\nData (Sorted by Nama):\n";
   cout << "====================================\n";
   nomor = 1;
   cout << setfill(' ') << left << setw(4) << "No." << setw(20) << "NIK" << setw(36) << "Nama" << setw(36) << "Alamat" << endl;
   cout << setfill(' ');
   int nomorIndex = 1;
   for (int i = 0; i < dataCount; i++) {
     if (temp[i].NIK != 0) {
       cout << left << setw(4) << nomorIndex++ << setw(20) << temp[i].NIK << setw(36) << temp[i].nama << setw(36) << temp[i].alamat << endl;
     }
   }
   cout << "====================================\n";
   cout << "Apakah ingin menyimpan hasil sort ke file? (y/n): ";
   char simpan;
   cin >> simpan;
   if (simpan == 'y' || simpan == 'Y') {
      string namaFileHasil;
      cout << "Masukkan nama file hasil: ";
      cin >> namaFileHasil;
      ofstream outFile(namaFileHasil);
      for (int i = 0; i < dataCount; i++) {
         if (temp[i].NIK != 0) {
            outFile << temp[i].NIK << ":" << temp[i].nama << ":" << temp[i].alamat << endl;
         }
      }
      outFile.close();
      cout << "Hasil sort berhasil disimpan ke file: " << namaFileHasil << endl;
      ofstream listFile("daftarFile.txt", ios::app);
      listFile << namaFileHasil << endl;
      listFile.close();
   }
}

void insertsort(){
   ifstream file("daftarFile.txt");
   cout << "Data yang tersedia:\n";
   string fileDipilih, namaFile, tempNIK, tempNama, tempAlamat;
   int dataCount = 0;
   while(getline(file, namaFile)){
      cout << "- " << namaFile << endl;
   }
   file.close();
   cout << "Pilih file: ";
   cin >> fileDipilih;
   ifstream fileData(fileDipilih);
   if(!fileData.is_open()){
      cout << "File tidak ditemukan!" << endl;
      return;
   }
   while(getline(fileData, tempNIK, ':') && getline(fileData, tempNama, ':') && getline(fileData, tempAlamat)){
      dataCount++;
   }
   fileData.clear();
   fileData.seekg(0, ios::beg);
   
   Warga temp[dataCount];
   int index = 0;

   cout << "\nData sebelum diurutkan\n";
   cout << "====================================\n";
   cout << setfill(' ');
   cout << left << setw(4) << "No." <<
   setw(20) << "NIK" <<
   setw(36) << "Nama" <<
   setw(36) << "Alamat" << endl;
   cout << setfill(' ');
   int nomor = 1;
   while(getline(fileData, tempNIK, ':') && getline(fileData, tempNama, ':') && getline(fileData, tempAlamat)){
      temp[index].NIK = stoll(tempNIK);
      temp[index].nama = tempNama;
      temp[index].alamat = tempAlamat;
      cout << left << setw(4) << nomor++ << setw(20) << tempNIK << setw(36) << tempNama << setw(36) << tempAlamat << endl;
      index++;
   }
   fileData.close();

    for (int i = 1; i < dataCount; i++) {
        Warga key = temp[i];
        int j = i - 1;

        while (j >= 0 && temp[j].alamat > key.alamat) {
            temp[j + 1] = temp[j];
            j--;
        }
        temp[j + 1] = key;
    }

    cout << "\nData urut by Alamat dengan INSERTION SORT\n";
    cout << "====================================\n";
    nomor = 1;
    cout << setfill(' ') << left << setw(4) << "No." << setw(20) << "NIK" << setw(36) << "Nama" << setw(36) << "Alamat" << endl;
    for (int i = 0; i < dataCount; i++) {
      if (temp[i].NIK != 0) {
        cout << left << setw(4) << nomor++ << setw(20) << temp[i].NIK << setw(36) << temp[i].nama << setw(36) << temp[i].alamat << endl;
      }
    }

   cout << "====================================\n";
   cout << "Apakah ingin menyimpan hasil sort ke file? (y/n): ";
   char simpan;
   cin >> simpan;

   if (simpan == 'y' || simpan == 'Y') {
      string namaFileHasil;
      cout << "Masukkan nama file hasil: ";
      cin >> namaFileHasil;

      ofstream outFile(namaFileHasil);

      for (int i = 0; i < dataCount; i++) {
         if (temp[i].NIK != 0) {
            outFile << temp[i].NIK << ":"
                    << temp[i].nama << ":"
                    << temp[i].alamat << endl;
         }
      }

      outFile.close();
      cout << "Hasil sort berhasil disimpan ke file: " << namaFileHasil << endl;
      ofstream listFile("daftarFile.txt", ios::app);
      listFile << namaFileHasil << endl;
      listFile.close();
   }
} 

void shellsort(){
   ifstream file("daftarFile.txt");
   cout << "Data yang tersedia:\n";
   string fileDipilih, namaFile, tempNIK, tempNama, tempAlamat;
   int dataCount = 0;
   while(getline(file, namaFile)){
      cout << "- " << namaFile << endl;
   }
   file.close();
   cout << "Pilih file: ";
   cin >> fileDipilih;
   ifstream fileData(fileDipilih);
   if(!fileData.is_open()){
      cout << "File tidak ditemukan!" << endl;
      return;
   }
   while(getline(fileData, tempNIK, ':') && getline(fileData, tempNama, ':') && getline(fileData, tempAlamat)){
      dataCount++;
   }
   fileData.clear();
   fileData.seekg(0, ios::beg);

   Warga temp[dataCount];
   int index = 0;

   cout << "\nData sebelum diurutkan\n";
   cout << "====================================\n";
   cout << setfill(' ');
   cout << left << setw(4) << "No." <<
   setw(20) << "NIK" <<
   setw(36) << "Nama" <<
   setw(36) << "Alamat" << endl;
   cout << setfill(' ');
   int nomor = 1;
   while(getline(fileData, tempNIK, ':') && getline(fileData, tempNama, ':') && getline(fileData, tempAlamat)){
      temp[index].NIK = stoll(tempNIK);
      temp[index].nama = tempNama;
      temp[index].alamat = tempAlamat;
      cout << left << setw(4) << nomor++ << setw(20) << tempNIK << setw(36) << tempNama << setw(36) << tempAlamat << endl;
      index++;
   }
   fileData.close();

    for (int gap = dataCount / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < dataCount; i++) {
            Warga key = temp[i];
            int j = i;

            while (j >= gap && temp[j - gap].NIK > key.NIK) {
                temp[j] = temp[j - gap];
                j -= gap;
            }
            temp[j] = key;
        }
    }

    cout << "\nData urut by NIK dengan SHELL SORT\n";
    cout << "====================================\n";
    nomor = 1;
    cout << setfill(' ') << left << setw(4) << "No." << setw(20) << "NIK" << setw(36) << "Nama" << setw(36) << "Alamat" << endl;
    for (int i = 0; i < dataCount; i++) {
      if (temp[i].NIK != 0) {
        cout << left << setw(4) << nomor++ << setw(20) << temp[i].NIK << setw(36) << temp[i].nama << setw(36) << temp[i].alamat << endl;
      }
    }

   cout << "====================================\n";
   cout << "Apakah ingin menyimpan hasil sort ke file? (y/n): ";
   char simpan;
   cin >> simpan;

   if (simpan == 'y' || simpan == 'Y') {
      string namaFileHasil;
      cout << "Masukkan nama file hasil: ";
      cin >> namaFileHasil;

      ofstream outFile(namaFileHasil);

      for (int i = 0; i < dataCount; i++) {
         if (temp[i].NIK != 0) {
            outFile << temp[i].NIK << ":"
                    << temp[i].nama << ":"
                    << temp[i].alamat << endl;
         }
      }

      outFile.close();
      cout << "Hasil sort berhasil disimpan ke file: " << namaFileHasil << endl;
      ofstream listFile("daftarFile.txt", ios::app);
      listFile << namaFileHasil << endl;
      listFile.close();
   }
}

void quicksort(){
   ifstream file("daftarFile.txt");
   cout << "Data yang tersedia:\n";
   string fileDipilih, namaFile, tempNIK, tempNama, tempAlamat;
   int dataCount = 0;
   while(getline(file, namaFile)){
      cout << "- " << namaFile << endl;
   }
   file.close();
   cout << "Pilih file: ";
   cin >> fileDipilih;
   ifstream fileData(fileDipilih);
   if(!fileData.is_open()){
      cout << "File tidak ditemukan!" << endl;
      return;
   }
   while(getline(fileData, tempNIK, ':') && getline(fileData, tempNama, ':') && getline(fileData, tempAlamat)){
      dataCount++;
   }
   fileData.clear();
   fileData.seekg(0, ios::beg);

   Warga temp[dataCount];
   int index = 0;

   cout << "\nData sebelum diurutkan\n";
   cout << "====================================\n";
   cout << setfill(' ');
   cout << left << setw(4) << "No." <<
   setw(20) << "NIK" <<
   setw(36) << "Nama" <<
   setw(36) << "Alamat" << endl;
   cout << setfill(' ');
   int nomor = 1;
   while(getline(fileData, tempNIK, ':') && getline(fileData, tempNama, ':') && getline(fileData, tempAlamat)){
      temp[index].NIK = stoll(tempNIK);
      temp[index].nama = tempNama;
      temp[index].alamat = tempAlamat;
      cout << left << setw(4) << nomor++ << setw(20) << tempNIK << setw(36) << tempNama << setw(36) << tempAlamat << endl;
      index++;
   }
   fileData.close();

   int stackLow[10], stackHigh[10];
   int top = -1;

   stackLow[++top] = 0;
   stackHigh[top] = dataCount - 1;

   while (top >= 0) {
      int low = stackLow[top];
      int high = stackHigh[top--];

      int i = low - 1;
      Warga pivot = temp[high];

      for (int j = low; j < high; j++) {
         if (temp[j].nama < pivot.nama) {
            i++;
            swap(temp[i], temp[j]);
         }
      }

      swap(temp[i + 1], temp[high]);
      int pi = i + 1;

      if (pi - 1 >= low) {
         stackLow[++top] = low;
         stackHigh[top] = pi - 1;
      }

      if (pi + 1 <= high) {
         stackLow[++top] = pi + 1;
         stackHigh[top] = high;
      }
   }

    cout << "\nData urut by Nama dengan QUICK SORT\n";
    cout << "====================================\n";
    nomor = 1;
    cout << setfill(' ') << left << setw(4) << "No." << setw(20) << "NIK" << setw(36) << "Nama" << setw(36) << "Alamat" << endl;
    for (int i = 0; i < dataCount; i++) {
      if (temp[i].NIK != 0) {
         cout << left << setw(4) << nomor++ << setw(20) << temp[i].NIK << setw(36) << temp[i].nama << setw(36) << temp[i].alamat << endl;
      }
    }

   cout << "====================================\n";
   cout << "Apakah ingin menyimpan hasil sort ke file? (y/n): ";
   char simpan;
   cin >> simpan;

   if (simpan == 'y' || simpan == 'Y') {
      string namaFileHasil;
      cout << "Masukkan nama file hasil: ";
      cin >> namaFileHasil;

      ofstream outFile(namaFileHasil);

      for (int i = 0; i < dataCount; i++) {
         if (temp[i].NIK != 0) {
            outFile << temp[i].NIK << ":"
                    << temp[i].nama << ":"
                    << temp[i].alamat << endl;
         }
      }

      outFile.close();
      cout << "Hasil sort berhasil disimpan ke file: " << namaFileHasil << endl;
      ofstream listFile("daftarFile.txt", ios::app);
      listFile << namaFileHasil << endl;
      listFile.close();
   }
}

void mergesort(){
   ifstream file("daftarFile.txt");
   cout << "Data yang tersedia:\n";
   string fileDipilih, namaFile, tempNIK, tempNama, tempAlamat;
   int dataCount = 0;
   while(getline(file, namaFile)){
      cout << "- " << namaFile << endl;
   }
   file.close();
   cout << "Pilih file: ";
   cin >> fileDipilih;
   ifstream fileData(fileDipilih);
   if(!fileData.is_open()){
      cout << "File tidak ditemukan!" << endl;
      return;
   }
   while(getline(fileData, tempNIK, ':') && getline(fileData, tempNama, ':') && getline(fileData, tempAlamat)){
      dataCount++;
   }
   fileData.clear();
   fileData.seekg(0, ios::beg);

   Warga temp[dataCount];
   int index = 0;

   cout << "\nData sebelum diurutkan\n";
   cout << "====================================\n";
   cout << setfill(' ');
   cout << left << setw(4) << "No." <<
   setw(20) << "NIK" <<
   setw(36) << "Nama" <<
   setw(36) << "Alamat" << endl;
   cout << setfill(' ');
   int nomor = 1;
   while(getline(fileData, tempNIK, ':') && getline(fileData, tempNama, ':') && getline(fileData, tempAlamat)){
      temp[index].NIK = stoll(tempNIK);
      temp[index].nama = tempNama;
      temp[index].alamat = tempAlamat;
      cout << left << setw(4) << nomor++ << setw(20) << tempNIK << setw(36) << tempNama << setw(36) << tempAlamat << endl;
      index++;
   }
   fileData.close();

   int currSize;
   int leftStart;

   for (currSize = 1; currSize <= dataCount - 1; currSize *= 2) {
      for (leftStart = 0; leftStart < dataCount - 1; leftStart += 2 * currSize) {
         int mid = min(leftStart + currSize - 1, dataCount - 1);
         int rightEnd = min(leftStart + 2 * currSize - 1, dataCount - 1);

         Warga merged[dataCount];
         int i = leftStart, j = mid + 1, k = leftStart;

         while (i <= mid && j <= rightEnd) {
            if (temp[i].alamat <= temp[j].alamat) {
               merged[k++] = temp[i++];
            } else {
               merged[k++] = temp[j++];
            }
         }

         while (i <= mid) {
            merged[k++] = temp[i++];
         }

         while (j <= rightEnd) {
            merged[k++] = temp[j++];
         }

         for (i = leftStart; i <= rightEnd; i++) {
            temp[i] = merged[i];
         }
      }
   }

   cout << "\nData urut by Alamat dengan MERGE SORT\n";
   cout << "====================================\n";
   nomor = 1;
   cout << setfill(' ') << left << setw(4) << "No." << setw(20) << "NIK" << setw(36) << "Nama" << setw(36) << "Alamat" << endl;
   for (int i = 0; i < dataCount; i++) {
      if (temp[i].NIK != 0) {
         cout << left << setw(4) << nomor++ << setw(20) << temp[i].NIK << setw(36) << temp[i].nama << setw(36) << temp[i].alamat << endl;
      }
   }

   cout << "====================================\n";
   cout << "Apakah ingin menyimpan hasil sort ke file? (y/n): ";
   char simpan;
   cin >> simpan;

   if (simpan == 'y' || simpan == 'Y') {
      string namaFileHasil;
      cout << "Masukkan nama file hasil: ";
      cin >> namaFileHasil;

      ofstream outFile(namaFileHasil);

      for (int i = 0; i < dataCount; i++) {
         if (temp[i].NIK != 0) {
            outFile << temp[i].NIK << ":"
                    << temp[i].nama << ":"
                    << temp[i].alamat << endl;
         }
      }

      outFile.close();
      cout << "Hasil sort berhasil disimpan ke file: " << namaFileHasil << endl;
      ofstream listFile("daftarFile.txt", ios::app);
      listFile << namaFileHasil << endl;
      listFile.close();
   }
}

int main() {
   int pilih;
   char ulangi;

   do{
      system("cls");
      cout << "Kelompok 1: 123250068, 123250070, 123250076" << endl;
      cout << "== Pencatatan Data Warga ==" << endl;
      cout << "MENU: " << endl;
      cout << "1. Input Data" << endl
      << "2. Tampil Data" << endl
      << "3. Search" << endl
      << "4. Sort" << endl
      << "5. Operasi File" << endl
      << "6. Exit" << endl;
      cout << "Pilih menu: ";
      cin >> pilih;
      switch(pilih){
      case 1:
         input();
      break;
      case 2:
         system("cls");
         cout << "================================== Data warga ==================================" << endl;
         tampil();
      break;
      case 3:
         search();
      break;
      case 4:
         sort();
      break;
      case 5:
         OperasiFile();
      break;
      case 6:
         exit(0);
      break;  
      default:
         cout << "Menu yang anda pilih tidak tersedia!" << endl
         << "=============================="<< endl;
      break;
      }
      if(pilih != 6){
         cout << "Kembali ke menu utama? (y/n):";
         cin >> ulangi;
      }
   }while(ulangi == 'y' || ulangi == 'Y');
}
