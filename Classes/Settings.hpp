
#ifndef Settings_hpp
#define Settings_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"
#include <iostream>
#include <vector>

using namespace cocos2d::extension;

class Settings: public cocos2d::Scene,TableViewDelegate,TableViewDataSource
{
public:
    
    cocos2d::Layer* IconsLayer = nullptr;
    cocos2d::ui::ScrollView* scrollView;
    
    bool outSideTouch = false;
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(Settings);
    
    void changeProfile(Ref* pSender,cocos2d::ui::Widget::TouchEventType type);
    
    void moveToSimulation(Ref *pSender);
    
    std::vector<int> record;
    
    int temp[10];
  
    
    
    //TableViewDataSource
    TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx) override;
    /**
     * Returns number of cells in a given table view.
     *
     * @return number of cells
     */
     ssize_t numberOfCellsInTableView(TableView *table) override;


    //TableViewDelegate
     void tableCellTouched(TableView* table, class TableViewCell* cell) override;


     cocos2d::Size tableCellSizeForIndex(TableView *table, ssize_t idx) override;
    
//    virtual cocos2d::Size cellSizeForTable(TableView* table);
    
    void closeChangeImagePopUp();
    
    void ImageClicked(Ref* pSender,int i);
    void clickImage1(Ref* pSender);
    void clickImage2(Ref* pSender);
    void clickImage3(Ref* pSender);
    void clickImage4(Ref* pSender);
    void clickImage5(Ref* pSender);
    void clickImage6(Ref* pSender);
    void clickImage7(Ref* pSender);
    void clickImage8(Ref* pSender);
    void clickImage9(Ref* pSender);
    
    
    void changeAudio(Ref* pSender,cocos2d::ui::Widget::TouchEventType type);
    void pauseMusic(float t);
    void resumeMusic(float t);
    
    void touchHandling();
   
    
};

#endif /* Settings_hpp */

