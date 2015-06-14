#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 100

int getTamLinha(FILE *file);
int getTamColuna(FILE *file);
void makeMatriz(FILE *file, char (*matriz)[TAM][TAM], int *tamColuna, int *tamLinha);
void printaMatriz( char (*matriz)[TAM][TAM], int tamLinha, int tamColuna );

int main ( void )
{
   static const char filename[] = "file.txt";
   static const char filenameout[] = "resposta.txt";
   FILE *file = fopen ( filename, "r" );
   FILE *fileout = fopen (filenameout, "w");
   int tamColuna, tamLinha;
   char Mat[TAM][TAM];

	if( file == NULL ){
		fprintf(stdout, "Impossivel abrir arquivo.\n");
		return(-1);
	}
	else{
		makeMatriz(file, &Mat, &tamColuna, &tamLinha);
		printf("TamColuna: %d\n", tamColuna);
		printf("TamLinha: %d\n", tamLinha);
		printaMatriz(&Mat, tamLinha , tamColuna);
		fclose(file);
	}
	return 0;
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

void makeMatriz(FILE *file, char (*matriz)[TAM][TAM], int *tamColuna, int *tamLinha){
	int tamLin = getTamLinha(file);
	int tamCol = getTamColuna(file);
	*tamColuna = tamCol; *tamLinha = tamLin;
	int i, j;
	char dado;
	
	for( i = 0 ; i < tamLin ; i++ ){
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
