//
//  GameScene.cpp
//  Osero
//
//  Created by 林　真史 on 2016/04/21.
//
//

#include "GameScene.hpp"
#include <iostream>
#include <string>
#include <memory>

//元main

int onPlay(){
    auto_ptr<Player> player[2];
    int current_player = 0;
    ConsoleBoard board;
    bool reverse = false;
    
    //先手・後手の設定
    if(reverse)
    {
        player[1].reset(new HumanPlayer());
        player[0].reset(new AIPlayer());
    }
    else
    {
        player[1].reset(new AIPlayer());
        player[0].reset(new HumanPlayer());

    }
    
    while (true) {
        board.print();
        
        try {
            player[current_player]->onTurn(board);
        } catch (UndoException& e)
        {
            do
            {
                board.undo();
                board.undo();
            }while (board.getMovablePos().empty());
            {
                continue;
            }
        }
        catch(ExitException& e)
        {
            return 0;
        }
        catch(GameOverException& e)
        {
            cout << "game finish " << endl;
            cout << "黒石" << board.countDisc(BLACK) << "  ";
            cout << "白石" << board.countDisc(WHITE) << endl;
            
            return 0;
        }
        
        //プレイヤーの交代
        current_player = ++current_player % 2;
    }
    
}