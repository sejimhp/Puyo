#include <Siv3D.hpp>
#include "Game.h"
#include "Player.h"

void Player::init(int X, int Y){
	this->X = X;
	this->Y = Y;
	count = 0;
}

void Player::run(){
	if (Input::KeyUp.clicked){

	}else if (Input::KeyDown.pressed){
		y += 2;
	}else if (Input::KeyLeft.clicked && x > 0 && (stage[x / SIZE - 1][y / SIZE + 2]==0 && stage[x / SIZE - 1][y / SIZE + 1]==0)){
		x -= SIZE;
	}else if (Input::KeyRight.clicked && x < 7 * SIZE && (stage[x / SIZE + 1][y / SIZE + 2]==0 && stage[x / SIZE + 1][y / SIZE + 1]==0)){
		x += SIZE;
	}
	if (y >= 10 * SIZE || stage[x / SIZE][y / SIZE + 2] != 0){
		stage[x / SIZE][y / SIZE] = puyo[count][0];
		stage[x / SIZE][y / SIZE + 1] = puyo[count][1];
		count++;
		y = 0;
		x = 3 * SIZE;
	}
	y++;
}

void Player::draw(){
	//赤　青　黄　緑　紫
	//置かれてるぷよ
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 12; j++){
			switch (stage[i][j]){
			case 1:
				TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE);
				break;
			case 2:
				TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE);
				break;
			case 3:
				TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE);
				break;
			case 4:
				TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE);
				break;
			case 5:
				TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE);
				break;
			}
		}
	}
	//落下中のぷよ
	for (int i = 0; i < 2; i++){
		switch (puyo[count][i]){
		case 1:
			TextureAsset(L"puyo")((puyo[count][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + x, Y + y + i * SIZE);
			break;
		case 2:
			TextureAsset(L"puyo")((puyo[count][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + x, Y + y + i * SIZE);
			break;
		case 3:
			TextureAsset(L"puyo")((puyo[count][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + x, Y + y + i * SIZE);
			break;
		case 4:
			TextureAsset(L"puyo")((puyo[count][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + x, Y + y + i * SIZE);
			break;
		case 5:
			TextureAsset(L"puyo")((puyo[count][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + x, Y + y + i * SIZE);
			break;
		}
	}
}

void Player::init(int data[][2]){
	for (int i = 0; i < 100; i++){
		puyo[i][0] = data[i][0];
		puyo[i][1] = data[i][1];
	}
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 12; j++){
			stage[i][j] = 0;
		}
	}
}