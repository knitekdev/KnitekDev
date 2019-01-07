#include "SoundManager.hpp"
Korek_Sound::Korek_Sound()
{
}
Korek_Sound::Korek_Sound(const std::string& filename)
{
    setSound(filename);
}
Korek_Sound::~Korek_Sound()
{
}

void Korek_Sound::setSound(const std::string& filename)
{
    if(soundBuffer.loadFromFile(filename))
        std::cout<<"Loaded: "<<filename<<std::endl;
    else
        std::cout<<"Error, can't load: "<<filename<<std::endl;
    sound.play();
}
void Korek_Sound::play()
{
    sound.setBuffer(soundBuffer);
    sound.setVolume(10.f);
    sound.play();
}

SoundManager::SoundManager()
{
    //ctor
}
SoundManager::~SoundManager()
{
    //dtor
}

void SoundManager::loadSound(const std::string& name, const std::string& filename)
{
    this->k_sounds[name] = Korek_Sound(filename);
}

Korek_Sound SoundManager::getRef(const std::string& name)
{
    return this->k_sounds.at(name);
}
