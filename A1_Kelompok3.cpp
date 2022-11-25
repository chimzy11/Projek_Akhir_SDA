#include <iostream>
#include <Windows.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <fstream> // library file
#include <sstream> // library konversi string
#include <limits>  // error handling
#include <iomanip>
#include <map>

using namespace std;

map<string, string> UserTerkini;

struct kereta_api
{
	string jenis, keberangkatan_awal, tujuan;
	int harga, lama_perjalanan;
	float jam;
};

struct pesanan
{
    string jenis, nama, keberangkatan_awal, tujuan;
    int jumlah_tiket, total_harga;
    float jam;
};

struct User
{
	string nama, tipe_identitas, nomor_identitas, jenis_kelamin, no_telp, username, password;
	int usia;
};

struct NodeJadwal
{
	kereta_api data;
	NodeJadwal *next;
	NodeJadwal *prev;
};

struct Node_Pesanan
{
    pesanan pesan;
    Node_Pesanan *next;
    Node_Pesanan *prev;
};

struct Node_dataUser
{
	User data_user;
	Node_dataUser *next;
	Node_dataUser *prev;
};

char ch;
int panjangJadwal, cek;
int panjang_dataUser;
int jumlah_tiket;

NodeJadwal *head_jadwal = NULL, *tail_jadwal = NULL;
Node_Pesanan *front = NULL, *rear = NULL;
// Node_dataUser user1;
Node_dataUser *head_user = NULL, *tail_user = NULL;

Node_dataUser *registrasi();
void menuAdmin();
void menuUser();
void menu_login();
void tampil_jadwal();
void FrontBackSplit(NodeJadwal *source, NodeJadwal **frontRef, NodeJadwal **backRef);
NodeJadwal *SortedMergeKeberangkatan(NodeJadwal *a, NodeJadwal *b);
int fibonacciSearchKeberangkatan(NodeJadwal *node, string x, int n);
void MergeSortKeberangkatan(NodeJadwal **headRef);
void pindahAkun_user(Node_dataUser **head_user);
void tagline();
void setcolor(unsigned short color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color);
}

// bool eror_handling(int eror)
// {
// 	if (cin.fail())
// 	{
// 		cin.clear();
// 		setcolor(4);
// 		cout << "\n>>>> DATA YANG DIMASUKKAN SALAH <<<<" << endl
// 			 << "---- Masukkan Angka Bukan Huruf ----" << endl;
// 		setcolor(7);
// 		cin.ignore(numeric_limits<streamsize>::max(), '\n');
// 		return true;
// 	}
// 	else
// 	{
// 		return false;
// 	}
// 	return eror;
// }
void inputan(string text){
  cout << setw(21) << left << text << ": ";
}

void errorHandling(int &cek){
    while(true){
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
			setcolor(4);
			cout << "\nERROR: Masukkan Angka Bukan Huruf!\n" << endl;
			setcolor(7);
			cout << "" ; inputan("Masukkan Pilihan "); cin >> cek;
        }
        else
		{
            break;
        }
    }
}

bool eror_handling(int eror)
{
	if (cin.fail())
	{
		cin.clear();
		setcolor(4);
		cout << "\n>>>> DATA YANG DIMASUKKAN SALAH <<<<" << endl
			 << "---- Masukkan Angka Bukan Huruf ----" << endl;
		setcolor(7);
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return true;
	}
	else
	{
		return false;
	}
	return eror;
}

void tagline()
{
	// tanggal / waktu sekarang berdasarkan sistem saat ini
	time_t now = time(0);
	// ubah sekarang menjadi bentuk string
	char *dt = ctime(&now);
	cout << "________________________________________________________________________________________________________________________________________" << endl;
	setcolor(3);
	cout << "                                              .  .   '   ...    .   .. .   ....  .   .                                     " << endl;
	cout << "                                              :.:        :  .   :   : ::   ...:    :                                       " << endl;
	cout << "                                              :  :       :..    :   : .:   :...    :                                       " << endl;
	cout << endl;
	setcolor(3);
	cout << "                                 J A D W A L  &  P E M E S A N A N  T I K E T  K E R E T A  A P I                         " << endl;
	setcolor(8);
	cout << "                                                    " << dt << "                                                   " << endl;
	setcolor(7);
	cout << "________________________________________________________________________________________________________________________________________" << endl;
}

void kalender()
{
	time_t a = time(0);
	tm *b = localtime(&a);

	int c = b->tm_mday;
	int d = b->tm_mon;
	++d;
	int e = b->tm_year;
	e = e + 1900;
	if (d == 1)
	{
		cout << c << " "
			 << "January"
			 << " " << e << endl;
	}
	else if (d == 2)
	{
		cout << c << " "
			 << "February"
			 << " " << e << endl;
	}
	else if (d == 3)
	{
		cout << c << " "
			 << "March"
			 << " " << e << endl;
	}
	else if (d == 4)
	{
		cout << c << " "
			 << "April"
			 << " " << e << endl;
	}
	else if (d == 5)
	{
		cout << c << " "
			 << "May"
			 << " " << e << endl;
	}
	else if (d == 6)
	{
		cout << c << " "
			 << "June"
			 << " " << e << endl;
	}
	else if (d == 7)
	{
		cout << c << " "
			 << "July"
			 << " " << e << endl;
	}
	else if (d == 8)
	{
		cout << c << " "
			 << "August"
			 << " " << e << endl;
	}
	else if (d == 9)
	{
		cout << c << " "
			 << "September"
			 << " " << e << endl;
	}
	else if (d == 10)
	{
		cout << c << " "
			 << "October"
			 << " " << e << endl;
	}
	else if (d == 11)
	{
		cout << c << " "
			 << "November"
			 << " " << e << endl;
	}
	else if (d == 12)
	{
		cout << c << " "
			 << "December"
			 << " " << e << endl;
	}
}

int jumlah_user(){
	int jumlah = 0;
	Node_dataUser *head = head_user;
	while(head != NULL){
		jumlah++;
		head = head->next;
	}
	return jumlah;
}

int jumlah_jadwal(){
	int jumlah = 0;
	NodeJadwal *head = head_jadwal;
	while(head != NULL){
		jumlah++;
		head = head->next;
	}
	return jumlah;
}

int jumlahtiket(string kereta){
	int jumlah = 0;
	Node_Pesanan *front_pesan = front;
	Node_Pesanan *sekali = front_pesan;
	while(sekali != NULL){
		if (sekali->pesan.jenis == kereta) {
			jumlah = jumlah + sekali->pesan.jumlah_tiket;
		}
		sekali = sekali->next;
	}
	return jumlah;
}

// ----------------------------USER--------------------------------------------
void data_diri(){
	system("cls");
	tagline();
	Node_dataUser *head = head_user;
	Node_dataUser *sekali = head;
	string namaUser = UserTerkini["Active"];
	setcolor(6);
	cout << "\n                                                     DATA DIRI ANDA";
	cout << endl;
	setcolor(7);
	cout << "\n----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	printf("%-25s%-25s%-25s%-25s%-20s%5s\n", "Nama Lengkap", "Tipe Identitas", "Nomor Identitas", "Jenis Kelamin", "Usia", "Nomor Telepon");
	cout << "----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	setcolor(9);
	while(sekali != NULL){
		if (sekali->data_user.nama == namaUser) {
			cout << setiosflags(ios::left) << setw(25) << sekali->data_user.nama;
			cout << setiosflags(ios::left) << setw(25) << sekali->data_user.tipe_identitas;
			cout << setiosflags(ios::left) << setw(25) << sekali->data_user.nomor_identitas;
			cout << setiosflags(ios::left) << setw(25) << sekali->data_user.jenis_kelamin;
			std::cout << std::fixed;
			std::cout << setiosflags(ios::left) << setw(5) << std::setprecision(2) << sekali->data_user.usia << setiosflags(ios::left) << setw(15) << " Tahun";
			cout << setiosflags(ios::left) << setw(0) << "+62" << sekali->data_user.no_telp << endl;
		}
		sekali = sekali->next;
	}
	setcolor(7);
		setcolor(8);
		cout << endl; cout << endl; system("pause");
		setcolor(7);
}

