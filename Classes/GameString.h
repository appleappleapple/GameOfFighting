#ifndef __GameString_SCENE_H__
#define __GameString_SCENE_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ChineseString.h"
#include "HelloWorldScene.h"//这是游戏界面的头文件
USING_NS_CC;
USING_NS_CC_EXT;
class GameString : public cocos2d::CCLayer
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameString);
	//字幕滚动完成后调用
	void RollEnd();
	//跳过按钮的事件
	void menuCloseCallback(CCObject* pSender);
};

#endif // __GameString_SCENE_H__
