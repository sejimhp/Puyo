#pragma once

#define PI 3.14159

class Player{
protected:
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
	int stage[6][12];
	//break
	int destroy[6][12], sum, destroy_flag;
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
	void break_puyo();
	void puyo_event();
	int start();
	void ending();

	void set(int data[][2]);
	void draw();
};