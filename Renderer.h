#pragma once

#include "Game.h"

class Game;

class Renderer{
public:
    virtual void render(const Game&) const=0;

    virtual ~Renderer(){}
};

class TextRender:public Renderer{
public:
    TextRender(){};

    //TextRender(std::streambuf& out);
    
    //std::ostream& setOutputStream(std::ostream&);

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