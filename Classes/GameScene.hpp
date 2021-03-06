//
//  GameScene.hpp
//  Osero
//
//  Created by 林　真史 on 2016/04/21.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <iostream>
#include <string>
#include <memory>

#include <stdio.h>
#include "Board.hpp"
#include "Player.hpp"
#include "AI.hpp"
#include "BoardView.hpp"

using namespace std;

class GameScene : public cocos2d::Layer
{
private:
    unique_ptr<Player> player[2];
    int _current_player;
    int _gameoverFlag;
    Reversi::Point _touchPoint;
    //Model
    Board *_board;
    //View
    CC_SYNTHESIZE_RETAIN(BoardView*, _boardViewLayer, BoardViewLayer);
    
    GameScene();
    virtual ~GameScene();
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void update(float delta);
    
    int onPlay();
    int putDisc(Reversi::Point p);
    CREATE_FUNC(GameScene);
};
#endif /* GameScene_hpp */
