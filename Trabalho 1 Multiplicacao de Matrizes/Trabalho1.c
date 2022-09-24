//Trabalho 1 - Multiplicacao de Matrizes
//Aluno Marcus Vinícius Torres de Oliveira
//DRE: 118142223
//Disciplina: ED

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//Matrizes e matrizes temporárias caso seja preciso
int **mat1, **temp1;
int **mat2, **temp2;
int **mat_saida, **mat_saida_strassen;
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
                mat_saida[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

//Multiplica as matrizes temporarias da forma tradicional
void multMatrizTradicionalTemporarias(int dim){
    for(int i=0; i<dim;i++){
        for(int j=0; j<dim; j++){
            for(int k=0; k<dim; k++){
                mat_saida[i][j] += temp1[i][k] * temp2[k][j];
            }
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

//Função para determinar se um número é potencia de 2
//Retorna 0 se for falso e 1 se for verdadeiro
int ehPotenciaDeDois(int n){
    int num = n;
    if( n == 0){
        //printf("%d Não é potencia de dois \n", num);
        return 0; //False
    }

    while (n != 1) {
        if (n % 2 != 0){
            //printf("%d Não é potencia de dois \n", num);
            return 0;
        }
        n = n / 2;
    }
    //printf("%d É potencia de dois \n", num);
    return 1; //True
}

void completaMatrizes(int dimAntiga,int **mat, int **temp){
    for(int i=0; i<dimAntiga;i++){
        for(int j=0; j<dimAntiga; j++){
            temp[i][j] = mat[i][j];
        }
    }
}

//Multiplica as matrizes usando o método de Strassen
//As matrizes precisam ser potência de 2
int multMatrizStrassen(int **mat1, int **mat2, int **matS){
    //Checa se a matriz é potência de 2, se não for, completa ela com zeros

    int m1, m2, m3, m4, m5, m6, m7;
    
    m1 = (mat1[0][0] + mat1[1][1])*(mat2[0][0]+mat2[1][1]);
    m2 = (mat1[1][0]+mat1[1][1])*mat2[0][0];
    m3 = mat1[0][0]*(mat2[0][1]-mat2[1][1]);
    m4 = mat1[1][1]*(mat2[1][0]-mat2[0][0]);
    m5 = (mat1[0][0] + mat1[0][1])*mat2[1][1];
    m6 = (mat1[1][0] - mat1[0][0])*(mat2[0][0]+mat2[0][1]);
    m7 = (mat1[0][1] - mat1[1][1])*(mat2[1][0]+mat2[1][1]);

    matS[0][0] = m1+m4-m5+m7;
    matS[0][1] = m3+m5;
    matS[1][0] = m2+m4;
    matS[1][1] = m1+m3-m2+m6;

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

//Alocação de memoria de entrada
int alocacaoMemoria(int dim){
    mat1 = (int **) malloc(sizeof(int*) * dim);
    for(int i = 0; i < dim; i++){
        mat1[i] = (int*) malloc(dim * sizeof(int));
    }
    if (mat1 == NULL) {printf("ERRO--malloc\n"); return 2;}
    mat2 = (int **) malloc(sizeof(int*) * dim);
    for(int i = 0; i < dim; i++){
        mat2[i] = (int*) malloc(dim * sizeof(int));
    }
    if (mat2 == NULL) {printf("ERRO--malloc\n"); return 2;}
}

//Alocação de memoria temporaria
int alocacaoMemoriaTemporaria(int dim){
    temp1 = (int **) malloc(sizeof(int*) * dim);
    for(int i = 0; i < dim; i++){
        temp1[i] = (int*) malloc(dim * sizeof(int));
    }
    if (temp1 == NULL) {printf("ERRO--malloc\n"); return 2;}
    temp2 = (int **) malloc(sizeof(int*) * dim);
    for(int i = 0; i < dim; i++){
        temp2[i] = (int*) malloc(dim * sizeof(int));
    }
    if (temp2 == NULL) {printf("ERRO--malloc\n"); return 2;}
}

//Alocação de memoria de saida
int alocacaoMemoriaSaida(int dim){
    mat_saida = (int **) malloc(sizeof(int*) * dim);
    for(int i = 0; i < dim; i++){
        mat_saida[i] = (int*) malloc(dim * sizeof(int));
    }
    if (mat_saida == NULL) {printf("ERRO--malloc\n"); return 2;}
    mat_saida_strassen = (int **) malloc(sizeof(int*) * dim);
    for(int i = 0; i < dim; i++){
        mat_saida_strassen[i] = (int*) malloc(dim * sizeof(int));
    }
    if (mat_saida_strassen == NULL) {printf("ERRO--malloc\n"); return 2;}
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
        //Variavel para mudar a dimensão das matrizes de entrada caso seja necessário
        int novoDim = 0;
        //Verifica se dim é potencia de 2 e se não for transforma em pot de 2
        int VerdOuFalso = ehPotenciaDeDois(dim);

        //Determina se vai alocar memoria de entrada ou temporaria
        if(VerdOuFalso == 0){
            novoDim = proximaPotenciaDe2(dim);
            alocacaoMemoriaTemporaria(novoDim);
            alocacaoMemoriaSaida(novoDim);
            //dim = novoDim;
        }else{
            alocacaoMemoria(dim);
            alocacaoMemoriaSaida(dim);
        }

        //Ler as matrizes de entrada pelo Scanf
        for(int i=0; i<dim;i++){
            for(int j=0; j<dim; j++){
                scanf("%d",&mat1[i][j]);
            }
        }

        for(int i=0; i<dim;i++){
            for(int j=0; j<dim; j++){
                scanf("%d",&mat2[i][j]);
            }
        }

        //Caso não seja uma potencia de 2 a dim
        if(novoDim != 0){
            completaMatrizes(dim, mat1, temp1);
            completaMatrizes(dim, mat2, temp2);
            printf("Matriz 1:");
            printMat(novoDim, temp1);
            puts("------------------------");
            printf("Matriz 2:");
            printMat(novoDim, temp2);
            puts("--------------------------");
            multMatrizTradicionalTemporarias(novoDim);
            printf("Matriz de saída: (metodo tradicional)");
            printMat(dim, mat_saida);
            puts("---------------------------");
            multMatrizStrassen(temp1, temp2, mat_saida_strassen);
            printf("Matriz de saída: (metodo Strassem)");
            printMat(novoDim, mat_saida_strassen);
        }else{

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
            multMatrizStrassen(mat1, mat2, mat_saida_strassen);
            printf("Matriz de saída: (metodo Strassem)");
            printMat(dim, mat_saida_strassen);
        }

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
