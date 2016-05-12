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
#include "GUIcomponents.hpp"
#include "ui/CocosGUI.h"
#include "GUIcomponents.hpp"

class BoardView : public cocos2d::Layer
{
private:
    CC_SYNTHESIZE_RETAIN(cocos2d::Node*, _boardLayer, BoardLayer);
    CC_SYNTHESIZE_RETAIN(cocos2d::Node*, _tableNode, TableNode);
    CC_SYNTHESIZE_RETAIN(cocos2d::RenderTexture*, _renderTexture, RenderTexture);
    CC_SYNTHESIZE_RETAIN(cocos2d::ui::Text *, _blackDiscNumLabel, BlackDiscNumLabel);
    CC_SYNTHESIZE_RETAIN(cocos2d::ui::Text *, _whiteDiscNumLabel, WhiteDiscNumLabel);
    CC_SYNTHESIZE(cocos2d::Vector<BoardTile *>, _tiles, Tiles);
    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Sprite *>, _discs, Discs);
    cocos2d::Vec2 _boardpos;
    cocos2d::Size winSize {};
public:
    BoardView();
    virtual ~BoardView();
    virtual bool init();
    void initUpdate(const Board &board);
    void update(const Board &board);
    
    CREATE_FUNC(BoardView);
};


#endif /* BoardView_h */
