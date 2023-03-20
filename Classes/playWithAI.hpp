
#ifndef playWithAI_hpp
#define playWithAI_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class playWithAI: public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(playWithAI);

};

#endif /* playWithAI_hpp */