void datauser(){ // Tambahin Nomor sebelum nama lengkap biar tau ada berapa user
	system("cls");
	tagline();
	Node_dataUser *sekali = head_user;
	setcolor(6);
	cout << "\n                                                      DATA DIRI USER";
	cout << endl;
	setcolor(7);
	cout << "\n----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	printf( "%-25s%-25s%-25s%-25s%-20s%5s\n", "Nama Lengkap", "Tipe Identitas", "Nomor Identitas", "Jenis Kelamin", "Usia", "Nomor Telepon");
	cout << "----------------------------------------------------------------------------------------------------------------------------------------" << endl;
	setcolor(9);
	while (sekali != NULL) {
		cout << setiosflags(ios::left) << setw(25) << sekali->data_user.nama;
		cout << setiosflags(ios::left) << setw(25) << sekali->data_user.tipe_identitas;
		cout << setiosflags(ios::left) << setw(25) << sekali->data_user.nomor_identitas;
		cout << setiosflags(ios::left) << setw(25) << sekali->data_user.jenis_kelamin;
		std::cout << std::fixed;
		std::cout << setiosflags(ios::left) << setw(5) << std::setprecision(2) << sekali->data_user.usia << setiosflags(ios::left) << setw(15) << " Tahun";
		cout << setiosflags(ios::left) << setw(0) << "+62" << sekali->data_user.no_telp << endl;
		sekali = sekali->next;
	}
	setcolor(7);
			setcolor(8);
		cout << endl; cout << endl; system("pause");
		setcolor(7);
}

void update_data_user(Node_dataUser **head_user){
	system("cls");
	tagline();
	datauser();
	int pilihan;
	Node_dataUser *temp = *head_user;
	int pilih_jk, pilih_tipeIdn;
	bool loop_nama = false;
	bool loop_uname = false;
	bool loop_nomor = false;
	bool loop_usia = false;
	bool loop_notelp = false;
	bool loop_pass = false;
	update:
	if (temp != NULL){
		cout << "" ; inputan("\nMasukkan Pilihan "); cin >> cek;
		pilihan = cek;
		cout << "  "; 
		if (pilihan <= jumlah_user() && pilihan > 0){
			for (int i = 1; i < pilihan; i++){
				temp = temp->next;
			}
			system("cls");
			tagline();
			cout<< "\n                    UPDATE - DATA - USER" << endl
	        	<< "                    -----------------------------" << endl;

			while (loop_nama == false){
				cout << "" ; inputan("Nama Lengkap "); fflush(stdin); getline(cin, temp->data_user.nama);
				if (temp->data_user.nama.length() > 1)
				{
					loop_nama = true;
				}
				else
				{
					setcolor(4);
					cout << "\nERROR: Nama Lengkap Wajib Diisi\n" << endl;
					setcolor(7);
					loop_nama = false;
				}
		   }	

			tipIdn :
			cout << "\nPilih Tipe Identitas: " << endl
				<< "1. Passport " << endl
				<< "2. KTP" << endl;
			cout << "" ; inputan("Masukkan Pilihan "); cin >> pilih_tipeIdn;
			errorHandling(pilih_tipeIdn);	
			if (pilih_tipeIdn == 1)
			{
				temp->data_user.tipe_identitas = "Passport";
				while (loop_nomor == false)
				{
					cout << "" ; inputan("Nomor Passport "); fflush(stdin); getline(cin, temp->data_user.nomor_identitas);
					if (temp->data_user.nomor_identitas.length() == 7)
					{
						loop_nomor = true;
					}
					else
					{
						setcolor(4);
						cout << "\nERROR: Passport harus terdiri dari 7 digit\n"
							<< endl;
						setcolor(7);
						loop_nomor = false;
					}
				}
			} else if (pilih_tipeIdn == 2) {
				temp->data_user.tipe_identitas = "KTP";
				while (loop_nomor == false)
				{
					cout << "" ; inputan("Nomor KTP "); fflush(stdin); getline(cin, temp->data_user.nomor_identitas);
					if (temp->data_user.nomor_identitas.length() == 16)
					{
						loop_nomor = true;
					}
					else
					{
						setcolor(4);
						cout << "\nERROR: KTP harus terdiri dari 16 digit\n"
							<< endl;
						setcolor(7);
						loop_nomor = false;
					}
				}
			} else {
				setcolor(4);
				cout << "ERROR: Pilihan Tersebut Tidak Ada!" << endl;
				setcolor(7);
				goto tipIdn;
			}

			jk :
			cout << "\nPilih Jenis Kelamin: " << endl
				<< "1. Perempuan " << endl
				<< "2. Laki-Laki" << endl;
			cout << "" ; inputan("Masukkan Pilihan "); cin >> pilih_jk;
			errorHandling(pilih_jk);	
			if (pilih_jk == 1)
			{
				temp->data_user.jenis_kelamin= "Perempuan";
			}
			else if (pilih_jk == 2)
			{
				temp->data_user.jenis_kelamin = "Laki-Laki";
			} else {
				setcolor(4);
				cout << "ERROR: Pilihan Tersebut Tidak Ada!" << endl;
				setcolor(7);
				goto jk;
			}

			while (loop_usia == false){
				cout << "" ; inputan("Usia "); cin >> temp->data_user.usia;
				if (temp->data_user.usia >= 17 and temp->data_user.usia <= 70)
				{
					loop_usia = true;
				}
				else
				{
					setcolor(4);
					cout << "\nERROR: Usia Maksimal 17 - 70 Tahun\n"
						<< endl;
					setcolor(7);
					loop_usia = false;
				}
			}	

			while (loop_notelp == false){
				cout << "Nomor Handphone     : +62 "; cin >> temp->data_user.no_telp;
				if (temp->data_user.no_telp.length() >= 10 or temp->data_user.no_telp.length() >= 11 or temp->data_user.no_telp.length() >= 12)
				{
					loop_notelp = true;
				}
				else
				{
					setcolor(4);
					cout << "\nERROR: Nomor telpon Maksimal 11 - 13 Digit\n" << endl;
					setcolor(7);
					loop_notelp = false;
				}
			}	
			setcolor(2);
			cout << "\nSUCCES: Data User Berhasil Diupdate" << endl;
			setcolor(7);

		} else {
			setcolor(4);
			cout << "ERROR: Pilihan Tersebut Tidak Ada!" << endl;
			setcolor(7);
			goto update;
		}
	}
}

Node_Pesanan *newPemesanan(){
	system("cls");
	tagline();
	Node_Pesanan *newPesanan = new Node_Pesanan;
	NodeJadwal *head = head_jadwal;
	int jumlah_tiket = 0;
	int pilihan;
	int jumlahjadwal = jumlah_jadwal();
	pilih: 
	tampil_jadwal();
	if (jumlahjadwal == 0) {
		setcolor(4);
		printf("%-50s%-35s%5s\n", "", "---Jadwal Kereta Api Kosong---", "");
		setcolor(7);

		setcolor(8);
		cout << endl; cout << endl; system("pause");
		setcolor(7);
		menuUser();
	} else {
		inputan("\nMasukkan Pilihan "); cin >> cek;
		pilihan = cek;
		errorHandling(pilihan);
		if (pilihan <= 0 || pilihan > jumlahjadwal){
			setcolor(4);
			cout << "\nERROR: Tiket Yang Dipilih Tidak Ada!" << endl;
			setcolor(7);
			goto pilih;
		} else {
			jumlah:
			inputan("Jumlah Tiket  "); cin >> jumlah_tiket;
			if (jumlah_tiket <= 0){
				cout << "\nMinimal Pembelian 1 Tiket" << endl;
				goto jumlah;
			} else {
				newPesanan->pesan.nama = UserTerkini["Active"];
				newPesanan->pesan.jumlah_tiket = jumlah_tiket;
				for (int i = 1; i < pilihan; i++){
					head = head->next;
				}
				newPesanan->pesan.keberangkatan_awal = head->data.keberangkatan_awal;
				newPesanan->pesan.total_harga = jumlah_tiket * head->data.harga;
				newPesanan->pesan.tujuan = head->data.tujuan;
				newPesanan->pesan.jenis = head->data.jenis;
				newPesanan->pesan.jam = head->data.jam;
				return newPesanan;
			}
		}
	}
}

void pemesanan(Node_Pesanan **front, Node_Pesanan **rear){
	system("cls");
	tagline();
	Node_Pesanan *pemesanan = newPemesanan();
	if(jumlah_tiket >= 100){
		setcolor(2);
		cout << "\nSOLD OUT: Tiket Kereta Api terjual Habis" << endl;
		setcolor(7);
	}else{
	    if (*front == NULL) {
	        *front = pemesanan;
	    } else {
	        (*rear)->next = pemesanan;
	    }
	    *rear = pemesanan;
	}
	setcolor(2);
	cout << "\nSUCCES: Tiket Kereta Api Berhasil Dipesan" << endl;
	setcolor(7);
	setcolor(8);
	cout << endl; cout << endl; system("pause");
	setcolor(7);
}

