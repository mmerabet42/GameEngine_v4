#include "Sound.h"

FMOD::System * dn::Sound::_fmodSystem = nullptr;
FMOD::Channel * dn::Sound::_fmodChannel = nullptr;

dn::Sound::Sound(const std::string & p_path)
	: _path(p_path)
{
	if (!dn::Sound::_fmodSystem)
	{
		FMOD::System_Create(&dn::Sound::_fmodSystem);
		dn::Sound::_fmodSystem->init(512, FMOD_INIT_NORMAL, nullptr);
	}
	this->_resultCreation = dn::Sound::_fmodSystem->createSound(_path.c_str(), FMOD_LOOP_OFF, nullptr, &this->_fmodSound);
}

std::string dn::Sound::path() const
{
	return this->_path;
}

bool dn::Sound::IsValid() const
{
	return this->_resultCreation == FMOD_OK;
}

void dn::Sound::Play()
{
	if (dn::Sound::_fmodSystem)
		dn::Sound::_fmodSystem->playSound(this->_fmodSound, nullptr, false, &dn::Sound::_fmodChannel);
}