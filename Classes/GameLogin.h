#ifndef __GameLogin_SCENE_H__
#define __GameLogin_SCENE_H__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;//重点要记得，要不会出现error C2065: “SEL_TouchEvent”: 未声明的标识符
class GameLogin : public cocos2d::CCLayer
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameLogin);

	//开始游戏按钮的回调事件
	void TouchBeginButton(cocos2d::CCObject* obj,gui::TouchEventType type);
	//设置游戏按钮的回调事件
	void TouchSetnButton(cocos2d::CCObject* obj,gui::TouchEventType type);
	//退出游戏按钮的回调事件
	void TouchExitButton(cocos2d::CCObject* obj,gui::TouchEventType type);
	//声音控制
	void TouchCheckMusic(cocos2d::CCObject* obj,gui::CheckBoxEventType type);


};

#endif // __GameLogin_SCENE_H__
