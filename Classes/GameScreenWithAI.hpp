
//
//  GameScreenWithAI.hpp
//  DemoProj-mobile
//
//  Created by octro on 01/09/22.
//

#ifndef GameScreenWithAI_hpp
#define GameScreenWithAI_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <vector>
#include <iostream>
#include "Settings.hpp"
#include "GameOver.hpp"

#include "AI.hpp"

using namespace std;

using namespace cocos2d;
class GameScreenWithAI : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(cocos2d::ui::RadioButton* rd1, cocos2d::ui::RadioButton* rd2);
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameScreenWithAI);
    
    //Helper Func to Call 
    void FunCallHelper();
    void winningPopUp(float dt);
    int piece;
    bool check=true;
    
    static cocos2d::ui::RadioButton* rdb1;
    static cocos2d::ui::RadioButton* rdb2;

    void touchdisable(float ft);
private:
        
    bool onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event );
    
    void onTouchEnded( cocos2d::Touch *touch, cocos2d::Event *event );
    
    cocos2d::Sprite* grid;
    cocos2d::Sprite* gridPieces[3][3];
    cocos2d::Rect gridRects[3][3];
    int gridArray[3][3];
    
    int turn;
    int gameState;
    
    void initGridRects();
    void InitGridPieces( );
    
    void CheckAndPlacePiece( cocos2d::Touch *touch );
    
    void CheckWin( int x, int y );
      
    void Check3Pieces( int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck );
    
    AI* ai;
    
    GameOver *gm1;

};

#endif /* GameScreen_hpp */