void tiket_masuk(Node_Pesanan **front){
	system("cls");
	tagline();
    if (*front == NULL) {
		setcolor(4);
		cout << "\nERROR: Tiket Ada Pemesan" << endl;
		setcolor(7);
		setcolor(8);
		cout << endl; cout << endl; system("pause");
		setcolor(7);
        return;
    }
    Node_Pesanan *temp = *front;
    *front = (*front)->next;
    cout<<"\nPemesan Tiket Telah Masuk Ke Kereta\n";
	setcolor(2);
	cout << "\nSUCCES CHECK IN: Penumpang Telah Masuk" << endl;
	setcolor(7);
    delete temp;
	setcolor(8);
	cout << endl; cout << endl; system("pause");
	setcolor(7);
}

void riwayat_pemesanan(){
	system("cls");
	tagline();
	Node_Pesanan *front_pesan = front;
	Node_Pesanan *sekali = front_pesan;
	string namaUser = UserTerkini["Active"];

	setcolor(6);
	cout << "\n                                                     R I W A Y A T  -  P E M E S A N A N";
	cout << endl;
	setcolor(7);
	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
	setcolor(1);
	printf("%-7s%-20s%-20s%-20s%-20s%-15s%-20s%5s\n", "No", "Nama Pemesan", "Jenis Kereta", "Jam Berangkat/WITA", "Keberangkatan Awal", "Tujuan Akhir", "Jumlah Tiket", "Total Harga");
	setcolor(8);
	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
	setcolor(7);
	int nomor = 1;
	while(sekali != NULL){
		if (sekali->pesan.nama == namaUser) {

			cout << setiosflags(ios::left) << setw(7) << nomor;
			cout << setiosflags(ios::left) << setw(20) << sekali->pesan.nama;
			cout << setiosflags(ios::left) << setw(20) << sekali->pesan.jenis;
			std::cout << std::fixed;
			std::cout << setiosflags(ios::left) << setw(20) << std::setprecision(2) << sekali->pesan.jam;
			cout << setiosflags(ios::left) << setw(20) << sekali->pesan.keberangkatan_awal;
			cout << setiosflags(ios::left) << setw(15) << sekali->pesan.tujuan;
			cout << setiosflags(ios::left) << setw(20) << sekali->pesan.jumlah_tiket;
			cout << setiosflags(ios::left) << setw(0) << "Rp. " << sekali->pesan.total_harga; cout << setiosflags(ios::left) << setw(5) << endl;
		}
		sekali = sekali->next;
		nomor++;
	}
	setcolor(8);
	cout << endl; cout << endl; system("pause");
	setcolor(7);
}

void informasi(){
	system("cls");
	tagline();
	setcolor(3);
	cout << "\n\n-------------------------------------I N F O R M A S I - K E R E T A - A P I - K ' D I N Z Y-----------------------------------------\n\n" << endl;
	cout << "1. Penumpang Wajib Menunjukkan data sudah vaksin melalui aplikasi PeduliLindungi/Kartu Vaksin" << endl	
		 << "2. Penumpang telah tervaksinasi 3 dosis (booster) " << endl
		 << "3. Penumpang yang tervaksinasi 1 / 2 dosis, tidak boleh melakukan perjalanan domestik" << endl
		 << "4. Anak-anak diperbolehkan naik kereta api tanpa syarat vaksinasi" << endl
		 << "5. WNA berusia 17 Tahun keatas" << endl
		 << "6. Penumpang harus dalam keadaan sehat tidak menderita dlu, batuk" << endl
		 << "7. penumpang wajib menggunakan maskerr" << endl
		 << "8. Penumpang wajib menjaga jarak dan menjaga kebersihan tangan\n" << endl << endl;
	setcolor(7);
	system("pause");

}

void menuUser(){
	system("cls");
	tagline();
	NodeJadwal *head = head_jadwal;
	NodeJadwal *sekali = head;
	string data_cari;
	int panjang_jadwal = jumlah_jadwal();
	int pilihan;
	cout << "\n---------------------------------------" << endl
		<< "|               MENU USER            |" << endl
		<< "---------------------------------------" << endl
		<< "1. Lihat Data Diri" << endl
		<< "2. Riwayat Pemesanan" << endl
		<< "3. Pesan Tiket" << endl
		<< "4. Cari Jadwal" << endl
		<< "5. Informasi Kereta Api "<< endl
		<< "0. Logout" << endl
		<< "---------------------------------------" << endl;
	cout << "" ; inputan("Masukkan Pilihan "); cin >> cek;
	pilihan = cek;
	errorHandling(pilihan);
	if (pilihan == 1){
		data_diri();
		pindahAkun_user(&head_user);
		menuUser();
	} else if (pilihan == 2){
		riwayat_pemesanan();
		pindahAkun_user(&head_user);
		menuUser();
	} else if (pilihan == 3){
		pemesanan(&front, &rear);
		menuUser();
	} else if (pilihan == 4){
		system("cls");
		tagline();
		MergeSortKeberangkatan(&head_jadwal);

		cout << "\nMasukkan Keberangkatan Awal : "; fflush(stdin); getline(cin, data_cari);
		int indeks = fibonacciSearchKeberangkatan(head_jadwal, data_cari, panjang_jadwal);
		if (indeks >= 0) {
			setcolor(6);
			printf("%-53s%-38s%5s\n", "", "DAFTAR JADWAL KERETA API", "");
			cout << "                                                         ";
			kalender();
			cout << endl;
			setcolor(8);
			cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
			setcolor(1);
			printf("%-7s%-20s%-25s%-25s%-25s%-20s%5s\n", "No", "Jenis Kereta", "Keberangkatan Awal", "Tujuan Akhir", "Jam Berangkat/WITA", "Lama Perjalanan", "Harga Tiket");
			setcolor(8);
			cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
			setcolor(7);
			for (int i = 0; i < indeks; i++){
				sekali = sekali->next;
			}
			setcolor(1);
			cout << setiosflags(ios::left) << setw(7) << indeks+1;
			cout << setiosflags(ios::left) << setw(20) << sekali->data.jenis;
			cout << setiosflags(ios::left) << setw(25) << sekali->data.keberangkatan_awal;
			cout << setiosflags(ios::left) << setw(25) << sekali->data.tujuan;
			std::cout << std::fixed;
			std::cout << setiosflags(ios::left) << setw(25) << std::setprecision(2) << sekali->data.jam;
			std::cout << std::fixed;
			std::cout << setiosflags(ios::left) << setw(5) << std::setprecision(2) << sekali->data.lama_perjalanan << setiosflags(ios::left) << setw(15) << " Menit";
			cout << setiosflags(ios::left) << setw(0) << "Rp. " << sekali->data.harga; cout << setiosflags(ios::left) << setw(5) << endl;
			setcolor(7);
		}  else {
			cout << "Kota " << data_cari << " tidak ditemukan pada jadwal!" << endl;
		}
		setcolor(8);
		cout << endl; cout << endl; system("pause");
		setcolor(7);
		menuUser();
	} else if (pilihan == 5){
		informasi();
		menuUser();
	} else if (pilihan == 0){
		cout << "\nAnda Telah Logout" << endl;
		menu_login();
	} else {
		setcolor(4);
		cout << "ERROR: Pilihan Tersebut Tidak Ada!" << endl;
		setcolor(7);
		menuUser();
	}
}

