
#include "PopSprite.h"

USING_NS_CC;

//��ʼ����Ϸ����ֵ����ȣ��߶ȣ�X�ᣬY��
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
	//���ó�ʼ����ֵ
	number = numbers;
	popX = PopSpriteX;
	popY = PopSpriteY;

	//������Ϸÿ��Pop�ı�����ɫ
	//��5��Ϊ��ÿ��ɫ��֮����һ����϶
	layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(200,190,180,255),width-3,height-3);
	//layerColorBG->setAnchorPoint(Point(0.5,0.5));
	layerColorBG->setPosition(Point(popX,popY));

	this->addChild(layerColorBG);
}

//��ȡɫ�������
cocos2d::Point PopSprite::getColorBGPoint(){
	return layerColorBG->getPosition();
}

//��ȡ����
int PopSprite::getNumber(){
	return number;
}

//��������
void PopSprite::setNumber(int num){
	number = num;
	//�ж�����������ɫ�����ɫ

	if(number == -1){
		//�����Ұ�ɫ
		layerColorBG->setColor(cocos2d::Color3B(200,190,180));
	}
	if(number == 0){
		//��ɫ
		layerColorBG->setColor(cocos2d::Color3B(250,230,40));
	}
	if(number == 1){
		//��ɫ
		layerColorBG->setColor(cocos2d::Color3B(40,180,250));
	}
	if(number == 2){
		//��ɫ
		layerColorBG->setColor(cocos2d::Color3B(130,220,110));
	}
	if(number == 3){
		//��ɫ
		layerColorBG->setColor(cocos2d::Color3B(250,80,130));
	}
	if(number == 4){
		//��ɫ
		layerColorBG->setColor(cocos2d::Color3B(180,50,250));
	}
}

//��ȡX��Y
int PopSprite::getPopX(){
	return popX;
}

int PopSprite::getPopY(){
	return popY;
}

//����X,Y
void PopSprite::setPopX(int x){
	popX = x;

}

void PopSprite::setPopY(int y){
	popY = y;
}