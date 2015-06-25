//[]----------------------------------------------------[]
//|  Trabalho 1 Sistemas Operacionais. 
//   Alunos: Leonardo Fuchs, Caique Minhare e Diogo Souza
//[]----------------------------------------------------[]

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Abrir arquivo
#include <string.h>
//#include <ctype.h> //Nao tenho certeza se precisa destas (Olhar testando.c)
//#include <stddef.h>
#include <assert.h> //Para o toupper

#define MAX 100 // Maior palavra = 47letras

//[]----------------------------------------------------[]
//|  Funcao que torna a palavra maiuscula
//[]----------------------------------------------------[]
char* strtoupper(char* s, int x) {
  assert(s != NULL);

  char* p = s;
  int aux = x;
  int cont = 0;
  for(cont = 0; cont < aux; cont++){
//  while (*p != '\0') {
    *p = toupper(*p);
    p++;
  }

  return s;
}

//[]----------------------------------------------------[]
//|  Funcao que transforma a matriz em sua transposta
//[]----------------------------------------------------[]
char transposto(int linha, int coluna, char matriz[linha][coluna])
{
	int i, j, aux;
  
  	for (i = 0; i < linha; i++) 
  	{
    	for (j = i + 1; j < coluna; j++) 
    	{
      		if (j != i) 
      		{
			aux = matriz[i][j];
   			matriz[i][j] = matriz[j][i];
   			matriz[j][i] = aux;
   			}
   		}
   	}
}


int main(int argc, char *argv[])
{

//[]----------------------------------------------------[]
//|  Declaracao de variaveis
//[]----------------------------------------------------[]
	int linha, coluna, numberOfThreads, i, j;
	char *read = "r", *write = "w";
	char outputFilename[] = "saida.txt";



//[]----------------------------------------------------[]
//|  Verificando abertura e salvamento do arquivo
//[]----------------------------------------------------[]
	FILE *input, *output;
	input = fopen("entrada.txt", read);

	if(input == NULL)
	{
		fprintf(stderr, "Erro ao abrir o arquivo entrada.txt!\n");
		exit(1);
	}

	output = fopen(outputFilename, write);

	if(output == NULL)
	{
		fprintf(stderr, "Erro ao salvar o arquivo saida.txt!\n");
	}

//[]----------------------------------------------------[]
//|  Escanear numero de linhas e de colunas no arquivo
//[]----------------------------------------------------[]
	fscanf(input, "%d", &linha);
	fscanf(input, "%d", &coluna);

//[]----------------------------------------------------[]
//|  Escanear matriz de palavras do arquivo
//[]----------------------------------------------------[]
	char cacaPalavra[linha+1][coluna];
	
	for(i = 0; i < linha; i++)
		for(j = 0; j < coluna; j++)
			fscanf(input, " %c", &cacaPalavra[i][j]);

	//Imprimir no arquivo para teste
	for(i = 0; i < linha; i++)
	{
		for(j = 0; j < coluna; j++)
			fprintf(output, "%c", cacaPalavra[i][j]);
		if(i + 1 != linha) //Gambiarra para nao fazer o ultimo \n
			fprintf(output, "\n");
	}

//[]----------------------------------------------------[]
//|  Escanear palavras procuradas do arquivo
// []----------------------------------------------------[]
	 int numeroPalavras = 0;
	 char c[MAX][0]; //Tentar c[MAX][0] e c[MAX];
	 while(1)
   	{
      c[numeroPalavras][0] = fgetc(input);
      if(feof(input))
      { 
         break ;
      }
      fprintf(output, "%c", c[numeroPalavras][0]);
      numeroPalavras++;

   	}
   //fprintf(output, "\n");

//[]----------------------------------------------------[]
//|  Fechar arquivo
//[]----------------------------------------------------[]

	fclose(input);
	fclose(output);


//[]----------------------------------------------------[]
//|  Criar matriz normal e matriz transposta
//[]----------------------------------------------------[]
/*
	char normal[linha][coluna], transposta[linha][coluna];
	for(i = 0; i < linha; i++)
		for(j = 0; j < coluna; j++)
			normal[linha][coluna] = cacaPalavra[linha][coluna];
	for(i = 0; i < linha; i++)
		for(j = 0; j < coluna; j++)
			transposta[linha][coluna] = transposto(linha, coluna, cacaPalavra[linha][coluna]);
*/

//[]----------------------------------------------------[]
//|  Escanear numero de threads fora do arquivo
//[]----------------------------------------------------[]
/*	numberOfThreads = atoi(argv[1]); 
	pthread_t threads[numberOfThreads];
//[]----------------------------------------------------[]
//|  Criacao das threads para as linhas
//[]----------------------------------------------------[]
	for(linha = 0; linha < numberOfThreads/2; linha++)
	{
		printf("Criando thread\n");
		status = pthread_create(&threads[linha], NULL, Funcao p/ varrer linha, Parametro que desconheco o que faz); // Metade varre linha e metade varre coluna(?)
		if(status != 0)
		{
			printf("Erro ao criar a thread\n");
			return 0;
		}
	}
//[]----------------------------------------------------[]
//|  Criacao das threads para as colunas
//[]----------------------------------------------------[]	
	for(coluna = 0; coluna < numberOfThreads/2; coluna++)
	{
		printf("Criando thread\n");
		status = pthread_create(&threads[coluna], NULL, Funcao p/ varrer coluna, Parametro que desconheco o que faz); // Metade varre linha e metade varre coluna(?)
		if(status != 0)
		{
			printf("Erro ao criar a thread\n");
			return 0;
		}
	}
*/
//[]----------------------------------------------------[]
//|  Varre linha com metade das threads                     
//[]----------------------------------------------------[]



//[]----------------------------------------------------[]
//|  Varre linha da transposta com metade das threads              
//[]----------------------------------------------------[]


return 0;
}
