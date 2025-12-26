// jumlah pasien
// nama pasien
// jenis kelamin
// usia
// penyakit
//tanggal
// setelah selesai masukan ke dalam data base yang berupa file
#include <stdio.h>

struct projek_klinik {
    char nama_pasien[50];
    char jenis_kelamin;
    int usia;
    char penyakit[50];
    char tanggal[20];
};

int main() {
    struct projek_klinik data[100];
    int total = 0, nomor_pasien_awal = 0;
    char lagi;

    FILE *file = fopen("database_project_klinik.txt", "r");
    if (file != NULL) {
        char ch;
        while ((ch = fgetc(file)) != EOF) {
            if (ch == '#') nomor_pasien_awal++;
        }
        fclose(file);
    }

    printf("=== Selamat datang di Klinik Sehat ===\n");
    do {
        struct projek_klinik *pasien = &data[total];

        printf("Masukkan nama pasien: ");
        scanf(" %49[^\n]", pasien->nama_pasien);

        // ==========================
        // VALIDASI JENIS KELAMIN
        // ==========================
        do {
            printf("Masukkan jenis kelamin (p/l): ");
            scanf(" %c", &pasien->jenis_kelamin);

            if (pasien->jenis_kelamin != 'p' &&
                pasien->jenis_kelamin != 'P' &&
                pasien->jenis_kelamin != 'l' &&
                pasien->jenis_kelamin != 'L') {
                printf("Input salah! Gunakan hanya 'p' atau 'l'.\n");
            }

        } while (pasien->jenis_kelamin != 'p' &&
                 pasien->jenis_kelamin != 'P' &&
                 pasien->jenis_kelamin != 'l' &&
                 pasien->jenis_kelamin != 'L');

        printf("Masukkan usia: ");
        scanf("%d", &pasien->usia);

        printf("Masukkan penyakit: ");
        scanf(" %49[^\n]", pasien->penyakit);

        printf("Masukkan tanggal (DD/MM/YYYY): ");
        scanf(" %19[^\n]", pasien->tanggal);

        total++;

        printf("Tambah data pasien lagi? (y/n): ");
        scanf(" %c", &lagi);

    } while ((lagi == 'y' || lagi == 'Y') && total < 100);

    file = fopen("database_project_klinik.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file database_pasien.txt\n");
        return 1;
    }

    for (int i = 0; i < total; i++) {
        fprintf(file, "#Pasien %d\n", nomor_pasien_awal + i + 1);
        fprintf(file, "Nama          : %s\n", data[i].nama_pasien);
        fprintf(file, "Jenis Kelamin : %c\n", data[i].jenis_kelamin);
        fprintf(file, "Usia          : %d\n", data[i].usia);
        fprintf(file, "Penyakit      : %s\n", data[i].penyakit);
        fprintf(file, "Tanggal       : %s\n", data[i].tanggal);
        fprintf(file, "-----------------------------\n");
    }

    fclose(file);
    printf("Data pasien berhasil disimpan ke file database_project_klinik.txt\n");

    return 0;
}
