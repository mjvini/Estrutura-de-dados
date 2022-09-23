//Trabalho 1 - Multiplicacao de Matrizes
//Aluno Marcus Vinícius Torres de Oliveira
//DRE: 118142223
//Disciplina: ED

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//Matrizes
int **mat1, **temp1;
int **mat2, **temp2;
int **mat_saida;
int dim;//Dimensão das matrizes de entrada

//Inicializa as matrizes de entrada(aleatoriamente) e saída
void inicializarMat(int dim){
    for(int i=0; i<dim;i++){
        for(int j=0; j<dim; j++){
            int num_random = rand() % 100; //Gera um número aleatório entre 0 e 99
            mat1[i][j] = num_random;
            mat2[i][j] = (num_random * (i+1)) % 100;
            mat_saida[i][j] = 0;
        }
    }
}

//Multiplica as matrizes da forma tradicional
void multMatrizTradicional(int dim){
    for(int i=0; i<dim;i++){
        for(int j=0; j<dim; j++){
            for(int k=0; k<dim; k++){
                mat_saida[i][j] += mat1[i][j] * mat2[i][j];
            }
        }
    }
}

void printMat(int dim, int* mat){
    //printf("Matriz: \n");
    for(int i=0; i<dim;i++){
        printf("\n");
        for(int j=0; j<dim; j++){
            printf("%d ", mat[i*dim+j]);
        }
        //puts("");
    }
    printf("\n");
}

