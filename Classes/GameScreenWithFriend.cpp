#include "GameScreenWithFriend.hpp"
#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Path.h"
#include "playWithAI.hpp"
#include "playWithFriend.hpp"
#include "AI.hpp"
#include "AppDelegate.h"
#include "HeaderLayer.hpp"
#include "GameScreenWithAI.hpp"
#include <iostream>

USING_NS_CC;

cocos2d::ui::RadioButton* rdbtn1;
cocos2d::ui::RadioButton* rdbtn2;


//Variables to store Piece value based on the selected radioButton************************
int myPiece;
int friendPiece;
int wPiece;


Scene* GameScreenWithFriend::createScene(cocos2d::ui::RadioButton* rd1,cocos2d::ui::RadioButton* rd2)
{
    rdbtn1=rd1;
    rdbtn2=rd2;
    return GameScreenWithFriend::create();
}


bool GameScreenWithFriend::init()
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
    

    Layer* layer = HeaderLayer::myCreate("Play With Friend",GAMESCREENWITHFRIEND);
    this->addChild(layer);
    
    
    
    //Adding Grid**************************************************
    
    grid = Sprite::create(GRID);
    grid->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    this->addChild(grid);
    
    
    
    //Creating eventListener********************************************
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScreenWithFriend::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScreenWithFriend::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    

    //Condition to Check selected radioButton from previous scene*********************************
    
    if(rdbtn1->isSelected())
    {
        turn = X_PIECE;
        myPiece = X_PIECE;
        friendPiece = O_PIECE;
//        AppDelegate::getStore()->startPiece.push_back(X_PIECE);
    }
    else
    {
        turn = O_PIECE;
        myPiece = O_PIECE;
        friendPiece = X_PIECE;
//        AppDelegate::getStore()->startPiece.push_back(O_PIECE);
    }

    
    gameState = STATE_PLAYING; //gameState to keep track the state**************************************
    
    
    
    initGridRects(); //To get Size and Position of individual 9 grid rectangles from 3X3 grid sprite***********************
    InitGridPieces();//To add Sprite on the 3X3 grid******************************
    
    
    //Intially Assigning -1 to gridArray*********************************
    for(int x=0;x<3;x++)
    {
        for(int y=0;y<3;y++)
        {
            gridArray[x][y] = EMPTY;
        }
    }
    
    return true;
}


void GameScreenWithFriend::initGridRects()
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


void GameScreenWithFriend::InitGridPieces()
{
    for(int x=0;x<3;x++)
    {
        for(int y=0;y<3;y++)
        {
            gridPieces[x][y] = Sprite::create( X_SPRITE );
            gridPieces[x][y]->setScale(0.8);
            gridPieces[x][y]->setPosition(Vec2(grid->getPositionX()+(160*(x-1)), grid->getPositionY()+(155* (y-1))));
            gridPieces[x][y]->setVisible( false );
            gridPieces[x][y]->setOpacity( 0 );
            this->addChild( gridPieces[x][y] );
        }
    }
}


bool GameScreenWithFriend::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return true;
}

void GameScreenWithFriend::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(gameState == STATE_PLAYING)
        CheckAndPlacePiece(touch);
}


//
void GameScreenWithFriend::CheckAndPlacePiece(cocos2d::Touch *touch)
{
    Vec2 touchPoint = touch->getLocation( );
    
    for ( int x = 0; x < 3; x++ )
    {
        for ( int y = 0; y < 3; y++ )
        {
            if ( gridRects[x][y].containsPoint( touchPoint ) )
            {
                if ( gridArray[x][y] == EMPTY )
                {
                    
                    AppDelegate::getStore()->positions.push_back({x,y});
                    
                    gameState = STATE_PLACING_PIECE;
                    
                    gridArray[x][y] = turn;
                    
                    if ( turn == X_PIECE )
                    {
                        gridPieces[x][y]->setTexture( X_SPRITE );
                    }
                    else
                    {
                        gridPieces[x][y]->setTexture( O_SPRITE );
                    }
                    
                    gridPieces[x][y]->setVisible( true );
                    
                    gridPieces[x][y]->runAction( Sequence::create( FadeIn::create( 0.5f), CallFunc::create( std::bind( &GameScreenWithFriend::CheckWin, this, x, y ) ), NULL ) );
                }
            }
        }
    }
}

