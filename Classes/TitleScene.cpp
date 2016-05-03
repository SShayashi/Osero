#include "TitleScene.hpp"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "BoardView.hpp"

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

        }
    });
    
    multiPlayBtn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        // タッチが終わった後に実行
        if (type == ui::Widget::TouchEventType::ENDED) {

        }
    });
    
    return true;
}
