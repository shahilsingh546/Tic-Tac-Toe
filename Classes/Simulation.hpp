
//
//  Simulation.hpp
//  DemoProj-mobile
//
//  Created by octro on 01/09/22.
//

#ifndef Simulation_hpp
#define Simulation_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "AppDelegate.h"
#include "GameOver.hpp"
#include <vector>

using namespace cocos2d;

class Simulation : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(int idx);

    virtual bool init();
    
    int flag;

    CREATE_FUNC(Simulation);
    
    
    
private:
    
    
    cocos2d::Sprite* grid;
    cocos2d::Sprite* gridPieces[3][3];
    cocos2d::Rect gridRects[3][3];   
//    int gridArray[3][3];
    
    int piece;
//    int gameState;
    
    void initGridRects();
    void InitGridPieces( );
    
    void PlacePiece();
    
    void goBack(Ref *pSender);
    
    static int recordIdx;
    
    void GoToGameOverScene();
    
    void HelperFunc();
    GameOver* gm;

};

#endif /* Simulation_hpp */


