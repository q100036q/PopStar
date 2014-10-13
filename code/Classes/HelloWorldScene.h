#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PopSprite.h"



class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	//�Զ�������Ϸ�е�pop10*10�ľ��η���,�������Ϊ��Ļ��С
	void autoCretaePopSprite(cocos2d::Size size);

	//��������ʶ��
	virtual bool onTouchBegan(cocos2d::Touch *t,cocos2d::Event *e);
	
private:
	//����pop����
	PopSprite *popStarSprite[10][10];

	//����õ�pop����
	PopSprite *getPopStarSprite(cocos2d::Size size,cocos2d::Point touch);
	
	//����һ����������ŵ����pop
	cocos2d::__Array *poparr;

	//ͨ�����ݹ����ĵ��pop�����ȡ�����������ҵ�����
	cocos2d::__Array *checkPopAround(PopSprite *pop);

	//ͨ����⵽�������ҵ�������ѭ�����ÿһ������������
	void checkPopIsNew(cocos2d::__Array *arrold);

	//�ÿհײ��ֱ�������䣨�����䣩
	void reDiessPopStar();
	void reDiessPopStarRun(int x);
	//�����ƶ�
	void reDissPopStarRL(int x);

	//�����Ϸ�Ƿ����
	bool reGameOver();
};

#endif // __HELLOWORLD_SCENE_H__
