#include "Hero.h"
USING_NS_CC; 
Hero::Hero(void)
{
	IsRunning=false;//没在放动画
	HeroDirecton=false;//向右运动
	Hero_name=NULL;
	IsAttack=false;
	m_HeroSprite=NULL;
}

Hero::~Hero(void)
{
	//注意最后一定要释放消息，否则内容泄露
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,"MessageSkill");
}
 void Hero::InitHeroSprite(char *hero_name)
 {
	Hero_name=hero_name;
	this->m_HeroSprite=CCSprite::create(hero_name);
	this->addChild(m_HeroSprite);

	//注册MessageSkill，如果接收到了，执行SkillAmiation
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(Hero::SkillAmiation),"MessageSkill",NULL);
 }
 void Hero::SetAnimation(const char *name_each,unsigned int num,bool run_directon)
 {
	 if(HeroDirecton!=run_directon)
	 {   HeroDirecton=run_directon;
	     m_HeroSprite->setFlipX(run_directon);
	 }
	 if(IsRunning)
		 return;
	 CCAnimation* animation = CCAnimation::create();  
	 for( int i=1;i<=num;i++)  
	 {  
		 char szName[100] = {0};  
		 sprintf(szName,"%s%d.png",name_each,i);  
		 animation->addSpriteFrameWithFileName(szName); //加载动画的帧  
	 }  
	 animation->setDelayPerUnit(0.1f);  
	 animation->setRestoreOriginalFrame(true);  
	 animation->setLoops(-1); //动画循环
	 if(HeroDirecton!=run_directon)
	 {   HeroDirecton=run_directon;

	 }
	 //将动画包装成一个动作
	 CCAnimate* act=CCAnimate::create(animation);
	
	 m_HeroSprite->runAction(act);
	 IsRunning=true;

 }
 void Hero::StopAnimation()
 {
	 if(!IsRunning)
		 return;
	m_HeroSprite->stopAllActions();//当前精灵停止所有动画

	//恢复精灵原来的初始化贴图 
	this->removeChild(m_HeroSprite,TRUE);//把原来的精灵删除掉
	m_HeroSprite=CCSprite::create(Hero_name);//恢复精灵原来的贴图样子
	m_HeroSprite->setFlipX(HeroDirecton);
	this->addChild(m_HeroSprite);
	IsRunning=false;
 }
  void Hero::AttackAnimation(const char *name_each,const unsigned int num,bool run_directon)
  {
	  if(IsAttack)
		  return;
	  IsAttack=true;
	  CCAnimation* animation = CCAnimation::create();  
	  for( int i=1;i<=num;i++)  
	  {  
		  char szName[100] = {0};  
		  sprintf(szName,"%s%d.png",name_each,i);  
		  animation->addSpriteFrameWithFileName(szName); //加载动画的帧  
	  }  
	  animation->setDelayPerUnit(0.05f);  
	  animation->setRestoreOriginalFrame(true);  
	  animation->setLoops(1); //动画循环
	  if(HeroDirecton!=run_directon)
	  {   HeroDirecton=run_directon;

	  }
	  //将动画包装成一个动作
	  CCAnimate* act=CCAnimate::create(animation);


	  //创建回调动作，攻击结束后调用AttackEnd()
	  CCCallFunc* callFunc=CCCallFunc::create(this,callfunc_selector(Hero::AttackEnd));
	  //创建连续动作
	 CCActionInterval* attackact=CCSequence::create(act,callFunc,NULL);
	  
	  m_HeroSprite->runAction(attackact); 

  }
  void Hero::AttackEnd()
  {
	  m_HeroSprite->setFlipX(HeroDirecton);
	   IsAttack=false;
  }
  bool Hero::JudgePositona (CCSize visibleSize)
  {
	  if(this->getPositionX()!=visibleSize.width/2)//精灵到达左边
		  return false;
	  else
		  return true;//到达中间位置
  }
CCSprite* Hero::GetSprite()
{
	return m_HeroSprite;
}

//技能特效
void Hero::SkillAmiation(CCObject * object)
{

	m_HeroSprite->stopAllActions();//当前精灵停止所有动画
	CCAnimation* animation = CCAnimation::create();  
	for( int i=1;i<=6;i++)  
	{  
		char szName[100] = {0};  
		sprintf(szName,"skill_%d.png",i);  
		animation->addSpriteFrameWithFileName(szName); //加载动画的帧  
	}  
	animation->setDelayPerUnit(0.1f);  
	animation->setRestoreOriginalFrame(true);  
	animation->setLoops(5); //动画循环
	//将动画包装成一个动作
	CCAnimate* act=CCAnimate::create(animation);

	//创建回调动作，攻击结束后调用AttackEnd()
	CCCallFunc* callFunc=CCCallFunc::create(this,callfunc_selector(Hero::AttackEnd));
	//创建连续动作
	CCActionInterval* skillattack=CCSequence::create(act,callFunc,NULL);
	 IsAttack=true;
	m_HeroSprite->runAction(skillattack);

}