#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include "Station.h"
#include <math.h>
#include <SDL2/SDL_mixer.h>

int collision(int x, int y, int w, int h, int x2, int y2, int w2, int h2)
{

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;


    leftA = x;
    rightA = x + w;
    topA = y;
    bottomA = y + h;


    leftB = x2;
    rightB = x2 + w2;
    topB = y2;
    bottomB = y2 + h2;

    if (bottomA <= topB)
    {
        return 0;
    }

    if (topA >= bottomB)
    {
        return 0;
    }

    if (rightA <= leftB)
    {
        return 0;
    }

    if (leftA >= rightB)
    {
        return 0;
    }

    return 1;
}
void pushTraveller(Traveller *head_traveller, Traveller *new_traveller)
{
    new_traveller->next = head_traveller->next;
    head_traveller->next = new_traveller;
}
void generateTraveller(Traveller *head_traveller, Traveller *new_traveller, SDL_Renderer *renderer)
{
    Traveller *list = head_traveller;
    int x = rand() % (1150 + 1 - 10) + 10;
    int y = rand() % (480 + 1 - 370) + 370;
    int traveller_x = rand() % (700 + 1 - 500) + 500;
    int traveller_y = rand() % (676 + 1 - 576) + 576;  // genere position au hasard
    int gender;
    int nameNumber;
    int width = 16;
    int height = 16;
    while (list->next != NULL)
    {
        int listx = list->x;
        int listy = list->y;
        int collide = collision(list->x, list->y, width, height, traveller_x, traveller_y, width, height);
        if (collide == 1)
        {
            traveller_x = rand() % (700 + 1 - 500) + 500;
            traveller_y = rand() % (676 + 1 - 576) + 576;   //permet de generer les voyageur sans qu'il se colle
            list = head_traveller;
        }
        else
        {
            list = list->next;
        }
    }
    char *manName[5] = {"Jean", "Pierre", "Luc", "Benoit", "Paul"};
    char *womanName[5] = {"Sofiane", "Lise", "Julia", "Caroline", "Sophie"};  //genere nom au hasard
    int arraySize = 5; 
    gender = rand() % 2;
    nameNumber = rand() % arraySize;
    if (gender == 1)
    {
        new_traveller->gender = 1;
        new_traveller->name = manName[nameNumber];
        new_traveller->texture = loadTexture("./images/man.png", renderer);
    }
    else if (gender == 0)
    {
        new_traveller->gender = 0;
        new_traveller->name = womanName[nameNumber];
        new_traveller->texture = loadTexture("./images/woman.png", renderer);
    }
    new_traveller->x = traveller_x;
    new_traveller->y = traveller_y;
    new_traveller->h = height;
    new_traveller->w = width;  // pour la tractoir des voyageurs
    new_traveller->speed = 1;
    float radians = atan2(y - new_traveller->y, x - new_traveller->x);
    new_traveller->distance = hypot(x - new_traveller->x, y - new_traveller->y) / new_traveller->speed;  // pour la tractoir des voyageurs
    new_traveller->dx = cos(radians) * new_traveller->speed;
    new_traveller->dy = sin(radians) * new_traveller->speed;
}
void generateTraveller2(Traveller *head_traveller, Traveller *new_traveller, SDL_Renderer *renderer)
{
    Traveller *list = head_traveller;
    int x = rand() % (1150 + 1 - 10) + 10;
    int y = rand() % (170 + 1 - 80) + 80;
    int traveller_x = rand() % (700 + 1 - 500) + 500;
    int traveller_y = rand() % (-4 + 1 - -60) + -60;
    int gender;
    int nameNumber;
    int width = 16;
    int height = 16;
    while (list->next != NULL)
    {
        int listx = list->x;
        int listy = list->y;
        int collide = collision(list->x, list->y, width, height, traveller_x, traveller_y, width, height);
        if (collide == 1)
        {
            traveller_x =  rand() % (700 + 1 - 500) + 500;
            traveller_y = rand() % (-4 + 1 - -60) + -60;
            list = head_traveller;
        }
        else
        {
            list = list->next;
        }
    }
    char *manName[5] = {"Jean", "Pierre", "Luc", "Benoit", "Paul"};
    char *womanName[5] = {"Sofiane", "Lise", "Julia", "Caroline", "Sophie"};
    int arraySize = 5;
    gender = rand() % 2;
    nameNumber = rand() % arraySize;
    if (gender == 1)
    {
        new_traveller->gender = 1;
        new_traveller->name = manName[nameNumber];
        new_traveller->texture = loadTexture("./images/man.png", renderer);
    }
    else if (gender == 0)
    {
        new_traveller->gender = 0;
        new_traveller->name = womanName[nameNumber];
        new_traveller->texture = loadTexture("./images/woman.png", renderer);
    }
    new_traveller->x = traveller_x;
    new_traveller->y = traveller_y;
    new_traveller->h = height;
    new_traveller->w = width;
    new_traveller->speed = 1;
    float radians = atan2(y - new_traveller->y, x - new_traveller->x);
    new_traveller->distance = hypot(x - new_traveller->x, y - new_traveller->y) / new_traveller->speed;
    new_traveller->dx = cos(radians) * new_traveller->speed;
    new_traveller->dy = sin(radians) * new_traveller->speed;
}

