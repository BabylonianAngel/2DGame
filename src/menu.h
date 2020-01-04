#ifndef MENU_H
#define MENU_H

#include "sdl2.h"
#include "constants.h"

// --------------- //
// Data structures //
// --------------- //
enum Difficulty{
    Easy,
    Medium,
    Hard
};

enum MenuState {
    MENU_PLAY_FOCUS,       // Play choice has focus
    MENU_QUIT_FOCUS,       // Quit choice has focus
    MENU_EASY_FOCUS,       //easy choice has focus
    MENU_MEDIUM_FOCUS,       // medium choice has focus
    MENU_HARD_FOCUS,       // hard choice has focus
    MENU_PLAY,             // Play has been chosen
    MENU_QUIT              // Play has been chosen
};

struct Menu {
    enum MenuState state;           // The choice of the user
    enum Difficulty difficulty;           // The Difficulty
    struct Spritesheet *background; // The menu background
    struct Spritesheet *title;      // The title sprite
    struct Spritesheet *play;       // The play sprite
    struct Spritesheet *quit;       // The quit sprite
    struct Spritesheet *author;     // me
                                    //difficulty
    struct Spritesheet *Esay;     
    struct Spritesheet *Medium;     
    struct Spritesheet *Hard;       
    SDL_Renderer *renderer;         // The renderer
};

// --------- //
// Functions //
// --------- //

/**
 * Creates a new menu.
 *
 * @param renderer  The renderer
 * @return          A pointer to the menu, NULL if there was an error
 */
struct Menu *Menu_initialize(SDL_Renderer *renderer);

/**
 * Start running the menu.
 *
 * @param menu  The menu to show
 */
void Menu_run(struct Menu *menu);

/**
 * Delete the menu.
 *
 * @param menu  The menu to delete
 */
void Menu_delete(struct Menu *menu);

#endif
