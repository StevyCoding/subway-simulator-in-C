#ifndef STATION_H
#define STATION_H
#include <SDL2/SDL_mixer.h>
typedef struct Door{
    float x,y;
}Door;
typedef struct Traveller
{
    float x, y,w,h;
    SDL_Texture *texture;
    char *name;
    int gender;
    int age;
    int distance;
    float dx;
    float dy;
    float speed;
   struct Traveller *next;
} Traveller;
typedef struct Metro
{
    SDL_Texture *texture;
    int x, y, w, h, speed;
    char *name;
    Door doors[7];
} Metro;
typedef struct
{
    int numberOfTravellerDown;
    int numberOfTravellerUp;
    Traveller travellerUpside;
    Traveller *travellersDown;
    Traveller *travellersUp;
    Metro metroRight;
    Metro metroLeft;
    SDL_Texture *stationTexture;

} Station;
int collision(int x,int y, int w, int h ,int x2,int y2,int w2, int h2);
void pushTraveller(Traveller* head_traveller,Traveller* new_traveller );
void generateTraveller(Traveller *head_traveller,Traveller* new_traveller,SDL_Renderer *renderer);
void deleteTraveller(Station *Station);
void rendererTravellersDown(SDL_Renderer *renderer,Station *station);
void f_resetDestTravellerDown(Station *station, int nextMetroLeft,int *reset);
void doRender(SDL_Renderer *renderer, Station *station);
int f_nextMetroRight(Station* station, int* nextMetroRight, int *timeBeforeMetroStart );
int f_nextMetroLeft(Station *station, int *nextMetroLeft, int *timeBeforeMetroStart);
int f_stopMetroLeft(Station *station, int *timeBeforeMetroStop, int *stopMetroLeft);
void moveMetro(Station* station);
void init_MetroLeftDoor(Station* station);
SDL_Texture *loadTexture(char *source, SDL_Renderer *renderer);
int f_stopMetroRight(Station* station,int *timeBeforeMetroStop,int* stopMetroRight,Mix_Chunk *voice);
void processEvents(SDL_Window *window,int* done);

void rendererTravellersUp(SDL_Renderer *renderer, Station *station);
void deleteTraveller2(Station *Station);
void generateTraveller2(Traveller *head_traveller, Traveller *new_traveller, SDL_Renderer *renderer);
void f_resetDestTravellerUp(Station *station, int nextMetroRight, int *reset);
void init_MetroRightDoor(Station *station);
#endif