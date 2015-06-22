#include "Player2.h"
#include "Player.h"
#include "Game.h"
#include <Siv3D.hpp>

int Player2::run(){
	switch (state){
	case State::START:
		break;
	case State::GAME:
		break_puyo();
		input();
		fall();
		if (stage[2][0] != 0){
			return 100;
		}
		if (attack != 0){
			int a = attack;
			attack = 0;
			return a;
		}
		break;
	case State::EVENT:
		puyo_event();
		break;
	case State::DESTROY:
		puyo_event();
		break;
	};
	return 0;
}


void Player2::input(){
	if (Input::KeyUp.clicked && rot_flag == 0){
		//Rotaition
		if (rot == 270){
			if (x == 0 && (stage[x / SIZE][y / SIZE] != 0 || stage[x / SIZE][y / SIZE + 1] != 0)){}
			else if (stage[x / SIZE - 1][y / SIZE] != 0 || stage[x / SIZE + 1][y / SIZE] != 0){}
			else
				rot_flag = 1;
		}
		else if (rot == 90){
			if (x == 0 && (stage[x / SIZE][y / SIZE] != 0 || stage[x / SIZE][y / SIZE - 1] != 0)){}
			else if (stage[x / SIZE - 1][y / SIZE + 1] != 0 || stage[x / SIZE + 1][y / SIZE + 1] != 0){}
			else
				rot_flag = 1;
		}
		else
			rot_flag = 1;
	}
	if (Input::KeyDown.pressed){
		//speedy
		ay++;
		y += 7 + ay;
	}
	if (Input::KeyDown.released){
		ay = 0;
	}
	if (Input::KeyLeft.clicked && x > 0){
		//Left
		if ((stage[x / SIZE - 1][y / SIZE + 2] == 0 && stage[x / SIZE - 1][y / SIZE + 1] == 0) && y > 0 && !(rot == 180 && x == SIZE))
			x -= SIZE;
		else if (stage[x / SIZE - 1][y / SIZE + 1] == 0 && y < 0 && !(rot == 180 && x == SIZE))
			x -= SIZE;
	}
	if (Input::KeyRight.clicked && x < (WID - 1) * SIZE){
		//Right
		if ((stage[x / SIZE + 1][y / SIZE + 2] == 0 && stage[x / SIZE + 1][y / SIZE + 1] == 0) && y > 0 && !(rot == 0 && x >= (WID - 2) * SIZE))
			x += SIZE;
		else if (stage[x / SIZE + 1][y / SIZE + 1] == 0 && y < 0 && !(rot == 0 && x >= (WID - 2) * SIZE))
			x += SIZE;
	}
}


int Player2::start(){
	if (Input::KeyDown.clicked == 1)
		ready = 1;
	if (ready == 1)
		return 1;
	else
		return 0;
}


