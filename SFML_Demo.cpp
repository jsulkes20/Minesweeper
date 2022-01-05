#include <SFML/Graphics.hpp>
#include <iostream>
#include <iostream>
#include <fstream>
#include "TextureManager.h"
#include "Board.h"
#include "Tile.h"
#include "Random.h"
using namespace std;
using namespace sf;


void DrawFigures(Board& board, RenderWindow& window);
const char* GetNumbText(int neighborBombs);
void RecursiveNeighbors(const vector<Tile*>& neighbors, Board& board);
int main()
{
	Board board;
	board.loadConf("boards/config.cfg");
	board.MakeBoard();
	int r = board.rows;
	int c = board.columns;

	board.setNeighbors();
	RenderWindow window(sf::VideoMode(board.width, board.height), "Minesweeper");
	TextureManager::LoadTexture("number_1");
	TextureManager::LoadTexture("number_2");
	TextureManager::LoadTexture("number_3");
	TextureManager::LoadTexture("number_4");
	TextureManager::LoadTexture("number_5");
	TextureManager::LoadTexture("number_6");
	TextureManager::LoadTexture("number_7");
	TextureManager::LoadTexture("number_8");
	TextureManager::LoadTexture("debug");
	TextureManager::LoadTexture("digits");
	TextureManager::LoadTexture("face_happy");
	TextureManager::LoadTexture("face_lose");
	TextureManager::LoadTexture("face_win");
	TextureManager::LoadTexture("flag");
	TextureManager::LoadTexture("mine");
	TextureManager::LoadTexture("test_1");
	TextureManager::LoadTexture("test_2");
	TextureManager::LoadTexture("test_3");
	TextureManager::LoadTexture("tile_revealed");
	TextureManager::LoadTexture("tile_hidden");
	sf::Sprite face;
	sf::Sprite debug;
	sf::Sprite test1;
	sf::Sprite test2;
	sf::Sprite test3;
	sf::Sprite digits;
	face.setTexture(TextureManager::GetTexture("face_happy"));
	debug.setTexture(TextureManager::GetTexture("debug"));
	test1.setTexture(TextureManager::GetTexture("test_1"));
	test2.setTexture(TextureManager::GetTexture("test_2"));
	test3.setTexture(TextureManager::GetTexture("test_3"));
	digits.setTexture(TextureManager::GetTexture("digits"));
	face.setPosition((board.width / 2.0f) - 32.0f, board.height - 88.0f);
	digits.setPosition(32.0f, board.height - 88.0f);
	debug.setPosition((board.width / 2.0f) + 112.0f, board.height - 88.0f);
	test1.setPosition((board.width / 2.0f) + 176.0f, board.height - 88.0f);
	test2.setPosition((board.width / 2.0f) + 240.0f, board.height - 88.0f);
	test3.setPosition((board.width / 2.0f) + 304.0f, board.height - 88.0f);
	int mouse1 = 0;
	int mouse2 = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}

			if (event.type == Event::MouseButtonPressed) {

				mouse1 = Mouse::getPosition(window).x;
				mouse2 = Mouse::getPosition(window).y;
				if (event.mouseButton.button == Mouse::Right) {


					if (board.height - 88 > mouse2 && board.lose == false && board.win==false) {

						if (board.board[mouse2 / 32][mouse1 / 32].GetIMG() == 0) {
							board.board[mouse2 / 32][mouse1 / 32].SetIMG(2);
							board.flagCount++;

						}
						else if (board.board[mouse2 / 32][mouse1 / 32].GetIMG() == 2) {
							board.board[mouse2 / 32][mouse1 / 32].SetIMG(0);
							board.flagCount--;
						}
						
					}





				}



				else if (event.mouseButton.button == Mouse::Left) {

					if (board.height - 88 > mouse2 && board.lose == false && board.win == false) {
						if (board.board[mouse2 / 32][mouse1 / 32].bomb == true) {

							if (board.board[mouse2 / 32][mouse1 / 32].GetIMG() == 0) {
								for (int i = 0; i < board.rows; i++) {
									for (int j = 0; j < board.columns; j++) {
										if (board.board[i][j].bomb == true) {
											if (board.board[i][j].GetIMG() == 0) {
												board.board[i][j].SetIMG(3);
											}
											else {
												board.board[i][j].SetIMG(4);
											}
										}
									}
								}
								board.lose = true;
								face.setTexture(TextureManager::GetTexture("face_lose"));
							}
							else if (board.board[mouse2 / 32][mouse1 / 32].GetIMG() == 2) {
								board.board[mouse2 / 32][mouse1 / 32].SetIMG(2);
							}
						}
						else {
							board.lose = false;
							if (board.board[mouse2 / 32][mouse1 / 32].GetIMG() == 0) {
								if (board.board[mouse2 / 32][mouse1 / 32].NeighborBombs() > 0) {
									board.board[mouse2 / 32][mouse1 / 32].SetIMG(1);
									
								}
								else {
									RecursiveNeighbors(board.board[mouse2 / 32][mouse1 / 32].neighbors, board);
								}
							}
							else if (board.board[mouse2 / 32][mouse1 / 32].GetIMG() == 2) {
								board.board[mouse2 / 32][mouse1 / 32].SetIMG(2);
							}
						}


					}
					else if (face.getGlobalBounds().contains(Vector2f(mouse1, mouse2))) {


						for (int i = 0; i < board.rows; i++) {
							for (int j = 0; j < board.columns; j++) {
								board.board[i][j].SetIMG(0);
								board.board[i][j].bomb = false;
							}
						}
						for (int i = 0; i < board.bombCount; i++) {
							int x = Random::Int(0, board.rows - 1);
							int y = Random::Int(0, board.columns - 1);
							board.board[x][y].bomb = true;

						}

						face.setTexture(TextureManager::GetTexture("face_happy"));
						board.lose = false;
						board.win = false;
					}
					else if (debug.getGlobalBounds().contains(Vector2f(mouse1, mouse2))) {
						if (board.lose == false && board.win==false) {
							board.showBombs = !board.showBombs;
						}
					}
					else if (test1.getGlobalBounds().contains(Vector2f(mouse1, mouse2))) {
						
						board.board.clear();
						face.setTexture(TextureManager::GetTexture("face_happy"));
						for (int i = 0; i < board.rows; i++) {
							for (int j = 0; j < board.columns; j++) {
								Tile tile(0);
								Vector2f posi = Vector2f((float)(j * 32), (float)(i * 32));


								board.b.push_back(tile);
							}

							board.board.push_back(board.b);

						}
						fstream infile;
						int rows = board.rows;
						vector<vector<char>> charBoard;
						vector<char> cb;
						infile.open("boards/testBoard1.brd");
						if (!infile.is_open()) {
							cout << "Did not open";
						}
						int i = 0;
						while (!infile.eof()) {
							string line;
							getline(infile, line);
							for (int j = 0; j < board.columns; j++) {
								if (line.at(j) == '1') {
									board.board[i][j].bomb = true;
								}
							}

							i++;
						}
						board.lose = false;
						board.win = false;
						
					}
					else if (test2.getGlobalBounds().contains(Vector2f(mouse1, mouse2))) {
						
						board.board.clear();
						face.setTexture(TextureManager::GetTexture("face_happy"));
						for (int i = 0; i < board.rows; i++) {
							for (int j = 0; j < board.columns; j++) {
								Tile tile(0);
								Vector2f posi = Vector2f((float)(j * 32), (float)(i * 32));


								board.b.push_back(tile);
							}

							board.board.push_back(board.b);

						}
						fstream infile;
						int rows = board.rows;
						vector<vector<char>> charBoard;
						vector<char> cb;
						infile.open("boards/testBoard2.brd");
						if (!infile.is_open()) {
							cout << "Did not open";
						}
						int i = 0;
						while (!infile.eof()) {
							string line;
							getline(infile, line);
							for (int j = 0; j < board.columns; j++) {
								if (line.at(j) == '1') {
									board.board[i][j].bomb = true;
								}
							}

							i++;
						}
						board.win = false;
						board.lose = false;
						
					}
					else if (test3.getGlobalBounds().contains(Vector2f(mouse1, mouse2))) {
						board.board.clear();
						face.setTexture(TextureManager::GetTexture("face_happy"));
						for (int i = 0; i < board.rows; i++) {
							for (int j = 0; j < board.columns; j++) {
								Tile tile(0);
								Vector2f posi = Vector2f((float)(j * 32), (float)(i * 32));


								board.b.push_back(tile);
							}

							board.board.push_back(board.b);

						}
						board.setNeighbors();
						fstream infile;
						int rows = board.rows;
						
						infile.open("boards/testBoard3.brd");
						if (!infile.is_open()) {
							cout << "Did not open";
						}
						int i = 0;
						while (!infile.eof()) {
							string line;
							getline(infile, line);
							for (int j = 0; j < board.columns; j++) {
								if (line.at(j) == '1') {
									board.board[i][j].bomb = true;
								}
							}

							i++;
						}
						board.win = false;
						board.lose = false;
					}
					else {
					board.win = false;
					board.lose = false;
}
					for (int i = 0; i < board.rows; i++) {
						for (int j = 0; j < board.columns; j++) {
							if (board.board[i][j].GetIMG() == 1 || board.board[i][j].GetIMG() == 5) {
								board.revealedTiles++;
							}
						}
					} 
					if (board.bombCount + board.revealedTiles == board.tileCount) {
						board.win = true;
						face.setTexture(TextureManager::GetTexture("face_win"));
						for (int i = 0; i < board.rows; i++) {
							for (int j = 0; j < board.columns; j++) {
								if (board.board[i][j].GetIMG()==0) {
									board.board[i][j].SetIMG(2);
								}
							}
						}
							

					}
					else {
						board.revealedTiles = 0;
					}
					cout << board.revealedTiles << endl;
				}
				
			}



		}




		window.clear();
		board.Counter();
		for (int i = 0; i < board.counter.size(); i++) {
			board.counter[i].setPosition(Vector2f(i * 21, board.rows * 32));
		}
		for (int i = 0; i < board.counter.size(); i++) {
			window.draw(board.counter[i]);
		}
		DrawFigures(board, window);
		window.draw(face);
		window.draw(debug);
		window.draw(test1);
		window.draw(test2);
		window.draw(test3);
		//window.draw(digits);


		window.display();
	}
	return 0;
}










