#include "SkillButton.h"
SkillButton* SkillButton::create(const char* fore_name,const char* back_name){

	SkillButton* ret = new SkillButton();

	//这样写更安全一些
	if(ret&&ret->init(fore_name,back_name)){
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);//安全删除
	return nullptr;
}
bool SkillButton::init(const char* fore_name,const char* back_name)
{
	if(!CCLayer::init()){
		return false;
	}

	this->setTouchEnabled(true);//开启触摸
	fore=CCSprite::create(fore_name);//fore_name是较亮的图片 
	this->addChild(fore,1);  

	back=CCSprite::create(back_name);//back_name是较暗的图片  
	pt=CCProgressTimer::create(back);
	this->addChild(pt,2);  
	
	IsSkilling=false;
	
	return true;

}
//开始冷却技能
void SkillButton::BeginSkill()
{
	if(IsSkilling)
		return;
	//转圈的CD实现  
	pt->setType(cocos2d::CCProgressTimerType(kCCProgressTimerTypeRadial)); 
	CCProgressTo *waittime=CCProgressTo::create(8,100);
	//创建回调动作，技能冷却结束后调用EndSkill()
	CCCallFunc* callFunc=CCCallFunc::create(this,callfunc_selector(SkillButton::EndSkill));
	//创建连续动作
	CCActionInterval* act=CCSequence::create(waittime,callFunc,NULL);
	pt->setVisible(true);
	IsSkilling=true;
	pt->runAction(act); 
	//第一个参数是消息的名字，第二个参数是CCObject * 类型的消息值，也就是你要发送的东西
	CCNotificationCenter::sharedNotificationCenter()->postNotification("MessageSkill",NULL);

}
//冷却技能结束后
void SkillButton::EndSkill()
{
	pt->setVisible(false);
	IsSkilling=false;
}

//判断是否点击的范围为精灵 如果是则执行动作  
void SkillButton::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)  
{  
	if(IsSkilling)
		return;
	//判断是否点击在精灵上面
	CCPoint touchPoint = convertTouchToNodeSpace(pTouch);  
	if(fore->boundingBox().containsPoint(touchPoint))  
	{  

		BeginSkill();
	}  
}  

//返回true表示支持触摸 返回false表示忽略   
bool SkillButton::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)  
{  
	return true;  
} 
///注册触摸代理支持,其中第二个参数为触摸的响应等级 值越小 响应等级越高  
void SkillButton::registerWithTouchDispatcher()  
{  
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);//true表示只有当前层能截取到触摸事件
}




