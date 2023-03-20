//
//  Scene2.hpp
//  DemoProj
//
//  Created by octro on 17/08/22.
//

#ifndef Scene2_hpp
#define Scene2_hpp

#include "cocos2d.h"

class Scene2: public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void playWithAIBtnClicked(Ref* pSender);
    
    void playWithFriendBtnClicked(Ref* pSender);
    
    void SettingsBtnClicked(Ref* pSender);
    
    void QuitBtnClicked(Ref* pSender);

    
    CREATE_FUNC(Scene2);
};

#endif /* Scene2_hpp */
