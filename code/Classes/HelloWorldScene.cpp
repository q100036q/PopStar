#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
	auto layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(180,170,160,255));
	this->addChild(layerColorBG);

    //�Զ�������Ϸ�е�pop10*10�ľ��η���
	autoCretaePopSprite(visibleSize);

	//���ü���
	auto touchListener = EventListenerTouchOneByOne::create();
	//���ûص��������λ��
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan,this);
	//_eventDispatcher��director �������¼��ɷ�����addEventListenerWithSceneGraphPriority�Ǹ�һ��ָ�����¼����һ���¼�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

	return true;
}

void HelloWorld::autoCretaePopSprite(cocos2d::Size size){
	//�����������
	srand(((unsigned)time(NULL)));
	//���ÿһ��pop�Ŀ�Ⱥ͸߶�
	//�����ס28�Ŀ��
	//��Ϊ�������Σ���ȸ��߶���һ����
	int lon = (size.width-30)/10;
	//ѭ��������10*10�ĵ�Ԫ��
	for(int j = 0; j<10; j++){
		for(int i = 0; i<10; i++){
			//ÿ���������������Χ0~4������Ӧ��ͬ����ɫ
			int maxX = 5;
			int minX = 0;
			//��ȡһ������� 
			int rangeX = maxX - minX;
			int actualX = (rand()%rangeX)+minX;
			//�����ֱ��ǣ���ʼ����ɫΪ-1����ȣ��߶ȣ�X������Ϊɫ����*ɫ�����+15��Y������Ϊɫ��߶�*ɫ�����+��������Ļ��1/6������
			PopSprite *pop = PopSprite::createPopSprite(-1,lon,lon,lon*j+15,lon*i+size.height/6);
			//λ��
			pop->setPopX(j); 
			pop->setPopY(i);
			//��ɫ
			pop->setNumber(actualX);
			
			addChild(pop,0);

			//pop���뵽������
			popStarSprite[j][i] = pop;
		}
	}
}

//��������ʶ��
bool HelloWorld::onTouchBegan(cocos2d::Touch *t,cocos2d::Event *e){
	//��ʼ������
	poparr = cocos2d::__Array::create();
	//��ȡ������X��Yֵ
	Point touchPo = t->getLocation();
	//��ȡ��Ļ��С
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//ͨ��������������ֵ�õ���������λ��
	PopSprite *pops = getPopStarSprite(visibleSize,touchPo);

	if(pops != NULL){
	//�����ʱ����
		//log("%d,%d",pops->getPopX(),pops->getPopY());
		poparr = checkPopAround(pops);
		if(poparr->count()>=2){

			//log("poparr:%d",poparr->count());

		checkPopIsNew(poparr);
		}else{
		return true;
		}
	}

	return true;
}

	//����õ�pop����
PopSprite *HelloWorld::getPopStarSprite(cocos2d::Size size,cocos2d::Point touch){
	//���ÿ��pop�Ŀ�ȸ��߶�
	//��͸���һ����
	int lon = (size.width-30)/10;

	//��������X��λ��
	//������ں����ϵڼ���ɫ��
	float x = (touch.x-15)/lon;
	//��������Y��λ��
	//�������ϵڼ���ɫ��
	float y = (touch.y - size.height/6)/lon;

	if(x<10 && y<10 && x>=0 &&y>=0)
	{
		int x1 = (touch.x-15)/lon;
		int y1 = (touch.y - size.height/6)/lon;
		//�����Ƿ���ȷ
		log("%d,%d",x1,y1);
		return popStarSprite[x1][y1];
	}
	else 
		return NULL;
}

