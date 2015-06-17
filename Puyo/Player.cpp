#include <Siv3D.hpp>
#include "Game.h"
#include "Player.h"

void Player::init(int X, int Y){
	this->X = X;
	this->Y = Y;
	count = 0;
	rot = 270;
	put_flag = 0;
	rot_flag = 0;
}

void Player::run(){
	//アニメーションなどのイベントはすべてpuyo_eventで・・・。

	switch (state){
	case State::START:
		break;
	case State::GAME:
		input();
		fall();
		break;
	case State::EVENT:
		puyo_event();
		break;
	case State::PAUSE:
		break;
	case State::END:
		ending();
		break;
	};
	/*if (puyo_event()){
		input();

		//fall action etc..
		fall();
		}*/
}

void Player::input(){
	switch (state){
	case State::START:
		break;
	case State::GAME:
		if (Input::KeyW.clicked && rot_flag == 0){
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
		else if (Input::KeyS.pressed){
			//speedy
			y += 2;
		}
		else if (Input::KeyA.clicked && x > 0 && (stage[x / SIZE - 1][y / SIZE + 2] == 0 && stage[x / SIZE - 1][y / SIZE + 1] == 0)){
			//Left
			x -= SIZE;
		}
		else if (Input::KeyD.clicked && x < 7 * SIZE && (stage[x / SIZE + 1][y / SIZE + 2] == 0 && stage[x / SIZE + 1][y / SIZE + 1] == 0)){
			//Right
			x += SIZE;
		}
		break;
	case State::EVENT:
		break;
	case State::PAUSE:
		break;
	case State::END:
		break;
	};

}

void Player::fall(){
	//Routaition
	if (rot_flag == 1){
		if (x == 0 && rot == 90)
			x += 36;
		else if (x == 7 * SIZE && rot == 270)
			x -= 36;
		rot += 5;
		if (rot % 90 == 0){
			rot_flag = 0;
			rot %= 360;
		}
	}
	//put puyo
	if ((y >= 10 * SIZE || stage[x / SIZE][y / SIZE + 2] != 0) && rot == 270){
		//down
		stage[x / SIZE][y / SIZE] = puyo[count][0];
		stage[x / SIZE][y / SIZE + 1] = puyo[count][1];
		put_flag = 1;
	}
	else if ((y >= 11 * SIZE || stage[x / SIZE][y / SIZE + 1] != 0) && rot == 90){
		//up
		stage[x / SIZE][y / SIZE] = puyo[count][0];
		stage[x / SIZE][y / SIZE - 1] = puyo[count][1];
		put_flag = 1;
	}
	else if ((y >= 11 * SIZE || stage[x / SIZE][y / SIZE + 1] != 0 || stage[x / SIZE - 1][y / SIZE + 1] != 0) && rot == 180){
		//left
		if (stage[x / SIZE][y / SIZE + 1] == 0){
			//under main puyo
			stage[x / SIZE - 1][y / SIZE] = puyo[count][1];
			put_flag = 2;
		}
		else if (stage[x / SIZE - 1][y / SIZE + 1] == 0){
			//under another puyo
			stage[x / SIZE][y / SIZE] = puyo[count][0];
			put_flag = 3;
		}
		else {
			stage[x / SIZE][y / SIZE] = puyo[count][0];
			stage[x / SIZE - 1][y / SIZE] = puyo[count][1];
			put_flag = 1;
		}
	}
	else if ((y >= 11 * SIZE || stage[x / SIZE][y / SIZE + 1] != 0 || stage[x / SIZE + 1][y / SIZE + 1] != 0) && rot == 0){
		//right
		if (stage[x / SIZE][y / SIZE + 1] == 0){
			//under main puyo
			stage[x / SIZE + 1][y / SIZE] = puyo[count][1];
			put_flag = 2;
		}
		else if (stage[x / SIZE + 1][y / SIZE + 1] == 0){
			//under another puyo
			stage[x / SIZE][y / SIZE] = puyo[count][0];
			put_flag = 3;
		}
		else {
			stage[x / SIZE][y / SIZE] = puyo[count][0];
			stage[x / SIZE + 1][y / SIZE] = puyo[count][1];
			put_flag = 1;
		}
	}

	if (put_flag != 0)
		state = State::EVENT;
	else
		y++;
}

int Player::put(){
	if (put_flag == 2){
		y += 3;
		if (stage[x / SIZE][y / SIZE + 1] != 0 || y >= 11 * SIZE){
			stage[x / SIZE][y / SIZE] = puyo[count][0];
			return 1;
		}
		return 0;
	}
	else if (put_flag == 3){
		y += 3;
		if (rot == 0 && (stage[x / SIZE + 1][y / SIZE + 1] != 0 || y > 11 * SIZE)){
			stage[x / SIZE + 1][y / SIZE] = puyo[count][1];
			return 1;
		}
		else if (rot == 180 && (stage[x / SIZE - 1][y / SIZE + 1] != 0 || y > 11 * SIZE)){
			stage[x / SIZE - 1][y / SIZE] = puyo[count][1];
			return 1;
		}
		return 0;
	}
	return 1;
}

void Player::puyo_event(){
	if (put_flag != 0 && put() == 1){
		put_flag = 0;
		count++;
		y = 0;
		x = 3 * SIZE;
		rot = 270;
		state = State::GAME;
	}
}

void Player::draw(){
	switch (state){
	case State::START:

		break;
	case State::END:
		break;
	case State::GAME:
	case State::EVENT:
	case State::PAUSE:
		//Red Blue Yellow Green Purple
		//putting puyo
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
		//puyo is falling
		for (int i = 0; i < 2; i++){
			if (put_flag == 2 && i == 1)
				break;;
			if (put_flag == 3)
				i++;
			int xx = X + x + (int)(i * (cos((double)rot / 360 * 2 * PI)) * SIZE);
			int yy = Y + y + (int)(i * (-sin((double)rot / 360 * 2 * PI)) * SIZE);
			switch (puyo[count][i]){
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
			}
		}
		//display next puyo and two later puyo
		for (int i = 0; i < 2; i++){
			switch (puyo[count + 1][i]){
			case 1:
				TextureAsset(L"puyo")((puyo[count + 1][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(330, 70 + i * SIZE + 10);
				TextureAsset(L"puyo")((puyo[count + 2][i] - 1) * 24, 0, 24, 24).scale(0.75).draw(386, 70 + i * 18 + 6);
				break;
			case 2:
				TextureAsset(L"puyo")((puyo[count + 1][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(330, 70 + i * SIZE + 10);
				break;
			case 3:
				TextureAsset(L"puyo")((puyo[count + 1][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(330, 70 + i * SIZE + 10);
				break;
			case 4:
				TextureAsset(L"puyo")((puyo[count + 1][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(330, 70 + i * SIZE + 10);
				break;
			case 5:
				TextureAsset(L"puyo")((puyo[count + 1][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(330, 70 + i * SIZE + 10);
				break;
			}
			switch (puyo[count + 2][i]){
			case 1:
				TextureAsset(L"puyo")((puyo[count + 2][i] - 1) * 24, 0, 24, 24).scale(0.75).draw(386, 70 + i * 18 + 6);
				break;
			case 2:
				TextureAsset(L"puyo")((puyo[count + 2][i] - 1) * 24, 0, 24, 24).scale(0.75).draw(386, 70 + i * 18 + 6);
				break;
			case 3:
				TextureAsset(L"puyo")((puyo[count + 2][i] - 1) * 24, 0, 24, 24).scale(0.75).draw(386, 70 + i * 18 + 6);
				break;
			case 4:
				TextureAsset(L"puyo")((puyo[count + 2][i] - 1) * 24, 0, 24, 24).scale(0.75).draw(386, 70 + i * 18 + 6);
				break;
			case 5:
				TextureAsset(L"puyo")((puyo[count + 2][i] - 1) * 24, 0, 24, 24).scale(0.75).draw(386, 70 + i * 18 + 6);
				break;
			}
		}
		break;
	};
}

void Player::set(int data[][2]){
	for (int i = 0; i < 100; i++){
		puyo[i][0] = data[i][0];
		puyo[i][1] = data[i][1];
	}
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 12; j++){
			stage[i][j] = 0;
		}
	}
	x = 3 * SIZE;
	state = State::GAME;
}

int Player::start(){
	if (Input::KeyS.clicked == 1)
		ready = 1;
	if (ready == 1)
		return 1;
	else
		return 0;
}

void Player::ending(){
}

void Player::pause(){
}