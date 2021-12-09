#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int contador;

void atendeSinal(int snum, siginfo_t* act, void* oldact) {
    if (++contador == 5)
    {
        printf("ok, pronto\n");

        exit(EXIT_FAILURE);
    } else {
        printf("ai\n");
    }
    
}

int main(int argc, char **argv) {
    char buffer[100];
    contador = 0;
    struct sigaction sa;

    sa.sa_sigaction = atendeSinal;

    sigaction(SIGINT, &sa, NULL);

    do {
        printf("Nome: ");
        fgets(buffer, 100, stdin);

        printf("Ola, %s\n", buffer);
    } while(strcmp(buffer, "sair") != 0);
}