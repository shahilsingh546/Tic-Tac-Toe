
#ifndef HeaderLayer_hpp
#define HeaderLayer_hpp

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"


USING_NS_CC;

class HeaderLayer : public cocos2d::Layer
{
public:
    
    HeaderLayer();
    HeaderLayer(std::string s,int n);
    
    static cocos2d::Layer* createLayer();

    virtual bool init();
    virtual void onEnter();
    
    CREATE_FUNC(HeaderLayer);
    
    //Store Header Title***************************************
    std::string title;
    //Store Scene Number to identify Scenes*******************************
    int sceneNum;

    void ContBtnClicked(Ref* pSender);
    void backBtnClicked(Ref *pSender);
    
    static HeaderLayer* myCreate(std::string s,int n);
    
    //Redio buttons****************************************
    cocos2d::ui::RadioButton* rd1;
    cocos2d::ui::RadioButton* rd2;
    
};

#endif /* HeaderLayer_hpp */

