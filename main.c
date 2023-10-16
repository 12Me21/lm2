#include <stdio.h>
#include <time.h>

#define BOARD_WIDTH 11
#define BOARD_HEIGHT 21

typedef struct {
	unsigned char color: 4; // 0 = empty, 1 = side wall, 2 = pusher, 3 = powerup, 4 = red ... 9 = purple
	unsigned char size: 4; // 0 = untouched, 1 = touched, 2 = bronze ... 5 = platinum
} Tile;

typedef struct {
	int x;
	int y;
} Pos;

typedef Tile Row[BOARD_WIDTH];

Tile* board_get(Row* board, Pos pos) {
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

//Tile board[BOARD_HEIGHT*2-1][BOARD_WIDTH] = {0};
//     [0] [1] [2] [3] [4]
// [0] X   X   X   X   X  
// [1]   X   X   X   X   ?
// [2] X   X   X   X   X  
// [3]   X   X   X   X   ?
// [4] X   X   X   X   X  
// [5]   X   X   X   X   ?
// [6] X   X   X   X   X  

Row board[BOARD_HEIGHT] = {0};

void print_tile(Tile* tile) {
	if (tile->color==0) {
		printf(" <{}> ");
	}
	else if (tile->color==1) {
		printf("  ||  ");
	}
	else if (tile->color==2) {
		printf(" \\VV/ ");
	}
	else if (tile->color==3) {
		printf(" <[]> ");
	}
	else {
		printf("\x1B[%dm <{}> \x1B[m", (int[]){101,43,103,102,104,45}[tile->color-4]);
	}
}

void print_board(Row* board) {
	for (int y=BOARD_HEIGHT-1; y>=0; y-=2) {
		printf("   ");
		for (int x=1; x<BOARD_WIDTH; x+=2) {
			print_tile(board_get(board, (Pos){x,y}));
			printf("");
		}
		printf("\n");
		if (y!=0) {
			for (int x=0; x<BOARD_WIDTH; x+=2) {
				print_tile(board_get(board, (Pos){x,y-1}));
				printf("");
			}
			printf("\n");
		}
	}
	nanosleep(&(struct timespec){0,2*99999999}, NULL);
}

void process_hit(Row* board, Pos pos) {
	Tile* tile = &board[pos.y][pos.x];
	Tile* front = &board[pos.y+2][pos.x];
	Tile* left = &board[pos.y+1][pos.x-1];
	Tile* right = &board[pos.y+1][pos.x+1];
	if (front->color<3) { // nothing
		// ok
		printf("HIT (nothing)\n");
		goto side;
	} else if (front->color==3) { // powerup
		// kill both
		printf("HIT (powerup)\n");
		*tile = (Tile){0};
		*front = (Tile){0};
	} else { // building
		if (tile->color == front->color && front->color != left->color && front->color != right->color) { // hit corner
			// todo: break all connected
			printf("HIT (corner)\n");
		} else { // otherwise
		side:;
			if (left->color>3) {
				printf("HIT (left)\n");
				*left = (Tile){tile->color, 0};
			}
			if (right->color>3) {
				printf("HIT (right)\n");
				*right = (Tile){tile->color, 0};
			}
			// now do the flood fill algorithm:
			// (todo)
		}
	}
}

// make this just do one step instead.
void shoot(Row* board, Tile tile, int x) {
	int y = x%2 ? 0 : 1;
	
	while (1) {
		Tile hit = board[y+2][x];
		Tile left = board[y+1][x-1];
		Tile right = board[y+1][x+1];
		int dir = 0;
		if (!left.color && !right.color && !hit.color) {
			printf("slide\n");
			y+=2;
			board[y][x] = tile;
			print_board(board);
			board[y][x] = (Tile){0};
		} else if (!left.color == !right.color) {
			printf("hit straight\n");
			goto hit;
		} else {
			printf("slide diagonal\n");
			dir = left.color ? 1 : -1;
			while (1) {
				y+=1;
				x+=dir;
				
				board[y][x] = tile;
				print_board(board);
				board[y][x] = (Tile){0};
				
				Tile hit = board[y+1][x+dir];
				if (hit.color==1) // wall bounce
					dir = -dir;
				if (hit.color)
					goto hit;
			}
		}
	}
 hit:;
	board[y][x] = tile;
	process_hit(board, (Pos){x,y});
}

void main() {
	for (int y=1; y<BOARD_HEIGHT; y+=2) {
		board[y][0] = (Tile){1};
		board[y][BOARD_WIDTH-1] = (Tile){1};
	}
	for (int x=0; x<BOARD_WIDTH; x+=1) {
		board[BOARD_HEIGHT-1-1+(x%2)][x] = (Tile){2};
	}
	
	//board_get(board, (Pos){2,4})[0] = (Tile){2, 0};
	shoot(board, (Tile){4,0}, 2);
	shoot(board, (Tile){5,0}, 3);
	shoot(board, (Tile){6,0}, 3);
	print_board(board);
}

//or:
//     0 1 2 3 4 5 6 7 8 9 A
// [8] - # - # - # - # - # -
// [7] # - # - # - # - # - #
// [6] - X . X . X . X . X -
// [5] # . X . X . X . X . #
// [4] - X . X . X . X . X -
// [3] # . X . X . X . X . #
// [2] - X . X . X . X . X -
// [1] # . s . s . s . s . #
// [0] - s . s . s . s . s -  (s = shooting position)

