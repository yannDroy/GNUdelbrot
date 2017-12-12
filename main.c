#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include "display.h"
#include "menu.h"
#include "const.h"

int main (){
    SDL_Surface* window = NULL;

    system("clear");
    fprintf(stdout, "*** GNUdelbrot Visualization ***\n\n");

    init();
    init_window(&window, WIDTH, HEIGHT);

    menu(window);

    sdl_kill();

    return EXIT_SUCCESS;
}
