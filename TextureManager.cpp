#include "TextureManager.h"

// "redeclare" the variable, so this file knows it exists and can use it
unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName)
{
	string path = "images/" + fileName + ".png";
	textures[fileName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string textureName)
{
	// find is better because it can stop at first instance
	// count will iterate through entire list
	if (textures.find(textureName) == textures.end())
		LoadTexture(textureName);
	return textures[textureName];
}

void TextureManager::Clear()
{
	textures.clear(); // get rid of all stored objects
}