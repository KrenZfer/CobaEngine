#ifndef _H_GAME_H_
#define _H_GAME_H_
#include <Graphic\WindowManager.h>
#include <Graphic\EngineProject2D.h>
#include <string>

using namespace EngineProject2D;
class Game {

public:
	Game();
	~Game();

	void init();
	void update();
	void run();

	WindowManager g_windowManager;

	int screenWidth;
	int screenHeight;
	string windowName;

};

#endif // !
