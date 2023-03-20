#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "Scene2.hpp"
#include "playWithAI.hpp"
#include "playWithFriend.hpp"
#include "Settings.hpp"
#include "AppDelegate.h"
#include "Path.h"

USING_NS_CC;


Scene* Scene2::createScene()
{
    return Scene2::create();
}


bool Scene2::init()
{
    if(!Scene::init())
        return false;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    
    //Adding Background sprite into the scene*****************************************************
    Sprite *bg = Sprite::create(BACKGROUND);
    bg->setContentSize(visibleSize);
    bg->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    this->addChild(bg,0);
    
    
    
    //creating and adding #layer2 into scene2***************************************
    auto layer2 =  Layer::create();
    layer2->setAnchorPoint(Vec2(0.5,0.5));
    layer2->setContentSize(visibleSize);
    bg->addChild(layer2);
    
    
    
    //Adding text and logo on top centre of the layer*****************************
    
        //Adding text into the layer*********
    auto text = Sprite::create(TIC_TAC_TOE_TEXT);
    text->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height+text->getContentSize().height/1.5));
    text->setContentSize(Size(bg->getContentSize().width*0.90,bg->getContentSize().height*0.10));
    layer2->addChild(text,3);
    auto moveText = MoveTo::create(2,Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height-text->getContentSize().height));
    
    
    
        //Adding logo into the layer********
    auto logo = Sprite::create(TIC_TAC_TOE_LOGO);
    logo->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height+text->getContentSize().height));
    logo->setScale(0.5);
    layer2->addChild(logo,4);
    auto moveLogo = MoveTo::create(1.5,Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height-(logo->getContentSize().height/2+text->getContentSize().height)));
    
    auto bounce1 = JumpTo::create(0.6, Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height-(logo->getContentSize().height/2+text->getContentSize().height)), logo->getContentSize().height/3, 1);
    
    auto bounce2 = JumpTo::create(0.6, Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height-(logo->getContentSize().height/2+text->getContentSize().height)), logo->getContentSize().height/3.6, 1);
                                 
    
    
    //logo_text and Logo action*******************************
    text->runAction(moveText);
    
    auto delay = DelayTime::create(1);
    
    auto seqforLogo = Sequence::create(delay, moveLogo, bounce1, bounce2, NULL);
    
    logo->runAction(seqforLogo);
    
    
    
    
    //Adding label into the #layer2***********************************
    auto chooseLabel = Label::createWithSystemFont("Choose your play mode", "fonts/Marker Felt.ttf", 45);
    chooseLabel->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/1.6+origin.y));
    chooseLabel->enableBold();
    chooseLabel->setColor(Color3B::YELLOW);
    chooseLabel->enableItalics();
    bg->addChild(chooseLabel,5);

    
    
    //playWithAI Button*******************************
    cocos2d::ui::Button* playWithAIButton = cocos2d::ui::Button::create(BUTTON_SPRITE);
    playWithAIButton->setPosition(Vec2(chooseLabel->getPositionX(),chooseLabel->getPositionY()-chooseLabel->getContentSize().height*2));
    playWithAIButton->setTitleText("Play With AI");
    playWithAIButton->setTitleFontName("arial");
    playWithAIButton->setTitleFontSize(36);
    playWithAIButton->setTitleColor(Color3B::BLACK);
    playWithAIButton->addTouchEventListener(CC_CALLBACK_1(Scene2::playWithAIBtnClicked,this));
    bg->addChild(playWithAIButton);
    

    
    
    //playWithFriend Button*******************************
    cocos2d::ui::Button* playWithFriendBtn = cocos2d::ui::Button::create(BUTTON_SPRITE);
    playWithFriendBtn->setPosition(Vec2(playWithAIButton->getPositionX(),playWithAIButton->getPositionY()-playWithAIButton->getContentSize().height*1.2));
    playWithFriendBtn->setTitleText("Play With Friend");
    playWithFriendBtn->setTitleFontName("arial");
    playWithFriendBtn->setTitleFontSize(36);
    playWithFriendBtn->setTitleColor(Color3B::BLACK);
    playWithFriendBtn->addTouchEventListener(CC_CALLBACK_1(Scene2::playWithFriendBtnClicked,this));
    bg->addChild(playWithFriendBtn);
    
    
    
    //Settings Button************************************
    cocos2d::ui::Button* SettingBtn = cocos2d::ui::Button::create(BUTTON_SPRITE);
    SettingBtn->setPosition(Vec2(playWithFriendBtn->getPositionX(),playWithFriendBtn->getPositionY()-playWithFriendBtn->getContentSize().height*1.2));
    SettingBtn->setTitleText("Settings");
    SettingBtn->setTitleFontName("arial");
    SettingBtn->setTitleFontSize(36);
    SettingBtn->setTitleColor(Color3B::BLACK);
    SettingBtn->addTouchEventListener(CC_CALLBACK_1(Scene2::SettingsBtnClicked,this));
    bg->addChild(SettingBtn);
    
    
    //Setting Icon on top of Setting Button******************************
    auto settingSprite = Sprite::create(SETTING_LOGO);
    settingSprite->setPosition(Vec2(SettingBtn->getPositionX()-120,SettingBtn->getPositionY()));
    settingSprite->setScale(0.15);
    this->addChild(settingSprite);
    
    
    
    //Quit Button*************************************
    cocos2d::ui::Button* quitBtn = cocos2d::ui::Button::create(BUTTON_SPRITE);
    quitBtn->setPosition(Vec2(SettingBtn->getPositionX(),SettingBtn->getPositionY()-SettingBtn->getContentSize().height*1.2));
    quitBtn->setTitleText("Quit");
    quitBtn->setTitleFontName("arial");
    quitBtn->setTitleFontSize(36);
    quitBtn->setTitleColor(Color3B::BLACK);
    quitBtn->addTouchEventListener(CC_CALLBACK_1(Scene2::QuitBtnClicked,this));
    bg->addChild(quitBtn);

    return true;
    
}


//playWithAI move to new Scene************************

void Scene2::playWithAIBtnClicked(Ref* pSender)
{
    auto scene = playWithAI::createScene();
    TransitionFade *transition = TransitionFade::create( 1.0f, scene );
    Director::getInstance()->pushScene(transition);
}


//playWithFriend move to new Scene************************

void Scene2::playWithFriendBtnClicked(Ref* pSender)
{
    auto scene = playWithFriend::createScene();
    TransitionFade *transition = TransitionFade::create( 1.0f, scene );
    Director::getInstance()->pushScene(transition);
}


//Settings move to new Scene****************************

void Scene2::SettingsBtnClicked(Ref* pSender)
{
    auto scene = Settings::createScene();
    TransitionFade *transition = TransitionFade::create( 1.0f, scene );
    Director::getInstance()->pushScene(transition);
}



void Scene2::QuitBtnClicked(Ref* pSender)
{
    Director::getInstance()->end();
}

