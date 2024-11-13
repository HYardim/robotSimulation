#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"
#include "robot.h"
#include "foreground.h"
#include "arena.h"
#include "background.h"
#include <time.h>

// Written by: Hakan YARDIM
// Date: 2024-11-11
// This program is a simulation of a robot that moves in an arena to collect markers and return home.

int main(void) {
    srand(time(NULL)); 
    int rows = rand() % 10 + 10;
    int cols = rand() % 12 + 15;
    init_arena(rows, cols);
    return 0;
}