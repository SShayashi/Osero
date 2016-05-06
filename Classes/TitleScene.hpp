#ifndef __Title_SCENE_H__
#define __Title_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "Utility.hpp"

using namespace cocostudio::timeline;

class Title : public cocos2d::Layer
{
private:
    cocos2d::Layer *BoardLayer {};
    CC_SYNTHESIZE_RETAIN(cocos2d::ui::Button*, _precedingBtn, PrecedingBtn);
public:
    Title();
    virtual ~Title();
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Title);
};

#endif // __Title_SCENE_H__
