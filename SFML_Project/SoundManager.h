#pragma once
#include <unordered_map>
#include <SFML/Audio.hpp>

enum class SOUND {
	PLAYER_WALKING
};

class SoundManager
{
private:
	std::unordered_map<SOUND, sf::Sound> sounds_;
	std::vector<sf::SoundBuffer> buffers_;
public:
	SoundManager();
	virtual ~SoundManager();
	void Add(const SOUND& sound_key, const std::string& filename);
	void Play(const SOUND& sound_key);
};

