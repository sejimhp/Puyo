#pragma once;
#include <Siv3D.hpp>
#include "Player.h"
#include "Player2.h"

#define WID 6
#define HEG 12
#define SIZE 36
#define STA1 80
#define STA2 (80 + 13 * SIZE)

class Game{
	enum class State{
		TITLE,
		START,
		GAME,
		PAUSE,
		END
	};
	Font font;
	State state;
	TimerMillisec timer;
	int data[100][2];
	Player player1;
	Player2 player2;
	int select;
	int count_flag;
public:
	Game();
	void run();
	void draw();
	void start();
	void finish();
	void draw_stage();
	void countdown();
};