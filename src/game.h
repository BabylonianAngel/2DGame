#ifndef GAME_H
#define GAME_H

#include "sdl2.h"
#include "constants.h"
#include <stdbool.h>


// --------------- //
// Data structures //
// --------------- //

enum GameState {
    PLAYING,                // Still playing
    GAME_OVER              // End of the game
};

struct Arc
{
    //can take different shapes
    float x;
    float y;
    float rad;
    float start;
    float end;
    int r,g,b,a;
};


struct Point {
    float x;
    float y;
};
struct Cursor{
   struct Point leftCorner;
   struct Point rightCorner;
   struct Point topCorner;
   struct Point center;
};
struct Time
{
    struct AnimatedSpritesheet *HundredOfSeconds; // each 100 sec
    struct AnimatedSpritesheet *TenSec; // each 10 sec
    struct AnimatedSpritesheet *sec; // The seconds
    struct AnimatedSpritesheet *ms; // The milisec
    struct AnimatedSpritesheet *Dot; // The .

};


struct Game {
    enum GameState state;           // The state of the game
    struct Spritesheet *background; // The game background
    struct Time Timer; // The timer
    struct Arc arc1,arc2,arc3,arc4; // Arcs walls of the game
    struct Cursor *cursor;          // Moving cursor
    SDL_Renderer *renderer;         // The renderer

};

// --------- //
// Functions //
// --------- //

/**
 * Creates a new game.
 *
 * @param renderer  The renderer
 * @return          A pointer to the menu, NULL if there was an error
 */
struct Game *Game_initialize(SDL_Renderer *renderer);


/**
 * Start running the game.
 *
 * @param menu  The menu to show
 */
void Game_run(struct Game *game,int difficulty);

/**
 * Delete the game.
 *
 * @param menu  The menu to delete
 */



// je suis n'ais pas vraiment le temp de documenter ces fonctions
double Set_Speed(int difficulty);
void Arcs_Move(struct Game *game, float speed);
void random_Arc1(struct Game *game);
void random_Arc2(struct Game *game);
void random_Arc3(struct Game *game);
void random_Arc4(struct Game *game);
void render_Game(struct Game *game);
float Cursor_Distance_From_Center(struct Game *game);
void render_basic_elements(struct Game *game);
void Game_delete(struct Game *game);
void Move_Cursor_Left(struct Game *game);
void Move_Cursor_Right(struct Game *game);
struct Point counterClockwise_rotate_point(float cx,float cy,float angle,struct Point p);
struct Point Clockwiser_rotate_point(float cx,float cy,float angle,struct Point p);
void Check_GameOver_Arc1(struct Game *game);
void Check_GameOver_Arc2(struct Game *game);
void Check_GameOver_Arc3(struct Game *game);
void Check_GameOver_Arc4(struct Game *game);
void GameOver(struct Game *game);
bool IsPointOnArc(struct Point p, struct Arc a);
void checkPoint(struct Point p, struct Arc a) ;
 float to_degrees(float radians);


#endif
