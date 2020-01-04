#ifndef ANIMATED_SPRITESHEET_H
#define ANIMATED_SPRITESHEET_H

#include "sdl2.h"
#include "spritesheet.h"
#include <stdbool.h>

struct AnimatedSpritesheet {
    struct Spritesheet *spritesheet; // The spritesheet to animate
    int currentRow;                  // The current row (current animation)
    int currentColumn;               // The current column (current frame)
    int delayBetweenFrame;           // The time between two frames
    int lastUpdate;                  // Elapsed time (in ms) since last update
    bool running;                    // True if and only if the sprite is running
};

/**
 * Creates an animated sprite sheet from an image file.
 *
 * @param filename           The name of the file containing the sprite sheet
 * @param numRows            The number of rows in the sprite sheet
 * @param numColumns         The number of columns in the sprite sheet
 * @param numSprites         The total number of sprites
 * @param delayBetweenFrame  The time between two frames
 * @param renderer           The renderer
 * @return                   The sprite sheet
 */
struct AnimatedSpritesheet *AnimatedSpritesheet_create(const char *filename,
                                                       int numRows,
                                                       int numColumns,
                                                       int numSprites,
                                                       int delayBetweenFrame,
                                                       SDL_Renderer* renderer);

/**
 * Deletes the animated sprite sheet.
 *
 * @param animatedSpritesheet  The animated sprite sheet to delete
 */
void AnimatedSpritesheet_delete(struct AnimatedSpritesheet *animatedSpritesheet);

/**
 * Sets the current row of the animate sprite sheet.
 *
 * Assumes that each row corresponds to one animation.
 *
 * @param animatedSpritesheet  The animated sprite sheet
 * @param rowNumber            The new row (animation)
 */
void AnimatedSpritesheet_setRow(struct AnimatedSpritesheet *animatedSpritesheet,
                                int rowNumber);

void AnimatedSpritesheet_setCol(struct AnimatedSpritesheet *animatedSpritesheet,
                                int colNumber);

/**
 * Starts animating the sprite sheet.
 *
 * @param animatedSpritesheet  The animated sprite sheet to start running
 */
void AnimatedSpritesheet_run(struct AnimatedSpritesheet *animatedSpritesheet);

/**
 * Stops the animation.
 *
 * @param animatedSpritesheet  The animated sprite sheet to stop
 */
void AnimatedSpritesheet_stop(struct AnimatedSpritesheet *animatedSpritesheet);

/**
 * Renders the animated sprite sheet at (x, y).
 *
 * @param animatedSpritesheet  The animated sprite sheet          
 * @param x                    The upper left corner x-coordinate
 * @param y                    The upper left corner y-coordinate
 */
void AnimatedSpritesheet_render(struct AnimatedSpritesheet *animatedSpritesheet,
                                int x,
                                int y,
                                bool isDot);

#endif
