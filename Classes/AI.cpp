//
//  AI.cpp
//  OseroConsole
//
//  Created by 林　真史 on 2016/04/21.
//  Copyright © 2016年 林　真史. All rights reserved.
//

#include "AI.hpp"

AlphaBetaAI::AlphaBetaAI() : AI()
{
}

int AlphaBetaAI::evaluate(const Board &board)
{
    int evaluatArray[9][9] = {
        {1,  1,  1,  1,  1,  1,  1,  1,  1},
        {1,100,-50, 10,  0,  0, 10,-50,100},
        {1,-50,-70, -5,-10,-10, -5,-70,-50},
        {1, 10,  0,-10, -5, -5,-10,  0, 10},
        {1,  0,-10, -5,  0,  0, -5,-10,  0},
        {1,  0,-10, -5,  0,  0, -5,-10,  0},
        {1, 10,  0,-10, -5, -5,-10,  0, 10},
        {1,-50,-70, -5,-10,-10, -5,-70,-50},
        {1,100,-50, 10,  0,  0, 10,-50,100}
    };
    int eval = 0;
    for( int y = 1; y <= 8; y++)
        for(int x = 1 ; x <= 8; x++)
        {
            if(board.getColor(Point(x,y)) == EMPTY)
            {
                continue;
                
            }else if(board.getColor(Point(x,y)) == board.getCurrentColor())
                eval += evaluatArray[x][y];
            else
                eval -= evaluatArray[x][y];
                
            eval += board.getCurrentColor() * board.getColor(Point(x,y));
        }
    
    int discdiff = board.getCurrentColor() * (board.countDisc(BLACK) - board.countDisc(WHITE));
    
    return discdiff + eval;
}
void AlphaBetaAI::move(Board& board)
{
    std::vector<Point> movables = board.getMovablePos();
    if(movables.empty())
    {
        // 打てる箇所がなければパス
        board.pass();
        return;
    }
    
    if(movables.size() == 1)
    {
        //打てる箇所が1箇所なら探索は行わない
        board.move(movables[0]);
        return;
    }
    
    //とりあえずランダム
//    board.move(movables[std::rand() % movables.size()]);
    
    
    int limit;
//    Eval = new MidEvaluator();
    sort(board, movables, presearch_depth); // 事前に手を良さそうな順にソート
    if(MAX_TURNS - board.getTurns() <= wld_depth)
    {
//        delete Eval;
        limit = std::numeric_limits<int>::max();
//        if(MAX_TURNS - board.getTurns() <= perfect_depth)
//            Eval = new PerfectEvaluator();
//        else
//            Eval = new WLDEvaluator();
    }
    else
    {
        limit = normal_depth;
    }
    
    int eval, alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();
    Point p;
    for(unsigned i=0; i<movables.size(); i++)
    {
        board.move(movables[i]);
        eval = -alphabeta(board, limit-1, -beta, -alpha);
        board.undo();
        
        if(eval > alpha)
        {
            alpha = eval;
            p = movables[i];
        }
    }
    
//    delete Eval;
//    Eval = NULL;
    
    board.move(p);
}

void AlphaBetaAI::sort(Board& board, std::vector<Point>& movables, int limit)
{
    std::vector<Move> moves;
    
    for(unsigned i=0; i<movables.size(); i++)
    {
        int eval;
        
        board.move(movables[i]);
        eval = -alphabeta(board, limit-1, -INT_MAX, INT_MAX);
        board.undo();
        
        Move move(movables[i].x, movables[i].y, eval);
        moves.push_back(move);
    }
    
    //評価値の大きい順にソート
    std::stable_sort(moves.begin(), moves.end(), MoveGreater());
    
    //結果の書き戻し
    movables.clear();
    for(unsigned i=0; i<moves.size(); i++)
    {
        movables.push_back(moves[i]);
    }
    
    return;
}

int AlphaBetaAI::alphabeta(Board& board, int limit, int alpha, int beta)
{
    if(board.isGameOver() || limit == 0)
        return evaluate(board);
    
    int score;
    const std::vector<Point>& movables = board.getMovablePos();
    
    if(movables.empty())
    {
        board.pass();
        score = -alphabeta(board, limit, -beta, -alpha);
        board.undo();
        return score;
    }
    
    for(unsigned i=0; i<movables.size(); i++)
    {
        board.move(movables[i]);
        score = -alphabeta(board, limit-1, -beta, -alpha);
        board.undo();
        
        if(score >= beta) return score;
        
        alpha = std::max(alpha, score);
        
    }
    
    return alpha;
}

