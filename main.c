#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "Station.h"
#include "Timer.h"
#include <SDL2/SDL_mixer.h>
#include "Menu.h"
int main(int argc, char *argv[])
{

    SDL_Window *window; // declaration d'unde fentre
    SDL_Renderer *renderer; //declaration d'une fenetre


    putenv((char *)"SDL_AUDIODRIVER=alsa"); // configurer audio driver
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0) // initalisation de la video,son et temps
    {
        fprintf(stderr, "Error to initalize SDl_Init  : %s", SDL_GetError());
        goto Quit; // si il y a erreur quitte le programme
    }
    if (TTF_Init() == -1) // initialiser la police
    {
        fprintf(stderr, "Error to initialize  TTF_Init : %s\n", TTF_GetError());
        goto Quit;
    }
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); // configuerer l'audio

    printf(" sound error : %s \n", Mix_GetError());
    Mix_Chunk *courneuveSound; // son metro ver couneuve
    Mix_Chunk *ivrySound; // son metro vers ivry
    Mix_Music *backgroundMusic; // music de fond
    courneuveSound = Mix_LoadWAV("./son/courneuve.wav");
    ivrySound = Mix_LoadWAV("./son/ivry.wav");
    backgroundMusic = Mix_LoadMUS("./son/backgroundMusic.mp3");
    Mix_VolumeMusic(MIX_MAX_VOLUME / 10);
    Mix_PlayMusic(backgroundMusic, -1);

    printf(" sound error : %s \n", Mix_GetError());
    Station station;
    EmulatorText timerText;       //  creation de police
    EmulatorText timerText2;
    EmulatorText timerText3;
    EmulatorText timerText4;
    Menu menu;

// variiable pour la gestion des arret du train
    int timeBeforeRightMetroStop = 0;     
    int timeBeforeRightMetroStart = 0;
    int timeBeforeLeftMetroStop = 0;
    int timeBeforeLeftMetroStart = 0;
    int stopMetroRight = 0;
    int stopMetroLeft = 0;
    int resetDestTravellerDown = 0;
    int resetDestTravellerUp = 0;
    int diffTime = 0;
    int diffTime2 = 0;
    int diffTime3 = 0;
    int diffTime4 = 0;
//Surface pour la police
    SDL_Surface *surfaceIvry[12];
    SDL_Texture *textureIvry[12];
    SDL_Surface *surfaceCourneuve[12];
    SDL_Texture *textureCourneuve[12];
// configuer l'emplacement et la taille du joueur
    station.travellerUpside.x = 600;
    station.travellerUpside.y = 400;
    station.travellerUpside.w = 17;
    station.travellerUpside.h = 17;
//configurer la taille et l'emplacement du metro vers la droite
    station.metroRight.x = -1200;
    station.metroRight.y = 194;
    station.metroRight.h = 90;
    station.metroRight.w = 1200;
    station.metroRight.speed = 4;
    init_MetroRightDoor(&station);
// 
    station.metroLeft.x = 0;
    station.metroLeft.y = 290;
    station.metroLeft.h = 90;
    station.metroLeft.w = 1200;
    station.metroLeft.speed = 4;
    init_MetroLeftDoor(&station);
// parametre les texts
    timerText.size = 65;
    timerText.font = TTF_OpenFont("./fonts/stedmi.ttf", timerText.size);
    timerText.color.r = 255;
    timerText.color.g = 193;
    timerText.color.b = 7;
    timerText.x = 1080; //1100
    timerText.y = 4;    //4
    timerText.w = 140;
    timerText.h = 40;

    timerText2.size = 65;
    timerText2.font = TTF_OpenFont("./fonts/stedmi.ttf", timerText.size);
    timerText2.color.r = 255;
    timerText2.color.g = 193;
    timerText2.color.b = 7;
    timerText2.x = 13; //1100
    timerText2.y = 4;  //4
    timerText2.w = 140;
    timerText2.h = 40;

    timerText3.color.g = 193;
    timerText3.color.b = 7;
    timerText3.x = 1080; //1100
    timerText3.y = 520;  //4
    timerText3.w = 140;
    timerText3.h = 50;

    timerText4.size = 65;
    timerText4.font = TTF_OpenFont("./fonts/stedmi.ttf", timerText.size);
    timerText4.color.r = 255;
    timerText4.color.g = 193;
    timerText4.color.b = 7;
    timerText4.x = 13;  //1100
    timerText4.y = 520; //4
    timerText4.w = 140;
    timerText4.h = 50;