void GameScreenWithFriend::CheckWin(int x, int y)
{
    Check3Pieces(0,0,1,1,2,2);
    Check3Pieces(0,0,0,1,0,2);
    Check3Pieces(0,0,1,0,2,0);
    Check3Pieces(0,1,1,1,2,1);
    Check3Pieces(0,2,1,1,2,0);
    Check3Pieces(0,2,1,2,2,2);
    Check3Pieces(1,0,1,1,1,2);
    Check3Pieces(2,0,2,1,2,2);

    
    // check who's current turn it is and switch
       if ( X_PIECE == turn )
       {
           turn = O_PIECE;
       }
       else
       {
           turn = X_PIECE;
       }
       
       if ( STATE_PLACING_PIECE == gameState )
       {
           gameState = STATE_PLAYING;
       }
    
    
    int emptyNum = 9;
        
        for ( int x = 0; x < 3; x++ )
        {
            for ( int y = 0; y < 3; y++ )
            {
                if ( EMPTY != gridArray[x][y] )
                {
                    emptyNum--;
                }
            }
        }
        
        // check if the game is a draw
        if ( 0 == emptyNum )
        {
            gameState = STATE_DRAW;
            
    
            int s=(int)AppDelegate::getStore()->MoveRecords.size();
            if(s>=10){
                vector<vector<pair<int,int>>> tempforMoveRecords;
                vector<int> tempForStartPiece;
                vector<string> tempForHeaderStr;
                
                for(int i=1;i<AppDelegate::getStore()->MoveRecords.size();i++)
                {
                    tempforMoveRecords.push_back(AppDelegate::getStore()->MoveRecords[i]);
                    tempForStartPiece.push_back(AppDelegate::getStore()->startPiece[i]);
                    tempForHeaderStr.push_back(AppDelegate::getStore()->headerStr[i]);
                }
                
                AppDelegate::getStore()->MoveRecords.clear();
                AppDelegate::getStore()->startPiece.clear();
                AppDelegate::getStore()->headerStr.clear();
                
                for(int i=0;i<tempforMoveRecords.size();i++)
                {
                    AppDelegate::getStore()->MoveRecords.push_back(tempforMoveRecords[i]);
                    AppDelegate::getStore()->startPiece.push_back(tempForStartPiece[i]);
                    AppDelegate::getStore()->headerStr.push_back(tempForHeaderStr[i]);
                }
            }
            
            
            AppDelegate::getStore()->MoveRecords.push_back(AppDelegate::getStore()->positions);
            AppDelegate::getStore()->startPiece.push_back(myPiece);
            AppDelegate::getStore()->headerStr.push_back("Play With Friend");
            AppDelegate::getStore()->positions.clear();
            
            AppDelegate::getStore()->StoringData();
            
            
            wPiece=-1;
            
            
            gm2->popUpAfterGame(this, -1, GAMESCREENWITHFRIEND);
        }
        
        std::cout << gameState << std::endl;
}


void GameScreenWithFriend::Check3Pieces( int x1, int y1, int x2, int y2, int x3, int y3 )
{
    if ( turn == gridArray[x1][y1] && turn == gridArray[x2][y2] && turn == gridArray[x3][y3] )
    {
        wPiece = turn;
        int s=(int)AppDelegate::getStore()->MoveRecords.size();
        if(s>=10){
            vector<vector<pair<int,int>>> tempforMoveRecords;
            vector<int> tempForStartPiece;
            vector<string> tempForHeaderStr;
            
            for(int i=1;i<AppDelegate::getStore()->MoveRecords.size();i++)
            {
                tempforMoveRecords.push_back(AppDelegate::getStore()->MoveRecords[i]);
                tempForStartPiece.push_back(AppDelegate::getStore()->startPiece[i]);
                tempForHeaderStr.push_back(AppDelegate::getStore()->headerStr[i]);
            }
            
            AppDelegate::getStore()->MoveRecords.clear();
            AppDelegate::getStore()->startPiece.clear();
            AppDelegate::getStore()->headerStr.clear();
            
            for(int i=0;i<tempforMoveRecords.size();i++)
            {
                AppDelegate::getStore()->MoveRecords.push_back(tempforMoveRecords[i]);
                AppDelegate::getStore()->startPiece.push_back(tempForStartPiece[i]);
                AppDelegate::getStore()->headerStr.push_back(tempForHeaderStr[i]);
            }
        }
        
        
        AppDelegate::getStore()->MoveRecords.push_back(AppDelegate::getStore()->positions);
        AppDelegate::getStore()->startPiece.push_back(myPiece);
        AppDelegate::getStore()->headerStr.push_back("Play With Friend");
        AppDelegate::getStore()->positions.clear();
        
        AppDelegate::getStore()->StoringData();
        
        __String winningPieceStr;
        
        if ( O_PIECE == turn )
        {
            winningPieceStr = O_SPRITE;
        }
        else
        {
            winningPieceStr = X_SPRITE;
        }
        
        Sprite *winningPieces[3];
        
        winningPieces[0] = Sprite::create( winningPieceStr.getCString( ) );
        winningPieces[0]->setPosition( gridPieces[x1][y1]->getPosition( ) );
        winningPieces[0]->setOpacity( 0 );
        this->addChild( winningPieces[0] );
        winningPieces[1] = Sprite::create( winningPieceStr.getCString( ) );
        winningPieces[1]->setPosition( gridPieces[x2][y2]->getPosition( ) );
        winningPieces[1]->setOpacity( 0 );
        this->addChild( winningPieces[1] );
        winningPieces[2] = Sprite::create( winningPieceStr.getCString( ) );
        winningPieces[2]->setPosition( gridPieces[x3][y3]->getPosition( ) );
        winningPieces[2]->setOpacity( 0 );
        this->addChild( winningPieces[2] );
        
        winningPieces[0]->runAction( FadeIn::create( 0.2f ) );
        winningPieces[1]->runAction( Sequence::create( DelayTime::create( 0.2f * 0.5 ), FadeIn::create( 0.2f ), NULL ) );
        winningPieces[2]->runAction( Sequence::create( DelayTime::create( 0.5f * 1.5 ), FadeIn::create( 0.2f ), NULL ) );
        
        gameState = STATE_WON;
        
        gm2->popUpAfterGame(this, turn, GAMESCREENWITHFRIEND);
    }
}

