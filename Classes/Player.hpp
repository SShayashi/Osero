//
//  Player.hpp
//  Osero
//
//  Created by 林　真史 on 2016/04/24.
//
//

#ifndef Player_h
#define Player_h

#include "AI.hpp"
#include "cocos2d.h"

using namespace std;
using namespace Reversi;

class Player
{
public:
    virtual void onTurn(Board& board)=0;
    virtual void onTurn(Board& board,Reversi::Point p)=0;
};

class UndoException
{
    
};

class ExitException
{
    
};

class GameOverException
{
    
};

class HumanPlayer : public Player,public cocos2d::Node
{
public:
    void onTurn(Board& board)
    {
        return ;
    }
    void onTurn(Board& board,Reversi::Point point)
    {
        if(board.getMovablePos().empty())
        {
            cout << "あなたはパスです." << endl;
            //イベント発信側
            auto event = cocos2d::EventCustom("human_pass");
            auto voice = cocos2d::Value("パスです");
            event.setUserData(&voice);
            getEventDispatcher()->dispatchEvent(&event);
            
            board.pass();
            return;
        }
        
        while (true) {
//
//            if(in == "U" || in == "u") throw UndoException();
//            if(in == "X" || in == "x") throw ExitException();
            
//            Reversi::Point p;
//            try {
//                p = Reversi::Point(in);
//            } catch (invalid_argument& e) {
//                cout << "正しい形式で入力してください" << endl;
//                continue;
//            }
            
            if(!board.move(point))
            {
                cout << "そこには置けません" << endl;
            }
            
            if(board.isGameOver()) throw GameOverException();
            
            break;
        }

    }
};


class AIPlayer :public Player
{
    AI* Ai;
    
public:
    
    
    
    AIPlayer():Ai(NULL)
    {
        Ai = new AlphaBetaAI();
    }
    
    ~AIPlayer()
    {
        delete Ai;
    }
    
    
    void onTurn(Board& board)
    {
        cout << "コンピュータが思考中";
        Ai->move(board);
        cout << "完了" << endl;
        if(board.isGameOver()) throw GameOverException();
    }
    
    void onTurn(Board& board,Reversi::Point p)
    {
        
    }
};



#endif /* Player_h */
