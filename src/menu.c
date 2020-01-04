#include "menu.h"
#include "spritesheet.h"
#include "sdl2.h"

#include <stdbool.h>

struct Menu *Menu_initialize(SDL_Renderer *renderer)
{
    struct Menu *menu;
    menu = malloc(sizeof(struct Menu));
    menu->renderer = renderer;
    menu->state = MENU_PLAY_FOCUS;
    menu->background = Spritesheet_create(BACKGROUND_FILENAME, 1, 1, 1, renderer);
    menu->title = Spritesheet_create(TITLE_FILENAME, 1, 1, 1, renderer);
    menu->play = Spritesheet_create(PLAY_FILENAME, 1, 1, 1, renderer);
    menu->quit = Spritesheet_create(QUIT_FILENAME, 1, 1, 1, renderer);
    menu->author = Spritesheet_create(AUTHOR_FILENAME, 1, 1, 1, renderer);
    menu->Esay = Spritesheet_create(DIFFICULTY_FILENAME_EASY, 1, 1, 1, renderer);
    menu->Medium = Spritesheet_create(DIFFICULTY_FILENAME_MEDIUM, 1, 1, 1, renderer);
    menu->Hard = Spritesheet_create(DIFFICULTY_FILENAME_HARD, 1, 1, 1, renderer);
    return menu;
}

int Menu_alpha(bool chosen)
{
    return chosen ? 255 : 64;
}

void Menu_run(struct Menu *menu)
{
    SDL_Event e; //This is a event listner
    menu->state = -1;
    //While the user dont quit the menu
    while (menu->state != MENU_PLAY && menu->state != MENU_QUIT)
    {
        while (SDL_PollEvent(&e) != 0)
        { //while there is no events, listen.
            if (e.type == SDL_QUIT)
            { // if the user Clicks on red X.
                menu->state = MENU_QUIT;
            }
            else if (e.type == SDL_KEYDOWN)
            { //Detect the type of the event.
                if (menu->state != MENU_EASY_FOCUS && menu->state != MENU_MEDIUM_FOCUS && menu->state != MENU_HARD_FOCUS)
                {
                    switch (e.key.keysym.sym)
                    {                                                  //In this case, Left and Right keys.
                    case SDLK_LEFT:                                    // PLAY BUTTON
                        menu->state = menu->state == MENU_PLAY_FOCUS ? //this basicaly toggles betwen quit and
                                          MENU_QUIT_FOCUS: MENU_PLAY_FOCUS; // play focus
                        break;
                    case SDLK_RIGHT: // QUIT BUTTON
                        menu->state = menu->state == MENU_PLAY_FOCUS ? MENU_QUIT_FOCUS : MENU_PLAY_FOCUS;
                        break;
                    case SDLK_RETURN: // ENTER
                        if (menu->state == MENU_PLAY_FOCUS)
                        {
                            menu->state = MENU_PLAY;
                        }
                        else if (menu->state == MENU_QUIT_FOCUS)
                        {
                            menu->state = MENU_QUIT;
                        }
                        break;
                    case SDLK_DOWN:
                        menu->state = MENU_EASY_FOCUS;
                        break;
                    }
                }
                else
                {
                    //Here, The user is choosing the difficulty
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_LEFT:
                        menu->state = menu->state == MENU_EASY_FOCUS ? MENU_HARD_FOCUS : ( menu->state == MENU_MEDIUM_FOCUS ? MENU_EASY_FOCUS : MENU_MEDIUM_FOCUS);
                        break;
                    case SDLK_RIGHT:
                        menu->state = menu->state == MENU_MEDIUM_FOCUS ? MENU_HARD_FOCUS : (menu->state == MENU_EASY_FOCUS ? MENU_MEDIUM_FOCUS : MENU_EASY_FOCUS);
                        break;
                    case SDLK_RETURN: // The user made his choice
                        if(menu->state == MENU_EASY_FOCUS ){menu->difficulty=Easy;} else if (menu->state == MENU_MEDIUM_FOCUS ){menu->difficulty=Medium;}else if (menu->state == MENU_HARD_FOCUS ){menu->difficulty=Hard;}
                        menu->state = MENU_PLAY_FOCUS;
                        break;
                    case SDLK_UP:
                        menu->state = MENU_PLAY_FOCUS;
                        break;
                    }
                }
            }
        }
        //Rendering the visual components inside the menu.
        SDL_SetRenderDrawColor(menu->renderer, 0x00, 0x00, 0x00, 0x00);
        //Clears any previous rendering on the menue.
        SDL_RenderClear(menu->renderer);
        // this sets the background in the application.
        Spritesheet_render(menu->background, BACKGROUND_X, BACKGROUND_Y, 255, 0);
        // Sets the title.
        Spritesheet_render(menu->title, TITLE_X, TITLE_Y, 255, 0);
        // Sets the play button
        Spritesheet_render(menu->play, PLAY_X, PLAY_Y, Menu_alpha(menu->state == MENU_PLAY_FOCUS), 0);
        // the quit buton
        Spritesheet_render(menu->quit, QUIT_X, QUIT_Y, Menu_alpha(menu->state == MENU_QUIT_FOCUS), 0);
        // the author
        Spritesheet_render(menu->author, SCREEN_WIDTH-100, SCREEN_HEIGHT-30, 255, 0);
        // the difficulty
        Spritesheet_render(menu->Esay, DIFFICULTY_X_EASY, DIFFICULTY_Y, Menu_alpha(menu->state == MENU_EASY_FOCUS), 0);
        Spritesheet_render(menu->Medium, DIFFICULTY_X_MEDIUM, DIFFICULTY_Y, Menu_alpha(menu->state == MENU_MEDIUM_FOCUS), 0);
        Spritesheet_render(menu->Hard, DIFFICULTY_X_HARD, DIFFICULTY_Y, Menu_alpha(menu->state == MENU_HARD_FOCUS), 0);

        //Update the screen with rendering performed.
        SDL_RenderPresent(menu->renderer);
    }
}

void Menu_delete(struct Menu *menu)
{
    if (menu != NULL)
    {
        // Deletes all the components.
        Spritesheet_delete(menu->background);
        Spritesheet_delete(menu->title);
        Spritesheet_delete(menu->play);
        Spritesheet_delete(menu->quit);
        free(menu);
    }
}
