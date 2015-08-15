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

#define TAM 10000


//[]----------------------------------------------------[]
//|  Declarações globais
//[]----------------------------------------------------[]
int tamColuna, tamLinha, qntdPalavras;
char** MatReal;
char MatPalavras[TAM][TAM]; //Mat e MatMatches

//[]----------------------------------------------------[]
//|  Funcoes para escanear o arquivo de entrada
//[]----------------------------------------------------[]
int getTamLinha(FILE *file);
int getTamColuna(FILE *file);
void makeMatriz(FILE *file, int *tamColuna, int *tamLinha, int *qntdPalavras);

//[]----------------------------------------------------[]
//|  Funcoes para printar a saida do arquivo
//[]----------------------------------------------------[]
void putMatrizNoArquivo(FILE *file, int qntdPalavras, int tamColuna, int tamLinha);

//[]----------------------------------------------------[]
//|  Funcoes auxiliares
//[]----------------------------------------------------[]
void *searchNaMatriz(void *palavraBuscada);
//void printaMatriz(char (*matriz)[TAM][TAM], int tamLinha, int tamColuna);
char* strtoupper(char* s, int x);

/*--------------------------------------------------------------------*/

//[]----------------------------------------------------[]
//|  Inicio da Main
//[]----------------------------------------------------[]	
int main (int argc, char *argv[])
{

//[]----------------------------------------------------[]
//|  Declarações
//[]----------------------------------------------------[]	
   //static const char filename[] = "file.txt"; // Arquivo de entrada de teste que se chama file.txt
	static const char filenameout[] = "resposta.txt"; // Arquivo de saida se chama resposta.txt

	FILE *file = fopen (argv[1], "r");
	FILE *fileout = fopen (filenameout, "w");

	int i = 0, j, num_Threads;

//[]----------------------------------------------------[]
//|  Alertas caso o usuario invoque o programa com parametros errados ou faltosos
//[]----------------------------------------------------[]	
   	if (argc != 3)
   	{
		fprintf(stderr,"Os parametros de entrada estao incorretos, siga o modelo:\n./executavel nome_do_arquivo.txt <numero_de_threads>\n");
		return -1;
	}

	if (atoi(argv[2]) <= 0) {
		fprintf(stderr,"O argumento %d deve ser um numero inteiro e positivo.\n", atoi(argv[1]));
		return -1;
	}
 
	num_Threads = atoi(argv[2]); // O numero de threads que eh informado pelo usuario ao executar
	pthread_t threads[num_Threads]; 


//[]----------------------------------------------------[]
//|  Abertura do arquivo, criacao das threads e salvamento no arquivo de saida
//[]----------------------------------------------------[]	
	if(file == NULL) //Conferindo se o arquivo foi devidamente aberto
	{
		fprintf(stdout, "Impossivel abrir arquivo.\n");
		return(-1);
	}
	else
	{
		makeMatriz(file, &tamColuna, &tamLinha, &qntdPalavras); // Chama a funcao makeMatriz que absorve os dados do arquivo de entrada

		for(i = 0; i < num_Threads; i++)
		{
			for(j = 0; j <= qntdPalavras; j++) 
			{
				int flag = 0; //Possuiremos 3 possibilidades

				if(qntdPalavras > num_Threads) // Primeira possibilidade em que a quantidade de palavras eh maior que o numero de threads
				{
					if(flag <= num_Threads) //Incremento a flag, quando ela estiver no maximo, preciso esperar
					{
						pthread_create(&threads[i], NULL, searchNaMatriz, &MatPalavras[j]);
						flag++;
						pthread_join(threads[i], NULL);
					}
					else // Flag no maximo, reseto o i e espero a primeira thread ser concluida para reutiliza-la
					{
						i = 0;
						pthread_join(threads[i], NULL);
					}
				}

				else if(qntdPalavras == num_Threads) //Segunda possibilidade em que a quantidade de palavras eh igual o numero de threads
				{ 
						pthread_create(&threads[i], NULL, searchNaMatriz, &MatPalavras[j]);
						pthread_join(threads[i], NULL);
				}

				else //Terceira possibilidade onde a quantidade de palavras eh menor que o numero de threads
				{ 
					pthread_create(&threads[i], NULL, searchNaMatriz, &MatPalavras[j]);
					pthread_join(threads[i], NULL);
				}
			}
		}

		putMatrizNoArquivo(fileout, qntdPalavras, tamColuna, tamLinha); // Armazena a resposta no arquivo de saida

		fclose(file);
		pthread_exit(NULL);
	}
	return 0;
}
//[]----------------------------------------------------[]
//|  Fim da Main
//[]----------------------------------------------------[]	

/*--------------------------------------------------------------------*/