Node_dataUser *registrasi(){
	system("cls");
	tagline();
    Node_dataUser *UserBaru = new Node_dataUser;
    string nama, tipe_identitas, nomor_identitas, jenis_kelamin, no_telp, username, password;
	int usia;
	bool loop = true;
	int pilih_jk, pilih_tipeIdn;
	bool loop_nama = false;
	bool loop_uname = false;
	bool loop_nomor = false;
	bool loop_usia = false;
	bool loop_notelp = false;
	bool loop_pass = false;

	while (loop){
		cout<< "                    REGESTRASI - USER - K'DINZY" << endl
	        << "                    -----------------------------" << endl;
		while (loop_nama == false){
			cout << "" ; inputan("Nama Lengkap "); fflush(stdin); getline(cin, nama);
			if (nama.length() > 1)
			{
				loop_nama = true;
			}
			else
			{
				setcolor(4);
				cout << "\nERROR: Nama Lengkap Wajib Diisi\n" << endl;
				setcolor(7);
				loop_nama = false;
			}
		}	

		tipIdn :
		cout << "\nPilih Tipe Identitas: " << endl
			 << "1. Passport " << endl
			 << "2. KTP" << endl;
		cout << "" ; inputan("Masukkan Pilihan "); cin >> pilih_tipeIdn;
		errorHandling(pilih_tipeIdn);	
		if (pilih_tipeIdn == 1)
		{
			tipe_identitas = "Passport";
			while (loop_nomor == false)
			{
				cout << "" ; inputan("Nomor Passport "); fflush(stdin); getline(cin, nomor_identitas);
				if (nomor_identitas.length() == 7)
				{
					loop_nomor = true;
				}
				else
				{
					setcolor(4);
					cout << "\nERROR: Passport harus terdiri dari 7 digit\n"
						<< endl;
					setcolor(7);
					loop_nomor = false;
				}
			}
		} else if (pilih_tipeIdn == 2) {
			tipe_identitas = "KTP";
			while (loop_nomor == false)
			{
				cout << "" ; inputan("Nomor KTP "); fflush(stdin); getline(cin, nomor_identitas);
				if (nomor_identitas.length() == 16)
				{
					loop_nomor = true;
				}
				else
				{
					setcolor(4);
					cout << "\nERROR: KTP harus terdiri dari 16 digit\n"
						<< endl;
					setcolor(7);
					loop_nomor = false;
				}
			}
		} else {
			setcolor(4);
			cout << "ERROR: Pilihan Tersebut Tidak Ada!" << endl;
			setcolor(7);
			goto tipIdn;
		}

		jk :
		cout << "\nPilih Jenis Kelamin: " << endl
			 << "1. Perempuan " << endl
			 << "2. Laki-Laki" << endl;
		cout << "" ; inputan("Masukkan Pilihan "); cin >> pilih_jk;
		errorHandling(pilih_jk);	
		if (pilih_jk == 1)
		{
			jenis_kelamin= "Perempuan";
		}
		else if (pilih_jk == 2)
		{
			jenis_kelamin = "Laki-Laki";
		} else {
			setcolor(4);
			cout << "ERROR: Pilihan Tersebut Tidak Ada!" << endl;
			setcolor(7);
			goto jk;
		}

		while (loop_usia == false){
			cout << "" ; inputan("Usia "); cin >> usia;
			if (usia >= 17 and usia <= 70)
			{
				loop_usia = true;
			}
			else
			{
				setcolor(4);
				cout << "\nERROR: Usia Maksimal 17 - 70 Tahun\n"
					<< endl;
				setcolor(7);
				loop_usia = false;
			}
		}	

		while (loop_notelp == false){
			cout << "Nomor Handphone     : +62 "; cin >> no_telp;
			if (no_telp.length() >= 10 or no_telp.length() >= 11 or no_telp.length() >= 12)
			{
				loop_notelp = true;
			}
			else
			{
				setcolor(4);
				cout << "\nERROR: Nomor telpon Maksimal 11 - 13 Digit\n" << endl;
				setcolor(7);
				loop_notelp = false;
			}
		}	

		while (loop_uname == false){
			cout << "" ; inputan("Username "); fflush(stdin); getline(cin, username);
			if (username.length() > 1)
			{
				loop_uname = true;
			}
			else
			{
				setcolor(4);
				cout << "\nERROR: Username Wajib Diisi\n" << endl;
				setcolor(7);
				loop_uname = false;
			}
		}	

		while (loop_pass == false){
			cout << "" ; inputan("Password "); fflush(stdin); getline(cin, password);
			if (password.length() >= 8)
			{
				loop_pass = true;
			}
			else
			{
				setcolor(4);
				cout << "\nERROR: Minimal Panjang Password 8 Karakter\n" << endl;
				setcolor(7);
				loop_pass = false;
			}
		}

		UserBaru->data_user.nama = nama;
		UserBaru->data_user.tipe_identitas = tipe_identitas;
		UserBaru->data_user.nomor_identitas = nomor_identitas;
		UserBaru->data_user.jenis_kelamin = jenis_kelamin;
		UserBaru->data_user.usia = usia;
		UserBaru->data_user.no_telp = no_telp;
		UserBaru->data_user.username = username;
		UserBaru->data_user.password = password;
		return UserBaru;
	}
}

// -----------------------------------ADMIN----------------------------------------

NodeJadwal *addJadwal(string kereta){
	system("cls");
	tagline();
	NodeJadwal *jadwalBaru = new NodeJadwal;
    string keberangkatan_awal, tujuan;
	int harga, lama_perjalanan;
	float jam;
	bool loop = true;
	bool loop_ka = false;
	bool loop_tujuan = false;
	bool loop_harga = false;
	bool loop_lp = false;
	bool loop_jam = false;

	while (loop){
		cout << "\n       K E R E T A - A P I - K ' D I N Z Y       " << endl;
		cout << "\n                    Tambah Jadwal Kereta Api "<< kereta << endl
	         << "                    ------------------------------" << endl;
		while (loop_ka == false){
			cout << "Keberangkatan Awal  : "; fflush(stdin); getline(cin, keberangkatan_awal);
			if (keberangkatan_awal.length() >= 1)
			{
				loop_ka = true;
			}
			else
			{
				setcolor(4);
				cout << "\nERROR: Keberangkatan Awal Wajib Diisi" << endl;
				setcolor(7);
				loop_ka = false;
			}
		}	

	    while (loop_tujuan == false){
			cout << "" ; inputan("\nTujuan Kereta "); fflush(stdin); getline(cin, tujuan);
			if (tujuan.length() >= 1)
			{
				loop_tujuan = true;
			}
			else
			{
				setcolor(4);
				cout << "\nERROR: Tujuan Kereta Wajib Diisi" << endl;
				setcolor(7);
				loop_tujuan = false;
			}
		}	

		while (loop_harga == false)
		{
			do
			{
			cout << "\nHarga               : Rp. "; cin >> cek;
			} while (eror_handling(cek) == true);
			harga = cek;
			if (harga >= 45000 and harga <= 400000)
			{
				loop_harga = true;
			}
			else
			{
				setcolor(4);
				cout << "\nERROR: Harga Tiket Kereta Api Minimal Rp.45000 dan Maksimal Rp.400000"
					<< endl;
				setcolor(7);
				loop_harga = false;
			}
		}

		while (loop_lp == false)
		{
			do
			{
				cout << "" ; inputan("\nLama Perjalanan "); cin >> cek;
			} while (eror_handling(cek) == true);
			lama_perjalanan = cek;
			if (lama_perjalanan >= 30 and lama_perjalanan <= 900)
			{
				loop_lp = true;
			}
			else
			{
				setcolor(4);
				cout << "\nERROR: Perjalanan Kereta Api Minimal 30 dan Maksimal 900 Menit"
					<< endl;
				setcolor(7);
				loop_lp = false;
			}
		}

		while (loop_jam == false)
		{
			cout << "" ; inputan("\nJam keberangkatan "); cin >> jam;
			if (jam >= 0 and jam < 23.60)
			{
				loop_jam = true;
			}
			else
			{
				setcolor(4);
				cout << "\nERROR: Tidak ada jam " << jam << endl;
				setcolor(7);
				loop_jam = false;
			}
		}
		cout << endl;

		jadwalBaru->data.jenis = kereta;
		jadwalBaru->data.keberangkatan_awal = keberangkatan_awal;
		jadwalBaru->data.tujuan = tujuan;
		jadwalBaru->data.harga = harga;
		jadwalBaru->data.lama_perjalanan = lama_perjalanan;
		jadwalBaru->data.jam = jam;
		return jadwalBaru;
	}
}

void tambah_jadwal(string kereta, NodeJadwal **head_jadwal, NodeJadwal **tail_jadwal){
	NodeJadwal *jadwal_baru = addJadwal(kereta);
	// NodeJadwal *sekali = *head_jadwal;
	// while (sekali != NULL){
	// 	if (sekali->data_user.username == jadwal_baru->data_user.username){
	// 		cout << "\nUsername Telah Digunakan" << endl;
	// 		return;
	// 	}
	// 	sekali = sekali->next;
	// }
	jadwal_baru->next = *head_jadwal;
	jadwal_baru->prev = NULL;
	if (*head_jadwal == NULL && *tail_jadwal == NULL){
		*head_jadwal = jadwal_baru;
		*tail_jadwal = jadwal_baru;
	}
	else {
		(*head_jadwal)->prev = jadwal_baru;
		*head_jadwal = jadwal_baru;
	}
	setcolor(2);
	cout << "\nSUCCES: Jadwal Berhasil Ditambah" << endl;
	setcolor(7);
	sleep(2);
}

