#include <stdio.h>

#define BOARD_WIDTH 11

struct Tile {
	unsigned char color: 4;
	unsigned char size: 4;
	inline Tile* rel(int x, int y) { return this+y*BOARD_WIDTH+x; } // note: sum of x and y must be an even number
	inline Tile* d() { return rel( 0,-2); }
	inline Tile* u() { return rel( 0, 2); }
	inline Tile* l() { return rel(-2, 0); }
	inline Tile* r() { return rel( 2, 0); }
	inline Tile* dl() { return rel(-1,-1); }
	inline Tile* dr() { return rel( 1,-1); }
	inline Tile* ul() { return rel(-1, 1); }
	inline Tile* ur() { return rel( 1, 1); }
};

Tile board[21][BOARD_WIDTH];

int main() {
	Tile* tile = &board[5][3];
	Tile* up = tile->u(); // same as &board[5+2][3];
	Tile* idk = tile->u()->l()->dl()->dr()->r(); // same as tile
	//    2 . 1
	//  3 . . .
	//    4 . t
	Tile* heck = nullptr;
	heck = heck->r();
	printf("%p", heck); // prints "0x2"
}
