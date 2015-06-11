#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){

FILE *ifp, *ofp;
char *mode = "r";
char outputFilename[] = "resultado.txt";
int ch, y, count, count1;

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

    // Escaneia o arquivo ifp e salva os valores da coluna e linha //
    fscanf(ifp,"%d %d",&ch,&y);
    char matAux[ch+1][y];
    for(count=0 ; count < ch ; count++)
        for(count1=0 ; count1 < y ; count1++)
            fscanf(ifp, " %c", &matAux[count][count1]);

    for(count=0 ; count < ch ; count++){
        for(count1=0 ; count1 < y ; count1++)
            fprintf(ofp, "%c", matAux[count][count1]);
        fprintf(ofp,"\n");
    }

    return 0;
}
