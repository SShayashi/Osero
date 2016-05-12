//
//  GUIcomponents.cpp
//  Osero
//
//  Created by 林　真史 on 2016/05/07.
//
//

#include "GUIcomponents.hpp"
using namespace cocos2d;

bool BoardTile::init()
{
    
    if (!Sprite::initWithFile("tile01.png")) {
        return false;
    }
    _boardState = BOARD_STATE::NONE;
    _color = EMPTY;
    return true;
}


void BoardTile::setColor(Color color)
{
    switch (color) {
        case WHITE:
        {
            _color = WHITE;
            Sprite* disc {Sprite::create("s.png")};
            disc->setPosition(this->getContentSize()/2);
            this->addChild(disc);
            this->setDisc(disc);
            return ;
        }
        case BLACK:
        {
            _color = BLACK;
            Sprite* disc {Sprite::create("k.png")};
            disc->setPosition(this->getContentSize()/2);
            this->addChild(disc);
            this->setDisc(disc);
            return ;
        }
        case EMPTY:
            break;
            
    }
}

