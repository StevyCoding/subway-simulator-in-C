#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Timer.h"
#include "Station.h"
#include <SDL2/SDL_mixer.h>

void textRendererUpside(EmulatorText *emulatorText, SDL_Renderer *renderer, Station *station, int *diffTime, SDL_Texture *textureIvry[], Mix_Chunk *voice)
{
    if (station->metroRight.x >= 1200)
    {
        if (*diffTime / 1000 == 0)
        {
            emulatorText->texture = textureIvry[10];
            Mix_VolumeChunk(voice, MIX_MAX_VOLUME / 4);
            Mix_PlayChannel(-1, voice, 0);
        }
        else if (*diffTime / 1000 == 1)
        {
            emulatorText->texture = textureIvry[9];
        }
        else if (*diffTime / 1000 == 2)
        {
            emulatorText->texture = textureIvry[8];
        }
        else if (*diffTime / 1000 == 3)
        {
            emulatorText->texture = textureIvry[7];
        }
        else if (*diffTime / 1000 == 4)
        {
            emulatorText->texture = textureIvry[6];
        }
        else if (*diffTime / 1000 == 5)
        {
            emulatorText->texture = textureIvry[5];
        }
        else if (*diffTime / 1000 == 6)
        {
            emulatorText->texture = textureIvry[4];
        }
        else if (*diffTime / 1000 == 7)
        {
            emulatorText->texture = textureIvry[3];
        }
        else if (*diffTime / 1000 == 8)
        {
            emulatorText->texture = textureIvry[2];
        }
        else if (*diffTime / 1000 == 9)
        {
            emulatorText->texture = textureIvry[1];
        }
        else if (*diffTime / 1000 == 10)
        {
            emulatorText->texture = textureIvry[0];
        }
    }
    else
    {
        emulatorText->texture = textureIvry[0];
    }
    SDL_Rect position;
    position.x = emulatorText->x;
    position.y = emulatorText->y;
    position.w = emulatorText->w;
    position.h = emulatorText->h;
    SDL_RenderCopy(renderer, emulatorText->texture, NULL, &position);
}
void textRendererDownside(EmulatorText *emulatorText, SDL_Renderer *renderer, Station *station, int *diffTime, SDL_Texture *textureCourneuve[], Mix_Chunk *voice)
{
    if (station->metroLeft.x + station->metroLeft.w <= 0)
    {
        if (*diffTime / 1000 == 0)
        {
            emulatorText->texture = textureCourneuve[10];
            Mix_VolumeChunk(voice, MIX_MAX_VOLUME / 4);
            Mix_PlayChannel(-1, voice, 0);
        }
        else if (*diffTime / 1000 == 1)
        {
            emulatorText->texture = textureCourneuve[9];
        }
        else if (*diffTime / 1000 == 2)
        {
            emulatorText->texture = textureCourneuve[8];
        }
        else if (*diffTime / 1000 == 3)
        {
            emulatorText->texture = textureCourneuve[7];
        }
        else if (*diffTime / 1000 == 4)
        {
            emulatorText->texture = textureCourneuve[6];
        }
        else if (*diffTime / 1000 == 5)
        {
            emulatorText->texture = textureCourneuve[5];
        }
        else if (*diffTime / 1000 == 6)
        {
            emulatorText->texture = textureCourneuve[4];
        }
        else if (*diffTime / 1000 == 7)
        {
            emulatorText->texture = textureCourneuve[3];
        }
        else if (*diffTime / 1000 == 8)
        {
            emulatorText->texture = textureCourneuve[2];
        }
        else if (*diffTime / 1000 == 9)
        {
            emulatorText->texture = textureCourneuve[1];
        }
        else if (*diffTime / 1000 == 10)
        {
            emulatorText->texture = textureCourneuve[0];
        }
    }
    else
    {
        emulatorText->texture = textureCourneuve[0];
    }
    SDL_Rect position;
    position.x = emulatorText->x;
    position.y = emulatorText->y;
    position.w = emulatorText->w;
    position.h = emulatorText->h;
    SDL_RenderCopy(renderer, emulatorText->texture, NULL, &position);
}
void rightMetroIvryText(SDL_Renderer *renderer, SDL_Surface *surface[], SDL_Texture *texture[], EmulatorText emulatorText)
{
    surface[0] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Ivry dans 0 seconde ", emulatorText.color, 600);
    surface[1] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Ivry dans 1 seconde ", emulatorText.color, 600);
    surface[2] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Ivry dans 2 secondes ", emulatorText.color, 600);
    surface[3] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Ivry dans 3 secondes ", emulatorText.color, 600);
    surface[4] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Ivry dans 4 secondes ", emulatorText.color, 600);
    surface[5] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Ivry dans 5 secondes ", emulatorText.color, 600);
    surface[6] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Ivry dans 6 secondes ", emulatorText.color, 600);
    surface[7] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Ivry dans 7 secondes ", emulatorText.color, 600);
    surface[8] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Ivry dans 8 secondes ", emulatorText.color, 600);
    surface[9] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Ivry dans 9 secondes ", emulatorText.color, 600);
    surface[10] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Ivry dans 10 secondes ", emulatorText.color, 600);

    texture[0] = SDL_CreateTextureFromSurface(renderer, surface[0]);
    texture[1] = SDL_CreateTextureFromSurface(renderer, surface[1]);
    texture[2] = SDL_CreateTextureFromSurface(renderer, surface[2]);
    texture[3] = SDL_CreateTextureFromSurface(renderer, surface[3]);
    texture[4] = SDL_CreateTextureFromSurface(renderer, surface[4]);
    texture[5] = SDL_CreateTextureFromSurface(renderer, surface[5]);
    texture[6] = SDL_CreateTextureFromSurface(renderer, surface[6]);
    texture[7] = SDL_CreateTextureFromSurface(renderer, surface[7]);
    texture[8] = SDL_CreateTextureFromSurface(renderer, surface[8]);
    texture[9] = SDL_CreateTextureFromSurface(renderer, surface[9]);
    texture[10] = SDL_CreateTextureFromSurface(renderer, surface[10]);

    SDL_FreeSurface(surface[0]);
    SDL_FreeSurface(surface[1]);
    SDL_FreeSurface(surface[2]);
    SDL_FreeSurface(surface[3]);
    SDL_FreeSurface(surface[4]);
    SDL_FreeSurface(surface[5]);
    SDL_FreeSurface(surface[6]);
    SDL_FreeSurface(surface[7]);
    SDL_FreeSurface(surface[8]);
    SDL_FreeSurface(surface[9]);
    SDL_FreeSurface(surface[10]);
}
void leftMetroCourneuveText(SDL_Renderer *renderer, SDL_Surface *surface[], SDL_Texture *texture[], EmulatorText emulatorText)
{
    surface[0] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Courneuve dans 0 seconde ", emulatorText.color, 600);
    surface[1] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Courneuve dans 1 seconde ", emulatorText.color, 600);
    surface[2] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Courneuve dans 2 secondes ", emulatorText.color, 600);
    surface[3] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Courneuve dans 3 secondes ", emulatorText.color, 600);
    surface[4] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Courneuve dans 4 secondes ", emulatorText.color, 600);
    surface[5] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Courneuve dans 5 secondes ", emulatorText.color, 600);
    surface[6] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Courneuve dans 6 secondes ", emulatorText.color, 600);
    surface[7] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Courneuve dans 7 secondes ", emulatorText.color, 600);
    surface[8] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Courneuve dans 8 secondes ", emulatorText.color, 600);
    surface[9] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Courneuve dans 9 secondes ", emulatorText.color, 600);
    surface[10] = TTF_RenderText_Blended_Wrapped(emulatorText.font, "Courneuve dans 10 secondes ", emulatorText.color, 600);

    texture[0] = SDL_CreateTextureFromSurface(renderer, surface[0]);
    texture[1] = SDL_CreateTextureFromSurface(renderer, surface[1]);
    texture[2] = SDL_CreateTextureFromSurface(renderer, surface[2]);
    texture[3] = SDL_CreateTextureFromSurface(renderer, surface[3]);
    texture[4] = SDL_CreateTextureFromSurface(renderer, surface[4]);
    texture[5] = SDL_CreateTextureFromSurface(renderer, surface[5]);
    texture[6] = SDL_CreateTextureFromSurface(renderer, surface[6]);
    texture[7] = SDL_CreateTextureFromSurface(renderer, surface[7]);
    texture[8] = SDL_CreateTextureFromSurface(renderer, surface[8]);
    texture[9] = SDL_CreateTextureFromSurface(renderer, surface[9]);
    texture[10] = SDL_CreateTextureFromSurface(renderer, surface[10]);

    SDL_FreeSurface(surface[0]);
    SDL_FreeSurface(surface[1]);
    SDL_FreeSurface(surface[2]);
    SDL_FreeSurface(surface[3]);
    SDL_FreeSurface(surface[4]);
    SDL_FreeSurface(surface[5]);
    SDL_FreeSurface(surface[6]);
    SDL_FreeSurface(surface[7]);
    SDL_FreeSurface(surface[8]);
    SDL_FreeSurface(surface[9]);
    SDL_FreeSurface(surface[10]);
}