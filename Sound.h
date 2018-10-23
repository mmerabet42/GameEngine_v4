#pragma once

#include <FMOD/fmod.hpp>
#include <string>

namespace dn
{
	class Application;

	class Sound
	{
		friend class dn::Application;
	public:
		Sound(const std::string & p_path);

		std::string path() const;
		bool IsValid() const;

		void Play();
	private:

		FMOD_RESULT _resultCreation;

		std::string _path;
		FMOD::Sound * _fmodSound;

		static FMOD::System * _fmodSystem;
		static FMOD::Channel * _fmodChannel;
	};
}
