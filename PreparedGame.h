#pragma once
#include "Game.h"
#include "JSON.h"
#include "MarkedMap.h"
#include "Renderer.h"

class PreparedGame: public Game,MarkedMap{
private:
    JSON scenario;
    void init();
public:
    PreparedGame(const std::string&);

    void registerRenderer(Renderer* rend){
		renderers.push_back(rend);
	}

    void run();

    ~PreparedGame(){
        for(auto renderer:renderers){
            delete renderer;
        }
    }
};