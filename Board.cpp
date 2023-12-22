#include "Board.h"

Board::Board(int width, int height, int count, unordered_map<string, sf::Sprite>& sprites)
{
	this->width = width;
	this->height = height;
	this->count = count;
	this->configCount = count;
	this->sprites = sprites;
	//loading digits into map for counter display
	digits[0] = sprites["digit_0"];
	digits[1] = sprites["digit_1"];
	digits[2] = sprites["digit_2"];
	digits[3] = sprites["digit_3"];
	digits[4] = sprites["digit_4"];
	digits[5] = sprites["digit_5"];
	digits[6] = sprites["digit_6"];
	digits[7] = sprites["digit_7"];
	digits[8] = sprites["digit_8"];
	digits[9] = sprites["digit_9"];
	//allocating 2-d vector to store tile objects in
	tiles = vector<vector<Tile>>(width, vector<Tile>(height));
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			//Fill in vector with tile objects
			Tile temp;
			//inFile >> temp.is_bomb;
			tiles[i].push_back(temp);
		}
	}
	//randomly assigns bombs to tiles
	generateRandom();
}

void Board::loadBoard(string fileName)
{
	//mines are counted in this code
	//small bug fix: count would be configCount + test board count
	count = 0;
	char temp;
	string path = "boards/" + fileName + ".brd";
	inFile.open(path);
	//iteratre from left to right (page style)
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			inFile >> temp;
			//temp is char, convert to decimal value
			if (temp - 48 != 0)
			{
				//reading from left to right
				tiles[j][i].is_bomb = temp - 48;
				count++;
			}
		}
	}
	//bux fix: test board count and config count conflict
	totalMines = count;
	inFile.close();
	//update tiles based on number of mines surrounding
	bombCount();
}

void Board::generateRandom()
{
	//invalid mine count error handling
	if (configCount > (width * height) || configCount < 0)
	{
		cout << "invalid count" << endl;
		return;
	}
	srand(time(NULL));
	int bomb = 1;
	int x, y;
	count = 0;
	while (count < configCount)
	{
		x = rand() % width;
		y = rand() % height;
		//if a 1 is generated, assign bomb to random tile, unless tile already has bomb, count++
		if (bomb == rand() % 2 && !tiles[x][y].is_bomb)
		{
			tiles[x][y].is_bomb = 1;
			count++;
		}
	}
	totalMines = count;
	//update tiles based on number of mines surrounding
	bombCount();
}

void Board::initializeNull()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				tiles[i][j].neighbors[k] = nullptr;
			}
		}
	}
}

