//
//  playWithAI.hpp
//  DemoProj
//
//  Created by octro on 17/08/22.
//

#ifndef playWithFriend_hpp
#define playWithFriend_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class playWithFriend: public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(playWithFriend);
};

#endif /* playWithFriend_hpp */

