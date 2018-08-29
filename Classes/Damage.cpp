#include "Damage.h"
#include "CommonData.h"
#include "Hero.h"
USING_NS_CC;

bool Damage::init(int source,float damageValue)
{

	m_fDamageValue=damageValue;

	m_Group=source;
	
	return true;
}

bool Damage::initSprite(std::string name) {
	/*
	if( this->initWithSpriteFrameName(name) ){
		this->setContentSize(this->getTextureRect().size);
		return 1;
	}
	return 0;
	*/
	return this->initWithFile(name);
}

Damage* Damage::create(int source,float damageValue){
	auto p=new Damage();
	if(p && p->init(source,damageValue))
	{
		p->autorelease();
		return p;
	}
	else
	{
		delete p;
		p=nullptr;
		return nullptr;
	}
}
void Damage::initPhysicsBody()
{
	auto body = PhysicsBody::createBox(this->getContentSize());
	body->getShape(0)->setRestitution(0.0f);
	body->getShape(0)->setFriction(0.0f);
	body->setCategoryBitmask(PhysicsMask::damage);
	body->setContactTestBitmask(PhysicsMask::hero);
	body->setCollisionBitmask(0);
	body->setRotationEnable(false);
	body->setGravityEnable(false);
	this->setPhysicsBody(body);

	//¼àÌýÆ÷
	auto listener=EventListenerPhysicsContact::create();
	listener->onContactBegin=[=](PhysicsContact& contact) -> bool {
		auto a=contact.getShapeA()->getBody();
		auto b=contact.getShapeB()->getBody();
		if(b->getCategoryBitmask()==PhysicsMask::damage 
			&& a->getCategoryBitmask()==PhysicsMask::hero)
			std::swap(a,b);
		if(a->getCategoryBitmask()==PhysicsMask::damage 
			&& b->getCategoryBitmask()==PhysicsMask::hero)
		{
			((Hero*)b->getNode())->causeDamage(this->m_fDamageValue);
			this->m_fDamageValue=0;
			this->removeFromParentAndCleanup(true);

		}
		//CCLOG("hit\n");
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}


float Damage::changeDamageValue(bool  enemyOrNot)
{
	//Hero* hero;
	if(enemyOrNot)
	{
		m_fDamageValue=this->m_fDamageValue- 1;//hero->causeDamage(3);

	}
	else
	{
		//
	}
	return m_fDamageValue;
}

