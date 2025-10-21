#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void shell(int* items, int count)
{
    int i, j, gap, k;
    int x, a[5];
    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (j >= 0) && (x < items[j]); j = j - gap) {
                items[j + gap] = items[j];
            }
            items[j + gap] = x;
        }
    }
}

void qs(int* items, int left, int right)
{
    int i, j;
    int x, y;
    i = left; j = right;

    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int* create_random_array(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000;
    }
    return arr;
}

int* create_ascending_array(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    return arr;
}

int* create_descending_array(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
    return arr;
}

int* create_mixed_array(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    int half = size / 2;

    for (int i = 0; i < half; i++) {
        arr[i] = i;
    }
    for (int i = half; i < size; i++) {
        arr[i] = size - i + half;
    }
    return arr;
}

double measure_shell_time(int* arr, int size) {
    int* temp = (int*)malloc(size * sizeof(int));
    memcpy(temp, arr, size * sizeof(int));

    clock_t start = clock();
    shell(temp, size);
    clock_t end = clock();

    free(temp);
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

double measure_qs_time(int* arr, int size) {
    int* temp = (int*)malloc(size * sizeof(int));
    memcpy(temp, arr, size * sizeof(int));

    clock_t start = clock();
    qs(temp, 0, size - 1);
    clock_t end = clock();

    free(temp);
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

double measure_qsort_time(int* arr, int size) {
    int* temp = (int*)malloc(size * sizeof(int));
    memcpy(temp, arr, size * sizeof(int));

    clock_t start = clock();
    qsort(temp, size, sizeof(int), compare);
    clock_t end = clock();

    free(temp);
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main() {
    system("chcp 1251");
    srand((unsigned int)time(NULL));
    int size = 100000;

    printf("Сравнение времени работы алгоритмов сортировки\n");
    printf("=============================================\n\n");

    printf("Размер массива: %d\n", size);
    printf("+------------------+---------------+---------------+---------------+\n");
    printf("| Тип массива      | Shell sort    | Quick sort    | qsort         |\n");
    printf("+------------------+---------------+---------------+---------------+\n");

    int* random_arr = create_random_array(size);
    int* asc_arr = create_ascending_array(size);
    int* desc_arr = create_descending_array(size);
    int* mixed_arr = create_mixed_array(size);

    // Случайный массив
    printf("| %-16s | %-13.6f | %-13.6f | %-13.6f |\n",
        "Случайный",
        measure_shell_time(random_arr, size),
        measure_qs_time(random_arr, size),
        measure_qsort_time(random_arr, size));
    printf("+------------------+---------------+---------------+---------------+\n");

    // Возрастающий массив
    printf("| %-16s | %-13.6f | %-13.6f | %-13.6f |\n",
        "Возрастающий",
        measure_shell_time(asc_arr, size),
        measure_qs_time(asc_arr, size),
        measure_qsort_time(asc_arr, size));
    printf("+------------------+---------------+---------------+---------------+\n");

    // Убывающий массив
    printf("| %-16s | %-13.6f | %-13.6f | %-13.6f |\n",
        "Убывающий",
        measure_shell_time(desc_arr, size),
        measure_qs_time(desc_arr, size),
        measure_qsort_time(desc_arr, size));
    printf("+------------------+---------------+---------------+---------------+\n");

    // Смешанный массив
    printf("| %-16s | %-13.6f | %-13.6f | %-13.6f |\n",
        "Смешанный",
        measure_shell_time(mixed_arr, size),
        measure_qs_time(mixed_arr, size),
        measure_qsort_time(mixed_arr, size));
    printf("+------------------+---------------+---------------+---------------+\n");

    free(random_arr);
    free(asc_arr);
    free(desc_arr);
    free(mixed_arr);

    return 0;
}