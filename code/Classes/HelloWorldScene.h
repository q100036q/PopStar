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

	//自动创建游戏中的pop10*10的矩形方阵,传入参数为屏幕大小
	void autoCretaePopSprite(cocos2d::Size size);

	//监听手势识别
	virtual bool onTouchBegan(cocos2d::Touch *t,cocos2d::Event *e);
	
private:
	//定义pop数组
	PopSprite *popStarSprite[10][10];

	//点击得到pop对象
	PopSprite *getPopStarSprite(cocos2d::Size size,cocos2d::Point touch);
	
	//创建一个数组来存放点击的pop
	cocos2d::__Array *poparr;

	//通过传递过来的点击pop对象获取他的上下左右的数据
	cocos2d::__Array *checkPopAround(PopSprite *pop);

	//通过检测到上下左右的数据来循环检测每一个的上下左右
	void checkPopIsNew(cocos2d::__Array *arrold);

	//让空白部分被上面填充（往下落）
	void reDiessPopStar();
	void reDiessPopStarRun(int x);
	//左右移动
	void reDissPopStarRL(int x);

	//检测游戏是否结束
	bool reGameOver();
};

#endif // __HELLOWORLD_SCENE_H__
