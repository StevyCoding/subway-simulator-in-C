#ifndef TIMER_H
#define TIMER_H
#include "Station.h"
typedef struct
{
    SDL_Color color;
    SDL_Texture *texture;
    TTF_Font *font;
    int size,x,y,w,h;
    
} EmulatorText;
void  textRendererUpside(EmulatorText* emulatorText,SDL_Renderer* renderer,Station *station,int *diffTime,SDL_Texture *textureIvry[],Mix_Chunk *voice);
void textRendererDownside(EmulatorText* emulatorText,SDL_Renderer* renderer,Station *station,int *diffTime,SDL_Texture *textureCourneuve[],Mix_Chunk *voice);
void rightMetroIvryText(SDL_Renderer *renderer,SDL_Surface *surface[],SDL_Texture *texture[],EmulatorText emulatorText);
void leftMetroCourneuveText(SDL_Renderer *renderer,SDL_Surface *surface[],SDL_Texture *texture[],EmulatorText emulatorText);


#endif