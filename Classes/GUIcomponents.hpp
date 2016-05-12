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
#include "Board.hpp"
const int TILE_SIZE = 75;
class BoardTile : public cocos2d::Sprite
{
public:
    
    enum class BOARD_STATE{
        BLACK,
        WHITE,
        AVAILABLE,
        NONE,
        COUNT
    };
    
    static int getSize(){
        return TILE_SIZE;
    }
    
    /** ステージ上の座標を配列中の位置に変換
     *
     *
     */
    static cocos2d::Vec2 convertToArraySpace(const cocos2d::Vec2& stagePosition)
    {
        auto x = floor(stagePosition.x / BoardTile::getSize());
        auto y = floor(stagePosition.y / BoardTile::getSize());
        return std::move(cocos2d::Vec2(x,y));
    }

    
    /** 配列中の座標をステージ上の座標に変換する
     *
     *
     */
//    static cocos2d::Vec2 convertToStageSpace(const cocos2d::Vec2& arrayPosition);
    
    static cocos2d::Vec2 convertToStageSpace(const cocos2d::Vec2& arrayPosition)
    {
        return std::move((arrayPosition + cocos2d::Vec2::ONE * 0.5) * BoardTile::getSize());
    }

    
    /** Reversiの色からそれにあったオセロを貼り付ける
     *
     */
    void setColor(const Color color);
    Color getColor()
    {
        return _color;
    }
    CREATE_FUNC(BoardTile);
    virtual bool init();
private:
    Color _color;
    CC_SYNTHESIZE_RETAIN(Sprite*, _disc, Disc);
    CC_SYNTHESIZE(BOARD_STATE, _boardState, BoardState);
    CC_SYNTHESIZE(Reversi::Point, _boardPoint, BoardPoint);
};


#endif /* GUIcomponents_hpp */
