
#include "Simulation.hpp"
#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Path.h"
#include "GameScreenWithAI.hpp"
#include "AppDelegate.h"
#include "Settings.hpp"
#include "HeaderLayer.hpp"
#include "GameOver.hpp"
#include "Path.h"
#include <iostream>
#include <vector>

using namespace cocos2d;

USING_NS_CC;

int Simulation::recordIdx = -1;


Scene* Simulation::createScene(int idx)
{
    recordIdx = idx;
    return Simulation::create();
}


bool Simulation::init()
{
    if(!Scene::init())
        return false;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    
    //Adding Background sprite into the scene*****************************************************
    
    auto gridBg = Sprite::create(GRID_BACKGROUND);
    gridBg->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    gridBg->setContentSize(Size(visibleSize.width,visibleSize.height));
    this->addChild(gridBg);
    
    
    
    
    Layer* layer = HeaderLayer::myCreate(AppDelegate::getStore()->headerStr[recordIdx],SIMULATION);
    this->addChild(layer);
    
    
    
    //Adding Grid**************************************************
    
    grid = Sprite::create(GRID);
    grid->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    this->addChild(grid);
    
    
    
    
    initGridRects(); //To get Size and Position of individual 9 grid rectangles from 3X3 grid sprite***********************
    InitGridPieces();//To add Sprite on the 3X3 grid******************************
    
    
    DelayTime *delayAction = DelayTime::create(0.3f);
    
    CallFunc *runCallback1 = CallFunc::create(CC_CALLBACK_0(Simulation::PlacePiece, this));

    this->runAction(Sequence::create(delayAction, runCallback1, NULL));

    gm = new GameOver(this);
    
    return true;
}

void Simulation::initGridRects()
{
        gridRects[0][0] = Rect(    grid->getBoundingBox( ).getMinX( ),
                                grid->getBoundingBox( ).getMinY( ),
                                grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox().size.height / 3
                                );
        
        gridRects[1][0] = Rect(    grid->getBoundingBox( ).getMinX( ) + grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox( ).getMinY( ),
                                grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox().size.height / 3
                                );
        
        gridRects[2][0] = Rect(    grid->getBoundingBox( ).getMinX( ) + ( ( grid->getBoundingBox().size.width / 3 ) * 2 ),
                                grid->getBoundingBox( ).getMinY( ),
                                grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox().size.height / 3
                                );
        
        gridRects[0][1] = Rect(    grid->getBoundingBox( ).getMinX( ),
                                grid->getBoundingBox( ).getMinY( ) + grid->getBoundingBox().size.height / 3,
                                grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox().size.height / 3
                                );
        
        gridRects[1][1] = Rect(    grid->getBoundingBox( ).getMinX( ) + grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox( ).getMinY( ) + grid->getBoundingBox().size.height / 3,
                                grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox().size.height / 3
                                );
        
        gridRects[2][1] = Rect(    grid->getBoundingBox( ).getMinX( ) + ( ( grid->getBoundingBox().size.width / 3 ) * 2 ),
                                grid->getBoundingBox( ).getMinY( ) + grid->getBoundingBox().size.height / 3,
                                grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox().size.height / 3
                                );
        
        gridRects[0][2] = Rect(    grid->getBoundingBox( ).getMinX( ),
                                grid->getBoundingBox( ).getMinY( ) + ( ( grid->getBoundingBox().size.height / 3 ) * 2 ),
                                grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox().size.height / 3
                                );
        
        gridRects[1][2] = Rect(    grid->getBoundingBox( ).getMinX( ) + grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox( ).getMinY( ) + ( ( grid->getBoundingBox().size.height / 3 ) * 2 ),
                                grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox().size.height / 3
                                );
        
        gridRects[2][2] = Rect(    grid->getBoundingBox( ).getMinX( ) + ( ( grid->getBoundingBox().size.width / 3 ) * 2 ),
                                grid->getBoundingBox( ).getMinY( ) + ( ( grid->getBoundingBox().size.height / 3 ) * 2 ),
                                grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox().size.height / 3
                              );
                              
}


void Simulation::InitGridPieces()
{
//    auto visibleSize = Director::getInstance()->getVisibleSize();
    for(int x=0;x<3;x++)
    {
        for(int y=0;y<3;y++)
        {
            gridPieces[x][y] = Sprite::create( X_SPRITE );
            gridPieces[x][y]->setScale(0.8);
//            gridPieces[x][y]->setPosition( Vec2( grid->getPositionX( ) + ( gridPieces[x][y]->getContentSize( ).width * ( x - 1 ) ), grid->getPositionY( ) + ( gridPieces[x][y]->getContentSize( ).height * ( y - 1 ) ) ) );
            
            gridPieces[x][y]->setPosition(Vec2(grid->getPositionX()+(160*(x-1)), grid->getPositionY()+(155* (y-1))));

            gridPieces[x][y]->setVisible( false );
            gridPieces[x][y]->setOpacity( 0 );
            this->addChild( gridPieces[x][y] );
        }
    }
    
}



void Simulation::PlacePiece()
{
    cout<<"Inside PlacePiece"<<endl;
    
    int turn = AppDelegate::getStore()->startPiece[recordIdx];
    
    vector<pair<int,int>> positions = AppDelegate::getStore()->MoveRecords[recordIdx];
    
    
    int i,n=9;
    for(i=0;i<positions.size();i++)
    {
        pair<int,int> p = positions[i];
        if(turn == X_PIECE)
        {
            gridPieces[p.first][p.second]->setTexture(X_SPRITE);
            turn = O_PIECE;
        }
        else
        {
            gridPieces[p.first][p.second]->setTexture(O_SPRITE);
            turn = X_PIECE;
        }

        gridPieces[p.first][p.second]->setVisible( true );
        auto delay = DelayTime::create(1+i);

        gridPieces[p.first][p.second]->runAction( Sequence::create( delay,FadeIn::create( 0.5f), nullptr));
        n--;
    }
    
    if(n==0)
    {
        piece = -1;
        DelayTime *delayAction1 = DelayTime::create(10.0f);
        CallFunc *runCallback2 = CallFunc::create(CC_CALLBACK_0(Simulation::GoToGameOverScene, this));
        this->runAction(Sequence::create(delayAction1,runCallback2, NULL));
    }
    else if(turn == X_PIECE)
    {
        piece = O_PIECE;
        DelayTime *delayAction1 = DelayTime::create(7.0f);
        CallFunc *runCallback2 = CallFunc::create(CC_CALLBACK_0(Simulation::GoToGameOverScene, this));
        this->runAction(Sequence::create(delayAction1,runCallback2, NULL));
    }
        
    else if(turn == O_PIECE)
    {
        piece = X_PIECE;
        DelayTime *delayAction1 = DelayTime::create(7.0f);
        CallFunc *runCallback2 = CallFunc::create(CC_CALLBACK_0(Simulation::GoToGameOverScene, this));
        this->runAction(Sequence::create(delayAction1,runCallback2, NULL));
    }

}



void Simulation::GoToGameOverScene()
{
    gm->popUpAfterGame(this,piece, SIMULATION);
}


