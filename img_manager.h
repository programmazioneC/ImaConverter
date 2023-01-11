
#define COLOR_WHITE 255
#define COLOR_BLACK 0

struct pixel {
	unsigned char R;
	unsigned char G;
	unsigned char B;
};

struct image {
	struct pixel** pixels;
	int width;
	int height;
};

/*Prende in input un'immagine a colori e ritorna un'immagine in scala di grigi*/
struct image RGB_to_greyscale(struct image img);

/*Prende in input un'immagine e ritorna la stessa immagine con l'aggiunta di un bordo spesso un pixel*/
struct image add_border(struct image img, struct pixel color);

/*Prende in input un file e ritorna l'immagine letta*/
struct image load_image(char* filename);

/*Prende in input un'immagine e la salva su file*/
int save_image(struct image img, char* filename);




