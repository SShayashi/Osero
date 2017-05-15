//
//  Board.cpp
//  OseroConsole
//
//  Created by 林　真史 on 2016/04/19.
//  Copyright © 2016年 林　真史. All rights reserved.
//

#include <stdio.h>
#include "Board.hpp"
#include <iostream>

//public method
using namespace Reversi;
Board::Board(){
    init();
}

/**
 * 開始直後の状態にする初期化メソッド
 *
 */
void Board::init()
{
    //全マスを空きマスへ
    for(int x=1; x <= BOARD_SIZE; x++)
    {
        for(int y=1; y <= BOARD_SIZE; y++)
        {
            RawBoard[x][y] = EMPTY;
        }
    }
    
    //壁の設定
    for(int y=0; y < BOARD_SIZE + 2; y++)
    {
        RawBoard[0][y] = WALL;
        RawBoard[BOARD_SIZE+1][y] = WALL;
    }
    
    for(int x=0; x < BOARD_SIZE + 2; x++)
    {
        RawBoard[x][0] = WALL;
        RawBoard[x][BOARD_SIZE+1] = WALL;
    }
    
    
    //初期配置
    RawBoard[4][4] = BLACK;
    RawBoard[5][5] = BLACK;
    RawBoard[4][5] = WHITE;
    RawBoard[5][4] = WHITE;
    
    
    //石数の初期設定
    Discs[BLACK] = 2;
    Discs[WHITE] = 2;
    Discs[EMPTY] = BOARD_SIZE*BOARD_SIZE - 4;
    
    Turns = 0; //手数は0から
    CurrentColor = BLACK; //先手は黒
    
    //ログを全て削除
    UpdateLog.clear();
    
    initMovable();
}


/**
 * pointで指定した位置に石を打つ
 * 処理が成功したらtrue,失敗したらfalseが帰ってくる
 *
 */
bool Board::move(const Point &point)
{
    
    //石が置けるかどうかを判定
    if(point.x < 0 || point.x > BOARD_SIZE) return false;
    if(point.y < 0 || point.y > BOARD_SIZE) return false;
    if(MovableDir[Turns][point.x][point.y] == NONE) return false;
    
    flipDiscs(point);
    
    Turns++;
    CurrentColor = -CurrentColor;
    
    initMovable();
    
    return true;
}

/**
 * MovablePos[Turns]とMobableDir[Turns]を計算する
 *
 */
void Board::initMovable()
{
    Disc disc(0,0,CurrentColor);
    
    int dir;
    
    MovablePos[Turns].clear();
    
    for(int x=1 ; x<=BOARD_SIZE;x++)
    {
        disc.x = x;
        for (int y =1; y<=BOARD_SIZE; y++)
        {
            disc.y = y;
            dir = checkMobility(disc);
            if(dir != NONE)
            {
                MovablePos[Turns].push_back(disc);
            }
            MovableDir[Turns][x][y] = dir;
        }
    }
}

/**
 * ゲームが終了していればtreuを、終了していなければfalseを返す
 *
 */
bool Board::isGameOver()const
{
    if(Turns == MAX_TURNS) return  true;
    //打てる手があるならゲーム終了でない
    if(MovablePos[Turns].size() != 0) return false;
    
    
    //逆の手番も考える
    Disc disc;
    disc.color = -CurrentColor;
    for (int x=1; x<=BOARD_SIZE; x++)
    {
        disc.x = x;
        for(int y=1; y<=BOARD_SIZE; y++)
        {
            disc.y = y;
            //置ける箇所が１つでもアレばゲーム終了でない
            if(checkMobility(disc) != NONE) return false;
        }
    }
    return true;
}

/**
 * 直前の一手に元に戻す。成功するとtureが帰る。元に戻せない場合、falseが帰る
 *
 */
bool Board::undo()
{
    //ゲーム開始次点はもうもどれない
    if(Turns == 0) return false;
    
    CurrentColor = -CurrentColor;
    
    const std::vector<Disc>& update = UpdateLog.back();
    
    //前回がパスかどうかで場合分けする
    
    //前回がパス
    if(update.empty())
    {
        MovablePos[Turns].clear();
        for(unsigned x=1; x<update.size(); x++)
        {
            for (unsigned y=1 ; y<=BOARD_SIZE ; y++)
            {
                MovableDir[Turns][x][y] =NONE;
            }
        }
    }
    else //前回がパスでない
    {
        Turns--;
        
        //一つ前にオセロを取り除く
        RawBoard[update[0].x][update[0].y] = EMPTY;
        //裏返していたオセロを元に戻していく
        for(unsigned i=1; i<update.size(); i++)
        {
            RawBoard[update[i].x][update[i].y] =-CurrentColor;
        }
        
        unsigned discdiff = update.size();
        Discs[CurrentColor] -=discdiff;
        Discs[-CurrentColor] += discdiff -1;
        Discs[EMPTY]++;
    }
    
    UpdateLog.pop_back();
    
    return true;
}

/**
 * パスできる場合はtrueが出来ない場合はfalseが帰るメソッド
 *
 */
bool Board::pass()
{
    if(MovablePos[Turns].size() != 0) return false;
    
    if(isGameOver()) return false;
    
    CurrentColor = -CurrentColor;
    
    UpdateLog.push_back(std::vector<Disc>());
    initMovable();
    
    return true;
}

//private method

/**
 * pointで指定された位置に石を打ち込み、挟み込める全ての石を裏返す。
 * [打った石]と「裏返した石」をUpdateLogに挿入する
 *
 */
