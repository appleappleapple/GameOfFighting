#ifndef __PROGRESSVIEW_H__
#define __PROGRESSVIEW_H__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT; 

class ProgressView : public CCNode
{
public:
    ProgressView();
	~ProgressView();
public:
	//设置血条背景
    void setBackgroundTexture(const char *pName);
	//设置血条前景
    void setForegroundTexture(const char *pName);
	//设置总血量
    void setTotalProgress(float total);
	//设置当前血量
    void setCurrentProgress(float progress);
	//得到当前血量
    float getCurrentProgress() const;
	//得到总血量
    float getTotalProgress() const;




private:
	//设置前景血条显示的长度
    void setForegroundTextureRect(const CCRect &rect);

private:
    CCSprite *m_progressBackground;//背景血条
    CCSprite *m_progressForeground;//前景血条
    float m_totalProgress;//总血量
    float m_currentProgress;//当前血量
    float m_scale;//放大倍数
};

#endif