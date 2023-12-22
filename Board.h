#pragma once
#include "TextureManager.h"
#include <time.h>
#include <fstream>
#include <iostream>
using namespace std;

struct Tile
{
	Tile* neighbors[8];
	int is_bomb = 0;
	int flag = 0;
	int revealed = 0;
	int bomb_count = 0;
};

class Board
{
	vector<vector<Tile>> tiles;
	ifstream inFile; // used to load boards
	//configCount holds config file mine count, totalMines used for current board mind count
	int width, height, count, configCount, totalMines;
	int debug = 0;	//keep debug on if board is reset
	int lost = 0;
	int won = 0;
	unordered_map<string, sf::Sprite> sprites;
	unordered_map<int, sf::Sprite> digits;
public:
	Board(int width, int height, int count, unordered_map<string, sf::Sprite>& sprites);
	void loadBoard(string fileName); // load a premade test board
	void generateRandom(); // create a random board, .brd file
	void initializeNull(); // helper function for bombCount();
	void bombCount(); // scan surrounding of each tile, determine bomb_count
	void reset(); // reset the board state
	void build(sf::RenderWindow& window);
	void leftClick(int x, int y);
	void rightClick(int x, int y);
	void recursiveReveal(Tile& tile);
	void Clear();
	//temp helper
	void debugMode() { debug = 1; }
};