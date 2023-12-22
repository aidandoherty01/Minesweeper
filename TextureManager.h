#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

class TextureManager
{
	//static == one and onlyy one of thes in memory, ever
	static unordered_map<string, sf::Texture> textures;
public:
	static void LoadTexture(string fileName); // LoadTexture("space")
	static sf::Texture& GetTexture(string textureName); // GetTexture("space")
	static void Clear(); // Call this once, at the end of main()
};