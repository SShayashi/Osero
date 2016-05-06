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
    auto_ptr<Player> player[2];
    int current_player;

    //Model
    Board board;
    //View
    BoardView *BoardLayer {};
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    int onPlay();
    CREATE_FUNC(GameScene);
};


class ConsoleBoard : public Board
{
public:
    void print()
    {
        cout << "  abcdefgh " << endl;
        for(int y=1 ; y<=8 ; y++)
        {
            cout << "  " << y;
            for(int x=1 ; x<=8; x++)
            {
                switch (getColor(Reversi::Point(x,y)))
                {
                    case BLACK:
                        cout << "●";
                        break;
                    case WHITE:
                        cout << "○";

                    default:
                        cout << "  ";
                        break;
                }
            }
            cout << endl;
        }
            
    }
};


#endif /* GameScene_hpp */
