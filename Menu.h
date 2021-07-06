#ifndef MENU_H
#define MENU_H
#include <SDL2/SDL_mixer.h>
typedef struct Option{
SDL_Texture *texture;
SDL_Texture *textures[2];
int x,y,w,h;
}Option;
typedef struct Menu{
    SDL_Texture *texture;
    Option option1;
    Option option2;

}Menu;
void initMenu(SDL_Renderer *renderer,Menu *menu);
void  renderMenu(SDL_Renderer *renderer,Menu *menu,int *selected,int *interface,int *done);
void renderOption1(SDL_Renderer *renderer,Menu *menu,int selected);

#endif