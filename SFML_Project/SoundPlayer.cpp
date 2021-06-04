#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
{
}

SoundPlayer::~SoundPlayer()
{
}

void SoundPlayer::SoundThread(sf::SoundBuffer& buffer)
{
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();
}


void SoundPlayer::PlaySound(SoundManager& sound_manager, const SOUND& sound_key)
{
	//sf::Thread sound_thread(&SoundPlayer::PlaySound, sound_manager.GetBuffer(sound_key));
	//sound_thread.launch();
	SoundPlayer::SoundThread(sound_manager.GetBuffer(sound_key));
}
