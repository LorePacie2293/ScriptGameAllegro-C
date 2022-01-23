#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

typedef enum{UP, DOWN, RIGHT, LEFT}direct;

typedef struct
{
	ALLEGRO_BITMAP *frame;					//puntatore alla bitmap
	int frame_iniz;							//frame iniziale del movimento
	int n_frame;							//il numero dei frame che compongono il movimento in una direzione
	int ord_direz_up, ord_direz_down;		//indicano le righe della bitmap in cui si trovano le direzioni down e up
	int ord_direz_left, ord_direz_right;	//indicano le righe della bitmap in cui si trovano le direzioni left e right
	int posx, posy;							//posizioni x-y
	int n_dir;								//il numero delle direzioni dello sprite
	int dir;								//direzione corrente 
	int speed;								//velocita di avanzamento
	int region_frame_iniz_x;				//La cordinadata x della sezione del frame x
	int region_frame_iniz_y;				//La cordinata y della sezione del frame y4
}AL_SPRITE;

void alAnimateSpritesAllUser(AL_SPRITE *sprite, ALLEGRO_EVENT evento, ALLEGRO_DISPLAY *display);
void alAnimateSpritesAllIa(AL_SPRITE *sprite, ALLEGRO_EVENT evento, ALLEGRO_DISPLAY *display);
bool checkLimitMap(AL_SPRITE *sprite, ALLEGRO_DISPLAY *display);

