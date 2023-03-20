
#include "playWithFriend.hpp"
#include "SplashScreen.hpp"
#include "SimpleAudioEngine.h"
#include "Scene2.hpp"
#include "ui/CocosGUI.h"
#include "AppDelegate.h"
#include "HeaderLayer.hpp"
#include "GameScreenWithAI.hpp"
#include "GameScreenWithFriend.hpp"
#include "Path.h"

USING_NS_CC;

Scene* playWithFriend::createScene()
{
    return playWithFriend::create();
}


bool playWithFriend::init()
{
    if(!Scene::init())
        return false;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    //Adding Background sprite into the scene*****************************************************
    auto bg = Sprite::create("res/resources part1/bg_portrait1.png");
    bg->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    bg->setContentSize(Size(visibleSize.width,visibleSize.height));
    this->addChild(bg,0);
    
    
    //Adding HeaderLayer for header bg and text*****************************************
    Layer* layer = HeaderLayer::myCreate("Play With Friend",PLAYWITHFRIEND);
    bg->addChild(layer);

    return true;
    
}
