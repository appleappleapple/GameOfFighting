#include "Map.h"
Map::Map():m_map(NULL)
{

}
Map::~Map()
{

}
void Map::InitMap(const char *map_name,const CCSize &window_size)
{
	this->m_map=CCSprite::create(map_name);
	m_map->setAnchorPoint(ccp(0,0));//设置锚点
	this->setAnchorPoint(ccp(0,0));//设置锚点
	this->addChild(m_map);



}
void Map::MoveMap(CCNode *hero,CCSize visibleSize)//
{
	if(hero->getPositionX()==visibleSize.width/2)//精灵运动到中间，地图才移动
	{
		if(this->getPositionX()!=-(m_map->getContentSize().width-visibleSize.width))//防止地图左边运动后超出边缘
		this->setPosition(this->getPositionX()-1,this->getPositionY());
	}
}
bool Map::JudgeMap(CCNode *hero,CCSize visibleSize)
{
	if(this->getPositionX()!=-(m_map->getContentSize().width-visibleSize.width))//防止地图左边运动后超出边缘
		return false;
	else //地图已经移动到达边缘
	return true;
}

