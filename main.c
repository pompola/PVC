#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 2500000
#define ITERATIONS 1000

void sequential_operations(double* a, double* b, double* add, double* sub, double* mul, double* div) {
    for (int i = 0; i < N; i++) {
        add[i] = a[i] + b[i];
        sub[i] = a[i] - b[i];
        mul[i] = a[i] * b[i];
        if (b[i] != 0.0) {
            div[i] = a[i] / b[i];
        }
        else {
            div[i] = 0.0;
        }
    }
}

void parallel_operations(double* a, double* b, double* add, double* sub, double* mul, double* div, int num_threads) {
#pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < N; i++) {
        add[i] = a[i] + b[i];
        sub[i] = a[i] - b[i];
        mul[i] = a[i] * b[i];
        if (b[i] != 0.0) {
            div[i] = a[i] / b[i];
        }
        else {
            div[i] = 0.0;
        }
    }
}

void initialize_arrays(double* a, double* b) {
    for (int i = 0; i < N; i++) {
        a[i] = (double)rand() / RAND_MAX * 100.0;
        b[i] = (double)rand() / RAND_MAX * 100.0 + 1.0; // избегаем деления на ноль
    }
}

double measure_time(void (*func)(double*, double*, double*, double*, double*, double*, int),
    double* a, double* b, double* add, double* sub, double* mul, double* div,
    int num_threads) {
    double start_time = omp_get_wtime();
    for (int i = 0; i < ITERATIONS; i++) {
        func(a, b, add, sub, mul, div, num_threads);
    }
    double end_time = omp_get_wtime();
    return (end_time - start_time) / ITERATIONS;
}

int main() {
    double* a = (double*)malloc(N * sizeof(double));
    double* b = (double*)malloc(N * sizeof(double));
    double* add = (double*)malloc(N * sizeof(double));
    double* sub = (double*)malloc(N * sizeof(double));
    double* mul = (double*)malloc(N * sizeof(double));
    double* div = (double*)malloc(N * sizeof(double));

    srand(time(NULL));
    initialize_arrays(a, b);

    // Последовательное выполнение
    double seq_time = measure_time((void (*)(double*, double*, double*, double*, double*, double*, int))sequential_operations,
        a, b, add, sub, mul, div, 1);
    printf("Sequential time: %.6f seconds per operation\n", seq_time);

    // Параллельное выполнение с разным количеством потоков
    int thread_counts[] = { 2, 4, 8, 16 };
    int num_tests = sizeof(thread_counts) / sizeof(thread_counts[0]);

    for (int i = 0; i < num_tests; i++) {
        int threads = thread_counts[i];
        double par_time = measure_time(parallel_operations, a, b, add, sub, mul, div, threads);
        printf("Parallel time (%d threads): %.6f seconds per operation\n",
            threads, par_time, seq_time / par_time);
    }

    free(a);
    free(b);
    free(add);
    free(sub);
    free(mul);
    free(div);

    return 0;
}
