#pragma once

class Player{
	//���W
	int X, Y;
	//�����p
	int x, y;
	//�Ֆʂ̃f�[�^
	int stage[8][12];
	//�Ղ�Ղ�
	int count;
	int puyo[100][2];
public:
	void init(int, int);
	void run();
	void init(int data[][2]);
	void draw();
};