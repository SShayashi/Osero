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

class Player :public cocos2d::Ref
{
public:
    virtual void onTurn(Board& board)=0;
    virtual void onTurn(Board& board,Reversi::Point p)=0;
};

class UndoException
{
    
};

class NotMoveException
{
    
};

class ExitException
{
    
};

class GameOverException
{
    
};

class HumanPlayer : public Player
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
            board.pass();
            return;
        }

        if(!board.move(point))
        {
            cout << "そこには置けません" << endl;
            throw NotMoveException();
        }
        
        if(board.isGameOver()) throw GameOverException();
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
