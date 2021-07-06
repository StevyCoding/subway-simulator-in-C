#include "SDL2/SDL.h"
#include <SDL2/SDL_mixer.h>
#include "Menu.h"
#include "Station.h"
void initMenu(SDL_Renderer *renderer,Menu *menu){
    menu->option1.x = 1024 / 2;
    menu->option1.y = 576 / 2 - 100;
    menu->option1.w = 200;
    menu->option1.h = 20;
    menu->option2.x = 1024 / 2 +11;
    menu->option2.y = 576 / 2;
    menu->option2.w = 140;
    menu->option2.h = 15;
    menu->texture = loadTexture("./images/menuBackground.png",renderer);
    menu->option1.textures[0] = loadTexture("./images/commencer.png",renderer);
    menu->option1.textures[1] = loadTexture("./images/commencer2.png",renderer);
    menu->option2.textures[0] = loadTexture("./images/quitter.png",renderer);
    menu->option2.textures[1] = loadTexture("./images/quitter2.png",renderer);
}
void  renderMenu(SDL_Renderer *renderer,Menu *menu,int *selected,int *interface,int *done){
     const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP])
    {
        *selected = 0;
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        *selected = 1;
    }
    if (state[SDL_SCANCODE_RETURN]){
        if(*selected == 0){
            *interface = 1;
        }
        else if(*selected == 1){
            *done = 1;
        }
    }
    SDL_QueryTexture(menu->texture, NULL, NULL, 0, 0);
    SDL_RenderCopy(renderer,menu->texture, NULL, NULL);


}

void renderOption1(SDL_Renderer *renderer,Menu *menu,int selected){
    if (selected == 0){
        menu->option1.texture = menu->option1.textures[1];
        menu->option2.texture = menu->option2.textures[0];
    }
    else if(selected == 1){
        menu->option2.texture = menu->option2.textures[1];
          menu->option1.texture = menu->option1.textures[0];
    }
    SDL_Rect commencer = {menu->option1.x,menu->option1.y,menu->option1.w,menu->option1.h};
    SDL_RenderCopy(renderer,menu->option1.texture, NULL, &commencer);

    SDL_Rect quitter = {menu->option2.x,menu->option2.y,menu->option2.w,menu->option2.h};
    SDL_RenderCopy(renderer,menu->option2.texture, NULL, &quitter);
}