void fileJadwal(NodeJadwal **head_jadwal, NodeJadwal **tail_jadwal)
{
	ifstream file;
	string jadwal, jenis, keberangkatan_awal, tujuan, harga, jam, lama;
	int harga_tiket, lama_perjalanan;
	float jam_keb;

	file.open("jadwal_kereta.txt", ios::in);
	if (file.is_open())
	{
		while (getline(file, jadwal))
		{
			NodeJadwal *nodeBaru = new NodeJadwal;
			stringstream file_jadwal(jadwal);
			getline(file_jadwal, jenis, ',');
			getline(file_jadwal, keberangkatan_awal, ',');
			getline(file_jadwal, tujuan, ',');
			getline(file_jadwal, jam, ',');
			getline(file_jadwal, lama, ',');
			getline(file_jadwal, harga, '\n');

			stringstream strjam(jam);
			stringstream strlama(lama);
			stringstream strharga(harga);

			strjam >> jam_keb;
			strlama >> lama_perjalanan;
			strharga >> harga_tiket;

			nodeBaru->data.jenis = jenis;
			nodeBaru->data.keberangkatan_awal = keberangkatan_awal;
			nodeBaru->data.tujuan = tujuan;
			nodeBaru->data.jam = jam_keb;
			nodeBaru->data.lama_perjalanan = lama_perjalanan;
			nodeBaru->data.harga = harga_tiket;

			if (*head_jadwal == NULL && *tail_jadwal == NULL)
			{
				nodeBaru->prev = NULL;
				nodeBaru->next = *head_jadwal;
				*head_jadwal = nodeBaru;
				*tail_jadwal = nodeBaru;
			}
			else
			{
				nodeBaru->prev = *tail_jadwal;
				nodeBaru->next = NULL;
				(*tail_jadwal)->next = nodeBaru;
				*tail_jadwal = nodeBaru;
			}
		}
		file.close();
	}
}

void pindah_jadwal(NodeJadwal **head_jadwal)
{
	fstream file;
	NodeJadwal *temp = *head_jadwal;

	file.open("jadwal_kereta.txt", ios::trunc | ios::out | ios::in);
	if (file.is_open())
	{
		while (temp != NULL)
		{
			file << temp->data.jenis << ",";
			file << temp->data.keberangkatan_awal << ",";
			file << temp->data.tujuan << ",";
			file << temp->data.jam << ",";
			file << temp->data.lama_perjalanan << ",";
			file << temp->data.harga << "\n";
			temp = temp->next;
		}
	}
	file.close();
}

void tampil_jadwal(){
	system("cls");
	tagline();
	NodeJadwal *head = head_jadwal;
	NodeJadwal *sekali = head;
	setcolor(6);
	printf("%-53s%-38s%5s\n", "", "DAFTAR JADWAL KERETA API", "");
	cout << "                                                         ";
	kalender();
	cout << endl;
	setcolor(8);
	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
	setcolor(1);
	printf("%-7s%-20s%-25s%-25s%-25s%-20s%5s\n", "No", "Jenis Kereta", "Keberangkatan Awal", "Tujuan Akhir", "Jam Berangkat/WITA", "Lama Perjalanan", "Harga Tiket");
	setcolor(8);
	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
	setcolor(7);
	if (sekali == NULL)
	{
		setcolor(4);
		printf("%-50s%-35s%5s\n", "", "---Jadwal Kereta Api Kosong---", "");
		setcolor(7);

		setcolor(8);
		cout << endl; cout << endl; system("pause");
		setcolor(7);
		return;
	} else { 
		int nomor = 1;
		while(sekali != NULL){
			setcolor(1);
			cout << setiosflags(ios::left) << setw(7) << nomor;
			cout << setiosflags(ios::left) << setw(20) << sekali->data.jenis;
			cout << setiosflags(ios::left) << setw(25) << sekali->data.keberangkatan_awal;
			cout << setiosflags(ios::left) << setw(25) << sekali->data.tujuan;
			std::cout << std::fixed;
			std::cout << setiosflags(ios::left) << setw(25) << std::setprecision(2) << sekali->data.jam;
			std::cout << std::fixed;
			std::cout << setiosflags(ios::left) << setw(5) << std::setprecision(2) << sekali->data.lama_perjalanan << setiosflags(ios::left) << setw(15) << " Menit";
			cout << setiosflags(ios::left) << setw(0) << "Rp. " << sekali->data.harga; cout << setiosflags(ios::left) << setw(5) << endl;
			setcolor(7);
			nomor++;
			sekali = sekali->next;
		}
	}
			setcolor(8);
		cout << endl; cout << endl; system("pause");
		setcolor(7);
}

void update_jadwal(NodeJadwal **head_jadwal){
	system("cls");
	tagline();
	int pilihan;
	int jadwal = jumlah_jadwal();
	string jenis1;
	bool loop_ka = false;
	bool loop_tujuan = false;
	bool loop_harga = false;
	bool loop_lp = false;
	bool loop_jam = false;
	NodeJadwal *temp = *head_jadwal;
	update:
	tampil_jadwal();
	if (temp != NULL){
		cout << endl;
		inputan("Masukkan Pilihan "); cin >> cek;
		pilihan = cek;
		errorHandling(pilihan);
		if (pilihan <= jadwal && pilihan > 0){
			for (int i = 1; i < pilihan; i++){
				temp = temp->next;
			}
			system("cls");
			tagline();
			cout << "\n       K E R E T A - A P I - K ' D I N Z Y       " << endl;
			cout << "\n                    Update Jadwal Kereta Api "<< temp->data.jenis << endl
				<< "                    ------------------------------" << endl;
			kereta:
			cout<< "1. Kereta Chmzy" << endl
				<< "2. Kereta Finder" << endl
				<< "3. Kereta Kacans" << endl
				<< "--------------------" << endl;
			cout << "\nJenis Kereta : "; fflush(stdin); getline(cin, jenis1);
			if (jenis1 == "1") {
				temp->data.jenis = "Chmzy";
			} else if (jenis1 == "2") {
				temp->data.jenis = "Finder";
			} else if (jenis1 == "3") {
				temp->data.jenis = "Kacans";
			} else {
				setcolor(4);
				cout << "\nERROR: Pilihan Kereta Tidak Ada!" << endl;
				setcolor(7);
				goto kereta;
			}
			system("cls");
			tagline();

			cout << "\n       K E R E T A - A P I - K ' D I N Z Y       " << endl;
			cout << "\n                    Update Jadwal Kereta Api "<< temp->data.jenis << endl
				<< "                    ------------------------------" << endl;
			while (loop_ka == false){
				cout << "Keberangkatan Awal  : "; fflush(stdin); getline(cin, temp->data.keberangkatan_awal);
				if (temp->data.keberangkatan_awal.length() >= 1)
				{
					loop_ka = true;
				}
				else
				{
					setcolor(4);
					cout << "\nERROR: Keberangkatan Awal Wajib Diisi" << endl;
					setcolor(7);
					loop_ka = false;
				}
			}	

			while (loop_tujuan == false){
				cout << "" ; inputan("\nTujuan Kereta "); fflush(stdin); getline(cin, temp->data.tujuan);
				if (temp->data.tujuan.length() >= 1)
				{
					loop_tujuan = true;
				}
				else
				{
					setcolor(4);
					cout << "\nERROR: Tujuan Kereta Wajib Diisi" << endl;
					setcolor(7);
					loop_tujuan = false;
				}
			}	

			while (loop_harga == false)
			{
				do
				{
				cout << "\nHarga               : Rp. "; cin >> cek;
				} while (eror_handling(cek) == true);
				temp->data.harga = cek;
				if (temp->data.harga >= 45000 and temp->data.harga <= 400000)
				{
					loop_harga = true;
				}
				else
				{
					setcolor(4);
					cout << "\nERROR: Harga Tiket Kereta Api Minimal Rp.45000 dan Maksimal Rp.400000"
						<< endl;
					setcolor(7);
					loop_harga = false;
				}
			}

			while (loop_lp == false)
			{
				do
				{
					cout << "" ; inputan("\nLama Perjalanan "); cin >> cek;
				} while (eror_handling(cek) == true);
				temp->data.lama_perjalanan = cek;
				if (temp->data.lama_perjalanan >= 30 and temp->data.lama_perjalanan <= 900)
				{
					loop_lp = true;
				}
				else
				{
					setcolor(4);
					cout << "\nERROR: Perjalanan Kereta Api Minimal 30 dan Maksimal 900 Menit"
						<< endl;
					setcolor(7);
					loop_lp = false;
				}
			}

			while (loop_jam == false)
			{
				cout << "" ; inputan("\nJam keberangkatan "); cin >> temp->data.jam;
				if (temp->data.jam >= 0 and temp->data.jam < 23.60)
				{
					loop_jam = true;
				}
				else
				{
					setcolor(4);
					cout << "\nERROR: Tidak ada jam " << temp->data.jam << endl;
					setcolor(7);
					loop_jam = false;
				}
			}
				setcolor(2);
				cout << "\nSUCCES: Jadwal Berhasil Diupdate" << endl;
				setcolor(7);
			} else {
				setcolor(4);
				cout << "ERROR: Pilihan Tersebut Tidak Ada!" << endl;
				setcolor(7);
				goto update;
			}
	}
	sleep(2);
}

