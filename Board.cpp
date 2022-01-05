#include "Board.h"
#include "TextureManager.h"
#include "Random.h"
#include <iostream>
#include <fstream>
#include <vector>

void Board::loadConf(const string& file) {

	ifstream infile;
	string widWord;
	string heiWord;
	string bcWord;

	infile.open(file);
	if (!infile.is_open()) {
		cout << "Did not open";
	}
	while (!infile.eof()) {
		getline(infile, widWord);
		columns = stoi(widWord);
		getline(infile, heiWord);
		rows = stoi(heiWord);
		getline(infile, bcWord);
		bombCount = stoi(bcWord);
	}

	width = columns * 32;
	height = (rows * 32) + 88;
	tileCount = rows * columns;
}



void Board::MakeBoard() {

	//        PUT ALL THE TILES ON THE BOARD AND GIVE EACH TILE A BOMB BOOLEAN OF TRUE IF IT IS A BOMB
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			Tile tile(0);
			Vector2f posi = Vector2f((float)(j * 32), (float)(i * 32));


			b.push_back(tile);
		}

		board.push_back(b);

	}
	for (int i = 0; i < bombCount; i++) {
		int x = Random::Int(0, rows - 1);
		int y = Random::Int(0, columns - 1);
		board[x][y].bomb = true;

	}
}

		

