#include <stdio.h>
#include <stdlib.h>

struct Utente {
    char nome[100];
    char sintomas[100];
    pid_t pid;
};

struct Message {
    char text[100];
};

struct RespostaBalcao {
    char especialidade[100];
    int prioridade;
    int listaDeEspera;
};

struct Medico
{
    char nome[100];
    char especialidade[100];
    pid_t pid;
};




int main(int argc, char **argv) {
    printf("%d\n", argc);

    for (int i = 0; i < argc; i++)
    {
        printf("Argumento %d: %s\n", i, argv[i]);
    }
    
}