#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "playWithFriend.hpp"
#include "Settings.hpp"
#include "Scene2.hpp"
#include "AppDelegate.h"
#include "Path.h"
#include<iostream>
#include "HeaderLayer.hpp"
#include "GameScreenWithAI.hpp"
#include "GameScreenWithFriend.hpp"
#include "Simulation.hpp"
#include "extensions/GUI/CCScrollView/CCScrollView.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;


Scene* Settings::createScene()
{
    return Settings::create();
    
}


bool Settings::init()
{
    if(!Scene::init())
        return false;
    

    for(int i=0;i<10;i++)
    {
        temp[i]=i+1;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    

    
    //Adding Background sprite into the scene*****************************************************
    auto bg = Sprite::create(BACKGROUND);
    bg->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    bg->setContentSize(Size(visibleSize.width,visibleSize.height));
    this->addChild(bg);
    
    
    
    //Adding HeaderLayer for header bg and text*****************************************
    Layer* layer = HeaderLayer::myCreate("Settings",SETTINGS);
    bg->addChild(layer,100);
 
    
    
    //Adding profile Bg*****************************************
    Sprite* profilebg=Sprite::create("res/Loading-Circle.png");
    profilebg->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/1.3));
    profilebg->setScale(0.72);
    bg->addChild(profilebg);
    bg->setTag(10);
    
    
    //Setting Profile from stored data in user Default*****************************
    if(AppDelegate::getStore()->ud->getStringForKey("Profile Image") == "")
    {
        AppDelegate::getStore()->ud->setStringForKey("Profile Image", "res/resources part4/avtar0.png");
    }
    
    auto profile = Sprite::create(AppDelegate::getStore()->ud->getStringForKey("Profile Image"));
    profile->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/1.3));
    profile->setScale(2);
    
     //clipping profile************************************************
     auto profileStencil = DrawNode::create();
     float profileStencilRadius = profile->getBoundingBox().size.width * 0.5f;
     profileStencil->drawSolidCircle(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/1.3), profileStencilRadius, 0.0f, 32.0f, Color4F::GREEN);
    
     auto profileClipper = ClippingNode::create();
     profileClipper->setStencil(profileStencil);
     profileClipper->setTag(21);
     this->addChild(profileClipper);
     profileClipper->addChild(profile);
     profile->setTag(22);
    

    
    //Change Image button to change profile Image****************************************
    cocos2d::ui::Button* changeImage = cocos2d::ui::Button::create(BUTTON_SPRITE);
    changeImage->setPosition(Vec2(profilebg->getPositionX(),profilebg->getPositionY()-profilebg->getContentSize().height*0.5));
    changeImage->setScale(0.7);
    changeImage->setTitleText("Change Image");
    changeImage->setTitleFontName("arial");
    changeImage->setTitleFontSize(45);
    changeImage->setTitleColor(Color3B::BLACK);
    changeImage->addTouchEventListener(CC_CALLBACK_2(Settings::changeProfile,this));
    bg->addChild(changeImage);
    
    
    
    
    //bg on bottom for tableView************************************************
    auto bottomBg = Sprite::create(BACKGROUND2);
    bottomBg->setContentSize(Size(visibleSize.width,visibleSize.height/1.85));
    bottomBg->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/3.69));
    bg->addChild(bottomBg);
    

    
    //Creating Table View on bottom half of Settings scene********************************
    TableView* tableView = TableView::create(this,Size(bottomBg->getContentSize().width, bottomBg->getContentSize().height));
    tableView->setDelegate(this);
    tableView->setPosition(Vec2(0,0));
    tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
//    table->setDataSource(this);
    tableView->setVerticalFillOrder(cocos2d::extension::TableView::VerticalFillOrder::TOP_DOWN);
    bottomBg->addChild(tableView);
    tableView->reloadData();

    
    return true;
    
}



