#pragma once

#define PI 3.14159

class Player{
	enum class State{
		START,
		GAME,
		EVENT,
		PAUSE,
		END
	} state;
	//array
	int X, Y;
	//falling
	int x, y;
	//stage data
	int stage[8][12];
	//puyopuyo
	int count;
	int puyo[100][2];
	//Rotaition
	int rot, rot_flag;
	//put
	int put_flag;
	int ready;
public:
	void init(int, int);

	void run();

	void fall();
	int put();
	void input();
	void puyo_event();
	int start();
	void ending();
	void pause();

	void set(int data[][2]);
	void draw();
};