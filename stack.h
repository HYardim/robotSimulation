#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "arena.h"
#include "robot.h"
#include "foreground.h"

typedef struct {
    int rowIndex;
    int colIndex;
    int orientation;
} State;

typedef struct StackNode {
    State data;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
} Stack;

void initStack(Stack *s);
bool isStackEmpty(Stack *s);
void push(Stack *s, State value);
State pop(Stack *s);
bool traverse_grid(struct Robot *robot, struct gridTile **grid, int rows, int cols);
bool dfs_find_home_recursive(struct Robot *robot, struct gridTile **grid, int rows, int cols, bool visited[rows][cols]);
#endif // STACK_H