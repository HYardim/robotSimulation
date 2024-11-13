#include "arena.h"
#include "robot.h"
#include "foreground.h"
#include "background.h"
#include "graphics.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// Function declarations
void init_gridTile(struct gridTile ***grid, int rows, int cols);
void identify_cornerTile(struct gridTile **grid, int rows, int cols);
void init_randomWallBlock(struct gridTile **grid, int rows, int cols);
int init_randomMarkerTile(struct gridTile **grid, int rows, int cols);
void init_homeTile(struct gridTile **grid, int rows, int cols);
void init_obstacleTile(struct gridTile **grid, int rows, int cols);
void init_robot(struct Robot *robot, struct gridTile **grid, int rows, int cols);
void move_robot(struct gridTile **grid, int rows, int cols, int numMarkers);
void init_arena(int rows, int cols);
void generateWallBlockL(struct gridTile **grid, int rows, int cols);
void generateWallBlockPlus(struct gridTile **grid, int rows, int cols);


void init_gridTile(struct gridTile ***grid, int rows, int cols) {
    *grid = (struct gridTile **)malloc(rows * sizeof(struct gridTile *));
    for (int i = 0; i < rows; i++) {
        (*grid)[i] = (struct gridTile *)malloc(cols * sizeof(struct gridTile));
        for (int j = 0; j < cols; j++) {
            (*grid)[i][j].rowIndex = i;
            (*grid)[i][j].columnIndex = j;
            (*grid)[i][j].width = 30;
            (*grid)[i][j].height = 30;
            (*grid)[i][j].x = j * 30 + 50; // Adding 50 pixel margin
            (*grid)[i][j].y = i * 30 + 50; // Adding 50 pixel margin
            (*grid)[i][j].isCorner = 0; // Initialize isCorner to 0
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                (*grid)[i][j].type = WALL;
            } else {
                (*grid)[i][j].type = EMPTY;
            }
        }
    }
    identify_cornerTile(*grid, rows, cols); // Was built for stages which robot was dropping the marker to the corner
}

void identify_cornerTile(struct gridTile **grid, int rows, int cols) {
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            int wallCount = 0;
            if (grid[i - 1][j].type == WALL) wallCount++; 
            if (grid[i + 1][j].type == WALL) wallCount++; 
            if (grid[i][j - 1].type == WALL) wallCount++; 
            if (grid[i][j + 1].type == WALL) wallCount++; 

            if (wallCount >= 2) {
                grid[i][j].isCorner = 1;
            } else {
                grid[i][j].isCorner = 0;
            }
        }
    }
}

void init_randomWallBlock(struct gridTile **grid, int rows, int cols) {
    srand(time(NULL));
    int wallLength = rand() % 2 + 2; 
    int startRow, startCol;
    do {
        startRow = rand() % rows;
        startCol = rand() % cols;
    } while (grid[startRow][startCol].type != EMPTY);

    // Randomly choose a direction: 0 = horizontal, 1 = vertical
    int direction = rand() % 2;

    for (int i = 0; i < wallLength; i++) {
        if (startRow >= 0 && startRow < rows && startCol >= 0 && startCol < cols && grid[startRow][startCol].type == EMPTY) {
            grid[startRow][startCol].type = WALL;
            if (direction == 0) {
                startCol++; 
            } else {
                startRow++; 
            }
        } else {
            // If we hit a boundary or non-empty tile, try to change direction
            if (direction == 0) {
                direction = 1; 
                startRow++;
            } else {
                direction = 0; 
                startCol++;
            }
        }
    }
}

