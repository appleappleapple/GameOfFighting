#include "HRocker.h"
const double PI=3.1415;
HRocker::HRocker(void)
{
	rocketRun=false;
}

HRocker::~HRocker(void)
{
}

//创建摇杆(摇杆的操作题图片资源名，摇杆背景图片资源名，起始坐标)
HRocker* HRocker::createHRocker(const char *rockerImageName,const char *rockerBGImageName,CCPoint position)
{
	HRocker *layer = HRocker::create();
	if (layer)
	{
		layer->rockerInit(rockerImageName,rockerBGImageName,position);
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}

//自定义初始化函数
void HRocker::rockerInit(const char* rockerImageName,const char* rockerBGImageName,CCPoint position)
{
	CCSprite *spRockerBG = CCSprite::create(rockerBGImageName);
	spRockerBG->setPosition(position);
	spRockerBG->setVisible(false);
	addChild(spRockerBG,0,tag_rockerBG);

	CCSprite *spRocker = CCSprite::create(rockerImageName);
	spRocker->setPosition(position);
	spRocker->setVisible(false);
	addChild(spRocker,1,tag_rocker);

	rockerBGPosition = position;
	rockerBGR = spRockerBG->getContentSize().width*0.5;//
	rocketDirection=-1;//表示摇杆方向不变
}

//启动摇杆(显示摇杆、监听摇杆触屏事件)
void HRocker::startRocker(bool _isStopOther)
{
	CCSprite *rocker = (CCSprite*)this->getChildByTag(tag_rocker);
	rocker->setVisible(true);

	CCSprite *rockerBG = (CCSprite *)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(true);

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-1,_isStopOther);
}

//停止摇杆(隐藏摇杆，取消摇杆的触屏监听)
void HRocker::stopRocker()
{
	CCSprite *rocker = (CCSprite *)this->getChildByTag(tag_rocker);
	rocker->setVisible(false);

	CCSprite * rockerBG = (CCSprite *)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(false);

	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}


//获取当前摇杆与用户触屏点的角度
float HRocker::getRad(CCPoint pos1,CCPoint pos2)
{
	float px1 = pos1.x;
	float py1 = pos1.y;
	float px2 = pos2.x;
	float py2 = pos2.y;

	//得到两点x的距离
	float x = px2 - px1;
	//得到两点y的距离
	float y = py1 - py2;
	//算出斜边长度
	float xie = sqrt(pow(x,2) + pow(y,2));
	//得到这个角度的余弦值(通过三角函数中的店里：角度余弦值=斜边/斜边)
	float cosAngle = x / xie;
	//通过反余弦定理获取到期角度的弧度
	float rad = acos(cosAngle);
	//注意：当触屏的位置Y坐标<摇杆的Y坐标，我们要去反值-0~-180
	if (py2 < py1)
	{
		rad = -rad;
	}
	return rad;
}

CCPoint getAngelePosition(float r,float angle){
	return ccp(r*cos(angle),r*sin(angle));
}

//抬起事件
bool HRocker::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint point = pTouch->getLocation();
	CCSprite *rocker = (CCSprite *)this->getChildByTag(tag_rocker);
	if (rocker->boundingBox().containsPoint(point))
		isCanMove = true;
	return true;
}
//移动事件
void HRocker::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!isCanMove)
	{
		return;
	}
	CCPoint point = pTouch->getLocation();
	CCSprite *rocker = (CCSprite *)this->getChildByTag(tag_rocker);
	//得到摇杆与触屏点所形成的角度
	float angle = getRad(rockerBGPosition,point);
	//判断两个圆的圆心距是否大于摇杆背景的半径
	if (sqrt(pow((rockerBGPosition.x - point.x),2) + pow((rockerBGPosition.y - point.y),2)) >= rockerBGR)
	{
	
		//保证内部小圆运动的长度限制
		rocker->setPosition(ccpAdd(getAngelePosition(rockerBGR,angle),ccp(rockerBGPosition.x,rockerBGPosition.y)));
	}
	else
		rocker->setPosition(point);
	//判断方向
	if(angle>=-PI/4&&angle<PI/4)
	{
		rocketDirection=rocker_right;
		rocketRun=false;
	}
	else if(angle>=PI/4&&angle<3*PI/4)
	{
		rocketDirection=rocker_up;
	}
	else if((angle>=3*PI/4&&angle<=PI)||(angle>=-PI&&angle<-3*PI/4))
	{
		rocketDirection=rocker_left;
		rocketRun=true;
	}
	else if(angle>=-3*PI/4&&angle<-PI/4)
	{
		rocketDirection=rocker_down;
	}
}
//离开事件
void HRocker::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!isCanMove)
	{
		return;
	}
	CCSprite *rockerBG = (CCSprite*)this->getChildByTag(tag_rockerBG);
	CCSprite *rocker = (CCSprite*)this->getChildByTag(tag_rocker);
	rocker->stopAllActions();
	rocker->runAction(CCMoveTo::create(0.08f,rockerBG->getPosition()));
	isCanMove = false;
	rocketDirection=rocker_stay;
}
