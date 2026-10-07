#include <stdio.h>
#include <pthread.h>

int nilai[] = {80, 75, 90, 85, 70, 95, 88};
int jumlah = 7;

float rata;
int med;
int maks;

pthread_mutex_t mutex;

// THREAD 1 - RATA-RATA
void *rataRata(void *arg) {
    int total = 0;

    for (int i = 0; i < jumlah; i++) {
        pthread_mutex_lock(&mutex);

        total += nilai[i];

        pthread_mutex_unlock(&mutex);
    }

    rata = (float) total / jumlah;

    pthread_exit(NULL);
}

// THREAD 2 - MEDIAN
void *median(void *arg) {
    int data[7];

    for (int i = 0; i < jumlah; i++) {
        pthread_mutex_lock(&mutex);

        data[i] = nilai[i];

        pthread_mutex_unlock(&mutex);
    }

    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = i + 1; j < jumlah; j++) {
            if (data[i] > data[j]) {
                int temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }

    med = data[jumlah / 2];

    pthread_exit(NULL);
}

// THREAD 3 - MAKSIMUM
void *maksimum(void *arg) {
    pthread_mutex_lock(&mutex);

    maks = nilai[0];

    for (int i = 1; i < jumlah; i++) {
        if (nilai[i] > maks) {
            maks = nilai[i];
        }
    }

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {

    pthread_t t1, t2, t3;

    pthread_mutex_init(&mutex, NULL);

    printf("====================================\n");
    printf(" PROGRAM \n");
    printf("====================================\n");

    pthread_create(&t1, NULL, rataRata, NULL);
    pthread_create(&t2, NULL, median, NULL);
    pthread_create(&t3, NULL, maksimum, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("\n1. RATA-RATA\n");
    printf("Rumus : Rata-rata = jumlah seluruh data / banyak data\n");
    printf("Jawab : %.2f\n", rata);

    printf("\n2. MEDIAN\n");
    printf("Rumus : Data diurutkan, kemudian mengambil nilai tengah\n");
    printf("Jawab : %d\n", med);

    printf("\n3. MAKSIMUM\n");
    printf("Rumus : Nilai maksimum = nilai terbesar\n");
    printf("Jawab : %d\n", maks);

    printf("\n====================================\n");
    printf(" SEMUA THREAD SELESAI\n");
    printf("====================================\n");

    pthread_mutex_destroy(&mutex);

    return 0;
}