//Função para determinar se um número é potencia de 2 
int ehPotenciaDeDois(int n){
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

void completaMatrizes(int dim, int *mat1, int *mat2){

}

//Multiplica as matrizes usando o método de Strassen
//As matrizes precisam ser potência de 2
int multMatrizStrassen(int *mat1, int *mat2, int *matS,int dim){
    //Checa se a matriz é potência de 2, se não for, completa ela com zeros
    int dimensao = ehPotenciaDeDois(dim);
    if(dimensao == 0){
        

    }

    int m1, m2, m3, m4, m5, m6, m7;
    
    m1 = ((*mat1+ *(mat1+dim+1)) * (*mat2+ *(mat2+dim+1)));  //(mat1[0][0] + mat1[1][1])*(mat2[0][0]+mat2[1][1]);
    m2 = ((*(mat1+dim)+ *(mat1+dim-1)) * (*mat2));//(mat1[1][0]+mat1[1][1])*mat2[0][0]
    m3 = (*mat1) * (*(mat2+1) - *(mat2+dim+1));//mat1[0][0]*(mat2[0][1]-mat2[1][1])
    m4 = (*(mat1+dim+1))* (*(mat2+dim) - *mat2);//mat1[1][1]*(mat2[1][0]-mat2[0][0])
    m5 = (*mat1+ *(mat1+1))*(*mat2+*(mat2+1));//(mat1[0][0] + mat1[0][1])*mat2[1][1]
    m6 = (*(mat1+dim)-*mat1)*(*mat2+ *(mat2+1));//(mat1[1][0] - mat1[0][0])*(mat2[0][0]+mat2[0][1])
    m7 = (*(mat1+1)- *(mat1+dim+1))*(*(mat2+dim)+ *(mat2+dim+1));//(mat1[0][1] - mat1[1][1])*(mat2[1][0]+mat2[1][1])

    printf("m1 = %d\n", m1);
    printf("m2 = %d\n", m2);
    printf("m3 = %d\n", m3);
    printf("m4 = %d\n", m4);
    printf("m5 = %d\n", m5);
    printf("m6 = %d\n", m6);
    printf("m7 = %d\n", m7);
    printf("matS = %d\n", *matS);
    printf("matS = %d\n", (*matS+1));
    printf("matS = %d\n", (*matS+dim));
    printf("matS = %d\n", (*matS+dim+1));

    *matS = (*matS)+m1+m4-m5+m7; //matS[0][0] = m1+m4-m5+m7
    *(matS+1) = *(matS+1)+m3+m5; //matS[0][1] = m3+m5
    *(matS+dim) = *(matS+dim)+m2+m4;//matS[1][0] = m2+m4
    *(matS+dim+1) = *(matS+dim+1)+m1+m3-m2+m6;//matS[1][1] = m1+m3-m2+m6

    return 1; //Tudo certo
}

//Retorna a potencia de 2 mais próxima 
int  proximaPotenciaDe2 ( unsigned  int  x ){
    int  value  =  1 ;

    while  ( value  <=  x){
        value  =  value  <<  1 ;
    }
    return  value ;
}

int alocacaoMemoria(int dim){
    mat1 = (int *) malloc(sizeof(int) * dim * dim);
    if (mat1 == NULL) {printf("ERRO--malloc\n"); return 2;}
    mat2 = (int *) malloc(sizeof(int) * dim * dim);
    if (mat2 == NULL) {printf("ERRO--malloc\n"); return 2;}
    mat_saida = (int *) malloc(sizeof(int) * dim * dim);
    if (mat_saida == NULL) {printf("ERRO--malloc\n"); return 2;}
}

int main(int argc, char* argv[]){
    
    //Leitura dos parametros de entrada
    /*
    if(argc<2) {
      fprintf(stderr,"Digite: %s <dimensao da matriz> \n", argv[0]); //argv[0] trás o nome do programa
      //return 1;
    }
    */
    //Nenhum argumento foi passado, caso 2
    if(argc == 1){
        printf("Cole aqui a dimensão e as matrizes: \n");
        scanf("%d\n", &dim);

        //Alocação de memoria
        //alocacaoMemoria();
        int novoDim;
        //Verifica se dim é potencia de 2 e se não for transforma em pot de 2
        int VerdOuFalso = ehPotenciaDeDois(dim);
        if(VerdOuFalso == 0){
        novoDim = proximaPotenciaDe2(dim);
        alocacaoMemoria(novoDim);
        dim = novoDim;
        }else{
            alocacaoMemoria(dim);
        }

        //Ler as matrizes de entrada pelo Scanf
        for(int i=0; i<dim;i++){
            for(int j=0; j<dim; j++){
                scanf("%d",&mat1[i*dim+j]);
            }
        }

        for(int i=0; i<dim;i++){
            for(int j=0; j<dim; j++){
                scanf("%d",&mat2[i*dim+j]);
            }
        }

        //Prints
        printf("dim: %d\n", dim);
        printf("Matriz 1:");
        printMat(dim, mat1);
        puts("------------------------");
        printf("Matriz 2:");
        printMat(dim, mat2);

        puts("--------------------------");

        multMatrizTradicional(dim);
        printf("Matriz de saída: (metodo tradicional)");
        printMat(dim, mat_saida);

        puts("---------------------------");

        multMatrizStrassen(mat1, mat2, mat_saida, dim);
        printf("Matriz de saída: (metodo Strassem)");
        printMat(dim, mat_saida);


        return 1;
    }
    
    if(argc < 2){ //Caso 1, um argumento foi passado
        fprintf(stderr, "Digite: %s <dimensao da matriz>\n", argv[0]); //argv[0] trás o nome do programa
        return 2;
    }
        //Armazena a dimensão passada pelo argumento
        dim = atoi(argv[1]);

        //Alocação de memoria
        alocacaoMemoria(dim);
        
        //Inicializa as matrizes de entrada com números aleatórios
        inicializarMat(dim);

        //Prints
        printf("dim: %d\n", dim);
        printf("Matriz 1:");
        printMat(dim, mat1);
        puts("------------------------");
        printf("Matriz 2:");
        printMat(dim, mat2);

        puts("--------------------------");

        multMatrizTradicional(dim);
        printf("Matriz de saída (metodo tradicional):");
        printMat(dim, mat_saida);

        //return 2;
    //}
    /*
    dim = atoi(argv[1]);

    //Inicialização das matrizes com números aleatórios
    srand(time(NULL));
    inicializarMat(dim);

    //Prints
    printf("dim: %d\n", dim);
    printf("Matriz 1:");
    printMat(dim, mat1);
    puts("------------------------");
    printf("Matriz 2:");
    printMat(dim, mat2);

    puts("--------------------------");

    multMatrizTradicional(dim);
    printf("Matriz de saída:");
    printMat(dim, mat_saida);
    */

    //Libera a memoria
    free(mat1);
    free(mat2);
    free(mat_saida);

    return 0;
}
