#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP
#include <iostream>
#include <SFML/Audio.hpp>
#include <string>
#include <map>

class Korek_Sound
{
public:
    Korek_Sound();
    Korek_Sound(const std::string&);
    virtual ~Korek_Sound();

    void play();
    void setSound(const std::string& filename);
private:
    sf::Sound sound;
    sf::SoundBuffer soundBuffer;
};

class SoundManager
{
    public:
        SoundManager();
        virtual ~SoundManager();

        void loadSound(const std::string& name,const std::string &filename);
        Korek_Sound getRef(const std::string& name);
    protected:

    private:
        std::map<std::string,Korek_Sound> k_sounds;

};


#endif // SOUNDMANAGER_HPP
