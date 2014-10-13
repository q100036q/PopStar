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

    //自动创建游戏中的pop10*10的矩形方阵
	autoCretaePopSprite(visibleSize);

	//设置监听
	auto touchListener = EventListenerTouchOneByOne::create();
	//设置回调监听点击位置
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan,this);
	//_eventDispatcher是director 关联的事件派发器，addEventListenerWithSceneGraphPriority是给一个指定的事件添加一个事件侦听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

	return true;
}

void HelloWorld::autoCretaePopSprite(cocos2d::Size size){
	//加入随机种子
	srand(((unsigned)time(NULL)));
	//求出每一个pop的宽度和高度
	//左边留住28的宽度
	//因为是正方形，宽度跟高度是一样的
	int lon = (size.width-30)/10;
	//循环，创建10*10的单元格
	for(int j = 0; j<10; j++){
		for(int i = 0; i<10; i++){
			//每次生成随机数（范围0~4），对应不同的颜色
			int maxX = 5;
			int minX = 0;
			//获取一个随机数 
			int rangeX = maxX - minX;
			int actualX = (rand()%rangeX)+minX;
			//参数分别是：初始化颜色为-1，宽度，高度，X轴坐标为色块宽度*色块个数+15，Y轴坐标为色块高度*色块个数+从整个屏幕的1/6初创建
			PopSprite *pop = PopSprite::createPopSprite(-1,lon,lon,lon*j+15,lon*i+size.height/6);
			//位置
			pop->setPopX(j); 
			pop->setPopY(i);
			//颜色
			pop->setNumber(actualX);
			
			addChild(pop,0);

			//pop加入到数组中
			popStarSprite[j][i] = pop;
		}
	}
}

