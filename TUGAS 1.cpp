#include <stdio.h>
#include <pthread.h>

int nilai[] = {80, 75, 90, 85, 70, 95, 88};
int jumlah = 7;

float rata;
int med;
int maks;

pthread_mutex_t mutex;

void *rataRata(void *arg) {
    int total = 0;

    printf("\n[THREAD 1]\n");

    pthread_mutex_lock(&mutex);
    printf("[THREAD 1] \n");

    for (int i = 0; i < jumlah; i++) {
        total += nilai[i];
    }

    rata = (float)total / jumlah;

    printf("Rumus : (80+75+90+85+70+95+88) / 7\n");
    printf("Jawab : %.2f\n", rata);

    printf("[THREAD 1] \n");
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *median(void *arg) {
    int data[7];

    printf("\n[THREAD 2] \n");

    pthread_mutex_lock(&mutex);
    printf("[THREAD 2] \n");

    for (int i = 0; i < jumlah; i++) {
        data[i] = nilai[i];
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

    printf("Rumus : Data diurutkan = 70 75 80 85 88 90 95\n");
    printf("Jawab : %d\n", med);

    printf("[THREAD 2] \n");
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *maksimum(void *arg) {

    printf("\n[THREAD 3]\n");

    pthread_mutex_lock(&mutex);
    printf("[THREAD 3\n");

    maks = nilai[0];

    for (int i = 1; i < jumlah; i++) {
        if (nilai[i] > maks) {
            maks = nilai[i];
        }
    }

    printf("Rumus : Nilai maksimum = nilai terbesar\n");
    printf("Jawab : %d\n", maks);

    printf("[THREAD 3\n");
    pthread_mutex_unlock(&mutex);

    return NULL;
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

    pthread_mutex_destroy(&mutex);

    printf("\n====================================\n");
    printf(" SEMUA THREAD SELESAI\n");
    printf("====================================\n");

    return 0;
}
