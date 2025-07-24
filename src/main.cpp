#include <Geode/modify/PlayerFireBoostSprite.hpp>

using namespace geode::prelude;

auto modEnabled = Mod::get()->getSettingValue<bool>("enable-mod");
auto swapColors = Mod::get()->getSettingValue<bool>("swap-colors");
auto useCustomColors = Mod::get()->getSettingValue<bool>("use-custom-colors");

auto c_Col1 = Mod::get()->getSettingValue<cocos2d::ccColor3B>("custom-col1");
auto c_Col2 = Mod::get()->getSettingValue<cocos2d::ccColor3B>("custom-col2");
auto c_ColWhite = Mod::get()->getSettingValue<cocos2d::ccColor3B>("custom-colwhite");

$on_mod(Loaded) {
	listenForSettingChanges("enable-mod", [](bool value) {
        modEnabled = value;
    });
	listenForSettingChanges("swap-colors", [](bool value) {
        swapColors = value;
    });
	listenForSettingChanges("use-custom-colors", [](bool value) {
		useCustomColors = value;
	});
	listenForSettingChanges("custom-col1", [](cocos2d::ccColor3B value) {
		c_Col1 = value;
	});
	listenForSettingChanges("custom-col2", [](cocos2d::ccColor3B value) {
		c_Col2 = value;
	});
	listenForSettingChanges("custom-colwhite", [](cocos2d::ccColor3B value) {
		c_ColWhite = value;
	});
}

class $modify(CustomFireBoost, PlayerFireBoostSprite) {
	static PlayerFireBoostSprite* create() {
		PlayerFireBoostSprite* ret = PlayerFireBoostSprite::create();

		if (!modEnabled) return ret;

		auto manager = GameManager::sharedState();

		cocos2d::ccColor3B color1;
		cocos2d::ccColor3B color2;
		cocos2d::ccColor3B colorWhite;
		if (useCustomColors) {
			color1 = c_Col1;
			color2 = c_Col2;
			colorWhite = c_ColWhite;
		} else {
			if (swapColors) {
				color1 = manager->colorForIdx(manager->getPlayerColor2());
				color2 = manager->colorForIdx(manager->getPlayerColor());
			} else {
				color1 = manager->colorForIdx(manager->getPlayerColor());
				color2 = manager->colorForIdx(manager->getPlayerColor2());
			}
			colorWhite = ccColor3B({255, 255, 255});
		}
		
		auto mainTintFire = CCSprite::createWithSpriteFrameName("c_fireBoost_001.png"_spr);
		auto secondaryTintFire = CCSprite::createWithSpriteFrameName("c_fireBoost_2_001.png"_spr);
		auto noTintFire = CCSprite::createWithSpriteFrameName("c_fireBoost_noTint_001.png"_spr);

		ret->setDisplayFrame(noTintFire->displayFrame());

		ret->addChild(secondaryTintFire, -1);
		ret->addChild(mainTintFire, -2);

		mainTintFire->setPosition({ret->getContentSize().width / 2, ret->getContentSize().height / 2});
		secondaryTintFire->setPosition({ret->getContentSize().width / 2, ret->getContentSize().height / 2});

		mainTintFire->setColor(color1);
		secondaryTintFire->setColor(color2);
		ret->setColor(colorWhite);

		return ret;
	}
};