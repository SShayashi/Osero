//
//  GUIcomponets.hpp
//  Osero
//
//  Created by 林　真史 on 2016/04/27.
//
//

#ifndef GUIcomponets_h
#define GUIcomponets_h
#include "cocos2d.h"
#include "Reversi.h"

class BoardTile : public cocos2d::Sprite
{
private:
    Sprite* _discimage;
public:
    CREATE_FUNC(BoardTile);
    virtual bool init()
    {
        if (!Sprite::initWithFile("tile01.png")) {
            return false;
        }
        return true;
    }
    
//    void setDisc(Disc &disc){
//        switch (disc.color) {
//            case BLACK:
//                break;
//            case WHITE:
//                break;
//                
//            default:
//                break;
//        }
//    
//    }
    
};

#endif /* GUIcomponets_h */