//ͨ�����ݹ����ĵ��pop�����ȡ�����������ҵ�����
cocos2d::__Array *HelloWorld::checkPopAround(PopSprite *pop){
	cocos2d::__Array *arr = cocos2d::__Array::create();
	//�����Χ�������������ϵĻ�����˵���Լ�����Ҳ���أ����ֻ��һ����ô������ε��
	bool isDoublePop = false;

	//�жϵ��λ�����ϵ���ͬ��
	int up = pop->getPopY();
	for(int yu = up+1; yu<10; yu++){
		//��X��λ�ú���ɫ����һ��ɫ���Xλ�ú���ɫ��ͬʱ
		if(popStarSprite[pop->getPopX()][up]->getNumber() == popStarSprite[pop->getPopX()][yu]->getNumber()){
			
			//addObject���ָ���Ķ���
			arr->addObject(popStarSprite[pop->getPopX()][yu]);
			//������ɫ���ֱ�Ϊ-1
			//popStarSprite[pop->getPopX()][yu]->setNumber(-1);
			isDoublePop = true;
		}else{
			break;
		}
	}
	//�жϵ��λ�����µ���ͬ��
	int down = pop->getPopY();
	for(int yd = down-1; yd>=0; yd--){
		//��X��λ�ú���ɫ����һ��ɫ���Xλ�ú���ɫ��ͬʱ
		if(popStarSprite[pop->getPopX()][down]->getNumber() == popStarSprite[pop->getPopX()][yd]->getNumber()){
			
			//addObject���ָ���Ķ���
			arr->addObject(popStarSprite[pop->getPopX()][yd]);
			//������ɫ���ֱ�Ϊ-1
			//popStarSprite[pop->getPopX()][yd]->setNumber(-1);
			isDoublePop = true;
		}else{
			break;
		}
	}
	//�жϵ��λ���������ͬ��
	int left = pop->getPopX();
	for(int yl = left-1; yl>=0; yl--){
		//��X��λ�ú���ɫ����һ��ɫ���Xλ�ú���ɫ��ͬʱ
		if(popStarSprite[left][pop->getPopY()]->getNumber() == popStarSprite[yl][pop->getPopY()]->getNumber()){
			
			//addObject���ָ���Ķ���
			arr->addObject(popStarSprite[yl][pop->getPopY()]);
			//������ɫ���ֱ�Ϊ-1
		//	popStarSprite[yl][pop->getPopY()]->setNumber(-1);
			isDoublePop = true;
		}else{
			break;
		}
	}
	//�жϵ��λ�����ҵ���ͬ��
	int right = pop->getPopX();
	for(int yr = right+1; yr<10; yr++){
		//��X��λ�ú���ɫ����һ��ɫ���Xλ�ú���ɫ��ͬʱ
		if(popStarSprite[right][pop->getPopY()]->getNumber() == popStarSprite[yr][pop->getPopY()]->getNumber()){
			
			//addObject���ָ���Ķ���
			arr->addObject(popStarSprite[yr][pop->getPopY()]);
			//������ɫ���ֱ�Ϊ-1
			//popStarSprite[yr][pop->getPopY()]->setNumber(-1);
			isDoublePop = true;
		}else{
			break;
		}
	}
	//�жϵ�����Լ������
	if(isDoublePop){
		arr->addObject(popStarSprite[pop->getPopX()][pop->getPopY()]);
		//popStarSprite[pop->getPopX()][pop->getPopY()]->setNumber(-1);
	}
	//log("arr:%d",arr->count());
	return arr;
}

void HelloWorld::checkPopIsNew(cocos2d::__Array *arrold){
	//����һ���������������ȡ���µ�����
	cocos2d::__Array *arrnew = cocos2d::__Array::create();
	//ÿһ���йص�ɫ�鶼ѭ��ִ��
	for(int i = 0; i<arrold->count(); i++){
		//��ѭ�������Ѿ��õ���������ȡ��ÿһ��pop����
		PopSprite *pop = (PopSprite *)arrold->getObjectAtIndex(i);
		//��һ��pop�������Χ��û�ж��󣬱��浽arrnews��
		cocos2d::__Array *arrnews = checkPopAround(pop);
		
		//log("arrnews:%d",arrnews->count());
		
		//дһ��forѭ���ж��ҵ��Ķ������϶������¶���
		for(int j = 0; j<arrnews->count(); j++){
			//����һ�������������ж�
			bool isSave = false;
			//����ѭ�����ҵ������ж���ֳ�һ���������Ķ��󱣴浽popnew
			PopSprite *popnew = (PopSprite *)arrnews->getObjectAtIndex(j);
			//�������Ѿ��ҵ��Ķ������������Ķ������XY����ıȽϣ����ж��Ƿ����¶��󡣡������ˡ�����
			for(int k = 0; k<poparr->count(); k++){
				//�������϶������popold�У�forѭ�������������������Ƚ�
				PopSprite *popold = (PopSprite *)poparr->getObjectAtIndex(k);
				if((popnew->getPopX() == popold->getPopX())&&(popnew->getPopY() == popold->getPopY())){
					//������϶�������
					isSave = true;
					break;
				}
			}

			if(!isSave){
				//�ѵõ����µĶ�������������ݵ�����
				arrnew->addObject(popnew);
				//log("arrnew:%d",arrnew->count());
			}

		}
	}
	//�������¶��󣬰��������������ݵ�������
	if(arrnew->count()>0){
		for(int f = 0; f<arrnew->count(); f++){
			poparr->addObject(arrnew->getObjectAtIndex(f));
		}
		//�������ã������
		checkPopIsNew(arrnew);
	}else{
	//�����������
		for(int s = 0; s<poparr->count(); s++){
			PopSprite *sp = (PopSprite *)poparr->getObjectAtIndex(s);
			sp->setNumber(-1);
		}
		//�ÿհױ����
		reDiessPopStar();
	}

}

