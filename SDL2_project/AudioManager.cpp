#include "AudioManager.h"

AudioManager* AudioManager::sInstance = nullptr;

AudioManager* AudioManager::Instance()
{
	if (sInstance == nullptr)
	{
		sInstance = new AudioManager();
	}
	return sInstance;
}

void AudioManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

AudioManager::AudioManager()
{
	mAssetManager = AssetManager::Instance();

	//Initialize the SDL_mixer using 44.1 khz and 2 channels (change if needed) and handle initialization errors
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		printf("Mixer Initialization Error: %s\n", Mix_GetError());
		Logger::Log(Mix_GetError(), Logger::RemovePathFromFile(__FILE__), __LINE__);
	}
}

AudioManager::~AudioManager()
{
	mAssetManager = nullptr;
	Mix_Quit();
}

void AudioManager::PlayMusic(std::string fileName, int loops)
{
	Mix_PlayMusic(mAssetManager->GetMusic(fileName), loops);
}

void AudioManager::PauseMusic()
{
	if (Mix_PlayingMusic() != 0)
	{
		Mix_PauseMusic();
	}
}

void AudioManager::ResumeMusic()
{
	if (Mix_PausedMusic() != 0)
	{
		Mix_ResumeMusic();
	}
}

void AudioManager::PlaySFX(std::string fileName, int loops, int channel)
{
	Mix_PlayChannel(channel, mAssetManager->GetSFX(fileName), loops);
}