void f_resetDestTravellerDown(Station *station, int nextMetroLeft, int *reset)
{
    Traveller *list = station->travellersDown;

    if (station->metroLeft.speed == 0 && station->metroLeft.x == 0 && *reset == 0)  // si le metro s'arrete
    {

        while (list->next != NULL)
        {
            int whichDoor = rand() % 7;
            float radians = atan2(station->metroLeft.doors[whichDoor].y - list->y, station->metroLeft.doors[whichDoor].x - list->x);
            list->distance = hypot(station->metroLeft.doors[whichDoor].x - list->x, station->metroLeft.doors[whichDoor].y - list->y);
            list->dx = cos(radians);
            list->dy = sin(radians);
            list = list->next;
        }
        *reset = 1;
    }
    else if (station->metroLeft.speed > 0 && *reset == 1) //si le metro démarre
    {

        while (list->next != NULL)
        {
            int x = rand() % (1150 + 1 - 10) + 10;
            int y = rand() % (470 + 1 - 390) + 390;
            float radians = atan2(y - list->y, x - list->x);
            list->distance = hypot(x - list->x, y - list->y);
            list->dx = cos(radians);
            list->dy = sin(radians);
            list = list->next;
        }
        *reset = 0;
    }
}
void f_resetDestTravellerUp(Station *station, int nextMetroRight, int *reset)
{
    Traveller *list = station->travellersUp;

    if (station->metroRight.speed == 0 && station->metroRight.x + station->metroRight.w  == 1200 && *reset == 0)
    {

        while (list->next != NULL)
        {
            int whichDoor = rand() % 7;
            float radians = atan2(station->metroRight.doors[whichDoor].y - list->y, station->metroRight.doors[whichDoor].x - list->x);
            list->distance = hypot(station->metroRight.doors[whichDoor].x - list->x, station->metroRight.doors[whichDoor].y - list->y);
            list->dx = cos(radians);
            list->dy = sin(radians);
            list = list->next;
        }
        *reset = 1;
    }
    else if (station->metroRight.speed > 0 && *reset == 1)
    {

        while (list->next != NULL)
        {
            int x = rand() % (1150 + 1 - 10) + 10;
            int y = rand() % (170 + 1 - 80) + 80;
            float radians = atan2(y - list->y, x - list->x);
            list->distance = hypot(x - list->x, y - list->y);
            list->dx = cos(radians);
            list->dy = sin(radians);
            list = list->next;
        }
        *reset = 0;
    }
}

void deleteTraveller(Station *station)
{
    Traveller *list = station->travellersDown;
    Traveller *nextNode;
    if (station->metroLeft.speed == 0 && station->metroLeft.x == 0)
    {
        if (station->travellersDown->distance <= 0)
        {
            station->travellersDown = list->next;
            SDL_DestroyTexture(list->texture);
            free(list);
            station->numberOfTravellerDown -= 1;
            return;
        }
        while(list != NULL){
            nextNode = list->next;
            if (nextNode && nextNode->distance <= 0)
            {
                list->next = nextNode->next;
                SDL_DestroyTexture(nextNode->texture);
                free(nextNode);
                station->numberOfTravellerDown -= 1;
                return;
            }
            else{
                list = nextNode;
            }
            
        }

    }
}
void deleteTraveller2(Station *station)
{
    Traveller *list = station->travellersUp;
    Traveller *nextNode;
    if (station->metroRight.speed == 0 && station->metroRight.x + station->metroRight.w  == 1200)
    {
        if (station->travellersUp->distance == 0)
        {
            station->travellersUp= list->next;
            SDL_DestroyTexture(list->texture);
            free(list);
            station->numberOfTravellerUp -= 1;
            return;
        }
        while(list != NULL){
            nextNode = list->next;
            if (nextNode && nextNode->distance == 0)
            {
                list->next = nextNode->next;
                SDL_DestroyTexture(nextNode->texture);
                free(nextNode);
                station->numberOfTravellerUp -= 1;
                return;
            }
            else{
                list = nextNode;
            }
            
        }

    }
}

