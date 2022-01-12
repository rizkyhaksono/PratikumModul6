#include <stdio.h> // file header untuk standar input dan output
#include <stdlib.h> // header file untuk standard library
#include <string.h> // strcmp(); strupr();
#include <conio.h> // getch();
#include <ctype.h> // tolower()

typedef struct mahasiswa{ //typedef berguna untuk membuat alias dari suatu tipe data
    char nimCek[30];
    char nim[30];
    char namaDepan[30];
    char namaBelakang[30];
    char kelas[30];
    char dosen[30];
}mahasiswa;

int dup, d, s, found, b = 0;
int data;
char ch[30];

void create(){
    mahasiswa *m; // pointer baru dari struct mahasiswa
    FILE *fp, *read; // file pointer, untuk mengcompile fungsi input dan output di file

    int n, i;
    int no = 0;

    printf("\nBerapa Data yang Ingin Ditambahkan : ");
    scanf("%d", &n);

    // menggembalikkan pointer *m ke sebuah array yg terdiri dari n dan sizeof
    m = (mahasiswa*)calloc(n, sizeof(mahasiswa));

    // membuat data dalam file
    fp = fopen("mahasiswa2.txt", "w");
    read = fopen("mahasiswa2.txt", "r");

    for(i = 0; i < n; i++){
        printf("\n\t=== [#] Input User %d ===\n", ++no); // nomor user

        nimUlang:
        fflush(stdin);
        printf("\n[-] Input NIM Praktikan \t: ");
        scanf("%[^\n]s", m[i].nimCek);
        dup = 0;

        // membaca sekumpulan data dari file
        // tanda yang menyatakan telah sampai pada record terakhir dari sebuah file.
        while(fscanf(read, "%[^#]#%[^#]#%[^#]#%[^\n]\n", m[i].nim, m[i].namaDepan, m[i].namaBelakang, m[i].kelas, m[i].dosen) !=  EOF){

            // di cek NIM yg ada di file dan NIM yg di inputkan
            if(strcmp(m[i].nim, m[i].nimCek) == 0){

                // jika iya, maka mengembalikan input dup = 1;
                dup = 1;
            }
        }

        // untuk ngecek nilai ASCII
        // di cek apakah NIM ada spesial karakter
        for(int index = 0; m[i].nimCek[index] != '\0'; index++) { // \0 =  diatur agar semua bit menjadi tidak nol
            // tanda !"#$%&'()*+`-'/
            if(m[i].nim[index] >= 0x21 && m[i].nimCek[index] <= 0x2F){
                printf("\nNIM Tidak Boleh Ada Kata Spesial\n");

                getch();
                goto nimUlang;
                break;
            // tanda :;<=>?@
            }else if(m[i].nimCek[index] >= 0x3A && m[i].nimCek[index] <= 0x40){
                printf("\nNIM Tidak Boleh Ada Kata Spesial\n");

                getch();
                goto nimUlang;
                break;
            }
        }

        // maka, NIM sudah ada
        if(dup == 1){
            fclose(fp);
            fclose(read);
            printf("\nNIM Yang Anda Inputkan Telah Tersedia\n");
            printf("\nDimohon Inputkan Ulang NIM\n");
            getch();
            goto nimUlang;
            break;
        }
        // jika tidak, lanjut membuat data
        if(dup == 0){
            // di copy NIM yg di "nimCek" menjadi "nim" biasa
            strcpy(m[i].nim,  m[i].nimCek);
            printf("[-] Masukkan Nama Depan \t: ");
            // untuk membersihkan output buffer dan memindahkan menuju sebuah tipe data
            fflush(stdin);
            scanf("%s", m[i].namaDepan);

            printf("[-] Masukkan Nama Belakang \t: ");
            fflush(stdin);
            scanf("%s", m[i].namaBelakang);
            // untuk menggabungkan 2 string
            strcat(m[i].namaDepan, m[i].namaBelakang);

            printf("[-] Nama Lengkap Anda\t\t: %s\n", m[i].namaDepan);
            printf("[-] Masukkan Kelas Pemrograman \t: ");
            // untuk membersihkan output buffer dan memindahkan menuju sebuah tipe data
            fflush(stdin);
            // untuk mengambil input dalam satu baris dan tdk memerlukan scanf
            gets(m[i].kelas);

            printf("[-] Masukkan Nama Dosen\t\t: ");
            // untuk membersihkan output buffer dan memindahkan menuju sebuah tipe data
            fflush(stdin);
            // untuk mengambil input dalam satu baris dan tdk memerlukan scanf
            gets(m[i].dosen);
        }

        // menulis sekumpulan data pada file
        fprintf(fp, "%s#" , m[i].nim);
        fprintf(fp, "%s#" , m[i].namaDepan);
        fprintf(fp, "%s#" , strupr(m[i].kelas)); // UpperCase
        fprintf(fp, "%s\n" , m[i].dosen);
    }
        // menutup sebuah file
        fclose(fp);
        fclose(read);

        printf("\nData Berhasil Ditambahkan\n");

}

