//
//  GUIcomponents.cpp
//  Osero
//
//  Created by 林　真史 on 2016/05/07.
//
//

#include "GUIcomponents.hpp"
using namespace cocos2d;

bool BoardTile::init(){
    
    if (!Sprite::initWithFile("tile01.png")) {
        return false;
    }
    return true;
}
