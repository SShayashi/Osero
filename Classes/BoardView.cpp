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
    winSize = Director::getInstance()->getVisibleSize();
    //背景
    auto background = Sprite::create("backpaper.jpg");
    background->setPosition(winSize/2);
    this->setBackGround(background);
    this->addChild(_background);
    
    //ボード定義
    this->setupBoard();

    return true;
}

/** テーブルへの最初の描画
 *
 */
void BoardView::setupBoard(){
    
    _tiles.clear();
    _discs.clear();
    //8*8のマスを作成
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++){
            auto tile {BoardTile::create()};
            tile->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
            tile->setContentSize(Size(BOARD_TILE_WIDTH, BOARD_TILE_WIDTH));
            tile->setPosition(BOARD_POSITION_X + BOARD_TILE_WIDTH*i,
                              BOARD_POSITION_Y + BOARD_TILE_WIDTH*j);

            
            Sprite* disc {Sprite::create("k.png")};
            disc->setPosition(tile->getContentSize()/2);
            tile->addChild(disc,1000);
            this->addChild(tile);
            _tiles.pushBack(tile);
//            _discs.pushBack(disc);
            
        }
    }
    return ;
}

void BoardView::update(Board &board){
    return ;
}