#include <stdio.h>

#define BOARD_WIDTH 11

struct Tile {
	unsigned char color: 4; // 0 = empty, 1 = side wall, 2 = pusher, 3 = powerup, 4 = red ... 9 = purple
	unsigned char size: 4; // 0 = untouched, 1 = touched, 2 = bronze ... 5 = platinum
	//unsigned char bl:1, br:1, tl:1, tr:1; // connections
	Tile* up() { return this+2*BOARD_WIDTH; }
	Tile* down() { return this-2*BOARD_WIDTH; }
	Tile* left() { return this-2; }
	Tile* right() { return this+2; }
};

Tile board[21][BOARD_WIDTH];

int main() {
	auto tile = &board[5][2];
	auto tile2 = &board[7][2];
	auto up = tile->up();
	tile2->color = 4;
	printf("tiles: %i\n", up->color);
}
