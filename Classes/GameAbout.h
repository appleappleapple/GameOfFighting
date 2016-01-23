#ifndef __GameAbout_SCENE_H__
#define __GameAbout_SCENE_H__
#include "cocos2d.h"

#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;//重点要记得，要不会出现error C2065: “SEL_TouchEvent”: 未声明的标识符
class GameAbout : public cocos2d::CCLayer
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameAbout);

	//返回开始界面的回调事件
	void TouchBackLoginButton(cocos2d::CCObject* obj,gui::TouchEventType type);
};

#endif // __GameAbout_SCENE_H__