// pour l'intervalle de temps pour chaque train
    int nextMetroRight = 0;
    int nextMetroLeft = 0;

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",        // window title
        SDL_WINDOWPOS_UNDEFINED, // initial x position
        SDL_WINDOWPOS_UNDEFINED, // initial y position
        1200,                    // width, in pixels
        576,                     // height, in pixels
        0                        // flags - see below
    );

    if (window == NULL)
    {
       
        printf("Could not create window: %s\n", SDL_GetError());
        goto Quit;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
   
        printf("Could not create a renderer: %s\n", SDL_GetError());
        goto Quit;
    }
    // charger les images dans les variable textures
    station.metroLeft.texture = loadTexture("./images/metroLeft.png", renderer);
    station.metroRight.texture = loadTexture("./images/metroRight.png", renderer);
    station.travellerUpside.texture = loadTexture("./images/player.png", renderer);
    station.stationTexture = loadTexture("./images/station.png", renderer);

    //Generate a new link list list of travellerDowside;
    station.numberOfTravellerDown = 30;
    station.travellersDown = (struct Traveller *)malloc(sizeof(struct Traveller));
    station.travellersDown->next = NULL;

    generateTraveller(station.travellersDown, station.travellersDown, renderer);
    for (int i = 0; i < station.numberOfTravellerDown; i++)
    {
        Traveller *new_traveller = (struct Traveller *)malloc(sizeof(struct Traveller));
        generateTraveller(station.travellersDown, new_traveller, renderer);
        pushTraveller(station.travellersDown, new_traveller);
    }

    //Generate a new link list list of travellerUpside ;
    station.numberOfTravellerUp = 30;
    station.travellersUp = (struct Traveller *)malloc(sizeof(struct Traveller));
    station.travellersUp->next = NULL;
    generateTraveller(station.travellersUp, station.travellersUp, renderer);
    for (int i = 0; i < station.numberOfTravellerUp; i++)
    {
        Traveller *new_traveller = (struct Traveller *)malloc(sizeof(struct Traveller));
        generateTraveller2(station.travellersUp, new_traveller, renderer);
        pushTraveller(station.travellersUp, new_traveller);
    }

    rightMetroIvryText(renderer, surfaceIvry, textureIvry, timerText);
    leftMetroCourneuveText(renderer, surfaceCourneuve, textureCourneuve, timerText);
    initMenu(renderer, &menu);
    menu.option1.texture = menu.option1.textures[0];
    int done = 0;
    //comparer le nombre de voyageur avec nombre actuell
    int travellerNb = 0;
    int travellerNb2 = 0;
    // permuter entre menu et jeu
    int interface = 0;
    //changer d'option
    int selected = 0;
    while (!done)
    {
        processEvents(window, &done); // pou la fermeture de la fenetre
        if (interface == 0)
        {
            renderMenu(renderer, &menu, &selected, &interface, &done);   /// interface du menu
            renderOption1(renderer, &menu, selected);
        }
        else if (interface == 1)
        {
            travellerNb = 30 - station.numberOfTravellerDown;
            travellerNb2 = 30 - station.numberOfTravellerUp;

            doRender(renderer, &station); // afficher les image de la station
            SDL_Rect position;
            deleteTraveller2(&station);// supprime les voyageur losqu'il entre dans le train
            deleteTraveller(&station);
            f_resetDestTravellerDown(&station, nextMetroLeft, &resetDestTravellerDown); // met a jour le positionnement des voyageur
            f_resetDestTravellerUp(&station, nextMetroRight, &resetDestTravellerUp); 
            f_resetDestTravellerDown(&station, nextMetroLeft, &resetDestTravellerDown); // met a jour le positionnement des voyageur
            diffTime4 = f_nextMetroLeft(&station, &nextMetroLeft, &timeBeforeLeftMetroStart); // récupère combien de temps il reste pour le prochain train
            diffTime3 = f_stopMetroLeft(&station, &timeBeforeLeftMetroStop, &stopMetroLeft); // recuperer combien de temps il il reste pour que le metro redémarre 
            moveMetro(&station);
            diffTime = f_stopMetroRight(&station, &timeBeforeRightMetroStop, &stopMetroRight, courneuveSound);   // interface du jeu
            diffTime2 = f_nextMetroRight(&station, &nextMetroRight, &timeBeforeRightMetroStart);
            //      printf(" number of travellers %d", station.numberOfTraveller);
            textRendererUpside(&timerText, renderer, &station, &diffTime2, textureIvry, ivrySound); // affiche le text qui sert de chronometre
            textRendererUpside(&timerText2, renderer, &station, &diffTime2, textureIvry, ivrySound);
            textRendererDownside(&timerText3, renderer, &station, &diffTime4, textureCourneuve, courneuveSound);
            textRendererDownside(&timerText4, renderer, &station, &diffTime4, textureCourneuve, courneuveSound);

            for (int i = 0; i < travellerNb; i++)
            {

                printf(" sound error : %s \n", Mix_GetError());
                Traveller *new_traveller = (struct Traveller *)malloc(sizeof(struct Traveller));  //regénère les voyageur lorsqu'il y en a moin de 30
                generateTraveller(station.travellersDown, new_traveller, renderer);
                pushTraveller(station.travellersDown, new_traveller);
                station.numberOfTravellerDown += 1;
            }
            //reg
            for (int i = 0; i < travellerNb2; i++)
            {

                printf(" sound error : %s \n", Mix_GetError());
                Traveller *new_traveller = (struct Traveller *)malloc(sizeof(struct Traveller)); //regénère les voyageur lorsqu'il y en a moin de 30
                generateTraveller2(station.travellersUp, new_traveller, renderer);
                pushTraveller(station.travellersUp, new_traveller);
                station.numberOfTravellerUp += 1;
            }
        }
        SDL_RenderPresent(renderer); // afficher le graphisme
    }
Quit:
    SDL_DestroyRenderer(renderer);
    // Close and destroy the window
    SDL_DestroyWindow(window);
    TTF_CloseFont(timerText.font);
    Mix_FreeChunk(courneuveSound); // liberation de la memoire
    Mix_FreeChunk(ivrySound);
    TTF_Quit();
    // Clean up
    SDL_Quit();

    return 0;
}