void StatistikPenjualan(){
	system("cls");
	tagline();
	int tiketChmzy = jumlahtiket("Chmzy");
	int tiketFinder = jumlahtiket("Finder");
	int tiketKacans = jumlahtiket("Kacans");

	cout << "\n  S T A T I S T I K - P E N J U A L A N - T I K E T";
	cout << endl;
	setcolor(3);
	cout << "\n-------------------------------------------" << endl;
	cout << "    Kereta Api      Total Tiket Terjual" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "     Chmzy                 " << tiketChmzy << endl;
	cout << "     Finder                " << tiketFinder << endl;
	cout << "     Kacans                " << tiketKacans << endl;
	cout << "-------------------------------------------" << endl;
	setcolor(8);
	cout << endl; cout << endl; system("pause");
	setcolor(7);
}

void HistoryPenjualan(){
	system("cls");
	tagline();
	Node_Pesanan *front_pesan = front;


	setcolor(6);
	cout << "\n                                                     R I W A Y A T  -  P E M E S A N A N";
	cout << endl;
	setcolor(7);
	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
	setcolor(1);
	printf("%-7s%-20s%-20s%-20s%-20s%-15s%-20s%5s\n", "No", "Nama Pemesan", "Jenis Kereta", "Jam Berangkat/WITA", "Keberangkatan Awal", "Tujuan Akhir", "Jumlah Tiket", "Total Harga");
	setcolor(8);
	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
	setcolor(7);
	int nomor = 1;
	while(front_pesan != NULL){

			cout << setiosflags(ios::left) << setw(7) << nomor;
			cout << setiosflags(ios::left) << setw(20) << front_pesan->pesan.nama;
			cout << setiosflags(ios::left) << setw(20) << front_pesan->pesan.jenis;
			std::cout << std::fixed;
			std::cout << setiosflags(ios::left) << setw(20) << std::setprecision(2) << front_pesan->pesan.jam;
			cout << setiosflags(ios::left) << setw(20) << front_pesan->pesan.keberangkatan_awal;
			cout << setiosflags(ios::left) << setw(15) << front_pesan->pesan.tujuan;
			cout << setiosflags(ios::left) << setw(20) << front_pesan->pesan.jumlah_tiket;
			cout << setiosflags(ios::left) << setw(0) << "Rp. " << front_pesan->pesan.total_harga; cout << setiosflags(ios::left) << setw(5) << endl;

		front_pesan = front_pesan->next;
		nomor++;
	}
	setcolor(8);
	cout << endl; cout << endl; system("pause");
	setcolor(7);
}

void hapus_jadwal(NodeJadwal **head_jadwal, NodeJadwal **tail_jadwal){
	system("cls");
	tagline();
	NodeJadwal *cur = *head_jadwal;
	int panjangjadwal = jumlah_jadwal();
	int indeks;
	tampil_jadwal();
	cout << "\nMasukkan Pilihan : "; cin >> indeks;
	errorHandling(indeks);
	int hapus = indeks - 1;
	if (hapus == 0 and panjangjadwal > 1) {
		NodeJadwal *del = *head_jadwal;
		*head_jadwal = (*head_jadwal)->next;
		(*head_jadwal)->prev = NULL;
		delete del;
	} else if (hapus == 0 && panjangjadwal == 1) {
		NodeJadwal *del = *head_jadwal;
		*head_jadwal = NULL;
		*tail_jadwal = NULL;
		delete del;
	} else if (hapus == panjangjadwal - 1) {
		NodeJadwal *del;
		del = *tail_jadwal;
		*tail_jadwal = (*tail_jadwal)->prev;
		(*tail_jadwal)->next = NULL;
		delete del;
	} else {
		if (hapus < panjangjadwal / 2)
		{
			NodeJadwal *cur = *head_jadwal;
			for (int trv = 1; trv <= hapus; trv++)
			{
				cur = cur->next;
			}
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			delete cur;
		} else {
			NodeJadwal *cur = *tail_jadwal;
			for (int trv = panjangjadwal - 1; trv > hapus; trv--)
			{
				cur = cur->prev;
			}
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			delete cur;
		}
	}
	panjangjadwal--;
	setcolor(2);
	cout << "\nSUCCES: Jadwal Berhasil Dihapus" << endl;
	setcolor(7);
	sleep(2);
}

