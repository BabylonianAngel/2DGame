#include "game.h"
#include "spritesheet.h"
#include "sdl2.h"

#include <stdbool.h>

#define MIDDLE_SCREEN_X SCREEN_WIDTH / 2
#define MIDDLE_SCREEN_Y SCREEN_HEIGHT / 2
#define CURSOR_POSITION_X MIDDLE_SCREEN_X
#define CURSOR_POSITION_Y MIDDLE_SCREEN_Y + 15

struct Game *Game_initialize(SDL_Renderer *renderer)
{
    printf("hello\n");
    struct Game *game;
    game = malloc(sizeof(struct Game));
    game->cursor = malloc(sizeof(struct Cursor));
    game->renderer = renderer;
    game->state = PLAYING;
    game->background = Spritesheet_create("../assets/Space.png", 1, 1, 1, renderer);
    //initializing cursor coordonates
    game->cursor->leftCorner.x = CURSOR_POSITION_X - 10;
    game->cursor->leftCorner.y = CURSOR_POSITION_Y;
    game->cursor->rightCorner.x = CURSOR_POSITION_X + 10;
    game->cursor->rightCorner.y = CURSOR_POSITION_Y;
    game->cursor->topCorner.x = CURSOR_POSITION_X;
    game->cursor->topCorner.y = CURSOR_POSITION_Y + 10;
    //initialising the center of the cursor as a rotation point.
    game->cursor->center.x = (game->cursor->leftCorner.x + game->cursor->rightCorner.x + game->cursor->topCorner.x) / 3;
    game->cursor->center.y = (game->cursor->leftCorner.y + game->cursor->rightCorner.y + game->cursor->topCorner.y) / 3;
    //intiaizing timer
    game->Timer.HundredOfSeconds = AnimatedSpritesheet_create("../assets/digits-small.png",1,11,1,100000,renderer);
    game->Timer.TenSec = AnimatedSpritesheet_create("../assets/digits-small.png",1,11,1,10000,renderer);
    game->Timer.sec = AnimatedSpritesheet_create("../assets/digits-small.png",1,11,1,1000,renderer);
    game->Timer.ms = AnimatedSpritesheet_create("../assets/digits-small.png",1,11,1,100,renderer);
    game->Timer.Dot = AnimatedSpritesheet_create("../assets/digits-small.png",1,11,1,10,renderer);
    //running the timer
    AnimatedSpritesheet_setCol(game->Timer.Dot,10);
    AnimatedSpritesheet_setCol(game->Timer.HundredOfSeconds,0);
    AnimatedSpritesheet_setCol(game->Timer.TenSec,0);
    AnimatedSpritesheet_setCol(game->Timer.sec,0);
    AnimatedSpritesheet_setCol(game->Timer.ms,0);
    AnimatedSpritesheet_run(game->Timer.HundredOfSeconds);
    AnimatedSpritesheet_run(game->Timer.TenSec);
    AnimatedSpritesheet_run(game->Timer.sec);
    AnimatedSpritesheet_run(game->Timer.ms);

    //initialising Arcs
    random_Arc1(game);
    //arc2
    random_Arc2(game);
    //arc3
    random_Arc3(game);
    //arc4
    random_Arc4(game);

    //We are payng
    game->state = PLAYING;

        if (game == NULL) {
        fprintf(stderr, "Failed to initialize The game: %s\n", IMG_GetError());
        return NULL;
    }   
    return game;
}

void Game_run(struct Game *game,  int difficulty)
{
    //-------------------------------------------------------
    //dont forget to handle errors on the components
    //-------------------------------------------------------

    //depends on the difficulty
    double speed = Set_Speed(difficulty);
    SDL_Event event;
    SDL_bool GameRunning = SDL_TRUE;

    render_basic_elements(game);

    while (GameRunning) //while the player didnt loose, the game is running
    {
        //setting the speed
        Arcs_Move(game, speed);
        //Arcs animation
        render_Game(game);
        while (SDL_PollEvent(&event))
        {
            /* code */
            switch (event.type)
            {
            //when a key is pressed
            case SDL_KEYDOWN:
                //Detecting the pressed key
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:

                    printf("Left key pressed\n");
                    Move_Cursor_Left(game);
                    break;
                case SDLK_RIGHT:
                    printf("Right key pressed\n");
                    Move_Cursor_Right(game);
                    break;

                default:
                    break;
                }
                break;
            //when a key is unpressed
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    printf("Left key up\n");
                    break;
                case SDLK_RIGHT:
                    printf("Right key up\n");
                    break;

                default:
                    break;
                }
                break;
            //if the user quit the game
            case SDL_QUIT:
                //The game is over
                GameRunning = SDL_FALSE;
                game->state = GAME_OVER;
                break;

            default:
                break;
            }
        }
        //If the game is over
        if (game->state==GAME_OVER){ GameRunning=SDL_FALSE;GameOver(game);}
        
    }
}
double Set_Speed(int difficulty){
    double speed=1;
    switch (difficulty)
    {
    case 0:
        speed = 1;
        break;
    case 1:
        speed = 2;
        break;
    case 2:
        speed = 3;
        break;
    
    default:
        break;
    }
    return speed;
};

