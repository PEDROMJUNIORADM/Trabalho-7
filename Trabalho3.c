#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

#define TAM 100
#define NUM_THREADS 256

int tamColuna, tamLinha, qntdPalavras;
char Mat[TAM][TAM], MatMatches[TAM][TAM], MatResposta[TAM][TAM];

int getTamLinha(FILE *file);
int getTamColuna(FILE *file);
void makeMatriz(FILE *file, char (*matriz)[TAM][TAM], char mat[TAM][TAM], int *tamColuna, int *tamLinha, int *qntdPalavras);
void printaMatriz( char (*matriz)[TAM][TAM], int tamLinha, int tamColuna );
void putMatrizNoArquivo(FILE *file, char matriz[TAM][TAM], char mat[TAM][TAM], int qntdPalavras, int tamColuna, int tamLinha);
void *searchNaMatriz(void *vp_Value);


int main (int argc, char *argv[]){
   static const char filename[] = "file.txt";
   static const char filenameout[] = "resposta.txt";
   FILE *file = fopen ( filename, "r" );
   FILE *fileout = fopen (filenameout, "w");
   int i=0, j, num_Threads;
   pthread_t threads[NUM_THREADS];
   num_Threads = atoi(argv[1]);
	if( file == NULL ){
		fprintf(stdout, "Impossivel abrir arquivo.\n");
		return(-1);
	}
	else{
		//scanf("%d", &num_Threads);
		makeMatriz(file, &Mat, MatMatches, &tamColuna, &tamLinha, &qntdPalavras);
		while( i < num_Threads ){
			for( j = 0 ; j <  qntdPalavras/num_Threads ; j++ )
				pthread_create( &threads[i], NULL, searchNaMatriz, &MatMatches[j]);
			pthread_join( threads[i] , NULL );
			i++;
			for( j = qntdPalavras/num_Threads ; j <= qntdPalavras ; j++ )
				pthread_create( &threads[i], NULL, searchNaMatriz, &MatMatches[j]);
		pthread_exit(NULL);
		}
		putMatrizNoArquivo(fileout, Mat, MatMatches, qntdPalavras, tamColuna, tamLinha);
		fclose(file);
	}
	return 0;
}

void *searchNaMatriz(void *vp_Value){
	int i, k, j, l, o;
	char *charHelper = ((char *) vp_Value);
		for( k = 0 ; k < tamLinha ; k++ ){
			for( j = 0 ; j < tamColuna ; j++){
				if( Mat[k][j] == charHelper[k] )
				// Procura na direita // 
					if ( tamColuna > (strlen(charHelper)+j) ){ 
						for( l = 0 ; charHelper[l] == Mat[j+l][k]; l++) {
							if(charHelper[l+1]=='\0'){ 
								printf("Matched: %s em %d %d\n",charHelper, j, k);
								return;
							}
						}
					}
					// Procura na esquerda //
					if (0 <= ( j - strlen(charHelper) ) ) { 							
						for( l = 0 ; charHelper[l] == Mat[j-l][k] ; l++) {
							if(charHelper[l+1]=='\0'){
								printf("Matched: %s em %d %d\n",charHelper, j, k);
								return;
							}
						}
					}
					// Procura na Coluna baixo - cima//
					if ( tamLinha > (strlen(charHelper) + k) ) { 
						for( l = 0 ; charHelper[l] == Mat[j][k+l]; l++) {
							if(charHelper[l+1]=='\0'){
								printf("Matched: %s em %d %d\n",charHelper, j, k);
								return;
							}
						}
					}
					// Procura na Coluna cima - baixo //
					if (0 <= (k - strlen(charHelper)) ) { 
						for( l = 0; charHelper[l] == Mat[j][k-l]; l++) {
							if(charHelper[l+1]=='\0'){
								printf("Matched: %s em %d %d\n",charHelper, j, k);
								return;
								}
						}
					}
			}
		}
}

void putMatrizNoArquivo(FILE *file, char matriz[TAM][TAM], char mat[TAM][TAM], int qntdPalavras, int tamColuna, int tamLinha){
	int i,j;
	
	for( i = 0 ; i < tamLinha; i++ ){
		for( j = 0 ; j < tamColuna ; j++ )
			fprintf(file, "%c", matriz[i][j] );
	fprintf(file, "\n");
	}
		fprintf(file, "\nPalavras da matriz de matches\n");
	for( i = 0 ; i <= qntdPalavras ; i++ )
		fprintf(file, "%s\n", mat[i]);
}

void printaMatriz( char (*matriz)[TAM][TAM], int tamLinha, int tamColuna ){
	int i, j;
	for( i = 0 ; i < tamLinha ; i++ ){
		for( j = 0 ; j < tamColuna ; j++ )
			printf("%c", (*matriz)[i][j]);
		printf("\n");
	}
	printf("\n");
}

void makeMatriz(FILE *file, char (*matriz)[TAM][TAM], char mat[TAM][TAM], int *tamColuna, int *tamLinha, int *qntdPalavras){
	int tamLin = getTamLinha(file);
	int tamCol = getTamColuna(file);
	int qntPal = 0;
	*tamColuna = tamCol; *tamLinha = tamLin;
	*qntdPalavras = qntPal;
	int i, j;
	char dado, palavra[TAM];
	
	for( i = 0 ; i <= tamLin ; i++ ){
		if( i == tamLin ){
			while( fscanf(file, " %s", palavra) != EOF ){
				strcpy( mat[qntPal] , palavra );
				*qntdPalavras = qntPal++;
			}
			break;
		}
		for( j = 0 ; j < tamCol ; j++ ){
			fscanf(file, " %c", &dado);
			(*matriz)[i][j] = dado;
		}
	}
}

int getTamLinha(FILE *file){
	int tamLinha;
	fscanf(file, "%d", &tamLinha);
	return tamLinha;
}

int getTamColuna(FILE *file){
	int tamColuna;
	fscanf(file, "%d", &tamColuna);
	return tamColuna;
}

