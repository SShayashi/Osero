//
//  BoardView.cpp
//  Osero
//
//  Created by 林　真史 on 2016/04/24.
//
//
#include "BoardView.hpp"
#include "Reversi.h"
#include "Board.hpp"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GUIcomponents.hpp"

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
    // titleLayerの読み込み
    auto boardLayer = CSLoader::getInstance()->createNode("BoardLayer.csb");
    this->addChild(boardLayer);

    auto homeBtn = boardLayer->getChildByName<ui::Button*>("home");
    auto undoBtn  = boardLayer->getChildByName<ui::Button*>("undo");
    auto tableNode = boardLayer->getChildByName("table");
    _boardpos = tableNode->getPosition();


    return true;
}

/** Modelを参照して画面へ描画
 *
 */
void BoardView::update(const Board &board){
    
    //8*8のマスを作成
    for(int y = 1; y <= 8; y++) {
        for(int x = 1; x <= 8; x++){
            auto tile {BoardTile::create()};
            auto pos = BoardTile::convertToStageSpace(Vec2(x,y));
            tile->setPosition(_boardpos - tile->getContentSize()  + pos );
            this->addChild(tile);
            tile->setColor(board.getColor(Reversi::Point(x,y)));
            _tiles.pushBack(tile);
        }
    }
    return ;
}
