#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

double **matrixA, **matrixB, **matrixC;
pthread_t *threads;
int N, M, L;

double **initializeMatrix(int r, int c);
void printMatrix(int r, int c, double **matrix);
void *computeElement(void *arg);

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

    matrixA = initializeMatrix(N, M);
    matrixB = initializeMatrix(M, L);
    matrixC = initializeMatrix(N, L);

    threads = malloc(N * L * sizeof(pthread_t));
    if (!threads)
    {
        printf("Failed to allocate memory for threads.\n");
        return 1;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < L; j++)
        {
            int *args = malloc(2 * sizeof(int));
            args[0] = i;
            args[1] = j;
            pthread_create(&threads[i * L + j], NULL, computeElement, (void *)args);
        }
    }

    for (int i = 0; i < N * L; i++)
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

void *computeElement(void *arg)
{
    int *args = (int *)arg;
    int i = args[0];
    int j = args[1];
    double temp = 0.0;
    for (int k = 0; k < M; k++)
    {
        temp += matrixA[i][k] * matrixB[k][j];
    }
    matrixC[i][j] = temp;
    free(arg);
    return NULL;
}
