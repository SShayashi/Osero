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
    _touchPoint     = Reversi::Point(10, 10);
    _board          = nullptr;
    _boardViewLayer = nullptr;
    player[0]       = nullptr;
    player[1]       = nullptr;
    
    
}
GameScene::~GameScene()
{
    delete _board;
    _board = nullptr;
    CC_SAFE_RELEASE_NULL(_boardViewLayer);
    CC_SAFE_RELEASE_NULL(player[0]);
    CC_SAFE_RELEASE_NULL(player[1]);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("undo");
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
    _current_player = 0;
    _gameoverFlag   = 0;

    //Modelの初期化
    _board = new Board();
    
    //先手・後手の設定
    if(Utility::getInstance()->getGameMode() == Utility::GAME_MODE::MULTI)
    {
        this->player[0].reset(new HumanPlayer());
        this->player[1].reset(new HumanPlayer());
    }else if(Utility::getInstance()->getPreceding() == Utility::PRECEDING::HUMAN) {
        this->player[0].reset(new HumanPlayer());
        this->player[1].reset(new AIPlayer());
    }else{
        this->player[0].reset(new AIPlayer());
        this->player[1].reset(new HumanPlayer());
    }
    CC_SAFE_RETAIN(this->player[0]);
    CC_SAFE_RETAIN(this->player[1]);
    
    
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
                this->_touchPoint = tile->getBoardPoint();
                return true;
            }
        }
        return false;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    this->_boardViewLayer->initUpdate(*_board);
    
    //CPUからの場合は一度相手にターンを渡す
    if(Utility::getInstance()->getPreceding() == Utility::PRECEDING::CPU)
        this->putDisc(Reversi::Point(0,0));
    
    //undoイベントの受け取り
    Director::getInstance()->getEventDispatcher()->addCustomEventListener("undo",[&](cocos2d::EventCustom *event)
    {
        this->putDisc(Reversi::Point(-1,-1));
        //おけない値を代入しているだけ
        this->_touchPoint = Reversi::Point(10,10);

    });
    
    this->scheduleUpdate();
    
    return true;
}

int GameScene::putDisc(Reversi::Point p)
{
    if(_gameoverFlag == 1) return 0;
    try {
        this->player[_current_player]->onTurn(*_board,p);
    } catch (UndoException& e)
    {
        do
        {
            _board->undo();
            _board->undo();
        }while (_board->getMovablePos().empty());
        this->_boardViewLayer->update(*_board);
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
        this->_boardViewLayer->update(*_board);
        this->_boardViewLayer->gameOver(*_board);
        this->_gameoverFlag = 1;
        //タッチできないようにリスナーの停止
//        this->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ALL_AT_ONCE);
        //プレイヤーの交代
        cout << "game finish " << endl;
        cout << "黒石" << _board->countDisc(BLACK) << "  ";
        cout << "白石" << _board->countDisc(WHITE) << endl;
        
        return 0;
    }
    

    this->_boardViewLayer->update(*_board);    
    _current_player = ++_current_player % 2 ;
    

    return 0;
}

void GameScene::update(float delta){
    this->putDisc(_touchPoint);
    
}
