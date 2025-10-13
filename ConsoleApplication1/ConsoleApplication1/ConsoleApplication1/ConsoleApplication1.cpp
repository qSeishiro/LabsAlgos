#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    system("chcp 1251");
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    int choice;

    do {
        printf("\n=== УМНОЖЕНИЕ МАТРИЦ ===\n");
        printf("Выберите размер массивов:\n");
        printf("1 - 100x100\n");
        printf("2 - 200x200\n");
        printf("3 - 400x400\n");
        printf("4 - 1000x1000\n");
        printf("5 - 2000x2000\n");
        printf("6 - 4000x4000\n");
        printf("7 - 10000x10000\n");
        printf("0 - Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        if (choice == 0) {
            printf("Выход из программы.\n");
            break;
        }

        int n;
        switch (choice) {
        case 1: n = 100; break;
        case 2: n = 200; break;
        case 3: n = 400; break;
        case 4: n = 1000; break;
        case 5: n = 2000; break;
        case 6: n = 4000; break;
        case 7: n = 10000; break;
        default:
            printf("Неверный выбор! Попробуйте снова.\n");
            continue;
        }

        printf("\nРазмер массивов: %dx%d\n", n, n);

        int** a = (int**)malloc(n * sizeof(int*));
        int** b = (int**)malloc(n * sizeof(int*));
        int** c = (int**)malloc(n * sizeof(int*));

        for (int i = 0; i < n; i++) {
            a[i] = (int*)malloc(n * sizeof(int));
            b[i] = (int*)malloc(n * sizeof(int));
            c[i] = (int*)malloc(n * sizeof(int));
        }

        clock_t start, end;
        double cpu_time_used;

        start = clock();
        srand(time(NULL));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = rand() % 100 + 1;
            }
        }
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Время заполнения массива A: %.8f секунд\n", cpu_time_used);

        start = clock();
        srand(time(NULL) + 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                b[i][j] = rand() % 100 + 1;
            }
        }
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Время заполнения массива B: %.8f секунд\n", cpu_time_used);

        printf("Выполняется умножение матриц %dx%d...\n", n, n);
        start = clock();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int elem_c = 0;
                for (int r = 0; r < n; r++) {
                    elem_c += a[i][r] * b[r][j];
                }
                c[i][j] = elem_c;
            }
        }

        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Время умножения матриц: %.8f секунд\n", cpu_time_used);

        for (int i = 0; i < n; i++) {
            free(a[i]);
            free(b[i]);
            free(c[i]);
        }
        free(a);
        free(b);
        free(c);

        printf("\nНажмите Enter для продолжения...");
        while (getchar() != '\n'); 
        getchar(); 

    } while (1);

    return 0;
}