void Board::bombCount()
{
	initializeNull();
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			//LEFT WALL////////////////////////////////////////////////
			if (i == 0)
			{
				//right
				tiles[i][j].neighbors[3] = &(tiles[i + 1][j]);
				if (tiles[i + 1][j].is_bomb)
					tiles[i][j].bomb_count++;
				//top left corner
				if (j == 0)
				{
					//bottom right
					tiles[i][j].neighbors[4] = &(tiles[i + 1][j + 1]);
					if (tiles[i + 1][j + 1].is_bomb)
						tiles[i][j].bomb_count++;
					//bottom
					tiles[i][j].neighbors[5] = &(tiles[i][j + 1]);
					if (tiles[i][j + 1].is_bomb)
						tiles[i][j].bomb_count++;
					continue;
				}
				//bottom left corner
				if (j == height - 1)
				{
					//top
					tiles[i][j].neighbors[1] = &(tiles[i][j - 1]);
					if (tiles[i][j - 1].is_bomb)
						tiles[i][j].bomb_count++;
					//top right
					tiles[i][j].neighbors[2] = &(tiles[i + 1][j - 1]);
					if (tiles[i + 1][j - 1].is_bomb)
						tiles[i][j].bomb_count++;
					continue;
				}
				//all other left wall tiles
				//top
				tiles[i][j].neighbors[1] = &(tiles[i][j - 1]);
				if (tiles[i][j - 1].is_bomb)
					tiles[i][j].bomb_count++;
				//top right
				tiles[i][j].neighbors[2] = &(tiles[i + 1][j - 1]);
				if (tiles[i + 1][j - 1].is_bomb)
					tiles[i][j].bomb_count++;
				//bottom right
				tiles[i][j].neighbors[4] = &(tiles[i + 1][j + 1]);
				if (tiles[i + 1][j + 1].is_bomb)
					tiles[i][j].bomb_count++;
				//bottom
				tiles[i][j].neighbors[5] = &(tiles[i][j + 1]);
				if (tiles[i][j + 1].is_bomb)
					tiles[i][j].bomb_count++;
			}
			//RIGHT WALL/////////////////////////////////////////////////
			if (i == width - 1)
			{
				//left
				tiles[i][j].neighbors[7] = &(tiles[i - 1][j]);
				if (tiles[i - 1][j].is_bomb)
					tiles[i][j].bomb_count++;
				//top right corner
				if (j == 0)
				{
					//bottom
					tiles[i][j].neighbors[5] = &(tiles[i][j + 1]);
					if (tiles[i][j + 1].is_bomb)
						tiles[i][j].bomb_count++;
					//bottom left
					tiles[i][j].neighbors[6] = &(tiles[i - 1][j + 1]);
					if (tiles[i - 1][j + 1].is_bomb)
						tiles[i][j].bomb_count++;
					continue;
				}
				//bottom right corner
				if (j == height - 1)
				{
					//top
					tiles[i][j].neighbors[1] = &(tiles[i][j - 1]);
					if (tiles[i][j - 1].is_bomb)
						tiles[i][j].bomb_count++;
					//top left
					tiles[i][j].neighbors[0] = &(tiles[i - 1][j - 1]);
					if (tiles[i - 1][j - 1].is_bomb)
						tiles[i][j].bomb_count++;
					continue;
				}
				//all other right wall tiles
				//top left
				tiles[i][j].neighbors[0] = &(tiles[i - 1][j - 1]);
				if (tiles[i - 1][j - 1].is_bomb)
					tiles[i][j].bomb_count++;
				//top
				tiles[i][j].neighbors[1] = &(tiles[i][j - 1]);
				if (tiles[i][j - 1].is_bomb)
					tiles[i][j].bomb_count++;
				//bottom
				tiles[i][j].neighbors[5] = &(tiles[i][j + 1]);
				if (tiles[i][j + 1].is_bomb)
					tiles[i][j].bomb_count++;
				//bottom left
				tiles[i][j].neighbors[6] = &(tiles[i - 1][j + 1]);
				if (tiles[i - 1][j + 1].is_bomb)
					tiles[i][j].bomb_count++;
				//left
				tiles[i][j].neighbors[7] = &(tiles[i - 1][j]);
				if (tiles[i - 1][j].is_bomb)
					tiles[i][j].bomb_count++;
			}
			//TOP WALL/////////////////////////////////////////////////
			//ignoring corners of board (already handled)
			if (j == 0 && i > 0 && i < width - 1)
			{
				//right
				tiles[i][j].neighbors[3] = &(tiles[i + 1][j]);
				if (tiles[i + 1][j].is_bomb)
					tiles[i][j].bomb_count++;
				//bottom right
				tiles[i][j].neighbors[4] = &(tiles[i + 1][j + 1]);
				if (tiles[i + 1][j + 1].is_bomb)
					tiles[i][j].bomb_count++;
				//bottom
				tiles[i][j].neighbors[5] = &(tiles[i][j + 1]);
				if (tiles[i][j + 1].is_bomb)
					tiles[i][j].bomb_count++;
				//bottom left
				tiles[i][j].neighbors[6] = &(tiles[i - 1][j + 1]);
				if (tiles[i - 1][j + 1].is_bomb)
					tiles[i][j].bomb_count++;
				//left
				tiles[i][j].neighbors[7] = &(tiles[i - 1][j]);
				if (tiles[i - 1][j].is_bomb)
					tiles[i][j].bomb_count++;
			}
			//BOTTOM WALL/////////////////////////////////////////////////
			//ignoring corners of board (already handled)
			if (j == height - 1 && i > 0 && i < width - 1)
			{
				//top left
				tiles[i][j].neighbors[0] = &(tiles[i - 1][j - 1]);
				if (tiles[i - 1][j - 1].is_bomb)
					tiles[i][j].bomb_count++;
				//top
				tiles[i][j].neighbors[1] = &(tiles[i][j - 1]);
				if (tiles[i][j - 1].is_bomb)
					tiles[i][j].bomb_count++;
				//top right
				tiles[i][j].neighbors[2] = &(tiles[i + 1][j - 1]);
				if (tiles[i + 1][j - 1].is_bomb)
					tiles[i][j].bomb_count++;
				//right
				tiles[i][j].neighbors[3] = &(tiles[i + 1][j]);
				if (tiles[i + 1][j].is_bomb)
					tiles[i][j].bomb_count++;
				//left
				tiles[i][j].neighbors[7] = &(tiles[i - 1][j]);
				if (tiles[i - 1][j].is_bomb)
					tiles[i][j].bomb_count++;
			}
			//non-perimiter tiles
			if (i > 0 && j > 0 && i < (width - 1) && j < (height - 1))
			{
				//top left
				tiles[i][j].neighbors[0] = &(tiles[i - 1][j - 1]);
				if (tiles[i - 1][j - 1].is_bomb)
					tiles[i][j].bomb_count++;
				//top
				tiles[i][j].neighbors[1] = &(tiles[i][j - 1]);
				if (tiles[i][j - 1].is_bomb)
					tiles[i][j].bomb_count++;
				//top right
				tiles[i][j].neighbors[2] = &(tiles[i + 1][j - 1]);
				if (tiles[i + 1][j - 1].is_bomb)
					tiles[i][j].bomb_count++;
				//right
				tiles[i][j].neighbors[3] = &(tiles[i + 1][j]);
				if (tiles[i + 1][j].is_bomb)
					tiles[i][j].bomb_count++;
				//bottom right
				tiles[i][j].neighbors[4] = &(tiles[i + 1][j + 1]);
				if (tiles[i + 1][j + 1].is_bomb)
					tiles[i][j].bomb_count++;
				//bottom
				tiles[i][j].neighbors[5] = &(tiles[i][j + 1]);
				if (tiles[i][j + 1].is_bomb)
					tiles[i][j].bomb_count++;
				//bottom left
				tiles[i][j].neighbors[6] = &(tiles[i - 1][j + 1]);
				if (tiles[i - 1][j + 1].is_bomb)
					tiles[i][j].bomb_count++;
				//left
				tiles[i][j].neighbors[7] = &(tiles[i - 1][j]);
				if (tiles[i - 1][j].is_bomb)
					tiles[i][j].bomb_count++;
			}
		}
	}
}


