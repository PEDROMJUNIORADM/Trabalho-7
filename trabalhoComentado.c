//[]----------------------------------------------------[]
//|  Trabalho 1 Sistemas Operacionais. 
//   Alunos: Leonardo Fuchs, Caique Minhare e Diogo Souza
//[]----------------------------------------------------[]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <stddef.h>
#include <assert.h>

#define TAM 100
#define NUM_THREADS 256


//[]----------------------------------------------------[]
//|  Declarações
//[]----------------------------------------------------[]
int tamColuna, tamLinha, qntdPalavras;
char Mat[TAM][TAM], MatMatches[TAM][TAM], MatResposta[TAM][TAM];

//[]----------------------------------------------------[]
//|  Funcoes para escanear o arquivo de entrada
//[]----------------------------------------------------[]
int getTamLinha(FILE *file);
int getTamColuna(FILE *file);
void makeMatriz(FILE *file, char (*matriz)[TAM][TAM], char mat[TAM][TAM], int *tamColuna, int *tamLinha, int *qntdPalavras);

//[]----------------------------------------------------[]
//|  Funcoes para printar a saida do arquivo
//[]----------------------------------------------------[]
void putMatrizNoArquivo(FILE *file, char matriz[TAM][TAM], char mat[TAM][TAM], int qntdPalavras, int tamColuna, int tamLinha);

//[]----------------------------------------------------[]
//|  Funcoes auxiliares
//[]----------------------------------------------------[]
void *searchNaMatriz(void *vp_Value);
void printaMatriz(char (*matriz)[TAM][TAM], int tamLinha, int tamColuna);
char* strtoupper(char* s, int x);

//[]----------------------------------------------------[]
//|  Inicio da Main
//[]----------------------------------------------------[]	
int main (int argc, char *argv[])
{

//[]----------------------------------------------------[]
//|  Declarações
//[]----------------------------------------------------[]	
   static const char filename[] = "file.txt"; // Arquivo de entrada se chama file.txt
   static const char filenameout[] = "resposta.txt"; // Arquivo de saida se chama resposta.txt

   FILE *file = fopen (filename, "r");
   FILE *fileout = fopen (filenameout, "w");

   int i = 0, j, num_Threads;

   pthread_t threads[NUM_THREADS]; 
 
   num_Threads = atoi(argv[1]);


//[]----------------------------------------------------[]
//|  Abertura do arquivo e salvamento no arquivo de saida
//[]----------------------------------------------------[]	
	if(file == NULL) //Conferindo se o arquivo foi aberto
	{
		fprintf(stdout, "Impossivel abrir arquivo.\n");
		return(-1);
	}
	else
	{
		makeMatriz(file, &Mat, MatMatches, &tamColuna, &tamLinha, &qntdPalavras); // Chama a funcao makeMatriz que absorve os dados do file.txt

		for(i = 0; i < num_Threads; i++)
		{
			for(j = 0; j <= qntdPalavras; j++) 
			{
				int flag = 0; //Possuiremos 3 possibilidades
				if(qntdPalavras > num_Threads) // Primeira possibilidade
				{
					if(flag <= num_Threads) //Incremento a flag, quando ela estiver no maximo, preciso esperar
					{
						pthread_create(&threads[i], NULL, searchNaMatriz, &MatMatches[j]);
						flag++;
					}
					else // Flag no maximo, zero o i e espero a primeira iteracao
					{
						i = 0;
						pthread_join(threads[i], NULL);
					}
				}

				else if(qntdPalavras == num_Threads){ //Segunda possibilidade
						pthread_create(&threads[i], NULL, searchNaMatriz, &MatMatches[j]);
						pthread_join(threads[i], NULL);}

				else{ //Terceira possibilidade
					pthread_create(&threads[i], NULL, searchNaMatriz, &MatMatches[j]);
					pthread_join(threads[i], NULL);}
			}
		}		
		putMatrizNoArquivo(fileout, Mat, MatMatches, qntdPalavras, tamColuna, tamLinha); // Armazena a resposta no arquivo de saida
		//printaMatriz(&Mat,tamLinha, tamColuna);
		fclose(file);
		pthread_exit(NULL);

		/* METODO ANTIGO DE CRIACAO
			while(i < num_Threads)
		{
			for(j = 0; j < qntdPalavras/num_Threads; j++) //?????
				pthread_create(&threads[i], NULL, searchNaMatriz, &MatMatches[j]);

			pthread_join(threads[i] , NULL);
			i++;

			for(j = qntdPalavras/num_Threads; j <= qntdPalavras; j++) //??????
				pthread_create(&threads[i], NULL, searchNaMatriz, &MatMatches[j]);

			//pthread_exit(NULL);
		}
		*/

	}
	return 0;
}
//[]----------------------------------------------------[]
//|  Fim da Main
//[]----------------------------------------------------[]	



