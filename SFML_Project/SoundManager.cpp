#include "SoundManager.h"

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::Add(const SOUND& sound_key, const std::string& filename)
{
	if (this->sounds_.find(sound_key) != this->sounds_.end())
	{
		throw std::invalid_argument("This item already exists.");
	}

	sf::SoundBuffer new_buffer;

	if (!new_buffer.loadFromFile(filename))
	{
		throw std::invalid_argument("Couldn't open sound file.");
	}

	this->sounds_.insert(std::pair<SOUND, sf::Sound>(sound_key, new_buffer));
}

