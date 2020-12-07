#pragma once
#include "Game.h"
#include "JSON.h"
#include "MarkedMap.h"
#include "Renderer.h"
#include "SVGRenderer.h"

/**
 * \class PreparedGame
 * 
 * \brief This is the class for the PreparedGame.
 *  
 * 
 * This class is derived from the Game and MarkedMap class. 
*/

class PreparedGame: public Game,MarkedMap{
private:
    ///This function initializes the game
    void init();
public:
    ///This is the constructor for the class.
    PreparedGame(const std::string&);
    ///This function registers renderers.
    void registerRenderer(Renderer* rend){
		renderers.push_back(rend);
	}
    ///This is the gameloop.
    void run();
    ///This is the destructor for the class.
    ~PreparedGame(){
        for(auto renderer:renderers){
            delete renderer;
        }
    }
};