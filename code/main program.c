/*
  Raihan Nur Ramadhan
  
  Online Bus Reservation Project in C Programming
  
  See the complete project details at: https://github.com/raihannur45/online-bus-reservation-program
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include "database.h"

struct database *user = NULL;

void header();
void headerlogin();
struct database *login();
void kodebus();
void buat_akun();
void menu_utama();
void menu_admin();
void pesan_tiket();
void lihat_detail();
void ubah_jadwal();
void batal();
void dompet();
void salin_data(struct database **tujuan, struct database *sumber);
void cetak_data(struct database *cetak);
void urut_tiket(struct database *cari);
void tukar_data(struct database *a, struct database *b);
void filter_tiket(struct database **cari, int *x);
int harga_tiket(struct database *temp);
void detail_pemesanan();
void reset_kursi();
void hapus_booking();
void panduan();
void denah_kursi();
void loading();
int cmpstr(const char* str, const char* substr);
void tambah_database();
void cari_database();
void cetak_database();
void ubah_database();
void hapus_database();
void cetak(struct database *temp);

int main(){
	input_database();
	int pilih;
	do{
		kodebus();		//memanggil fungsi untuk mengisi kode bus pada database
		headerlogin();		//memanggil fungsi header
		printf("1. Sudah punya akun\n2. Buat akun baru\n0. Tutup aplikasi\nPilih: ");
		//do while untuk error handling
		do{
			scanf("%d", &pilih);
			if(pilih < 0 || pilih > 2){
				printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
			}
		} while(pilih < 0 || pilih > 2);
		//apabila user memilih 1 maka akan diarahkan ke fungsi untuk melakukan login
		if(pilih == 1){
			user = login();		//node akun yang ditemukan akan ditunjuk oleh struct user
			if(user != NULL){
				if(strcmp(user->username, "admin") == 0 && strcmp(user->password, "admin") == 0){
					menu_admin();	//apabila struct user menunjuk ke akun admin maka akan diarahkan ke menu admin
				} else{
					menu_utama();	//apabila struct user menunjuk ke akun selain admin maka akan login dan diarahkan ke menu utama
				}	
			} 	
		//apabila user memilih 2 maka akan diarahkan ke fungsi untuk membuat akun baru
		} else if(pilih == 2){
			buat_akun();
		//apabila user memilih selain 1 dan 2 maka user akan diarahkan untuk keluar dari program
		} else {
			headerlogin();
			printf("Apakah anda yakin ingin menutup program ini?\n0. Iya\n1. Tidak\nPilih: ");
			do{
				scanf("%d", &pilih);
				if(pilih < 0 || pilih > 1){
					printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
				}	
			} while(pilih < 0 || pilih > 1);
		}
	} while(pilih != 0);
	return 0;
}

void headerlogin(){	//fungsi untuk membuat header pada halaman login
	system("cls");
	printf("\t\t\t\t\t\t        **        \n");
	printf("\t\t\t\t\t\t      ******      \n");
	printf("\t\t\t\t\t\t    **********    \n");
	printf("\t\t\t\t\t\t  **************  \n");	
	printf("\t\t\t\t\t\t******************\n");
	printf("\t\t\t\t\t       *  Ailasor Online  *\n");
	printf("\t\t\t\t\t\t******************\n");
	printf("\t\t\t\t\t\t  **************  \n");
	printf("\t\t\t\t\t\t    **********    \n");
	printf("\t\t\t\t\t\t      ******      \n");
	printf("\t\t\t\t\t\t        **        \n");
	printf("\t\t\t\t      Kenyamanan Anda Adalah Prioritas Kami\n\n");
}

void header(){	//fungsi untuk membuat header
	system("cls");
	printf("\t\t\t\t\t\t******************\n");
	printf("\t\t\t\t\t\t* Ailasor Online *\n");
	printf("\t\t\t\t\t\t******************\n\n");
}

struct database *login(){	//fungsi untuk melakukan login
	int pilih, i = 0;
	char cekuser[20], cekpwd[20];
	struct database *temp;
	header();
	printf("Username: ");	//input username dan dimasukkan ke variabel untuk nantinya di cek dengan database
	scanf("%s", cekuser);
	printf("Password: ");	//input password
	//script untuk menginput password agar menjadi **** dan nantinya akan di cek dengan database
	while(1){
        cekpwd[i] = getch();	//menerima input karakter dan disimpan pada array
        if(cekpwd[i] == 13) break;	//apabila karakter yang diinput adalah ENTER maka penginputan password berakhir
        //apabila karakter yang diinput adalah backspace maka akan menghapus simbol * dan karakter yang telah terinput
		else if(cekpwd[i] == 8){	
            if(i > 0){
            	i--;
            	cekpwd[i] = '\0';
            	printf("\b \b");
			}
		//apabila selain ENTER dan backspace maka akan mencetak simbol * untuk merepresentasikan karakter
        } else{
        	if(i < 20){
        		i++;
        		printf("*");
			}
		}
    }
    cekpwd[i] = '\0';	//deklarasi akhir dari password
    //melakukan cek ke database
    temp = akun;
    while(temp != NULL){
    	if(strcmp(cekuser, temp->username) == 0 && strcmp(cekpwd, temp->password) == 0){
			return temp;	//apabila ditemukan username dan password yang cocok di database, maka akan mereturn node database tersebut
		}
		temp = temp->next;
	}
	//kondisi apabila tidak ditemukan username dan password yang cocok, maka akan mereturn nilai -1
	printf("\nUsername atau Password yang anda masukkan salah\nTekan tombol apapun untuk kembali ke halaman login");
	getch();
	return NULL;
}

void kodebus(){	//fungsi untuk mengisi kode bus pada database
	struct database *temp = bus;	
	int b = 0, d = 0;
	while(temp != NULL){
		if(strcmp("Ekonomi",temp->kelas) == 0){	//untuk bus kelas ekonomi maka kode akan diawali dengan huruf E
			sprintf(temp->kode,"E-%04d",b);
			b++;
		}else{										//untuk bus kelas eksekutif maka kode akan diawali dengan huruf X
			sprintf(temp->kode,"X-%04d",d);	
			d++;
		}
		temp = temp->next;
	}
}

void buat_akun(){	//fungsi untuk membuat akun baru
	int i, pilih, user_terpakai;
	char namabaru[20], userbaru[20], pwdbaru[20], cekpwd[20];
	struct database *temp;
	header();
	printf("Buat akun Ailasor Online\n");
	printf("Masukkan nama anda\n: ");	//memasukkan nama untuk akun
	scanf("\n");
	scanf("%[^\n]s", &namabaru);
	printf("Masukkan username yang diinginkan (username hanya boleh menggunakan huruf, angka, underscores, dan titik)\n: ");	//memasukkan username
	do{
		user_terpakai = 0;
		scanf("%s", &userbaru);
		temp = akun;
		while(temp != NULL){
			if(strcmp(userbaru, temp->username) == 0){
				printf("Username sudah digunakan, silahkan masukkan username lain\n: ");
				user_terpakai = 1;
			}
			temp = temp->next;
		}
	} while(user_terpakai == 1);
	printf("Password (4 - 20 karakter)\n: ");	//memasukkan password
	do{
		i = 0;
		while(1){
	        pwdbaru[i] = getch();
	        if(pwdbaru[i] == 13) break;
	        else if(pwdbaru[i] == 8){
	            if(i > 0){
	            	i--;
	            	pwdbaru[i] = '\0';
	            	printf("\b \b");
				}
	        } else{
	        	if(i < 20){
	        		i++;
	        		printf("*");
				}
			}
	    }
    	pwdbaru[i] = '\0';
    	//apabila password kurang dari 4 karakter maka user diminta untuk menginput ulang password
	    if(i < 4) printf("\nPassword kurang dari 4 karakter, silahkan masukkan ulang password yang diinginkan\n: ");
	} while(i < 4);	
	do{
		//user diminta untuk memasukkan ulang password yang sebelumnya telah dimasukkan
		printf("\nMasukkan kembali password\n: ");
		i = 0;
		while(1){
	        cekpwd[i] = getch();
	        if(cekpwd[i] == 13) break;
	        else if(cekpwd[i] == 8){
	            if(i > 0){
	            	i--;
	            	cekpwd[i] = '\0';
	            	printf("\b \b");
				}
	        } else{
	        	if(i < 20){
	        		i++;
	        		printf("*");
				}
			}
	    }
	    cekpwd[i] = '\0';
	    //apabila konfirmasi password salah maka user diberi pilihan untuk konfirmasi ulang atau kembali ke menu awal
	    if(strcmp(cekpwd, pwdbaru) != 0){
	    	printf("\nPassword salah\n1. Konfimasi ulang password\n0. Kembali\nPilih: ");
		    do{
				scanf("%d", &pilih);
				if(pilih < 0 || pilih > 1){
					printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
				}
			} while(pilih < 0 || pilih > 1);
			if(pilih == 0)	return;
		}
	} while(strcmp(cekpwd, pwdbaru) != 0);	//akan terus looping selama konfirmasi password salah
	
	insert_akun(userbaru, pwdbaru, namabaru, 0);	//memasukkan data akun baru ke database akun
    //pemberitahuan bahwa akun telah berhasil dibuat
	printf("\nAkun berhasil dibuat\nTekan tombol apapun untuk kembali ke halaman login\n");
	getch();	
}

void menu_utama(){	//fungsi yang berisikan menu utama dari program
	int pilih;
	do{
		header();
		printf("Selamat datang %s, ada yang bisa kami bantu?\n\n", user->nama);	//nama user akan ditampilkan sesuai database
		printf("1. Pesan tiket\n2. Lihat detail pemesanan\n3. Ubah jadwal\n4. Batalkan tiket\n5. Dompet Ailasor\n6. Panduan\n0. Keluar\n\nPilih: ");
		scanf("%d", &pilih);
		if(pilih == 1){						//apabila pilih 1 maka akan diarahkan ke fungsi untuk memesan tiket
			pesan_tiket();
		} else if(pilih == 2){				//apabila pilih 2 maka akan diarahkan ke fungsi untuk melihat tiket yang sudah dipesan
			lihat_detail();
		} else if(pilih == 3){				//apabila pilih 3 maka akan diarahkan ke fungsi untuk mengubah jadwal perjalanan
			ubah_jadwal();
		} else if(pilih == 4){				//apabila pilih 4 maka akan diarahkan ke fungsi untuk membatalkan tiket
			batal();
		} else if(pilih == 5){				//apabila pilih 5 maka akan diarahkan ke fungsi untuk mengecek Dompet Ailasor
			dompet();
		} else if(pilih == 6){				//apabila pilih 6 maka akan diarahkan ke fungsi untuk melihat panduan pengguna
			panduan();
		} else if(pilih == 0){				//apabila pilih 0 maka akan diarahkan untuk keluar dari menu utama
			header();
			printf("Apakah anda yakin ingin keluar?\n0. Iya\n1. Tidak\nPilih: ");
			do{
				scanf("%d", &pilih);
				if(pilih < 0 || pilih > 1){
					printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
				}	
			} while(pilih < 0 || pilih > 1);
		} else {
			printf("\nError!! input salah\nTekan tombol apapun untuk kembali ke menu utama");
			getch();
		}
	} while(pilih != 0);
}

void menu_admin(){	//fungsi yang berisikan menu admin
	int pilih;
	do{
		kodebus();
		header();
		printf("Menu Admin\n\n");
		printf("1. Tambah database bus\n2. Cari database bus\n3. Cetak database\n4. Ubah database bus \n5. Hapus database bus\n0. Keluar\n\nPilih: ");
		scanf("%d", &pilih);
		if(pilih == 1){						//apabila pilih 1 maka akan diarahkan ke fungsi untuk menambah database bus
			tambah_database();
		} else if(pilih == 2){				//apabila pilih 2 maka akan diarahkan ke fungsi untuk mencari database bus
			cari_database();
		} else if(pilih == 3){				//apabila pilih 3 maka akan diarahkan ke fungsi untuk mengubah database bus yang sudah ada
			cetak_database();
		} else if(pilih == 4){				//apabila pilih 4 maka akan diarahkan ke fungsi untuk mengubah database bus yang sudah ada
			ubah_database();
		} else if(pilih == 5){				//apabila pilih 5 maka akan diarahkan ke fungsi untuk menghapus database bus yang sudah ada
			hapus_database();
		} else if(pilih == 0){				//apabila pilih 0 maka akan diarahkan untuk keluar dari menu utama
			header();
			printf("Apakah anda yakin ingin keluar?\n0. Iya\n1. Tidak\nPilih: ");
			do{
				scanf("%d", &pilih);
				if(pilih < 0 || pilih > 1){
					printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
				}	
			} while(pilih < 0 || pilih > 1);
		} else {
			printf("\nError!! input salah");
			getch();
		}
	} while(pilih != 0);
}

void pesan_tiket(){	//fungsi untuk memesan tiket
	int i, j, k, pilih, filter, x, kursi_terisi, tanggaltemp, bulantemp, tahuntemp;
	char cekasal[20], cektujuan[20], telp[20], email[30];
	struct database *temp;	
	struct database *cari;	//struct untuk menyimpan hasil pencarian tiket
	header();
	//memasukkan informasi awal untuk pemesanan tiket
	printf("Masukkan kota asal: ");
	scanf("%s", &cekasal);
	strupr(cekasal);
	printf("Masukkan kota tujuan: ");
	scanf("%s", &cektujuan);
	strupr(cektujuan);
	printf("Masukkan tanggal keberangkatan\nTanggal: ");
	scanf("%d", &tanggaltemp);
    printf("Bulan: ");
	scanf("%d", &bulantemp);
    printf("Tahun: ");
	scanf("%d", &tahuntemp);
    sprintf(user->tanggal, "%d/%d/%d", tanggaltemp, bulantemp, tahuntemp);
	printf("Masukkan jumlah tiket: ");
	scanf("%d", &user->jumlah_tiket);
	printf("Mencari bus");
	loading();	//memanggil fungsi untuk animasi loading
	reset_filter:	//label untuk melakukan perintah goto
	x = 0;
	cari = NULL;
	filter = 0;	//variabel filter menandakan apakah data hasil pencarian sedang difilter atau tidak
	//mencari data bus yang cocok dengan informasi yang telah dimasukkan diawal fungsi
	temp = bus;
    while(temp != NULL){
    	if(cmpstr(temp->asal, cekasal) == 0 && cmpstr(temp->tujuan, cektujuan) == 0 && temp->kursi >= user->jumlah_tiket){
			salin_data(&cari, temp);	//memanggil fungsi untuk menyalin informasi dari database ke struct cari
			x++;
		}
		temp = temp->next;
	}
	//apabila tidak ada data yang cocok maka akan dikembalikan ke menu utama
	if(cari == NULL){
		printf("\nHasil tidak ditemukan\nTekan tombol apapun untuk kembali ke menu utama");
		getch();
		return;
	}
	do{
		header();
		printf("\n%d bus ditemukan\n\n", x);
		cetak_data(cari);	//memanggil fungsi untuk mencetak hasil pencarian
		if(filter == 0){	//beberapa menu pilihan apabila filter data belum aktif
			printf("1. Pilih tiket\n2. Urutkan tiket\n3. Filter tiket\n0. Kembali\nPilih: ");
		} else{		//akan ada tambahan menu "reset filter" apabila filter sudah aktif
			printf("1. Pilih tiket\n2. Urutkan tiket\n3. Tambah filter\n4. Hapus filter\n0. Kembali\nPilih: ");
		}
		do{
			scanf("%d", &pilih);
			if(pilih < 0 || pilih > 4){
				printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
			}
		} while(pilih < 0 || pilih > 4);
		if(pilih == 2){					//apabila pilih 2 maka akan diarahkan ke fungsi untuk melakukan sorting pada hasil pencarian
			urut_tiket(cari);
		} else if(pilih == 3){			//apabila pilih 3 maka akan diarahkan ke fungsi untuk memfilter hasil pencarian
			filter = 1;		//menandakan filter sudah aktif
			filter_tiket(&cari, &x);
		} else if(pilih == 4){			//apabila pilih 4 maka akan dilakukan perintah goto untuk kembali ke label reset_filter
			goto reset_filter;
		} else if(pilih == 0){			//apabila pilih 0 maka akan diarahkan ke menu utama
			return;
		}
	} while(pilih == 2 || pilih == 3);		//akan terus looping apabila user memilih 2 dan 3
	//apabila user memilih 1 maka program akan lanjut untuk memasukkan tiket yang dipilih
	printf("Masukkan angka sesuai dengan nomor urutan yang tertera: ");
	do{
		scanf("%d", &pilih);
		if(pilih < 0 || pilih > x){
			printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
		}
	} while(pilih < 0 || pilih > x);
	//travers ke node dari trayek yang dipilih
	for(i = 1; i != pilih; i++){
		cari = cari->next;
	}
	//mencari node data bus yang dipesan pada struct database dengan membandingkan kode bus
	temp = bus;
	while(temp != NULL){
		if(stricmp(temp->kode, cari->kode) == 0){
			break;	//node ditemukan pada database bus
		}
		temp = temp->next;
	}
	salin_data(&user, temp);		//menyalin data perjalanan
	header();
	//memasukkan informasi pemesan berupa rincian kontak
	printf("Rincian Kontak:\nDetail pesanan anda akan dikirim ke rincian kontak yang akan anda berikan\nNama: %s\n", user->nama);
	printf("Masukkan nomor HP: +62");
	scanf("%s", &telp);
	printf("Masukkan email: ");
	scanf("%s", &email);
	//memasukkan informasi untuk tiap penumpang
	for(i = 0; i < user->jumlah_tiket; i++){
		header();
		printf("Data penumpang ke-%d:\n", i + 1);
		printf("Nama penumpang: ");		//mengisi nama penumpang
		scanf("\n");
		scanf("%[^\n]s", &(user->nama_p[i]));
		printf("Usia: ");				//mengisi usia penumpang
		scanf("%d", &(user->usia[i]));
		denah_kursi();
		printf("\nNomor kursi yang tersedia: ");
		//looping untuk menampilkan nomor kursi yang tersedia
		for(j = 0; j <= user->kursi; j++){
			kursi_terisi = 0;	//variabel ini untuk menandakan apakah nomor kursi tersebut tersedia (kursi_terisi = 0) atau tidak (kursi_terisi = 1)
			for(k = 0; k < 10;  k++){
				if(j == temp->kursi_terpilih[k]){	
					kursi_terisi = 1;		//apabila nomor kursi tersebut sudah diisi maka nilai variabel menjadi 1
				}
			}
			if(kursi_terisi == 1){	//kursi yang sudah diisi / tidak tersedia maka tidak akan dicetak
				continue;
			} else{					//kursi yang tersedia akan dicetak
				printf("%d ", j);
			}
		}
		do{
			//memilih nomor kursi
			printf("\nPilih nomor kursi: ");
			scanf("%d", &(user->kursi_terpilih[i]));
			if(user->kursi_terpilih[i] < 1 || user->kursi_terpilih[i] > user->kursi){
				user->kursi_terpilih[i] = 0;	//apabila memilih nomor kursi di luar rentang kursi tersedia maka nilainya akan dirubah menjadi nilai default suatu variabel
			}
			kursi_terisi = 0;
			for(k = 0; k < 10; k++){
				if(temp->kursi_terpilih[k] == user->kursi_terpilih[i]){
					kursi_terisi = 1;	//apabila nomor kursi yang dimasukkan sudah pernah dipilih sebelumnya maka nilai variabel menjadi 1
				} 
			}
			if(kursi_terisi == 1){
				printf("Maaf kursi tidak tersedia, silahkan pilih kursi lain");
			}
		} while(kursi_terisi == 1); //akan terus looping apabila memilih kursi yang tidak tersedia
		temp->kursi_terpilih[i] = user->kursi_terpilih[i];	//data kursi yang dipilih disalin ke database
		temp->kursi--;	//kursi yang tersedia pada database akan berkurang 1 setelah selesai memilih kursi
	}
	detail:
	header();
	detail_pemesanan();	//fungsi menampilkan detail pemesanan
	user->harga = harga_tiket(temp);	//menghitung harga tiket total
	printf("Total harga: Rp%d\n\n", user->harga);
	//membayar tiket
	printf("Pilih metode pembayaran:\n1. Dompet Ailasor\n2. Transfer bank\nPilih: ");
	do{
		scanf("%d", &pilih);
		if(pilih < 1 || pilih > 2){
			printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
		}
	} while(pilih < 1 || pilih > 2);
	header();
	if(pilih == 1){
		//bayar dengan Dompet Ailasor
		printf("Saldo di dompet saat ini: Rp%d\nKami akan menarik Rp%d dari dompet anda\nApakah anda yakin?\n1. Iya\n2. Tidak\nPilih: ", user->dompet, user->harga);
		do{
			scanf("%d", &pilih);
			if(pilih < 1 || pilih > 2){
				printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
			}
		} while(pilih < 1 || pilih > 2);
		if(pilih == 1){
			if(user->dompet < user->harga){	//apabila saldo kurang dari harga tiket maka akan dikembalikan untuk memilih metode pembayaran
				printf("Saldo anda tidak mencukupi, anda akan diarahkan kembali ke detail pembayaran\nTekan tombol apapun untuk kembali");
				getch();
				goto detail;
			}
			else{
				user->dompet -= user->harga;	//apabila saldo cukup, maka saldo Dompet Ailasor dikurangi dengan harga tiket
			}
		}
		else goto detail;
	} else{
		//bayar dengan transfer bank
		printf("Transfer senilai Rp%d ke rekening berikut untuk melakukan pembayaran:\nBank Permata, No Rek: 9858534562 a.n. PT. Ailasor Bus\n\n", user->harga);
		printf("Tenggat waktu pembayaran adalah 2 jam dari sekarang\n1. Konfirmasi pembayaran\n0. Kembali\nPilih: ");
		do{
			scanf("%d", &pilih);
			if(pilih < 0 || pilih > 1){
				printf("\nError!! input salah, silahkan ulangi input\n");
			}
		} while(pilih < 0 || pilih > 1);
		if(pilih == 0) goto detail;
	}
	header();
	printf("Pembayaran anda sedang kami proses, harap tunggu sebentar");
	loading();
	header();
	printf("Pembayaran berhasil\nTekan tombol apapun untuk kembali ke menu utama");
	getch();
}

void dompet(){	//fungsi untuk mengecek Dompet Ailasor dan top up
	int pilih, topup;
	header();
	printf("Saldo Dompet Ailasor anda: Rp%d\n", user->dompet);
	printf("1. Top up Dompet Ailasor\n0. Kembali\nPilih: ");
	do{
		scanf("%d", &pilih);
		if(pilih < 0 || pilih > 1){
			printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
		}
	} while(pilih < 0 || pilih > 1);
	if(pilih == 1){
		printf("Masukkan jumlah top up: Rp");	//memasukkan nominal untuk top up
		scanf("%d", &topup);
		header();
		//pembayaran melalui rekening bank
		printf("Transfer senilai Rp%d ke rekening berikut untuk melakukan pembayaran:\nBank Permata, No Rek: 9858534562 a.n. PT. Ailasor Bus\n\n", topup);
		printf("Tenggat waktu pembayaran adalah 2 jam dari sekarang\n1. Konfirmasi pembayaran\n0. Menu utama\nPilih: ");
		do{
			scanf("%d", &pilih);
			if(pilih < 0 || pilih > 1){
				printf("\nError!! input salah, silahkan ulangi input\n");
			}
		} while(pilih < 0 || pilih > 1);
		if(pilih == 1){
			header();
			printf("Pembayaran anda sedang kami proses, harap tunggu sebentar");
			user->dompet += topup;	//nominal top up ditambahkan ke dompet
			loading();
			header();
			printf("Pembayaran berhasil\nTekan tombol apapun untuk kembali ke halaman utama");
			getch();
		}
	}
}

void salin_data(struct database **tujuan, struct database *sumber){	//fungsi untuk menyalin informasi dari sumber ke tujuan
	if(*tujuan == user){
		strcpy((*tujuan)->asal, sumber->asal);	
		strcpy((*tujuan)->tujuan, sumber->tujuan);
		strcpy((*tujuan)->kelas, sumber->kelas);
		strcpy((*tujuan)->berangkat, sumber->berangkat);
		strcpy((*tujuan)->tiba, sumber->tiba);
		strcpy((*tujuan)->kode, sumber->kode);
		(*tujuan)->kursi = sumber->kursi;
		(*tujuan)->harga = sumber->harga;
		return;
	}
	
	struct database *baru, *temp;
	baru = (struct database*)malloc(sizeof(struct database));
	
	strcpy(baru->asal, sumber->asal);	
	strcpy(baru->tujuan, sumber->tujuan);
	strcpy(baru->kelas, sumber->kelas);
	strcpy(baru->berangkat, sumber->berangkat);
	strcpy(baru->tiba, sumber->tiba);
	strcpy(baru->kode, sumber->kode);
	baru->kursi = sumber->kursi;
	baru->harga = sumber->harga;
	
	if(*tujuan == NULL){
		*tujuan = baru;
		(*tujuan)->next = NULL;
	}
	else{
		temp = *tujuan;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = baru;
		baru->next = NULL;
	}
}

void cetak_data(struct database *cari){	//fungsi untuk mencetak hasil pencarian
	struct database *temp;
	int i = 1;
	temp = cari;
	printf("%4s", "No");
	printf("%9s", "Kode");
	printf("%15s", "Kota asal");
	printf("%15s", "Kota tujuan");
	printf("%15s", "Kelas");
	printf("%15s", "Berangkat");
	printf("%15s", "Tiba");
	printf("%18s", "Kursi tersedia");
	printf("%13s\n", "Harga");
	printf("========================================================================================================================\n");
	while(temp != NULL){
		printf("%4d%9s%15s%15s%15s%15s%15s%18d%13d\n", i, temp->kode, temp->asal, temp->tujuan, temp->kelas, temp->berangkat, temp->tiba, temp->kursi, temp->harga);
		i++;
		temp = temp->next;
	}
	printf("\n");
}

void urut_tiket(struct database *cari){	//fungsi untuk melakukan sorting pada hasil pencarian
	int ditukar, pilih;
	struct database *temp, *kiritemp = NULL;
	
	header();
	printf("\nBerdasarkan\n1. Harga termurah\n2. Harga termahal\n3. Waktu keberangkatan awal\n4. Waktu keberangkatan akhir\nPilih: ");
	do{
		scanf("%d", &pilih);
		if(pilih < 1 || pilih > 4){
		printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
		}
	} while(pilih < 1 || pilih > 4);
	do{
		ditukar = 0;
		temp = cari;
		while(temp->next != kiritemp){
			if(pilih == 1){				//sorting ascending untuk data harga
				if(temp->harga > temp->next->harga){
					tukar_data(temp, temp->next);	//apabila terpenuhi maka akan diarahkan ke fungsi untuk menukar urutan data
					ditukar = 1;
				} 
			} else if(pilih == 2){		//sorting descending untuk data harga
				if(temp->harga < temp->next->harga){
					tukar_data(temp, temp->next);
					ditukar = 1;
				} 
			} else if(pilih == 3){		//sorting ascending untuk data waktu berangkat
				if(strcmp(temp->berangkat,temp->next->berangkat) > 0){
					tukar_data(temp, temp->next);
					ditukar = 1;
				} 
			} else{						//sorting descending untuk data waktu berangkat
				if(strcmp(temp->berangkat,temp->next->berangkat) < 0){
					tukar_data(temp, temp->next);
					ditukar = 1;
				} 
			}
			temp = temp->next;
		}
		kiritemp = temp;
	} while(ditukar);
}

void tukar_data(struct database *a, struct database *b){	//fungsi untuk sorting
	int tempnum;
	char tempchar[20];
	strcpy(tempchar,a->asal);	//3 baris kebawah menukar asal
	strcpy(a->asal,b->asal);	
	strcpy(b->asal,tempchar);
	strcpy(tempchar,a->tujuan);	//3 baris kebawah menukar tujuan
	strcpy(a->tujuan,b->tujuan);	
	strcpy(b->tujuan,tempchar);
	strcpy(tempchar,a->kelas);	//3 baris kebawah menukar kelas
	strcpy(a->kelas,b->kelas);	
	strcpy(b->kelas,tempchar);
	strcpy(tempchar,a->berangkat);	//3 baris kebawah menukar keberangkatan
	strcpy(a->berangkat,b->berangkat);	
	strcpy(b->berangkat,tempchar);
	strcpy(tempchar,a->tiba);	//3 baris kebawah menukar tiba
	strcpy(a->tiba,b->tiba);	
	strcpy(b->tiba,tempchar);
	strcpy(tempchar,a->kode);	//3 baris kebawah menukar kode bus
	strcpy(a->kode,b->kode);	
	strcpy(b->kode,tempchar);
	tempnum = a->kursi;	// 3 baris kebawah menukar kursi
	a->kursi = b->kursi;
	b->kursi = tempnum;
	tempnum = a->harga;	// 3 baris kebawah menukar harga
	a->harga = b->harga;
	b->harga = tempnum;
}

void filter_tiket(struct database **cari, int *x){	//fungsi untuk memfilter hasil pencarian
	struct database *temp = *cari, *terfilter = NULL;
	int pilih, filternum; 
	char filterchar[20];
	header();
	printf("\nBerdasarkan\n1. Waktu keberangkatan\n2. Waktu tiba\n3. Harga\n4. Kelas\nPilih: ");
	do{
		scanf("%d", &pilih);
		if(pilih < 1 || pilih > 4){
			printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
		}
	} while(pilih < 1 || pilih > 4);
	*x = 0;		//counter dari jumlah pencarian sebelumnya direset
	switch(pilih){
		case 1:		//filter atau searching berdasarkan waktu berangkat
			printf("Masukkan batas waktu keberangkatan: ");
			scanf("%s", &filterchar);
			printf("Cari waktu keberangkatan\n1. Sebelum pukul %s\n2. Setelah pukul %s\nPilih: ", filterchar, filterchar);
			do{
				scanf("%d", &pilih);
				if(pilih < 1 || pilih > 2){
				printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
				}
			} while(pilih < 1 || pilih > 2);
			while(temp != NULL){
				if(pilih == 1){	//searching data pada struct temp dengan waktu keberangkatan di bawah waktu yang ditentukan
					if(strcmp(filterchar,temp->berangkat) > 0){
						salin_data(&terfilter, temp);	//data yang ditemukan akan disalin kembali ke struct temp dan menimpa data sebelumnya
						*x+=1;	//counter struct temp bertambah setiap ada data yang disalin
					}
				} else {	//searching data pada struct temp dengan waktu keberangkatan di atas waktu yang ditentukan
					if(strcmp(filterchar,temp->berangkat) < 0){
						salin_data(&terfilter, temp);
						*x+=1;
					}
				}
				temp = temp->next;
			}
			break;
		case 2:	//filter atau searching berdasarkan waktu tiba
			printf("Masukkan batas waktu tiba: ");
			scanf("%s", &filterchar);
			printf("Cari waktu tiba\n1. Sebelum pukul %s\n2. Setelah pukul %s\nPilih: ", filterchar, filterchar);
			do{
				scanf("%d", &pilih);
				if(pilih < 1 || pilih > 2){
				printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
				}
			} while(pilih < 1 || pilih > 2);
			while(temp != NULL){
				if(pilih == 1){
					if(strcmp(filterchar,temp->tiba) > 0){
						salin_data(&terfilter, temp);
						*x+=1;
					}
				} else {
					if(strcmp(filterchar,temp->tiba) < 0){
						salin_data(&terfilter, temp);
						*x+=1;
					}
				}
				temp = temp->next;
			}
			break;
		case 3:	//filter atau searching berdasarkan harga
			printf("Masukkan batas harga tiket: ");
			scanf("%d", &filternum);
			printf("Cari harga tiket\n1. Di bawah Rp %d\n2. Di atas Rp %d\nPilih: ", filternum, filternum);
			do{
				scanf("%d", &pilih);
				if(pilih < 1 || pilih > 2){
				printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
				}
			} while(pilih < 1 || pilih > 2);
			while(temp != NULL){
				if(pilih == 1){
					if(filternum > temp->harga){
						salin_data(&terfilter, temp);
						*x+=1;
					}
				} else {
					if(filternum < temp->harga){
						salin_data(&terfilter, temp);
						*x+=1;
					}
				}
				temp = temp->next;
			}
			break;
		case 4:	//filter atau searching berdasarkan kelas
			printf("1. Ekonomoi\n2. Eksekutif\nPilih: ");
			do{
				scanf("%d", &pilih);
				if(pilih < 1 || pilih > 2){
				printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
				}
			} while(pilih < 1 || pilih > 2);
			while(temp != NULL){
				if(pilih == 1){
					if(strcmp("Ekonomi",temp->kelas) == 0){
						salin_data(&terfilter, temp);
						*x+=1;
					}
				} else {
					if(strcmp("Eksekutif",temp->kelas) == 0){
						salin_data(&terfilter, temp);
						*x+=1;
					}
				}
				temp = temp->next;
			}
			break;
	}
	*cari = terfilter;
}

int harga_tiket(struct database *temp){		//fungsi untuk menghitung harga tiket total
	int i, total = 0;
	float diskon;
	for(i = 0; i < user->jumlah_tiket; i++){
		//penerapan diskon
		if(user->usia[i] < 3 || user->usia[i] > 60){
			diskon = 0.8;		//usia penumpang dibawah 3 tahun atau di atas 60 tahun mendapat diskon 20%
		} else{
			diskon = 1;
		}
		total += temp->harga * diskon;
	}
	return total;
}

void detail_pemesanan(){	//fungsi untuk menampilkan detail pemesanan tiket
	int i;
	printf("Detail Pemesanan\n\n");
	printf("Nama pemesan: %s\n", user->nama);
	printf("Tanggal berangkat: %s\n", user->tanggal);
	printf("Kota asal: %s\n", user->asal);
	printf("Kota tujuan: %s\n", user->tujuan);
	printf("Waktu berangkat: %s\n", user->berangkat);
	printf("Waktu tiba: %s\n", user->tiba);
	printf("Kelas bus: %s\n\n", user->kelas);
	for(i = 0; i < user->jumlah_tiket; i++){
		printf("Data penumpang ke-%d:\n", i + 1);
		printf("Nama penumpang: %s\n", user->nama_p[i]);
		printf("Usia: %d tahun\n", user->usia[i]);
		printf("Nomor kursi: %d\n\n", user->kursi_terpilih[i]);
	}
}

void lihat_detail(){	//fungsi untuk melihat tiket yang sudah dipesan
	header();
	if(user->harga == 0){	//apabila belum terdapat nilai pada struct , maka akan kembali ke menu utama
		printf("Anda belum memesan tiket, pilih opsi nomor 1 untuk memesan tiket\nTekan tombol apapun untuk kembali ke menu utama");
		getch();
	} else{
		detail_pemesanan();	//menampilkan data yang sudah dipesan
		printf("Tekan tombol apapun untuk kembali ke menu utama");
		getch();
	}
}

void ubah_jadwal(){	//fungsi untuk mengubah jadwal dari tiket yang sudah dipesan
	int pilih, i, biaya_ubah_jadwal = 30000, x = 0, tanggaltemp, bulantemp, tahuntemp;
    struct database *temp;
	struct database *cari = NULL;	//struct untuk menyimpan hasil pencarian tiket
	header();
	if(user->harga == 0){	//apabila belum terdapat nilai pada struct , maka akan kembali ke menu utama
		printf("Anda belum memesan tiket, pilih opsi nomor 1 untuk memesan tiket\nTekan tombol apapun untuk kembali ke menu utama");
		getch();
	} else{
		printf("Ketentuan ubah jadwal:\n");
		printf("- Perubahan jadwal akan dikenakan biaya Rp%d\n", biaya_ubah_jadwal);
		printf("- Anda tidak dapat mengubah kelas bus\n");
		printf("- Anda tidak dapat memilih kursi\n");
		printf("\nApakah ada ingin melanjutkan?\n1. Lanjut\n0. Kembali\nPilih: ");
		do{
			scanf("%d", &pilih);
			if(pilih < 0 || pilih > 1){
				printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
			}
		} while(pilih < 0 || pilih > 1);
		if(pilih == 1){
			header();
			printf("Masukkan tanggal keberangkatan baru\nTanggal: ");
			scanf("%d", &tanggaltemp);
            printf("Bulan: ");
			scanf("%d", &bulantemp);
            printf("Tahun: ");
			scanf("%d", &tahuntemp);
            sprintf(user->tanggal, "%d/%d/%d", tanggaltemp, bulantemp, tahuntemp);
			printf("Mencari bus pada tanggal %s, Harap tunggu sebentar", user->tanggal);
			loading();
			//searching pada database
            temp = bus;
            while(temp != NULL){
                if(cmpstr(temp->asal, user->asal) == 0 && cmpstr(temp->tujuan, user->tujuan) == 0 && temp->kursi >= user->jumlah_tiket && cmpstr(temp->kelas, user->kelas) == 0){
					salin_data(&cari, temp);
					x++;
				}
                temp = temp->next;
            }
			header();
			printf("\n%d bus ditemukan\n\n", x);
			cetak_data(cari);	//menampilkan data hasil searching
			printf("1. Pilih tiket\n0. Menu utama\nPilih: ");
			do{
				scanf("%d", &pilih);
				if(pilih < 0 || pilih > 1){
					printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
				}
			} while(pilih < 0 || pilih > 1);
			if(pilih == 1){	//input 1 untuk memilih tiket
				printf("Pilih tiket baru\nMasukkan angka sesuai dengan nomor urutan yang tertera: ");
				do{
					scanf("%d", &pilih);
					if(pilih < 0 || pilih > x){
						printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
					}
				} while(pilih < 0 || pilih > x);
                //travers ke node dari trayek yang dipilih
                for(i = 1; i != pilih; i++){
                    cari = cari->next;
                }
				//mencari node data bus yang dipesan pada struct database dengan membandingkan kode bus
                temp = bus;
                while(temp != NULL){
                    if(stricmp(temp->kode, cari->kode) == 0){
                        break;	//node ditemukan pada database bus
                    }
                    temp = temp->next;
                }
				salin_data(&user, temp);	//menyalin data dari database ke struct user untuk memperbaharui jadwal
				user->harga = harga_tiket(temp);
				//menentukan nomor kursi baru untuk tiap penumpang
				for(i = 0; i < user->jumlah_tiket; i++){
					user->kursi_terpilih[i] = i + 1;
					temp->kursi_terpilih[i] = user->kursi_terpilih[i];
					temp->kursi--;
				}
				header();
				detail_pemesanan(); //menampilkan detail pemesanan
				//membayar tiket dari Dompet Ailasor
				printf("Biaya sebesar Rp%d akan ditarik dari Dompet Ailasor\n1. Lanjut\n0. Menu utama\nPilih: ", biaya_ubah_jadwal);
				do{
					scanf("%d", &pilih);
					if(pilih < 0 || pilih > 1){
						printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
					}
				} while(pilih < 0 || pilih > 1);
				if(pilih == 1){
					if(user->dompet < biaya_ubah_jadwal){
						printf("Saldo anda tidak mencukupi, top up Dompet Ailasor untuk melanjutkan pembayaran\nTekan tombol apapun untuk kembali ke menu utama");
						getch();
					}
					else{
						header();
						printf("Pembayaran anda sedang kami proses, harap tunggu sebentar");
						loading();
						reset_kursi();	//menghapus nomor kursi yang telah dipilih sebelumnya dan mereset jumlah kursi pada database
						user->dompet -= biaya_ubah_jadwal;
						header();
						printf("Pembayaran berhasil\nTekan tombol apapun untuk kembali ke menu utama");
						getch();
					}
				}
			}
		}
	}
}

void batal(){	//fungsi untuk membatalkan tiket yang telah dipesan
	int pilih, refund;
	header();
	if(user->harga == 0){	//apabila belum terdapat nilai pada struct , maka akan kembali ke menu utama
		printf("Anda belum memesan tiket, pilih opsi nomor 1 untuk memesan tiket\nTekan tombol apapun untuk kembali ke menu utama");
		getch();
	} else{
		printf("Apakah anda yakin ingin melanjutkan untuk membatalkan tiket?\nBiaya tiket akan direfund ke Dompet Ailasor sejumlah 80%c dari biaya tiket\n1. Lanjut\n0. Kembali\nPilih: ", '%');
		do{
			scanf("%d", &pilih);
			if(pilih < 0 || pilih > 1){
				printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
			}
		} while(pilih < 0 || pilih > 1);
		header();
		if(pilih == 1){
			printf("Harap tunggu sebentar, pembatalan tiket sedang diproses");
			loading();
			refund = 0.8 * user->harga;	//menentukan nominal refund
			user->dompet += refund;		//refund ditambahkan ke Dompet Ailasor
			reset_kursi();		//menghapus nomor kursi yang telah dipilih sebelumnya dan mereset jumlah kursi pada database
			hapus_booking();	//menghapus struct booking untuk perjalanan sebelumnya
			header();
			printf("Tiket berhasil dibatalkan, saldo sebesar Rp%d telah dikembalikan ke dompet anda\nTekan tombol apapun untuk kembali ke menu utama", refund);
			getch();
		}	
	}	
}

void reset_kursi(){		//fungsi untuk mereset jumlah kursi pada database ke jumlah awal
	int j;
	struct database *temp;
	temp = bus;
	while(temp != NULL){
		if(strcmp(user->kode, temp->kode) == 0){	//mencari indeks database yang sesuai dengan tiket yang dipesan dengan membandingkan kode bus
			for(j = 0; j < user->jumlah_tiket; j++){
				temp->kursi_terpilih[j] = 0;	//menghilangkan nomor kursi yang telah dipilih pada database
				temp->kursi++;					//jumlah kursi bertambah 1 setelah 1 nomor kursi dihilangkan 
			}
		}
		temp = temp->next;
	}
}

void hapus_booking(){	//menghapus data pada struct booking
	strcpy(user->asal, " ");
	strcpy(user->tujuan, " ");
	strcpy(user->kelas, " ");
	strcpy(user->berangkat, " ");
	strcpy(user->tiba, " ");
	strcpy(user->kode, " ");
	user->kursi = 0;
	user->harga = 0;
}

void panduan(){		//fungsi untuk menampilkan panduan penggunaan program
	header();
	printf("Panduan Pengguna\n");
	printf("- Pilih 1 untuk melihat jadwal bus dan memesan tiket\n");
	printf("- Pilih 2 untuk melihat detail tiket yang telah dipesan\n");
	printf("- Pilih 3 untuk mengubah jadwal perjalanan\n");
	printf("- Pilih 4 untuk membatalkan tiket yang telah dipesan\n");
	printf("- Pilih 5 untuk mengecek dan top up untuk Dompet Aliasor\n");
	printf("- Pilih 0 untuk keluar dari akun\n");
	printf("\nTekan tombol apapun untuk kembali ke menu utama");
	getch();
}

void denah_kursi(){		//fungsi untuk menampilkan denah kursi
	printf("Denah kursi:\n");
	printf("  %15s%8s%8s%8s%15s%8s\n","4","8","12","16","20","24");
	printf(" d%9s%6s%8s%8s%8s%15s%8s\n","supir","3","7","11","15","19","23");
	printf(" e\n");
	printf(" p\n");
	printf(" a\n");
	printf(" n%15s%8s%8s%8s%15s%8s\n","2","6","10","14","18","22");
	printf("  %9s%6s%8s%8s%8s%9s%6s%8s\n","pintu","1","5","9","13","pintu","17","21");
}

void loading(){		//fungsi untuk membuat animasi loading pada program
	int i, j = 0;
	printf("\n");
	do{
		for(i = 0; i < 4; i++){
		printf(".");	//mencetak simbol titik sebanyak 4 kali dengan delay tiap print 500 ms
		Sleep(500);
	}
	printf("\r                           \r");	//menghapus simbol titik yang telah dicetak dan mengembalikan kursor ke awal
	j++;
	} while(j < 3);		//fungsi akan diulang sebanyak 3 kali
}

int cmpstr(const char* str, const char* substr){	//fungsi untuk membandingkan keyword pencarian dengan database
    int i = 0, j = 0;
	char str1;
	char str2;
	char substr1;
	char substr2;
	
    while (((str[j] != '\0') && (substr[i] != '\0'))) {
  		str1 = str[j] + 32;
		str2 = str[j] - 32;
		substr1 = substr[i] + 32;
		substr2 = substr[i] - 32;
        if ( (str[j] != substr[i]) && (str2 != substr[i]) && (str1 != substr[i]) && (str[j] != substr1) && (str[j] != substr2) ) {
            j++;
            i = 0;
        }
        else {
            i++;
            j++;
        }
    }
    if (substr[i] == 0)
        return 0;
    else
        return -1;
}

void tambah_database(){		//fungsi untuk menambah database bus
	header();
	char tempasal[20], temptujuan[20], tempkelas[20], tempberangkat[20], temptiba[20];
	int tempkursi, tempharga;
	printf("Input asal: ");
	scanf("%s", &tempasal);
	printf("Input tujuan: ");
	scanf("%s", &temptujuan);
	do{
		printf("Input kelas: ");
		scanf("%s", &tempkelas);
		if(stricmp(tempkelas, "Ekonomi") == 0)	strcpy(tempkelas, "Ekonomi");
		else if(stricmp(tempkelas, "Eksekutif") == 0)	strcpy(tempkelas, "Eksekutif");
	} while(strcmp(tempkelas, "Ekonomi") != 0 && strcmp(tempkelas, "Eksekutif") != 0);
	printf("Input waktu berangkat: ");
	scanf("%s", &tempberangkat);
	printf("Input waktu tiba: ");
	scanf("%s", &temptiba);
	printf("Input jumlah kursi: ");
	scanf("%d", &tempkursi);
	printf("Input harga tiket: ");
	scanf("%d", &tempharga);
	insert_bus(tempasal, temptujuan, tempkelas, tempberangkat,  temptiba, tempkursi, tempharga);
	printf("Data berhasil ditambahkan\n\nTekan tombol apapun untuk kembali");
	getch();
}

void cari_database(){		//fungsi untuk mencari database bus
	int pilih;
	char tempasal[20], temptujuan[20], tempkode[10];
	struct database *cari, *temp;
	header();
	cari = NULL;
	temp = bus;
	header();
	printf("\nCari berdasarkan:\n1. Asal\n2. Tujuan\n3. Kode bus\n\nPilih: ");
	do{
		scanf("%d", &pilih);
		if(pilih < 1 || pilih > 3){
			printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
		}
	} while(pilih < 1 || pilih > 3);
	if(pilih == 1){		
		printf("Input asal: ");
		scanf("%s", &tempasal);
		while(temp != NULL){
	    	if(cmpstr(temp->asal, tempasal) == 0){
				salin_data(&cari, temp);
			}
			temp = temp->next;
		}
	} else if(pilih == 2){
		printf("Input tujuan: ");
		scanf("%s", &temptujuan);
		while(temp != NULL){
	    	if(cmpstr(temp->tujuan, temptujuan) == 0){
				salin_data(&cari, temp);
			}
			temp = temp->next;
		}
	} else if(pilih == 3){
		printf("Input kode bus: ");
		scanf("%s", &tempkode);
		while(temp != NULL){
	    	if(stricmp(temp->kode, tempkode) == 0){
				salin_data(&cari, temp);
			}
			temp = temp->next;
		}
	}
	header();
	if(cari == NULL)	printf("Data tidak ditemukan\n");
	else	cetak_data(cari);
	printf("Tekan tombol apapun untuk kembali");
	getch();
}

void cetak_database(){
	struct database *temp = bus;
	header();
	cetak_data(temp);
	printf("Tekan tombol apapun untuk kembali");
	getch();
}

void ubah_database(){		//fungsi untuk mengubah database bus yang sudah ada
	char tempasal[20], temptujuan[20], tempkelas[20], tempberangkat[20], temptiba[20];
	int tempkursi, tempharga;
	char tempkode[10];
	struct database *temp = bus;
	
	header();
	printf("Input kode trayek bus yang ingin diubah: ");
	scanf("%s", &tempkode);
	while(temp != NULL){
		if(stricmp(temp->kode, tempkode) == 0){
			break;
		}
		temp = temp->next;
	}
	
	header();
	if(temp == NULL){
		printf("Data tidak ditemukan");
	} else{
		printf("Data trayek ditemukan:\n");
		cetak(temp);
		printf("\nInput asal baru (input '-' jika tidak ingin merubah data)\n: ");
		scanf("%s", &tempasal);
		printf("Input tujuan (input '-' jika tidak ingin merubah data)\n: ");
		scanf("%s", &temptujuan);
		printf("Input kelas (input '-' jika tidak ingin merubah data)\n: ");
		scanf("%s", &tempkelas);
		printf("Input waktu berangkat (input '-' jika tidak ingin merubah data)\n: ");
		scanf("%s", &tempberangkat);
		printf("Input waktu tiba (input '-' jika tidak ingin merubah data)\n: ");
		scanf("%s", &temptiba);
		printf("Input jumlah kursi (input -1 jika tidak ingin merubah data)\n: ");
		scanf("%d", &tempkursi);
		printf("Input harga tiket (input -1 jika tidak ingin merubah data)\n: ");
		scanf("%d", &tempharga);
		
		strcpy(temp->kode, "");
		if(strcmp(tempasal,"-") != 0)	strcpy(temp->asal, tempasal);
		if(strcmp(temptujuan,"-") != 0)	strcpy(temp->tujuan, temptujuan);
		if(strcmp(tempkelas,"-") != 0)	strcpy(temp->kelas, tempkelas);
		if(strcmp(tempberangkat,"-") != 0)	strcpy(temp->berangkat, tempberangkat);
		if(strcmp(temptiba,"-") != 0)	strcpy(temp->tiba, temptiba);
		if(tempkursi != -1)	temp->kursi = tempkursi;
		if(tempharga != -1)	temp->harga = tempharga;
		
		printf("\nData trayek baru:\n");
		cetak(temp);
	}
	printf("\nTekan tombol apapun untuk kembali");
	getch();
}

void hapus_database(){		//fungsi untuk menghapus database bus yang sudah ada
	char tempkode[10];
	int pilih;
	struct database *temp = bus, *sebelum = bus;
	
	header();
	printf("Input kode trayek bus yang ingin dihapus: ");
	scanf("%s", &tempkode);
	while(temp != NULL){
		if(stricmp(temp->kode, tempkode) == 0){
			break;
		}
		sebelum = temp;
		temp = temp->next;
	}
	
	header();
	if(temp == NULL){
		printf("Data tidak ditemukan");
	} else{
		printf("Data trayek ditemukan:\n");
		cetak(temp);
		printf("\nApakah yakin ingin menghapus data ini?\n1. Iya\n0. Tidak\nPilih: ");
		do{
			scanf("%d", &pilih);
			if(pilih < 0 || pilih > 1){
				printf("\nError!! input salah, silahkan ulangi input\nPilih: ");
			}
		} while(pilih < 0 || pilih > 1);
		if(pilih == 0)	return;
		
		if(temp == bus)
	        bus =  bus->next;
	    sebelum->next = temp->next;
	    temp->next = NULL;
	    free(temp);
		printf("\nData trayek bus berhasil dihapus\n");
	}
	
	printf("\nTekan tombol apapun untuk kembali");
	getch();
}

void cetak(struct database *temp){
	printf("\n%3s", "No");
	printf("%9s", "Kode");
	printf("%15s", "Kota asal");
	printf("%15s", "Kota tujuan");
	printf("%15s", "Kelas");
	printf("%15s", "Berangkat");
	printf("%15s", "Tiba");
	printf("%20s", "Kursi tersedia");
	printf("%13s\n", "Harga");
	printf("========================================================================================================================\n");
	printf("%3d%9s%15s%15s%15s%15s%15s%20d%13d\n", 1, temp->kode, temp->asal, temp->tujuan, temp->kelas, temp->berangkat, temp->tiba, temp->kursi, temp->harga);
}
