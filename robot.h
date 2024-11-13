#ifndef ROBOT_H
#define ROBOT_H

#include "arena.h"

struct Robot {
    int x;
    int y;
    int rowIndex;
    int colIndex;
    int markerCount;
    int orientation; // 0: UP, 1: LEFT, 2: DOWN, 3: RIGHT
    int searchMarker;
};

int canMoveForward(struct Robot *robot, struct gridTile **grid,int rows, int cols);
void forward(struct Robot *robot, struct gridTile **grid, int rows, int cols);
void right(struct Robot *robot, struct gridTile **grid);
void left(struct Robot *robot, struct gridTile **grid);
void pickUpMarker(struct Robot *robot, struct gridTile **grid);
void dropMarker(struct Robot *robot, struct gridTile **grid);
int markerCount(struct Robot *robot);
int atMarker(struct Robot *robot, struct gridTile **grid);
int isAtHome(struct Robot *robot, struct gridTile **grid);


#endif // ROBOT_H