void Board::setNeighbors() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == 0) {//up
				board[i][j].neighbors.push_back(nullptr);
			}
			else {
				board[i][j].neighbors.push_back(&board[i - 1][j]);
			}
			if (j == columns - 1) {//right
				board[i][j].neighbors.push_back(nullptr);
			} else {
				board[i][j].neighbors.push_back(&board[i][j + 1]);

			}
			if (i == rows - 1) {//down
				board[i][j].neighbors.push_back(nullptr);
			}
			else {
				board[i][j].neighbors.push_back(&board[i + 1][j]);
			}
			if (j == 0) {//left
				board[i][j].neighbors.push_back(nullptr);
			}
			else {
				board[i][j].neighbors.push_back(&board[i][j - 1]);
			} 
			if (i == 0 || j==columns-1) { //upperright
				board[i][j].neighbors.push_back(nullptr);
			}
			else {
				board[i][j].neighbors.push_back(&board[i - 1][j + 1]);
			}
			if (i == rows - 1  || j==columns-1) { //bottomright
				board[i][j].neighbors.push_back(nullptr);
			}
			else {
				board[i][j].neighbors.push_back(&board[i + 1][j + 1]);
			}
			if (j == 0 || i==rows-1) { //bottomleft
				board[i][j].neighbors.push_back(nullptr);
			}
			else {
				board[i][j].neighbors.push_back(&board[i + 1][j - 1]);
			}
			if (i == 0 || j==0) {  //topleft
				board[i][j].neighbors.push_back(nullptr);
			}
			else {
				board[i][j].neighbors.push_back(&board[i - 1][j - 1]);
			}
		}
	}
}

		/*void Board::setNeighbors() {
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					if (i == 0) {//All top
						if (j != 0 && j != columns - 1) { //top
							board[i][j].neighbors.push_back(nullptr); //order of neighbor vector is up, right, down, left, upperright, bottomright, bottomleft, upperleft
							board[i][j].neighbors.push_back(&board[i][j + 1]);//right
							board[i][j].neighbors.push_back(&board[i + 1][j]);//down
							board[i][j].neighbors.push_back(&board[i][j - 1]);//left
							board[i][j].neighbors.push_back(nullptr);//upright
							board[i][j].neighbors.push_back(&board[i + 1][j + 1]);//bottomright
							board[i][j].neighbors.push_back(&board[i + 1][j - 1]);//bottomleft
							board[i][j].neighbors.push_back(nullptr);//topleft

						}
						else if (j == 0) { //top left
							board[i][j].neighbors.push_back(nullptr); //order of neighbor vector is up, right, down, left, upperright, bottomright, bottomleft, upperleft
							board[i][j].neighbors.push_back(&board[i][j + 1]);//right
							board[i][j].neighbors.push_back(&board[i + 1][j]);//down
							board[i][j].neighbors.push_back(nullptr);//left
							board[i][j].neighbors.push_back(nullptr);//upright
							board[i][j].neighbors.push_back(&board[i + 1][j + 1]);//bottomright
							board[i][j].neighbors.push_back(nullptr);//bottomleft
							board[i][j].neighbors.push_back(nullptr);//topleft

						}
						else if (j == columns - 1) {//top right
							board[i][j].neighbors.push_back(nullptr); //order of neighbor vector is up, right, down, left, upperright, bottomright, bottomleft, upperleft
							board[i][j].neighbors.push_back(nullptr);//right
							board[i][j].neighbors.push_back(&board[i + 1][j]);//down
							board[i][j].neighbors.push_back(&board[i][j - 1]);//left
							board[i][j].neighbors.push_back(nullptr);//upright
							board[i][j].neighbors.push_back(nullptr);//bottomright
							board[i][j].neighbors.push_back(&board[i + 1][j - 1]);//bottomleft
							board[i][j].neighbors.push_back(nullptr);//topleft

						}
					}
					else if (i == rows - 1) {//All Bottom
						if (j != 0 && j != columns - 1) {
							board[i][j].neighbors.push_back(&board[i - 1][j]); //order of neighbor vector is up, right, down, left, upperright, bottomright, bottomleft, upperleft
							board[i][j].neighbors.push_back(&board[i][j + 1]);//right
							board[i][j].neighbors.push_back(nullptr);//down
							board[i][j].neighbors.push_back(&board[i][j - 1]);//left
							board[i][j].neighbors.push_back(&board[i - 1][j + 1]);//upright
							board[i][j].neighbors.push_back(nullptr);//bottomright
							board[i][j].neighbors.push_back(nullptr);//bottomleft
							board[i][j].neighbors.push_back(&board[i - 1][j - 1]);//topleft
						}
						else if (j == 0) { //Bottomleft
							board[i][j].neighbors.push_back(&board[i - 1][j]); //order of neighbor vector is up, right, down, left, upperright, bottomright, bottomleft, upperleft
							board[i][j].neighbors.push_back(&board[i][j + 1]);//right
							board[i][j].neighbors.push_back(nullptr);//down
							board[i][j].neighbors.push_back(nullptr);//left
							board[i][j].neighbors.push_back(&board[i - 1][j + 1]);//upright
							board[i][j].neighbors.push_back(nullptr);//bottomright
							board[i][j].neighbors.push_back(nullptr);//bottomleft
							board[i][j].neighbors.push_back(nullptr);//topleft
						}
						else if (j == columns - 1) {//Bottomright
							board[i][j].neighbors.push_back(&board[i - 1][j]); //order of neighbor vector is up, right, down, left, upperright, bottomright, bottomleft, upperleft
							board[i][j].neighbors.push_back(nullptr);//right
							board[i][j].neighbors.push_back(nullptr);//down
							board[i][j].neighbors.push_back(&board[i][j - 1]);//left
							board[i][j].neighbors.push_back(nullptr);//upright
							board[i][j].neighbors.push_back(nullptr);//bottomright
							board[i][j].neighbors.push_back(nullptr);//bottomleft
							board[i][j].neighbors.push_back(&board[i - 1][j - 1]);//topleft
						}


					}
					else if (i != 0 && i == rows - 1) {
						if (j == 0) { //All left
							board[i][j].neighbors.push_back(&board[i - 1][j]); //order of neighbor vector is up, right, down, left, upperright, bottomright, bottomleft, upperleft
							board[i][j].neighbors.push_back(&board[i][j + 1]);//right
							board[i][j].neighbors.push_back(&board[i + 1][j]);//down
							board[i][j].neighbors.push_back(nullptr);//left
							board[i][j].neighbors.push_back(&board[i - 1][j + 1]);//upright
							board[i][j].neighbors.push_back(&board[i + 1][j + 1]);//bottomright
							board[i][j].neighbors.push_back(nullptr);//bottomleft
							board[i][j].neighbors.push_back(nullptr);//topleft
						}
						else if (j == columns - 1) { //All Right
							board[i][j].neighbors.push_back(&board[i - 1][j]); //order of neighbor vector is up, right, down, left, upperright, bottomright, bottomleft, upperleft
							board[i][j].neighbors.push_back(nullptr);//right
							board[i][j].neighbors.push_back(&board[i + 1][j]);//down
							board[i][j].neighbors.push_back(&board[i][j - 1]);//left
							board[i][j].neighbors.push_back(nullptr);//upright
							board[i][j].neighbors.push_back(nullptr);//bottomright
							board[i][j].neighbors.push_back(&board[i + 1][j - 1]);//bottomleft
							board[i][j].neighbors.push_back(&board[i - 1][j - 1]);//topleft
						}

					}
					if (i > 0 && j > 0 && i < rows - 1 && j < columns - 1) { //ANY INTERIOR TILES
						board[i][j].neighbors.push_back(&board[i - 1][j]); //order of neighbor vector is up, right, down, left, upperright, bottomright, bottomleft, upperleft
						board[i][j].neighbors.push_back(&board[i][j + 1]);//right
						board[i][j].neighbors.push_back(&board[i + 1][j]);//down
						board[i][j].neighbors.push_back(&board[i][j - 1]);//left
						board[i][j].neighbors.push_back(&board[i - 1][j + 1]);//upright
						board[i][j].neighbors.push_back(&board[i + 1][j + 1]);//bottomright
						board[i][j].neighbors.push_back(&board[i + 1][j - 1]);//bottomleft
						board[i][j].neighbors.push_back(&board[i - 1][j - 1]);//topleft
					}



				}
			}
		}
		*/

void Board::Counter() {
	int bombsLeft = bombCount - flagCount;
	int first = abs(bombsLeft / 100) % 10;
	int second = abs(bombsLeft / 10) % 10;
	int third = abs(bombsLeft) % 10;
	for (int i = 0; i < 11; i++) {
		allDigits[i].setTextureRect(IntRect(i * 21, 0, 21, 32));
		allDigits[i].setTexture(TextureManager::GetTexture("digits"));
	}
	counter.clear();
	if (bombsLeft < 0) {
		counter.push_back(allDigits[10]);
	}
	counter.push_back(allDigits[first]);
	counter.push_back(allDigits[second]);
	counter.push_back(allDigits[third]);

}
