#include "HelloWorldScene.h"
#include "FlyWord.h"
#include "Gamepause.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "iconv/iconv.h"

USING_NS_CC;
USING_NS_CC_EXT; 

CCScene* HelloWorld::scene()
{

    CCScene *scene = CCScene::create();
    HelloWorld *layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{

    if ( !CCLayer::init() )
    {
        return false;
    }
    //得到窗口的大小
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

   // 修改背景图片,更改为自己定义的地图
	mymap=Map::create();
	mymap->InitMap("12.png",visibleSize);
	this->addChild(mymap,0);//这里的0表示放在最底层
    
	//添加摇杆
	rocker = HRocker::createHRocker("Direction_bt.png","Direction_bc.png",ccp(110,60));//其中第一张图片为摇杆的按钮，第二张为背景
	this->addChild(rocker,2);
	rocker->startRocker(false);//true表示只能响应这层的触摸


	//添加赵云精灵
	hero=Hero::create();
	hero->InitHeroSprite("hero.png");
	hero->setPosition(ccp(200,200));
	this->addChild(hero,1);
	
	//添加攻击按钮
	btn=ControlButton::create();
	btn->CreateButton("bt.png");
	btn->setPosition(ccp(visibleSize.width-50,50));
	this->addChild(btn,2);

	//添加技能按钮
	btn_skill=SkillButton::create("skill_back.png","skill_fore.png");
	btn_skill->setPosition(ccp(visibleSize.width-150,60));
	this->addChild(btn_skill,2);


	//设置英雄的血条 
	m_pProgressView = new ProgressView();  
	m_pProgressView->setPosition(ccp(150, 450));  
	m_pProgressView->setScale(2.2f);  
	m_pProgressView->setBackgroundTexture("xue_back.png");  
	m_pProgressView->setForegroundTexture("xue_fore.png");  
	m_pProgressView->setTotalProgress(1000.0f);  
	m_pProgressView->setCurrentProgress(1000.0f); 
	//下面两个是为了让血条更好好看
	CCSprite *xuekuang=CCSprite::create("kuang.png");//添加血条的框架
	xuekuang->setPosition(ccp(m_pProgressView->getPositionX(),m_pProgressView->getPositionY()));
	CCSprite *touxiang=CCSprite::create("touxiang.png");//添加英雄的左上角的小头像
	touxiang->setPosition(ccp(m_pProgressView->getPositionX()-120,m_pProgressView->getPositionY()));
	this->addChild(touxiang,2);
	this->addChild(xuekuang,2);
	this->addChild(m_pProgressView, 2);  


	//添加怪物
	monster1=Monster::create();
	monster1->InitMonsterSprite("monster.png","xue_back.png","xue_fore.png");
	monster1->setPosition(ccp(visibleSize.width-50,visibleSize.height/2));
	mymap->addChild(monster1);//将怪物添加到地图中，这样怪物才能随地图移动
	monster1->StartListen(hero,mymap);
  	

	//添加暂停按钮
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create("play.png","pause.png",this,menu_selector(HelloWorld::menuPauseCallback));
	pCloseItem->setPosition(ccp(visibleSize.width - pCloseItem->getContentSize().width/2 , visibleSize.height - pCloseItem->getContentSize().height/2));
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	//启动updata事件
	this->scheduleUpdate();

    return true;
}

void HelloWorld::update(float delta)
{
	
	//判断是否按下摇杆及其类型
	CCSize visibleSize1 = CCDirector::sharedDirector()->getVisibleSize();//得到窗口大小
	if(!hero->IsAttack)//不攻击时才可以跑
	{
	switch(rocker->rocketDirection)
	{
	case  1:	
		hero->SetAnimation("hero_run",8,rocker->rocketRun);	
		if(hero->getPositionX()<=visibleSize1.width-8)//不让精灵超出右边,8可以改成你喜欢的
		{
			if(!hero->JudgePositona(visibleSize1)||mymap->JudgeMap(hero,visibleSize1))//精灵没到达窗口中间位置或者地图已经移动到边缘了，精灵才可以移动，否则只播放动画
				hero->setPosition(ccp(hero->getPosition().x+1,hero->getPosition().y)); //向右走
			//下面是移动地图
			mymap->MoveMap(hero,visibleSize1);
		}
		break;
	case  2:
		hero->SetAnimation("hero_run",8,rocker->rocketRun);
		hero->setPosition(ccp(hero->getPosition().x, hero->getPosition().y+1));   //向上走
		break;
	case 3:
		hero->SetAnimation("hero_run",8,rocker->rocketRun);
		if(hero->getPositionX()>=8)//不让精灵超出左边,8可以改成你喜欢的
			hero->setPosition(ccp(hero->getPosition().x-1,hero->getPosition().y));   //向左走
		break;
	case 4:
		hero->SetAnimation("hero_run",8,rocker->rocketRun);
		hero->setPosition(ccp(hero->getPosition().x,hero->getPosition().y-1));   //向下走
		break;
	case 0:
		hero->StopAnimation();//停止所有动画和运动
		break;
	}
	}


	//判断是否出动攻击
	if(btn->isTouch)
	{
		if(hero->IsAttack)
			return;//英雄正在攻击
		hero->AttackAnimation("hero_attack",20,rocker->rocketRun);
	}


	if(hero->IsAttack)//英雄正在攻击
	{
	  if(!monster1->Isdead)//怪物还没死
	  {
	    if(abs(hero->getPositionY()-monster1->getPositionY()-mymap->getPositionY())<30)//怪物和英雄应该在一个差不多的水平高度上，攻击才有效
	    {
         //检测是否碰撞到怪物
	      if (this->isRectCollision(CCRectMake(hero->getPositionX(), hero->getPositionY(),hero->GetSprite()->getContentSize().width-70, hero->GetSprite()->getContentSize().height-30), CCRectMake(monster1->getPositionX()+mymap->getPositionX(), monster1->getPositionY()+mymap->getPositionY(), monster1->GetSprite()->getContentSize().width-30,monster1->GetSprite()->getContentSize().height-20))) 
	         {
		        monster1->HurtAnimation("monster_hurt",2,monster1->MonsterDirecton);//受伤
	         }
	     }
	  }
	}

	
	if(!monster1->Isdead)//怪物没死
	{
		if(monster1->IsAttack)//怪物正在攻击
		{
			if(abs(hero->getPositionY()-monster1->getPositionY()-mymap->getPositionY())<30)//怪物和英雄应该在一个差不多的水平高度上，攻击才有效
			{
				//检测是否碰撞到英雄
				if (this->isRectCollision(CCRectMake(hero->getPositionX(), hero->getPositionY(),hero->GetSprite()->getContentSize().width-70, hero->GetSprite()->getContentSize().height-30), CCRectMake(monster1->getPositionX()+mymap->getPositionX(), monster1->getPositionY()+mymap->getPositionY(), monster1->GetSprite()->getContentSize().width-30,monster1->GetSprite()->getContentSize().height-20))) 
				{
					
					m_pProgressView->setCurrentProgress(m_pProgressView->getCurrentProgress()-1);
					
				}

		    }
	}
	}

}
///碰撞检测
bool HelloWorld::isRectCollision (CCRect rect1, CCRect rect2)
{
	float x1 = rect1.origin.x;//矩形1中心点的横坐标
	float y1 = rect1.origin.y;//矩形1中心点的纵坐标
	float w1 = rect1.size.width;//矩形1的宽度
	float h1 = rect1.size.height;//矩形1的高度
	float x2 = rect2.origin.x;
	float y2 = rect2.origin.y;
	float w2 = rect2.size.width;
	float h2 = rect2.size.height;

	if (x1+w1*0.5<x2-w2*0.5)  
		return false;//矩形1在矩形2左方，两者无碰撞
	else if (x1-w1*0.5>x2+w2*0.5)
		return false;//矩形1在矩形2右方，两者无碰撞
	else if (y1+h1*0.5<y2-h2*0.5)
		return false;//矩形1在矩形2下方，两者无碰撞
	else if (y1-h1*0.5>y2+h2*0.5)
		return false;//矩形1在矩形2上方，两者无碰撞

	return true;
}
//暂停界面
void HelloWorld::menuPauseCallback(CCObject* pSender)
{
	//得到窗口的大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width,visibleSize.height);

	//遍历当前类的所有子节点信息，画入renderTexture中。
	//这里类似截图。
	renderTexture->begin(); 
	this->getParent()->visit();
	renderTexture->end();
	//将游戏界面暂停，压入场景堆栈。并切换到GamePause界面
	CCDirector::sharedDirector()->pushScene(Gamepause::scene(renderTexture));

}







