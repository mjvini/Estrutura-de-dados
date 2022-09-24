#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int dim;
int **mat1, **novaMat1;

//Inicializa as matrizes de entrada(aleatoriamente) e saída
void inicializarMat(int dim, int **mat){
    for(int i=0; i<dim;i++){
        for(int j=0; j<dim; j++){
            int num_random = rand() % 100; //Gera um número aleatório entre 0 e 99
            mat[i][j] = num_random;
            //mat2[i*dim+j] = (num_random * (i+1)) % 100;
            //mat_saida[i*dim+j] = 0;
        }
    }
}

//Inicializa as matrizes de entrada(aleatoriamente) e saída com 0
void inicializarMat2(int dim, int **mat){
    for(int i=0; i<dim;i++){
        for(int j=0; j<dim; j++){
            //int num_random = rand() % 100; //Gera um número aleatório entre 0 e 99
            mat[i][j] = 0;
            //mat2[i*dim+j] = (num_random * (i+1)) % 100;
            //mat_saida[i*dim+j] = 0;
        }
    }
}

void printMat(int dim, int** mat){
    //printf("Matriz: \n");
    for(int i=0; i<dim;i++){
        printf("\n");
        for(int j=0; j<dim; j++){
            printf("%d ", mat[i][j]);
        }
        //puts("");
    }
    printf("\n");
}

int function_ehPotenciaDeDois(int n){
    int num = n;
    if( n == 0){
        printf("%d Não é potencia de dois \n", num);
        return 0; //False
    }

    while (n != 1) {
        if (n % 2 != 0){
            printf("%d Não é potencia de dois \n", num);
            return 0;
        }
        n = n / 2;
    }
    printf("%d É potencia de dois \n", num);
    return 1; //True
}

void completaMatrizes(int dimAntiga,int **mat, int **matNova){
    for(int i=0; i<dimAntiga;i++){
        for(int j=0; j<dimAntiga; j++){
            matNova[i][j] = mat[i][j];
        }
    }
}

/*
int** arr = (int**)malloc(r * sizeof(int*));
    for (i = 0; i < r; i++)
        arr[i] = (int*)malloc(c * sizeof(int));
*/

int alocacaoMemoria(int dim){
    mat1 = (int **) malloc(sizeof(int*) * dim);
        for(int i = 0; i < dim; i++){
            mat1[i] = (int*) malloc(dim * sizeof(int));
        }
    if (mat1 == NULL) {printf("ERRO--malloc\n"); return 2;}
}

//Retorna a potencia de 2 mais próxima 
int  proximaPotenciaDe2 ( unsigned  int  x ){
    int  value  =  1 ;

    while  ( value  <=  x){
        value  =  value  <<  1 ;
    }
    return  value ;
}

int main(){

    int novoDim;
    

    dim = 4;
    alocacaoMemoria(dim);

    srand(time(NULL));
    inicializarMat(dim, mat1);
    printMat(dim, mat1);



    //Verifica se dim é potencia de 2 e se não for transforma em pot de 2
    int VerdOuFalso = function_ehPotenciaDeDois(dim);
    printf("Valor de verdoufalso: %d\n", VerdOuFalso);
    
    if(VerdOuFalso == 0){
        novoDim = proximaPotenciaDe2(dim);
        //alocacaoMemoria(novoDim, novaMat1);
        novaMat1 = (int **) malloc(sizeof(int*) * novoDim);
        for(int i = 0; i < novoDim; i++){
            novaMat1[i] = (int*) malloc(novoDim * sizeof(int));
        }
        if (novaMat1 == NULL) {printf("ERRO--malloc\n"); return 2;}
        //srand(time(NULL));
        inicializarMat2(novoDim, novaMat1);
        printMat(novoDim, novaMat1);
        completaMatrizes(dim, mat1, novaMat1);
        printMat(novoDim, novaMat1);
        //free(novaMat1);
    }
    


    free(mat1);
    free(novaMat1);
    return 0;

}
