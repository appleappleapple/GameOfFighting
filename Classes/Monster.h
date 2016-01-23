#ifndef __Monster_H__
#define __Monster_H__
#include "cocos2d.h"
#include "ProgressView.h"
USING_NS_CC;
class Monster:public cocos2d::CCNode
{
public:
	Monster(void);
	~Monster(void);
	//根据图片名创建怪物，不带血条的怪物
	void InitMonsterSprite(char *name);
	//根据图片名创建怪物，带血条的怪物
	void InitMonsterSprite(char *name,char *xue_back,char* xue_fore);

	//设置走动动画,num为图片数目，run_directon为精灵脸朝向，false朝右,name_each为name_png中每一小张图片的公共名称部分
	void SetAnimation(const char *name_each,const unsigned int num,bool run_directon);
	//停止走动动画
	void StopAnimation();
	//判断是否在跑动画
	bool IsRunning;

	//攻击动画
	void AttackAnimation(const char *name_each,const unsigned int num,bool run_directon);
	//攻击动画结束
	void AttackEnd();
	//判断是否在攻击动画
	bool IsAttack;

	//受伤动画
	void HurtAnimation(const char *name_each,const unsigned int num,bool run_directon);
	//受伤动画结束
	void HurtEnd();
	//判断是否在受伤动画
	bool IsHurt;

	//死亡动画
	void DeadAnimation(const char *name_each,const unsigned int num,bool run_directon);
	//死亡动画结束
	void DeadEnd();
	//判断是否死亡
	bool Isdead;

	//怪物死亡闪烁结束
	void BlinkEnd();

	//返回英雄
	CCSprite* GetSprite();
	//怪物运动的方向
	bool MonsterDirecton;

	//在可视范围内，怪物跟随英雄运动
	void FollowRun(CCNode* m_hero,CCNode* m_map);
	//判断是否攻击
	void JudegeAttack();
	//怪物巡逻路线
	void MonsterSeeRun();


	//怪物启动监听英雄
	void StartListen(CCNode* m_hero,CCNode* m_map);
	//监听函数,每隔3秒检测下，计算英雄与怪物的距离
	void updateMonster(float delta);
	//更新函数，如果英雄在可视范围内，不断触发
	void update(float delta);

	CREATE_FUNC(Monster);

private:
	CCSprite* m_MonsterSprite;//怪物精灵
	char *Monster_name;//用来保存初始状态的精灵图片名称
	ProgressView*  Monster_xue;//怪物血条
	CCNode* my_hero;//当前英雄
	CCNode* my_map;//当前地图
	float   dis;//当前怪物和英雄的距离
	
};
#endif // 

