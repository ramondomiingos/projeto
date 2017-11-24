#include "ppm.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>



void lerppm (FILE *arquivo, cabPPM cppm){
	int i, j;
	
	fscanf(arquivo, "%c", &cppm.tipo);
	fscanf(arquivo, "%i\n", &cppm.tipo2);
	fscanf(arquivo, "%i ", &cppm.alt);
	fscanf(arquivo, "%i\n", &cppm.larg);
	fscanf(arquivo, "%i\n", &cppm.qualidade);
	
	pixPPM **pixels = malloc(cppm.alt*sizeof(int*));
	if(pixels == NULL){
		printf("Erro na alocação");
	}
	for(i=0;i<cppm.alt;i++){	
		pixels[i] = malloc(cppm.larg*sizeof(int));
	}
	printf("leu cabeçario\n");

	for(i=0;i<cppm.alt;i++){
		for(j=0;j<cppm.larg;j++){
/*
		fread(&pixels[i][j].verde,sizeof(int),1,arquivo);
		fread(&pixels[i][j].vermelho,sizeof(int),1,arquivo);
		fread(&pixels[i][j].azul,sizeof(int),1,arquivo);
	
*/
		fscanf(arquivo,"%hhu",&pixels[i][j].verde);
		fscanf(arquivo,"%hhu",&pixels[i][j].vermelho);
		fscanf(arquivo,"%hhu",&pixels[i][j].azul);
		
		}
	}
printf("leu corpo\n");
	
	fclose(arquivo);


escreverppm(cppm,pixels);
escreverppmgray(cppm,pixels);

	

}
	
