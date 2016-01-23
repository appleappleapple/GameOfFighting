#ifndef __HERO_H__
#define __HERO_H__
#include "cocos2d.h"
using namespace cocos2d;
 class Hero:public cocos2d::CCNode
 {
 public:
	   Hero(void);
	  ~Hero(void);
	 //根据图片名创建英雄
	 void InitHeroSprite(char *hero_name);
	 //返回当前英雄
	 CCSprite* GetSprite();

	 //设置动画,num为图片数目，run_directon为精灵脸朝向，false朝右,name_each为name_png中每一小张图片的公共名称部分
	 void SetAnimation(const char *name_each,const unsigned int num,bool run_directon);
	//停止动画
	 void StopAnimation();

	 //攻击动画
	 void AttackAnimation(const char *name_each,const unsigned int num,bool run_directon);
	 //攻击动画结束
	 void AttackEnd();
	 //判断英雄是否运动到了窗口的中间位置,visibleSize为当前窗口的大小  
	 bool JudgePositona(CCSize visibleSize);  

	 //技能特效
	 void SkillAmiation(CCObject * object);//注意要有参数，因为是观察者模式的调用函数，要不会提示“类型转换”: 无法从“void (__thiscall Hero::* )(void)”转换为“cocos2d::SEL_CallFuncO”




	//判断是否在跑动画
	 bool IsRunning;
	 //判断是否在攻击动画
	 bool IsAttack;
	 //英雄运动的方向
	 bool HeroDirecton;

	 

	 CREATE_FUNC(Hero);
 private:
	 CCSprite* m_HeroSprite;//精灵
	 char *Hero_name;//用来保存初始状态的精灵图片名称
 };
#endif // __HERO_H__