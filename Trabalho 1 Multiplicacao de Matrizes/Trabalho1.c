//Trabalho 1 - Multiplicacao de Matrizes
//Aluno Marcus Vinícius Torres de Oliveira
//DRE: 118142223
//Disciplina: ED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Matrizes
int *matriz_aleatoria_entrada1;
int *matriz_aleatoria_entrada2;
int *matriz_resultado_saida;

//Inicializa as matrizes de entrada(aleatoriamente) e saída
void inicializarMat(int dim){
    for(int i=0; i<dim;i++){
        for(int j=0; j<dim; j++){
            int num_random = rand() % 100; //Gera um número aleatório entre 0 e 99
            matriz_aleatoria_entrada1[i*dim+j] = num_random;
            matriz_resultado_saida[i*dim+j] = 0;
        }
    }
}

//Multiplica as matrizes da forma tradicional
void matrizSeq(int dim){
    for(int i=0; i<dim;i++){
        for(int j=0; j<dim; j++){
            for(int k=0; k<dim; k++){
                matriz_resultado_saida[i*dim+j] += matriz_aleatoria_entrada1[i*dim+k] * matriz_aleatoria_entrada1[k*dim+j];
            }
        }
    }
}

int main(int argc, char* argv[]){
    
    int dim;//Dimensão das matrizes de entrada

    //Leitura dos parametros de entrada
    if(argc<2) {
      printf("Digite: %s <dimensao da matriz> \n", argv[0]); //argv[0] trás o nome do programa
      return 1;
    }
    dim = atoi(argv[1]);
    

    matriz_aleatoria_entrada1 = (int *) malloc(sizeof(int) * dim * dim);
    if (matriz_aleatoria_entrada1 == NULL) {printf("ERRO--malloc\n"); return 2;}
    matriz_aleatoria_entrada2 = (int *) malloc(sizeof(int) * dim * dim);
    if (matriz_aleatoria_entrada2 == NULL) {printf("ERRO--malloc\n"); return 2;}
    matriz_resultado_saida = (int *) malloc(sizeof(int) * dim * dim);
    if (matriz_resultado_saida == NULL) {printf("ERRO--malloc\n"); return 2;}


    //Inicialização das matrizes com números aleatórios
    srand(time(NULL));
    inicializarMat(dim);


}
