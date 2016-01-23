#include "ProgressView.h"

ProgressView::ProgressView()
	: m_progressBackground(NULL)
	, m_progressForeground(NULL)
	, m_totalProgress(0.0f)
	, m_currentProgress(0.0f)
	, m_scale(1.0f)
{	
	


}
ProgressView::~ProgressView()
{
	//CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,"jian_xue");//移除观察者
	CCNotificationCenter::sharedNotificationCenter()->purgeNotificationCenter(); // 释放通知中心对象
}
void ProgressView::setBackgroundTexture( const char *pName )
{
    m_progressBackground = CCSprite::create(pName);
    this->addChild(m_progressBackground);
}

void ProgressView::setForegroundTexture( const char *pName )
{
    m_progressForeground = CCSprite::create(pName);
    m_progressForeground->setAnchorPoint(ccp(0.0f, 0.5f));//设置锚点
    m_progressForeground->setPosition(ccp(-m_progressForeground->getContentSize().width * 0.5f, 0));
    this->addChild(m_progressForeground);
}

void ProgressView::setTotalProgress( float total )
{
    if (m_progressForeground == NULL) {return;}
    m_scale = m_progressForeground->getContentSize().width / total;
    m_totalProgress = total;
}

void ProgressView::setCurrentProgress( float progress )
{
    if (m_progressForeground == NULL) {return;}
    if (progress < 0.0f) {progress = 0.0f;}
    if (progress > m_totalProgress) {progress = m_totalProgress;}
    m_currentProgress = progress;
    float rectWidth = progress * m_scale;
    const CCPoint from = m_progressForeground->getTextureRect().origin;
    const CCRect rect = CCRectMake(from.x, from.y, rectWidth, m_progressForeground->getContentSize().height);
    setForegroundTextureRect(rect);

}

void ProgressView::setForegroundTextureRect( const CCRect &rect )
{
    m_progressForeground->setTextureRect(rect);
}



float ProgressView::getCurrentProgress() const
{

    return m_currentProgress;
}

float ProgressView::getTotalProgress() const
{
    return m_totalProgress;
}

