#pragma once;
#include <Siv3D.hpp>
#include "Player.h"

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
	Player player1, player2;
	int select;
public:
	Game();
	void run();
	void draw();
	void start();
	void finish();
	void draw_stage();
};