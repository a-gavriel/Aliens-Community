#include <stdio.h>
#include <stdlib.h>
#include <time.h> 


#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>



#include "../include/graph_points.h"
#include "../include/alien.h"
#include "../include/bridge.h"
#include "../include/Random_Generators.h"
#include "../include/ConfigFile_Reader.h"

alien_t list_A_in [32] = {0};
alien_t list_A_out [24] = {0};
alien_t list_down_top_left [12] = {0};
alien_t list_down_top_center [5] = {0};
alien_t list_down_top_right [12] = {0};
alien_t list_up_top_left [12] = {0};
alien_t list_up_top_center [5] = {0};
alien_t list_up_top_right [11] = {0};
alien_t list_bridge_left [5] = {0};
alien_t list_bridge_center [5] = {0};
alien_t list_bridge_right [5] = {0};
alien_t list_down_bottom_left [9] = {0};
alien_t list_down_bottom_center [4] = {0};
alien_t list_down_bottom_right [11] = {0};
alien_t list_up_bottom_left [9] = {0};
alien_t list_up_bottom_center [4] = {0};
alien_t list_up_bottom_right [10] = {0};
alien_t list_B_in [32] = {0};
alien_t list_B_out [23] = {0};

void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

void draw_aliens(ALLEGRO_BITMAP* alien1, ALLEGRO_BITMAP* alien2, ALLEGRO_BITMAP* alien3 ){
    pid_t cid;
    float cx,cy;
    char alienType;
    const Point* route_coords;
    for (int i = 0; i< 19; ++i){
        alien_t* currentRoute = routes[i];        
        for (int j = 0; j < routes_sizes[i] ; ++j){
            cid = currentRoute[j].threadID;           
            if (cid != 0) {
                route_coords = routes_coords[i];    
                cx = route_coords[j].x;
                cy = route_coords[j].y;
                alienType = currentRoute[j].alienType;
                switch(alienType){
                    case 'N':
                        al_draw_bitmap(alien1, cx, cy, 0);
                        break;
                    case 'n':
                        al_draw_bitmap(alien1, cx, cy, ALLEGRO_FLIP_HORIZONTAL );
                        break;
                    case 'A':
                        al_draw_bitmap(alien2, cx, cy, 0);
                        break;
                    case 'a':
                        al_draw_bitmap(alien2, cx, cy, ALLEGRO_FLIP_HORIZONTAL);
                        break;
                    case 'B':
                        al_draw_bitmap(alien3, cx, cy, 0);
                        break;
                    case 'b':
                        al_draw_bitmap(alien3, cx, cy, ALLEGRO_FLIP_HORIZONTAL);
                        break;
                    
                }
            }
        }
    }
}



int main()
{
    //Read all config files
    Read_program_config();
    //Bridges
    left_bridge = (bridge_params_t){0,0,bridgeL.max_weigth,-1,bridgeL.bridge_type};
    right_bridge = (bridge_params_t){0,0,bridgeR.max_weigth,1,bridgeL.bridge_type};
    center_bridge = (bridge_params_t){0,0,bridgeC.max_weigth,0,bridgeL.bridge_type};

    init_mutex();

    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_DISPLAY* disp = al_create_display(1380, 760);
    must_init(disp, "display");

    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");

	must_init(al_init_image_addon(), "image addon");
	ALLEGRO_BITMAP* wallpaper = al_load_bitmap("../misc/imgs/Fondo.png");
    must_init(wallpaper, "wallpaper");

    ALLEGRO_BITMAP* alien1 = al_load_bitmap("../misc/imgs/Alien1.png");
    must_init(alien1, "alien1");
    ALLEGRO_BITMAP* alien2 = al_load_bitmap("../misc/imgs/Alien2.png");
    must_init(alien2, "alien2");
    ALLEGRO_BITMAP* alien3 = al_load_bitmap("../misc/imgs/Alien3.png");
    must_init(alien3, "alien3");

    must_init(al_init_primitives_addon(), "primitives");
    must_init(al_install_mouse(), "mouse");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());       

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    float x, y;
    x = 100;
    y = 100;

    int counter = 0;
    
    
    #define KEY_SEEN     1
    #define KEY_RELEASED 2

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    al_start_timer(timer);
    time_t t;
    // Initializes random number generator
    srand((unsigned) time(&t));
    uint frame = 0;
    printf("%d,%d,%d\n",aliensG.alfa,aliensG.beta,aliensG.normal);
    printf("randome seed %d\n",aliensG.mean);
    double randomseed = (double) aliensG.mean;
    uint randomexp = expRandom(randomseed);
    uint f_new_alien = randomexp*30/1000000;
    printf("Next alien in %d\n",f_new_alien/30);
    int randint;
    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                if(key[ALLEGRO_KEY_UP]){ 
                    key[ALLEGRO_KEY_UP] = 0;
                    counter = (counter + 1)%12;                    
                    x = A_top_right[counter].x;
                    y = A_top_right[counter].y;
                    
                    printf("moved rect to: %f,%f\n",x,y);
                    }
                    
                if(key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                    key[i] = 0;
                if(frame == f_new_alien){
                    frame = 0;
                    randint = rand()%100;
                    if (randint < aliensG.normal){
                        generateAlien(alienTypes+(rand()%2)*3);
                    }else if (randint < (aliensG.normal + aliensG.alfa )){
                        generateAlien(alienTypes+1+(rand()%2)*3);
                    }else{
                        generateAlien(alienTypes+2+(rand()%2)*3);
                    }
                    
                    randomexp = expRandom(randomseed);
                    f_new_alien = randomexp*30/1000000;
                    printf("Next alien in %d\n",f_new_alien/30);
                }
                BridgeMovements();
                redraw = true;
                ++frame;
                break;


            case  ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                printf("clicked: %d,%d\n",event.mouse.x,event.mouse.y);
                int r = getAlien(event.mouse.x,event.mouse.y);
                if (r!=-1)
                    printf("alien found in %d\n",r);
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                //key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] = KEY_RELEASED;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(wallpaper,0,0,0);
            al_draw_filled_rectangle(100, 100, 100 + 10, 100 + 10, al_map_rgb(255, 0, 0));
			draw_aliens(alien1, alien2, alien3);
            al_flip_display();

            redraw = false;
        }
    }
	al_destroy_bitmap(wallpaper);
	al_destroy_bitmap(alien1);
    al_destroy_bitmap(alien2);
    al_destroy_bitmap(alien3);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    exit(3);
    //return 0;
}