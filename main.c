#include <stdio.h>
#include "ppm.h"
#include <string.h>
#include <unistd.h>
#include <math.h>


int main(int argc, char *argv[]){
	FILE *arquivo;
	char *formato=NULL, *input_a=NULL, *output_a=NULL, *imagem=NULL, opt;

while((opt = getopt(argc, argv, "i:o:f:")) != -1){

	switch(opt){
        case 'i':
		imagem = optarg;

		break;
        case 'o':
		output_a = optarg;
		input_a = NULL;
		break;
        case 'f':
		formato = optarg;
		
		break;
	case '?':
		break;
        default:
		printf("Argumento Invalido!\n");
		return -1;
    	}
}
	arquivo = fopen(imagem, "r");
	if(arquivo == NULL){
		printf("Imagem nao encontrada no sistema\n");
	}
	if(strcmp(formato, "ppm") == 0){ // caso a extensao da imagem seja ppm
		cabPPM imagemPPM;
		lerppm(arquivo, imagemPPM);		
	}
	fclose(arquivo);
	return 0;
}