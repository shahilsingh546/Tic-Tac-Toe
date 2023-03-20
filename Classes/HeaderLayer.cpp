
#include "HeaderLayer.hpp"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "Scene2.hpp"
#include "playWithAI.hpp"
#include "playWithFriend.hpp"
#include "GameScreenWithAI.hpp"
#include "GameScreenWithFriend.hpp"
#include "Simulation.hpp"
#include "Path.h"
#include <iostream>


Layer* HeaderLayer::createLayer()
{
    return HeaderLayer::create();
}

HeaderLayer* HeaderLayer::myCreate(std::string s,int n){
    
    HeaderLayer* prt = new (std::nothrow) HeaderLayer(s,n);
    if(prt && prt->init()){
        prt->autorelease();
    }else{
        delete prt;
        prt = NULL;
    }
    return prt;
}

HeaderLayer::HeaderLayer()
{
    
}

HeaderLayer::HeaderLayer(std::string s,int n)
{
    title = s;
    sceneNum =n;
}

bool HeaderLayer::init()
{
    if(!Layer::init())
        return false;
    
    
    return true;
}

void HeaderLayer::onEnter()
{
    Layer::onEnter();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    //Adding header bg**********************************************************************
    
    auto header = Sprite::create(HEADER_BACKGROUND);
    header->setAnchorPoint(Vec2(0.5,1));
    header->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height+origin.y));
    header->setContentSize(Size(visibleSize.width, visibleSize.height*0.1));
    this->addChild(header,1);
    
    
    
    //Adding header text*******************************************************************
    
    auto headerText = this->title;
    auto headerLabel = Label::createWithTTF(headerText, "fonts/Marker Felt.ttf", 45);
    headerLabel->setPosition(Vec2(header->getContentSize().width*0.5f,header->getContentSize().height*0.5));
    headerLabel->setColor(Color3B::YELLOW);
    headerLabel->enableItalics();
    header->addChild(headerLabel);
    
    
    
    //AAdding Back button************************************************
    cocos2d::ui::Button* backButton = cocos2d::ui::Button::create(BACK_BUTTON_SPRITE);
    backButton->setAnchorPoint(Vec2(0,0.5));
    backButton->setPosition(Vec2(0, header->getContentSize().height*0.5f));
    backButton->setScale(0.6);
    backButton->addTouchEventListener(CC_CALLBACK_1(HeaderLayer::backBtnClicked,this));
    backButton->setTouchEnabled(true);
    header->addChild(backButton);
    
    
    if(sceneNum == PLAYWITHAI || sceneNum == PLAYWITHFRIEND)
    {
        //Adding label below header*************************************
        
        auto choosePlayerLabel = Label::createWithSystemFont("Choose Your Player", "fonts/Marker Felt.ttf", 45);
        choosePlayerLabel->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/1.3+origin.y));
        choosePlayerLabel->setColor(Color3B::WHITE);
        choosePlayerLabel->enableItalics();
        this->addChild(choosePlayerLabel);
        
        
        
        //Adding players into the scene*****************************

            //Adding player #p1*******************
        auto p1 = Sprite::create(PLAYER1);
        p1->setPosition(Vec2(choosePlayerLabel->getPositionX()*0.5,choosePlayerLabel->getPositionY()-choosePlayerLabel->getContentSize().height*3));
        this->addChild(p1);

            //Adding player #p2*******************
        auto p2 = Sprite::create(PLAYER2);
        p2->setPosition(Vec2(choosePlayerLabel->getPositionX()*1.5,choosePlayerLabel->getPositionY()-choosePlayerLabel->getContentSize().height*3));
        this->addChild(p2);
        
        
        
        
            //Rd1****************
        rd1 = ui::RadioButton::create(RADIO_BTN_DESELECTED,RADIO_BTN_SELECTED,RADIO_BTN_SELECTED,RADIO_BTN_DESELECTED,RADIO_BTN_DESELECTED);
        rd1->setPosition(Vec2(p1->getPositionX(),p1->getPositionY()-p1->getContentSize().height));
        rd1->setScale(0.6);

        
            //Rd2****************
        rd2 =  ui::RadioButton::create(RADIO_BTN_DESELECTED,RADIO_BTN_SELECTED,RADIO_BTN_SELECTED,RADIO_BTN_DESELECTED,RADIO_BTN_DESELECTED);
        rd2->setPosition(Vec2(p2->getPositionX(),p1->getPositionY()-p1->getContentSize().height));
        rd2->setScale(0.6);

        
        //Creating Radiogroup for adding RadioButtons******************************
        auto radioGroup = ui::RadioButtonGroup::create();
        radioGroup->setPosition(Vec2(0,0));
        radioGroup->addChild(rd1);
        radioGroup->addChild(rd2);
        radioGroup->addRadioButton(rd1);
        radioGroup->addRadioButton(rd2);
        this->addChild(radioGroup);
        
        
        
        
        cocos2d::ui::Button* circle = cocos2d::ui::Button::create("maincircle.png");
        circle->setPosition(Vec2(visibleSize.width*0.5,rd1->getPositionY()-rd1->getContentSize().height*1.5));
        circle->setScale(1);
//        circle->setTitleText("Continue");
        circle->setTitleFontName("arial");
        circle->setTitleFontSize(45);
        circle->setTitleColor(Color3B::BLACK);
        circle->addTouchEventListener(CC_CALLBACK_1(HeaderLayer::ContBtnClicked,this));
        this->addChild(circle);
        
        cocos2d::ui::Button* strip = cocos2d::ui::Button::create("mainprof.png");
        strip->setAnchorPoint(Vec2(1,0.5));
//        strip->setRotation(180);
        strip->setPosition(Vec2(circle->getContentSize().width*0.19f,circle->getContentSize().height*0.5f));
        strip->setScale(1);
//        strip->setTitleText("Continue");
        strip->setTitleFontName("arial");
        strip->setTitleFontSize(45);
        strip->setTitleColor(Color3B::BLACK);
        strip->addTouchEventListener(CC_CALLBACK_1(HeaderLayer::ContBtnClicked,this));
        circle->addChild(strip);

    }
  
}


void HeaderLayer::ContBtnClicked(Ref* pSender)
{
    cocos2d::Scene* scene;
    if(sceneNum == PLAYWITHAI)
    {
        scene = GameScreenWithAI::createScene(rd1,rd2);
    }
    else
    {
        scene = GameScreenWithFriend::createScene(rd1,rd2);
    }
    TransitionFade *transition = TransitionFade::create( 1.0f, scene );
    Director::getInstance()->replaceScene(transition);
}


void HeaderLayer::backBtnClicked(Ref* pSender)
{
    cocos2d::Scene* scene;
    if((title == "Play With AI" || title == "Play With Friend" || title == "Settings") && (sceneNum == PLAYWITHAI || sceneNum == PLAYWITHFRIEND || sceneNum == SETTINGS))
    {
        scene = Scene2::createScene();
    }
    
    else if(title == "Play With AI" && sceneNum == GAMESCREENWITHAI)
    {
        scene = playWithAI::createScene();
    }
    
    else if(title == "Play With Friend" && sceneNum == GAMESCREENWITHFRIEND)
    {
        scene = playWithFriend::createScene();
    }
    
    else if(sceneNum == SIMULATION)
    {
        scene = Settings::createScene();
    }
    TransitionFade *transition = TransitionFade::create( 1.0f, scene );
    Director::getInstance()->replaceScene(transition);
    
}