void DrawFigures(Board& board, RenderWindow& window) {
	Sprite hide;
	Sprite fl;
	Sprite bomb;
	Sprite reveal;
	Sprite numb;

	fl.setTexture(TextureManager::GetTexture("flag"));
	bomb.setTexture(TextureManager::GetTexture("mine"));
	reveal.setTexture(TextureManager::GetTexture("tile_revealed"));
	hide.setTexture(TextureManager::GetTexture("tile_hidden"));
	for (int i = 0; i < board.rows; i++) {
		for (int j = 0; j < board.columns; j++) {
			if (board.board[i][j].GetIMG() == 0) {
				hide.setPosition(Vector2f((float)(j * 32), (float)(i * 32)));
				window.draw(hide);
				if (board.showBombs == true) {
					if (board.board[i][j].bomb == true) {
						bomb.setPosition(Vector2f((float)(j * 32), (float)(i * 32)));
						window.draw(bomb);
					}

				}

			}
			else if (board.board[i][j].GetIMG() == 1) {

				reveal.setPosition(Vector2f((float)(j * 32), (float)(i * 32)));
				numb.setPosition(Vector2f((float)(j * 32), (float)(i * 32)));
				numb.setTexture(TextureManager::GetTexture(GetNumbText(board.board[i][j].NeighborBombs())));
				
				window.draw(reveal);
				window.draw(numb);

				

				if (board.showBombs == true) {
					if (board.board[i][j].bomb == true) {
						bomb.setPosition(Vector2f((float)(j * 32), (float)(i * 32)));
						window.draw(bomb);
					}

				}
			}
			else if (board.board[i][j].GetIMG() == 2) {

				fl.setPosition(Vector2f((float)(j * 32), (float)(i * 32)));
				hide.setPosition(Vector2f((float)(j * 32), (float)(i * 32)));
				window.draw(hide);
				window.draw(fl);
				if (board.showBombs == true) {
					if (board.board[i][j].bomb == true) {
						bomb.setPosition(Vector2f((float)(j * 32), (float)(i * 32)));
						window.draw(bomb);
					}

				}
			}
			else if (board.board[i][j].GetIMG() == 3) {
				bomb.setPosition(Vector2f((float)(j * 32), (float)(i * 32)));
				reveal.setPosition(Vector2f((float)(j * 32), (float)(i * 32)));
				window.draw(reveal);
				window.draw(bomb);
				if (board.showBombs == true) {
					if (board.board[i][j].bomb == true) {
						bomb.setPosition(Vector2f((float)(j * 32), (float)(i * 32)));
						window.draw(bomb);
					}

				}
			}
			else if (board.board[i][j].GetIMG() == 4) {
				fl.setPosition(Vector2f((float)(j * 32), (float)(i * 32)));
				hide.setPosition(Vector2f((float)(j * 32), (float)(i * 32)));
				bomb.setPosition(Vector2f((float)(j * 32), (float)(i * 32)));
				window.draw(hide);
				window.draw(fl);
				window.draw(bomb);
			}
			else if (board.board[i][j].GetIMG() == 5) {
				reveal.setPosition(Vector2f((float)(j * 32), (float)(i * 32)));
				window.draw(reveal);
			}





			/*else if (board.board[i][j].bomb==false && board.board[i][j]->hidden == false) {
				if (board.board[i][j]->NeighborBombs()>1) {
					reveal.setPosition(Vector2f((float)(j * 32), (float)(i * 32)));
					numb.setPosition(Vector2f((float)(j * 32), (float)(i * 32)));
					numb.setTexture(TextureManager::GetTexture(GetNumbText(board.board[i][j]->NeighborBombs())));
					window.draw(reveal);
					window.draw(numb);
				}
				else {
					RecursiveNeighbors(board.board[i][j]->neighbors, window);
					board.revealedTiles++;

				}
			}


		*/




		}
	}
}







