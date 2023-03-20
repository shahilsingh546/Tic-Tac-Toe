#include "GameScreenWithAI.hpp"
#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "AppDelegate.h"
#include "Path.h"
#include "playWithAI.hpp"
#include "AI.hpp"
#include "AppDelegate.h"
#include "Settings.hpp"
#include "GameOver.hpp"
#include "HeaderLayer.hpp"
#include "extensions/GUI/CCScrollView/CCScrollView.h"
#include <iostream>
#include <vector>
#include "cocos-ext.h"

using namespace std;

USING_NS_CC;

cocos2d::ui::RadioButton* GameScreenWithAI::rdb1 = nullptr;
cocos2d::ui::RadioButton* GameScreenWithAI::rdb2 = nullptr;
//Variables to store Piece value based on the selected radioButton************************
int playerPiece;
int aiPiece;
int winnerPiece;
//bool GameScreenWithAI::check =true;

AppDelegate* store = AppDelegate::getStore();

Scene* GameScreenWithAI::createScene()
{
    return GameScreenWithAI::create();
}

Scene* GameScreenWithAI::createScene(cocos2d::ui::RadioButton* rd1,cocos2d::ui::RadioButton* rd2)
{
    rdb1=rd1;
    rdb2=rd2;
    return GameScreenWithAI::create();
}


bool GameScreenWithAI::init()
{
    if(!Scene::init())
        return false;
    
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    
    //Adding Background sprite into the scene*****************************************************
    auto bg = Sprite::create(GRID_BACKGROUND);
    bg->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    bg->setContentSize(Size(visibleSize.width,visibleSize.height));
    this->addChild(bg);
    
    
    
    Layer* layer = HeaderLayer::myCreate("Play With AI",GAMESCREENWITHAI);
    this->addChild(layer);
    
    
    //Adding Grid**************************************************
    grid = Sprite::create(GRID);
    grid->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    bg->addChild(grid);
    
    
    
    //Creating eventListener********************************************
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScreenWithAI::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScreenWithAI::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    

    //Condition to Check selected radioButton from previous scene*********************************
    
    if(rdb1->isSelected())
    {
        turn = X_PIECE;
        playerPiece = X_PIECE;
        aiPiece = O_PIECE;
    }
    else
    {
        turn = O_PIECE;
        playerPiece = O_PIECE;
        aiPiece = X_PIECE;
    }
    
    

    ai = new AI(turn); //Creating and assigning turn to AI***************************************************
    
    
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


void GameScreenWithAI::initGridRects()
{
        gridRects[0][0] = Rect( grid->getBoundingBox( ).getMinX( ),
                                grid->getBoundingBox( ).getMinY( ),
                                grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox().size.height / 3
                                );
        
        gridRects[1][0] = Rect( grid->getBoundingBox( ).getMinX( ) + grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox( ).getMinY( ),
                                grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox().size.height / 3
                                );
        
        gridRects[2][0] = Rect( grid->getBoundingBox( ).getMinX( ) + ( ( grid->getBoundingBox().size.width / 3 ) * 2 ),
                                grid->getBoundingBox( ).getMinY( ),
                                grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox().size.height / 3
                                );
        
        gridRects[0][1] = Rect( grid->getBoundingBox( ).getMinX( ),
                                grid->getBoundingBox( ).getMinY( ) + grid->getBoundingBox().size.height / 3,
                                grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox().size.height / 3
                                );
        
        gridRects[1][1] = Rect( grid->getBoundingBox( ).getMinX( ) + grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox( ).getMinY( ) + grid->getBoundingBox().size.height / 3,
                                grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox().size.height / 3
                                );
        
        gridRects[2][1] = Rect( grid->getBoundingBox( ).getMinX( ) + ( ( grid->getBoundingBox().size.width / 3 ) * 2 ),
                                grid->getBoundingBox( ).getMinY( ) + grid->getBoundingBox().size.height / 3,
                                grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox().size.height / 3
                                );
        
        gridRects[0][2] = Rect( grid->getBoundingBox( ).getMinX( ),
                                grid->getBoundingBox( ).getMinY( ) + ( ( grid->getBoundingBox().size.height / 3 ) * 2 ),
                                grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox().size.height / 3
                                );
        
        gridRects[1][2] = Rect( grid->getBoundingBox( ).getMinX( ) + grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox( ).getMinY( ) + ( ( grid->getBoundingBox().size.height / 3 ) * 2 ),
                                grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox().size.height / 3
                                );
        
        gridRects[2][2] = Rect( grid->getBoundingBox( ).getMinX( ) + ( ( grid->getBoundingBox().size.width / 3 ) * 2 ),
                                grid->getBoundingBox( ).getMinY( ) + ( ( grid->getBoundingBox().size.height / 3 ) * 2 ),
                                grid->getBoundingBox().size.width / 3,
                                grid->getBoundingBox().size.height / 3
                              );
                              
}


void GameScreenWithAI::InitGridPieces()
{
    for(int x=0;x<3;x++)
    {
        for(int y=0;y<3;y++)
        {
            gridPieces[x][y] = Sprite::create( X_SPRITE );
            gridPieces[x][y]->setScale(0.8);
            gridPieces[x][y]->setPosition(Vec2(grid->getPositionX()+(155*(x-1)), grid->getPositionY()+(155* (y-1))));
            gridPieces[x][y]->setVisible( false );
            gridPieces[x][y]->setOpacity( 0 );
            this->addChild( gridPieces[x][y] );
        }
    }
}


bool GameScreenWithAI::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return true;
}


