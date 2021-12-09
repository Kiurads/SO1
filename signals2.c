#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>

void atendeSinal(int snum, siginfo_t* act, void* oldact) {
    printf("\n\nTempo!\n\n");
}

int main(int argc, char **argv) {
    srand(time(NULL));

    int erros;
    int num1, num2, resposta;
    int acertos = 0;
    int N = 20;
    struct sigaction sa;

    erros = 0;

    sa.sa_sigaction = atendeSinal;

    sa.sa_flags = SA_NODEFER;

    sigaction(SIGALRM, &sa, NULL);

    do {
        if (N > 5) {
            N--;
        }
        
        num1 = rand() % 101;
        num2 = rand() % 101;

        resposta = -1;

        printf("%d + %d = ", num1, num2);

        alarm(N);

        scanf("%d", &resposta);

        if (resposta == (num1 + num2)) {
            printf("Acertou!\n\n");
            acertos++;
        } else {
            printf("Melhor sorte para a proxima!\n\n");
            erros++;
        }
        
    } while(erros < 2);

    printf("Acabou o jogo com uma pontuacao de %d\n\n", acertos);
}