//PopUp Appear with images options in scrollView to Choose Image*******************************************************
void Settings::changeProfile(Ref* psender, cocos2d::ui::Widget::TouchEventType type){
    
    if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
        
    auto visibleSize=Director::getInstance()->getVisibleSize();
    auto origin=Director::getInstance()->getVisibleOrigin();
    
    
    //PopUp Layer**********************************
    IconsLayer =  Layer::create();
    IconsLayer->setAnchorPoint(Vec2(0.5,0.5));
    IconsLayer->setContentSize(Size(visibleSize.width*0.9,visibleSize.height*0.6));
    this->addChild(IconsLayer,0,50);
    
    // PopUp Background************************************
    Sprite *layerbg = Sprite::create(BACKGROUND2);
    layerbg->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
    layerbg->setContentSize(Size(visibleSize.width*0.9,visibleSize.height*0.6));
    IconsLayer->addChild(layerbg);
    
    //PopUp Header Background*********************************
    Sprite *SelectImageHeader = Sprite::create(HEADER_BACKGROUND);
    SelectImageHeader->setContentSize(Size(layerbg->getContentSize().width,layerbg->getContentSize().height*0.1));
    SelectImageHeader->setPosition(Vec2(layerbg->getContentSize().width/2,layerbg->getContentSize().height-SelectImageHeader->getContentSize().height*0.5f));
    layerbg->addChild(SelectImageHeader);
    
    //PopUp Header Text**********************************
    auto label1 = Label::createWithTTF("Choose Profile Image", "fonts/Marker Felt.ttf", 32);
    label1->setPosition(Vec2(SelectImageHeader->getContentSize().width*0.5,SelectImageHeader->getContentSize().height*0.5));
    label1->setColor(Color3B::YELLOW);
    label1->enableItalics();
    SelectImageHeader->addChild(label1);
    
    
    //Close Button of PopUp on top Right Corner ***********************************
    cocos2d::ui::Button* closeButton = cocos2d::ui::Button::create(CLOSE_ICON_SPRITE);
    closeButton->setScale(0.6);
    closeButton->setPosition(Vec2(SelectImageHeader->getContentSize().width/2+180,SelectImageHeader->getContentSize().height-label1->getContentSize().height*0.7f));
    closeButton->addTouchEventListener(CC_CALLBACK_0(Settings::closeChangeImagePopUp,this));
    SelectImageHeader->addChild(closeButton);

   
    
    //ScrollView on PopUp *************************************************
    Size scollFrameSize = Size(layerbg->getContentSize().width,layerbg->getContentSize().height-SelectImageHeader->getContentSize().height);
    scrollView = cocos2d::ui::ScrollView::create();
    scrollView->setContentSize(scollFrameSize);
    scrollView->setAnchorPoint(Vec2(0.5,0.5));
    scrollView->setPosition(Vec2(layerbg->getPositionX(),layerbg->getPositionY()-SelectImageHeader->getContentSize().height*0.5));
    scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
    scrollView->setSwallowTouches(true);
    scrollView->setScrollBarColor(Color3B::BLACK);
    scrollView->setScrollBarOpacity(100);
    scrollView->setClippingEnabled(true);
    auto containerSize = Size(scollFrameSize.width, scollFrameSize.height*2);
    scrollView->setInnerContainerSize(containerSize);
    IconsLayer->addChild(scrollView);

    
    //Loop to Add Images as MenuItemImage on scroll View*************************************************
    int idx=0;
    for(int i=0;i<=9;i++)
    {
//        auto litem=MenuItemImage::create("res/resources part4/avtar"+std::to_string(i)+".png","res/resources part4/avtar"+std::to_string(i)+".png",CC_CALLBACK_1(Settings::ImageClicked, this,i));
//        litem->setScale(1.3);
        auto litem = cocos2d::ui::Button::create("res/resources part4/avtar"+std::to_string(i)+".png");
        litem->setScale(1.3);
        litem->addTouchEventListener(CC_CALLBACK_1(Settings::ImageClicked, this,i));
        scrollView->addChild(litem);
        if(i%2==0)
        {
            litem->setPosition(Vec2(scrollView->getPositionX()*0.5, SelectImageHeader->getPositionY()*1.74-idx*170));
        }
        else
        {
            litem->setPosition(Vec2(scrollView->getPositionX()*1.3, SelectImageHeader->getPositionY()*1.74-idx*170));
            idx++;
        }
        
//        auto menu = Menu::create(litem,nullptr);
//        menu->setAnchorPoint(Vec2(0,0));
//        menu->setPosition(Vec2 :: ZERO);
//        scrollView->addChild(menu,i,"List"+std::to_string(i));
    }
        
         touchHandling();

    return;
    }
}


//Handling touch disable after change Image Pop Up***************************************
void Settings::touchHandling(){
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->setSwallowTouches(true);
    // trigger when you push down
    listener1->onTouchBegan = [=](Touch* touch, Event* event){
        Sprite* target = static_cast<Sprite*>(event->getCurrentTarget());
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());

        if(!IconsLayer->getBoundingBox().containsPoint(locationInNode))
        {
            listener1->setSwallowTouches(true);
        }
        return true; // if you are consuming it
    };
    // trigger when you let up
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        // your code
    };

    // Add listener
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, IconsLayer);
}


