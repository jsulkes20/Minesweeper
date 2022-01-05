#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
using namespace std;
using namespace sf;

class Tile {
private:
	Sprite spr;
	int imageState;
public:
	bool neighborBombs=false;
	bool bomb=false;
	bool flag = false;
	vector<Tile*> neighbors;
	Vector2f pos;
	bool hidden=true;
	void setSprite(const sf::Texture& texture);
	Sprite& GetSprite();
	void setPos(const Vector2f& pos);
	Vector2f GetPos();
	void isFlag(bool f);
	void isBomb(bool b);
	int NeighborBombs();
	Tile(int imgst);
	int GetIMG();
	void SetIMG(int img);
	Tile();
	 //0 is hidden, 1 is revealed, 2 is flag, 3 is number, 4 is mine
};