void display(){
    mahasiswa m1; // alias dari typedef
    FILE *read; // file pointer

    read = fopen("mahasiswa2.txt", "r");
    data = 0;
    found = 0;

    // membaca sekumpulan data dari file
    // tanda yang menyatakan telah sampai pada record terakhir dari sebuah file.
    while(fscanf(read,"%[^#]#%[^#]#%[^#]#%[^\n]\n", m1.nim, m1.namaDepan , m1.kelas, m1.dosen) != EOF){
        data++;
        // jika ketemu, maka menampilkan data user
        found = 1;
        printf("\n\t=== [#] Daftar User %d ===\n\n", data);
        printf("[-] NIM Praktikan \t: %s\n", m1.nim);
        printf("[-] Nama Praktikan \t: %s\n", m1.namaDepan);
        printf("[-] Kelas Praktikan\t: %s\n", m1.kelas);
        printf("[-] Dosen Praktikan\t: %s\n", m1.dosen);
    }

    // jika tidak ada found, maka tidak ada data di file
    if(!found){
        printf("\nData Tidak Ada, Silahkan Membuat Data Terlebih Dahulu!\n");
    }

    // menutup sebuah file
    fclose(read);
}

void append(){
    mahasiswa *m; // pointer baru dari struct mahasiswa
    FILE *fp, *read;

    int n, i;
    int no = 0;

    printf("\nBerapa Data yang Ingin Ditambahkan : ");
    scanf("%d", &n);

    // menggembalikkan pointer *m ke sebuah array yg terdiri dari n dan sizeof
    m = (mahasiswa*)calloc(n, sizeof(mahasiswa));

    // menambahkan data dalam file
    fp = fopen("mahasiswa2.txt", "a");
    read = fopen("mahasiswa2.txt", "r");

    for(i = 0; i < n; i++){
        printf("\n\t=== [#] Input User %d ===\n", ++no); // nomor user

        nimUlang1:
        fflush(stdin);
        printf("\n[-] Input NIM Praktikan \t: ");
        scanf("%[^\n]s", m[i].nimCek);
        dup = 0;

        // membaca sekumpulan data dari file
        // tanda yang menyatakan telah sampai pada record terakhir dari sebuah file.
        while(fscanf(read, "%[^#]#%[^#]#%[^#]#%[^\n]\n", m[i].nim, m[i].namaDepan, m[i].namaBelakang, m[i].kelas, m[i].dosen) !=  EOF){
            // di cek NIM yg ada di file dan NIM yg di inputkan
            if(strcmp(m[i].nim, m[i].nimCek) == 0){
                // jika iya, maka mengembalikan input dup = 1;
                dup = 1;
            }
        }

        // untuk ngecek nilai ASCII
        // di cek apakah NIM ada spesial karakter
        for(int index = 0; m[i].nimCek[index]!='\0'; index++) {
            // tanda !"#$%&'()*+`-'/
            if(m[i].nim[index] >= 0x21 && m[i].nimCek[index] <= 0x2F){
                printf("\nNIM Tidak Boleh Ada Kata Spesial\n");

                getch();
                goto nimUlang1;
                break;
            // tanda :;<=>?@
            }else if(m[i].nimCek[index] >= 0x3A && m[i].nimCek[index] <= 0x40){
                printf("\nNIM Tidak Boleh Ada Kata Spesial\n");

                getch();
                goto nimUlang1;
                break;
            }
        }

        // maka, NIM sudah ada
        if(dup == 1){
            fclose(fp);
            fclose(read);
            printf("\nNIM Yang Anda Inputkan Telah Tersedia\n");
            printf("\nDimohon Inputkan Ulang NIM\n");
            getch();
            goto nimUlang1;
            break;
        }
        // jika tidak, lanjut membuat data
        if(dup == 0){
            // di copy NIM yg di "nimCek" menjadi "nim" biasa
            strcpy(m[i].nim,  m[i].nimCek);
            printf("[-] Masukkan Nama Depan \t: ");
            // untuk membersihkan output buffer dan memindahkan menuju sebuah tipe data
            fflush(stdin);
            scanf("%s", m[i].namaDepan);

            printf("[-] Masukkan Nama Belakang \t: ");
            // untuk membersihkan output buffer dan memindahkan menuju sebuah tipe data
            fflush(stdin);
            scanf("%s", m[i].namaBelakang);
            // untuk menggabungkan 2 string
            strcat(m[i].namaDepan, m[i].namaBelakang);

            printf("[-] Nama Lengkap Anda\t\t: %s\n", m[i].namaDepan);
            printf("[-] Masukkan Kelas Pemrograman\t: ");
            // untuk membersihkan output buffer dan memindahkan menuju sebuah tipe data
            fflush(stdin);
            // untuk mengambil input dalam satu baris dan tdk memerlukan scanf
            gets(m[i].kelas);

            printf("[-] Masukkan Nama Dosen\t\t: ");
            fflush(stdin);
            // untuk mengambil input dalam satu baris dan tdk memerlukan scanf
            gets(m[i].dosen);
        }

        // menulis sekumpulan data pada file
        fprintf(fp, "%s#" , m[i].nim);
        fprintf(fp, "%s#" , m[i].namaDepan);
        fprintf(fp, "%s#" , strupr(m[i].kelas));
        fprintf(fp, "%s\n" , m[i].dosen);
    }
        // menutup file
        fclose(fp);
        fclose(read);
        printf("\nData Berhasil Ditambahkan\n");

}

