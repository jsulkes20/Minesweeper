#include "Tile.h"

void Tile::setSprite(const sf::Texture& texture) {
    spr.setTexture(texture);
}
Sprite &Tile::GetSprite() {
    return spr;
}
Tile::Tile(int imgst) {
    imageState = imgst;
}
Tile::Tile() {
    imageState = 0;
}
int Tile::GetIMG() {
    return imageState;
}
int Tile::NeighborBombs() {
    int num=0;
    for (unsigned int i = 0; i < neighbors.size(); i++) {
        if (neighbors[i] != nullptr) {
            if (neighbors[i]->bomb == true) {
                
                num++;
            }
        }
        
    }
    return num;
}
void Tile:: SetIMG(int img) {
    imageState= img;
}


