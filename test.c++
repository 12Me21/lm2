#include <stdio.h>

#define BOARD_WIDTH 11

struct Tile {
	unsigned char color: 4;
	unsigned char size: 4;
	inline Tile* rel(int x, int y) { return this+y*BOARD_WIDTH+x; } // x+y should be an even number
	inline Tile* d() { return this-2*BOARD_WIDTH; }
	inline Tile* u() { return this+2*BOARD_WIDTH; }
	inline Tile* l() { return this-2; }
	inline Tile* r() { return this+2; }
	inline Tile* dl() { return this-BOARD_WIDTH-1; }
	inline Tile* dr() { return this-BOARD_WIDTH+1; }
	inline Tile* ul() { return this+BOARD_WIDTH-1; }
	inline Tile* ur() { return this+BOARD_WIDTH+1; }

};

Tile board[21][BOARD_WIDTH];

int main() {
	Tile* tile = &board[5][3];
	Tile* up = tile->u(); // same as &board[5+2][3];
}
