class Tile {

public:

	enum TileColor
	{
		BLUE,
		RED,
		GREY,
		EMPTY
	};

	bool operator == (const Tile &Ref) const;

	Tile(TileColor tileColor, int xPos, int yPos);
	Tile(TileColor tileColor, int xPos, int yPos, int value);
	Tile();

	TileColor tileColor;
	int value;
	int xPos;
	int yPos;



private:





};