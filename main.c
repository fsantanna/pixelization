#include <time.h>
#include <pico.h>

#define W 50
#define H 50

static char MAP[W][H];

#include "art.c"
#include "map.c"

int main (void) {
    pico_init(1);
    pico_set_size((Pico_Dim){5*W,5*H}, (Pico_Dim){W,H});
    pico_set_title("Master of Pixelization");
    pico_set_expert(1);

    for (int l=0; l<H; l++) {
        for (int c=0; c<W; c++) {
            MAP[l][c] = 0;
        }
    }

    srand(time(NULL));
    int X = rand() % W;
    int Y = rand() % H;
    MAP[Y][X] = 1;

    while (1) {
        pico_output_clear();

        pico_set_anchor_draw((Pico_Anchor){PICO_LEFT, PICO_TOP});
        pico_output_draw_buffer((Pico_Pos){0,0}, map_buf, map_dim);

        pico_set_anchor_draw((Pico_Anchor){PICO_CENTER, PICO_MIDDLE});
        pico_output_draw_buffer((Pico_Pos){X,Y}, tower_buf, tower_dim);
        pico_set_color_draw((Pico_Color){0xFF,0xFF,0xFF,0xFF});
        for (int l=0; l<H; l++) {
            for (int c=0; c<W; c++) {
                if (MAP[l][c] != 0) {
                    pico_output_draw_pixel((Pico_Pos){c,l});
                }
            }
        }
        pico_set_color_draw((Pico_Color){0xFF,0xFF,0x00,0xFF});
        pico_output_draw_pixel((Pico_Pos){X,Y});
        pico_output_present();

        int timeout;
        {
            SDL_Event e;
            timeout = !pico_input_event_timeout(&e, PICO_ANY, 1000);
            if (e.type == SDL_QUIT) {
                break;
            }
            /*
            switch (e.type) {
                case SDL_QUIT:
                    break;
            }
            */
        }

        if (timeout) {
            static int D[15] = {
                0, 0, 0, 0, 0,
                1, 1, 1, 1,
                2, 2, 2,
                3, 3,
                4
            };
            int x = -1;
            int y = -1;
            while (x<0 || y<0 || x>=W || y>=H || MAP[y][x]==1) {
                // TODO: assert available position
                x = X + D[rand()%15] * (rand()%2==1 ? 1 : -1);
                y = Y + D[rand()%15] * (rand()%2==1 ? 1 : -1);
            }
            MAP[y][x] = 1;

            X = Y = -1;
            while (X<0 || X<0 || MAP[Y][X]==0) {
                X = rand() % W;
                Y = rand() % H;
            }
        }
    }

    pico_init(0);
}