void search(){
    mahasiswa m1; // alias dari typedef
    FILE *read; // pointer dari file
    read = fopen("mahasiswa2.txt", "r");

    printf("\nMasukkan NIM yang Ingin Dicari : ");
    scanf("%s", &ch);

    found = 0; // untuk cek data apakah masuk atau tidak

    // membaca sekumpulan data dari file
    // tanda yang menyatakan telah sampai pada record terakhir dari sebuah file.
    while(fscanf(read, "%[^#]#%[^#]#%[^#]#%[^\n]\n", m1.nim, m1.namaDepan , m1.kelas,m1. dosen) != EOF){
        // membandingkan NIM di file dan NIM input an
        if(strcmp(m1.nim, ch) == 0){
            found = 1;

            printf("\n[-] NIM Lengkap \t: %s\n", m1.nim);
            printf("[-] Nama Lengkap \t: %s\n", m1.namaDepan);
            printf("[-] Kelas Pemrograman \t: %s\n", m1.kelas);
            printf("[-] Dosen Pengampu \t: %s\n", m1.dosen);
        }

        // jika tidak ada NIM, maka tampilkan ini
        if(!found){
            printf("\nData Tidak Ada, Silahkan Membuat Data Terlebih Dahulu!\n");
        }
    }
    fclose(read);
}

