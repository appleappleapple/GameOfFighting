#include "GameAbout.h"
#include "GameLogin.h"
CCScene* GameAbout::scene()
{

    CCScene *scene = CCScene::create();
    GameAbout *layer = GameAbout::create();
    scene->addChild(layer);
    return scene;
}

bool GameAbout::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//加载cocos studio制作的界面
	gui::TouchGroup* ul = gui::TouchGroup::create(); 
	gui::Layout* equipe_root =dynamic_cast<gui::Layout*>(GUIReader::shareReader()->widgetFromJsonFile("About_1.json"));
	ul->addWidget(equipe_root); 
	this->addChild(ul,2);

	//给开始按钮添加事件监听
	gui::Button *Btn_Back_Login = dynamic_cast<gui::Button*>(equipe_root->getChildByName("Back_Login"));//Begin_Game为在Cocos Studio中定义的按钮的名称
	Btn_Back_Login->addTouchEventListener(this,toucheventselector(GameAbout::TouchBackLoginButton));
    
    return true;
}
void GameAbout::TouchBackLoginButton(cocos2d::CCObject* obj,gui::TouchEventType type)
{

      if(type==gui::TouchEventType::TOUCH_EVENT_BEGAN)
	  {
		  CCDirector::sharedDirector()->replaceScene(GameLogin::scene());//随机方格消失进入游戏主界面
	  }

}




