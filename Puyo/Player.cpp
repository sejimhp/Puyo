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
	time = 0;
}

int Player::run(){
	switch (state){
	case State::START:
		break;
	case State::GAME:
		break_puyo();
		input();
		fall();
		if (stage[2][0] != 0){
			return 1;
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

void Player::input(){
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
	if (Input::KeyS.pressed){
		//speedy
		y += 10;
	}
	if (Input::KeyA.clicked && x > 0 && (stage[x / SIZE - 1][y / SIZE + 2] == 0 && stage[x / SIZE - 1][y / SIZE + 1] == 0)){
		//Left
		x -= SIZE;
	}
	if (Input::KeyD.clicked && x < (WID - 1) * SIZE && (stage[x / SIZE + 1][y / SIZE + 2] == 0 && stage[x / SIZE + 1][y / SIZE + 1] == 0)){
		//Right
		x += SIZE;
	}

}

void Player::fall(){
	//Routaition
	if (rot_flag == 1){
		if (x == 0 && rot == 90)
			x += 36;
		else if (x == (WID - 1) * SIZE && rot == 270)
			x -= 36;
		rot += 10;
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
		break_puyo();
	}
	else if ((y >= 11 * SIZE || stage[x / SIZE][y / SIZE + 1] != 0) && rot == 90){
		//up
		stage[x / SIZE][y / SIZE] = puyo[count][0];
		stage[x / SIZE][y / SIZE - 1] = puyo[count][1];
		put_flag = 1;
		break_puyo();
	}
	else if ((y >= 11 * SIZE || stage[x / SIZE][y / SIZE + 1] != 0 || stage[x / SIZE - 1][y / SIZE + 1] != 0) && rot == 180){
		//left
		if (stage[x / SIZE][y / SIZE + 1] == 0){
			//under main puyo
			stage[x / SIZE][y / SIZE] = puyo[count][0];
			stage[x / SIZE - 1][y / SIZE] = puyo[count][1];
		}
		else if (stage[x / SIZE - 1][y / SIZE + 1] == 0){
			//under another puyo
			stage[x / SIZE][y / SIZE] = puyo[count][0];
			stage[x / SIZE + 1][y / SIZE] = puyo[count][1];
		}
		else {
			stage[x / SIZE][y / SIZE] = puyo[count][0];
			stage[x / SIZE - 1][y / SIZE] = puyo[count][1];
		}
		put_flag = 1;
	}
	else if ((y >= 11 * SIZE || stage[x / SIZE][y / SIZE + 1] != 0 || stage[x / SIZE + 1][y / SIZE + 1] != 0) && rot == 0){
		//right
		if (stage[x / SIZE][y / SIZE + 1] == 0){
			//under main puyo
			stage[x / SIZE][y / SIZE] = puyo[count][0];
			stage[x / SIZE + 1][y / SIZE] = puyo[count][1];
		}
		else if (stage[x / SIZE + 1][y / SIZE + 1] == 0){
			//under another puyo
			stage[x / SIZE][y / SIZE] = puyo[count][0];
			stage[x / SIZE + 1][y / SIZE] = puyo[count][1];
		}
		else {
			stage[x / SIZE][y / SIZE] = puyo[count][0];
			stage[x / SIZE + 1][y / SIZE] = puyo[count][1];
		}
		put_flag = 1;
	}

	break_puyo();
	if (put_flag != 0)
		state = State::EVENT;
	else
		y++;
}

int Player::search(int i, int j, int state){
	int sum = 1;

	if (stage[i][j] == stage[i][j - 1] && j != 0 && state != 2){
		sum += search(i, j - 1, 1);
	}
	if (stage[i][j] == stage[i][j + 1] && j != (HEG - 1) && state != 1){
		sum += search(i, j + 1, 2);
	}
	if (stage[i][j] == stage[i - 1][j] && i != 0 && state != 4){
		sum += search(i - 1, j, 3);
	}
	if (stage[i][j] == stage[i + 1][j] && i != (WID - 1) && state != 3){
		sum += search(i + 1, j, 4);
	}
	return sum;
}

void Player::sub(int i, int j, int state){
	destroy[i][j] = 1;

	if (stage[i][j] == stage[i][j - 1] && j != 0 && state != 2){
		sub(i, j - 1, 1);
	}
	if (stage[i][j] == stage[i][j + 1] && j != (HEG - 1) && state != 1){
		sub(i, j + 1, 2);
	}
	if (stage[i][j] == stage[i - 1][j] && i != 0 && state != 4){
		sub(i - 1, j, 3);
	}
	if (stage[i][j] == stage[i + 1][j] && i != (WID - 1) && state != 3){
		sub(i + 1, j, 4);
	}
	//exti disturbance
	if (stage[i][j - 1] == 6){
		destroy[i][j - 1] = 1;
	}
	if (stage[i][j + 1] == 6){
		destroy[i][j + 1] = 1;
	}
	if (stage[i + 1][j] == 6){
		destroy[i + 1][j] = 1;
	}
	if (stage[i - 1][j] == 6){
		destroy[i - 1][j] = 1;
	}
}

void Player::break_puyo(){
	int val = 0;
	for (int i = WID - 1; i >= 0; i--){
		for (int j = HEG - 1; j >= 0; j--){
			if (stage[i][j] != 0)
				val = search(i, j, 0);
			if (val >= 4){
				if (stage[i][j] != 0)
					sub(i, j, 0);
				state = State::DESTROY;
			}
		}
	}
}

int Player::put(){
		int t;
	while (1){
		t = 0;
		for (int j = 10; j > 0; j--){
			for (int i = 0; i < 6; i++){
				if (stage[i][j] != 0 && stage[i][j + 1] == 0){
					stage[i][j + 1] = stage[i][j];
					stage[i][j] = 0;
					t++;
				}
			}
		}
		if (t == 0)
			break;
	}
	break_puyo();
	return 1;
}

void Player::puyo_event(){
	switch (state){
	case State::EVENT:
		if (put() == 1){
			put_flag = 0;
			count++;
			y = 0;
			x = 2 * SIZE;
			rot = 270;
			state = State::GAME;
		}
		break;
	case State::DESTROY:
		time = 254;
		time %= 255;
		state = State::GAME;
		for (int i = 0; i < WID; i++){
			for (int j = 0; j < HEG; j++){
				if (destroy[i][j] == 1)
					stage[i][j] = 0;
			}
		}
		state = State::EVENT;
		break;
	};
}

void Player::draw(){
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
				case 1:
					if (destroy[i][j] == 1){
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE, Alpha(time));
					}
					else{
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE);
					}
					break;
				case 2:
					if (destroy[i][j] == 1){
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE, Alpha(time));
					}
					else{
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE);
					}
					break;
				case 3:
					if (destroy[i][j] == 1){
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE, Alpha(time));
					}
					else{
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE);
					}
					break;
				case 4:
					if (destroy[i][j] == 1){
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE, Alpha(time));
					}
					else{
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE);
					}
					break;
				case 5:
					if (destroy[i][j] == 1){
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE, Alpha(time));
					}
					else{
						TextureAsset(L"puyo")((stage[i][j] - 1) * 24, 0, 24, 24).scale(1.5).draw(X + i * SIZE, Y + j * SIZE);
					}
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
				TextureAsset(L"puyo")((puyo[count + 1][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(WID * SIZE + 38 , 70 + i * SIZE + 10);
				break;
			case 2:
				TextureAsset(L"puyo")((puyo[count + 1][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(WID * SIZE + 38 , 70 + i * SIZE + 10);
				break;
			case 3:
				TextureAsset(L"puyo")((puyo[count + 1][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(WID * SIZE + 38 , 70 + i * SIZE + 10);
				break;
			case 4:
				TextureAsset(L"puyo")((puyo[count + 1][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(WID * SIZE + 38 , 70 + i * SIZE + 10);
				break;
			case 5:
				TextureAsset(L"puyo")((puyo[count + 1][i] - 1) * 24, 0, 24, 24).scale(1.5).draw(WID * SIZE + 38 , 70 + i * SIZE + 10);
				break;
			}
			switch (puyo[count + 2][i]){
			case 1:
				TextureAsset(L"puyo")((puyo[count + 2][i] - 1) * 24, 0, 24, 24).draw(WID * SIZE + 85, 130 + i * 24 + 12);
				break;
			case 2:
				TextureAsset(L"puyo")((puyo[count + 2][i] - 1) * 24, 0, 24, 24).draw(WID * SIZE + 85, 130 + i * 24 + 12);
				break;
			case 3:
				TextureAsset(L"puyo")((puyo[count + 2][i] - 1) * 24, 0, 24, 24).draw(WID * SIZE + 85, 130 + i * 24 + 12);
				break;
			case 4:
				TextureAsset(L"puyo")((puyo[count + 2][i] - 1) * 24, 0, 24, 24).draw(WID * SIZE + 85, 130 + i * 24 + 12);
				break;
			case 5:
				TextureAsset(L"puyo")((puyo[count + 2][i] - 1) * 24, 0, 24, 24).draw(WID * SIZE + 85, 130 + i * 24 + 12);
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
	for (int i = 0; i < WID; i++){
		for (int j = 0; j < HEG; j++){
			stage[i][j] = 0;
		}
	}
	x = 2 * SIZE;
	state = State::GAME;
	count = 0;
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
	if (stage[2][0] == 0)
		TextureAsset(L"winner").draw(X - 10, 250);
	else
		TextureAsset(L"loser").draw(X + 10, 250);
}