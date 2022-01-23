#include "spritesAnimation.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*Stampa 1 frame alla volta di una sprite UNITO IN UN UNICO FILE, quindi ne permette l'ANIMAZIONE.
  Ogni FRAME E DIVISO, per MOVIMENTO sull'asse x, e per DIREZIONE sull'asse y.
  Lo sprite e controllato dall'utente.
  Supporta gli eventi: TIMER*/
void alAnimateSpritesAllUser(AL_SPRITE *sprite, ALLEGRO_EVENT evento, ALLEGRO_DISPLAY *display)
{
	bool status_move = false;
	
	//movimento regolato col timer
	if(evento.type == ALLEGRO_EVENT_TIMER)
	{
		ALLEGRO_KEYBOARD_STATE keyboard_state;
		
		al_get_keyboard_state(&keyboard_state);
		if(al_key_down(&keyboard_state, ALLEGRO_KEY_UP))
		{
			status_move = true;
			sprite->dir = sprite->ord_direz_up;
			
			//limite alto raggiunto
			if(checkLimitMap(sprite, display))
				sprite->posy -= sprite->speed;
		}
		else if(al_key_down(&keyboard_state, ALLEGRO_KEY_RIGHT))
		{
			status_move = true;
			sprite->dir = sprite->ord_direz_right;
			
			//limite destro non raggiunto
			if(checkLimitMap(sprite, display))
				sprite->posx += sprite->speed;
		}
		else if(al_key_down(&keyboard_state, ALLEGRO_KEY_DOWN))
		{
			status_move = true;
			sprite->dir = sprite->ord_direz_down;
			
			//limite basso non raggiunto
			if(checkLimitMap(sprite, display))
				sprite->posy += sprite->speed;
		}
		else if(al_key_down(&keyboard_state, ALLEGRO_KEY_LEFT))
		{
			status_move = true;
			sprite->dir = sprite->ord_direz_left;
			
			//limite sinistro non raggiunto
			if(checkLimitMap(sprite, display))
				sprite->posx -= sprite->speed;
		}
		
		//nesun tasto premuto, frame fermo
		else
			status_move = false;
			
		//calcolo sezione bitmap x
		//se e stato premuto un tasto, passa al frame successivo
		if(status_move)
			sprite->region_frame_iniz_x += al_get_bitmap_width(sprite->frame) / sprite->n_frame;
				
		//se non e stato premuto, passa la frame iniziale
		else
			sprite->region_frame_iniz_x = (al_get_bitmap_width(sprite->frame) / sprite->n_frame) * (sprite->frame_iniz - 1); 
				
		//limite frame superato, inizializza posizione
		if(sprite->region_frame_iniz_x >= al_get_bitmap_width(sprite->frame))
			sprite->region_frame_iniz_x = 0;
			
		//calcolo sezione bitmap y
		sprite->region_frame_iniz_y = sprite->dir;
		
		//STAMPA SPRITE
		al_draw_bitmap_region(sprite->frame, sprite->region_frame_iniz_x, al_get_bitmap_height(sprite->frame) * sprite->region_frame_iniz_y / sprite->n_dir, al_get_bitmap_width(sprite->frame) / sprite->n_frame, al_get_bitmap_height(sprite->frame) / sprite->n_dir, sprite->posx, sprite->posy, 0);
	}
}

void alAnimateSpritesAllIa(AL_SPRITE *sprite, ALLEGRO_EVENT evento, ALLEGRO_DISPLAY *display)
{
	int static passo = 0;				//il numero di passi eseguiti in una direzione.
	int passi_min_direz = 10;			//i passi minimi da eseguire nella stessa direzione.
	bool status_move = false;

	if(evento.type == ALLEGRO_EVENT_TIMER)
	{
		//se e il primo passo, nuova direzione
		if(passo == 0)
		{
			sprite->dir = rand() % 4;
		}
		
		//su
		if(sprite->dir == sprite->ord_direz_up)
		{
			status_move = true;
			
			//limite su non raggiunto
			if(checkLimitMap(sprite, display))
				sprite->posy -= sprite->speed;
		}
		
		//giu
		else if(sprite->dir == sprite->ord_direz_down)
		{
			status_move = true;
			
			//limite su non raggiunto
			if(checkLimitMap(sprite, display))
				sprite->posy += sprite->speed;
		}
		
		//sinistra
		else if(sprite->dir == sprite->ord_direz_left)
		{
			status_move = true;
			
			//limite su non raggiunto
			if(checkLimitMap(sprite, display))
				sprite->posx -= sprite->speed;
		}
		
		//destra
		else if(sprite->dir == sprite->ord_direz_right)
		{
			status_move = true;
			
			//limite su non raggiunto
			if(checkLimitMap(sprite, display))
				sprite->posx += sprite->speed;
		}
		else
			status_move = false;
		
		//numero passi raggiunto, cambia direzione
		if(passo == passi_min_direz)
			passo = 0;
			
		//altrimenti fai un passo
		else
			passo++;
			
		//calcolo sezione bitmap x
		//se e stato premuto un tasto, passa al frame successivo
		if(status_move)
			sprite->region_frame_iniz_x += al_get_bitmap_width(sprite->frame) / sprite->n_frame;
				
		//se non e stato premuto, passa la frame iniziale
		else
			sprite->region_frame_iniz_x = (al_get_bitmap_width(sprite->frame) / sprite->n_frame) * (sprite->frame_iniz - 1); 
				
		//limite superato, inizializza posizione
		if(sprite->region_frame_iniz_x >= al_get_bitmap_width(sprite->frame))
			sprite->region_frame_iniz_x = 0;
			
		//calcolo sezione bitmap y
		sprite->region_frame_iniz_y = sprite->dir;
			
		al_draw_bitmap_region(sprite->frame, sprite->region_frame_iniz_x, al_get_bitmap_height(sprite->frame) * sprite->region_frame_iniz_y / sprite->n_dir, al_get_bitmap_width(sprite->frame) / sprite->n_frame, al_get_bitmap_height(sprite->frame) / sprite->n_dir, sprite->posx, sprite->posy, 0);	
	}	
}

//controlla se il personaggio ha raggiunto uno dei limiti del display
bool checkLimitMap(AL_SPRITE *sprite, ALLEGRO_DISPLAY *display)
{
	//direzione destra
	if(sprite->dir == sprite->ord_direz_right)
	{
		//limite destro raggiunto
		if(sprite->posx + (al_get_bitmap_width(sprite->frame) / sprite->n_frame) >= al_get_display_width(display))
			return false;
		else
			true;
	}
	
	//direzione basso
	else if(sprite->dir == sprite->ord_direz_down)
	{
		//limite basso raggiunto
		if(sprite->posy + (al_get_bitmap_height(sprite->frame) / sprite->n_dir) >= al_get_display_height(display))
			return false;
		else
			true;
	}
	
	//direzione alto
	else if(sprite->dir == sprite->ord_direz_up)
	{
		//limite alto raggiunto
		if(sprite->posy <= 0)
			return false;
		else
			true;
	}
	
	//direzione sinistra
	else if(sprite->dir == sprite->ord_direz_left)
	{
		//limite sinistra raggiunto
		if(sprite->posx <= 0)
			return false;
		else
			true;
	}
		
		
	
		
		
	

	

}
