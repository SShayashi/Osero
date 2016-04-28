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
#include "GUIcomponets.hpp"

class BoardView : public cocos2d::Layer
{
private:
    CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*, _background, BackGround);
    CC_SYNTHESIZE(cocos2d::Vector<BoardTile *>, _tiles, Tiles);
    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Sprite *>, _discs, Discs);
public:
    
    cocos2d::Size winSize {};
    
    virtual bool init();
    void setupBoard();
    void update(Board &board);
    // implement the "static create()" method manually
    CREATE_FUNC(BoardView);
};


#endif /* BoardView_h */
