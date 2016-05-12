//
//  GameScene.cpp
//  Osero
//
//  Created by 林　真史 on 2016/04/21.
//
//

#include "GameScene.hpp"
#include "Utility.hpp"
#include <iostream>
#include <string>
#include <memory>

GameScene::GameScene()
{
    _current_player = 0;
    _board          = nullptr;
    _boardViewLayer = nullptr;
    player[0]       = nullptr;
    player[1]       = nullptr;
    
    
}
GameScene::~GameScene()
{
    delete _board;
    CC_SAFE_RELEASE_NULL(_boardViewLayer);
    CC_SAFE_RELEASE_NULL(player[0]);
    CC_SAFE_RELEASE_NULL(player[1]);
}

//元main
cocos2d::Scene* GameScene::createScene()
{
    auto scene = cocos2d::Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //Modelの初期化
    _board = new Board();
    
    //先手・後手の設定
    if(Utility::getInstance()->getGameMode() == Utility::GAME_MODE::MULTI)
    {
        player[0].reset(new HumanPlayer());
        player[1].reset(new HumanPlayer());
    }else if(Utility::getInstance()->getPreceding() == Utility::PRECEDING::HUMAN) {
        player[0].reset(new HumanPlayer());
        player[1].reset(new AIPlayer());
    }else{
        player[0].reset(new AIPlayer());
        player[1].reset(new HumanPlayer());
    }
    player[0]->retain();
    player[1]->retain();
    
    
    //viewの初期設定
    auto boardlayer = BoardView::create();
    this->setBoardViewLayer(boardlayer);
    this->addChild(_boardViewLayer);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* touch, Event* event){
        cocos2d::Vec2 touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);

        auto itr = this->_boardViewLayer->getTiles();
        for (const auto& tile : itr)
        {
            //相対位置を取得する
            if(tile->getBoundingBox().containsPoint(touchPoint))
            {
                auto p = tile->getBoardPoint();
                CCLOG("tilep: x:%d y:%d",p.x,p.y);
                this->putDisc(p);
                return true;
            }
        }
        return false;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    this->_boardViewLayer->initUpdate(*_board);
    
    return true;
}

int GameScene::putDisc(Reversi::Point p)
{
    try {
        player[_current_player]->onTurn(*_board,p);
    } catch (UndoException& e)
    {
        do
        {
            _board->undo();
            _board->undo();
        }while (_board->getMovablePos().empty());
        return 0;
    }
    catch(NotMoveException& e)
    {
        return 0;
    }
    catch(ExitException& e)
    {
        return 0;
    }
    catch(GameOverException& e)
    {
        cout << "game finish " << endl;
        cout << "黒石" << _board->countDisc(BLACK) << "  ";
        cout << "白石" << _board->countDisc(WHITE) << endl;
        
        return 0;
    }
    
    //プレイヤーの交代
    this->_boardViewLayer->update(*_board);
    _current_player = ++_current_player % 2 ;

    return 0;
}