#include <stdio.h>

typedef struct pixel{
	unsigned char verde;
	unsigned char vermelho;
	unsigned char azul;
}pixPPM;

typedef struct CabePPM{
	char tipo;
	int tipo2;
	int alt;
	int larg;
	int qualidade;
}cabPPM;


void lerppm (FILE *arquivo, cabPPM cppm);
void escreverppm(cabPPM cppm, pixPPM **pixels);
void escreverppmgray(cabPPM cppm, pixPPM **pixels);
void gauss2(cabPPM cppm, pixPPM **pixels);
void escreverppmaguss(cabPPM cppm, pixPPM **pixels);
void escreversobel(cabPPM cppm, pixPPM **sobelIMG);
void sobel ( cabPPM cppm, pixPPM **pixels);