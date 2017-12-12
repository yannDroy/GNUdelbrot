#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "display.h"
#include "menu.h"
#include "const.h"

void menu (SDL_Surface* window){
    SDL_Event event;
    int run = 1;
    int change = 1;
    int definition = 1;
    int deep = 0;
    int colors = 3;
    int bw = 0;
    double xmin = -3.0;
    double xmax = 3.0;
    double ymin = -2.0;
    double ymax = 2.0;
    double xrange, yrange, xstep, ystep;
    double clickx, clicky;

    while(run){
        xrange = fabs(xmin - xmax);
        yrange = fabs(ymin - ymax);
        xstep = definition * (xrange / (double) window->w);
        ystep = definition * (yrange / (double) window->h);

        if(change){
            mandelbrot_set(window, xmin, xmax, ymin, ymax, definition, colors, bw);
            change = 0;
            fprintf(stdout, "x range : [%lf ; %lf] -> %lf\n", xmin, xmax, xrange);
            fprintf(stdout, "y range : [%lf ; %lf] -> %lf\n", ymin, ymax, yrange);
            fprintf(stdout, "centre : [%lf ; %lf]\n", (xmin + xrange / 2), (ymin + yrange / 2));
            fprintf(stdout, "definition : %d pixel(s) / step\n", definition);
            fprintf(stdout, "step : %lf\n", xstep);
            fprintf(stdout, "deep : %d / %d\n", deep, MAX_DEEP);
            fprintf(stdout, "number of color shades : %d\n", colors);
            fprintf(stdout, "'H' for help\n\n\n");
        }
            
        SDL_WaitEvent(&event);

        switch(event.type){
        case SDL_QUIT:
            run = 0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
            case SDLK_ESCAPE:
                run = 0;
                break;
            case SDLK_h:
                fprintf(stdout, "User's manual :\n");
                fprintf(stdout, "  * left/right click : zoom in/out with click as center\n");
                fprintf(stdout, "  * backspace : reset the view (default [-3, 3], [-2, 2])\n");
                fprintf(stdout, "  * keypad +/- : higher/lower pixel definition\n");
                fprintf(stdout, "  * keypad enter : reset pixel definition (default 1)\n");
                fprintf(stdout, "  * left/right arrows : increase/decrease the number of color shades\n");
                fprintf(stdout, "  * right ctrl : reset the numberof color shades (default 3)\n");
                fprintf(stdout, "  * space/left alt : zoom in/out with the current center as center\n");
                fprintf(stdout, "  * enter : switch between colors and black and white scheme\n");
                fprintf(stdout, "  * s : save the current view in a .bmp file\n");
                fprintf(stdout, "  * h : help\n");
                fprintf(stdout, "  * esc : quit\n\n\n");
                break;
            case SDLK_RETURN:
                bw = 1 - bw;
                change = 1;
                break;
            case SDLK_LEFT:
                if(colors > 1){
                    colors--;
                    change = 1;
                }
                break;
            case SDLK_RIGHT:
                if(colors < 20){
                    colors++;
                    change = 1;
                }
                break;
            case SDLK_RCTRL:
                if(colors != 5){
                    colors = 3;
                    change = 1;
                }
                break;
            case SDLK_KP_PLUS:
                if(definition > 1){
                    definition--;
                    change = 1;
                }
                break;
            case SDLK_KP_MINUS:
                if(definition < 10){
                    definition++;
                    change = 1;
                }
                break;
            case SDLK_KP_ENTER:
                if(definition != 1){
                    definition = 1;
                    change = 1;
                }
                break;
            case SDLK_BACKSPACE:
                if(deep != 0){
                    xmin = -3.0;
                    xmax = 3.0;
                    ymin = -2.0;
                    ymax = 2.0;
                    
                    change = 1;
                    deep = 0;
                }
                break;
            case SDLK_DOWN:
                break;
            case SDLK_UP:
                break;
            case SDLK_SPACE:
                if(deep < MAX_DEEP){
                    xmin = (xmin + xrange / 2) - (xrange / 4);
                    xmax = (xmax - xrange / 2) + (xrange / 4);
                    ymin = (ymin + yrange / 2) - (yrange / 4);
                    ymax = (ymax - yrange / 2) + (yrange / 4);

                    deep++;
                    change = 1;
                }
                break;
            case SDLK_LALT:
                if(deep > -2){
                    xmin = (xmin + xrange / 2) - xrange;
                    xmax = (xmax - xrange / 2) + xrange;
                    ymin = (ymin + yrange / 2) - yrange;
                    ymax = (ymax - yrange / 2) + yrange;

                    deep--;
                    change = 1;
                }
                break;
            case SDLK_s:
                SDL_SaveBMP(window, "Gnudelbrot.bmp");
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            break;
        case SDL_MOUSEBUTTONDOWN:
            clickx = (double) (xmin + ((event.button.x / definition) * xstep));
            clicky = (double) (ymin + ((event.button.y / definition) * ystep));

            switch(event.button.button){
            case SDL_BUTTON_LEFT:
                if(deep < MAX_DEEP){
                    xmin = clickx - (xrange / 4);
                    xmax = clickx + (xrange / 4);
                    ymin = clicky - (yrange / 4);
                    ymax = clicky + (yrange / 4);

                    deep++;
                    change = 1;
                }
                break;
            case SDL_BUTTON_RIGHT:
                if(deep > -2){
                    xmin = clickx - xrange;
                    xmax = clickx + xrange;
                    ymin = clicky - yrange;
                    ymax = clicky + yrange;

                    deep--;
                    change = 1;
                }
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            break;
        case SDL_MOUSEMOTION:
            break;
        default:
            break;
        }
    }
}
