//
//  BoardView.hpp
//  Osero
//
//  Created by 林　真史 on 2016/04/24.
//
//

#ifndef BoardView_h
#define BoardView_h

#include "cocos2d.h"
#include "Board.hpp"

class BoardView : public cocos2d::Layer
{
private:
    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Sprite *>, _tiles, Tiles);
    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Sprite *>, _discs, Discs);
public:
    virtual bool init();
    void setupBoard();
    void reflectBoard(Board &board);
    // implement the "static create()" method manually
    CREATE_FUNC(BoardView);
};


#endif /* BoardView_h */
