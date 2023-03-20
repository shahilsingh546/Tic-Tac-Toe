//
//  AI.hpp
//  DemoProj
//
//  Created by octro on 05/09/22.
//

#ifndef AI_hpp
#define AI_hpp

#include <stdio.h>
#include "cocos2d.h"
#include <vector>
#include <array>

class AI
{
public:
    AI( int playerPiece );
    
    void PlacePiece( int ( *gridArray )[3][3], cocos2d::Sprite *gridPieces[3][3], int *gameState );
    
private:
    void CheckSection( int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck, int ( *gridArray )[3][3], cocos2d::Sprite *gridPieces[3][3] );
    void CheckIfPieceIsEmpty( int x, int y, int ( *gridArray )[3][3], cocos2d::Sprite *gridPieces[3][3] );
    
    int aiPiece;
    int playerPiece;
    
    std::vector<std::array<int, 6>> checkMatchVector;

};

#endif /* AI_hpp */
