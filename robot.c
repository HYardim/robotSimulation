#include "robot.h"
#include "foreground.h"
#include "graphics.h"
#include <time.h>
#include <stdlib.h>

int canMoveForward(struct Robot *robot, struct gridTile **grid, int rows, int cols) {
    int nextRow = robot->rowIndex;
    int nextCol = robot->colIndex;
    // Determine the next position based on the robot's orientation
    if (robot->orientation == 0) { 
        nextRow--;
    } else if (robot->orientation == 1) { 
        nextCol--;
    } else if (robot->orientation == 2) { 
        nextRow++;
    } else if (robot->orientation == 3) { 
        nextCol++;
    }
    if (nextRow >= 0 && nextRow < rows && nextCol >= 0 && nextCol < cols) {
        if (grid[nextRow][nextCol].type != WALL && grid[nextRow][nextCol].type != OBSTACLE) {
            return 1; 
        }
    }
    return 0; 
}

void forward(struct Robot *robot, struct gridTile **grid, int rows, int cols) {    
    erase_robot(robot, grid);
    if (robot->orientation == 0) { // UP
        robot->rowIndex--;
        robot->y -= 30;
    } else if (robot->orientation == 1) { // LEFT
        robot->colIndex--;
        robot->x -= 30;
    } else if (robot->orientation == 2) { // DOWN
        robot->rowIndex++;
        robot->y += 30;            
    } else if (robot->orientation == 3) { // RIGHT
        robot->colIndex++;
        robot->x += 30;
    }
   
    draw_robot(robot); // Redraw the robot at the new position  
} 

void left(struct Robot *robot, struct gridTile **grid) {
    erase_robot(robot, grid); 
    robot->orientation = (robot->orientation + 1) % 4; 
    sleep(20);
}

void right(struct Robot *robot, struct gridTile **grid) {
    erase_robot(robot, grid); 
    robot->orientation = (robot->orientation + 3) % 4;
    draw_robot(robot); 
    sleep(20);
}

int atMarker(struct Robot *robot, struct gridTile **grid) {
    return grid[robot->rowIndex][robot->colIndex].type == MARKER;
}

void pickUpMarker(struct Robot *robot, struct gridTile **grid) {
    robot->markerCount++;
    grid[robot->rowIndex][robot->colIndex].type = EMPTY;
}

void dropMarker(struct Robot *robot, struct gridTile **grid) {
    if (robot->markerCount > 0) {
        robot->markerCount--;
        grid[robot->rowIndex][robot->colIndex].type = MARKER;
        
    }
}

int isAtHome(struct Robot *robot, struct gridTile **grid) {
    if (grid[robot->rowIndex][robot->colIndex].type == HOME) return 1;
    else return 0;
}

int markerCount(struct Robot *robot) {
    return robot->markerCount;
}