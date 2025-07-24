#include <Geode/modify/PlayerFireBoostSprite.hpp>

using namespace geode::prelude;

class $modify(CustomFireBoost, PlayerFireBoostSprite) {
	static PlayerFireBoostSprite* create() {
		PlayerFireBoostSprite* ret = PlayerFireBoostSprite::create();

		auto manager = GameManager::sharedState();
		
		auto mainTintFire = CCSprite::createWithSpriteFrameName("c_fireBoost_001.png"_spr);
		auto secondaryTintFire = CCSprite::createWithSpriteFrameName("c_fireBoost_2_001.png"_spr);
		auto noTintFire = CCSprite::createWithSpriteFrameName("c_fireBoost_noTint_001.png"_spr);

		ret->setDisplayFrame(noTintFire->displayFrame());

		ret->addChild(secondaryTintFire, -1);
		ret->addChild(mainTintFire, -2);

		mainTintFire->setPosition({ret->getContentSize().width / 2, ret->getContentSize().height / 2});
		secondaryTintFire->setPosition({ret->getContentSize().width / 2, ret->getContentSize().height / 2});

		mainTintFire->setColor(manager->colorForIdx(manager->getPlayerColor()));
		secondaryTintFire->setColor(manager->colorForIdx(manager->getPlayerColor2()));

		return ret;
	}
};