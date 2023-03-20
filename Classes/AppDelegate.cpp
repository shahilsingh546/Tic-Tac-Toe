/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copyVec
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

#include "AppDelegate.h"
#include "SplashScreen.hpp"
#include "cocos2d.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif
#include <iostream>
using namespace std;

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);




AppDelegate* AppDelegate::store = nullptr;

AppDelegate::AppDelegate()
{
    labelrecords.push_back("Sound");
    for(int i=1;i<=10;i++)
    {
        labelrecords.push_back("GamePlay "+std::to_string(i)) ;
    }
    store = this;
}

AppDelegate* AppDelegate::getStore(){
    return store;
}



AppDelegate::~AppDelegate()
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    //creating userDefault**********************************
    ud = cocos2d::UserDefault::getInstance();
    
    //Retriveing Game Data********************************
    RetrievingData();
    
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("DemoProj", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("DemoProj");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);
//    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    /*if (frameSize.height > mediumResolutionSize.height)
    {
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }*/

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = SplashScreen::createScene();

    // run
    director->runWithScene(scene);
    
    

    return true;
}


void AppDelegate::StoringData()
{
    
    //Storing MoveRecords**************************
    for(int i=0;i<AppDelegate::getStore()->MoveRecords.size();i++)
    {
        string s="";
        for(int j=0;j<AppDelegate::getStore()->MoveRecords[i].size();j++)
        {
            string s1 = to_string(AppDelegate::getStore()->MoveRecords[i][j].first);
            string s2 = to_string(AppDelegate::getStore()->MoveRecords[i][j].second);
            s += s1 + s2;
        }
        if(i==0)
        {
            ud->setStringForKey("GamePlay1", s);
            ud->setIntegerForKey("startPiece1", startPiece[i]);
            ud->setStringForKey("header1", headerStr[i]);
        }
        if(i==1)
        {
            ud->setStringForKey("GamePlay2", s);
            ud->setIntegerForKey("startPiece2", startPiece[i]);
            ud->setStringForKey("header2", headerStr[i]);
        }
        if(i==2)
        {
            ud->setStringForKey("GamePlay3", s);
            ud->setIntegerForKey("startPiece3", startPiece[i]);
            ud->setStringForKey("header3", headerStr[i]);
        }
        if(i==3)
        {
            ud->setStringForKey("GamePlay4", s);
            ud->setIntegerForKey("startPiece4", startPiece[i]);
            ud->setStringForKey("header4", headerStr[i]);
        }
        if(i==4)
        {
            ud->setStringForKey("GamePlay5", s);
            ud->setIntegerForKey("startPiece5", startPiece[i]);
            ud->setStringForKey("header5", headerStr[i]);
        }
        if(i==5)
        {
            ud->setStringForKey("GamePlay6", s);
            ud->setIntegerForKey("startPiece6", startPiece[i]);
            ud->setStringForKey("header6", headerStr[i]);
        }
        if(i==6)
        {
            ud->setStringForKey("GamePlay7", s);
            ud->setIntegerForKey("startPiece7", startPiece[i]);
            ud->setStringForKey("header7", headerStr[i]);
        }
        if(i==7)
        {
            ud->setStringForKey("GamePlay8", s);
            ud->setIntegerForKey("startPiece8", startPiece[i]);
            ud->setStringForKey("header8", headerStr[i]);
        }
        if(i==8)
        {
            ud->setStringForKey("GamePlay9", s);
            ud->setIntegerForKey("startPiece9", startPiece[i]);
            ud->setStringForKey("header9", headerStr[i]);
        }
        if(i==9)
        {
            ud->setStringForKey("GamePlay10", s);
            ud->setIntegerForKey("startPiece10", startPiece[i]);
            ud->setStringForKey("header10", headerStr[i]);
        }
        
    }
    ud->setIntegerForKey("MoveRecordsSize", (int)AppDelegate::getStore()->MoveRecords.size());
    
    
    //Storing startPiece******************
}

void AppDelegate::RetrievingData()
{
    int n = ud->getIntegerForKey("MoveRecordsSize");
    for(int i=0;i<n;i++)
    {
        string pos="";
        vector<pair<int,int>> temp;
        if(i==0)
        {
            pos = ud->getStringForKey("GamePlay1");
            startPiece.push_back(ud->getIntegerForKey("startPiece1"));
            headerStr.push_back((ud->getStringForKey("header1")));
        }
        if(i==1)
        {
            pos = ud->getStringForKey("GamePlay2");
            startPiece.push_back(ud->getIntegerForKey("startPiece2"));
            headerStr.push_back((ud->getStringForKey("header2")));
        }
        if(i==2)
        {
            pos = ud->getStringForKey("GamePlay3");
            startPiece.push_back(ud->getIntegerForKey("startPiece3"));
            headerStr.push_back((ud->getStringForKey("header3")));
        }
        if(i==3)
        {
            pos = ud->getStringForKey("GamePlay4");
            startPiece.push_back(ud->getIntegerForKey("startPiece4"));
            headerStr.push_back((ud->getStringForKey("header4")));
        }
        if(i==4)
        {
            pos = ud->getStringForKey("GamePlay5");
            startPiece.push_back(ud->getIntegerForKey("startPiece5"));
            headerStr.push_back((ud->getStringForKey("header5")));
        }
        if(i==5)
        {
            pos = ud->getStringForKey("GamePlay6");
            startPiece.push_back(ud->getIntegerForKey("startPiece6"));
            headerStr.push_back((ud->getStringForKey("header6")));
        }
        if(i==6)
        {
            pos = ud->getStringForKey("GamePlay7");
            startPiece.push_back(ud->getIntegerForKey("startPiece7"));
            headerStr.push_back((ud->getStringForKey("header7")));
        }
        if(i==7)
        {
            pos = ud->getStringForKey("GamePlay8");
            startPiece.push_back(ud->getIntegerForKey("startPiece8"));
            headerStr.push_back((ud->getStringForKey("header8")));
        }
        if(i==8)
        {
            pos = ud->getStringForKey("GamePlay9");
            startPiece.push_back(ud->getIntegerForKey("startPiece9"));
            headerStr.push_back((ud->getStringForKey("header9")));
        }
        if(i==9)
        {
            pos = ud->getStringForKey("GamePlay10");
            startPiece.push_back(ud->getIntegerForKey("startPiece10"));
            headerStr.push_back((ud->getStringForKey("header10")));
        }
        for(int j=0;j<pos.length();j+=2)
        {
            temp.push_back({pos[j]-'0',pos[j+1]-'0'});
        }
        MoveRecords.push_back(temp);
        temp.clear();
    }
}



// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}

