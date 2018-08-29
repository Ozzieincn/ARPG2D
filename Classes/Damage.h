#ifndef __DAMAGE_H__
#define __DAMAGE_H__

#include "cocos2d.h"

class Damage : public cocos2d::Sprite {
public:
	float changeDamageValue(bool);

	static bool loadResources(); // resource loader, carried once

	bool init(int,float);

	static Damage* create(int,float);

	void initPhysicsBody();

	bool initSprite(std::string);

private:
	float m_fDamageValue;

	int m_Group;//source
};

#endif