#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT; 
class SkillButton:public cocos2d::CCLayer{
public:
	//创建冷却技能按钮,create 和 init 是连在一起的,调用create的时候必然会调用init
	static SkillButton* create(const char* fore_name,const char* back_name);
	//初始化按钮
	bool init(const char* fore_name,const char* back_name);

	//开始冷却技能
	void BeginSkill();
	//冷却技能结束后
	void EndSkill();
	//判断是否在冷却技能
	bool IsSkilling;

	//开始触摸
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);  
	//触摸结束
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent); 
	///注册触摸代理支持
	void registerWithTouchDispatcher(); 



private:
	CCSprite *fore;//fore是较亮的图片  
	CCSprite *back;//back是较暗的图片  
	CCProgressTimer *pt;//技能效果
	

};