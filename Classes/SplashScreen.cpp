/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "SplashScreen.hpp"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "Scene2.hpp"
#include<iostream>
#include<vector>
#include "cocos2d.h"
#include "Path.h"
#include "AppDelegate.h"

using namespace std;

USING_NS_CC;

Scene* SplashScreen::createScene()
{
    return SplashScreen::create();
}


// on "init" you need to initialize your instance
bool SplashScreen::init()
{
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Adding background to the scene***********************************
    Sprite *bg = Sprite::create(BACKGROUND);
    bg->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    bg->setContentSize(Size(visibleSize.width,visibleSize.height));
    this->addChild(bg);
    
    
    
    //creating a layer #baseLayer and adding into the scene*************************************
    auto baseLayer =  Layer::create();
    baseLayer->setAnchorPoint(Vec2(0.5,0.5));
    baseLayer->setContentSize(visibleSize);
    bg->addChild(baseLayer);
    
    
    
    //Adding octro logo into #baseLayer*************************************
    auto logo = Sprite::create(OCTRO_LOGO);
    logo->setAnchorPoint(Vec2(0.5,0.5));
    logo->setScale(1.5);
    logo->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    baseLayer->addChild(logo,1);
    baseLayer->setOpacity(255);
    
    
    
    
    
    //Adding Loading bar into #baseLayer***********************************
    auto loadingBar = Sprite::create(LOADING_BAR);
    loadingBar->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/4+origin.y));
    loadingBar->setScale(0.8);
    bg->addChild(loadingBar);
    
    auto loadingHover = cocos2d::ui::LoadingBar::create(LOADING_BAR_HOVER);
    loadingHover->setDirection(cocos2d::ui::LoadingBar::Direction::LEFT);
    loadingHover->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/4+origin.y));
    loadingHover->setScale(0.8);
    bg->addChild(loadingHover);
    
    
    
    //Adding Label under the Loading Bar**************************************
    auto loadingLabel = Label::createWithTTF("Loading "+std::to_string(0)+"%..", "fonts/Marker Felt.ttf", 36);
    loadingLabel->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/4+origin.y-loadingBar->getContentSize().height*1.5));
    baseLayer->addChild(loadingLabel,4);
    
    
    
    //Code to fill Loading Bar wrt X sec*****************************************
    this->schedule([=](float delta=0.5){
            int percent = loadingHover->getPercent();
            percent+=2;
            loadingHover->setPercent(percent);
        loadingLabel->setString("Loading "+std::to_string(percent)+"%..");
            if (percent>=100) {
                this->unschedule("updateLoadingBar");
                //Moving Scene 2 after X sec***********************************
                this->schedule(schedule_selector(SplashScreen::moveToScene2), delta);
            }
        }, 0.1f, "updateLoadingBar");
    
    
    
    //Adding animation sprite into the #baseLayer ********************************
//    auto anim = Sprite::create("res/resources part1/anim_images/monophy-0.png");
//    anim->setAnchorPoint(Vec2(0.5,0.5));
//    anim->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
//    baseLayer->addChild(anim,0);
    
    
        //Used to Load pList file**************************************
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/resources part1/spriteSheet2.plist");
    
        //frames vector to store spriteFrames from spriteSheet*************************************
    Vector<SpriteFrame*> frames;
    
    
        //loop to push all png frames***************************************
    for (int i = 0; i < 125; i++)
    {
        std::string frame = "res/resources part1/anim_images/monophy-"+std::to_string(i)+".png";
        auto s = Sprite::create(frame);
        frames.pushBack(s->getSpriteFrame());
    }
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
    Animate* animate = Animate::create(animation);
    
        // run it and repeat it forever
//    anim->runAction(RepeatForever::create(animate));
    
    
    
    
    
    
    
//    Adding audio***************************************************************
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->preloadBackgroundMusic("res/Audio/mainMusic.mp3");
    audio->playBackgroundMusic("res/Audio/mainMusic.mp3",true);
    audio->setBackgroundMusicVolume(0.22);
    
    if(AppDelegate::getStore()->ud->getStringForKey("Sound") == "res/soundOff.png")
    {
        audio->pauseBackgroundMusic();
    }

    return true;

    
}



// moveToScene2 Function move to Scene2**************************************************

void SplashScreen::moveToScene2(float ft)
{
    auto scene = Scene2::createScene();
    TransitionFade *transition = TransitionFade::create( 2.0f, scene );
    Director::getInstance()->replaceScene(transition);

}

