//
//  BoardView.cpp
//  Osero
//
//  Created by 林　真史 on 2016/04/24.
//
//
#include "BoardView.hpp"

#define ORIGINAL_TILE_WIDTH 128

#define BOARD_OFFSET 20
#define BOARD_POSITION_X 20
#define BOARD_POSITION_Y 300
#define BOARD_TILE_WIDTH 75
using namespace cocos2d;

bool BoardView::init(){
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->setupBoard();

    return true;
}

/** テーブルへの最初の
 *
 */
void BoardView::setupBoard(){
    
    Size winSize = Director::getInstance()->getVisibleSize();
    
    _tiles.clear();
    _discs.clear();
    //8*8のマスを作成
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++){
            Sprite* tile {Sprite::create("tile01.png")};
            tile->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
            tile->setContentSize(Size(BOARD_TILE_WIDTH, BOARD_TILE_WIDTH));
            tile->setPosition(BOARD_POSITION_X + BOARD_TILE_WIDTH*i,
                              BOARD_POSITION_Y + BOARD_TILE_WIDTH*j);

            this->addChild(tile);
            _tiles.pushBack(tile);
            
            Sprite* disc {Sprite::create("k.png")};
            disc->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            disc->setPosition(tile->getContentSize()/2);
            disc->setContentSize(Size(100,100));
            tile->addChild(disc,1000);
            _discs.pushBack(disc);
            
        }
    }
    
    
    return ;
}

void BoardView::reflectBoard(Board &board){
    return ;
}