void Board::reset()
{
	//reset to default board state (except debug mode)
	count = configCount;
	lost = 0;
	won = 0;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			//reset each tile to default state
			tiles[i][j].is_bomb = 0;
			tiles[i][j].flag = 0;
			tiles[i][j].revealed = 0;
			tiles[i][j].bomb_count = 0;
		}
	}
}

// Building/Drawing the Board /////////////////////////////////////////
void Board::build(sf::RenderWindow& window)
{
	int temp, first, second, third, not_revealed = width * height;
	for (int i = 0; i < width; i++)
	{
		//draw footer first, mostly constant
		//drawing face depending on win state
		if (won)
		{
			sprites["face_win"].setPosition(sf::Vector2f(32.f * 11, 32.f * height));
			window.draw(sprites["face_win"]);
		}
		else if (lost)
		{
			sprites["face_lose"].setPosition(sf::Vector2f(32.f * 11, 32.f * height));
			window.draw(sprites["face_lose"]);
		}
		else
		{
			sprites["face_happy"].setPosition(sf::Vector2f(32.f * 11, 32.f * height));
			window.draw(sprites["face_happy"]);
		}
		sprites["debug"].setPosition(sf::Vector2f(32.f * 15, 32.f * height));
		window.draw(sprites["debug"]);
		sprites["test_1"].setPosition(sf::Vector2f(32.f * 17, 32.f * height));
		window.draw(sprites["test_1"]);
		sprites["test_2"].setPosition(sf::Vector2f(32.f * 19, 32.f * height));
		window.draw(sprites["test_2"]);
		sprites["test_3"].setPosition(sf::Vector2f(32.f * 21, 32.f * height));
		window.draw(sprites["test_3"]);
		//going through ever tile
		for (int j = 0; j < height; j++)
		{
			//if the hasn't been clicked
			if (!tiles[i][j].revealed)
			{
				//if game is lost, reveal all bombs
				if (lost && tiles[i][j].is_bomb)
				{
					//formatting
					sprites["tile_revealed"].setPosition(sf::Vector2f(32.f * i, 32.f * j));
					window.draw(sprites["tile_revealed"]);
					//drawing all mines
					sprites["mine"].setPosition(sf::Vector2f(32.f * i, 32.f * j));
					window.draw(sprites["mine"]);
					//skip all other drawings unless resart is hit => lost = 0
					continue;
				}
				//draw hidden tile for unrevealed
				sprites["tile_hidden"].setPosition(sf::Vector2f(32.f * i, 32.f * j));
				window.draw(sprites["tile_hidden"]);
				//if game is won, draw flags on all unrevealed tiles/bombs
				if (won && tiles[i][j].is_bomb)
				{
					tiles[i][j].flag = 1;
					//little hack
					count = 0;
				}
				//if flagged, draw flag over tile
				if (tiles[i][j].flag)
				{
					sprites["flag"].setPosition(sf::Vector2f(32.f * i, 32.f * j));
					window.draw(sprites["flag"]);
				}
			}
			else
			{
				not_revealed--;
				//if tile has been clicked, reveal hidden tile
				switch (tiles[i][j].bomb_count)
				{
				case 0:
					sprites["tile_revealed"].setPosition(sf::Vector2f(32.f * i, 32.f * j));
					window.draw(sprites["tile_revealed"]);
					//insert recursive reveal here
					break;
				case 1:
					sprites["number_1"].setPosition(sf::Vector2f(32.f * i, 32.f * j));
					window.draw(sprites["number_1"]);
					break;
				case 2:
					sprites["number_2"].setPosition(sf::Vector2f(32.f * i, 32.f * j));
					window.draw(sprites["number_2"]);
					break;
				case 3:
					sprites["number_3"].setPosition(sf::Vector2f(32.f * i, 32.f * j));
					window.draw(sprites["number_3"]);
					break;
				case 4:
					sprites["number_4"].setPosition(sf::Vector2f(32.f * i, 32.f * j));
					window.draw(sprites["number_4"]);
					break;
				case 5:
					sprites["number_5"].setPosition(sf::Vector2f(32.f * i, 32.f * j));
					window.draw(sprites["number_5"]);
					break;
				case 6:
					sprites["number_6"].setPosition(sf::Vector2f(32.f * i, 32.f * j));
					window.draw(sprites["number_6"]);
					break;
				case 7:
					sprites["number_7"].setPosition(sf::Vector2f(32.f * i, 32.f * j));
					window.draw(sprites["number_7"]);
					break;
				case 8:
					sprites["number_8"].setPosition(sf::Vector2f(32.f * i, 32.f * j));
					window.draw(sprites["number_8"]);
					break;
				default:
					break;
				}
			}
			//if debug mode is on, reveal all mines, assuming game hasn't been lost
			//reveal flag all mines if game is won
			if (debug)
			{
				if (tiles[i][j].is_bomb)
				{
					sprites["mine"].setPosition(sf::Vector2f(32.f * i, 32.f * j));
					window.draw(sprites["mine"]);
				}
			}
		}
		//if the number of unrevealed tiles = number of mines, game is won
		//no tiles left besides mines
		if (not_revealed == totalMines)
			won = 1;
		//Mine Counter (can go into negative)
		temp = count;
		first = temp / 100;
		temp %= 100;
		second = temp / 10;
		third = temp % 10;
		//if mines go into negative, convert to positive integers and display negative sign
		if (count < 0)
		{
			sprites["digit_neg"].setPosition(sf::Vector2f(0.f, height * 32.f));
			window.draw(sprites["digit_neg"]);
			first *= -1;
			second *= -1;
			third *= -1;
		}
		digits[first].setPosition(sf::Vector2f(21.f * 1, height * 32.f));
		window.draw(digits[first]);
		digits[second].setPosition(sf::Vector2f(21.f * 2, height * 32.f));
		window.draw(digits[second]);
		digits[third].setPosition(sf::Vector2f(21.f * 3, height * 32.f));
		window.draw(digits[third]);
	}
}

