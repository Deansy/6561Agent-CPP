#include "Tile.h";

Tile::Tile(TileColor tileColor, int xPos, int yPos) {
	this->tileColor = tileColor;
	this->xPos = xPos;
	this->yPos = yPos;
	this->value = 1;
}

Tile::Tile() {
	
}

Tile::Tile(TileColor tileColor, int xPos, int yPos, int value) {
	this->tileColor = tileColor;
	this->xPos = xPos;
	this->yPos = yPos;
	this->value = value;
}


bool Tile::operator== (const Tile &Ref) const
{


	if (Ref.tileColor != this->tileColor) {
		return false;
	}

	if (Ref.value != this->value) {
		return false;
	}

	if (Ref.xPos != this->xPos) {
		return false;
	}

	if (Ref.yPos != this->yPos) {
		return false;
	}


	return true;
}