#ifndef __ControlButton_H__
#define __ControlButton_H__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT; 
class ControlButton :public CCNode
{
public:
	ControlButton();
	~ControlButton();
	CREATE_FUNC(ControlButton);
	//创建普通按钮,其中name_png为按钮的背景图片，button_title为按钮图片上要显示的文字，num为文字的透明度0-100，0为透明
	 void CreateButton(const char* name_png,const char* button_title="0",unsigned int num=0);

	//绑写按钮事件 
	void BindButtonEven();


	/* 当鼠标处于按下并曾经点中按钮时，则触发一次 */ 
	virtual void touchDownAction(CCObject* pSender, CCControlEvent event); 
	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标进入按钮范围，则触发一次 */  
	virtual void touchDragEnter(CCObject* pSender, CCControlEvent event);  
	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标离开按钮范围，则触发一次 */  
	 virtual void touchDragExit(CCObject* pSender, CCControlEvent event);  
	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标进入按钮范围，则触发，只要达到条件，就不断触发 */  
	 virtual void touchDragInside(CCObject* pSender, CCControlEvent event);  
	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标离开按钮范围，则触发，只要达到条件，就不断触发 */ 
	 virtual void touchDragOutside(CCObject* pSender, CCControlEvent event);  
	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标松开且在按钮范围内，则触发一次 */
	 virtual void touchUpInside(CCObject* pSender, CCControlEvent event);  
	/* 当鼠标处于按下并曾经点中按钮的状态下，鼠标松开且在按钮范围外，则触发一次 */  
	 virtual void touchUpOutside(CCObject* pSender, CCControlEvent event);  
	/* 暂时没有发现能用鼠标触发这个事件的操作，看了注释，应该是由其它事件中断按钮事件而触发的 */ 
	virtual void touchCancel(CCObject* pSender, CCControlEvent event);

	//是否按下按钮
	bool isTouch;
	//按钮控件变量
	CCControlButton* controlBtn;
private:

};
#endif 