void update(){
    mahasiswa m1; // alias dari typedef
    FILE *read, *update; // pointer dari file

    update = fopen("updateMhs.txt", "w");
    read = fopen("mahasiswa2.txt", "r");

    printf("\nMasukkan NIM yang Ingin Diupdate : ");
    scanf(" %s", &ch);
    found = 0;

    // membaca sekumpulan data dari file
    while(fscanf(read, "%[^#]#%[^#]#%[^#]#%[^\n]\n", m1.nim, m1.namaDepan , m1.kelas,m1. dosen) != EOF){ // end of file
        // membandingkan NIM file dengan NIM inputan
        if(strcmp(m1.nim, ch) == 0){
            found = 1;
            printf("\n[-] NIM Lengkap \t: %s\n", m1.nim);
            printf("[-] Nama Lengkap \t: %s\n", m1.namaDepan);
            printf("[-] Kelas Pemrograman \t: %s\n", m1.kelas);
            printf("[-] Dosen Pengampu \t: %s\n", m1.dosen);

            // untuk membersihkan output buffer dan memindahkan menuju sebuah tipe data
            fflush(stdin);
            printf("\n=== [#] Input User Baru ===\n\n");
            printf("[-] NIM Praktikum Baru\t\t\t: ");
            scanf("%s", m1.nim);

            // untuk membersihkan output buffer dan memindahkan menuju sebuah tipe data
            fflush(stdin);
            printf("[-] Nama Depan Baru\t\t\t: ");
            scanf(" %s", m1.namaDepan);

            // untuk membersihkan output buffer dan memindahkan menuju sebuah tipe data
            fflush(stdin);
            printf("[-] Nama Belakang Baru\t\t\t: ");
            scanf(" %s", m1.namaBelakang);

            printf("[-] Kelas Pemrograman Dasar Baru\t: ");
            // untuk membersihkan output buffer dan memindahkan menuju sebuah tipe data
            fflush(stdin);
            // untuk mengambil input dalam satu baris dan tdk memerlukan scanf
            gets(m1.kelas);

            printf("[-] Nama Dosen Pengampu Baru\t\t: ");
            // untuk membersihkan output buffer dan memindahkan menuju sebuah tipe data
            fflush(stdin);
            // untuk mengambil input dalam satu baris dan tdk memerlukan scanf
            gets(m1.dosen);

            // menggabungkan 2 string
            strcat(m1.namaDepan, m1.namaBelakang);

            // menulis sekumpulan data pada file
            fprintf(update, "%s#", m1.nim);
            fprintf(update, "%s#", m1.namaDepan);
            fprintf(update, "%s#", strupr(m1.kelas));
            fprintf(update, "%s\n", m1.dosen);

            printf("\nData Sudah Diupdate\n\n");
        }else{

            // menulis sekumpulan data pada file
            fprintf(update, "%s#", m1.nim);
            fprintf(update, "%s#", m1.namaDepan);
            fprintf(update, "%s#", strupr(m1.kelas));
            fprintf(update, "%s\n", m1.dosen);
        }

        if(!found){
            printf("\nData Tidak Ada, Silahkan Membuat Data Terlebih Dahulu!\n");
            break;
        }
    }

    fclose(update);
    fclose(read);

    // harus close file dulu baru remove dan rename

    // menghapus file mahasiswa2
    remove("mahasiswa2.txt");

    // mengganti nama file updateMhs ke mahasiswa2
    rename("updateMhs.txt", "mahasiswa2.txt");
}