void Board::flipDiscs(const Point &point)
{
    int x,y;
    Disc operation(point.x, point.y, CurrentColor);
    
    int dir = MovableDir[Turns][point.x][point.y];
    
    std::vector<Disc> update;
    
    RawBoard[point.x][point.y] = CurrentColor;
    update.push_back(operation);
    
    //上の石を全て裏返していく
    if (dir & UPPER) {
        y = point.y;
        operation.x = point.x;
        
        while (RawBoard[point.x][--y] != CurrentColor)
        {
            RawBoard[point.x][y] = CurrentColor;
            operation.y = y;
            update.push_back(operation);
        }
    }
    
    //下
    if(dir & LOWER)
    {
        y = point.y;
        operation.x = point.x;
        while(RawBoard[point.x][++y] == -CurrentColor)
        {
            RawBoard[point.x][y] = CurrentColor;
            operation.y = y;
            update.push_back(operation);
        }
    }
    
    // 右
    if(dir & LEFT)
    {
        x = point.x;
        operation.y = point.y;
        while(RawBoard[--x][point.y] == -CurrentColor)
        {
            RawBoard[x][point.y] = CurrentColor;
            operation.x = x;
            update.push_back(operation);
        }
    }
    
    // 左
    if(dir & RIGHT)
    {
        x = point.x;
        operation.y = point.y;
        while(RawBoard[++x][point.y] == -CurrentColor)
        {
            RawBoard[x][point.y] = CurrentColor;
            operation.x = x;
            update.push_back(operation);
        }
    }
    
    // 右上
    if(dir & UPPER_RIGHT)
    {
        x = point.x;
        y = point.y;
        while(RawBoard[++x][--y] == -CurrentColor)
        {
            RawBoard[x][y] = CurrentColor;
            operation.x = x;
            operation.y = y;
            update.push_back(operation);
        }
    }
    
    // 左上
    if(dir & UPPER_LEFT)
    {
        x = point.x;
        y = point.y;
        while(RawBoard[--x][--y] == -CurrentColor)
        {
            RawBoard[x][y] = CurrentColor;
            operation.x = x;
            operation.y = y;
            update.push_back(operation);
        }
    }
    
    // 右下
    if(dir & LOWER_LEFT)
    {
        x = point.x;
        y = point.y;
        while(RawBoard[--x][++y] == -CurrentColor)
        {
            RawBoard[x][y] = CurrentColor;
            operation.x = x;
            operation.y = y;
            update.push_back(operation);
        }
    }
    
    // 左下
    if(dir & LOWER_RIGHT)
    {
        x = point.x;
        y = point.y;
        while(RawBoard[++x][++y] == -CurrentColor)
        {
            RawBoard[x][y] = CurrentColor;
            operation.x = x;
            operation.y = y;
            update.push_back(operation);
        }
    }
    
    x = point.x;
    y = point.y;
    // 石の数を更新
    
    unsigned discdiff = update.size();
    
    Discs[CurrentColor]  += discdiff;
    Discs[-CurrentColor] -= discdiff -1;
    Discs[EMPTY]--;
    
    UpdateLog.push_back(update);
}

/**
 * 置いた石が周りのどの石を裏返せるかの判定
 * @param Disc
 * @return 方向 NONEなら置けない
 */
unsigned int Board::checkMobility(const Disc &disc)const
{
    
    if(RawBoard[disc.x][disc.y] != EMPTY)return  NONE;
    
    int x,y;
    unsigned dir =NONE;
    
    //上の判定
    if(RawBoard[disc.x][disc.y-1] == -disc.color)
    {
        x = disc.x;
        y = disc.y-2;
        //持っている石の色の反対がどれだけ上に続いているかを判定
        while (RawBoard[x][y] == -disc.color) {y--;}
        if(RawBoard[x][y] == disc.color) dir |= UPPER;
    }
    
    // 下
    if(RawBoard[disc.x][disc.y+1] == -disc.color)
    {
        x = disc.x; y = disc.y+2;
        while(RawBoard[x][y] == -disc.color) { y++; }
        if(RawBoard[x][y] == disc.color) dir |= LOWER;
    }
    
    // 左
    if(RawBoard[disc.x-1][disc.y] == -disc.color)
    {
        x = disc.x-2; y = disc.y;
        while(RawBoard[x][y] == -disc.color) { x--; }
        if(RawBoard[x][y] == disc.color) dir |= LEFT;
    }
    
    // 右
    if(RawBoard[disc.x+1][disc.y] == -disc.color)
    {
        x = disc.x+2; y = disc.y;
        while(RawBoard[x][y] == -disc.color) { x++; }
        if(RawBoard[x][y] == disc.color) dir |= RIGHT;
    }
    
    
    // 右上
    if(RawBoard[disc.x+1][disc.y-1] == -disc.color)
    {
        x = disc.x+2; y = disc.y-2;
        while(RawBoard[x][y] == -disc.color) { x++; y--; }
        if(RawBoard[x][y] == disc.color) dir |= UPPER_RIGHT;
    }
    
    // 左上
    if(RawBoard[disc.x-1][disc.y-1] == -disc.color)
    {
        x = disc.x-2; y = disc.y-2;
        while(RawBoard[x][y] == -disc.color) { x--; y--; }
        if(RawBoard[x][y] == disc.color) dir |= UPPER_LEFT;
    }
    
    //　左下
    if(RawBoard[disc.x-1][disc.y+1] == -disc.color)
    {
        x = disc.x-2; y = disc.y+2;
        while(RawBoard[x][y] == -disc.color) { x--; y++; }
        if(RawBoard[x][y] == disc.color) dir |= LOWER_LEFT;
    }
    
    // 右下
    if(RawBoard[disc.x+1][disc.y+1] == -disc.color)
    {
        x = disc.x+2; y = disc.y+2;
        while(RawBoard[x][y] == -disc.color) { x++; y++; }
        if(RawBoard[x][y] == disc.color) dir |= LOWER_RIGHT;
    }
    
    
    return dir;

}
