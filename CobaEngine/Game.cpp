#include "Game.h"

Game::Game() : screenWidth(800), screenHeight(600), windowName("Game")
{
	init();
}


Game::~Game(){}

void Game::init() {
	EngineProject2D::init();

	g_windowManager.createWindow(windowName, screenWidth, screenHeight, true, WindowManager::WINDOWED);
}

void Game::update() {
	int l;
	while (true)
	{
		cout << "halo" << endl;
		cin >> l;
		SDL_Quit();
		exit(0);
	}
}

void Game::run() {
	init();
	update();
}

int main(int argc, char *argv[]) {
	Game game;
	game.run();
	return 0;
}