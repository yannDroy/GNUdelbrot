#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

void init ();

void init_window (SDL_Surface** window, int width, int heigth);

void sdl_kill ();

void mandelbrot_set (SDL_Surface* window, double xmin, double xmax, double ymin, double ymax, int def, int colors, int bw);

void choose_color (int n, int* r, int* v, int* b, int colors, int bw);
