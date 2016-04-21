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
                switch (getColor(Point(x,y)))
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
