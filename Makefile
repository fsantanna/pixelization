all:
	gcc -o pixel.exe main.c -I pico/src pico/src/pico.c pico/src/hash.c -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lSDL2_gfx
