#ifndef FOREGROUND_H
#define FOREGROUND_H

#include "robot.h"
#include "arena.h"

void erase_robot(struct Robot *robot, struct gridTile **grid);
void draw_robot(struct Robot *robot);

#endif // FOREGROUND_H