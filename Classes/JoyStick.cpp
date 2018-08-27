#include "JoyStick.h"
#include "Hero.h"
#include "CommonData.h"
USING_NS_CC;

bool JoyStick::init()
{

	if (!Layer::init()) {
		return false;
	}

	/*1. ����ҡ�˵ı���*/
	this->rocker_bg = Sprite::create("yaogancir1.png");
	rocker_bg->setPosition(Point(150, 150));
	addChild(rocker_bg,99,10);
	this->setVisible(false);

	/*2. ����ҡ��*/
	this->rocker = Sprite::create("yaogandot1.png");
	rocker->setPosition(Point(150, 150));
	addChild(rocker,99,11);
	this->setVisible(false);
	touchsucceed = false;

	return true;
}

void JoyStick::onEnter()
{
	/*���ȵ��ø����onEnter����*/
	Layer::onEnter();

	/*�������㴥���ļ���, ������auto*/
	listener = EventListenerTouchOneByOne::create();

	/*����ʹ��lambda���ʽ��������������������̫��, �������ǻ���ʹ�ûص�����*/
	listener->onTouchBegan = CC_CALLBACK_2(JoyStick::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(JoyStick::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(JoyStick::onTouchEnded, this);

	/*ע�����*/
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

/*��ǰ����Ӹ������Ƴ�ʱ����ø÷���*/
void JoyStick::onExit()
{
	/*�ӷַ������Ƴ�ע��ļ���*/
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

	/*�����ø����onExit()����*/
	Layer::onExit();
}

bool JoyStick::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	if (touch->getLocation().x < VISIBLE_SIZE.width / 2){
		this->setVisible(true);
		/*��������ʼ��ʱ�� ����������λ�ú��������ĵ�λ�õľ��� < Բ�İ뾶 ���ǲ���Move*/
		/*��ȡ������λ��*/
		Point touch_pos = touch->getLocation();
		//��ȡԲ�ĵ�
		Point center = touch_pos;
		center_x = touch_pos.x;
		center_y = touch_pos.y;
		//ҡ�˰뾶
		radius = rocker_bg->getContentSize().width / 2;
		rocker->setPosition(touch_pos);
		this->getChildByTag(11)->setPosition(center);
		this->getChildByTag(10)->setPosition(center);
		touchsucceed = true;
		return true;
	}

}

void JoyStick::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	if (touchsucceed){
		/*�������ƶ���ʱ�� ����������λ�ú��������ĵ�λ�õľ��� < Բ�İ뾶 */
		/*��ȡ������λ��*/
		Point touch_pos = touch->getLocation();
		/*��ȡԲ�ĵ�*/
		float dis = sqrt(pow((touch->getLocation().x - center_x), 2) + pow((touch->getLocation().y - center_y), 2));
		float angle = acos((touch_pos.x - center_x) / dis);

		if (dis <= radius) {
			rocker->setPosition(Point(touch_pos));
		}
		else {
			/*������ϰ�Բ*/
			if (touch_pos.y >  center_y) {
				rocker->setPosition(Point(center_x + radius*cos(angle), center_y + radius*sin(angle)));
			}
			else {
				rocker->setPosition(Point(center_x + radius*cos(angle), center_y - radius*sin(angle)));
			}
		}
		if (touch_pos.x > center_x){
			hero->setWalking(false, Hero::BTN_LEFT);
			hero->setWalking(true, Hero::BTN_RIGHT);
		}
		else{
			hero->setWalking(false, Hero::BTN_RIGHT);
			hero->setWalking(true, Hero::BTN_LEFT);

		}
	}

}

void JoyStick::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	/*�ڽ�������ʱ��ҡ����ʧ*/
	this->setVisible(false);
	touchsucceed = false;
	hero->setWalking(false, Hero::BTN_RIGHT);
	hero->setWalking(false, Hero::BTN_LEFT);
}

void JoyStick::setHero(Hero* h){
	this->hero = h;
}
