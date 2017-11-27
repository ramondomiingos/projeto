#include "ppm.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#define PI 3.141592
void lerppm (FILE *arquivo, cabPPM cppm){
	int i, j;
	fscanf(arquivo, "%c", &cppm.tipo);
	fscanf(arquivo, "%i\n", &cppm.tipo2);
	fscanf(arquivo, "%i ", &cppm.larg);
	fscanf(arquivo, "%i\n", &cppm.alt);
	fscanf(arquivo, "%i\n", &cppm.qualidade);

	pixPPM **pixels = malloc(cppm.alt*sizeof(pixPPM*));
	if(pixels == NULL){
		printf("Erro na alocação");
	}
	for(i=0;i<cppm.alt;i++){	
		pixels[i] = malloc(cppm.larg*sizeof(pixPPM));
	}
	

	for(i=0;i<cppm.alt;i++){
		for(j=0;j<cppm.larg;j++){
		fscanf(arquivo,"%hhu",&pixels[i][j].verde);
		fscanf(arquivo,"%hhu",&pixels[i][j].vermelho);
		fscanf(arquivo,"%hhu",&pixels[i][j].azul);
		}
	}

fclose(arquivo);
escreverppm(cppm,pixels);
gauss2(cppm,pixels);
//escreverppmgray(cppm,pixels);
}
	
void escreverppm(cabPPM cppm, pixPPM **pixels){
	FILE *arq1;
	int i, j;
	
	arq1 = fopen("imagem.ppm", "w");

	fprintf(arq1, "%c", cppm.tipo);
	fprintf(arq1, "%i\n", cppm.tipo2);
	fprintf(arq1, "%i ", cppm.larg);
	fprintf(arq1, "%i\n", cppm.alt);
	fprintf(arq1, "%i\n", cppm.qualidade);






	for( int i=0;i<cppm.alt;i++){
		for( int j=0;j<cppm.larg;j++){


			fprintf(arq1,"%d\n",pixels[i][j].verde);
			fprintf(arq1,"%d\n",pixels[i][j].vermelho);
			fprintf(arq1,"%d\n",pixels[i][j].azul);
			
		}
	}
		printf("Escreveu corpo!\n");
		
}


void escreverppmgray(cabPPM cppm, pixPPM **pixels){
	FILE *arq1;
	int i, j;

	arq1 = fopen("imagemgray.ppm", "w");

	fprintf(arq1, "%c", cppm.tipo);
	fprintf(arq1, "%i\n", cppm.tipo2);
	fprintf(arq1, "%i ", cppm.larg);
	fprintf(arq1, "%i\n", cppm.alt);
	fprintf(arq1, "%i\n", cppm.qualidade);

	

	for(i=0;i<cppm.alt;i++){
		for(j=0;j<cppm.larg;j++){

			int cinza ;
			cinza = (pixels[i][j].verde*0.30)+(pixels[i][j].vermelho*0.59)+(pixels[i][j].azul*0,11);
			
			pixels[i][j].verde = cinza;
			pixels[i][j].vermelho= cinza;
			pixels[i][j].azul = cinza;


fprintf(arq1,"%d\n",pixels[i][j].verde);
fprintf(arq1,"%d\n",pixels[i][j].vermelho);
fprintf(arq1,"%d\n",pixels[i][j].azul);



			//fprintf(arq1,"%d\n",pixels[i][j].verde+(pixels[i][j].verde*0.30));
			//fprintf(arq1,"%d\n",pixels[i][j].vermelho+(pixels[i][j].vermelho*0.59));
			//fprintf(arq1,"%d\n",pixels[i][j].azul+(pixels[i][j].azul*0,11));
			
		}
	}
		printf("Escreveu corpo! Gray\n");


}

void gauss2(cabPPM cppm, pixPPM **pixels){

	int z;
	float normalizationFactor = 16;
	/* int filtro[7][7] = {{1, 1, 2, 2, 2, 1, 1},
	 					{1, 3, 4, 5, 4, 3, 1},
	 					{2, 4, 7, 8, 7, 4, 2}, 
						{2, 5, 8, 10, 8, 5, 2}, 
						{2, 4, 7, 8, 7, 4, 2}, 
						{1, 3, 4, 5, 4, 3, 1}, 
						{1, 1, 2, 2, 2, 1, 1}};*/
	int filtro[5][5] = {{2, 4 , 5, 4, 2},
						{4 , 9, 12, 9, 4},
						{5, 12, 15, 12,5},
						{4, 9, 12, 9, 4},
						{2, 4 , 5, 4, 2}};
	/*int filtro[3][3]={{1,1 ,1},
					{2, 40, 2},
					{1,1,1}};*/


pixPPM **gaussIMG = malloc(cppm.alt*sizeof(pixPPM*));
	if(gaussIMG == NULL){
		printf("Erro na alocação");
	}
	for(z=0;z<cppm.alt;z++){	
		gaussIMG[z] = malloc(cppm.larg*sizeof(int));
	}
	

 printf("Entrou na Gauus \n");

float novopixel ;
float peso ;

for(int i = 0; i < cppm.alt; i++){       
 for(int j = 0; j < cppm.larg; j++) {   
        novopixel = 0;
         peso = 0;
        for( int a = -2; a < 2; a++){               
            for( int b = -2; b < 2; b++){

                if((i+a >= 0 ) && (i+a < cppm.alt-2)){ 
                	if((j+b >= 0 ) && (j+b < cppm.larg-2)){


                   int one =i+a;
                   int two = j+b;
                   int valor = pixels[one][two].azul;
                   int valordofiltro= filtro[a+2][b+2];

                    novopixel = (novopixel + ( valor * valordofiltro));
                    peso = peso + valordofiltro;
              
                    }
                }   
            }
        }           
			novopixel = (int)novopixel/159;
			
        	gaussIMG[i][j].verde =novopixel;
			gaussIMG[i][j].vermelho = novopixel;
			gaussIMG[i][j].azul = novopixel;

    }
}
  //  escreverppmaguss(cppm, gaussIMG);
   sobel(cppm, gaussIMG);

}