//[]----------------------------------------------------[]
//|  Funcao que procura na matriz por uma palavra especifica
//[]----------------------------------------------------[]	
void *searchNaMatriz(void *palavraBuscada)
{
	int i, k, j, l, o, contadorLetra, cont;
	char *charHelper = ((char *) palavraBuscada); //A palavra a ser pesquisada eh armazenada em charHelper
	
		for(k = 0; k < tamLinha; k++)
		{
			for(j = 0; j < tamColuna; j++)
			{

					// Pesquisa a palavra de cima para baixo// 
					if (tamColuna >= (strlen(charHelper)))
					{ 
						for(l = 0; charHelper[l] == tolower(MatReal[j+l][k]); l++)
						{
							if(charHelper[l+1] == '\0') //Confere se a palavra a ser pesquisada acabou
							{
								contadorLetra = strlen(charHelper);
								for(cont = 0 ; cont < contadorLetra ; cont++)
									MatReal[j+cont][k] = toupper(MatReal[j+cont][k]);
								return;
							}
						}
					}

					// Pesquisa a palavra de baixo para cima //
					if (0 <= (j - strlen(charHelper)))
					{ 							
						for(l = 0; charHelper[l] == tolower(MatReal[j-l][k]); l++)
						{
							if(charHelper[l+1]=='\0') //Confere se a palavra a ser pesquisada acabou
							{
								contadorLetra = strlen(charHelper);
								for(cont = 0 ; cont < contadorLetra ; cont++)
									MatReal[j-cont][k] = toupper(MatReal[j-cont][k]);
								return;
							}
						}
					}

					// Pesquisa a palavra da esquerda para a direita//
					if (tamLinha >= (strlen(charHelper) + k))
					{ 
						for(l = 0; charHelper[l] == tolower(MatReal[j][k+l]); l++)
						{
							if(charHelper[l+1]=='\0') //Confere se a palavra a ser pesquisada acabou
							{
								contadorLetra = strlen(charHelper);
								for(cont = 0 ; cont < contadorLetra ; cont++)
									MatReal[j][k+cont] = toupper(MatReal[j][k+cont]);
								return;
							}
						}
					}

					// Pesquisa a palavra da direita para a esquerda //
					if (0 <= (k - strlen(charHelper)))
					{ 
						for(l = 0; charHelper[l] == tolower(MatReal[j][k-l]); l++)
						{
							if(charHelper[l+1]=='\0') //Confere se a palavra a ser pesquisada acabou
							{
								contadorLetra = strlen(charHelper);
								for(cont = 0 ; cont < contadorLetra ; cont++)
									MatReal[j][k-cont] = toupper(MatReal[j][k-cont]);
								return;
							}
						}
					}
			}
		}
}

//[]----------------------------------------------------[]
//|  Funcao que gera o arquivo de saida
//[]----------------------------------------------------[]	
void putMatrizNoArquivo(FILE *file, int qntdPalavras, int tamColuna, int tamLinha)
{
	int i,j;
	
	for(i = 0 ; i < tamLinha; i++)
	{
		for(j = 0; j < tamColuna; j++)
		{
			fprintf(file, "%c", MatReal[i][j]);
		}
	fprintf(file, "\n");
	}
}
/*
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
*/

//[]----------------------------------------------------[]
//|  Funcao que absorve o arquivo de entrada
//[]----------------------------------------------------[]	
void makeMatriz(FILE *file, int *tamColuna, int *tamLinha, int *qntdPalavras)
{
	int i, j, tamLin, tamCol, qntPal = 0;
	char dado, palavra[TAM];

	tamLin = getTamLinha(file);
	tamCol = getTamColuna(file);
	
	*tamColuna = tamCol;
	*tamLinha = tamLin;
	*qntdPalavras = qntPal;
	
	char **MatReal = (char**)malloc(tamLin * sizeof(char*));
	for(i = 0; i < tamLin; i++)
		MatReal[i] = (char*)malloc(tamCol * sizeof(char));

	for(i = 0 ; i <= tamLin ; i++)
	{
		if(i == tamLin) //Simboliza que o caca-palavras se acabou e agora sera escaneado as palavras a serem buscadas
		{
			while(fscanf(file, " %s", palavra) != EOF)
			{
				strcpy(MatPalavras[qntPal], palavra);
				*qntdPalavras = qntPal++;
			}
			break; //Se o while acabou significa que todas as palavras ja foram lidas e armazenadas
		}

		for(j = 0; j < tamCol; j++)
		{
			fscanf(file, " %c", &dado); //Escaneando a linha do caca-palavras
			MatReal[i][j] = dado;
		}

	}
}

//[]----------------------------------------------------[]
//|  Funcao que escaneia o numero de linhas do caca palavras
//[]----------------------------------------------------[]	
int getTamLinha(FILE *file)
{
	int tamLinha;
	fscanf(file, "%d", &tamLinha);
	return tamLinha;
}

//[]----------------------------------------------------[]
//|  Funcao que escaneia o numero de colunas do caca palavras
//[]----------------------------------------------------[]
int getTamColuna(FILE *file)
{
	int tamColuna;
	fscanf(file, "%d", &tamColuna);
	return tamColuna;
}
