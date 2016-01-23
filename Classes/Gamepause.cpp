#include "Gamepause.h"
#include "HelloWorldScene.h"//这是游戏界面的头文件
#include "GameLogin.h"//这是游戏登录界面的头文件
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
//传入一个CCrenderTexture 
//相当于一个正在运行的游戏的截图作为这个暂停对话框的背景 
//这样就看起来像是对话框在游戏界面之上，一般游戏当中都是这样子写的。
CCScene* Gamepause::scene(CCRenderTexture* sqr)
{

    CCScene *scene = CCScene::create();
    Gamepause *layer = Gamepause::create();
		scene->addChild(layer,1);//把游戏层放上面，我们还要在这上面放按钮


	//增加部分：使用Game界面中截图的sqr纹理图片创建Sprite
	//并将Sprite添加到GamePause场景层中
	//得到窗口的大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite *back_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());  
	back_spr->setPosition(ccp(visibleSize.width/2,visibleSize.height/2)); //放置位置,这个相对于中心位置。
	back_spr->setFlipY(true);            //翻转，因为UI坐标和OpenGL坐标不同
	back_spr->setColor(cocos2d::ccGRAY); //图片颜色变灰色
	scene->addChild(back_spr);


	//添加游戏暂停背景小图，用来放按钮
	CCSprite *back_small_spr = CCSprite::create("back_pause.png");
	back_small_spr->setPosition(ccp(visibleSize.width/2,visibleSize.height/2)); //放置位置,这个相对于中心位置。
	scene->addChild(back_small_spr);


    return scene;
}

bool Gamepause::init()
{

    if ( !CCLayer::init() )
    {
        return false;
    }
	//得到窗口的大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//原点坐标
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//继续游戏按钮
	CCMenuItemImage *pContinueItem = CCMenuItemImage::create(
		"pause_continue.png",
		"pause_continue.png",
		this,
		menu_selector(Gamepause::menuContinueCallback));

	pContinueItem->setPosition(ccp( visibleSize.width/2 ,visibleSize.height/2+30));

	//重新开始游戏按钮
	CCMenuItemImage *pRestartItem = CCMenuItemImage::create(
		"pause_restart.png",
		"pause_restart.png",
		this,
		menu_selector(Gamepause::menuRestart));

	pRestartItem->setPosition(ccp( visibleSize.width/2 ,visibleSize.height/2-20));

	//回主界面
	CCMenuItemImage *pLoginItem = CCMenuItemImage::create(
		"pause_login.png",
		"pause_login.png",
		this,
		menu_selector(Gamepause::menuLogin));

	pLoginItem->setPosition(ccp( visibleSize.width/2 ,visibleSize.height/2-70));


	CCMenu* pMenu = CCMenu::create(pContinueItem,pRestartItem,pLoginItem,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 2);
    return true;
}
void Gamepause::menuContinueCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->popScene();

}
//重新开始游戏
void  Gamepause::menuRestart(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}
//回主界面
void  Gamepause::menuLogin(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(GameLogin::scene());
}






