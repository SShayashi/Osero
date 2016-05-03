#ifndef __Title_SCENE_H__
#define __Title_SCENE_H__

#include "cocos2d.h"
#include "Utility.hpp"

class Title : public cocos2d::Layer
{
private:
    cocos2d::Layer *BoardLayer {};
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Title);
};

#endif // __Title_SCENE_H__
