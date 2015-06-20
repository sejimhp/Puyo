#include "Player2.h"
#include "Player.h"
#include "Game.h"
#include <Siv3D.hpp>

int Player2::run(){
	//アニメーションなどのイベントはすべてpuyo_eventで・・・。

	switch (state){
	case State::START:
		break;
	case State::GAME:
		input();
		fall();
		if (stage[2][0] != 0)
			return 1;
		break;
	case State::EVENT:
		puyo_event();
		break;
	};
	return 0;
}


void Player2::input(){
	switch (state){
	case State::START:
		break;
	case State::GAME:
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
			y += 10;
		}
		if (Input::KeyLeft.clicked && x > 0 && (stage[x / SIZE - 1][y / SIZE + 2] == 0 && stage[x / SIZE - 1][y / SIZE + 1] == 0)){
			//Left
			x -= SIZE;
		}
		if (Input::KeyRight.clicked && x < (WID - 1) * SIZE && (stage[x / SIZE + 1][y / SIZE + 2] == 0 && stage[x / SIZE + 1][y / SIZE + 1] == 0)){
			//Right
			x += SIZE;
		}
		break;
	case State::EVENT:
		break;
	};
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
	static int time = 0;
	switch (state){
	case State::START:
		time++;
		time %= 180;
		if (ready == 1)
			TextureAsset(L"ready").draw(X + 10, Y + 200);
		else
			TextureAsset(L"down").scale(0.75).draw(X + 5, Y + 200, Alpha((int)(255 * (sin((double)time / 360 * 2 * PI)))));
	case State::GAME:
	case State::EVENT:
		TextureAsset(L"batu").draw(X + 2 * SIZE, Y);
		//Red Blue Yellow Green Purple
		//putting puyo
		for (int i = 0; i < WID; i++){
			for (int j = 0; j < HEG; j++){
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
			}
			switch (puyo[count + 2][i]){
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
			}
		}
		break;
	};
}