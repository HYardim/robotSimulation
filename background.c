#include "background.h"
#include "graphics.h"

#include <stdio.h>

void drawBackground(int rows, int cols, struct gridTile **grid) {
    int windowHeight = grid[rows - 1][cols - 1].y + grid[rows - 1][cols - 1].height + 100;
    int windowWidth = grid[rows - 1][cols - 1].x + grid[rows - 1][cols - 1].width + 100;
    setWindowSize(windowWidth, windowHeight);

    background();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j].type == WALL) {
                setRGBColour(178, 34, 34); // Red color for WALL
                fillRect(grid[i][j].x, grid[i][j].y, grid[i][j].width, grid[i][j].height);
            } 
            else if (grid[i][j].type == EMPTY) {
                setColour(white); // White color for EMPTY
                fillRect(grid[i][j].x, grid[i][j].y, grid[i][j].width, grid[i][j].height);
                setColour(black);
                drawRect(grid[i][j].x, grid[i][j].y, grid[i][j].width, grid[i][j].height);
            }
            else if (grid[i][j].type == MARKER) {
                setColour(blue); // Blue for MARKER
                fillRect(grid[i][j].x, grid[i][j].y, grid[i][j].width, grid[i][j].height);
                setColour(black);
                drawRect(grid[i][j].x, grid[i][j].y, grid[i][j].width, grid[i][j].height);
            }
            else if (grid[i][j].type == OBSTACLE) {
                setColour(black); // Black for OBSTACLE
                fillRect(grid[i][j].x, grid[i][j].y, grid[i][j].width, grid[i][j].height);
                setColour(black);
                drawRect(grid[i][j].x, grid[i][j].y, grid[i][j].width, grid[i][j].height);
            }
            else if (grid[i][j].type == HOME) {
                setRGBColour(204, 0, 204); //Pink for HOME
                fillRect(grid[i][j].x, grid[i][j].y, grid[i][j].width, grid[i][j].height);
                setColour(black);
                drawRect(grid[i][j].x, grid[i][j].y, grid[i][j].width, grid[i][j].height);
            }
        }
    }
}

    
