//
//  Utility.cpp
//  Osero
//
//  Created by 林　真史 on 2016/05/03.
//
//

#include "Utility.hpp"
USING_NS_CC;

Utility* Utility::mUtility = NULL;

Utility::Utility()
{
    
}

Utility* Utility::getInstance()
{
    if(mUtility == NULL)
    {
        mUtility = new Utility();
        mUtility->initialize();
    }
    
    return mUtility;
}

// 値の初期化
void Utility::initialize()
{
    _gamemode = GAME_MODE::SINGLE;
}