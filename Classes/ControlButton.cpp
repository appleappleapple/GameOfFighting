#include "ControlButton.h"
ControlButton::ControlButton():controlBtn(0),isTouch(0)
{
	
}
ControlButton::~ControlButton()
{

}
void ControlButton::CreateButton(const char* name_png,const char* button_title,unsigned int num)
{
	//得到按钮图片的大小 
	CCScale9Sprite* btn = CCScale9Sprite::create(name_png);  
	int  png_height=static_cast<int>(btn->getContentSize().height);
	int  png_width=static_cast<int>( btn->getContentSize().width);
	btn->release();

	//要显示的图片大小 
	CCRect rect = CCRectMake(0,0,png_width,png_height);   //图片的大小  
	CCRect rectInsets = CCRectMake(1,1,1,1); //left，right，width，height  
//	CCRect rectInsets = CCRectMake(2,2,png_width-4,png_height-4); //left，right，width，height 

	//按钮标题,Marker Felt为字体类型，png_height为字体高度
	CCLabelTTF *title = CCLabelTTF::create(button_title, "Marker Felt",png_height);  
	title->setOpacity(num);//设置可见度,让文字可见或不可见

	//正常状态下的按钮图片 
	CCScale9Sprite *btnNormal = CCScale9Sprite::create(name_png,rect,rectInsets);  
	
	//创建按钮
	controlBtn = CCControlButton::create(title,btnNormal); 

	//绑定事件
	BindButtonEven();
	this->addChild(controlBtn); 

	
}
void ControlButton::BindButtonEven()
{
	if(!controlBtn)
		return;
	controlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButton::touchDownAction),CCControlEventTouchDown);  
	controlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButton::touchDragEnter),CCControlEventTouchDragEnter);  
	controlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButton::touchDragExit),CCControlEventTouchDragExit);  
	controlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButton::touchDragInside),CCControlEventTouchDragInside);  	
	controlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButton::touchDragOutside),CCControlEventTouchDragOutside);  	
	controlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButton::touchUpInside),CCControlEventTouchUpInside);  
	controlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButton::touchUpOutside),CCControlEventTouchUpOutside);  
	controlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButton::touchCancel),CCControlEventTouchCancel); 
}
/* 当鼠标处于按下并曾经点中按钮时，则触发一次 */  
void ControlButton::touchDownAction(CCObject* pSender, CCControlEvent event)
{
		isTouch=true;

}
/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标进入按钮范围，则触发一次 */  
void ControlButton::touchDragEnter(CCObject* pSender, CCControlEvent event)
{

}
/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标离开按钮范围，则触发一次 */  
void ControlButton::touchDragExit(CCObject* pSender, CCControlEvent event)
{
	
}
/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标进入按钮范围，则触发，只要达到条件，就不断触发 */  
void ControlButton::touchDragInside(CCObject* pSender, CCControlEvent event)
{

}
/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标离开按钮范围，则触发，只要达到条件，就不断触发 */  
void ControlButton::touchDragOutside(CCObject* pSender, CCControlEvent event)
{
}
/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标松开且在按钮范围内，则触发一次 */  
void ControlButton::touchUpInside(CCObject* pSender, CCControlEvent event)
{
		isTouch=false;

}

/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标松开且在按钮范围外，则触发一次 */  
void ControlButton::touchUpOutside(CCObject* pSender, CCControlEvent event)
{
	
}
/* 暂时没有发现能用鼠标触发这个事件的操作，看了注释，应该是由其它事件中断按钮事件而触发的 */ 
void ControlButton::touchCancel(CCObject* pSender, CCControlEvent event)
{

}