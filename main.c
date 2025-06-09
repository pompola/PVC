#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 2500000
#define ITERATIONS 1000

// Инициализация массивов
void initialize_arrays(double *a, double *b) {
    for (int i = 0; i < N; i++) {
        a[i] = (double)rand() / RAND_MAX * 100.0;
        b[i] = (double)rand() / RAND_MAX * 100.0 + 1.0; // избегаем деления на ноль
    }
}

// Последовательные операции
void add_sequential(double *a, double *b, double *res) {
    for (int i = 0; i < N; i++) {
        res[i] = a[i] + b[i];
    }
}

void sub_sequential(double *a, double *b, double *res) {
    for (int i = 0; i < N; i++) {
        res[i] = a[i] - b[i];
    }
}

void mul_sequential(double *a, double *b, double *res) {
    for (int i = 0; i < N; i++) {
        res[i] = a[i] * b[i];
    }
}

void div_sequential(double *a, double *b, double *res) {
    for (int i = 0; i < N; i++) {
        if (b[i] != 0.0) {
            res[i] = a[i] / b[i];
        } else {
            res[i] = 0.0;
        }
    }
}

// Параллельные операции
void add_parallel(double *a, double *b, double *res, int num_threads) {
    int i;
#pragma omp parallel for num_threads(num_threads)
    for (i = 0; i < N; i++) {
        res[i] = a[i] + b[i];
    }
}

void sub_parallel(double *a, double *b, double *res, int num_threads) {
    int i;
#pragma omp parallel for num_threads(num_threads)
    for (i = 0; i < N; i++) {
        res[i] = a[i] - b[i];
    }
}

void mul_parallel(double *a, double *b, double *res, int num_threads) {
    int i;
#pragma omp parallel for num_threads(num_threads)
    for (i = 0; i < N; i++) {
        res[i] = a[i] * b[i];
    }
}

void div_parallel(double *a, double *b, double *res, int num_threads) {
    int i;
#pragma omp parallel for num_threads(num_threads)
    for (i = 0; i < N; i++) {
        if (b[i] != 0.0) {
            res[i] = a[i] / b[i];
        } else {
            res[i] = 0.0;
        }
    }
}

// Замер времени для одной операции
double measure_time(void (*op)(double*, double*, double*, int), 
                    double *a, double *b, double *res, 
                    int num_threads) {
    double start_time = omp_get_wtime();
    for (int i = 0; i < ITERATIONS; i++) {
        op(a, b, res, num_threads);
    }
    double end_time = omp_get_wtime();
    return (end_time - start_time) / ITERATIONS;
}

int main() {
    double *a = (double*)malloc(N * sizeof(double));
    double *b = (double*)malloc(N * sizeof(double));
    double *add = (double*)malloc(N * sizeof(double));
    double *sub = (double*)malloc(N * sizeof(double));
    double *mul = (double*)malloc(N * sizeof(double));
    double *div = (double*)malloc(N * sizeof(double));

    srand(time(NULL));
    initialize_arrays(a, b);

    // Последовательное выполнение
    printf("Sequential execution:\n");
    double add_seq_time = measure_time(add_sequential, a, b, add, 1);
    double sub_seq_time = measure_time(sub_sequential, a, b, sub, 1);
    double mul_seq_time = measure_time(mul_sequential, a, b, mul, 1);
    double div_seq_time = measure_time(div_sequential, a, b, div, 1);

    printf("  Addition: %.6f sec/op\n", add_seq_time);
    printf("  Subtraction: %.6f sec/op\n", sub_seq_time);
    printf("  Multiplication: %.6f sec/op\n", mul_seq_time);
    printf("  Division: %.6f sec/op\n\n", div_seq_time);

    // Параллельное выполнение с разным количеством потоков
    int thread_counts[] = {2, 4, 8, 16};
    int num_tests = sizeof(thread_counts) / sizeof(thread_counts[0]);

    for (int i = 0; i < num_tests; i++) {
        int threads = thread_counts[i];
        printf("Parallel execution (%d threads):\n", threads);

        double add_par_time = measure_time(add_parallel, a, b, add, threads);
        double sub_par_time = measure_time(sub_parallel, a, b, sub, threads);
        double mul_par_time = measure_time(mul_parallel, a, b, mul, threads);
        double div_par_time = measure_time(div_parallel, a, b, div, threads);
printf("  Addition: %.6f sec/op (Speedup: %.2f)\n", 
               add_par_time, add_seq_time / add_par_time);
        printf("  Subtraction: %.6f sec/op (Speedup: %.2f)\n", 
               sub_par_time, sub_seq_time / sub_par_time);
        printf("  Multiplication: %.6f sec/op (Speedup: %.2f)\n", 
               mul_par_time, mul_seq_time / mul_par_time);
        printf("  Division: %.6f sec/op (Speedup: %.2f)\n\n", 
               div_par_time, div_seq_time / div_par_time);
    }

    free(a);
    free(b);
    free(add);
    free(sub);
    free(mul);
    free(div);

    return 0;
}
