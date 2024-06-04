#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

double **matrixA, **matrixB, **matrixC;
pthread_t *threads;
int N, M, L;

double **initializeMatrix(int r, int c);
void printMatrix(int r, int c, double **matrix);
void *multiplyRow(void *arg);

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <N> <M> <L>\n", argv[0]);
        return 1;
    }

    N = atoi(argv[1]);
    M = atoi(argv[2]);
    L = atoi(argv[3]);

    if (M == 0 || N == 0 || L == 0)
    {
        printf("Matrix dimensions must be greater than 0.\n");
        return 1;
    }

    matrixA = initializeMatrix(N, M);
    matrixB = initializeMatrix(M, L);
    matrixC = initializeMatrix(N, L);

    threads = malloc(N * sizeof(pthread_t));
    if (!threads)
    {
        printf("Failed to allocate memory for threads.\n");
        return 1;
    }

    for (int i = 0; i < N; i++)
    {
        pthread_create(&threads[i], NULL, multiplyRow, (void *)(size_t)i);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printMatrix(N, L, matrixC);

    free(matrixA);
    free(matrixB);
    free(matrixC);
    free(threads);
    return 0;
}

double **initializeMatrix(int r, int c)
{
    double **matrix = (double **)malloc(r * sizeof(double *));
    for (int i = 0; i < r; i++)
    {
        matrix[i] = (double *)malloc(c * sizeof(double));
        for (int j = 0; j < c; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
    return matrix;
}

void printMatrix(int r, int c, double **matrix)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%5.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void *multiplyRow(void *arg)
{
    int row = (int)(size_t)arg;
    for (int j = 0; j < L; j++)
    {
        double temp = 0.0;
        for (int k = 0; k < M; k++)
        {
            temp += matrixA[row][k] * matrixB[k][j];
        }
        matrixC[row][j] = temp;
    }
    return NULL;
}
