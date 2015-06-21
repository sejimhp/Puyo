#pragma once
#include <Siv3D.hpp>

#define PI 3.14159

class Player{
protected:
	enum class State{
		START,
		GAME,
		EVENT,
		DESTROY
	} state;
	//array
	int X, Y;
	//falling
	int x, y, ay;
	int falling[6][14];
	//stage data
	int stage[6][12];
	//break
	int destroy[6][12], time;
	//puyopuyo
	int count;
	int puyo[100][2];
	//Rotaition
	int rot, rot_flag;
	//put
	int fall_flag;
	int ready;
public:
	void init(int, int);

	int run();

	void fall();
	int put();
	void input();
	void break_puyo();
	int search(int, int, int);
	void sub(int, int, int);
	void puyo_event();
	int start();
	void ending();

	void set(int data[][2]);
	void draw();
};