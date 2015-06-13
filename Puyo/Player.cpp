#include <Siv3D.hpp>
#include "Game.h"
#include "Player.h"

void Player::init(int X, int Y){
	//赤　青　黄　緑　紫
	this->X = X;
	this->Y = Y;
}

void Player::run(){

}

void Player::draw(){
	TextureAsset(L"puyo")(0, 0, 24, 24).scale(1.5).draw(X, Y);
}

void Player::set(int data[][2]){
	for (int i = 0; i < 100; i++){
		puyo[i][0] = data[i][0];
		puyo[i][1] = puyo[i][1];
	}
}