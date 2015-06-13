#pragma once;
#include <Siv3D.hpp>

#define SIZE 36
#define STA1 80
#define STA2 (80 + 13 * SIZE)

class Game{
	enum class State{
		TITLE,
		GAME,
		PAUSE,
		END
	};
	Font font;
	State state;
public:
	void init();
	void run();
	void draw();
};