void GameOver(struct Game *game){
    SDL_RenderClear(game->renderer);
    game->background = Spritesheet_create("../assets/Gameover.png", 1, 1, 1, game->renderer);
    Spritesheet_render(game->background, BACKGROUND_X, BACKGROUND_Y, 255, 0);
    SDL_RenderPresent(game->renderer);
    SDL_Delay(1000);
    Game_delete(game);
};

void Game_delete(struct Game *game)
{
    if (game != NULL)
    {
        Spritesheet_delete(game->background);
        free(game->cursor);
        free(game->Timer.Dot);
        free(game->Timer.ms);
        free(game->Timer.sec);
        free(game->Timer.TenSec);
        free(game->Timer.HundredOfSeconds);
        free(game);
    }
};
void Arcs_Move(struct Game *game, float speed)
{
    game->arc1.rad = game->arc1.rad - speed;
    game->arc2.rad = game->arc2.rad - speed;
    game->arc3.rad = game->arc3.rad - speed;
    game->arc4.rad = game->arc4.rad - speed;
};
void random_Arc1(struct Game *game)
{
    game->arc1.x = SCREEN_WIDTH / 2;
    game->arc1.y = SCREEN_HEIGHT / 2;
    //start + end need to be <  |180|
    float start = 0;
    float end = (rand() % 80) + 100;  
    float rad = 500;
    game->arc1.start = start;
    game->arc1.end = end;
    game->arc1.rad = rad;
    game->arc1.r = 255;
    game->arc1.g = 255;
    game->arc1.b = 255;
    game->arc1.a = 255;
};
void random_Arc2(struct Game *game)
{
    game->arc2.x = SCREEN_WIDTH / 2;
    game->arc2.y = SCREEN_HEIGHT / 2;
    float start = (rand() % 10) + 1; 
    float end = (rand() % 10) - 150;  
    float rad = 700;
    game->arc2.start = start;
    game->arc2.end = end;
    game->arc2.rad = rad;
    game->arc2.r = 255;
    game->arc2.g = 255;
    game->arc2.b = 255;
    game->arc2.a = 255;
};
void random_Arc3(struct Game *game)
{
    game->arc3.x = SCREEN_WIDTH / 2;
    game->arc3.y = SCREEN_HEIGHT / 2;
    float start = ((rand() % 10) - 80);
    float end = 90;
    float rad = 900;
    game->arc3.start = start;
    game->arc3.end = end;
    game->arc3.rad = rad;
    game->arc3.r = 255;
    game->arc3.g = 255;
    game->arc3.b = 255;
    game->arc3.a = 255;

};
void random_Arc4(struct Game *game)
{
    game->arc4.x = SCREEN_WIDTH / 2;
    game->arc4.y = SCREEN_HEIGHT / 2;
    float start = (rand() % 170) + 10; 
    float end = 0;
    float rad = 1100;
    game->arc4.start = start;
    game->arc4.end = end;
    game->arc4.rad = rad;
    game->arc4.r = 255;
    game->arc4.g = 255;
    game->arc4.b = 255;
    game->arc4.a = 255;
};
void render_Game(struct Game *game)
{
    //refresh
    SDL_RenderClear(game->renderer);
    Spritesheet_render(game->background, BACKGROUND_X, BACKGROUND_Y, 255, 0);
    float cursorDist =  Cursor_Distance_From_Center(game);

    //Drawing my Arcs
    if (game->arc1.rad > cursorDist) //if his lifetime didnt reaches his limits,
    { 
        arcRGBA(game->renderer, game->arc1.x, game->arc1.y, game->arc1.rad , game->arc1.start, game->arc1.end, game->arc1.r, game->arc1.g, game->arc1.b, game->arc1.a);
        
    }
    else 
    {
        //make another arc
        Check_GameOver_Arc1(game);
        random_Arc1(game);
    }
    //arc2
    if (game->arc2.rad > cursorDist)
    {
       arcRGBA(game->renderer, game->arc2.x, game->arc2.y, game->arc2.rad, game->arc2.start, game->arc2.end, game->arc2.r, game->arc2.g, game->arc2.b, game->arc2.a);
    }
    else
    {
        //reset arc
       Check_GameOver_Arc2(game);
       random_Arc2(game);
    }
    //arc3
        if (game->arc3.rad > cursorDist)
    {
       arcRGBA(game->renderer, game->arc3.x, game->arc3.y, game->arc3.rad , game->arc3.start, game->arc3.end, game->arc3.r, game->arc3.g, game->arc3.b, game->arc3.a);
    }
    else
    {
        //reset arc
        Check_GameOver_Arc3(game);
        random_Arc3(game);
    }
    //arc4
        if (game->arc4.rad > cursorDist)
    {
        arcRGBA(game->renderer, game->arc4.x, game->arc4.y, game->arc4.rad, game->arc4.start, game->arc4.end, game->arc4.r, game->arc4.g, game->arc4.b, game->arc4.a);
    }
    else
    {
        //reset arc
        Check_GameOver_Arc4(game);
       random_Arc4(game);
    }

    ////////////////////////////////////////////
    filledCircleRGBA(game->renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 10, 255, 255, 255, 255);
    filledTrigonRGBA(game->renderer, game->cursor->leftCorner.x, game->cursor->leftCorner.y, game->cursor->rightCorner.x, game->cursor->rightCorner.y, game->cursor->topCorner.x, game->cursor->topCorner.y, 255, 255, 255, 255);
    ///////////////////////////////////////////
    //Timer
    AnimatedSpritesheet_render(game->Timer.HundredOfSeconds,SCREEN_WIDTH-105,10,false);
    AnimatedSpritesheet_render(game->Timer.TenSec,SCREEN_WIDTH-85,10,false);
    AnimatedSpritesheet_render(game->Timer.sec,SCREEN_WIDTH-70,10,false);
    AnimatedSpritesheet_render(game->Timer.ms,SCREEN_WIDTH-40,10,false);
    AnimatedSpritesheet_render(game->Timer.Dot,SCREEN_WIDTH-53,10,true);
    //Rendering
    SDL_RenderPresent(game->renderer);
};

