//
//  Board.h
//  OseroConsole
//
//  Created by 林　真史 on 2016/04/19.
//  Copyright © 2016年 林　真史. All rights reserved.
//

#ifndef Board_h
#define Board_h

#include "Reversi.h"
#include <vector>

class Board
{
public:
    Board();
    void init();
    bool move(const Reversi::Point& point);
    bool pass();
    bool undo();
    bool isGameOver() const;
    
    //石の数を数える
    unsigned countDisc(Color color) const
    {
        return Discs[color];
    }
    
    //pointで指定された位置の色を返す
    Color getColor(const Reversi::Point& p) const
    {
        return RawBoard[p.x][p.y];
    }
    
    //石を打てる座標が並んだvectorを返す
    const std::vector<Reversi::Point>& getMovablePos() const
    {
        return MovablePos[Turns];
    }
    
    //直前の手で打った石と裏返した石が並んだvectorを返す
    std::vector<Disc> getUpdate() const
    {
        if(UpdateLog.empty()) return std::vector<Disc>();
        else return UpdateLog.back();
    }
    
    //現在の手番を返す
    Color getCurrentColor() const
    {
        return CurrentColor;
    }
    
    //現在の手数を返す
    unsigned getTurns() const
    {
        return Turns;
    }
    
    
private:

    static const unsigned NONE        =   0;
    static const unsigned UPPER       =   1;
    static const unsigned UPPER_LEFT  =   2;
    static const unsigned LEFT        =   4;
    static const unsigned LOWER_LEFT  =   8;
    static const unsigned LOWER       =  16;
    static const unsigned LOWER_RIGHT =  32;
    static const unsigned RIGHT       =  64;
    static const unsigned UPPER_RIGHT = 128;
    
    
    Color RawBoard[BOARD_SIZE+2][BOARD_SIZE+2];
    unsigned Turns;
    Color CurrentColor;
    
    std::vector<std::vector<Disc> > UpdateLog;
    
    std::vector<Reversi::Point> MovablePos[MAX_TURNS+1];
    unsigned MovableDir[MAX_TURNS+1][BOARD_SIZE+2][BOARD_SIZE+2];
    unsigned Liberty[BOARD_SIZE+2][BOARD_SIZE+2];
    
    ColorStorage<unsigned> Discs;

    
//    unsigned Liberty[BOARD_SIZE+2][BOARD_SIZE+2];
    void flipDiscs(const Reversi::Point& point);
    unsigned checkMobility(const Disc& disc) const;
    void initMovable();
    
    
};


#endif /* Board_h */
