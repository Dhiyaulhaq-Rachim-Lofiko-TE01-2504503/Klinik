#include <stdio.h>

struct Pasien {
    char nama[50];
    char jenis_kelamin;
    int usia;
};

int main() {
    int jumlah;
    int i, j;
    int valid;

    printf("=== SISTEM PENDAFTARAN PASIEN ===\n");
    printf("Masukkan jumlah pasien: ");
    scanf("%d", &jumlah);

    struct Pasien data[jumlah];

    for (i = 0; i < jumlah; i++) {
        printf("\nData Pasien ke-%d\n", i + 1);

        /* ===== INPUT NAMA ===== */
        do {
            valid = 1;
            int huruf = 0;

            printf("Nama Pasien : ");
            scanf(" %[^\n]", data[i].nama);

            for (j = 0; data[i].nama[j] != '\0'; j++) {
                if ((data[i].nama[j] >= 'A' && data[i].nama[j] <= 'Z') ||
                    (data[i].nama[j] >= 'a' && data[i].nama[j] <= 'z')) {
                    huruf++;
                } else if (data[i].nama[j] == ' ') {
                    /* spasi boleh */
                } else {
                    valid = 0;
                    break;
                }
            }

            if (huruf < 2) valid = 0;

            if (!valid) {
                printf("Nama tidak valid! Gunakan huruf & spasi, minimal 2 huruf.\n");
            }

        } while (!valid);

        /* ===== JENIS KELAMIN ===== */
        do {
            printf("Jenis Kelamin (L/P): ");
            scanf(" %c", &data[i].jenis_kelamin);

            if (data[i].jenis_kelamin != 'L' &&
                data[i].jenis_kelamin != 'l' &&
                data[i].jenis_kelamin != 'P' &&
                data[i].jenis_kelamin != 'p') {
                printf("Input salah! Masukkan L atau P.\n");
            }

        } while (data[i].jenis_kelamin != 'L' &&
                 data[i].jenis_kelamin != 'l' &&
                 data[i].jenis_kelamin != 'P' &&
                 data[i].jenis_kelamin != 'p');

        /* ===== USIA ===== */
        do {
            printf("Usia Pasien : ");
            scanf("%d", &data[i].usia);

            if (data[i].usia <= 0 || data[i].usia >= 120) {
                printf("Usia tidak valid! Masukkan 1–119.\n");
            }

        } while (data[i].usia <= 0 || data[i].usia >= 120);
    }

    /* ===== OUTPUT ===== */
    printf("\n=== DATA PASIEN ===\n");
    for (i = 0; i < jumlah; i++) {
        printf("\nPasien ke-%d\n", i + 1);
        printf("Nama          : %s\n", data[i].nama);
        printf("Jenis Kelamin : %c\n", data[i].jenis_kelamin);
        printf("Usia          : %d\n", data[i].usia);
        printf("----------------------\n");
    }

    return 0;
}
