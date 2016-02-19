#pragma once

#include <string>
#include <vector>
#include "stdafx.h"
#include "AssetManager.h"
#include "Stage.h"
#include "Game.h"

#define window_width 1920

AssetManager::AssetManager() {
	Stage stage;
}

using namespace std;


void AssetManager::load_images() {

}
void AssetManager::load_audio() {

}
void AssetManager::setStage(Stage & s)
{
	stage = s;
}
void AssetManager::move_camera_left(Stage &stage, Player &p1, Player &p2) {
	if (p1.facing_right && (p2.character->sprite.getPosition().x + p2.character->width/2 != window_width) && (stage.window_offset > 0)) {  
		stage.sprite.move(2.0000000f, 0);
		stage.window_offset = stage.window_offset - 2;
		cout << stage.window_offset << endl;
	}
}
void AssetManager::move_camera_right(Stage &stage, Player &p1, Player &p2) {
	if (!p1.facing_right && p2.character->sprite.getPosition().x - p2.character->width / 2 != 0 && stage.window_offset < stage.window_limit) {
		stage.sprite.move(-2.0000000f, 0);
		stage.window_offset = stage.window_offset + 2;
		cout << stage.window_offset << endl;
	}
}
AssetManager::~AssetManager()
{
}