#include "img_manager.h"
#include <stdlib.h>
#include <stdio.h>

struct image empty_img() {
	struct image img;
	img.height = 0;
	img.width = 0;
	img.pixels = NULL;
	return img;
}
static int avg(struct pixel px) {
	return (px.R+px.G+px.B) / 3;
}
struct image img_create(int h,int w){
	struct image img;
	img.height = h;
	img.width = w;
	int i;
	img.pixels = calloc(h, sizeof(struct pixel*));
	for ( i = 0; i < img.height; i++)
	{
		img.pixels[i] = calloc(w, sizeof(struct pixel**));
	}
	return img;
}
struct image one_color_img(int h,int w,struct pixel px) {
	struct image img = img_create(h, w);
	int i, j;
	for ( i = 0; i < h; i++)
	{
		for ( j = 0; j < w; j++)
		{
			img.pixels[i][j].R = px.R;
			img.pixels[i][j].G = px.G;
			img.pixels[i][j].B = px.B;
		}
	}
	return img;
}
/*Prende in input un'immagine a colori e ritorna un'immagine in scala di grigi*/
struct image RGB_to_greyscale(struct image img) {
	int i, j;
	for ( i = 0; i < img.height; i++)
	{
		for ( j = 0; j < img.width; j++)
		{
			int val = avg(img.pixels[i][j]);
			img.pixels[i][j].R = val;
			img.pixels[i][j].G = val;
			img.pixels[i][j].B = val;

		}
	}
	return img;
}
/*posso creare una matrice più grande che contenga l'altra */
/*Prende in input un'immagine e ritorna la stessa immagine con l'aggiunta di un bordo spesso un pixel*/
struct image add_border(struct image img, struct pixel color) {
	
	struct image new_img = one_color_img(img.height+2, img.width+2, color);
	int i, j;
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
struct image load_image(char* filename) {
	struct image img= empty_img();
	int h=0, w=0;
	int r, g, b;
	int i, j;
	FILE* fload = fopen(filename,"r");
	if (fload !=NULL)
	{
		fscanf(fload, "%d\t%d", &h, &w);
		
		img.height = h;
		img.width = w;
		img.pixels = calloc(img.height, sizeof(struct pixel*));
		for ( i = 0; i < img.height; i++)
		{
			img.pixels[i] = calloc(w, sizeof(struct pixel**));
			for ( j = 0; j < img.width; j++)
			{
				if (fscanf(fload, "%d\t%d\t%d", &r, &g, &b) == EOF) { return empty_img(); }
				img.pixels[i][j].R = (unsigned char)r;
				img.pixels[i][j].G = (unsigned char)g;
				img.pixels[i][j].B = (unsigned char)b;
				
			}
		}
		fclose(fload);
		return img;
	}
	else { fclose(fload); return img; }
}

/*Prende in input un'immagine e la salva su file*/
int save_image(struct image img, char* filename) {
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
		fclose(fw);
		return 1;
	}
	else
	{
		return 0;
	}
	

}