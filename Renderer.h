#pragma once
#include <iostream>
#include "Game.h"

class Game;

/**
 * \class Renderer
 * 
 * \brief This is the abstract class for rendering.
 *  
 * 
 * 
*/
class Renderer{
public:
    /// This is a pure virtual function for rendering.
    virtual void render(const Game&) const=0;
    /// This is the destructor for the class.
    virtual ~Renderer(){}
};
/**
 * \class TextRender
 * 
 * \brief This is the class for the textrendering.
 *  
 * This class is derived from the Renderer class.
 * 
*/
class TextRender:public Renderer{
protected:
    std::ostream* output=&std::cout;
public:
    /// This is the default constructor for the class.
    TextRender(){}
    /// This is a constructor for the class.
    explicit TextRender(std::ostream&);
    /// This function is for setting the output stream
    void setOutputStream(std::ostream&);
};
/**
 * \class HeroTextRender
 * 
 * \brief This is the class for the textrendering with the hero's vision.
 *  
 * This class is derived from the TextRenderer class.
 * 
*/
class HeroTextRender:public TextRender{
public:
    /// This is the default constructor for the class.
    HeroTextRender(){}
    /// This is a constructor for the class.
    explicit HeroTextRender(std::ostream& out):TextRender(out) {}
    /// This function is for the actual rendering.
    void render(const Game&) const override;
};
/**
 * \class ObserverTextRender
 * 
 * \brief This is the class for the textrendering with the observer's vision.
 *  
 * This class is derived from the TextRenderer class.
 * 
*/
class ObserverTextRender:public TextRender{
public:
     /// This is the default constructor for the class.
    ObserverTextRender(){}
     /// This is a constructor for the class.
    explicit ObserverTextRender(std::ostream& out):TextRender(out) {}
    /// This function is for the actual rendering.
    void render(const Game&) const override;
};