void escreverppm(cabPPM cppm, pixPPM **pixels){
	FILE *arq1;
	int i, j;
	printf("Entrou na escrever!\n");
	arq1 = fopen("imagem.ppm", "w");

	fprintf(arq1, "%c", cppm.tipo);
	fprintf(arq1, "%i\n", cppm.tipo2);
	fprintf(arq1, "%i ", cppm.alt);
	fprintf(arq1, "%i\n", cppm.larg);
	fprintf(arq1, "%i\n", cppm.qualidade);

	printf("Escreveu cabeçario!\n");




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
	printf("Entrou na escrever!\n");
	arq1 = fopen("imagemgray.ppm", "w");

	fprintf(arq1, "%c", cppm.tipo);
	fprintf(arq1, "%i\n", cppm.tipo2);
	fprintf(arq1, "%i ", cppm.alt);
	fprintf(arq1, "%i\n", cppm.larg);
	fprintf(arq1, "%i\n", cppm.qualidade);

	printf("Escreveu cabeçario!\n");




	for(i=0;i<cppm.alt;i++){
		for(j=0;j<cppm.larg;j++){

			//fprintf(arquivo, "%d\n%d\n%d\n",pixels[i][j].verde,pixels[i][j].vermelho ,pixels[i][j].azul);
/*	
		fwrite(&pixels[i][j].verde, sizeof(int),1,arquivo);
		fwrite(&pixels[i][j].vermelho, sizeof(int),1,arquivo);
		fwrite(&pixels[i][j].azul, sizeof(int),1,arquivo);
		*/
			int cinza ;
			cinza = (pixels[i][j].verde*0.30)+(pixels[i][j].vermelho*0.59)+(pixels[i][j].azul*0,11);
			//if(cinza >255){
			//	cinza=255;
			//}
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

gauss2(cppm,pixels);
}
/*
void gauss2(cabPPM cppm, pixPPM **pixels){

	int y,x,i,j,newpx;
	int filtro[5][5] = {{ 2,  4,  5,  4, 2 },
                        { 4,  9, 12,  9, 4 },
                        { 5, 12, 15, 12, 5 },
                        { 4,  9, 12,  9, 4 },
                        { 2,  4,  5,  4, 2 }};



pixPPM **gaussIMG = calloc(1,cppm.alt*sizeof(int*));
	if(gaussIMG == NULL){
		printf("Erro na alocação");
	}
	for(i=0;i<cppm.alt;i++){	
		gaussIMG[i] = calloc(1,cppm.larg*sizeof(int));
	}
	int row,col;

 int sum = 0;
 int div = 0;  
 printf("Entrou na Gauus 2\n");
	 for( row = 0; row < cppm.alt; row++ ){
        for( col = 0; col < cppm.larg; col++ ){
           

          

		    for( y = 0; y < 5; y++ ){
		            for( x = 0; x < 5; x++ )
		            {
		     
		            px =  read_pixel( img,  col + (x - 2), row + (y - 2) );
                    sum += ( px->red *  kernel[y][x] );
                    div += kernel[y][x];
		            }
		        }

		        newpx = sum / div;

		        gaussIMG[row][col].verde = newpx;
			gaussIMG[row][col].vermelho= newpx;
			gaussIMG[row][col].azul = newpx;

		       
        }
    }

    escreverppmaguss(cppm, gaussIMG);
}
*/


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
	/*int filtro[5][5] = {{2, 4 , 5, 4, 2},
						{4 , 9, 12, 9, 4},
						{5, 12, 15, 12,5},
						{4, 9, 12, 9, 4},
						{2, 4 , 5, 4, 2}};*/
	int filtro[3][3]={{1,1 ,1},
					{2, 40, 2},
					{1,1,1}};


pixPPM **gaussIMG = malloc(cppm.alt*sizeof(int*));
	if(gaussIMG == NULL){
		printf("Erro na alocação");
	}
	for(z=0;z<cppm.alt;z++){	
		gaussIMG[z] = malloc(cppm.larg*sizeof(int));
	}
	

 printf("Entrou na Gauus 2\n");

float novopixel ;
float peso ;

for(int i = 0; i < cppm.alt; i++){       
 for(int j = 0; j < cppm.larg; j++) {   
        novopixel = 0;
         peso = 0;
        for( int a = -1; a < 1; a++){               
            for( int b = -1; b < 1; b++){

                if((i+a >= 0 ) && (i+a < cppm.alt-1)){ 
                	if((j+b >= 0 ) && (j+b < cppm.larg-1)){


                   int one =i+a;
                   int two = j+b;
                   int valor = pixels[one][two].azul;
                   int valordofiltro= filtro[a+1][b+1];

                    novopixel = (novopixel + ( valor * valordofiltro));
                    peso = peso + valordofiltro;
              
                    }
                }   
                                  
             
            }
        }
     

               
			novopixel = (int)novopixel/peso;
			
        	gaussIMG[i][j].verde =novopixel;
			gaussIMG[i][j].vermelho = novopixel;
			gaussIMG[i][j].azul = novopixel;

    }
}

/*
	 for (int i = 0; i < cppm.alt; i++) {
		for (int j = 0; j < cppm.larg; j++) {
	
			int filter = 0 ;
			int div =0;
			for (int k = 0; k < 3; k++) {
				for (int l = 0; l < 3; l++) {
					if ( ((i-1+k) >= 0 && (j-1+l) >= 0) && (i+1 < cppm.alt && j+1 < cppm.larg) ) {
						int a = i-1+k;
						int b= j-1+l;
						filter =(int)filter +( pixels[a][b].verde * (filtro[k][l]));
						div= filtro[k][l]+div;
						
					}
				}
			}
			filter =(int) filter/div;
			
			gaussIMG[i][j].verde = filter;
			gaussIMG[i][j].vermelho = filter;
			gaussIMG[i][j].azul = filter;
			
		}

	}
	*/



    escreverppmaguss(cppm, gaussIMG);
   sobel(cppm, gaussIMG);

}





void escreverppmaguss(cabPPM cppm, pixPPM **gaussIMG){
	FILE *arq3;
	int i, j;
	printf("Entrou na escrever GAUSS!\n");
	arq3 = fopen("imagemgauss.ppm", "w");

	
	fprintf(arq3, "%c", cppm.tipo);
	fprintf(arq3, "%i\n", cppm.tipo2);
	fprintf(arq3, "%i ", cppm.alt);
	fprintf(arq3, "%i\n", cppm.larg);
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
	pixPPM **sobelIMG = malloc(cppm.alt*sizeof(int*));
	if(sobelIMG == NULL){
		printf("Erro na alocação");
	}
	for(int z=0;z<cppm.alt;z++){	
		sobelIMG[z] = malloc(cppm.larg*sizeof(int));
	}
	
			

for (int i=0; i < cppm.alt; i++) {
		for (int j=0; j < cppm.larg; j++) {
			aux_x = 0;
			aux_y = 0;
			for (int k=0; k < 3; k++) {
				for (int l=0; l < 3; l++) {
					if ( (i+k-1 < 0) || (j+l-1 < 0) || ((unsigned int)i-1+k >= cppm.alt) || ((unsigned int)j-1+l >= cppm.larg) ) {
						continue;
					}

					aux_x += (double) pixels[i+k-1][j+l-1].vermelho * sobelx[k][l];
					aux_y += (double) pixels[i+k-1][j+l-1].vermelho * sobely[k][l];
				
				}
			}
			unsigned char sobel = sqrt((aux_x * aux_x) + (aux_y * aux_y));
			
			if (sobel > cppm.qualidade) { 
				sobelIMG[i][j].vermelho = 255;
				sobelIMG[i][j].azul = 255;
				sobelIMG[i][j].verde = 255;
				
			}
			else {
				sobelIMG[i][j].vermelho  = sobel ;
				sobelIMG[i][j].azul = sobel ;
				sobelIMG[i][j].verde  = sobel ;
			}
		}
	}



  	escreversobel(cppm, sobelIMG);

}
void escreversobel(cabPPM cppm, pixPPM **sobelIMG){
	FILE *arq4;
	int i, j;
	printf("Entrou na escrever SOBEL!\n");
	arq4 = fopen("imagemsobel.ppm", "w");

	
	fprintf(arq4, "%c", cppm.tipo);
	fprintf(arq4, "%i\n", cppm.tipo2);
	fprintf(arq4, "%i ", cppm.alt);
	fprintf(arq4, "%i\n", cppm.larg);
	fprintf(arq4, "%i\n", cppm.qualidade);

	printf("Escreveu cabeçario!\n");




	for(i=0;i<cppm.alt;i++){
		for(j=0;j<cppm.larg;j++){

	fprintf(arq4,"%hhu\n",sobelIMG[i][j].vermelho);
	fprintf(arq4,"%hhu\n",sobelIMG[i][j].verde);
	fprintf(arq4,"%hhu\n",sobelIMG[i][j].azul);
	
		}
	}
		printf("Escreveu corpo! SOBEL!\n");


}