void rendererTravellersDown(SDL_Renderer *renderer, Station *station)
{
    Traveller *list = station->travellersDown;
    while (list->next != NULL)
    {
        SDL_Rect travellerDown = {list->x, list->y, list->w, list->h};
        SDL_RenderCopy(renderer, list->texture, NULL, &travellerDown);
        if (list->distance)
        {

            list->distance -= 1;
            list->x += list->dx;  //faire bouger les voyageurs
            list->y += list->dy;
        }
        list = list->next;
    }
}
void rendererTravellersUp(SDL_Renderer *renderer, Station *station)
{
    Traveller *list = station->travellersUp;
    while (list->next != NULL)
    {
        SDL_Rect travellerUp = {list->x, list->y, list->w, list->h};
        SDL_RenderCopy(renderer, list->texture, NULL, &travellerUp);
        if (list->distance)
        {

            list->distance -= 1;
            list->x += list->dx;
            list->y += list->dy;
        }
        list = list->next;
    }
}

void doRender(SDL_Renderer *renderer, Station *station)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LEFT])
    {
        station->travellerUpside.x -= 3;
        printf(" position x : %f\n", station->travellerUpside.x);
        printf(" position y : %f\n", station->travellerUpside.y);
    }
    if (state[SDL_SCANCODE_RIGHT])
    {
        station->travellerUpside.x += 3;
        printf(" position x : %f\n", station->travellerUpside.x);
        printf(" position y : %f\n", station->travellerUpside.y);
    }
    if (state[SDL_SCANCODE_UP])
    {
        if(station->travellerUpside.y > 385){
        station->travellerUpside.y -= 3;
        }

        printf(" position x : %f\n", station->travellerUpside.x);
        printf(" position y : %f\n", station->travellerUpside.y);
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        station->travellerUpside.y += 3;
        printf(" position x : %f\n", station->travellerUpside.x);
        printf(" position y : %f\n", station->travellerUpside.y);
    }
  
    int collide = collision(station->travellerUpside.x,station->travellerUpside.y,station->travellerUpside.w,station->travellerUpside.h,
    station->metroLeft.x,station->metroLeft.y,station->metroLeft.w,station->metroLeft.h); 
    if(station->metroLeft.speed == 0 && station->travellerUpside.y < 390){
        station->travellerUpside.x = 600;
        station->travellerUpside.y = 574;
    }
    //affichage du renderer en arriere plan
    SDL_QueryTexture(station->stationTexture, NULL, NULL, 0, 0);
    SDL_RenderCopy(renderer, station->stationTexture, NULL, NULL);

    // creation d'un spite pour les travellers du  bas
    rendererTravellersDown(renderer, station);
    rendererTravellersUp(renderer, station);
    // creation du sprite metro allant ver la droite
    SDL_Rect metroRectRight = {station->metroRight.x, station->metroRight.y, 1200, 90};
    SDL_RenderCopy(renderer, station->metroRight.texture, NULL, &metroRectRight);

    // creation du sprite  metro
    SDL_Rect metroRectLeft = {station->metroLeft.x, station->metroLeft.y, 1200, 90};
    SDL_RenderCopy(renderer, station->metroLeft.texture, NULL, &metroRectLeft);
    SDL_Rect travellerUpsideRect = {station->travellerUpside.x, station->travellerUpside.y,station->travellerUpside.w,station->travellerUpside.h};
    SDL_RenderCopy(renderer, station->travellerUpside.texture, NULL, &travellerUpsideRect);
}

