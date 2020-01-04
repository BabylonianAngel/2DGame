#include "application.h"
#include "sdl2.h"
#include <stdio.h>
#include <time.h>

struct Application *Application_initialize()
{
    //ctreates the application
    struct Application *application;
    //To randomize numbers
    srand(time(NULL));
    //This function initializes the subsystems specified
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "SDL failed to initialize: %s\n", SDL_GetError());
        return NULL;
    }
    // Priority of 1. linear filtering (supported by OpenGL and Direct3D)
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        fprintf(stderr, "Warning: Linear texture filtering not enabled!");
    }
    //if evrything is ok,
    application = malloc(sizeof(struct Application));
    application->window = SDL_CreateWindow("MyGame", //creating the window named ...
                                           SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                           SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (application->window == NULL)
    { //if there is a problem.
        fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
        return NULL;
    }
    //Renderer, Create a 2D rendering context for a window.
    application->renderer = SDL_CreateRenderer(application->window, -1,
                                               SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (application->renderer == NULL)
    {
        fprintf(stderr, "Renderer could not be created: %s\n", SDL_GetError());
        return NULL;
    }
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        fprintf(stderr, "SDL_image failed to initialize: %s\n", IMG_GetError());
        return NULL;
    }
    //initialising the menu here.
    application->menu = Menu_initialize(application->renderer);
    if (application->menu == NULL)
    {
        fprintf(stderr, "Failed to initialize menu: %s\n", IMG_GetError());
        return NULL;
    }
    application->state = APPLICATION_STATE_MENU;
    //audio
    application->sound = NULL;
    return application;
}

void Application_run(struct Application *application)
{
    Playmusic(application);
    while (application->state != APPLICATION_STATE_QUIT)
    { //while the user does not quit
        //Managing States
        switch (application->state)
        {
        case APPLICATION_STATE_MENU:
            Menu_run(application->menu);
            if (application->menu->state == MENU_QUIT)
            {
                application->state = APPLICATION_STATE_QUIT;
            }
            else if (application->menu->state == MENU_PLAY)
            {
                // the user wants to play
                application->state = APPLICATION_STATE_PLAY;
            }
            break;
        case APPLICATION_STATE_PLAY:
            //  Running the game.
            application->game = Game_initialize(application->renderer);
            Game_run(application->game, application->menu->difficulty);
            if (application->game->state == GAME_OVER) // if the payer loose, we quit the game to the menu.
            {
                application->state = APPLICATION_STATE_MENU;
            }
            break;
        case APPLICATION_STATE_QUIT:
            break;
        }
    }
}

void Playmusic(struct Application *application){
    //mixer
    int audio_rate = 22050; Uint16 audio_format = AUDIO_S16SYS; int audio_channels = 2; int audio_buffers = 4096;

    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) { fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());}
    //Mix_Chunk *sound = NULL;

    application->sound = Mix_LoadWAV("../assets/courtesy.wav"); if(application->sound == NULL) { fprintf(stderr, "Unable to load WAV file: %s\n", Mix_GetError()); }
    int channel;

    channel = Mix_PlayChannel(-1, application->sound, 0); if(channel == -1) { fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError()); }
}


void Application_shutDown(struct Application *application)
{
    SDL_DestroyRenderer(application->renderer);
    SDL_DestroyWindow(application->window);
    Menu_delete(application->menu);
    // clean up audio
    Mix_FreeChunk(application->sound);
    Mix_CloseAudio();
    free(application);
    application = NULL;
    IMG_Quit();
    SDL_Quit();
}
