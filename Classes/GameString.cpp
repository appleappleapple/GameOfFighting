#include "GameString.h"
CCScene* GameString::scene()
{
    CCScene *scene = CCScene::create();
    GameString *layer = GameString::create();
    scene->addChild(layer);
    return scene;
}
bool GameString::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	//加个按钮
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"exct.png",
		"exct.png",
		this,
		menu_selector(GameString::menuCloseCallback));

	pCloseItem->setPosition(ccp( visibleSize.width -80 ,visibleSize.height-60));
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);


  //加背景
    CCSprite* pSprite = CCSprite::create("enter.png");
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(pSprite, 0);


	//创建要显示的文字
	CCLabelTTF* pLabel=CCLabelTTF::create(ChineseString::GBKToUTF8("我是林炳文Evankaka～～\n这是游戏《赵云要格斗》\n欢迎来到我的世界～～～\n我是林炳文Evankaka～～\n这是游戏《赵云要格斗》\n欢迎来到我的世界～～～\n我是林炳文Evankaka～～\n这是游戏《赵云要格斗》"),"Arial",25);
	pLabel->setAnchorPoint(CCPointZero);
	ccColor3B color = ccc3(255,255,0);
	pLabel->setColor(color);
	pLabel->setPosition(ccp(50, -200));//Y轴注意为负,X轴对应下面的point[4]的50，让他们对齐

	//绘制裁剪区域
	CCDrawNode* shap = CCDrawNode::create();
	CCPoint point[4] = {ccp(50,0), ccp(400,0), ccp(400,200), ccp(50,200)};//可以根据文字适当修改下大小
	shap->drawPolygon(point,4,ccc4f(255,255,255,255),0, ccc4f(255,255,255,255));//绘制四边形


	////创建遮罩
	CCClippingNode* pClip = CCClippingNode::create();
	pClip->setInverted(false);
	pClip->setStencil(shap);//一定要有，要不会报错
	pClip->addChild(pLabel);
	this->addChild(pClip);
	
	//开始让字幕滚动啦
	CCMoveBy* moveact=CCMoveBy::create(10.0f,CCPointMake(0,400));//0.5秒向上移动70
	CCCallFunc* callFunc=CCCallFunc::create(this,callfunc_selector(GameString::RollEnd));//创建回调动作，文字飘动完后
	CCActionInterval* act=CCSequence::create(moveact,callFunc,NULL);//创建连续动作
	pLabel->runAction(act);

    return true;
}

void GameString::RollEnd()
{
CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());//进入游戏主界面
}

void GameString::menuCloseCallback(CCObject* pSender)
{
	RollEnd();
}


