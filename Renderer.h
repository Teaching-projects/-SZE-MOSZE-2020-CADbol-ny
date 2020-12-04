#pragma once

#include "Game.h"

class Game;

class Renderer{
public:
    virtual void render(const Game&) const=0;
};

class TextRender:public Renderer{
public:
    
    TextRender(){};

    TextRender(std::ostream&);
    
    void setOutputStream(std::ostream&);

};

class HeroTextRender:public TextRender{
public:
    HeroTextRender(){};

    void render(const Game&) const;
};

class ObserverTextRender:public TextRender{
public:
    ObserverTextRender(){};

    void render(const Game&) const;
};