//Closing Change Image PopUp Layer********************
void Settings::closeChangeImagePopUp()
{
    if(IconsLayer)
    {
        IconsLayer->removeFromParent();
        IconsLayer = nullptr;
    }
}


//Handling Click On Images**************************************************
void Settings::ImageClicked(Ref *pSender, int i)
{
    std::cout<<"image "<<i;
    auto sc1=dynamic_cast<ClippingNode*>(this->getChildByTag(21));
          if(sc1){
        Sprite* sc2=dynamic_cast<Sprite*>(sc1->getChildByTag(22));
            if(sc2){
        sc2->setTexture("res/resources part4/avtar"+to_string(i)+".png");
        AppDelegate::getStore()->ud->setStringForKey("Profile Image", "res/resources part4/avtar"+to_string(i)+".png");
            }
          }
    Layer* temp=dynamic_cast<Layer*>(this->getChildByTag(50));
      if(temp){
        temp->removeFromParentAndCleanup(true);
      }
}



//TableViewDataSource
TableViewCell* Settings::tableCellAtIndex(TableView *table, ssize_t idx)
{
    TableViewCell *cell = table->dequeueCell();
    if(!cell){
        cell = new cocos2d::extension::TableViewCell();
        cell->autorelease();
    }else{
        cell->removeFromParentAndCleanup(true);
    }
    
    if(idx>10)
        idx=10;
    string labelstr = AppDelegate::getStore()->labelrecords[idx];
    
    cell = TableViewCell::create();

    
    Label* label = Label::createWithTTF(labelstr, "fonts/arial.ttf", 40);//Create Text label
    label->setTag (2);//create label for label, Tag 2
    label->setAnchorPoint (Point (0, 0));//Set the label's anchor
    label->setColor(Color3B::YELLOW);
    label->setPosition(Vec2(cell->getContentSize().width*0.5,cell->getContentSize().height*0.2f));
    cell->addChild (label);

    
    if(idx == 0)
    {
        if(AppDelegate::getStore()->ud->getStringForKey("Sound") == "")
        {
            AppDelegate::getStore()->ud->setStringForKey("Sound", "res/soundOn.png");
        }
       auto soundButton =cocos2d::ui::Button::create(AppDelegate::getStore()->ud->getStringForKey("Sound"));
       soundButton->addTouchEventListener(CC_CALLBACK_2(Settings::changeAudio,this));
       soundButton->setPosition(Vec2(label->getPositionX()+label->getContentSize().width*3.5,label->getPositionY()+15));
       soundButton->setTag(101);
       cell->addChild(soundButton);
    }

    return cell;
   
}


//Adding touch event listener on sound button********************************************
bool flag=true;
void Settings::changeAudio(Ref* pSender,cocos2d::ui::Widget::TouchEventType type)
{
    if(AppDelegate::getStore()->ud->getStringForKey("Sound") == "res/soundOn.png")
        flag =false;
    if(type == cocos2d::ui::Widget::TouchEventType::ENDED){
            cocos2d::ui::Button* btn = (cocos2d::ui::Button*)(pSender);
            if(flag){
                btn->loadTextureNormal("res/soundOn.png");
                AppDelegate::getStore()->ud->setStringForKey("Sound", "res/soundOn.png");
                resumeMusic(0);
            }
            else{
                btn->loadTextureNormal("res/soundOff.png");
                AppDelegate::getStore()->ud->setStringForKey("Sound", "res/soundOff.png");
                pauseMusic(0);
            }
            flag = !flag;
        }
        return ;
}


//pause Music*************
void Settings::pauseMusic(float t)
{
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->pauseBackgroundMusic();
}

//Resume music***************
void Settings::resumeMusic(float t)
{
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->resumeBackgroundMusic();
}


Size Settings::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(table->getViewSize().width,table->getViewSize().height*0.13f);
}


ssize_t Settings::numberOfCellsInTableView(TableView *table)
{
    return AppDelegate::getStore()->MoveRecords.size()+1;
}


void Settings::tableCellTouched(TableView* table, TableViewCell* cell)
{
     int index =(int) cell->getIdx();
     log("index %d",index);
//
     if(index!=0)
     {
         auto scene = Simulation::createScene(index-1);
         Director::getInstance()->replaceScene(scene);
     }
 }
