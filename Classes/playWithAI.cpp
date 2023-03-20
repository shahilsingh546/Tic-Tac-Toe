#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "playWithAI.hpp"
#include "GameScreenWithAI.hpp"
#include "Scene2.hpp"
#include "HeaderLayer.hpp"
#include "AppDelegate.h"
#include "Path.h"

USING_NS_CC;

Scene* playWithAI::createScene()
{
    return playWithAI::create();
}


bool playWithAI::init()
{
    if(!Scene::init())
        return false;
    
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    
    //Adding Background sprite into the scene*****************************************************
    auto bg = Sprite::create(BACKGROUND);
    bg->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    bg->setContentSize(Size(visibleSize.width,visibleSize.height));
    this->addChild(bg);
    
 
    //Adding HeaderLayer for header bg and text*****************************************
    
    HeaderLayer* layer = HeaderLayer::myCreate("Play With AI",PLAYWITHAI);
    bg->addChild(layer);


    return true;
    
}
