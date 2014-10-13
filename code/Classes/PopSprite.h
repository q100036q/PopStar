
#ifndef __PopStar__PopSprite__
#define __PopStar__PopSprite__

#include "cocos2d.h"

class PopSprite : public cocos2d::Sprite{
public:
	//初始化游戏的数值，宽度，高度，X轴，Y轴
	static PopSprite *createPopSprite(int numbers,int width,int height,float PopSpriteX,float PopSpriteY);
	virtual bool init();
	CREATE_FUNC(PopSprite);
	
	//获取数字
	int getNumber();
	//设置数字
	void setNumber(int num);
	
	//获取色块的坐标
	cocos2d::Point getColorBGPoint();

	//获取pop的位置
	int popX,popY;
	//获取X，Y
	int getPopX();
	int getPopY();
	//设置X,Y
	void setPopX(int x);
	void setPopY(int y);
public:
	//显示颜色
	int number;
	void enemyInit(int numbers,int width,int height,float PopSpriteX,float PopSpriteY);
	//显示的背景
	cocos2d::LayerColor *layerColorBG;
};

#endif