//
//  BoardTest.cpp
//  OseroConsole
//
//  Created by 林　真史 on 2016/04/21.
//  Copyright © 2016年 林　真史. All rights reserved.
//

#include <stdio.h>
#include "Board.hpp"
#include <iostream>

using namespace::std;
using namespace Reversi;
class ConsoleBoard : public Board
{
public:
    void print()
    {
        cout << "  abcdefgh " << endl;
        for(int y=1; y<=8; y++)
        {
            cout << " " << y;
            for(int x=1; x<=8; x++)
            {
                switch(getColor(Point(x, y)))
                {
                    case BLACK:
                        cout << "●";
                        break;
                    case WHITE:
                        cout << "○";
                        break;
                    default:
                        cout << "□";
                        break;
                }
            }
            cout << endl;
        }
    }
};

ostream& operator<<(ostream& os, const Point& p)
{
    string s = p;
    os << s;
    return os;
}
//
//int main()
//{
//    ConsoleBoard board;
//    
//    while(true)
//    {
//        board.print();
//        cout << "黒石" << board.countDisc(BLACK) << " ";
//        cout << "白石" << board.countDisc(WHITE) << " ";
//        cout << "空マス" << board.countDisc(EMPTY) << endl << endl;
//        
//        
//        cout << "手を入力してください: ";
//        Point p;
//        
//        string in;
//        cin >> in;
//        
//        if(in == "p")
//        {
//            // パス
//            if(!board.pass())
//                cerr << "パスできません" << endl;
//            
//            continue;
//        }
//        
//        if(in == "u")
//        {
//            // undo
//            board.undo();
//            continue;
//        }
//        
//        try
//        {
//            
//            Point parse(in);
//            p = parse;
//        }
//        catch(invalid_argument e)
//        {
//            cerr << "リバーシ形式の手を入力してください" << endl;
//            continue;
//        }
//        
//        if(board.move(p) == false)
//        {
//            cerr << "そこには置けません！" << endl;
//            continue;
//        }
//        
//        if(board.isGameOver())
//        {
//            cout << "----------------ゲーム終了----------------" << endl;
//            return 0;
//        }
//    }
//    
//    return 0;
//}


