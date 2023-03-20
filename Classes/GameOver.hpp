#pragma once

#include "cocos2d.h"

class GameOver
{
public:
    
    GameOver(cocos2d::Scene* scene);
    
    void popUpAfterGame(cocos2d::Scene* scene,int piece,int n);
    
private:
//    std::string winningMsg;
    
    void touchHandling();
    
    void Home(cocos2d::Ref *pSender);
    
    void Retry(cocos2d::Ref *pSender);
    
//    void GameOverTouchHandling();
    
};