int f_nextMetroRight(Station *station, int *nextMetroRight, int *timeBeforeMetroStart)
{
    int diffTime = SDL_GetTicks() - *timeBeforeMetroStart;
    if (station->metroRight.x >= 1200 && *nextMetroRight == 0)
    {
        *timeBeforeMetroStart = SDL_GetTicks();
        *nextMetroRight = 1;
    }
    else if (diffTime > 10000 && *nextMetroRight == 1)
    {
        station->metroRight.x = -1200;
        *nextMetroRight = 0;
    }
    return diffTime;
}
int f_nextMetroLeft(Station *station, int *nextMetroLeft, int *timeBeforeMetroStart)
{

    int diffTime = SDL_GetTicks() - *timeBeforeMetroStart;
    if (station->metroLeft.x + station->metroLeft.w < 0 && *nextMetroLeft == 0)
    {
        *timeBeforeMetroStart = SDL_GetTicks();
        *nextMetroLeft = 1;
    }
    else if (diffTime > 10000 && *nextMetroLeft == 1)
    {
        station->metroLeft.x = 1200;
        *nextMetroLeft = 0;
    }
    return diffTime;
}
void moveMetro(Station *station)
{
    station->metroLeft.x -= station->metroLeft.speed;
    station->metroRight.x += station->metroRight.speed;
}
void init_MetroLeftDoor(Station *station)
{
    station->metroLeft.doors[0].x = 150;
    station->metroLeft.doors[0].y = 380;
    station->metroLeft.doors[1].x = 300;
    station->metroLeft.doors[1].y = 380;
    station->metroLeft.doors[2].x = 405;
    station->metroLeft.doors[2].y = 380;  //iniatiaslisation des porte de chaque metro
    station->metroLeft.doors[3].x = 550;
    station->metroLeft.doors[3].y = 380;
    station->metroLeft.doors[4].x = 750;
    station->metroLeft.doors[4].y = 380;
    station->metroLeft.doors[5].x = 900;
    station->metroLeft.doors[5].y = 380;
    station->metroLeft.doors[6].x = 1060;
    station->metroLeft.doors[6].y = 380;
}
void init_MetroRightDoor(Station *station)
{
    station->metroRight.doors[0].x = 150;
    station->metroRight.doors[0].y = 190;
    station->metroRight.doors[1].x = 300;
    station->metroRight.doors[1].y = 190;
    station->metroRight.doors[2].x = 405;
    station->metroRight.doors[2].y = 190;
    station->metroRight.doors[3].x = 550; //iniatiaslisation des porte de chaque metro
    station->metroRight.doors[3].y = 190;
    station->metroRight.doors[4].x = 750;
    station->metroRight.doors[4].y = 190;
    station->metroRight.doors[5].x = 900;
    station->metroRight.doors[5].y = 190;
    station->metroRight.doors[6].x = 1060;
    station->metroRight.doors[6].y = 190;
}
SDL_Texture *loadTexture(char *source, SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load(source);
    if (surface == NULL)
    {
        printf("Could not create a surface");  // charger les texture dans une variale de type texture
        exit(0);
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

int f_stopMetroRight(Station *station, int *timeBeforeMetroStop, int *stopMetroRight,Mix_Chunk *voice)
{
    int diffTime = SDL_GetTicks() - *timeBeforeMetroStop;
    if (station->metroRight.x + station->metroRight.w == 1200 && *stopMetroRight == 0)
    {
        *timeBeforeMetroStop = SDL_GetTicks();
        station->metroRight.speed = 0;
        *stopMetroRight = 1;
    }
    else if (*stopMetroRight == 1 && diffTime >= 5000)
    {
        station->metroRight.speed = 4;
        *stopMetroRight = 0;
       
    }
    return diffTime;
}
int f_stopMetroLeft(Station *station, int *timeBeforeMetroStop, int *stopMetroLeft)
{
    int diffTime = SDL_GetTicks() - *timeBeforeMetroStop;
    if (station->metroLeft.x == 0 && *stopMetroLeft == 0)
    {
        *timeBeforeMetroStop = SDL_GetTicks();
        station->metroLeft.speed = 0;
        *stopMetroLeft = 1;
    }
    else if (*stopMetroLeft == 1 && diffTime >= 5000)
    {
        station->metroLeft.speed = 4;
        *stopMetroLeft = 0;
        
    }
    return diffTime;
}
void processEvents(SDL_Window *window, int *done)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_WINDOWEVENT_CLOSE:
        {
            if (window)
            {
                SDL_DestroyWindow(window);
                window = NULL;
                *done = 1;
            }
        }
        break;
        case SDL_KEYDOWN:
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                *done = 1;
                break;
            }
        }
        break;
        case SDL_QUIT:
            *done = 1;
            break;
        }
    }
    
}
