#include <Siv3D.hpp>

#include "Game.h"
#include "Player.h"
#include "Player2.h"

Game::Game(){
	TextureAsset::Register(L"block", L"item/block.png");
	TextureAsset::Register(L"background", L"item/background.png");
	TextureAsset::Register(L"stage", L"item/stage.png");
	TextureAsset::Register(L"T", L"item/time.png");
	TextureAsset::Register(L"puyo", L"item/puyo.png");
	TextureAsset::Register(L"2p", L"item/2p.png");
	TextureAsset::Register(L"cpu1", L"item/cpu1.png");
	TextureAsset::Register(L"cpu2", L"item/cpu2.png");
	TextureAsset::Register(L"cpu3", L"item/cpu3.png");
	TextureAsset::Register(L"title", L"item/title.png");
	TextureAsset::Register(L"sankaku", L"item/sankaku.png");
	TextureAsset::Register(L"tech", L"item/tech.png");
	TextureAsset::Register(L"ready", L"item/ready.png");
	TextureAsset::Register(L"s", L"item/s.png");
	TextureAsset::Register(L"down", L"item/down.png");
	TextureAsset::Register(L"game_start", L"item/game_start.png");
	TextureAsset::Register(L"pause", L"item/pause.png");
	TextureAsset::Register(L"batu", L"item/batu.png");
	TextureAsset::Register(L"winner", L"item/winner.png");
	TextureAsset::Register(L"loser", L"item/loser.png");

	font(30);
	state = State::TITLE;

	player1.init(30, 70);
	player2.init(460, 70);

	select = 0;
	count_flag = 0;
}

void Game::run(){
	int val1;
	int val2;
	switch (state){
	case State::TITLE:
		if (Input::KeyEnter.clicked && select == 0)
			state = State::START;
		if (Input::KeyUp.clicked){
			if (select == 0)
				select = 3;
			else
				select--;
		}
		if (Input::KeyDown.clicked){
			select++;
			select %= 4;
		}
		break;
	case State::START:
		if (count_flag == 1){
			start();
			state = State::GAME;
			count_flag = 0;
		}
		break;
	case State::GAME:
		if (Input::KeyP.clicked)
		{
			state = State::PAUSE;
			timer.pause();
		}
		val1 = player1.run();
		val2 = player2.run();
		if (val1 > 0 && val1 < 100)
			player2.obs(val1);
		if (val2 > 0 && val1 < 100)
			player1.obs(val2);

		if (val1 == 10 || val2 == 100){
			state = State::END;
			timer.pause();
		}
		break;
	case State::PAUSE:
		if (Input::KeyP.clicked)
		{
			state = State::GAME;
			timer.start();
		}
		break;
	case State::END:
		if (Input::KeyEnter.clicked)
		{
			state = State::TITLE;
			timer.reset();
		}
		break;
	}
}

void Game::draw(){
	switch (state){
	case State::TITLE:
		TextureAsset(L"sankaku").draw(140, 260 + select * 70);
		font(L"¦2pˆÈŠO–¢ŽÀ‘•").draw(500, 250);
		TextureAsset(L"title").draw(20, 50);
		TextureAsset(L"2p").draw(180, 250);
		TextureAsset(L"cpu1").draw(180, 320);
		TextureAsset(L"cpu2").draw(180, 390);
		TextureAsset(L"cpu3").draw(180, 460);
		break;
	case State::START:
		draw_stage();
		player2.start();
		if (player1.start() == 1 && player2.start() == 1){
			countdown();
		}
		break;
	case State::GAME:
		draw_stage();
		break;
	case State::PAUSE:
		draw_stage();
		TextureAsset(L"pause").draw(400, 160);
		break;
	case State::END:
		draw_stage();
		font(L"END").draw();
		player1.ending();
		player2.ending();
		break;
	}

}

void Game::start(){
	int a;
	int rand = Random(1, 5);
	for (int i = 0; i < 100; i++)
	{
		do{
			a = Random(1, 5);
		} while (a == rand);
		data[i][0] = a;
		do{
			a = Random(1, 5);
		} while (a == rand);
		data[i][1] = a;
	}
	player1.set(data);
	player2.set(data);
	timer.start();
}

void Game::draw_stage(){
	//TextureAsset(L"background").draw();
	Rect(0, 0, 850, 550).draw(Palette::Gray);
	TextureAsset(L"stage").map(SIZE * WID, SIZE * HEG).draw(30, 70);
	TextureAsset(L"stage").map(SIZE * WID, SIZE * HEG).draw(460, 70);
	Rect(246, 70, 60, 90).draw(Palette::Black);
	Rect(400, 70, 60, 90).draw(Palette::Black);
	Rect(246 + 40, 130, 50, 70).draw(Palette::Black);
	Rect(400 - 30, 130, 50, 70).draw(Palette::Black);
	Rect(260, 275, 185, 50).draw(Palette::Black);
	TextureAsset(L"T").draw(273, 230);
	//timer
	font((timer.elapsed() / 60000), L"•ª", ((timer.elapsed() % 60000) / 1000), L"•b", ((timer.elapsed() % 1000) / 100)).draw(278, 280);
	player1.draw();
	player2.draw();
}

void Game::countdown(){
	static unsigned int time;
	unsigned int time1 = Time::GetMillisec();
	if ((time1 - time) > 5000)	time = Time::GetMillisec();
	if ((time1 - time) > 4000)	{ count_flag = 1; return; }
	else {
		if ((time1 - time) > 3000)
			TextureAsset(L"game_start")(120, 0, 140, 40).draw(280, 400);
		else
			TextureAsset(L"game_start")((int)(time1 - time) / 1000 * 50, 0, 40, 40).draw(330, 400);
	}
	count_flag = 0;
}