//
//  Utility.hpp
//  Osero
//
//  Created by 林　真史 on 2016/05/03.
//
//

#ifndef Utility_hpp
#define Utility_hpp

#include "cocos2d.h"
USING_NS_CC;


class Utility
{
private:
    Utility();
    static Utility* mUtility;
public:
    //ゲーム内で利用する共用体
    
    //ゲームの種類
    enum class GAME_MODE{
        SINGLE,
        MULTI,
        COUNT
    };
    
    //先攻後攻
    enum class PRECEDING{
        HUMAN,
        CPU,
        COUNT
    };
    
    
    static Utility* getInstance();
    // 値の初期化
    void initialize();
    
    // メソッドと変数
    CC_SYNTHESIZE(GAME_MODE, _gamemode, GameMode);
    CC_SYNTHESIZE(PRECEDING, _preceding, Preceding);
};

#endif /* Utility_hpp */
