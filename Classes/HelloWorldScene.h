#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "HRocker.h"
#include "Hero.h"
#include "ControlButton.h"
#include "Map.h"
#include "ProgressView.h" 
#include "Monster.h"
#include "SkillButton.h"
class HelloWorld : public cocos2d::CCLayer
{
public:
    virtual bool init();  

    static cocos2d::CCScene* scene();
    CREATE_FUNC(HelloWorld);
	//每帧更新时调用的事件
	virtual void update(float delta);
	//矩形碰撞检测
	bool isRectCollision (CCRect rect1, CCRect rect2);
	//暂停界面
	void  menuPauseCallback(CCObject* pSender);	

private:
	 HRocker* rocker;//摇杆
	 Hero*    hero;///精灵
	 ControlButton* btn;//按钮控件变量
	 Map*     mymap;//地图  
	 ProgressView *m_pProgressView;  //血条
	 Monster *monster1;//怪物种类1
	 SkillButton* btn_skill;//技能按钮
};

#endif // __HELLOWORLD_SCENE_H__
