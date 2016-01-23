#include "FlyWord.h"
FlyWord* FlyWord::create(const char *word,const int fontSize,CCPoint begin){

	FlyWord* ret = new FlyWord();
	//这样写更安全一些
	if(ret && ret->init(word,fontSize,begin)){
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);//安全删除
	return nullptr;
}

bool FlyWord::init(const char *word,const int fontSize,CCPoint begin){
	if(!CCNode::init()){
		return false;
	}
	//初始化
	_begin = begin;
	m_plabel = CCLabelTTF::create(word,"Marker Felt",fontSize);

	//设置颜色
	ccColor3B RGB;
	RGB.r=255;
	RGB.g=0;
	RGB.b=0;
	m_plabel->setColor(RGB);

	this->addChild(m_plabel);
	this->setPosition(ccp(begin.x,begin.y));
	//初始化完成后就开始飘字了
	Flying();
	return true;
}

//文字从下到上飘动
void FlyWord::Flying()
{
	
	CCMoveBy* moveact=CCMoveBy::create(0.5f,CCPointMake(0,70));//0.5秒向上移动70

	//创建回调动作，文字飘动完后
	CCCallFunc* callFunc=CCCallFunc::create(this,callfunc_selector(FlyWord::Flyend));
	//创建连续动作
	CCActionInterval* act=CCSequence::create(moveact,callFunc,NULL);
	//setVisible(true);
	this->runAction(act);


}
//文字飘动后删除所有对象
void FlyWord::Flyend()
{
	//完成之后把该对象从内存中删除掉
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
}