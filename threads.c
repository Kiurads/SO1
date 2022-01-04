#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define NTHREADS 4

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct TDados 
{
    int continua;
    char escreve;
    pthread_t tid;
    void* ret;
} TDados;

void * imprime(void * arg) 
{
    TDados* dados = (TDados*) arg;

    while (dados->continua)
    {
        pthread_mutex_lock(&mutex);
        printf(".");
        for (int i = 0; i < 3; i++)
        {
            printf("%c", dados->escreve);
            fflush(stdout);
            sleep(1);
        }
        printf(".");
        fflush(stdout);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    return NULL;
}

int main(int argc, char **argv) 
{
    int res;
    TDados threads[NTHREADS];
    char string[100];

    for (int i = 0; i < NTHREADS; i++) 
    {
        threads[i].continua = 1;
        threads[i].escreve = 'A' + i;

        res = pthread_create(&threads[i].tid, NULL, imprime, (void*) &threads[i]);

        if (res != 0) 
        {
            perror("Erro na criacao da thread\n");
            exit(EXIT_FAILURE);
        }
    }

    while (strcmp(string, "sair") != 0)
    {
        fgets(string, 100, stdin);

        if (string[strlen(string) - 1] == '\n')
        {
            string[strlen(string) - 1] = '\0';
        }
        

        printf("Escreveu: %s\n", string);
    }
    
    for (int i = 0; i < NTHREADS; i++)
    {
        threads[i].continua = 0;
        pthread_join(threads[i].tid, &threads[i].ret);

        printf("\nTerminou a thread: %c\n", threads[i].escreve);
    }

    exit(EXIT_SUCCESS);
}