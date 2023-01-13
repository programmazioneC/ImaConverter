#include <stdio.h>
#include<stdlib.h>
#include "img_manager.h"
struct image create_img(int h, int w) {
	struct  image img;
	int i;
	img.height = h;
	img.width = w;
	img.pixels = calloc(h, sizeof(struct pixels*));
	for ( i = 0; i < h; i++)
	{
		img.pixels[i] = calloc(w, sizeof(struct pixels**));
	}
	return img;
}
struct image get_empty_img() {
	struct image img;
	img.height = 0;
	img.width = 0;
	img.pixels = NULL;
	return img;
}
int average(struct pixel px) {
	return (px.R+px.G+px.B)/3;
}

struct image one_color_img(int h,int w, struct pixel color) {
	struct image img= create_img(h,w);
	int i, j;
	for ( i = 0; i < img.height; i++)
	{
		for ( j = 0; j < img.width; j++)
		{
			img.pixels[i][j] = color;
		}
	}
	return img;	
}
/*Prende in input un'immagine a colori e ritorna un'immagine in scala di grigi*/
struct image RGB_to_greyscale(struct image img){
	int i, j;

	for ( i = 0; i < img.height; i++)
	{
		for ( j = 0; j < img.width; j++)
		{
			int val = average(img.pixels[i][j]);
			img.pixels[i][j].R = (unsigned char)val;
			img.pixels[i][j].G = (unsigned char)val;
			img.pixels[i][j].B = (unsigned char)val;
		}
	}
	return img;
}

/*Prende in input un'immagine e ritorna la stessa immagine con l'aggiunta di un bordo spesso un pixel*/
/*mi ricordo che una matrice grande contiene una piccola
ha senso che io crei una matrice più grande di 2 colonne e 2 righe in più tutta del colore di cui voglio fare il bordo
*/
struct image add_border(struct image img, struct pixel color){
	struct image new_img = one_color_img(img.height+2,img.width+2,color);
	int i, j;
	/*NOTARE CHE USO h,w DELLA VECCHIA IMMAGINE
	E CHE SCORRO LA NUOVA SOMMANDO 1, IN QUESTO MODO
	NON SOVRASCIVO I BORDI*/
	for ( i = 0; i < img.height; i++)
	{
		for ( j = 0; j < img.width; j++)
		{
			new_img.pixels[i + 1][j + 1] = img.pixels[i][j];
		}
	}
	return new_img;
}

/*Prende in input un file e ritorna l'immagine letta*/
/*nel caso vada male deve ritornare una immagine vuota
con la matrice = NULL e altezza e profindità = 0, mi conviene fare una funzione d'appoggio*/
struct image load_image(char* filename){
	FILE* fr = fopen(filename,"r");
	int r,g, b ;
	int i, j, h, w;
	struct image img;
	if (fr != NULL) {
		
		if (fscanf(fr, "%d\t%d", &h, &w) == EOF) { return get_empty_img(); }
		/*devo allocare memoria in base alle dimensioni passate nel file: mi conviene farlo in una 
		funzione a parte che restituisca una matrice vuota con le dimensioni*/
		img = create_img(h, w);
		for ( i = 0; i < img.height; i++)
		{
			for ( j = 0; j < img.width; j++)
			{
				fscanf(fr, "%d\t%d\t%d", &r, &g, &b);
				img.pixels[i][j].R = (unsigned char)r;
				img.pixels[i][j].G = (unsigned char)g;
				img.pixels[i][j].B = (unsigned char)b;
			}
		}
		return img;
		fclose(fr);
	}
	else
	{
		return get_empty_img();
	}
}

/*Prende in input un'immagine e la salva su file*/
int save_image(struct image img, char* filename){
	int i, j;
	FILE* fw = fopen(filename, "w");
	if (fw != NULL) {
		fprintf(fw, "%d\t%d\n", img.height, img.width);
		for (i = 0; i < img.height; i++)
		{
			for (j = 0; j < img.width; j++)
			{
				fprintf(fw, "%d\t%d\t%d\n", img.pixels[i][j].R, img.pixels[i][j].G, img.pixels[i][j].B);
			}
		}
		return 1;
	}
	else
	{
		return 0;
	}
	
}
