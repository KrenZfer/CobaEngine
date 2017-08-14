#pragma once

#include <GameEngine\Graphic\GLSLProgram.h>
#include <GameEngine\Graphic\WindowManager.h>
#include <GameEngine\Graphic\Camera.h>
#include <GameEngine\Graphic\Timing.h>
#include <GameEngine\Graphic\SpriteBatch.h>
#include <GameEngine\Graphic\FontManager.h>
#include <GameEngine\Graphic\Sprite.h>
#include <GameEngine\Graphic\ImageLoader.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\type_ptr.hpp>

using namespace std;

class Zombie;

enum class GameState { PLAY, EXIT, PAUSE };

class MainGame {
public:
	MainGame();
	~MainGame();
	void run();

private:

	//Initializes SDL
	void initSystems();

	//Initializes shaders
	void initShaders();

	//Initialize levels
	void initLevel();

	//Main game loop
	
	void gameLoop();
	void drawGame();
	void drawSomethingHud();
	void processInput();
	GameState m_gameState;
	EngineProject2D::GLSLProgram m_fontProgram;
	EngineProject2D::WindowManager m_window;
	EngineProject2D::Camera m_camera;
	EngineProject2D::SpriteBatch m_hudSpriteBatch2;
	EngineProject2D::SpriteBatch spritePerson;
	EngineProject2D::FontManager* m_fontManager;
	EngineProject2D::GLSLProgram m_spriteProgram;
	int m_screenWidth;
	int m_screenHeight;
	EngineProject2D::FpsLimiter m_fpsLimiter;
	float m_fps;
	int m_currentLevel;
	EngineProject2D::Sprite person;
	EngineProject2D::Sprite tembok;
	GLuint fontProgram;
	GLuint spriteProgram;
	bool once;

};
