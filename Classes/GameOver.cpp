#include "cocos2d.h"
#include "GameOver.hpp"
#include "GameScreenWithAI.hpp"
#include "playWithAI.hpp"
#include "GameScreenWithFriend.hpp"
#include "playWithFriend.hpp"
#include "Scene2.hpp"
#include "Settings.hpp"
#include "Simulation.hpp"
#include "Path.h"
#include "ui/CocosGUI.h"


int sceneNo = -1;
cocos2d::Sprite* bg;
GameOver::GameOver(cocos2d::Scene* scene)
{
    
}


void GameOver::popUpAfterGame(cocos2d::Scene* scene,int piece,int n)
{
    sceneNo = n;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    bg = Sprite::create(PopUpBackground);
    bg->setContentSize(Size(visibleSize.width*0.98,visibleSize.height*0.5));
    bg->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    scene->addChild(bg);
    
    auto seq = Sequence::create(DelayTime::create(2.0f),FadeIn::create(2.0f), NULL);
    bg->runAction(seq);
    
    
    
    std::string winningMsg="";
    if(piece == X_PIECE)
        winningMsg = "X Won!!";
    else if(piece == O_PIECE)
        winningMsg = "O Won!!";
    else
        winningMsg = "Match Drawn!!";
    
    
    auto label = Label::createWithTTF(winningMsg,"fonts/arial.ttf",40);
    label->setPosition(Vec2(bg->getPosition()));
//    label->setScale(label->getContentSize().width*0.03, label->getContentSize().height*0.05);
    label->enableBold();
    label->enableItalics();
    label->setColor(Color3B(34, 139, 230));
    scene->addChild(label);
    
    
    auto settingSprite = Sprite::create(RETRY_SPRITE);
    MenuItemSprite *settingItem = MenuItemSprite::create( settingSprite, settingSprite, settingSprite, CC_CALLBACK_1( GameOver::Retry, this ) );
    settingItem->setPosition(Vec2(label->getPositionX()*1.2,label->getPositionY()*0.8));
    settingItem->setScale(0.6);
    
    auto homeSprite = Sprite::create(HOME_SPRITE);
    MenuItemSprite *homeItem = MenuItemSprite::create( homeSprite, homeSprite, homeSprite, CC_CALLBACK_1( GameOver::Home, this ) );
    homeItem->setPosition(Vec2(label->getPositionX()*0.7,label->getPositionY()*0.8));
    homeItem->setScale(0.6);
    
    Menu *menu = Menu::create(settingItem, homeItem, NULL );
    menu->setPosition( Vec2(15,0));
    scene->addChild(menu);
    
    touchHandling();
 
}


void GameOver::touchHandling(){
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    // trigger when you push down
    listener1->onTouchBegan = [=](Touch* touch, Event* event){
//        Sprite* target = static_cast<Sprite*>(event->getCurrentTarget());
//        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());



        return true; // if you are consuming it
    };
    // trigger when you let up
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        // your code
    };

    // Add listener
    auto _eventDispatcher = Director::getInstance()->getEventDispatcher();
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, bg);
}



void GameOver::Home(cocos2d::Ref *pSender)
{
    Scene *scene = Scene2::createScene( );
    TransitionFade *transition = TransitionFade::create( 1.0f, scene );
        
    Director::getInstance( )->replaceScene( transition );
}

void GameOver::Retry(cocos2d::Ref *pSender)
{
    Scene *scene;
    if(sceneNo == GAMESCREENWITHAI)
    {
        scene = playWithAI::createScene();
    }
    else if(sceneNo == GAMESCREENWITHFRIEND)
    {
        scene = playWithFriend::createScene();
    }
    else if(sceneNo == SIMULATION)
    {
        scene = Settings::createScene();
    }
    TransitionFade *transition = TransitionFade::create( 1.0f, scene );
        
    Director::getInstance( )->replaceScene( transition );
}