void Board::leftClick(int x, int y)
{
	
	//if clicking outside of minefield (footer)
	if (y >= height)
	{
		//click on smiley
		if (x >= 11 && x <= 12 && y >= height && y <= (height + 1))
		{
			reset();
			generateRandom();
		}
		//click on debug
		if (x >= 15 && x <= 16 && y >= height && y <= (height + 1))
		{
			if (debug)
				debug = 0;
			else
				debug = 1;
		}
		//click on test boards
		if (x >= 17 && x <= 18 && y >= height && y <= (height + 1))
		{
			reset();
			loadBoard("testboard1");
		}
		if (x >= 19 && x <= 20 && y >= height && y <= (height + 1))
		{
			reset();
			loadBoard("testboard2");
		}
		if (x >= 21 && x <= 22 && y >= height && y <= (height + 1))
		{
			reset();
			loadBoard("testboard3");
		}
		return;
	}
	//if already revealed or has flag, ignore click
	if (tiles[x][y].revealed || tiles[x][y].flag)
		return;
	//clicking on a bomb loses the game
	if (tiles[x][y].is_bomb)
	{
		lost = 1;
		return;
	}
	//reveals tile
	tiles[x][y].revealed = 1;
	//if tile is a blank tile, call recursiveReveal()
	if (tiles[x][y].bomb_count == 0)
		recursiveReveal(tiles[x][y]);
}

