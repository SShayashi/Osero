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

#include "TitleScene.hpp"

#include <iostream>

#define ORIGINAL_TILE_WIDTH 128

#define BOARD_OFFSET 20
#define BOARD_POSITION_X 20
#define BOARD_POSITION_Y 300
#define BOARD_TILE_WIDTH 75
using namespace cocos2d;

BoardView::BoardView()
{
    _tableNode     = nullptr;
    _renderTexture = nullptr;
    _boardLayer    = nullptr;
    _whiteDiscNumLabel = nullptr;
    _blackDiscNumLabel = nullptr;
}
BoardView::~BoardView()
{
    CC_SAFE_RELEASE_NULL(_tableNode);
    CC_SAFE_RELEASE_NULL(_renderTexture);
    CC_SAFE_RELEASE_NULL(_boardLayer);
    CC_SAFE_RELEASE_NULL(_whiteDiscNumLabel);
    CC_SAFE_RELEASE_NULL(_blackDiscNumLabel);
}

bool BoardView::init(){
    if ( !Layer::init() )
    {
        return false;
    }
    winSize = Director::getInstance()->getVisibleSize();
    //背景
    // titleLayerの読み込み
    auto boardLayer = CSLoader::getInstance()->createNode("BoardLayer.csb");
    this->setBoardLayer(boardLayer);
    this->addChild(_boardLayer);
    
    //レンダリング用のテクスチャの初期化
    auto renderTexture = RenderTexture::create(winSize.width, winSize.height);
    renderTexture->setClearColor(cocos2d::Color4F(0,0,1,0.5));
    renderTexture->setPosition(Vec2(winSize.width/2, winSize.height/2));
    this->setRenderTexture(renderTexture);
    this->addChild(_renderTexture);

    auto homeBtn = boardLayer->getChildByName<ui::Button*>("home");
    auto undoBtn  = boardLayer->getChildByName<ui::Button*>("undo");
    auto whiteDiscNumLabel = boardLayer->getChildByName<ui::Text*>("white_disc_num");
    auto blackDiscNumLabel = boardLayer->getChildByName<ui::Text*>("black_disc_num");
    auto tableNode = boardLayer->getChildByName("table");
    
    
    homeBtn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto title = Title::createScene();
            auto transition = TransitionCrossFade::create(0.5, title);
            Director::getInstance()->replaceScene(transition);
            
        }
    });
    
    
    this->setBlackDiscNumLabel(blackDiscNumLabel);
    this->setWhiteDiscNumLabel(whiteDiscNumLabel);
    
    //位置をタイル一枚分下にずらす
    tableNode->setPosition(tableNode->getPosition() - Vec2(BOARD_TILE_WIDTH,BOARD_TILE_WIDTH));
    setTableNode(tableNode);
    


    return true;
}

/** Modelを参照して画面へ描画
 *
 */
void BoardView::initUpdate(const Board &board){
    
    //枚数更新
    _blackDiscNumLabel->setString(std::to_string(board.countDisc(BLACK)));
    _whiteDiscNumLabel->setString(std::to_string(board.countDisc(WHITE)));
    
    if(board.getCurrentColor() == -1)
        _boardLayer->getChildByName<ui::Text*>("turn")->setString("白の\nターン");
    else
        _boardLayer->getChildByName<ui::Text*>("turn")->setString("黒の\nターン");
    
    _tiles.clear();
    //8*8のマスを作成
    for(int y = 1; y <= 8; y++) {
        for(int x = 1; x <= 8; x++){
            _renderTexture->begin();
            
            auto tile {BoardTile::create()};
            auto pos = BoardTile::convertToStageSpace(Vec2(x,y));
            tile->setPosition(_tableNode->getPosition() + pos);
            tile->setBoardPoint(Reversi::Point(x,y));
            tile->setColor(board.getColor(Reversi::Point(x,y)));
            
            _tiles.pushBack(tile);
            tile->visit();
            _renderTexture->end();
            tile->retain();

        }
    }
    return ;
}

void BoardView::update(const Board &board)
{
    
    std::cout << "現在のターンは(0が白　1が黒)";
    std::cout << board.getCurrentColor() << std::endl;
    
    std::cout << "  abcdefgh " << std::endl;
    for(int y=8; y>=1; y--)
    {
        std::cout << " " << y;
        for(int x=1; x<=8; x++)
        {
            switch(board.getColor(Reversi::Point(x, y)))
            {
                case BLACK:
                    std::cout << "●";
                    break;
                case WHITE:
                    std::cout << "○";
                    break;
                default:
                    std::cout << "□";
                    break;
            }
        }
        std::cout << std::endl;
    }
    
    std::cout << "黒石" << board.countDisc(BLACK) << " ";
    std::cout << "白石" << board.countDisc(WHITE) << " ";
    std::cout << "空マス" << board.countDisc(EMPTY) << std::endl << std::endl;
    
    _blackDiscNumLabel->setString(std::to_string(board.countDisc(BLACK)));
    _whiteDiscNumLabel->setString(std::to_string(board.countDisc(WHITE)));

    if(board.getCurrentColor() == -1)
        _boardLayer->getChildByName<ui::Text*>("turn")->setString("白の\nターン");
    else
        _boardLayer->getChildByName<ui::Text*>("turn")->setString("黒の\nターン");
    
    //8*8のマスを作成
    for(int y = 1; y <= 8; y++) {
        for(int x = 1; x <= 8; x++){
            auto n =(y-1)*8 + x-1;
            //色の変更がない場合はスルー
            if (_tiles.at(n)->getColor() == board.getColor(Reversi::Point(x,y)))
                continue;
            
            _renderTexture->begin();
            auto tile {BoardTile::create()};
            auto pos = BoardTile::convertToStageSpace(Vec2(x,y));
            tile->setPosition(_tableNode->getPosition() + pos);
            tile->setBoardPoint(Reversi::Point(x,y));
            tile->setColor(board.getColor(Reversi::Point(x,y)));
//            _tableNode->addChild(tile);
            _tiles.replace(n,tile);
            tile->visit();
            _renderTexture->end();
            tile->retain();
            
        }
    }
    

    return ;
}