void RecursiveNeighbors(const vector<Tile*>& neighbors, Board& board) {
	for (unsigned int i = 0; i < neighbors.size(); i++) {
		if (neighbors[i] != nullptr) {
			if (neighbors[i]->NeighborBombs() > 0 && neighbors[i]->bomb == false) {
				neighbors[i]->SetIMG(1);
				
				
			}

			else if (neighbors[i]->NeighborBombs() == 0 && neighbors[i]->bomb == false && neighbors[i]->GetIMG()==0) {
				neighbors[i]->SetIMG(5);
				

				RecursiveNeighbors(neighbors[i]->neighbors, board);

			}



		}

	}
}







const char* GetNumbText(int nb) {
	const char* solution = "";
	if (nb == 1) {
		solution = "number_1";
	}
	else if (nb == 2) {
		solution = "number_2";
	}
	else if (nb == 3) {
		solution = "number_3";
	}
	else if (nb == 4) {
		solution = "number_4";
	}
	else if (nb == 5) {
		solution = "number_5";
	}
	else if (nb == 6) {
		solution = "number_6";
	}
	else if (nb == 7) {
		solution = "number_7";
	}
	else if (nb == 8) {
		solution = "number_8";
	}
	return solution;
}


/*void changeBoard(string& test) {
	if (test == "face") {
		MakeBoard();
	}
	else if (test == "boards/testboard1.brd") {
		loadConf(test);
		showbombs = true;
		MakeBoard();
	}
	else if (test == "boards/testboard2.brd") {
		loadConf(test);
		showbombs = true;
		MakeBoard();
	}
	else if (test == "boards/testboard3.brd") {
		loadConf(test);
		showbombs = true;
		MakeBoard();
	}
}
*/