void delete_rec(){
    mahasiswa m1; // alias dari typedef
    FILE *read, *update; // pointer untuk file

    read = fopen("mahasiswa2.txt", "r");
    update = fopen("updateMhs.txt", "w");

    printf("\nMasukkan NIM yang Ingin Dihapus : ");
    scanf("%s", ch);

    d = 0;

    // membaca sekumpulan data dari file
    // tanda yang menyatakan telah sampai pada record terakhir dari sebuah file.
    while(fscanf(read, "%[^#]#%[^#]#%[^#]#%[^\n]\n", m1.nim, m1.namaDepan, m1.kelas, m1.dosen) != EOF){
        // membandingkan NIM file dengan NIM input
        if(strcmp(m1.nim, ch) !=0 ){

            // menulis sekumpulan data pada file
            fprintf(update, "%s#", m1.nim);
            fprintf(update, "%s#", m1.namaDepan);
            fprintf(update, "%s#", m1.kelas);
            fprintf(update, "%s\n", m1.dosen);
        }else if(strcmp(m1.nim, ch) != 1){
            d++;
            printf("\nData Berhasil Dihapus!\n");
            getch();
        }
    }

    // jika data tidak ada, maka tampilkan
    if(d == 0){
        printf("\nData Yang Ingin Dihapus Tidak ada\n");
    }

    fclose(read);
    fclose(update);

    // harus close file dulu baru remove dan rename

    // menghapus file mahasiswa2
    remove("mahasiswa2.txt");

    // mengganti nama file updateMhs ke mahasiswa2
    rename("updateMhs.txt", "mahasiswa2.txt");
}

int main(){
    int ch;

    up:
    printf("[+] Tugas Modul 6\n");
    printf("\n|| ============================================ ||\n");
    printf("|| \t\t\t\t\t\t||");
    printf("\n||\t Nama \t: Muhammad Rizky Haksono \t||\n");
    printf("||\t NIM  \t: 202110370311325 \t \t||\n");
    printf("||\t Kelas \t: G \t\t\t \t||\n");
    printf("|| \t\t\t\t\t\t||");
    printf("\n|| ============================================ ||\n");

    printf("\n|| ============================================ ||\n");
    printf("|| \t\t\t\t\t\t||\n");
    printf("||\t\t[-] 1. Create \t\t\t||\n");
    printf("||\t\t[-] 2. Show \t\t\t||\n");
    printf("||\t\t[-] 3. Append \t\t\t||\n");
    printf("||\t\t[-] 4. Search \t\t\t||\n");
    printf("||\t\t[-] 5. Update \t\t\t||\n");
    printf("||\t\t[-] 6. Delete \t\t\t||\n");
    printf("||\t\t[-] 0. Exit \t\t\t||\n");
    printf("|| \t\t\t\t\t\t||");
    printf("\n|| ============================================ ||\n");

    again:
    printf("\n\n[+] Pilihan Menu : ");
    scanf("%d", &ch);

    switch(ch){
        case 1:
            create();
            break;
        case 2:
            display();
            break;
        case 3:
            append();
            break;
        case 4:
            search();
            break;
        case 5:
            update();
            break;
        case 6:
            delete_rec();
            break;
        case 0:
            done:

            printf("\n|| ====================================================== ||\n");
            printf("|| \t\t\t\t\t\t\t  ");
            printf("|| \n");
            printf("||  [-] Terima Kasih Telah Menggunakan Pemrograman CRUD!  ||\n");
            printf("|| \t\t\t\t\t\t\t  ");
            printf("|| \n");
            printf("|| ====================================================== ||\n");

            exit(0);
            break;
        default:
            printf("\nInput Anda Salah!");
            goto again;
            break;
    }

    char konfirmasi;
    key:
    printf("\n[+] Apakah Ingin Melanjutkan Program? [y/n] : ");
    scanf("%s", &konfirmasi);

    switch(tolower(konfirmasi)){
    case 'y':
        system("cls");
        goto up;
        break;
    case 'n':
        system("cls");
        goto done;
        break;
    default:
        printf("\nInputan Anda Salah!\n");
        goto key;
        break;
    }
    return 0;
}
