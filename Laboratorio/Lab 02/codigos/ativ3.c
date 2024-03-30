/*
Autor: Matheus Vinicius da Costa
Criação: 30/03/2024 
Att: 30/03/2024

Descricao: Esse code cria um vetor e divide funçoes para processos 
dentro do vetor, cada processo tem a função de encontrar um item dentro do vetor, 
caso encontre ele vai exibir uma mensagem


*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define finder 3
#define N_FILHOS 4									//Número de Processos filho
#define N_VETOR 10									//Tamanho do vetor


//size = tamanho do vetor
int* create_random_array(int size){
    int* array = (int*) malloc(sizeof(int) * size);
    int i;
    for(i = 0; i < size; i++){
        array[i] = rand() % size;
    }
    return array;
}

void print_array(int* array, int size){
    printf("[");
    int i;
    for(i = 0; i < size; i++){
        printf("%d ", array[i]);
    }
    printf("]\n");
}


int main(){

    //Criação do vetor com valores aleatorios
    int* vet = create_random_array(N_VETOR);
    print_array(vet, N_VETOR);

    //Calculo da parte do vetor recebida pelos filhos
    int quant = N_VETOR / N_FILHOS;
    int qnt_aux = N_VETOR % N_FILHOS;

    //Inicialização dos filhos
    pid_t pid, pidret;
    int status = 0, proc = finder;
    int i = 0, j = 0, x = 0;
    int aux = 0;

    pid = getpid();

    for (i = 0; i < N_FILHOS & pid != 0; ++i){
        pid = fork();

        if(pid >= 0){
            if(pid  == 0){
                
                //O filho recebe sua parte do vetor
                if(i < qnt_aux){
                    aux = quant + 1;
                } else{
                    aux = quant;
                }

                //Calculo da posição em que o vetor deve começar
                if(i < qnt_aux){
                    x = i * (quant);
                } else{
                    x = i * aux + qnt_aux;
                }

                //Passagem na respectiva parte do filho
                for(j = x; j < x + aux; j++){
                    if(vet[j] == proc){
                        printf("O valor %d foi encontrado na posicao %d do vetor\n", proc, j);
                        return 1;
                    }
                }
                return 0;

            }
        } else{
            printf("Erro ao criar o processo filho\n");
            exit(0);
        }
    }

    //Verifica qual filho encontrou o valor procurado
    if(pid){
        x = 0;

        do{
            pidret = wait(&status);
            if(WEXITSTATUS(status) != 0){
                printf("O filho %d encontrou o valor procurado\n", pidret);
            }
            x++;
        } while(x < N_FILHOS);
    }


    return 0;
}