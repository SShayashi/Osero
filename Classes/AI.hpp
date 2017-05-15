//
//  AI.hpp
//  OseroConsole
//
//  Created by 林　真史 on 2016/04/21.
//  Copyright © 2016年 林　真史. All rights reserved.
//

#ifndef AI_hpp
#define AI_hpp

#include <stdio.h>
#include "Board.hpp"
#include "Evaluator.hpp"
#include "MidEvaluator.hpp"
using namespace Reversi;
class AI
{
public:
    AI(){
        presearch_depth = 2;
        normal_depth    = 5;
        wld_depth       = 15;
        perfect_depth   = 13;
    }
    
    unsigned presearch_depth;
    unsigned normal_depth;
    unsigned wld_depth;
    unsigned perfect_depth;
    
    virtual void move(Board&) = 0;
};

class AlphaBetaAI : public AI
{
public:
    AlphaBetaAI();
    void move(Board& board);
    int evaluate(const Board& board);
    void sort(Board& board, std::vector<Reversi::Point>&, int limit);
    int alphabeta(Board& board, int limit, int alpha, int beta);
protected:
    Evaluator* Eval;
};

class Move :public Reversi::Point
{
public:
    int eval;
    Move() :Point(0,0),eval(0){}
    Move(int x, int y, int e) : Point(x, y), eval(e) {}
};

class MoveGreater
{
public:
    bool operator() (const Move& lhs, const Move& rhs)
    {return (lhs.eval > rhs.eval);}
};



#endif /* AI_hpp */