void Player2::draw(){
	switch (state){
	case State::START:
		time++;
		time %= 180;
		if (ready == 1)
			TextureAsset(L"ready").draw(X + 10, Y + 200);
		else
			TextureAsset(L"s").scale(0.75).draw(X + 5, Y + 200, Alpha((int)(255 * (sin((double)time / 360 * 2 * PI)))));
		break;
	case State::GAME:
	case State::EVENT:
	case State::DESTROY:
		TextureAsset(L"batu").draw(X + 2 * SIZE, Y);
		//Red Blue Yellow Green Purple
		//putting puyo
		for (int i = 0; i < WID; i++){
			for (int j = 0; j < HEG; j++){
				switch (stage[i][j]){
				case 0:
					break;
				case 1:
					if (destroy[i][j] == 1){
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE, Alpha((time % 5) * 50));
					}
					else{
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE);
					}
					break;
				case 2:
					if (destroy[i][j] == 1){
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE, Alpha((time % 5) * 50));
					}
					else{
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE);
					}
					break;
				case 3:
					if (destroy[i][j] == 1){
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE, Alpha((time % 5) * 50));
					}
					else{
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE);
					}
					break;
				case 4:
					if (destroy[i][j] == 1){
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE, Alpha((time % 5) * 50));
					}
					else{
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE);
					}
					break;
				case 5:
					if (destroy[i][j] == 1){
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE, Alpha((time % 5) * 50));
					}
					else{
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE);
					}
					break;
				default:
					if (destroy[i][j] == 1){
						TextureAsset(L"tech").draw(X + i * SIZE, Y + j * SIZE, Alpha((time % 5) * 50));
					}
					else{
						TextureAsset(L"tech").draw(X + i * SIZE, Y + j * SIZE);
					}
					break;
				}
			}
		}
		//puyo is falling
		for (int i = 0; i < 2; i++){
			int xx = X + x + (int)(i * (cos((double)rot / 360 * 2 * PI)) * SIZE);
			int yy = Y + y + (int)(i * (-sin((double)rot / 360 * 2 * PI)) * SIZE);
			switch (puyo[count][i]){
			case 0:
				break;
			case 1:
				TextureAsset(L"puyo")((puyo[count][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(xx, yy);
				break;
			case 2:
				TextureAsset(L"puyo")((puyo[count][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(xx, yy);
				break;
			case 3:
				TextureAsset(L"puyo")((puyo[count][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(xx, yy);
				break;
			case 4:
				TextureAsset(L"puyo")((puyo[count][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(xx, yy);
				break;
			case 5:
				TextureAsset(L"puyo")((puyo[count][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(xx, yy);
				break;
			default:
				TextureAsset(L"tech").draw(xx, yy);
				break;
			}
		}
		//fall_flag == 1
		if (fall_flag == 1)
			for (int i = 0; i < WID; i++){
				for (int j = 0; (j + falling[i][13]) < HEG; j++){
					switch (falling[i][j]){
					case 0:
						break;
					case 1:
						TextureAsset(L"puyo")((falling[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + (falling[i][13] - j) * SIZE + time);
						break;
					case 2:
						TextureAsset(L"puyo")((falling[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + (falling[i][13] - j) * SIZE + time);
						break;
					case 3:
						TextureAsset(L"puyo")((falling[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + (falling[i][13] - j) * SIZE + time);
						break;
					case 4:
						TextureAsset(L"puyo")((falling[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + (falling[i][13] - j) * SIZE + time);
						break;
					case 5:
						TextureAsset(L"puyo")((falling[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + (falling[i][13] - j) * SIZE + time);
						break;
					default:
						TextureAsset(L"tech").draw(X + i * SIZE, Y + (falling[i][13] - j) * SIZE + time);
						break;
					}
				}
			}
		//display next puyo and two later puyo
		for (int i = 0; i < 2; i++){
			switch (puyo[count + 1][i]){
			case 0:
				break;
			case 1:
				TextureAsset(L"puyo")((puyo[count + 1][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(409, 70 + i * SIZE + 10);
				break;
			case 2:
				TextureAsset(L"puyo")((puyo[count + 1][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(409, 70 + i * SIZE + 10);
				break;
			case 3:
				TextureAsset(L"puyo")((puyo[count + 1][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(409, 70 + i * SIZE + 10);
				break;
			case 4:
				TextureAsset(L"puyo")((puyo[count + 1][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(409, 70 + i * SIZE + 10);
				break;
			case 5:
				TextureAsset(L"puyo")((puyo[count + 1][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(409, 70 + i * SIZE + 10);
				break;
			default:
				TextureAsset(L"tech").draw(409, 70 + i * SIZE + 10);
				break;
			}
			switch (puyo[count + 2][i]){
			case 0:
				break;
			case 1:
				TextureAsset(L"puyo")((puyo[count + 2][i] - 1) * 24, 0, 24, 24).draw(382, 130 + i * 24 + 12);
				break;
			case 2:
				TextureAsset(L"puyo")((puyo[count + 2][i] - 1) * 24, 0, 24, 24).draw(382, 130 + i * 24 + 12);
				break;
			case 3:
				TextureAsset(L"puyo")((puyo[count + 2][i] - 1) * 24, 0, 24, 24).draw(382, 130 + i * 24 + 12);
				break;
			case 4:
				TextureAsset(L"puyo")((puyo[count + 2][i] - 1) * 24, 0, 24, 24).draw(382, 130 + i * 24 + 12);
				break;
			case 5:
				TextureAsset(L"puyo")((puyo[count + 2][i] - 1) * 24, 0, 24, 24).draw(382, 130 + i * 24 + 12);
				break;
			default:
				TextureAsset(L"tech").draw(382, 130 + i * 24 + 12);
				break;
			}
		}
		break;
	};
}