float Cursor_Distance_From_Center(struct Game *game){
    struct Point Arc_Center, CursorPoint;
    float Dist;
    Arc_Center.x= MIDDLE_SCREEN_X;
    Arc_Center.y= MIDDLE_SCREEN_Y;
    CursorPoint.x = game->cursor->topCorner.x;
    CursorPoint.y = game->cursor->topCorner.y;

    return Dist = sqrt( powf((CursorPoint.x-Arc_Center.x),2) + powf((CursorPoint.y-Arc_Center.y),2));
};

void render_basic_elements(struct Game *game)
{
    Spritesheet_render(game->background, BACKGROUND_X, BACKGROUND_Y, 255, 0);
    filledCircleRGBA(game->renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 10, 255, 255, 255, 255);
    filledTrigonRGBA(game->renderer, game->cursor->leftCorner.x, game->cursor->leftCorner.y, game->cursor->rightCorner.x, game->cursor->rightCorner.y, game->cursor->topCorner.x, game->cursor->topCorner.y, 255, 255, 255, 255);
    SDL_RenderPresent(game->renderer);
};
void Move_Cursor_Left(struct Game *game)
{
    //refresh
    SDL_RenderClear(game->renderer);
    //render the background
    Spritesheet_render(game->background, BACKGROUND_X, BACKGROUND_Y, 255, 0);
    //Counter Clockwise rotation of the triangle around the middle of the screen.
    game->cursor->center = counterClockwise_rotate_point(MIDDLE_SCREEN_X, MIDDLE_SCREEN_Y, 0.5, game->cursor->center);
    game->cursor->leftCorner = counterClockwise_rotate_point(MIDDLE_SCREEN_X, MIDDLE_SCREEN_Y, 0.5, game->cursor->leftCorner);
    game->cursor->rightCorner = counterClockwise_rotate_point(MIDDLE_SCREEN_X, MIDDLE_SCREEN_Y, 0.5, game->cursor->rightCorner);
    game->cursor->topCorner = counterClockwise_rotate_point(MIDDLE_SCREEN_X, MIDDLE_SCREEN_Y, 0.5, game->cursor->topCorner);
    //rendering
    filledCircleRGBA(game->renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 10, 255, 255, 255, 255);
    filledTrigonRGBA(game->renderer, game->cursor->leftCorner.x, game->cursor->leftCorner.y, game->cursor->rightCorner.x, game->cursor->rightCorner.y, game->cursor->topCorner.x, game->cursor->topCorner.y, 255, 255, 255, 255);
    SDL_RenderPresent(game->renderer);
};
void Move_Cursor_Right(struct Game *game)
{
    SDL_RenderClear(game->renderer);
    ///////////////////////////////
    Spritesheet_render(game->background, BACKGROUND_X, BACKGROUND_Y, 255, 0);
    // Clockwise rotation of the triangle around the middle of the screen.
    game->cursor->center = Clockwiser_rotate_point(MIDDLE_SCREEN_X, MIDDLE_SCREEN_Y, 0.5, game->cursor->center);
    game->cursor->leftCorner = Clockwiser_rotate_point(MIDDLE_SCREEN_X, MIDDLE_SCREEN_Y, 0.5, game->cursor->leftCorner);
    game->cursor->rightCorner = Clockwiser_rotate_point(MIDDLE_SCREEN_X, MIDDLE_SCREEN_Y, 0.5, game->cursor->rightCorner);
    game->cursor->topCorner = Clockwiser_rotate_point(MIDDLE_SCREEN_X, MIDDLE_SCREEN_Y, 0.5, game->cursor->topCorner);
    //rendering
    filledCircleRGBA(game->renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 10, 255, 255, 255, 255);
    filledTrigonRGBA(game->renderer, game->cursor->leftCorner.x, game->cursor->leftCorner.y, game->cursor->rightCorner.x, game->cursor->rightCorner.y, game->cursor->topCorner.x, game->cursor->topCorner.y, 255, 255, 255, 255);
    SDL_RenderPresent(game->renderer);
};

