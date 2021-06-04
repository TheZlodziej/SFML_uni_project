#pragma once
#include "SoundManager.h"

class SoundPlayer
{
private:
	static void SoundThread(sf::SoundBuffer& buffer);

public:
	SoundPlayer();
	virtual ~SoundPlayer();

	static void PlaySound(SoundManager& sound_manager, const SOUND& sound_key);
};

