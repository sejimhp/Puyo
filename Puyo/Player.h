#pragma once

class Player{
	//���W
	int X, Y;
	//�Ֆʂ̃f�[�^
	int stage[8][12];
	//�Ղ�Ղ�
	int count;
	int puyo[100][2];
public:
	void init(int, int);
	void run();
	void set(int data[][2]);
	void draw();
};