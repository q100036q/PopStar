
#ifndef __PopStar__PopSprite__
#define __PopStar__PopSprite__

#include "cocos2d.h"

class PopSprite : public cocos2d::Sprite{
public:
	//��ʼ����Ϸ����ֵ����ȣ��߶ȣ�X�ᣬY��
	static PopSprite *createPopSprite(int numbers,int width,int height,float PopSpriteX,float PopSpriteY);
	virtual bool init();
	CREATE_FUNC(PopSprite);
	
	//��ȡ����
	int getNumber();
	//��������
	void setNumber(int num);
	
	//��ȡɫ�������
	cocos2d::Point getColorBGPoint();

	//��ȡpop��λ��
	int popX,popY;
	//��ȡX��Y
	int getPopX();
	int getPopY();
	//����X,Y
	void setPopX(int x);
	void setPopY(int y);
public:
	//��ʾ��ɫ
	int number;
	void enemyInit(int numbers,int width,int height,float PopSpriteX,float PopSpriteY);
	//��ʾ�ı���
	cocos2d::LayerColor *layerColorBG;
};

#endif