void escreverppmaguss(cabPPM cppm, pixPPM **gaussIMG){
	FILE *arq3;
	int i, j;
	printf("Entrou na escrever GAUSS!\n");
	arq3 = fopen("imagemgauss.ppm", "w");

	
	fprintf(arq3, "%c", cppm.tipo);
	fprintf(arq3, "%i\n", cppm.tipo2);
	fprintf(arq3, "%i ", cppm.larg);
	fprintf(arq3, "%i\n", cppm.alt);
	fprintf(arq3, "%i\n", cppm.qualidade);

	printf("Escreveu cabeçario!\n");




	for(i=0;i<cppm.alt;i++){
		for(j=0;j<cppm.larg;j++){

	fprintf(arq3,"%d\n",gaussIMG[i][j].verde);
	fprintf(arq3,"%d\n",gaussIMG[i][j].vermelho);
	fprintf(arq3,"%d\n",gaussIMG[i][j].azul);
	
		}
	}
		printf("Escreveu corpo! GAUS!\n");

fclose(arq3);
free(gaussIMG);

}

void sobel ( cabPPM cppm, pixPPM **pixels){

	int sobelx[3][3]={{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};
                       
	int sobely[3][3]={{1, 2, 1}, {0, 0, 0}, {1, -2, -1}};			

			double aux_x = 0;
			double aux_y = 0;
	pixPPM **sobelIMG = malloc(cppm.alt*sizeof(pixPPM*));
	if(sobelIMG == NULL){
		printf("Erro na alocação");
	}
	for(int z=0;z<cppm.alt;z++){	
		sobelIMG[z] = malloc(cppm.larg*sizeof(pixPPM));
	}
	
for (int i=1; i < cppm.alt-1; i++) {
		for (int j=1; j < cppm.larg-1; j++) {
			aux_x = 0;
			aux_y = 0;
			for (int k=0; k < 3; k++) {
				for (int l=0; l < 3; l++) {
					

					aux_x += pixels[i+k-1][j+l-1].vermelho * sobelx[k][l];
					aux_y += pixels[i+k-1][j+l-1].vermelho * sobely[k][l];
				
				}
			}
			double sobel = abs(sqrt((aux_x * aux_x) + (aux_y * aux_y)));
			
			
				sobelIMG[i][j].vermelho = sobel;
				sobelIMG[i][j].azul = sobel;
				sobelIMG[i][j].verde = sobel;
				
			
			
	}
	}

  	escreversobel(cppm, sobelIMG);

}

void escreversobel(cabPPM cppm, pixPPM **sobelIMG){
	FILE *arq4;
	int i, j;

	arq4 = fopen("imagemsobel.ppm", "w");

	
	fprintf(arq4, "%c", cppm.tipo);
	fprintf(arq4, "%i\n", cppm.tipo2);
	fprintf(arq4, "%i ", cppm.larg);
	fprintf(arq4, "%i\n", cppm.alt);
	fprintf(arq4, "%i\n", cppm.qualidade);



	for(i=0;i<cppm.alt;i++){
		for(j=0;j<cppm.larg;j++){

	fprintf(arq4,"%hhu\n",sobelIMG[i][j].vermelho);
	fprintf(arq4,"%hhu\n",sobelIMG[i][j].verde);
	fprintf(arq4,"%hhu\n",sobelIMG[i][j].azul);
	
		}
	}
		printf("Escreveu corpo! SOBEL!\n");

fclose(arq4);
FILE *arq5;
arq5 = fopen("imagempbm.pbm", "w");
	fprintf(arq5, "P3");
	fprintf(arq5, "%i ", cppm.larg);
	fprintf(arq5, "%i\n", cppm.alt);
	fprintf(arq5, "1\n");

	for(i=0;i<cppm.alt;i++){
		for(j=0;j<cppm.larg;j++){
			if(sobelIMG[i][j].vermelho >= 150){
	fprintf(arq5,"1\n");
	fprintf(arq5,"1\n");
	fprintf(arq5,"1\n");
			}else{
	fprintf(arq5,"0\n");
	fprintf(arq5,"0\n");
	fprintf(arq5,"0\n");
			}
	
	
		}
	}
}