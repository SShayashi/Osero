#include "TitleScene.hpp"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "BoardView.hpp"
#include "GameScene.hpp"

USING_NS_CC;
using namespace cocostudio::timeline;

Scene* Title::createScene()
{
    auto scene = Scene::create();
    auto layer = Title::create();
    scene->addChild(layer);
    return scene;
}

bool Title::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // titleLayerの読み込み
    auto titlelayer = CSLoader::getInstance()->createNode("TitleLayer.csb");
    this->addChild(titlelayer);

    auto singlePlayBtn = titlelayer->getChildByName<ui::Button*>("singlePlay");
    auto multiPlayBtn = titlelayer->getChildByName<ui::Button*>("multiPlay");
    

    singlePlayBtn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        // タッチが終わった後に実行
        if (type == ui::Widget::TouchEventType::ENDED) {
            Utility::getInstance()->setGameMode(Utility::GAME_MODE::SINGLE);
            
            auto gamescene = GameScene::createScene();
            auto transition = TransitionCrossFade::create(0.5, gamescene);
            Director::getInstance()->replaceScene(transition);
        }
    });
    
    multiPlayBtn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        // タッチが終わった後に実行
        if (type == ui::Widget::TouchEventType::ENDED) {
            Utility::getInstance()->setGameMode(Utility::GAME_MODE::MULTI);
            
            auto gamescene = GameScene::createScene();
            auto transition = TransitionCrossFade::create(0.5, gamescene);
            Director::getInstance()->replaceScene(transition);
        }
    });
    
    return true;
}
