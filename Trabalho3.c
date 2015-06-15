#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 100

int getTamLinha(FILE *file);
int getTamColuna(FILE *file);
void makeMatriz(FILE *file, char (*matriz)[TAM][TAM], char mat[TAM][TAM], int *tamColuna, int *tamLinha, int *qntdPalavras);
void printaMatriz( char (*matriz)[TAM][TAM], int tamLinha, int tamColuna );
void putMatrizNoArquivo(FILE *file, char matriz[TAM][TAM], char mat[TAM][TAM], int qntdPalavras, int tamColuna, int tamLinha);

int main ( void )
{
   static const char filename[] = "file.txt";
   static const char filenameout[] = "resposta.txt";
   FILE *file = fopen ( filename, "r" );
   FILE *fileout = fopen (filenameout, "w");
   int tamColuna, tamLinha, qntdPalavras;
   char Mat[TAM][TAM], MatMatches[TAM][TAM];
   int i;

	if( file == NULL ){
		fprintf(stdout, "Impossivel abrir arquivo.\n");
		return(-1);
	}
	else{
		makeMatriz(file, &Mat, MatMatches, &tamColuna, &tamLinha, &qntdPalavras);
		//printaMatriz(&Mat, tamLinha, tamColuna);
		putMatrizNoArquivo(fileout, Mat, MatMatches, qntdPalavras, tamColuna, tamLinha);
		fclose(file);
	}
	return 0;
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
		if ( i == tamLin ){
			while( fscanf(file, " %s", palavra) != EOF ){
				strcpy( mat[qntPal] , palavra );
				*qntdPalavras = qntPal++;
			}
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
