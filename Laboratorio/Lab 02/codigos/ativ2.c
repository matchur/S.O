/*
Autor: Matheus Vinicius da Costa
Criação: 30/03/2024 
Att: 30/03/2024

Descricao: Esse code espera que o argumento que esteja vindo 
seja um comando e então executa ele como um filho do processo.
O processo pai então espera e ao termino da execução do código
ele exibe uma mensagem


*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <comando>\n", argv[0]);
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Erro ao criar processo filho");
        exit(1);
    } else if (pid == 0) {
        // Processo filho
        execvp(argv[1], &argv[1]); // Executa o comando
        perror("Erro ao executar o comando");
        exit(1);
    } else {
        // Processo pai
        int status;
        waitpid(pid, &status, 0); // Aguarda o término do filho
        if (WIFEXITED(status)) {
            printf("O comando foi executado com sucesso.\n");
        } else {
            printf("O comando falhou ao ser executado.\n");
        }
    }

    return 0;
}