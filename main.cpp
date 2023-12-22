#include "TextureManager.h"
#include "Board.h"

int main()
{
	//Loading Textures
	unordered_map<string, sf::Sprite> sprites;
	sprites["debug"].setTexture(TextureManager::GetTexture("debug"));
	sprites["face_happy"].setTexture(TextureManager::GetTexture("face_happy"));
	sprites["face_lose"].setTexture(TextureManager::GetTexture("face_lose"));
	sprites["face_win"].setTexture(TextureManager::GetTexture("face_win"));
	sprites["flag"].setTexture(TextureManager::GetTexture("flag"));
	sprites["mine"].setTexture(TextureManager::GetTexture("mine"));
	sprites["number_1"].setTexture(TextureManager::GetTexture("number_1"));
	sprites["number_2"].setTexture(TextureManager::GetTexture("number_2"));
	sprites["number_3"].setTexture(TextureManager::GetTexture("number_3"));
	sprites["number_4"].setTexture(TextureManager::GetTexture("number_4"));
	sprites["number_5"].setTexture(TextureManager::GetTexture("number_5"));
	sprites["number_6"].setTexture(TextureManager::GetTexture("number_6"));
	sprites["number_7"].setTexture(TextureManager::GetTexture("number_7"));
	sprites["number_8"].setTexture(TextureManager::GetTexture("number_8"));
	sprites["test_1"].setTexture(TextureManager::GetTexture("test_1"));
	sprites["test_2"].setTexture(TextureManager::GetTexture("test_2"));
	sprites["test_3"].setTexture(TextureManager::GetTexture("test_3"));
	sprites["tile_hidden"].setTexture(TextureManager::GetTexture("tile_hidden"));
	sprites["tile_revealed"].setTexture(TextureManager::GetTexture("tile_revealed"));
	//Loading digit textures
	sf::Texture digits = TextureManager::GetTexture("digits");
	sf::Sprite digit_0(digits, sf::IntRect(0 * 21, 0, 21, 32));
	sprites["digit_0"] = digit_0;
	sf::Sprite digit_1(digits, sf::IntRect(1 * 21, 0, 21, 32));
	sprites["digit_1"] = digit_1;
	sf::Sprite digit_2(digits, sf::IntRect(2 * 21, 0, 21, 32));
	sprites["digit_2"] = digit_2;
	sf::Sprite digit_3(digits, sf::IntRect(3 * 21, 0, 21, 32));
	sprites["digit_3"] = digit_3;
	sf::Sprite digit_4(digits, sf::IntRect(4 * 21, 0, 21, 32));
	sprites["digit_4"] = digit_4;
	sf::Sprite digit_5(digits, sf::IntRect(5 * 21, 0, 21, 32));
	sprites["digit_5"] = digit_5;
	sf::Sprite digit_6(digits, sf::IntRect(6 * 21, 0, 21, 32));
	sprites["digit_6"] = digit_6;
	sf::Sprite digit_7(digits, sf::IntRect(7 * 21, 0, 21, 32));
	sprites["digit_7"] = digit_7;
	sf::Sprite digit_8(digits, sf::IntRect(8 * 21, 0, 21, 32));
	sprites["digit_8"] = digit_8;
	sf::Sprite digit_9(digits, sf::IntRect(9 * 21, 0, 21, 32));
	sprites["digit_9"] = digit_9;
	sf::Sprite digit_neg(digits, sf::IntRect(10 * 21, 0, 21, 32));
	sprites["digit_neg"] = digit_neg;
	
	//Reading Config File
	int width, height, count;
	ifstream inFile("boards/config.cfg");
	if (!inFile.is_open())
		return 1;
	inFile >> width >> height >> count;
	//cout << "Width: " << width << "\nHeight: " << height << "\nCount: " << count << endl;
	
	//Creating Board
	Board board(width, height, count, sprites);
	sprites.clear();

	//Creating Window
	sf::RenderWindow window(sf::VideoMode(width * 32, height * 32 + 100), "Minesweeper");
	//sf::Vector2u size = window.getSize();
	//cout << "Window Width & Height: " << size.x << ", " << size.y << endl;

	//digit_1.move(sf::Vector2f(21.f, 0.f));

	int xPos, yPos;
	while (window.isOpen())
	{
		window.clear(sf::Color::White);
		board.build(window);
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				xPos = event.mouseButton.x;
				yPos = event.mouseButton.y;
				xPos /= 32;
				yPos /= 32;
				//cout << "xPos: " << xPos << " yPos: " << yPos << endl;
				if (event.mouseButton.button == sf::Mouse::Left)
					board.leftClick(xPos, yPos);
				if (event.mouseButton.button == sf::Mouse::Right)
					board.rightClick(xPos, yPos);
				break;
			default:
				break;
			}
		}
		window.display();
	}
	TextureManager::Clear();
	board.Clear();
	return 0;
}