#include <Siv3D.hpp>

#include "Game.h"

void Game::init(){
	TextureAsset::Register(L"block", L"item/block.png");
	TextureAsset::Register(L"background", L"item/background.png");
	TextureAsset::Register(L"stage", L"item/stage.png");
	TextureAsset::Register(L"T", L"item/time.png");
	state = State::TITLE;
	font(30);
}

void Game::run(){
	switch (state){
	case State::TITLE:
		if (Input::KeyEnter.clicked)
		{
			state = State::GAME;
		}
		break;
	case State::GAME:
		if (Input::KeyEnter.clicked)
		{
			state = State::PAUSE;
		}
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
		font(L"TITLE").draw();
		break;
	case State::GAME:
		//TextureAsset(L"background").draw();
		Rect(0, 0, 850, 550).draw(Palette::Gray);
		TextureAsset(L"stage").map(SIZE * 8, SIZE * 12).draw(30, 70);
		TextureAsset(L"stage").map(SIZE * 8, SIZE * 12).draw(530, 70);
		Rect(328, 70, 70, 100).draw(Palette::Black);
		Rect(450, 70, 70, 100).draw(Palette::Black);
		Rect(330, 275, 185, 50).draw(Palette::Black);
		TextureAsset(L"T").draw(345, 230);
		break;
	case State::PAUSE:
		font(L"PAUSE").draw();
		break;
	case State::END:
		font(L"END").draw();
		break;
	}

}