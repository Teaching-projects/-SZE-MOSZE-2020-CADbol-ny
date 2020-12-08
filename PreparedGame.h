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

class PreparedGame:public Game,MarkedMap{
private:
    ///This function initializes the game
    void init();
public:
    ///This is the constructor for the class.
    explicit PreparedGame(const std::string&);
    ///This is the gameloop.
    void run() override;
    ///This is the destructor for the class.
    ~PreparedGame(){
        for(auto renderer:renderers){
            delete renderer;
        }
    }
};