#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>


typedef struct ALLEGRO_DISPLAY ALLEGRO_DISPLAY;
int screen_width = 1366;
int screen_high = 768;

int main()
{

	ALLEGRO_DISPLAY *display = al_create_display(screen_width, screen_high);
	//al_is_image_addon_initialized();

	sleep(10000);
	//al_shutdown_image_addon();
	al_destroy_display(display);
	return EXIT_SUCCESS;
}

//gcc -o ./bin/graphics ./src/graphics.c $(pkg-config allegro-5 allegro_font-5 allegro_image-5 --libs --cflags)
//sudo gcc -o ./bin/graphics ./src/graphics.c -I /usr/local/include/allegro5/ -L /usr/local/lib/ -lallegro -lm
//pkg-config --variable pc_path pkg-config



