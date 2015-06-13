# include <Siv3D.hpp>
# include "Game.h"


void Main()
{
	Window::SetTitle(L"PuyoGame");
	Window::Resize(850, 550);

	Game game;
	while (System::Update())
	{
		game.run();
		game.draw();
	}
}
