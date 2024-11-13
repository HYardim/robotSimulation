#include "stack.h"
#include "robot.h"
#include "foreground.h"
#include "graphics.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h> 

void initStack(Stack *s) {
    s->top = NULL;
}

bool isStackEmpty(Stack *s) {
    return s->top == NULL;
}

void push(Stack *s, State value) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

State pop(Stack *s) {
    if (isStackEmpty(s)) {
        State emptyState = {-1, -1, -1};
        return emptyState;
    }
    StackNode *temp = s->top;
    State value = temp->data;
    s->top = s->top->next;
    free(temp);
    return value;
}

bool dfs_recursive(struct Robot *robot, struct gridTile **grid, int rows, int cols, bool visited[rows][cols]) {
    robot->x = grid[robot->rowIndex][robot->colIndex].x;
    robot->y = grid[robot->rowIndex][robot->colIndex].y;
    draw_robot(robot);

    if (atMarker(robot, grid)) {
        pickUpMarker(robot, grid);
        robot->markerCount++;
        return true; 
    }

    visited[robot->rowIndex][robot->colIndex] = true;

    for (int i = 0; i < 4; i++) {
        if (canMoveForward(robot, grid, rows, cols)) {
            // Check if the forward tile has been visited before
            int nextRow = robot->rowIndex;
            int nextCol = robot->colIndex;
            if (robot->orientation == 0) nextRow--; 
            else if (robot->orientation == 1) nextCol--; 
            else if (robot->orientation == 2) nextRow++; 
            else if (robot->orientation == 3) nextCol++; 

            if (!visited[nextRow][nextCol]) {
                forward(robot, grid, rows, cols);
                robot->x = grid[robot->rowIndex][robot->colIndex].x;
                robot->y = grid[robot->rowIndex][robot->colIndex].y;
                draw_robot(robot);

                if (dfs_recursive(robot, grid, rows, cols, visited)) {
                    return true; 
                }

                // Backtrack
                robot->rowIndex = nextRow;
                robot->colIndex = nextCol;
                robot->orientation = (robot->orientation + 2) % 4; // Reverse direction
                forward(robot, grid, rows, cols); // Move back to the previous state
                robot->orientation = (robot->orientation + 2) % 4; // Restore original orientation
                robot->x = grid[robot->rowIndex][robot->colIndex].x;
                robot->y = grid[robot->rowIndex][robot->colIndex].y;
                draw_robot(robot);
            }
        }
        right(robot, grid);
    }

    return false; 
}

bool traverse_grid(struct Robot *robot, struct gridTile **grid, int rows, int cols) {
    bool visited[rows][cols];
    memset(visited, false, sizeof(visited));
    return dfs_recursive(robot, grid, rows, cols, visited);
}

bool dfs_find_home_recursive(struct Robot *robot, struct gridTile **grid, int rows, int cols, bool visited[rows][cols]) {
    robot->x = grid[robot->rowIndex][robot->colIndex].x;
    robot->y = grid[robot->rowIndex][robot->colIndex].y;
    draw_robot(robot);

    if (isAtHome(robot, grid)) {
        return true; 
    }

    visited[robot->rowIndex][robot->colIndex] = true;

    for (int i = 0; i < 4; i++) {
        if (canMoveForward(robot, grid, rows, cols)) {
            // Check if the forward tile has been visited before
            int nextRow = robot->rowIndex;
            int nextCol = robot->colIndex;
            if (robot->orientation == 0) nextRow--; // UP
            else if (robot->orientation == 1) nextCol--; // LEFT
            else if (robot->orientation == 2) nextRow++; // DOWN
            else if (robot->orientation == 3) nextCol++; // RIGHT

            if (!visited[nextRow][nextCol]) {
                forward(robot, grid, rows, cols);
                robot->x = grid[robot->rowIndex][robot->colIndex].x;
                robot->y = grid[robot->rowIndex][robot->colIndex].y;
                draw_robot(robot);

                if (dfs_find_home_recursive(robot, grid, rows, cols, visited)) {
                    return true; 
                }

                // Backtrack
                robot->rowIndex = nextRow;
                robot->colIndex = nextCol;
                robot->orientation = (robot->orientation + 2) % 4; // Reverse direction
                forward(robot, grid, rows, cols); // Move back to the previous state
                robot->orientation = (robot->orientation + 2) % 4; // Restore original orientation
                robot->x = grid[robot->rowIndex][robot->colIndex].x;
                robot->y = grid[robot->rowIndex][robot->colIndex].y;
                draw_robot(robot);
            }
        }
        right(robot, grid);
    }

    return false; 
}




