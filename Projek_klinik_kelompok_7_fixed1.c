#include <stdio.h>
#include <string.h>

struct projek_klinik {
    char nama_pasien[50];
    char jenis_kelamin;
    int usia;
    char penyakit[50];
    char tanggal[50];
};

// =================== TAMBAH DATA DENGAN KONFIRMASI ===================
void tambah_data() {
    struct projek_klinik data;
    char lagi[10], konfirmasi[10];
    int nomor_pasien_awal = 0;

    // Hitung nomor pasien terakhir
    FILE *file = fopen("database_klinik.txt", "r");
    if (file != NULL) {
        char ch;
        while ((ch = fgetc(file)) != EOF) {
            if (ch == '#') nomor_pasien_awal++;
        }
        fclose(file);
    }

    file = fopen("database_klinik.txt", "a");
    if (!file) {
        printf("Gagal membuka file.\n");
        return;
    }

    do {
        while (1) { // loop input field sampai konfirmasi benar
            // Input nama pasien
            printf("Masukkan nama pasien: ");
            fgets(data.nama_pasien, sizeof(data.nama_pasien), stdin);
            data.nama_pasien[strcspn(data.nama_pasien, "\n")] = '\0';

            // Input jenis kelamin
            do {
                printf("Masukkan jenis kelamin (p/l): ");
                fgets(konfirmasi, sizeof(konfirmasi), stdin);
                data.jenis_kelamin = konfirmasi[0];
                if (!(data.jenis_kelamin=='p'||data.jenis_kelamin=='P'||data.jenis_kelamin=='l'||data.jenis_kelamin=='L'))
                    printf("Input salah! Hanya p/l.\n");
            } while (!(data.jenis_kelamin=='p'||data.jenis_kelamin=='P'||data.jenis_kelamin=='l'||data.jenis_kelamin=='L'));

            // Input usia
            char usia_str[20];
            while (1) {
                printf("Masukkan usia: ");
                fgets(usia_str, sizeof(usia_str), stdin);
                if (sscanf(usia_str, "%d", &data.usia)==1 && data.usia>0) break;
                printf("Input salah! Usia harus angka positif.\n");
            }

            // Input penyakit
            printf("Masukkan penyakit: ");
            fgets(data.penyakit, sizeof(data.penyakit), stdin);
            data.penyakit[strcspn(data.penyakit, "\n")] = '\0';

            // Input tanggal
            printf("Masukkan tanggal (DD/MM/YYYY): ");
            fgets(data.tanggal, sizeof(data.tanggal), stdin);
            data.tanggal[strcspn(data.tanggal, "\n")] = '\0';

            // Tampilkan ringkasan
            printf("\n===== KONFIRMASI DATA PASIEN =====\n");
            printf("Nama Pasien   : %s\n", data.nama_pasien);
            printf("Jenis Kelamin : %c\n", data.jenis_kelamin);
            printf("Usia          : %d\n", data.usia);
            printf("Penyakit      : %s\n", data.penyakit);
            printf("Tanggal       : %s\n", data.tanggal);
            printf("=================================\n");

            // Konfirmasi
            do {
                printf("Apakah data sudah benar? (y/n): ");
                fgets(konfirmasi, sizeof(konfirmasi), stdin);
            } while (!(konfirmasi[0]=='y'||konfirmasi[0]=='Y'||konfirmasi[0]=='n'||konfirmasi[0]=='N'));

            if (konfirmasi[0]=='y'||konfirmasi[0]=='Y') {
                fprintf(file, "#%d\nNama Pasien: %s\nJenis Kelamin: %c\nUsia: %d\nPenyakit: %s\nTanggal: %s\n\n",
                        nomor_pasien_awal+1,
                        data.nama_pasien,
                        data.jenis_kelamin,
                        data.usia,
                        data.penyakit,
                        data.tanggal);
                nomor_pasien_awal++;
                printf("✅ Data berhasil disimpan.\n");
                break; // keluar loop input
            } else {
                printf("❌ Data dibatalkan. Silakan input ulang dari awal.\n\n");
            }
        }

        // Tambah data lagi?
        do {
            printf("\nTambah data lagi? (y/n): ");
            fgets(lagi, sizeof(lagi), stdin);
        } while (!(lagi[0]=='y'||lagi[0]=='Y'||lagi[0]=='n'||lagi[0]=='N'));

    } while (lagi[0]=='y'||lagi[0]=='Y');

    fclose(file);
}

// =================== TAMPIL DATA ===================
void tampilkan_data() {
    FILE *file = fopen("database_klinik.txt", "r");
    if (!file) {
        printf("Belum ada data pasien.\n");
        return;
    }

    char line[200];
    printf("\n===== DATA PASIEN =====\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

// =================== CARI DATA ===================
void cari_data() {
    char keyword[50];
    printf("Masukkan nama pasien: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    FILE *file = fopen("database_klinik.txt", "r");
    if (!file) {
        printf("Belum ada data.\n");
        return;
    }

    char line[200];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, keyword)) {
            found = 1;
            printf("\nData pasien ditemukan:\n%s", line);
            for (int i = 0; i < 5; i++) {
                if (fgets(line, sizeof(line), file))
                    printf("%s", line);
            }
        }
    }

    if (!found)
        printf("Data pasien tidak ditemukan.\n");

    fclose(file);
}

// =================== MAIN ===================
int main() {
    char input[20];
    int pilihan;

    do {
        printf("\n=== MENU KLINIK SEHAT ===\n");
        printf("1. Tambah Data Pasien\n");
        printf("2. Tampilkan Data Pasien\n");
        printf("3. Cari Data Pasien\n");
        printf("4. Keluar\n");
        printf("Pilih menu (1-4): ");

        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &pilihan) != 1) {
            printf("Input salah! Masukkan angka 1-4.\n");
            continue;
        }

        switch (pilihan) {
            case 1:
                tambah_data();
                break;
            case 2:
                tampilkan_data();
                break;
            case 3:
                cari_data();
                break;
            case 4:
                printf("Terima kasih telah menggunakan layanan Klinik Sehat.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }

    } while (pilihan != 4);

    return 0;
}