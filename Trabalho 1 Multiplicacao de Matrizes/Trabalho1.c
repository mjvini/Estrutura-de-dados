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

//Inicializa as matrizes de entrada(aleatoriamente) e saída = 0
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

//Alocação de memoria de entrada
int **alocacaoMemoria(int dim){
    int **matTemp = (int **) malloc(sizeof(int*) * dim);
    for(int i = 0; i < dim; i++){
        matTemp[i] = (int*) malloc(sizeof(int*) * dim);
    }
    return matTemp;
}

//Gerar alocação de matrizes
void gerarAlocacao(int dim){
    mat1 = alocacaoMemoria(dim);
    mat2 = alocacaoMemoria(dim);
    mat_saida = alocacaoMemoria(dim);
    mat_saida_strassen = alocacaoMemoria(dim);
}

//Gerar alocação de matrizes temporárias
void gerarAlocacaoTemp(int dim){
    temp1 = alocacaoMemoria(dim);
    temp2 = alocacaoMemoria(dim);
    mat_saida = alocacaoMemoria(dim);
    mat_saida_strassen = alocacaoMemoria(dim);
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

void printMat(int dim, int **mat){
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

//Adição das matrizes de Strassen
int **adicao(int **mat1, int **mat2, int dim){

    int **matTemp = alocacaoMemoria(dim);
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            matTemp[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
    return matTemp;
}

//Subtração das matrizes de Strassen
int **subtracao(int **mat1, int **mat2, int dim){
    
    int **matTemp = alocacaoMemoria(dim);
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            matTemp[i][j] = mat1[i][j] - mat2[i][j];
        }
    }
    return matTemp;
}

//Multiplica as matrizes usando o método de Strassen
//As matrizes precisam ser potência de 2
int **multMatrizStrassen(int **mat1, int **mat2, int dim){
	int **matSaida = alocacaoMemoria(dim);
	int n = dim/2;

  	if (dim == 1) {
    	int **C = alocacaoMemoria(1);
    	C[0][0] = mat1[0][0] * mat2[0][0];
    	return C;
	}
	else{
		int **A11 = alocacaoMemoria(n);
		int **A12 = alocacaoMemoria(n);
		int **A21 = alocacaoMemoria(n);
		int **A22 = alocacaoMemoria(n);
		int **B11 = alocacaoMemoria(n);
		int **B12 = alocacaoMemoria(n);
		int **B21 = alocacaoMemoria(n);
		int **B22 = alocacaoMemoria(n);

		for(int i=0; i<n; i++) {
		    for(int j=0; j<n; j++) {
		        A11[i][j] = mat1[i][j];
		        A12[i][j] = mat1[i][n+j];
		        A21[i][j] = mat1[n+i][j];
		        A22[i][j] = mat1[n+i][n+j];
		        B11[i][j] = mat2[i][j];
		        B12[i][j] = mat2[i][n+j];
		        B21[i][j] = mat2[n+i][j];
		        B22[i][j] = mat2[n+i][n+j];
	   		}
		}

		int **m1 = multMatrizStrassen(A11, subtracao(B12, B22, n), n);
		int **m2 = multMatrizStrassen(adicao(A11, A12, n), B22, n);
		int **m3 = multMatrizStrassen(adicao(A21, A22, n), B11, n);
		int **m4 = multMatrizStrassen(A22, subtracao(B21, B11, n), n);
		int **m5 = multMatrizStrassen(adicao(A11, A22, n), adicao(B11, B22, n), n);
		int **m6 = multMatrizStrassen(subtracao(A12, A22, n), adicao(B21, B22, n), n);
		int **m7 = multMatrizStrassen(subtracao(A11, A21, n), adicao(B11, B12, n), n);

		int **C11 = subtracao(adicao(adicao(m5, m4, n), m6, n), m2, n);
		int **C12 = adicao(m1, m2, n);
		int **C21 = adicao(m3, m4, n);
		int **C22 = subtracao(subtracao(adicao(m5, m1, n), m3, n), m7, n);

		for(int i = 0; i < n; i++) {
		    for(int j = 0; j < n; j++) {
		        matSaida[i][j] = C11[i][j];
		        matSaida[i][j+n] = C12[i][j];
		        matSaida[n+i][j] = C21[i][j];
		        matSaida[n+i][n+j] = C22[i][j];
		    }
		}
	
		return matSaida;
	}
}

//Retorna a potencia de 2 mais próxima 
int  proximaPotenciaDe2 ( unsigned  int  x ){
    int  value  =  1 ;

    while  ( value  <=  x){
        value  =  value  <<  1 ;
    }
    return  value ;
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
        printf("aqui");
        //Verifica se dim é potencia de 2 e se não for transforma em pot de 2
        int VerdOuFalso = ehPotenciaDeDois(dim);
        //printf("aqui");

        //Determina se vai alocar memoria de entrada ou temporaria
        if(VerdOuFalso == 0){
            novoDim = proximaPotenciaDe2(dim);
            gerarAlocacao(novoDim);
            dim = novoDim;
        }else{
            gerarAlocacaoTemp(dim);
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
            mat_saida_strassen = multMatrizStrassen(temp1, temp2, novoDim);
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
            //mat_saida_strassen = multMatrizStrassen(mat1, mat2, dim);
            printf("Matriz de saída: (metodo Strassem)");
            //printMat(dim, mat_saida_strassen);
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
        mat1 = alocacaoMemoria(dim);
        mat2 = alocacaoMemoria(dim);
        mat_saida = alocacaoMemoria(dim);
        mat_saida_strassen = alocacaoMemoria(dim);
        
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
