#include "foreground.h"
#include "graphics.h"

void erase_robot(struct Robot *robot, struct gridTile **grid) {
    foreground();
    int x_min = robot->x;
    int x_max = robot->x + 30;
    int y_min = robot->y;
    int y_max = robot->y + 30;

    if (grid[robot->rowIndex][robot->colIndex].type == HOME) {
        setRGBColour(204, 0, 204); // Redraw pink colour for HOME
        fillRect(x_min, y_min, x_max - x_min, y_max - y_min);
        setColour(black);
        drawRect(x_min, y_min, x_max - x_min, y_max - y_min); 
    } else {
        setColour(white); 
        fillRect(x_min, y_min, x_max - x_min, y_max - y_min); 
        setColour(black);
        drawRect(x_min, y_min, x_max - x_min, y_max - y_min); 
    }
}

void draw_robot(struct Robot *robot) {
    foreground();
    int x_coords[3];
    int y_coords[3];

    if (robot->orientation == 0) { // Robot is facing UP
        x_coords[0] = robot->x;
        x_coords[1] = robot->x + 15;
        x_coords[2] = robot->x + 30;
        y_coords[0] = robot->y + 30;
        y_coords[1] = robot->y;
        y_coords[2] = robot->y + 30;
    } else if (robot->orientation == 1) { // Robot is facing LEFT
        x_coords[0] = robot->x + 30;
        x_coords[1] = robot->x;
        x_coords[2] = robot->x + 30;
        y_coords[0] = robot->y;
        y_coords[1] = robot->y + 15;
        y_coords[2] = robot->y + 30;
    } else if (robot->orientation == 2) { // Robot is facing DOWN
        x_coords[0] = robot->x;
        x_coords[1] = robot->x + 15;
        x_coords[2] = robot->x + 30;
        y_coords[0] = robot->y;
        y_coords[1] = robot->y + 30;
        y_coords[2] = robot->y;
    } else if (robot->orientation == 3) { // Robot is facing RIGHT
        x_coords[0] = robot->x;
        x_coords[1] = robot->x + 30;
        x_coords[2] = robot->x;
        y_coords[0] = robot->y;
        y_coords[1] = robot->y + 15;
        y_coords[2] = robot->y + 30;
    }
    setColour(green);
    fillPolygon(3, x_coords, y_coords);
    sleep(5);
}