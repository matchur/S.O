/*
Autor: Matheus Vinicius da Costa
Criação: 30/03/2024 
Att: 30/03/2024

Descricao: Esse code realiza a criação de processos utilizando
uma estrutura de arvore binaria com N niveis de profundidade 

O valor inicial esta em 3, mude a variavel "niveis" para mudar a 
profundidade da arvore

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void cria_hier(int level, int max_level) {
    if (level == max_level) {
        // Nível máximo atingido, não cria mais filhos
        printf("Processo Final: PID %d\n", getpid());
        return;
    }

    printf("Processo nível %d: PID %d\n", level, getpid());

    // Cria dois filhos
    for (int i = 0; i < 2; ++i) {
        pid_t pid = fork();
        if (pid == 0) {
            // Processo filho
            cria_hier(level + 1, max_level);
            // Saída do loop para evitar que o filho crie seus próprios filhos
            break;
        } else if (pid < 0) {
            _exit(1);
        }
        // Processo pai
        wait(NULL); // Espera o filho terminar
    }
}

int main() {
    int niveis = 3; //MODIFIQUE AQUI - N 
    cria_hier(0, niveis);
    return 0;
}