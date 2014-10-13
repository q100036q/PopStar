
#include "PopSprite.h"

USING_NS_CC;

//初始化游戏的数值，宽度，高度，X轴，Y轴
PopSprite *PopSprite::createPopSprite(int numbers,int width,int height,float PopSpriteX,float PopSpriteY){
	PopSprite *enemy = new PopSprite();
	if (enemy && enemy->init()){
		enemy->autorelease();
		enemy->enemyInit(numbers,width,height,PopSpriteX,PopSpriteY);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool PopSprite::init(){
	if(!Sprite::init()){
		return false;
	}
	return true;
}

void PopSprite::enemyInit(int numbers,int width,int height,float PopSpriteX,float PopSpriteY){
	//设置初始化的值
	number = numbers;
	popX = PopSpriteX;
	popY = PopSpriteY;

	//加入游戏每个Pop的背景颜色
	//减5是为了每个色块之间留一条缝隙
	layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(200,190,180,255),width-3,height-3);
	//layerColorBG->setAnchorPoint(Point(0.5,0.5));
	layerColorBG->setPosition(Point(popX,popY));

	this->addChild(layerColorBG);
}

//获取色块的坐标
cocos2d::Point PopSprite::getColorBGPoint(){
	return layerColorBG->getPosition();
}

//获取数字
int PopSprite::getNumber(){
	return number;
}

//设置数字
void PopSprite::setNumber(int num){
	number = num;
	//判断数字来调整色块的颜色

	if(number == -1){
		//背景灰白色
		layerColorBG->setColor(cocos2d::Color3B(200,190,180));
	}
	if(number == 0){
		//黄色
		layerColorBG->setColor(cocos2d::Color3B(250,230,40));
	}
	if(number == 1){
		//蓝色
		layerColorBG->setColor(cocos2d::Color3B(40,180,250));
	}
	if(number == 2){
		//绿色
		layerColorBG->setColor(cocos2d::Color3B(130,220,110));
	}
	if(number == 3){
		//红色
		layerColorBG->setColor(cocos2d::Color3B(250,80,130));
	}
	if(number == 4){
		//紫色
		layerColorBG->setColor(cocos2d::Color3B(180,50,250));
	}
}

//获取X，Y
int PopSprite::getPopX(){
	return popX;
}

int PopSprite::getPopY(){
	return popY;
}

//设置X,Y
void PopSprite::setPopX(int x){
	popX = x;

}

void PopSprite::setPopY(int y){
	popY = y;
}