#pragma once
#include "Game.h"
#include "Renderer.h"

class Game;
/**
 * \class SVGRenderer
 * 
 * \brief This is the abstract class for SVGrendering.
 *  
 * 
 * 
*/
class SVGRenderer:public Renderer{
protected:
    
    const std::string filename;///< This is the destination filename.

public:
    /// This is the constructor for the class.
    explicit SVGRenderer(const std::string& file):filename(file){}
    /// This is a pure virtual function for rendering.
    void render(const Game&) const override{}
};
/**
 * \class CharacterSVGRenderer
 * 
 * \brief This is the abstract class for rendering.
 *  
 * This class is derived from the SVGRenderer class.
 * 
*/
class CharacterSVGRenderer:public SVGRenderer{

public:
    /// This is the constructor for the class.
    explicit CharacterSVGRenderer(const std::string& file):SVGRenderer(file){}
    /// This function is for SVG rendering.
    void render(const Game&)const override;
};
/**
 * \class ObserverSVGRenderer
 * 
 * \brief This is the abstract class for rendering.
 *  
 * This class is derived from the SVGRenderer class.
 * 
*/
class ObserverSVGRenderer:public SVGRenderer{

public:
    /// This is the constructor for the class.
    explicit ObserverSVGRenderer(const std::string& file):SVGRenderer(file){}
    /// This function is for SVG rendering.
    void render(const Game&)const override;
};