#pragma once

#define PI 3.14159

class Player{
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
public:
	void init(int, int);

	void run();
	void action();
	int put();
	void input();
	void puyo_event();

	void set(int data[][2]);
	void draw();
};