//[]----------------------------------------------------[]
//|  Procura na matriz por uma palavra
//[]----------------------------------------------------[]	
void *searchNaMatriz(void *vp_Value)
{
	int i, k, j, l, o, contadorLetra, cont;
	char *charHelper = ((char *) vp_Value); //A palavra a ser pesquisada eh armazenada em charHelper

		for(k = 0; k < tamLinha; k++)
		{
			for(j = 0; j < tamColuna; j++)
			{
					// Cima para baixo// 
					if (tamColuna >= (strlen(charHelper)))
					{ 
						for(l = 0; charHelper[l] == Mat[j+l][k]; l++)
						{
							if(charHelper[l+1] == '\0')
							{
								contadorLetra = strlen(charHelper);
								strtoupper(charHelper, contadorLetra); // AQUI EU NAO SEI QUAL DEVE SER A PALAVRA A SER AUMENTADA, NAO DEVE SER ESSA
								printf("Matched: %s em %d %d\n", charHelper, j+1, k+1);
								for( cont = 0 ; cont < contadorLetra ; cont++ )
									Mat[j+cont][k] = toupper(Mat[j+cont][k]);
								return;
							}
						}
					}
					// Baixo para cima //
					if (0 <= (j - strlen(charHelper) ))
					{ 							
						for(l = 0; charHelper[l] == Mat[j-l][k]; l++)
						{
							if(charHelper[l+1]=='\0')
							{
								contadorLetra = strlen(charHelper);
								strtoupper(charHelper, contadorLetra); // AQUI EU NAO SEI QUAL DEVE SER A PALAVRA A SER AUMENTADA, NAO DEVE SER ESSA
								for( cont = 0 ; cont < contadorLetra ; cont++ )
									Mat[j-cont][k] = toupper(Mat[j-cont][k]);
								return;
							}
						}
					}
					//Esquerda para direita//
					if (tamLinha >= (strlen(charHelper) + k))
					{ 
						for(l = 0; charHelper[l] == Mat[j][k+l]; l++)
						{
							if(charHelper[l+1]=='\0')
							{
								contadorLetra = strlen(charHelper);
								strtoupper(charHelper, contadorLetra); // AQUI EU NAO SEI QUAL DEVE SER A PALAVRA A SER AUMENTADA, NAO DEVE SER ESSA
								printf("Matched: %s em %d %d\n",charHelper, j+1, k+1);
								for( cont = 0 ; cont < contadorLetra ; cont++ )
									Mat[j][k+cont] = toupper(Mat[j][k+cont]);
								return;
							}
						}
					}
					// Direita para esquerda //
					if (0 <= (k - strlen(charHelper)))
					{ 
						for(l = 0; charHelper[l] == Mat[j][k-l]; l++)
						{
							if(charHelper[l+1]=='\0')
							{
								contadorLetra = strlen(charHelper);
								strtoupper(charHelper, contadorLetra); // AQUI EU NAO SEI QUAL DEVE SER A PALAVRA A SER AUMENTADA, NAO DEVE SER ESSA
								printf("Matched: %s em %d %d\n",charHelper, j+1, k+1);
								for( cont = 0 ; cont < contadorLetra ; cont++ )
									Mat[j][k-cont] = toupper(Mat[j][k-cont]);
								return;
							}
						}
					}
			}
		}
}

//[]----------------------------------------------------[]
//|  Gera o arquivo de saida
//[]----------------------------------------------------[]	
void putMatrizNoArquivo(FILE *file, char matriz[TAM][TAM], char mat[TAM][TAM], int qntdPalavras, int tamColuna, int tamLinha)
{
	int i,j;
	
	for( i = 0 ; i < tamLinha; i++ )
	{
		for(j = 0; j < tamColuna; j++ )
			fprintf(file, "%c", matriz[i][j]);
	fprintf(file, "\n");
	}
	/*	fprintf(file, "\nPalavras da matriz de matches\n");
	for( i = 0 ; i <= qntdPalavras ; i++ )
		fprintf(file, "%s\n", mat[i]);
	*/
}

//[]----------------------------------------------------[]
//|  Imprime a matriz para verificacao
//[]----------------------------------------------------[]	
void printaMatriz(char (*matriz)[TAM][TAM], int tamLinha, int tamColuna)
{
	int i, j;
	for(i = 0 ; i < tamLinha ; i++)
	{
		for(j = 0; j < tamColuna; j++)
			printf("%c", (*matriz)[i][j]);
		printf("\n");
	}
	printf("\n");
}

//[]----------------------------------------------------[]
//|  Absorve o arquivo de entrada
//[]----------------------------------------------------[]	
void makeMatriz(FILE *file, char (*matriz)[TAM][TAM], char mat[TAM][TAM], int *tamColuna, int *tamLinha, int *qntdPalavras)
{
	int tamLin, tamCol, i, j, qntPal;
	char dado, palavra[TAM];

	tamLin = getTamLinha(file);
	tamCol = getTamColuna(file);

	qntPal = 0;
	
	*tamColuna = tamCol;
	*tamLinha = tamLin;
	*qntdPalavras = qntPal;
	
	for(i = 0 ; i <= tamLin ; i++)
	{
		if(i == tamLin) //significa que ja acabou a matriz e vamos comecar a scanear as palavras
		{
			while(fscanf(file, " %s", palavra) != EOF)
			{
				strcpy(mat[qntPal] , palavra); //mat recebe a palavra
				*qntdPalavras = qntPal++; //a quantidade de palavras eh incrementada
			}
			break; //Se saiu do loop eh porque acabaram as palavras
		}

		for(j = 0; j < tamCol; j++)
		{
			fscanf(file, " %c", &dado); //escaneio a linha da matriz
			(*matriz)[i][j] = dado; // salvo ela em matriz
		}

	}
}

int getTamLinha(FILE *file)
{
	int tamLinha;
	fscanf(file, "%d", &tamLinha);
	return tamLinha;
}

int getTamColuna(FILE *file)
{
	int tamColuna;
	fscanf(file, "%d", &tamColuna);
	return tamColuna;
}


char* strtoupper(char* s, int x) 
{
	char* p = s;
	int aux = x;
	int cont = 0;

	for(cont = 0; cont < aux; cont++)
	{
    	*p = toupper(*p);
    	p++;
  	}
  	return s;
}
