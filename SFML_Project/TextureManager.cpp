#include "TextureManager.h"

TextureManager::TextureManager()
{}

TextureManager::~TextureManager()
{}

void TextureManager::Add(const TEXTURE& texture_key, const std::string& filename)
{
	if (this->textures.find(texture_key) != this->textures.end())
	{
		throw std::invalid_argument("This item already exists.");
	}

	sf::Texture new_texture;

	if (!new_texture.loadFromFile(filename))
	{
		throw std::invalid_argument("Couldn't open texture file.");
	}

	this->textures.insert(std::pair<TEXTURE, sf::Texture>(texture_key, new_texture));
}

sf::Texture& TextureManager::Get(const TEXTURE& texture_key)
{
	if (this->textures.find(texture_key) == this->textures.end())
	{
		throw std::out_of_range("This texture doesn't exist.");
	}

	return this->textures.at(texture_key);
}
