
//
//  GameScreenWithFriend.hpp
//  DemoProj-mobile
//
//  Created by octro on 01/09/22.
//

#ifndef GameScreenWithFriend_hpp
#define GameScreenWithFriend_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "AI.hpp"
#include "GameOver.hpp"

using namespace cocos2d;
class GameScreenWithFriend : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(cocos2d::ui::RadioButton* rd1, cocos2d::ui::RadioButton* rd2);

    virtual bool init();
//    virtual void onEnter();

    CREATE_FUNC(GameScreenWithFriend);
    
    
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
      
    void Check3Pieces( int x1, int y1, int x2, int y2, int x3, int y3);
    
    void FunCallHelper();
    void winningPopUp(float dt);
    
    GameOver *gm2;

};

#endif /* GameScreenWithFriend_hpp */