//监听手势识别
bool HelloWorld::onTouchBegan(cocos2d::Touch *t,cocos2d::Event *e){
	//初始化数组
	poparr = cocos2d::__Array::create();
	//获取触摸的X和Y值
	Point touchPo = t->getLocation();
	//获取屏幕大小
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//通过传入上面两个值得到触摸对象位置
	PopSprite *pops = getPopStarSprite(visibleSize,touchPo);

	if(pops != NULL){
	//点击的时候检测
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

	//点击得到pop对象
PopSprite *HelloWorld::getPopStarSprite(cocos2d::Size size,cocos2d::Point touch){
	//求出每个pop的宽度跟高度
	//宽和高是一样的
	int lon = (size.width-30)/10;

	//求出点击的X的位置
	//即求出在横轴上第几个色块
	float x = (touch.x-15)/lon;
	//求出点击的Y的位置
	//求纵轴上第几个色块
	float y = (touch.y - size.height/6)/lon;

	if(x<10 && y<10 && x>=0 &&y>=0)
	{
		int x1 = (touch.x-15)/lon;
		int y1 = (touch.y - size.height/6)/lon;
		//测试是否正确
		log("%d,%d",x1,y1);
		return popStarSprite[x1][y1];
	}
	else 
		return NULL;
}

//通过传递过来的点击pop对象获取他的上下左右的数据
cocos2d::__Array *HelloWorld::checkPopAround(PopSprite *pop){
	cocos2d::__Array *arr = cocos2d::__Array::create();
	//如果周围对象有两个以上的话，就说明自己对象也返回，如果只有一个那么忽略这次点击
	bool isDoublePop = false;

	//判断点击位置往上的相同数
	int up = pop->getPopY();
	for(int yu = up+1; yu<10; yu++){
		//当X的位置和颜色与上一个色块的X位置和颜色相同时
		if(popStarSprite[pop->getPopX()][up]->getNumber() == popStarSprite[pop->getPopX()][yu]->getNumber()){
			
			//addObject添加指定的对象
			arr->addObject(popStarSprite[pop->getPopX()][yu]);
			//设置颜色数字变为-1
			//popStarSprite[pop->getPopX()][yu]->setNumber(-1);
			isDoublePop = true;
		}else{
			break;
		}
	}
	//判断点击位置往下的相同数
	int down = pop->getPopY();
	for(int yd = down-1; yd>=0; yd--){
		//当X的位置和颜色与上一个色块的X位置和颜色相同时
		if(popStarSprite[pop->getPopX()][down]->getNumber() == popStarSprite[pop->getPopX()][yd]->getNumber()){
			
			//addObject添加指定的对象
			arr->addObject(popStarSprite[pop->getPopX()][yd]);
			//设置颜色数字变为-1
			//popStarSprite[pop->getPopX()][yd]->setNumber(-1);
			isDoublePop = true;
		}else{
			break;
		}
	}
	//判断点击位置往左的相同数
	int left = pop->getPopX();
	for(int yl = left-1; yl>=0; yl--){
		//当X的位置和颜色与上一个色块的X位置和颜色相同时
		if(popStarSprite[left][pop->getPopY()]->getNumber() == popStarSprite[yl][pop->getPopY()]->getNumber()){
			
			//addObject添加指定的对象
			arr->addObject(popStarSprite[yl][pop->getPopY()]);
			//设置颜色数字变为-1
		//	popStarSprite[yl][pop->getPopY()]->setNumber(-1);
			isDoublePop = true;
		}else{
			break;
		}
	}
	//判断点击位置往右的相同数
	int right = pop->getPopX();
	for(int yr = right+1; yr<10; yr++){
		//当X的位置和颜色与上一个色块的X位置和颜色相同时
		if(popStarSprite[right][pop->getPopY()]->getNumber() == popStarSprite[yr][pop->getPopY()]->getNumber()){
			
			//addObject添加指定的对象
			arr->addObject(popStarSprite[yr][pop->getPopY()]);
			//设置颜色数字变为-1
			//popStarSprite[yr][pop->getPopY()]->setNumber(-1);
			isDoublePop = true;
		}else{
			break;
		}
	}
	//判断点击到自己的情况
	if(isDoublePop){
		arr->addObject(popStarSprite[pop->getPopX()][pop->getPopY()]);
		//popStarSprite[pop->getPopX()][pop->getPopY()]->setNumber(-1);
	}
	//log("arr:%d",arr->count());
	return arr;
}

void HelloWorld::checkPopIsNew(cocos2d::__Array *arrold){
	//创建一个新数组来保存获取到新的数据
	cocos2d::__Array *arrnew = cocos2d::__Array::create();
	//每一个有关的色块都循环执行
	for(int i = 0; i<arrold->count(); i++){
		//用循环来从已经得到的数据中取出每一个pop对象
		PopSprite *pop = (PopSprite *)arrold->getObjectAtIndex(i);
		//第一个pop对象的周围有没有对象，保存到arrnews中
		cocos2d::__Array *arrnews = checkPopAround(pop);
		
		//log("arrnews:%d",arrnews->count());
		
		//写一个for循环判断找到的对象是老对象还是新对象
		for(int j = 0; j<arrnews->count(); j++){
			//定义一个布尔类型做判断
			bool isSave = false;
			//再用循环将找到的所有对象分成一个个单独的对象保存到popnew
			PopSprite *popnew = (PopSprite *)arrnews->getObjectAtIndex(j);
			//把所有已经找到的对象跟这个单独的对象进行XY坐标的比较，来判断是否是新对象。。。醉了——！
			for(int k = 0; k<poparr->count(); k++){
				//把所有老对象存入popold中，for循环把它跟单独对象来比较
				PopSprite *popold = (PopSprite *)poparr->getObjectAtIndex(k);
				if((popnew->getPopX() == popold->getPopX())&&(popnew->getPopY() == popold->getPopY())){
					//如果是老对象，跳出
					isSave = true;
					break;
				}
			}

			if(!isSave){
				//把得到了新的对象加入存放新数据的数组
				arrnew->addObject(popnew);
				//log("arrnew:%d",arrnew->count());
			}

		}
	}
	//若真有新对象，把它加入存放老数据的数组中
	if(arrnew->count()>0){
		for(int f = 0; f<arrnew->count(); f++){
			poparr->addObject(arrnew->getObjectAtIndex(f));
		}
		//迭代调用，来检测
		checkPopIsNew(arrnew);
	}else{
	//清空所有数据
		for(int s = 0; s<poparr->count(); s++){
			PopSprite *sp = (PopSprite *)poparr->getObjectAtIndex(s);
			sp->setNumber(-1);
		}
		//让空白被填充
		reDiessPopStar();
	}

}

//让空白部分被上面填充（往下落）
//一列列进行检测，有空格那么就交换
void HelloWorld::reDiessPopStar(){
	for(int x = 0; x<10; x++){
		//因为需要循环调用自己，所以新建一个方法
		reDiessPopStarRun(x);
	}
	//完成上下移动发后，判断是否需要左右移动
		for(int x = 0; x<10; x++){
			reDissPopStarRL(x);
		}
	//检测游戏是否结束
	reGameOver();
}

void HelloWorld::reDiessPopStarRun(int x){
	//检测出每列的空格数，存入number
	int number = 0;
	for(int k = 0; k<10; k++){
		if(popStarSprite[x][k]->getNumber() == -1){
			number++;
		}
	}
	//判断空格是否大于1
	if(number>0){
		for(int y = 0; y<10; y++){
			//判断是否要继续回调自己
			if(popStarSprite[x][y]->getNumber() == -1){
				//对空格进行判断，值是不是等于number，如果是，那么该空格是最顶上一个就不需要再回调自己循环了，跳出
				if((10-popStarSprite[x][y]->getPopY())>number){
					//将空格替换
					for(int s = y; s<10; s++){
						//如果是最顶上的的，那么替换成空格
						if(s+1 == 10){
							popStarSprite[x][s]->setNumber(-1);
						}else{
							//如果不是，那么用上面的替换
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
		//检测出每列的空格数
		int number = 0;
		for(int k = 0; k<10; k++){
			if(popStarSprite[x][k]->getNumber() == -1){
				number++;
			}
		}
	
		//判断空格是否为10，即整列都为空
		if(number == 10){
			for(int z = 0; z<10; z++){
				//将空格替换
				for(int s = x; s<9; s++){	
					//因为向左移动，所以s小于9
					popStarSprite[s][z]->setNumber(popStarSprite[s+1][z]->getNumber());
					popStarSprite[s+1][z]->setNumber(-1);
				}				
			}	
	}
}

//检测游戏是否结束
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
		//如果结束，调用创建方法重新开始
		Director::getInstance()->replaceScene(TransitionFade::create(1,HelloWorld::createScene()));
	}else{
		//游戏继续
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