void FrontBackSplit(NodeJadwal *source, NodeJadwal **frontRef, NodeJadwal **backRef) {
    NodeJadwal *fast;
    NodeJadwal *slow;
    slow = source;
    fast = source->next;
   
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
 
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

void MergeSortKeberangkatan(NodeJadwal **headRef) {
	NodeJadwal *head = *headRef;
	NodeJadwal *a;
	NodeJadwal *b;
	/* Base case -- length 0 or 1 */
	if ((head == NULL) || (head->next == NULL)) {
		return;
	}
	/* Split head into 'a' and 'b' sublists */
	FrontBackSplit(head, &a, &b);
	/* Recursively sort the sublists */
	MergeSortKeberangkatan(&a);
	MergeSortKeberangkatan(&b);
	/* answer = merge the two sorted lists together */
	*headRef = SortedMergeKeberangkatan(a, b);
} 

NodeJadwal *SortedMergeKeberangkatan(NodeJadwal *a, NodeJadwal *b) {
	NodeJadwal *result = NULL;
  
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

	if (a->data.keberangkatan_awal <= b->data.keberangkatan_awal) {
        result = a;
        result->next = SortedMergeKeberangkatan(a->next, b);
    }
    else {
        result = b;
        result->next = SortedMergeKeberangkatan(a, b->next);
    }
    return (result);
}

int fibonacciSearchKeberangkatan(NodeJadwal *node, string x, int n) {
    int F0 = 0; 
    int F1 = 1; 
    int F = F0 + F1; 
    while (F < n){
        F0 = F1;
        F1 = F;
        F = F0 + F1;
    }

    int offset = -1;
    int trv = 0;

    while (F > 1){
    	NodeJadwal *temp = node;
        int i = min(offset + F0, n - 1);
        while (temp->next != NULL && trv < i){
        	temp = temp->next;
        	trv++;
		}
        if (temp->data.keberangkatan_awal < x){
            F = F1;
            F1 = F0;
            F0 = F - F1;
            offset = i;
        }
        else if (temp->data.keberangkatan_awal > x){
            F = F0;
            F1 = F1 - F0;
            F0 = F - F1;
        }
        else return i;
        trv = 0;
    }
    NodeJadwal *temp2 = node;
    while (temp2->next != NULL && trv < offset+1){
        	temp2 = temp2->next;
        	trv++;
	}
    if (F1 && temp2->data.keberangkatan_awal == x) return offset + 1;
    return -1;
}

void menuAdmin(){
	system("cls");
	tagline();
	NodeJadwal *head = head_jadwal;
	NodeJadwal *sekali = head;
	int pilih, pilih1, pilih2, pilih3;
	string data_cari;
	int panjang_jadwal = jumlah_jadwal();
	setcolor(3);
	cout << "\n            MENU UTAMA ADMIN" << endl            
			<< "---------------------------------------" << endl
		 << "1. Kelola Jadwal" << endl
		 << "2. Tampil Semua Jadwal" << endl
		 << "3. Statistik Penjualan Tiket" << endl
		 << "4. History Penjualan" << endl
		 << "5. Cari Jadwal" << endl
		 << "6. Kelola Data User" << endl
		 << "0. Logout" << endl
		 << "---------------------------------------" << endl;
	setcolor(7);
	cout << "" ; inputan("Masukkan Pilihan "); cin >> cek;
	pilih = cek;
	errorHandling(pilih);
	if(pilih == 1){
		system("cls");
		tagline();
		setcolor(3);
		 cout << "\n      KELOLA JADWAL KERETA " << endl            
			<< "---------------------------------------" << endl
			<< "1. Tambah Jadwal" << endl
			<< "2. Update Jadwal" << endl
			<< "3. Hapus Jadwal" << endl
			<< "0. Kembali" << endl;
		setcolor(7);
		cout << "" ; inputan("Masukkan Pilihan "); cin >> cek;
		pilih1 = cek;
		errorHandling(pilih1);
		if (pilih1 == 1){
			kereta:
			system("cls");
			tagline();
			setcolor(3);
			cout << "\n          JENIS KERETA API" << endl            
				<< "---------------------------------------" << endl
				<< "1. Kereta Chmzy" << endl
				<< "2. Kereta Finder" << endl
				<< "3. Kereta Kacans" << endl
				<< "0. Kembali" << endl
				<< "---------------------------------------" << endl;
			setcolor(7);
			cout << "" ; inputan("Masukkan Pilihan "); cin >> cek;
			pilih2 = cek;
			errorHandling(pilih2);
			if (pilih2 == 1){
				tambah_jadwal("Chmzy",&head_jadwal, &tail_jadwal);
				MergeSortKeberangkatan(&head_jadwal);
				pindah_jadwal(&head_jadwal);
				menuAdmin();
			} else if (pilih2 == 2){
				tambah_jadwal("Finder",&head_jadwal, &tail_jadwal);
				pindah_jadwal(&head_jadwal);
				menuAdmin();
			} else if (pilih2 == 3){
				tambah_jadwal("Kacans",&head_jadwal, &tail_jadwal);
				pindah_jadwal(&head_jadwal);
				menuAdmin();
			} else if (pilih2 == 0){
				menuAdmin();
			} else {
				setcolor(4);
				cout << "ERROR: Pilihan Tersebut Tidak Ada!" << endl;
				setcolor(7);
				goto kereta;
			}
		} else if (pilih1 == 2){
			update_jadwal(&head_jadwal);
			pindah_jadwal(&head_jadwal);
			menuAdmin();
		} else if (pilih1 == 3){
			hapus_jadwal(&head_jadwal, &tail_jadwal);
			pindah_jadwal(&head_jadwal);
			menuAdmin(); 
		} else if (pilih1 == 0){
			menuAdmin();
		} else {
			setcolor(4);
			cout << "ERROR: Pilihan Tersebut Tidak Ada!" << endl;
			setcolor(7);
			menuAdmin();
		}
	} else if (pilih == 2){
		tampil_jadwal();
		pindah_jadwal(&head_jadwal);
		menuAdmin();
	} else if (pilih == 3){
		StatistikPenjualan();
		menuAdmin();
	} else if (pilih == 4){
		HistoryPenjualan();
		menuAdmin();
	} else if (pilih == 5){
		system("cls");
		tagline();
		MergeSortKeberangkatan(&head_jadwal);

		cout << "\nMasukkan Keberangkatan Awal : "; fflush(stdin); getline(cin, data_cari);
		int indeks = fibonacciSearchKeberangkatan(head_jadwal, data_cari, panjang_jadwal);
		if (indeks >= 0) {
			setcolor(6);
			printf("%-53s%-38s%5s\n", "", "DAFTAR JADWAL KERETA API", "");
			cout << "                                                         ";
			kalender();
			cout << endl;
			setcolor(8);
			cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
			setcolor(1);
			printf("%-7s%-20s%-25s%-25s%-25s%-20s%5s\n", "No", "Jenis Kereta", "Keberangkatan Awal", "Tujuan Akhir", "Jam Berangkat/WITA", "Lama Perjalanan", "Harga Tiket");
			setcolor(8);
			cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
			setcolor(7);
			for (int i = 0; i < indeks; i++){
				sekali = sekali->next;
			}
			setcolor(1);
			cout << setiosflags(ios::left) << setw(7) << indeks+1;
			cout << setiosflags(ios::left) << setw(20) << sekali->data.jenis;
			cout << setiosflags(ios::left) << setw(25) << sekali->data.keberangkatan_awal;
			cout << setiosflags(ios::left) << setw(25) << sekali->data.tujuan;
			std::cout << std::fixed;
			std::cout << setiosflags(ios::left) << setw(25) << std::setprecision(2) << sekali->data.jam;
			std::cout << std::fixed;
			std::cout << setiosflags(ios::left) << setw(5) << std::setprecision(2) << sekali->data.lama_perjalanan << setiosflags(ios::left) << setw(15) << " Menit";
			cout << setiosflags(ios::left) << setw(0) << "Rp. " << sekali->data.harga; cout << setiosflags(ios::left) << setw(5) << endl;
			setcolor(7);
		}  else {
			setcolor(4);
			cout << "\nERROR: Keberangkatan Awal " << data_cari << " tidak ditemukan pada jadwal!" << endl;
			setcolor(7);
		}
				setcolor(8);
		cout << endl; cout << endl; system("pause");
		setcolor(7);
		menuAdmin();
	} else if (pilih == 6){
		kelola_user :
		system("cls");
		tagline();
		setcolor(3);
		cout<< "\n            KELOLA DATA USER           |" << endl
			<< "---------------------------------------" << endl
			<< "1. Lihat data user" << endl
			<< "2. Update data user" << endl
			<< "3. Check in Tiket" << endl
			<< "0. Kembali" << endl
			<< "---------------------------------------" << endl;
			setcolor(7);
			cout << "" ; inputan("Masukkan Pilihan "); cin >> cek;
			pilih3 = cek;
			errorHandling(pilih3);		
			if (pilih3 == 1){
				datauser();
				menuAdmin();
			} else if (pilih3 == 2){
				update_data_user(&head_user);
				menuAdmin();
			} else if (pilih3 == 3){
				tiket_masuk(&front);
				menuAdmin();
			} else if (pilih3 == 0){
				menuAdmin();
			} else {
				setcolor(4);
				cout << "ERROR: Pilihan Tersebut Tidak Ada!" << endl;
				setcolor(7);
				goto kelola_user;
			}
	} else if (pilih == 0){
		cout << "\nAnda Telah Logout" << endl;
		menu_login();
	} else {
		setcolor(4);
		cout << "ERROR: Pilihan Tersebut Tidak Ada!" << endl;
		setcolor(7);
		menuAdmin();
	}
}

void regis(Node_dataUser **head_user, Node_dataUser **tail_user)
{
    Node_dataUser *UserBaru = registrasi();
    Node_dataUser *sekali = *head_user;
    while (sekali != NULL){
		if (sekali->data_user.username == UserBaru->data_user.username){
			cout << "\nUsername Telah Digunakan" << endl;
			return;
		}
		sekali = sekali->next;
	}
    UserBaru->prev = *tail_user;
	UserBaru->next = NULL;
	if (*head_user == NULL && *tail_user == NULL){
		*head_user = UserBaru;
		*tail_user = UserBaru;
	}
	else {
		(*tail_user)->next = UserBaru;
		*tail_user = UserBaru;
	}
	sleep(1);
	setcolor(2);
	cout << "\nSUCCES: Berhasil Melakukan Registrasi" << endl;
	setcolor(7);
	sleep(2);
}

void fileUser(Node_dataUser **head_user,Node_dataUser **tail_user){
	ifstream file;
    string akun_user, nama, tipe_identitas, nomor_identitas, jenis_kelamin, no_telp, username, password, usia;
	int usia_int;

	file.open("akun_user1.txt", ios::in);
	if (file.is_open())
	{
		while (getline(file, akun_user))
		{
			Node_dataUser *UserBaru = new Node_dataUser;
			stringstream akun(akun_user);
			getline(akun, nama, ',');
			getline(akun, tipe_identitas, ',');
			getline(akun, nomor_identitas, ',');
			getline(akun, jenis_kelamin, ',');
			getline(akun, usia, ',');
			getline(akun, no_telp, ',');
			getline(akun, username, ',');
			getline(akun, password, '\n');

			stringstream strusia(usia);

			strusia >> usia_int;

			UserBaru->data_user.nama = nama;
			UserBaru->data_user.tipe_identitas = tipe_identitas;
			UserBaru->data_user.nomor_identitas = nomor_identitas;
			UserBaru->data_user.jenis_kelamin = jenis_kelamin;
			UserBaru->data_user.usia = usia_int;
			UserBaru->data_user.no_telp = no_telp;
			UserBaru->data_user.username = username;
			UserBaru->data_user.password = password;


			if (*head_user == NULL && *tail_user == NULL)
			{
				UserBaru->prev = NULL;
				UserBaru->next = *head_user;
				*head_user = UserBaru;
				*tail_user = UserBaru;
			}
			else
			{
				UserBaru->prev = *tail_user;
				UserBaru->next = NULL;
				(*tail_user)->next = UserBaru;
				*tail_user = UserBaru;
			}
		}
		file.close();
	}
}

void pindahAkun_user(Node_dataUser **head_user)
{
	fstream file;
	Node_dataUser *temp = *head_user;

	file.open("akun_user1.txt", ios::trunc | ios::out | ios::in);
	if (file.is_open())
	{
		while (temp != NULL)
		{
			file << temp->data_user.nama << ",";
			file << temp->data_user.tipe_identitas << ",";
			file << temp->data_user.nomor_identitas << ",";
			file << temp->data_user.jenis_kelamin << ",";
			file << temp->data_user.usia << ",";
			file << temp->data_user.no_telp << ",";
			file << temp->data_user.username << ",";
			file << temp->data_user.password << "\n";
			temp = temp->next;
		}
	}
	file.close();
}

void lupa_password(Node_dataUser *head_user)
{
	int i = 0;
	string username_ingat;
	int usia_ingat;

	system("cls");
	tagline();

	cout << "\nMasukkan Username yang Anda Ingat : ";
	cin >> username_ingat;
	cout << "\nMasukkan Usia yang Anda Ingat     : ";
	cin >> usia_ingat;

	while (head_user != NULL)
	{
		if (username_ingat == head_user->data_user.username && usia_ingat  == head_user->data_user.usia)
		{
			i = 1;
			break;
		}
	}
	if (i == 1)
	{
		sleep(2);
		system("cls");
		tagline();
		setcolor(2);
		cout << "\nSUCCES: Akun Anda Ditemukan" << endl;
		setcolor(7);
		cout << "\nPassword Anda : " << head_user->data_user.password << endl;
		setcolor(4);
		cout << "\n-----SELALU INGAT PASSWORD ANDA-----" << endl;
		setcolor(8);
		cout << endl; cout << endl; system("pause");
		setcolor(7);
		menu_login();
	}
	else
	{
		sleep(2);
		system("cls");
		tagline();
		setcolor(4);
		cout << "---- MAAF, Akun Tidak Ditemukan!----" << endl;
		setcolor(7);
		sleep(3);
		menu_login();
	}
}


void login(Node_dataUser *head_user)
{
	string login = "block";
	bool loop_pass = false;
	bool loop_uname = false;
	system("cls");
	tagline();
    int i = 0, a = 1;
	char pilih;

	do{
		string username1, password1;
		
		while (loop_uname == false){
			cout << "" ; inputan("\nMasukkan Username "); cin >> username1;
			if (username1.length() > 1)
			{
				loop_uname = true;
			}
			else
			{
				setcolor(4);
				cout << "\nERROR: Username Wajib Diisi\n" << endl;
				setcolor(7);
				loop_uname = false;
			}
		}	
		while (loop_pass == false){
			cout << "" ; inputan("\nMasukkan Password "); ch = _getch();
			while (ch != 13)
			{
				password1.push_back(ch);
				cout << '*';
				ch = _getch();
			}

			if (password1.length() >= 5)
			{
				loop_pass = true;
			}
			else
			{
				setcolor(4);
				cout << "\n\nERROR: Minimal Panjang Password 8 Karakter\n" << endl;
				setcolor(7);
				loop_pass = false;
			}
		}


		// ch = _getch();

		// while (ch != 13)
		// {
		// 	password.push_back(ch);
		// 	cout << '*';
		// 	ch = _getch();
		// }
		// cout << endl;
		// ifstream read("akun_user.txt");
		ifstream read("akun_user1.txt");

		while (head_user != NULL)
		{
			if (head_user->data_user.username == username1)
			{
				if (head_user->data_user.password == password1){

					sleep(1);
					setcolor(2);
					cout << endl;
					cout << "\nSUCCES: Anda Berhasil Login" << endl;
					sleep(1);
					setcolor(7);
					UserTerkini.insert({"Active", head_user->data_user.nama});
					system("cls");
					tagline();
					sleep(1);
					setcolor(1);
					cout << "\n                                         W E L C O M E - TO - K ' D I N Z Y - K A I                         " << endl;
					setcolor(7); 
					cout << "                                                     "<< head_user->data_user.nama <<"                         " << endl;
					sleep(2);
					login = "Berhasil";
					a = 4;
					menuUser();
					break;
				} else {
					setcolor(4);
					cout << endl;
					cout << "\nLOGIN ERROR: Username/Password Salah!\n" << endl;
					setcolor(7);
					cout << "Lupa Password? [y/t] : ", cin >> pilih;
					if (pilih == 'y')
					{
						lupa_password(head_user);
					}
					else if (pilih == 't')
					{
						a = a + 1;
						break;
					}
				}
			} else if (username1 == "admin" && password1 == "admin"){
				sleep(1);
				setcolor(2);
				cout << endl;
				cout << "\nSUCCES: Anda Berhasil Login" << endl;
				setcolor(7);
				sleep(1);
				system("cls");
				tagline();
				setcolor(1);
				cout << "\n                                          W E L C O M E - TO - K ' D I N Z Y - K A I                         " << endl;
				setcolor(7);
				cout << "                                                             ADMIN                         " << endl;
				sleep(2);
				login = "Berhasil";
				a = 4;
				menuAdmin();
				break;
			}
			head_user = head_user->next;
			
		}
		if (username1 == "admin" && password1 == "admin"){
			sleep(1);
			setcolor(2);
			cout << endl;
			cout << "\nSUCCES: Anda Berhasil Login" << endl;
			setcolor(7);
			sleep(1);
			system("cls");
			tagline();
			setcolor(1);
			cout << "\n                                             W E L C O M E - TO - K ' D I N Z Y - K A I                         " << endl;
			setcolor(7);
			cout << "                                                                 ADMIN                         " << endl;
			sleep(2);
			login = "Berhasil";
			a = 4;
			menuAdmin();
			break;
		} else {
			setcolor(4);
			cout << endl;
			cout << "\nLOGIN ERROR: Username/Password Salah!\n"<< endl;
			setcolor(7);
			a = a + 1;
			break;
		}
	} while (a <= 3);
	if (login!= "Berhasil")
	{
		setcolor(4);
		cout << "\nERROR: Anda telah 3x salah login!\n";
		setcolor(7);
		exit(0);
	}
	sleep(2);
}

void menu_login(){
	system("cls");
	tagline();
    int pilihan;
	while(pilihan != 3){
		system("cls");
		tagline();
		setcolor(3);
		cout<< "\n           PILIH MENU SIGN "<< endl
			<< "---------------------------------------" << endl
			<< "1. Login" << endl
			<< "2. Registrasi" << endl
			<< "3. Exit" << endl
			<< "---------------------------------------" << endl;
		setcolor(7);
		cout << "" ; inputan("Masukkan Pilihan "); cin >> cek;
		
		pilihan = cek;
		errorHandling(pilihan);
		switch (pilihan){
			case 1:
				UserTerkini.clear();
				login(head_user);
				pindahAkun_user(&head_user);
				break;
			case 2:
				UserTerkini.clear();
				regis(&head_user, &tail_user);
				pindahAkun_user(&head_user);
				break;
			case 3:
				exit(0);
				break;
			default:
				setcolor(4);
				cout << "ERROR: Pilihan Tersebut Tidak Ada!" << endl;
				setcolor(7);
		}
	}
}

int main()
{
	fileUser(&head_user, &tail_user);
	fileJadwal(&head_jadwal, &tail_jadwal);

	system("cls");
	menu_login();
}