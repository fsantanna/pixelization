#include <time.h>
#include <pico.h>

#define W 100
#define H 100

static char MAP[W][H];

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
    int x = rand() % W;
    int y = rand() % H;

    MAP[y][x] = 1;

    while (1) {
        pico_output_clear();
        for (int l=0; l<H; l++) {
            for (int c=0; c<W; c++) {
                if (MAP[l][c] != 0) {
                    pico_output_draw_pixel((Pico_Pos){c,l});
                }
            }
        }
        pico_output_present();

        {
            SDL_Event e;
            pico_input_event_timeout(&e, SDL_ANY, 2000);
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
    }

    pico_init(0);
}

