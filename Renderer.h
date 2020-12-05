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
    std::streambuf* current_stream_buf=std::cout.rdbuf();///<This is the current streambuffer.
public:
    /// This is the default constructor for the class.
    TextRender(){};
    /// This is a constructor for the class.
    template<typename T>
    TextRender(T);
    /// This function is for setting the output stream
    template<typename T>
    void setOutputStream(T);

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
    HeroTextRender(){};
    /// This is a constructor for the class.
    template<class T>
    HeroTextRender(T);
    /// This function is for the actual rendering.
    void render(const Game&) const;
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
    ObserverTextRender(){};
     /// This is a constructor for the class.
    template<typename T>
    ObserverTextRender(T);
    /// This function is for the actual rendering.
    void render(const Game&) const;
};