void GameScreenWithAI::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if(gameState == STATE_PLAYING && check == true)
    {
        CheckAndPlacePiece(touch);
        check =false;
        this->scheduleOnce(schedule_selector(GameScreenWithAI::touchdisable), 1.5f);
    }
}

void GameScreenWithAI::touchdisable(float ft){
    check=true;
}

//
void GameScreenWithAI::CheckAndPlacePiece(cocos2d::Touch *touch)
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
//                    cout<<x<<" "<<y<<endl;
                    
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
                    
                    gridPieces[x][y]->runAction( Sequence::create( FadeIn::create( 0.5f), CallFunc::create( std::bind( &GameScreenWithAI::CheckWin, this, x, y ) ), NULL ) );
                }
            }
        }
    }
}

void GameScreenWithAI::CheckWin(int x, int y)
{
    Check3Pieces(0,0,1,1,2,2, playerPiece);
    Check3Pieces(0,0,0,1,0,2, playerPiece);
    Check3Pieces(0,0,1,0,2,0, playerPiece);
    Check3Pieces(0,1,1,1,2,1, playerPiece);
    Check3Pieces(0,2,1,1,2,0, playerPiece);
    Check3Pieces(0,2,1,2,2,2, playerPiece);
    Check3Pieces(1,0,1,1,1,2, playerPiece);
    Check3Pieces(2,0,2,1,2,2, playerPiece);
    
    
    if ( STATE_WON != gameState )
        {
            gameState = STATE_AI_PLAYING;
            ai->PlacePiece( &gridArray, gridPieces, &gameState );
            
            Check3Pieces( 0, 0, 1, 0, 2, 0, aiPiece );
            Check3Pieces( 0, 1, 1, 1, 2, 1, aiPiece );
            Check3Pieces( 0, 2, 1, 2, 2, 2, aiPiece );
            Check3Pieces( 0, 0, 0, 1, 0, 2, aiPiece );
            Check3Pieces( 1, 0, 1, 1, 1, 2, aiPiece );
            Check3Pieces( 2, 0, 2, 1, 2, 2, aiPiece );
            Check3Pieces( 0, 0, 1, 1, 2, 2, aiPiece );
            Check3Pieces( 0, 2, 1, 1, 2, 0, aiPiece );
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
            AppDelegate::getStore()->startPiece.push_back(playerPiece);
            AppDelegate::getStore()->headerStr.push_back("Play With AI");
            AppDelegate::getStore()->positions.clear();
            
            AppDelegate::getStore()->StoringData();
            
            
            winnerPiece=-1;
            gm1->popUpAfterGame(this, -1, GAMESCREENWITHAI);
        }
        
        std::cout << gameState << std::endl;
}


void GameScreenWithAI::Check3Pieces(int x1, int y1, int x2, int y2, int x3, int y3,int pieceToCheck)
{
    if ( pieceToCheck == gridArray[x1][y1] && pieceToCheck == gridArray[x2][y2] && pieceToCheck == gridArray[x3][y3] )
        {
         
            winnerPiece = pieceToCheck;
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
            AppDelegate::getStore()->startPiece.push_back(playerPiece);
            AppDelegate::getStore()->headerStr.push_back("Play With AI");
            AppDelegate::getStore()->positions.clear();
            
            
            //Funtion call to Userstore data********************************
            AppDelegate::getStore()->StoringData();
            
        
            
            __String winningPieceStr;
            cout<<"Winner"<<endl;
            if ( O_PIECE == pieceToCheck )
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

        
            
            if ( playerPiece == pieceToCheck )
            {
                gameState = STATE_WON;
                piece = pieceToCheck;
            }
            else
            {
                gameState = STATE_LOSE;
                piece = pieceToCheck;
            }
            
            FunCallHelper();
        }
}

void GameScreenWithAI::FunCallHelper()
{
    float delay = 1.0f;
    this->scheduleOnce(schedule_selector(GameScreenWithAI::winningPopUp), delay);
}


void GameScreenWithAI::winningPopUp(float dt)
{

    gm1->popUpAfterGame(this, piece, GAMESCREENWITHAI);

}

