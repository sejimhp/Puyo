#pragma once

class Player{
	//座標
	int X, Y;
	//盤面のデータ
	int stage[8][12];
	//ぷよぷよ
	int count;
	int puyo[100][2];
public:
	void init(int, int);
	void run();
	void set(int data[][2]);
	void draw();
};