void generateWallBlockL(struct gridTile **grid, int rows, int cols) {
    srand(time(NULL));
    int numLShapes = rand() % 3 + 1; // Generate between 1 and 3 "L" shapes

    for (int n = 0; n < numLShapes; n++) {
        int startRow, startCol;
        bool validLShape = false;

        while (!validLShape) {
            startRow = rand() % rows;
            startCol = rand() % cols;

            // Randomly choose the orientation of the "L" shape
            int direction = rand() % 4;

            if (direction == 0) { // "L" shape facing down-right
                if (startRow < rows - 1 && startCol < cols - 1 &&
                    grid[startRow][startCol].type == EMPTY &&
                    grid[startRow + 1][startCol].type == EMPTY &&
                    grid[startRow + 1][startCol + 1].type == EMPTY) {
                    grid[startRow][startCol].type = WALL;
                    grid[startRow + 1][startCol].type = WALL;
                    grid[startRow + 1][startCol + 1].type = WALL;
                    validLShape = true;
                }
            } else if (direction == 1) { // "L" shape facing down-left
                if (startRow < rows - 1 && startCol > 0 &&
                    grid[startRow][startCol].type == EMPTY &&
                    grid[startRow + 1][startCol].type == EMPTY &&
                    grid[startRow + 1][startCol - 1].type == EMPTY) {
                    grid[startRow][startCol].type = WALL;
                    grid[startRow + 1][startCol].type = WALL;
                    grid[startRow + 1][startCol - 1].type = WALL;
                    validLShape = true;
                }
            } else if (direction == 2) { // "L" shape facing up-right
                if (startRow > 0 && startCol < cols - 1 &&
                    grid[startRow][startCol].type == EMPTY &&
                    grid[startRow - 1][startCol].type == EMPTY &&
                    grid[startRow - 1][startCol + 1].type == EMPTY) {
                    grid[startRow][startCol].type = WALL;
                    grid[startRow - 1][startCol].type = WALL;
                    grid[startRow - 1][startCol + 1].type = WALL;
                    validLShape = true;
                }
            } else if (direction == 3) { // "L" shape facing up-left
                if (startRow > 0 && startCol > 0 &&
                    grid[startRow][startCol].type == EMPTY &&
                    grid[startRow - 1][startCol].type == EMPTY &&
                    grid[startRow - 1][startCol - 1].type == EMPTY) {
                    grid[startRow][startCol].type = WALL;
                    grid[startRow - 1][startCol].type = WALL;
                    grid[startRow - 1][startCol - 1].type = WALL;
                    validLShape = true;
                }
            }
        }
    }
}



void generateWallBlockPlus(struct gridTile **grid, int rows, int cols) {
    srand(time(NULL));
    int numPlusShapes = rand() % 3 + 1; // Generate between 1 and 3 "+" shapes

    for (int n = 0; n < numPlusShapes; n++) {
        int startRow, startCol;
        bool validPlusShape = false;

        while (!validPlusShape) {
            startRow = rand() % rows;
            startCol = rand() % cols;

            if (startRow > 0 && startRow < rows - 1 && startCol > 0 && startCol < cols - 1 &&
                grid[startRow][startCol].type == EMPTY &&
                grid[startRow - 1][startCol].type == EMPTY &&
                grid[startRow + 1][startCol].type == EMPTY &&
                grid[startRow][startCol - 1].type == EMPTY &&
                grid[startRow][startCol + 1].type == EMPTY) {
                grid[startRow][startCol].type = WALL;
                grid[startRow - 1][startCol].type = WALL;
                grid[startRow + 1][startCol].type = WALL;
                grid[startRow][startCol - 1].type = WALL;
                grid[startRow][startCol + 1].type = WALL;
                validPlusShape = true;
            }
        }
    }
}




void init_homeTile(struct gridTile **grid, int rows, int cols) {
    srand(time(NULL));
    int homeRowIndex, homeColIndex;
    bool validHomeTile = false;

    while (!validHomeTile) {
        homeRowIndex = rand() % rows;
        homeColIndex = rand() % cols;

        if (grid[homeRowIndex][homeColIndex].type == EMPTY) {
            bool surroundedByWallsOrObstacles = false;

            // Check adjacent tiles
            if ((homeRowIndex > 0 && grid[homeRowIndex - 1][homeColIndex].type == WALL) || // Up
                (homeRowIndex < rows - 1 && grid[homeRowIndex + 1][homeColIndex].type == WALL) || // Down
                (homeColIndex > 0 && grid[homeRowIndex][homeColIndex - 1].type == WALL) || // Left
                (homeColIndex < cols - 1 && grid[homeRowIndex][homeColIndex + 1].type == WALL) || // Right
                (homeRowIndex > 0 && grid[homeRowIndex - 1][homeColIndex].type == OBSTACLE) || // Up
                (homeRowIndex < rows - 1 && grid[homeRowIndex + 1][homeColIndex].type == OBSTACLE) || // Down
                (homeColIndex > 0 && grid[homeRowIndex][homeColIndex - 1].type == OBSTACLE) || // Left
                (homeColIndex < cols - 1 && grid[homeRowIndex][homeColIndex + 1].type == OBSTACLE)) { // Right
                surroundedByWallsOrObstacles = true;
            }
            if (!surroundedByWallsOrObstacles) {
                validHomeTile = true;
            }
        }
    }

    grid[homeRowIndex][homeColIndex].type = HOME;
}

