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
    int X = rand() % W;
    int Y = rand() % H;
    MAP[Y][X] = 1;

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

        int timeout;
        {
            SDL_Event e;
            timeout = !pico_input_event_timeout(&e, SDL_ANY, 1000);
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
            int x = -1;
            while (x<0 || x>=W) {
                x = X + sqrt(rand() % W/2) * (rand()%2==1 ? 1 : -1);
            }

            int y = -1;
            while (y<0 || y>=H) {
                y = Y + sqrt(rand() % H/2) * (rand()%2==1 ? 1 : -1);
            }

            MAP[y][x] = 1;
        }
    }

    pico_init(0);
}