struct Point counterClockwise_rotate_point(float cx, float cy, float angle, struct Point p)
{
    float s = sin(angle);
    float c = cos(angle);

    // translate point back to origin:
    p.x -= cx;
    p.y -= cy;

    // rotate point
    float xnew = p.x * c - p.y * s;
    float ynew = p.x * s + p.y * c;

    // translate point back:
    p.x = xnew + cx;
    p.y = ynew + cy;
    return p;
};
struct Point Clockwiser_rotate_point(float cx, float cy, float angle, struct Point p)
{
    float s = sin(angle);
    float c = cos(angle);

    // translate point back to origin:
    p.x -= cx;
    p.y -= cy;

    // rotate point
    float xnew = p.x * c + p.y * s;
    float ynew = -p.x * s + p.y * c;

    // translate point back:
    p.x = xnew + cx;
    p.y = ynew + cy;
    return p;
};

void Check_GameOver_Arc1(struct Game *game){
    struct Point Center, CursorPoint;
    Center.x= game->arc1.x;
    Center.y= game->arc1.y;
    CursorPoint.x = game->cursor->center.x;
    CursorPoint.y = game->cursor->center.y;

    float A = to_degrees(atan2 (CursorPoint.y - Center.y, CursorPoint.x  - Center.x));
    //Now if R < Radius the point is inside the circle.
    //To check if the angle is between StartingAngle (S) and EndingAngle (E) you need to consider two possibilities:
    //1) if S < E then if S < A < E the point lies inside the slice
    if (game->arc1.start<game->arc1.end)
    {
        if (game->arc1.start<A && A<game->arc1.end)
        {
            printf("gameover\n");
            game->state=GAME_OVER;
        }
        
    }
    //2) if S > E then there are 2 possible scenarios
    if (game->arc1.start>game->arc1.end)
    {
        //if A > S and A > E then the point lies inside the slice
        if (A>game->arc1.start && A >game->arc1.end)
        {
            printf("gameover\n");
            game->state=GAME_OVER;
        }
        //if A < S and A < E then the point lies inside the slice
        if (A<game->arc1.start && A <game->arc1.end)
        {
            printf("gameover\n");
            game->state=GAME_OVER;
        }        
        
    }   
};
void Check_GameOver_Arc2(struct Game *game){
    struct Point Center, CursorPoint;
    Center.x= game->arc2.x;
    Center.y= game->arc2.y;
    CursorPoint.x = game->cursor->center.x;
    CursorPoint.y = game->cursor->center.y;

    float A = to_degrees(atan2 (CursorPoint.y - Center.y, CursorPoint.x  - Center.x));
    //Now if R < Radius the point is inside the circle.
    //To check if the angle is between StartingAngle (S) and EndingAngle (E) you need to consider two possibilities:
    //1) if S < E then if S < A < E the point lies inside the slice
    if (game->arc2.start<game->arc2.end)
    {
        if (game->arc2.start<A && A<game->arc2.end)
        {
            printf("gameover\n");
            game->state=GAME_OVER;
        }
        
    }
    //2) if S > E then there are 2 possible scenarios
    if (game->arc2.start>game->arc2.end)
    {
        //if A > S and A > E then the point lies inside the slice
        if (A>game->arc2.start && A >game->arc2.end)
        {
            printf("gameover\n");
            game->state=GAME_OVER;
        }
        //if A < S and A < E then the point lies inside the slice
        if (A<game->arc2.start && A <game->arc2.end)
        {
            printf("gameover\n");
            game->state=GAME_OVER;
        }        
        
    }   
};
void Check_GameOver_Arc3(struct Game *game){
    struct Point Center, CursorPoint;
    Center.x= game->arc3.x;
    Center.y= game->arc3.y;
    CursorPoint.x = game->cursor->center.x;
    CursorPoint.y = game->cursor->center.y;

    float A = to_degrees(atan2 (CursorPoint.y - Center.y, CursorPoint.x  - Center.x));
    //Now if R < Radius the point is inside the circle.
    //To check if the angle is between StartingAngle (S) and EndingAngle (E) you need to consider two possibilities:
    //1) if S < E then if S < A < E the point lies inside the slice
    if (game->arc3.start<game->arc3.end)
    {
        if (game->arc3.start<A && A<game->arc3.end)
        {
            printf("gameover\n");
            game->state=GAME_OVER;
        }
        
    }
    //2) if S > E then there are 2 possible scenarios
    if (game->arc3.start>game->arc3.end)
    {
        //if A > S and A > E then the point lies inside the slice
        if (A>game->arc3.start && A >game->arc3.end)
        {
            printf("gameover\n");
            game->state=GAME_OVER;
        }
        //if A < S and A < E then the point lies inside the slice
        if (A<game->arc3.start && A <game->arc3.end)
        {
            printf("gameover\n");
            game->state=GAME_OVER;
        }        
        
    }   
};
void Check_GameOver_Arc4(struct Game *game){
    struct Point Center, CursorPoint;
    Center.x= game->arc4.x;
    Center.y= game->arc4.y;
    CursorPoint.x = game->cursor->center.x;
    CursorPoint.y = game->cursor->center.y;

    float A = to_degrees(atan2 (CursorPoint.y - Center.y, CursorPoint.x  - Center.x));
    //Now if R < Radius the point is inside the circle.
    //To check if the angle is between StartingAngle (S) and EndingAngle (E) you need to consider two possibilities:
    //1) if S < E then if S < A < E the point lies inside the slice
    if (game->arc4.start<game->arc4.end)
    {
        if (game->arc4.start<A && A<game->arc4.end)
        {
            printf("gameover\n");
            game->state=GAME_OVER;
        }
        
    }
    //2) if S > E then there are 2 possible scenarios
    if (game->arc4.start>game->arc4.end)
    {
        //if A > S and A > E then the point lies inside the slice
        if (A>game->arc4.start && A >game->arc4.end)
        {
            printf("gameover\n");
            game->state=GAME_OVER;
        }
        //if A < S and A < E then the point lies inside the slice
        if (A<game->arc4.start && A <game->arc4.end)
        {
            printf("gameover\n");
            game->state=GAME_OVER;
        }        
        
    }   
};

 float to_degrees(float radians) {
    return radians * (180.0 / M_PI);
};

// Tous les autres éléments du jeu sont des formes géométriques (triangle, disque,
// secteurs de disque, arc de cercles) qui peuvent être générées à l'aide de la
// bibliothèque SDL-gfx.

// before you continiue, checkup Maze bitbucket

//How does animation works?

//Solution 1 : Redraw the triangle to slightly rotate it when input from user
//Solution 2 : render the triangle once onto a target texture, and then rotate it using SDL_RenderCopyEx().

//Completed
// You should reorganize your files

//I need to create structures to represent my arcs so i can manipulate there coordinates more easily
//I want 4 Arcs /game

//completed


//How to detect when the game is over
// How to detect when the cursor touches an arc

//Completed

// Timing Animation using spritesheets

//completed

//Dont forget the sound