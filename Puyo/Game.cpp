#include <Siv3D.hpp>

#include "Game.h"
#include "Player.h"

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
	
	font(30);
	state = State::TITLE;
	
	player1.init(30, 70);
	player2.init(530, 70);

	select = 0;
}

void Game::run(){
	switch (state){
	case State::TITLE:
		if (Input::KeyEnter.clicked){
			state = State::START;;
		}
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
		if (player1.start() == 1 && player1.start() == 1){
			start();
			state = State::GAME;
		}
		break;
	case State::GAME:
		if (Input::KeyEnter.clicked)
		{
			state = State::PAUSE;
		}
		time = Time::GetMillisec() - start_time;
		player1.run();
		player2.run();
		break;
	case State::PAUSE:
		if (Input::KeyEnter.clicked)
		{
			state = State::END;
		}
		break;
	case State::END:
		if (Input::KeyEnter.clicked)
		{
			state = State::TITLE;
		}
		break;
	}
}

void Game::draw(){
	switch (state){
	case State::TITLE:
		TextureAsset(L"sankaku").draw(180, 260 + select * 70);
		font(L"Å¶2pà»äOñ¢é¿ëï").draw(500, 250);
		TextureAsset(L"title").draw(80, 50);
		TextureAsset(L"2p").draw(220, 250);
		TextureAsset(L"cpu1").draw(220, 320);
		TextureAsset(L"cpu2").draw(220, 390);
		TextureAsset(L"cpu3").draw(220, 460);
		break;
	case State::START:
		draw_stage();
		break;
	case State::GAME:
		draw_stage();
		break;
	case State::PAUSE:
		draw_stage();
		font(L"PAUSE").draw();
		break;
	case State::END:
		draw_stage();
		font(L"END").draw();
		break;
	}

}

void Game::start(){
	int a;
	for (int i = 0; i < 100;i ++)
	{
		a = Random(1, 5);	
		data[i][0] = a;
		a = Random(1, 5);	
		data[i][1] = a;
	}
	player1.set(data);
	player2.set(data);
	start_time = Time::GetMillisec();
}

void Game::draw_stage(){
		//TextureAsset(L"background").draw();
		Rect(0, 0, 850, 550).draw(Palette::Gray);
		TextureAsset(L"stage").map(SIZE * 8, SIZE * 12).draw(30, 70);
		TextureAsset(L"stage").map(SIZE * 8, SIZE * 12).draw(530, 70);
		Rect(318, 70, 60, 90).draw(Palette::Black);
		Rect(470, 70, 60, 90).draw(Palette::Black);
		Rect(380, 70, 30, 50).draw(Palette::Black);
		Rect(438, 70, 30, 50).draw(Palette::Black);
		Rect(330, 275, 185, 50).draw(Palette::Black);
		TextureAsset(L"T").draw(345, 230);
		//timer
		font((time / 60000),L"ï™", ((time % 60000) / 1000), L"ïb", ((time % 1000) / 100)).draw(350, 280);
		player1.draw();
		player2.draw();
}