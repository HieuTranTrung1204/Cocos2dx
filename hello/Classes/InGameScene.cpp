#include "InGameScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

Scene* InGameScene::createScene()
{
	return InGameScene::create();
}

// on "init" you need to initialize your instance
bool InGameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Background
	background = Layer::create();
	this->addChild(background);

	auto background1 = Sprite::create("background.png");
	background1->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	auto background2 = Sprite::create("background.png");
	background2->setPosition(Vec2(background1->getPosition().x,
		background1->getPosition().y + background1->getContentSize().height));

	// Add Event Touch 
	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(InGameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(InGameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(InGameScene::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(InGameScene::onTouchCancelled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	// Add Event Touch End

	Vec2 pointStart = Vec2(320, 250);
	auto begin = Sprite::create("begin.png");
	begin->setPosition(pointStart);

	background->addChild(background1);
	background->addChild(background2);
	background->addChild(begin);

	Size backgroundSize = background1->getContentSize();
	{
		auto border = Sprite::create("red_border.png");
		float scale = backgroundSize.height / border->getContentSize().height;
		border->setScaleY(scale);
		border->setPosition(Vec2(border->getContentSize().width / 2, backgroundSize.height / 2));
		background->addChild(border);
	}
	{
		auto border = Sprite::create("red_border.png");
		float scale = backgroundSize.height / border->getContentSize().height;
		border->setScaleY(scale);
		border->setPosition(Vec2( visibleSize.width - border->getContentSize().width / 2, backgroundSize.height / 2));
		background->addChild(border);
	}
	// Obstacle
	Vec2 circlePointStart = Vec2(400, 800);
	circle = ObstacleCircel::create(circlePointStart);
	circle->setPosition(Vec2(400, 800));
	addChild(circle);

	player = Player::create(pointStart);
	player->mState = PlayerState::Rotate;
	addChild(player);

	this->scheduleUpdate();
	return true;
}


// called when the touch first begins
bool InGameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	Point touchPoint = touch->getLocation();
	CCLOG("Touch %f - %f", touchPoint.x, touchPoint.y);

	player->mState = PlayerState::Orientation;
	return true; // true if the function wants to swallow the touch
}

// called when the user moves their finger
void InGameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{

}

// called when the user lifts their finger
void InGameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	player->mState = PlayerState::Stationary;
	CCLOG("rotate: %d", player->rotate);

	float dis = Director::getInstance()->getWinSize().height
		 * player->parent *0.01f 
		- player->getBall()->getPosition().y;
	float angle = player->rotate;
	float radius = CC_DEGREES_TO_RADIANS(angle);
	float x = dis * sinf(radius);
	float y = dis * cosf(radius);

	Vec2 denta = Vec2(x, y);
	player->Move(denta);

	auto move_ease_in = EaseOut::create(MoveBy::create(1.75f, Vec2(0, y)), 2.0f);
	auto action = Sequence::create( move_ease_in, nullptr);
	auto cam = Camera::getDefaultCamera();
	cam->runAction(action);
}

// called when the device goes to another application such as a phone call
void InGameScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{

}

void InGameScene::update(float dt)
{
	float r2 = player->getBall()->getContentSize().width + circle->getRadius();
	float dis = player->getPosition().distance(circle->getPosition());
	if(dis < r2)
	{
		circle->isCollision = true;
		CCLOG("Player ball detect collision .......");
	}
	else
	{
		circle->isCollision = false;
	}
}