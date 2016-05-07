//
//  GUIcomponents.hpp
//  Osero
//
//  Created by 林　真史 on 2016/05/07.
//
//

#ifndef GUIcomponents_hpp
#define GUIcomponents_hpp

#include "cocos2d.h"
#include "Reversi.h"

class BoardTile : public cocos2d::Sprite
{
private:
    Sprite* _discimage;
public:
    
    enum class BOARD_STATE{
        BLACK,
        WHITE,
        AVAILABLE,
        NONE,
        COUNT
    };
    
    CREATE_FUNC(BoardTile);
    virtual bool init();
};


#endif /* GUIcomponents_hpp */
