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

using namespace std;

class Player
{
public:
    virtual void onTurn(Board& board)=0;
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

class HumanPlayer : public Player
{
public:
    void onTurn(Board& board)
    {
        if(board.getMovablePos().empty())
        {
            cout << "あなたはパスです." << endl;
            board.pass();
            return;
        }
        
        while (true) {
            cout << "手を入力してください:";
            string in;
            cin >> in;
            
            if(in == "U" || in == "u") throw UndoException();
            if(in == "X" || in == "x") throw ExitException();
            
            Point p;
            try {
                p = Point(in);
            } catch (invalid_argument& e) {
                cout << "正しい形式で入力してください" << endl;
                continue;
            }
            
            if(!board.move(p))
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
};



#endif /* Player_h */
