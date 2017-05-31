Pour compiler le projet

gcc -O2 -Wall `sdl-config --cflags` graphics.c projet.c -o spaceinvader `sdl-config --libs` -lm -lSDL_ttf -lSDL_mixer
