#include <stdio.h>
#include <stdlib.h>

int main(void){

FILE *ifp, *ofp;
char *mode = "r";
char outputFilename[] = "resultado.txt";
int ch, y;
char rola[] = "rola";

    ifp = fopen("arquivo.txt", mode);

    if (ifp == NULL) {
    fprintf(stderr, "Erro ao abrir o arquivo.txt!\n");
    exit(1);
    }

ofp = fopen(outputFilename, "w");

    if (ofp == NULL) {
    fprintf(stderr, "Erro ao salvar o arquivo %s!\n", outputFilename);
    exit(1);
    }

    ch = 40;
    fputs(rola,ofp);
