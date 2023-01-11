#include "img_manager.h"
#include <stdlib.h>
#include <stdio.h>
#define IMG_FILE_NAME "test_img.txt" //file con l'immagine originale
#define SOL_FILE_NAME "solution_img.txt" //file con l'immagine della soluzione

#define RES_FILE_NAME "result_img.txt" //file dove salvare il risultato della trasformazione
#define TEST_FILE "test_save.txt" //file dove testare lettura e salvataggio


/*Prende in input un'immagine. Se è vuota ritorna 1, altrimenti ritorna 0*/
static int is_empty(struct image img) {
	if (img.height == 0 && img.width == 0 && img.pixels == NULL)
		return 1;
	return 0;
}

/*Prende in input due pixel. Se sono equivalenti ritorna 1, altrimenti ritorna 0*/
static int pixel_compare(struct pixel p1, struct pixel p2) {
	return (p1.R == p2.R && p1.G == p2.G && p1.B == p2.B) ? 1 : 0;
}

/*Prende in input due immagini. Se sono equivalenti ritorna 1, altrimenti ritorna 0*/
static int img_compare(struct image img1, struct image img2) {
	int i, j;
	if (img1.height != img2.height || img1.width != img2.width)
		return 0;

	for (i = 0; i < img1.height; i++)
		for (j = 0; j < img1.width; j++)
			if (!pixel_compare(img1.pixels[i][j], img2.pixels[i][j]))
				return 0;
	return 1;
}

/*Stampa la matrice dell'immagine, andando a capo ad ogni riga*/
void print_image(struct image img) {
	int i, j;
	for (i = 0; i < img.height; i++) {
		for (j = 0; j < img.width; j++) {
			printf("(%d, %d, %d)\t", img.pixels[i][j].R, img.pixels[i][j].G, img.pixels[i][j].B);
		}
		printf("\n");
	}
}

int main() {
	/*TEST LOAD/SAVE*/
	//carico l'immagine originale
	struct image img = load_image(IMG_FILE_NAME);
	if (is_empty(img)) {
		printf("il caricamento non è andato a buon fine o l'immagine è vuota.");
	}
	//stampo l'immagine caricata
	printf("Immagine iniziale: \n");
	print_image(img);

	//salvo l'immagine originale
	if (!save_image(img, TEST_FILE))
		printf("errore nel salvataggio\n");
	//carico l'immagine che ho appena salvato
	struct image loaded_img = load_image(TEST_FILE);
	if (!img_compare(img, loaded_img))
		printf("Le due immagini non combaciano. Errore nel salvataggio o nel caricamento");

	/*-----------------------------------------------------------------------------------*/


	/*TEST GREYSCALE*/
	//creo una nuova immagine ottenuta dalla trasformazione in scala di grigi dell'originale.
	struct image grayscale = RGB_to_greyscale(img);

	//stampo l'immagine trasformata
	printf("Immagine in scala di grigi: \n");
	print_image(grayscale);

	/*TEST BORDER*/
	struct pixel white;
	white.R = 255;
	white.G = 255;
	white.B = 255;
	//creo una nuova immagine ottenuta dall'aggiunta di un bordo bianco all'immagine in scala di grigi
	struct image grey_with_border = add_border(grayscale, white);

	//stampo l'immagine trasformata
	printf("Immagine in scala di grigi con aggiunta di bordo: \n");
	print_image(grey_with_border);


	//carico l'immagine della soluzione
	struct image sol_img = load_image(SOL_FILE_NAME);
	if (is_empty(sol_img)) {
		printf("il caricamento non è andato a buon fine o l'immagine è vuota.");
	}

	//confronto il risultato ottenuto con la soluzione
	if (img_compare(grey_with_border, sol_img))
		printf("il risultato ottenuto combacia con la soluzione\n");
	else printf("il risultato ottenuto è errato\n");


	return 0;
}