#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

#define SERVER_FIFO "/tmp/server_fifo"
#define MAX_SIZE 100

int main() {
    int fifo_fd;
    int read_res;
    char buffer[MAX_SIZE];

    mkfifo(SERVER_FIFO, 0777);

    printf("\nFIFO criado!\n");
    
    if (fifo_fd == -1)
    {
        perror("\nErro ao abrir/criar o FIFO");
        exit(EXIT_FAILURE);
    }
    
    do
    {
        fifo_fd = open(SERVER_FIFO, O_RDONLY);

        memset(buffer, '\0', MAX_SIZE);

        read_res = read(fifo_fd, &buffer, MAX_SIZE);

        for (size_t i = 0; i < MAX_SIZE; i++)
        {
            if (buffer[i] == '\n')
            {
                buffer[i] = '\0';
                break;
            }   
        }

        printf("\nRecebido: %s\n", buffer);
    
        close(fifo_fd);
    } while (strcmp(buffer, "sair") != 0);
    
    unlink(SERVER_FIFO);

    return 0;
}