void Board::rightClick(int x, int y)
{
	//if outside of field, ignore
	if (y > height)
		return;
	//ignore if already revealed tile
	if (tiles[x][y].revealed)
		return;
	//if there's already a flag, remove the flag at that location
	if (tiles[x][y].flag)
	{
		tiles[x][y].flag = 0;
		count++;
		return;
	}
	//place a flag and reduce the remaining mines counter
	tiles[x][y].flag = 1;
	count--;
}

void Board::recursiveReveal(Tile& tile)
{
	//addresses of tiles and neighbor address AREN'T THE PROBLEM
	//neither is the tile variable or neigbor member variables
	for (int k = 0; k < 8; k++)
	{
		//if neighboring tile isn't:
		// a bomb, nullptr, revealed, numbered
		// -> reveal and recursive call on selected tile
		if (tile.neighbors[k] == nullptr)
			continue;
		if (tile.neighbors[k]->is_bomb == 0 && tile.neighbors[k]->revealed == 0)
		{
			tile.neighbors[k]->revealed = 1;
			if (tile.neighbors[k]->bomb_count != 0)
				continue;
			recursiveReveal(*(tile.neighbors[k]));
		}
	}
	cout << "outside recursive" << endl;
}

void Board::Clear()
{
	sprites.clear();
	digits.clear();
}