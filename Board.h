#include "Tile.h"
#include "string"
#include <vector>
#include <iostream>
#include <fstream>
class Board {

public:
	void loadConf(const string& file);
	void changeBoard(string& test);
	void setNeighbors();
	void MakeBoard();
	vector<char> cb;
	int flagCount = 0;
	vector<Tile> b;
	vector<vector<Tile>> board;
	bool showbombs = false;
	bool win = false;
	bool lose = false;
	int width=0;
	bool showBombs=false;
	int height=0;
	int rows=0;
	int columns=0;
	int bombCount=0;
	int tileCount=0;
	int revealedTiles = 0;
	vector<Sprite> counter;
	void Counter();
	void addDigit(int d);
	Sprite allDigits[11];
};