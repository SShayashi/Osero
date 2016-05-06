#include "TitleScene.hpp"
#include "BoardView.hpp"
#include "GameScene.hpp"
#include "Utility.hpp"

USING_NS_CC;
using namespace cocostudio::timeline;

Title::Title()
{
    _precedingBtn = nullptr;
}
Title::~Title()
{
    CC_SAFE_RELEASE_NULL(_precedingBtn);
}
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
    auto multiPlayBtn  = titlelayer->getChildByName<ui::Button*>("multiPlay");
    
    auto precedingBtn  = titlelayer->getChildByName<ui::Button*>("preceding");
    //先行，後攻ボタンの初期値
    precedingBtn->setTitleText("黒が先行");
    precedingBtn->setTitleColor(Color3B::BLACK);
    precedingBtn->setColor(Color3B::GRAY);
    setPrecedingBtn(precedingBtn);
    
    
    //１人プレイ２人プレイのボタンを生成
    singlePlayBtn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            Utility::getInstance()->setGameMode(Utility::GAME_MODE::SINGLE);
            
            auto gamescene = GameScene::createScene();
            auto transition = TransitionCrossFade::create(0.5, gamescene);
            Director::getInstance()->replaceScene(transition);
        }
    });
    
    multiPlayBtn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            Utility::getInstance()->setGameMode(Utility::GAME_MODE::MULTI);
            
            auto gamescene = GameScene::createScene();
            auto transition = TransitionCrossFade::create(0.5, gamescene);
            Director::getInstance()->replaceScene(transition);
        }
    });
    
    precedingBtn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED)
            if(getPrecedingBtn()->getColor() == Color3B::WHITE)
            {
                this->_precedingBtn->setColor(Color3B::GRAY);
                this->_precedingBtn->setTitleText("黒が先行");
                Utility::Utility::getInstance()->setPreceding(Utility::PRECEDING::BLACK);
                
            }else{
                this->_precedingBtn->setColor(Color3B::WHITE);
                this->_precedingBtn->setTitleText("白が先行");
                Utility::Utility::getInstance()->setPreceding(Utility::PRECEDING::WHITE);
            }
    });
    
    return true;
}
