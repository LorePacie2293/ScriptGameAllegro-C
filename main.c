#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "spritesAnimation.h"

main()
{
	al_init();
	al_init_image_addon();
	al_install_keyboard();
	
	AL_SPRITE player = {al_load_bitmap("player3.png"), 2, 16, 0, 4, 6, 2, 400, 200, 8, 5, 5, (al_get_bitmap_width(player.frame) / player.n_frame) * (player.frame_iniz), 0};
	AL_SPRITE player2 = {al_load_bitmap("player2.png"), 1, 6, 1, 0, 2, 3, 200, 500, 4, 0, 5, (al_get_bitmap_width(player2.frame) / player2.n_frame) * (player2.frame_iniz), 0};
	AL_SPRITE player3 = {al_load_bitmap("player.png"), 1, 3, 0, 2, 3, 1, 600, 200, 4, 2, 5, (al_get_bitmap_width(player3.frame) / player3.n_frame) * (player3.frame_iniz), 0};
	AL_SPRITE player4 = {al_load_bitmap("player4.png"), 1, 9, 0, 2, 1, 3, 700, 300, 4, 2, 5, (al_get_bitmap_width(player4.frame) / player4.n_frame) * (player4.frame_iniz), 0};

	ALLEGRO_TIMER *timer = al_create_timer(1/30.0);
	ALLEGRO_DISPLAY *display = al_create_display(800, 600);
	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
	ALLEGRO_EVENT evento;
	
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_keyboard_event_source());
	
	al_start_timer(timer);
	do
	{
		al_wait_for_event(queue, &evento);
		
		if(evento.type == ALLEGRO_EVENT_TIMER)
		{
			alAnimateSpritesAllUser(&player, evento, display);
			alAnimateSpritesAllIa(&player2, evento, display);
			alAnimateSpritesAllIa(&player3, evento, display);
			alAnimateSpritesAllIa(&player4, evento, display);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}while(evento.keyboard.keycode != ALLEGRO_KEY_E);
}
