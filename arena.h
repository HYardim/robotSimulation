#ifndef ARENA_H
#define ARENA_H


#define EMPTY 0
#define WALL 1
#define OBSTACLE 2
#define MARKER 3
#define HOME 4

struct gridTile {
    int columnIndex;
    int rowIndex;
    int width;
    int height;
    int x;
    int y;
    int type; // 0: EMPTY, 1: WALL, 2: OBSTACLE, 3: MARKER
    int isCorner;
};

struct emptyTile {
    struct gridTile base;
};

struct wallTile {
    struct gridTile base;
};

struct obstacleTile {
    struct gridTile base;
};

struct markerTile {
    struct gridTile base;
};

struct homeTile {
    struct gridTile base;
};

void init_gridTile(struct gridTile ***grid, int rows, int cols);
int init_randomMarkerTile(struct gridTile **grid, int rows, int cols);
void init_homeTile(struct gridTile **grid, int rows, int cols);
void init_arena(int rows, int cols);
void drawBackground(int cols, int rows, struct gridTile **grid);
void identify_cornerTile(struct gridTile **grid, int rows, int cols);
void init_obstacleTile(struct gridTile **grid, int rows, int cols);
void generateWallBlockL(struct gridTile **grid, int rows, int cols);
void init_randomWallBlock(struct gridTile **grid, int rows, int cols);
void generateWallBlockPlus(struct gridTile **grid, int rows, int cols);
#endif // ARENA_H