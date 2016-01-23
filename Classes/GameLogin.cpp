#include "GameLogin.h"
#include "GameAbout.h"
#include "HelloWorldScene.h"//这是游戏界面的头文件
#include "SimpleAudioEngine.h"
#include "GameString.h"
using namespace CocosDenshion;
CCScene* GameLogin::scene()
{
    CCScene *scene = CCScene::create();
    GameLogin *layer = GameLogin::create();
    scene->addChild(layer);
    return scene;
}

bool GameLogin::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//加载cocos studio制作的界面
	gui::TouchGroup* ul = gui::TouchGroup::create(); 
	gui::Layout* equipe_root =dynamic_cast<gui::Layout*>(GUIReader::shareReader()->widgetFromJsonFile("MyLogin_1.ExportJson"));
	ul->addWidget(equipe_root); 
	this->addChild(ul,2);

	//给开始按钮添加事件监听
	gui::Button *Btn_Begin = dynamic_cast<gui::Button*>(equipe_root->getChildByName("Begin_Game"));//Begin_Game为在Cocos Studio中定义的按钮的名称
	Btn_Begin->addTouchEventListener(this,toucheventselector(GameLogin::TouchBeginButton));
	//给设置按钮添加事件监听
	gui::Button *Btn_Set = dynamic_cast<gui::Button*>(equipe_root->getChildByName("Set_Game")); //Set_Game为在Cocos Studio中定义的按钮的名称
	Btn_Set->addTouchEventListener(this,toucheventselector(GameLogin::TouchSetnButton));
	//给开始按钮添加事件监听
	gui::Button *Btn_Exit = dynamic_cast<gui::Button*>(equipe_root->getChildByName("Exit_Game")); //Exit_Game为在Cocos Studio中定义的按钮的名称
	Btn_Exit->addTouchEventListener(this,toucheventselector(GameLogin::TouchExitButton));
	
	gui::CheckBox *Check_Music=dynamic_cast<gui::CheckBox*>(equipe_root->getChildByName("CheckBox_Music"));
	//gui::CheckBox *Check_Music = static_cast<CheckBox*>(GameLogin::seekWidgetByName(ul,"CheckBox_Music"));
	Check_Music->addEventListenerCheckBox(this,checkboxselectedeventselector(GameLogin::TouchCheckMusic));

	//添加音乐
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic( "backmusic.mp3");    //加载背景音 
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);//设置音量0.0-1.0
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("backmusic.mp3",true);     //播放音乐,true表示重复

    return true;
}
void GameLogin::TouchBeginButton(cocos2d::CCObject* obj,gui::TouchEventType type)
{

      if(type==gui::TouchEventType::TOUCH_EVENT_BEGAN)
	  {
		CCDirector::sharedDirector()->replaceScene(GameString::scene());//进入游戏主界面
	  }

}

//设置游戏按钮的回调事件
void GameLogin::TouchSetnButton(cocos2d::CCObject* obj,gui::TouchEventType type)
{
	if(type==gui::TouchEventType::TOUCH_EVENT_BEGAN)
	{
		CCDirector::sharedDirector()->replaceScene(GameAbout::scene());//进入游戏主界面设置
	}
}
//退出游戏按钮的回调事件
void GameLogin::TouchExitButton(cocos2d::CCObject* obj,gui::TouchEventType type)
{
	if(type==gui::TouchEventType::TOUCH_EVENT_BEGAN)   
	CCDirector::sharedDirector()->end();
}
//声音控制
void GameLogin::TouchCheckMusic(cocos2d::CCObject* obj,gui::CheckBoxEventType type)
{
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();//停止背景音乐
		break;
	case CHECKBOX_STATE_EVENT_UNSELECTED:
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();//重新开始背景音乐
		break;
	default:
		break;
	}
}


