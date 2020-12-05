#pragma once
#include "Game.h"

class Game;

class SVGRenderer{
protected:
    const std::string filename;

public:

    SVGRenderer(const std::string& file):filename(file){}

    virtual void render(const Game&) const=0;
};

class CharacterSVGRenderer:public SVGRenderer{

public:

    CharacterSVGRenderer(const std::string& file):SVGRenderer(file){}

    void render(const Game&)const;
};

class ObserverSVGRenderer:public SVGRenderer{

public:

    ObserverSVGRenderer(const std::string& file):SVGRenderer(file){}

    void render(const Game&)const;
};