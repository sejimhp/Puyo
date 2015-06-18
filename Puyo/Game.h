#pragma once;
#include <Siv3D.hpp>
#include "Player.h"
#include "Player2.h"

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
	unsigned int start_time, time;
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