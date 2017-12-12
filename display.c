#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "display.h"
#include "complex.h"
#include "const.h"

void init (){
  if(SDL_Init(SDL_INIT_VIDEO) == -1){
    fprintf(stderr, "SDL loading failure : %s.\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
}

void init_window (SDL_Surface** window, int width, int heigth){
  *window = SDL_SetVideoMode(width, heigth, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

  if(window == NULL){
    fprintf(stderr, "Window opening failure : %s.\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }else{
    SDL_WM_SetCaption("GNUdelbrot 1.9", NULL);
    SDL_WM_SetIcon(IMG_Load("icon.gif"), NULL);
    SDL_Flip(*window);
  }
}

void sdl_kill (){
  SDL_Quit();
}

void mandelbrot_set (SDL_Surface* window, double xmin, double xmax, double ymin, double ymax, int def, int colors, int bw){
    SDL_Surface* pixel = NULL;
    SDL_Rect pos;
    complex current, c;
    double x, y;
    double x_range, y_range, x_step, y_step;
    int count = 0;
    int i, j;
    int r, v, b;

    pixel = SDL_CreateRGBSurface(SDL_HWSURFACE, def, def, 32, 0, 0, 0, 0);

    x = xmin;
    y = ymin;

    x_range = fabs(xmin - xmax);
    y_range = fabs(ymin - ymax);

    x_step = def * (x_range / (double) window->w);
    y_step = def * (y_range / (double) window->h);

    for(i = 0; i < WIDTH; i += def){
        for(j = 0; j < HEIGHT; j += def){
            count = 0;

            current.re = 0;//x;
            current.im = 0;//y;

            c.re = x;//0.41
            c.im = y;//0;

            while(magnitude(current) < 2 && count < MAX_REC){
                current = next_term(current, c);
                count++;
            }

            pos.x = i;
            pos.y = j;

            choose_color(count, &r, &v, &b, colors, bw);

            SDL_FillRect(pixel, NULL, (SDL_MapRGB(window->format, r, v, b)));

            SDL_BlitSurface(pixel, NULL, window, &pos);

            y += y_step;
        }
        x += x_step;
        y = ymin;

        SDL_Flip(window);
    }

    SDL_FreeSurface(pixel);
}


void choose_color (int n, int* r, int* v, int* b, int colors, int bw){
    if(n == MAX_REC){
        if(!bw){
            *r = 0;
            *v = 0;
            *b = 0;
        }else{
            *r = 255;
            *v = 255;
            *b = 255;
        }
    }else{
        if(!bw){
            n *= (1530 * colors) / MAX_REC;
            n %= 1530;

            if(n <= 255){ // bleu -> cyan
                *r = 0;
                *v = n;
                *b = 255;
            }else if(n <= 510){ // cyan -> vert
                *r = 0;
                *v = 255;
                *b = 510 - n;
            }else if(n <= 765){ // vert -> jaune
                *r = n - 510;
                *v = 255;
                *b = 0;
            }else if(n <= 1020){ // jaune -> rouge
                *r = 255;
                *v = 1020 - n;
                *b = 0;
            }else if(n <= 1275){ // rouge -> violet
                *r = 255;
                *v = 0;
                *b = n - 1020;
            }else if(n <= 1530){ // violet -> bleu
                *r = 1530 - n;
                *v = 0;
                *b = 255;
            }
        }else{
            n *= (510 * colors) / MAX_REC;
            n %= 510;
            
            if(n < 255){
                *r = n;
                *v = n;
                *b = n;
            }else{
                *r = 510 - n;
                *v = 510 - n;
                *b = 510 - n;
            }
        }
    }
}
