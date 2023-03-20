
#include "AI.hpp"
#include "cocos2d.h"
#include "Path.h"
#include <iostream>
#include <vector>
#include "AppDelegate.h"
#include "GameScreenWithAI.hpp"


std::string x_sprite = "res/resources part3/p1.png";
std::string o_sprite = "res/resources part3/p2.png";

using namespace std;

AI::AI(int playerPiece)
{
    this->playerPiece = playerPiece;
    
    if(playerPiece == X_PIECE)
    {
        aiPiece = O_PIECE;
    }
    else
    {
        aiPiece = X_PIECE;
    }
    
    
        checkMatchVector.push_back( { 0, 2, 1, 2, 2, 2 } );
        checkMatchVector.push_back( { 0, 2, 0, 1, 0, 0 } );
        checkMatchVector.push_back( { 0, 2, 1, 1, 2, 0 } );
        checkMatchVector.push_back( { 2, 2, 1, 2, 0, 2 } );
        checkMatchVector.push_back( { 2, 2, 2, 1, 2, 0 } );
        checkMatchVector.push_back( { 2, 2, 1, 1, 0, 0 } );
        checkMatchVector.push_back( { 0, 0, 0, 1, 0, 2 } );
        checkMatchVector.push_back( { 0, 0, 1, 0, 2, 0 } );
        checkMatchVector.push_back( { 0, 0, 1, 1, 2, 2 } );
        checkMatchVector.push_back( { 2, 0, 2, 1, 2, 2 } );
        checkMatchVector.push_back( { 2, 0, 1, 0, 0, 0 } );
        checkMatchVector.push_back( { 2, 0, 1, 1, 0, 2 } );
        checkMatchVector.push_back( { 0, 1, 1, 1, 2, 1 } );
        checkMatchVector.push_back( { 1, 2, 1, 1, 1, 0 } );
        checkMatchVector.push_back( { 2, 1, 1, 1, 0, 1 } );
        checkMatchVector.push_back( { 1, 0, 1, 1, 1, 2 } );
        checkMatchVector.push_back( { 0, 1, 2, 1, 1, 1 } );
        checkMatchVector.push_back( { 1, 2, 1, 0, 1, 1 } );
        checkMatchVector.push_back( { 0, 2, 2, 0, 1, 1 } );
        checkMatchVector.push_back( { 2, 2, 0, 0, 1, 1 } );
        checkMatchVector.push_back( { 0, 2, 2, 2, 1, 2 } );
        checkMatchVector.push_back( { 0, 0, 2, 0, 1, 0 } );
        checkMatchVector.push_back( { 0, 2, 0, 0, 0, 1 } );
        checkMatchVector.push_back( { 2, 2, 2, 0, 2, 1 } );
    
}

void AI::PlacePiece(int (*gridArray)[3][3], cocos2d::Sprite *(*gridPieces)[3], int *gameState)
{
    
    try
        {
            // check if AI can win
            for ( int i = 0; i < checkMatchVector.size( ); i++ )
            {
                CheckSection( checkMatchVector[i][0], checkMatchVector[i][1], checkMatchVector[i][2], checkMatchVector[i][3], checkMatchVector[i][4], checkMatchVector[i][5], aiPiece, gridArray, gridPieces );
            }

            // check if player can win
            for ( int i = 0; i < checkMatchVector.size( ); i++ )
            {
                CheckSection( checkMatchVector[i][0], checkMatchVector[i][1], checkMatchVector[i][2], checkMatchVector[i][3], checkMatchVector[i][4], checkMatchVector[i][5], playerPiece, gridArray, gridPieces );
            }
        
    
            //Check for center*********
            CheckIfPieceIsEmpty(1, 1, gridArray, gridPieces);
            
            
            //Check for cornor********
            CheckIfPieceIsEmpty(0, 0, gridArray, gridPieces);
            CheckIfPieceIsEmpty(0, 2, gridArray, gridPieces);
            CheckIfPieceIsEmpty(2, 0, gridArray, gridPieces);
            CheckIfPieceIsEmpty(2, 2, gridArray, gridPieces);
            
            //Check for any Empty Pieces
            CheckIfPieceIsEmpty(0, 1, gridArray, gridPieces);
            CheckIfPieceIsEmpty(1, 0, gridArray, gridPieces);
            CheckIfPieceIsEmpty(1, 2, gridArray, gridPieces);
            CheckIfPieceIsEmpty(2, 1, gridArray, gridPieces);
            
        }
    
    catch(int error)
    {
        
    }
    
    *gameState = STATE_PLAYING;
    
}

void AI::CheckSection( int x1, int y1, int x2, int y2, int x, int y, int pieceToCheck, int ( *gridArray )[3][3], cocos2d::Sprite *gridPieces[3][3] )
{
    if ( ( *gridArray )[x1][y1] == pieceToCheck && ( *gridArray )[x2][y2] == pieceToCheck )
    {
        if ( EMPTY == ( *gridArray )[x][y] )
        {
            AppDelegate::getStore()->positions.push_back({x,y});
//            cout<<x<<" "<<y<<endl;
            
            ( *gridArray )[x][y] = aiPiece;
            
            if(aiPiece == X_PIECE)
                gridPieces[x][y]->setTexture(x_sprite);
            
            else
                gridPieces[x][y]->setTexture(o_sprite);
            
            gridPieces[x][y]->setVisible( true );
            
            gridPieces[x][y]->runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(0.5f),cocos2d::FadeIn::create( 0.5f ), nullptr) );

            throw -1;
        }
    }
}

void AI::CheckIfPieceIsEmpty( int x, int y, int ( *gridArray )[3][3], cocos2d::Sprite *gridPieces[3][3] )
{
    // check if
    if ( EMPTY == ( *gridArray )[x][y] )
    {
        AppDelegate::getStore()->positions.push_back({x,y});
//        cout<<x<<" "<<y<<endl;
        
        ( *gridArray )[x][y] = aiPiece;
        
        if(aiPiece == X_PIECE)
            gridPieces[x][y]->setTexture(x_sprite);
        
        else
            gridPieces[x][y]->setTexture(o_sprite);
        
        gridPieces[x][y]->setVisible( true );
        
        gridPieces[x][y]->runAction( cocos2d::Sequence::create(cocos2d::DelayTime::create(0.5f),cocos2d::FadeIn::create( 0.5f ), nullptr) );
//        GameScreenWithAI::check = true;
        
        throw -2;
    }
}