int init_randomMarkerTile(struct gridTile **grid, int rows, int cols) {
    srand(time(NULL));
    int numMarkers = rand() % 5 + 4; // Generate between 1 and 5 markers

    for (int i = 0; i < numMarkers; i++) {
        struct markerTile marker;
        bool validMarkerTile = false;

        while (!validMarkerTile) {
            marker.base.rowIndex = rand() % rows;
            marker.base.columnIndex = rand() % cols;

            if (grid[marker.base.rowIndex][marker.base.columnIndex].type == EMPTY) {
                bool surroundedByWallsOrObstacles = false;

                // Check adjacent tiles to see if marker is accessible by the robot
                if ((marker.base.rowIndex > 0 && grid[marker.base.rowIndex - 1][marker.base.columnIndex].type == WALL) || // Up
                    (marker.base.rowIndex < rows - 1 && grid[marker.base.rowIndex + 1][marker.base.columnIndex].type == WALL) || // Down
                    (marker.base.columnIndex > 0 && grid[marker.base.rowIndex][marker.base.columnIndex - 1].type == WALL) || // Left
                    (marker.base.columnIndex < cols - 1 && grid[marker.base.rowIndex][marker.base.columnIndex + 1].type == WALL) || // Right
                    (marker.base.rowIndex > 0 && grid[marker.base.rowIndex - 1][marker.base.columnIndex].type == OBSTACLE) || // Up
                    (marker.base.rowIndex < rows - 1 && grid[marker.base.rowIndex + 1][marker.base.columnIndex].type == OBSTACLE) || // Down
                    (marker.base.columnIndex > 0 && grid[marker.base.rowIndex][marker.base.columnIndex - 1].type == OBSTACLE) || // Left
                    (marker.base.columnIndex < cols - 1 && grid[marker.base.rowIndex][marker.base.columnIndex + 1].type == OBSTACLE)) { // Right
                    surroundedByWallsOrObstacles = true;
                }

                if (!surroundedByWallsOrObstacles) {
                    validMarkerTile = true;
                }
            }
        }

        grid[marker.base.rowIndex][marker.base.columnIndex].type = MARKER;
    }
    return numMarkers;
}

void init_obstacleTile(struct gridTile **grid, int rows, int cols) {
    srand(time(NULL));
    int numObstacles = rand() % 5 + 8; // Generate between 1 and 5 obstacles

    for (int i = 0; i < numObstacles; i++) {
        struct gridTile obstacle;
        do {
            obstacle.rowIndex = rand() % rows;
            obstacle.columnIndex = rand() % cols;
        } while (grid[obstacle.rowIndex][obstacle.columnIndex].type != EMPTY);
        grid[obstacle.rowIndex][obstacle.columnIndex].type = OBSTACLE;
    }
}



void init_robot(struct Robot *robot, struct gridTile **grid, int rows, int cols) {
    srand(time(NULL)); 
    int rowIndex, colIndex;
    bool validPosition = false;
    while (!validPosition) {
        rowIndex = rand() % rows;
        colIndex = rand() % cols;

        if (grid[rowIndex][colIndex].type == EMPTY) {
            bool adjacentToWall = false;
            if ((rowIndex > 0 && grid[rowIndex - 1][colIndex].type == WALL) || // Up
                (rowIndex < rows - 1 && grid[rowIndex + 1][colIndex].type == WALL) || // Down
                (colIndex > 0 && grid[rowIndex][colIndex - 1].type == WALL) || // Left
                (colIndex < cols - 1 && grid[rowIndex][colIndex + 1].type == WALL)) { // Right
                adjacentToWall = true;
            }

            if (!adjacentToWall) {
                validPosition = true;
            }
        }
    }
    robot->rowIndex = rowIndex;
    robot->colIndex = colIndex;
    robot->orientation = rand() % 4;
    robot->x = grid[rowIndex][colIndex].x;
    robot->y = grid[rowIndex][colIndex].y;
    robot->markerCount = 0;
    robot->searchMarker = 1;
}

void move_robot(struct gridTile **grid, int rows, int cols, int numMarkers) {
    struct Robot robot;
    init_robot(&robot, grid, rows, cols);
    draw_robot(&robot);

    // Traverse all grid tiles until all markers are found
    int markersFound = 0;
    while (markersFound < numMarkers) {
        if (traverse_grid(&robot, grid, rows, cols)) {
            markersFound++;
        } else {
            break; // No more markers found
        }
    }

    bool visited[rows][cols];
    memset(visited, false, sizeof(visited));
    if (dfs_find_home_recursive(&robot, grid, rows, cols, visited)) {
        // Drop all markers at the home tile
        while (robot.markerCount > 0) {
            dropMarker(&robot, grid);
        }
    }
}

void init_arena(int rows, int cols) {
    struct gridTile **grid;
    init_gridTile(&grid, rows, cols);
    srand(time(NULL));
    generateWallBlockL(grid, rows, cols);
    generateWallBlockPlus(grid, rows, cols);

    int numWallBlocks = rand() % 5 + 10;
    for(int i = 0; i < numWallBlocks; i++) {
        init_randomWallBlock(grid, rows, cols);
    }

    init_obstacleTile(grid, rows, cols);
    int numMarkers = init_randomMarkerTile(grid, rows, cols);
    init_homeTile(grid, rows, cols);
    drawBackground(rows, cols, grid);

    move_robot(grid, rows, cols, numMarkers);
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);
}