//�ÿհײ��ֱ�������䣨�����䣩
//һ���н��м�⣬�пո���ô�ͽ���
void HelloWorld::reDiessPopStar(){
	for(int x = 0; x<10; x++){
		//��Ϊ��Ҫѭ�������Լ��������½�һ������
		reDiessPopStarRun(x);
	}
	//��������ƶ������ж��Ƿ���Ҫ�����ƶ�
		for(int x = 0; x<10; x++){
			reDissPopStarRL(x);
		}
	//�����Ϸ�Ƿ����
	reGameOver();
}

void HelloWorld::reDiessPopStarRun(int x){
	//����ÿ�еĿո���������number
	int number = 0;
	for(int k = 0; k<10; k++){
		if(popStarSprite[x][k]->getNumber() == -1){
			number++;
		}
	}
	//�жϿո��Ƿ����1
	if(number>0){
		for(int y = 0; y<10; y++){
			//�ж��Ƿ�Ҫ�����ص��Լ�
			if(popStarSprite[x][y]->getNumber() == -1){
				//�Կո�����жϣ�ֵ�ǲ��ǵ���number������ǣ���ô�ÿո������һ���Ͳ���Ҫ�ٻص��Լ�ѭ���ˣ�����
				if((10-popStarSprite[x][y]->getPopY())>number){
					//���ո��滻
					for(int s = y; s<10; s++){
						//�������ϵĵģ���ô�滻�ɿո�
						if(s+1 == 10){
							popStarSprite[x][s]->setNumber(-1);
						}else{
							//������ǣ���ô��������滻
							popStarSprite[x][s]->setNumber(popStarSprite[x][s+1]->getNumber());
						}
					}
					reDiessPopStarRun(x);
				}else{
					break;
				}
			}
		}
	}
}
void HelloWorld::reDissPopStarRL(int x){
		//����ÿ�еĿո���
		int number = 0;
		for(int k = 0; k<10; k++){
			if(popStarSprite[x][k]->getNumber() == -1){
				number++;
			}
		}
	
		//�жϿո��Ƿ�Ϊ10�������ж�Ϊ��
		if(number == 10){
			for(int z = 0; z<10; z++){
				//���ո��滻
				for(int s = x; s<9; s++){	
					//��Ϊ�����ƶ�������sС��9
					popStarSprite[s][z]->setNumber(popStarSprite[s+1][z]->getNumber());
					popStarSprite[s+1][z]->setNumber(-1);
				}				
			}	
	}
}

//�����Ϸ�Ƿ����
bool HelloWorld::reGameOver(){
	bool isGameOver = true;
	for(int j = 0; j<10; j++){
		for(int i = 0; i<10; i++){
			if(checkPopAround(popStarSprite[j][i])->count()> 0 && popStarSprite[j][i]->getNumber() != -1){
				isGameOver = false;
				break;
			}
		}
		if(isGameOver == false){
			break;
		}
	}
	if(isGameOver){
		//������������ô����������¿�ʼ
		Director::getInstance()->replaceScene(TransitionFade::create(1,HelloWorld::createScene()));
	}else{
		//��Ϸ����
	}
	return isGameOver;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
