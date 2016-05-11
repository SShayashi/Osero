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
    
    //レンダリング用のテクスチャの初期化
    auto renderTexture = RenderTexture::create(winSize.width, winSize.height);
    renderTexture->setClearColor(cocos2d::Color4F(0,0,1,0.5));
    renderTexture->setPosition(Vec2(winSize.width/2, winSize.height/2));
    this->setRenderTexture(renderTexture);
    this->addChild(_renderTexture);

    auto homeBtn = boardLayer->getChildByName<ui::Button*>("home");
    auto undoBtn  = boardLayer->getChildByName<ui::Button*>("undo");
    auto tableNode = boardLayer->getChildByName("table");
    //位置をタイル一枚分下にずらす
    _tableNode = tableNode;
    _tableNode->setPosition(_tableNode->getPosition() - Vec2(BOARD_TILE_WIDTH,BOARD_TILE_WIDTH));
    


    return true;
}

/** Modelを参照して画面へ描画
 *
 */
void BoardView::update(const Board &board){
    
    _renderTexture->begin();
    //8*8のマスを作成
    for(int y = 1; y <= 8; y++) {
        for(int x = 1; x <= 8; x++){
            auto tile {BoardTile::create()};
            auto pos = BoardTile::convertToStageSpace(Vec2(x,y));
            tile->setPosition(pos);
            tile->setBoardPoint(Reversi::Point(x,y));
            tile->setColor(board.getColor(Reversi::Point(x,y)));
            _tableNode->addChild(tile);
            
            _tiles.pushBack(tile);
            tile->visit();
            tile->retain();
        }
    }
    
    _renderTexture->end();
    return ;
}
