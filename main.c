typedef struct {
	unsigned char color: 4; // 0 = empty, 1 = powerup, 2 = red ... 7 = purple
	unsigned char size: 4; // 0 = untouched, 1 = touched, 2 = bronze ... 5 = platinum
} Tile;

typedef struct {
	int x;
	int y;
} Pos;

typedef Tile Row[5*2-1];
typedef Row* Board;

Tile* board_get(Board* board, Pos pos) {
	return &board[pos.y][pos.x];
}

// tile types:
// empty
// powerup × 4

// per color:
// untouched
// touched
// 2x2
// 3x3
// 4x4
// 5x5

// TYPE|red-purple|powerup
// un  |6         |1 (empty)
// 1x1 |6         |0
// 2x2 |6         |1
// 3x3 |6         |1
// 4x4 |6         |1
// 5x5 |6         |1
// 6x6 |6         |1

#define BOARD_WIDTH 5
#define BOARD_HEIGHT 9

Tile board[BOARD_HEIGHT*2-1][BOARD_WIDTH] = {0};
//     [0] [1] [2] [3] [4]
// [0] X   X   X   X   X  
// [1]   X   X   X   X   ?
// [2] X   X   X   X   X  
// [3]   X   X   X   X   ?
// [4] X   X   X   X   X  
// [5]   X   X   X   X   ?
// [6] X   X   X   X   X  

Tile board[BOARD_HEIGHT*2-1][BOARD_WIDTH*2-1] = {0};

//or:
//     0 1 2 3 4 5 6 7 8 
// [0] X . X . X . X . X 
// [1] . X . X . X . X . 
// [2] X . X . X . X . X 
// [3] . X . X . X . X . 
// [4] X . X . X . X . X 
// [5] . X . X . X . X . 
// [6] X . X . X . X . X 
