#include <stdio.h>

struct projek_klinik {
    char nama_pasien[50];
    char jenis_kelamin;
    int usia;
    char penyakit[50];
    char tanggal[50];
};
// fungsi untuk menambah data pasien
void tambah_data() {
    struct projek_klinik data;
    char lagi;

    int nomor_pasien_awal = 0;

    FILE *file = fopen("database_klinik.txt", "r");
    if (file != NULL) {
        char ch;
        while ((ch = fgetc(file)) != EOF) {
            if (ch == '#') nomor_pasien_awal++;
        }
        fclose(file);
    }

    file = fopen("database_project_klinik.txt", "a");
    if (!file) {
        printf("Gagal membuka file.\n");
        return;
    }

    do {
        printf("Masukkan nama pasien: ");
        scanf(" %49[^\n]", data.nama_pasien);

        // validasi jenis kelamin
        do {
            printf("Masukkan jenis kelamin (p/l): ");
            scanf(" %c", &data.jenis_kelamin);

            if (data.jenis_kelamin != 'p' && data.jenis_kelamin != 'P' &&
                data.jenis_kelamin != 'l' && data.jenis_kelamin != 'L') {
                printf("Input salah! Hanya p / l.\n");
            }
        } while (data.jenis_kelamin != 'p' && data.jenis_kelamin != 'P' &&
                 data.jenis_kelamin != 'l' && data.jenis_kelamin != 'L');

        printf("Masukkan usia: ");
        scanf("%d", &data.usia);

        printf("Masukkan penyakit: ");
        scanf(" %49[^\n]", data.penyakit);

        printf("Masukkan tanggal (DD/MM/YYYY): ");
        scanf(" %49[^\n]", data.tanggal);

        fprintf(file, "#%d\nNama Pasien: %s \nJenis Kelamin: %c\nUsia: %d\nPenyakit: %s\nTanggal: %s\n\n",
                nomor_pasien_awal + 1, data.nama_pasien, data.jenis_kelamin,
                data.usia, data.penyakit, data.tanggal);

        nomor_pasien_awal++;

        printf("Tambah data lagi? (y/n): ");
        scanf(" %c", &lagi);
    } while (lagi == 'y' || lagi == 'Y');

    fclose(file);
}

// fungsi untuk menampilkan data pasien

// fungsi untuk mencari data pasien

// switch menu utama
int main() {
    int pilihan;

    do {
        printf("=== Menu Klinik Sehat ===\n");
        printf("1. Tambah Data Pasien\n");
        printf("2. Tampilkan Data Pasien\n");
        printf("3. Cari Data Pasien\n");
        printf("4. Keluar\n");
        printf("Pilih menu (1-4): ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambah_data();
                break;
            case 2:
                // tampilkan_data();
                break;
            case 3:
                // cari_data();
                break;
            case 4:
                printf("Terima kasih telah menggunakan layanan Klinik Sehat.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (pilihan != 4);

    return 0;
}