#include "MainGame.h"
#include <GameEngine\Graphic\EngineProject2D.h>
#include <GameEngine\Graphic\ErrorHandling.h>
#include <GameEngine\Graphic\ResourceManager.h>
#include <GLM/gtx/rotate_vector.hpp>
#include <random>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 1.3f;

MainGame::MainGame() : m_screenWidth(800), m_screenHeight(600), m_gameState(GameState::PLAY), m_fps(0.0f)
{
	once = true;
}


MainGame::~MainGame()
{

}


void MainGame::run() 
{
	initSystems();
	gameLoop();
}


void MainGame::initSystems()
{
	//Initialize Game Engine
	EngineProject2D::init(); //Initialize sdl and set to double buffer.

	//Create Window
	m_window.createWindow("CobaEngine", m_screenWidth, m_screenHeight, false, EngineProject2D::WindowManager::WINDOWED);

	//Set up shaders
	initShaders();

	m_hudSpriteBatch2.Init();
	spritePerson.Init();
	

	//Initialize sprite font

	m_fontManager = new EngineProject2D::FontManager();

	m_fontManager->InitFont(32, "Fonts/arial.ttf");

	//Initialize camera
	m_camera.init(m_screenWidth, m_screenHeight);
	m_camera.setPosition(vec2(0.0f, 0.0f));

	person.init(0.0f, 0.0f, 1.0f, "Sprite/CharacterLeft_Jump.png");
	tembok.init(40.0f, 50.0f, 1.0f, "Sprite/light_bricks.png");
}


void MainGame::initShaders()
{
	fontProgram = m_fontProgram.BuildShader("Shaders/fonts.vert", "Shaders/fonts.frag");
	spriteProgram = m_spriteProgram.BuildShader("Shaders/spriteshader.vert", "Shaders/spriteshader.frag");
}


void MainGame::gameLoop()
{
	m_fpsLimiter.setMaxFPS(60.0f);

	const float DESIRED_FPS = 60;
	const int MAX_PHYSICS_STEPS = 6;
	const float MS_PER_SECOND = 1000;
	const float DESIRED_FRAME_TIME = MS_PER_SECOND / DESIRED_FPS;
	const float MAX_DELTA_TIME = 1.0f;

	float previousTicks = SDL_GetTicks(); //number of ticks since sdl was initialized


	while (m_gameState != GameState::EXIT)
	{
		float newTicks = SDL_GetTicks();
		float frameTime = newTicks - previousTicks; //Frame time is inversely proportional to fps
		previousTicks = newTicks;
		float totalDeltaTime = frameTime / DESIRED_FRAME_TIME;

		m_fpsLimiter.begin();

		processInput();

		int i = 0;
		while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS) //Risk spiral of death is cpu takes too long
		{
			float deltaTime = glm::min(totalDeltaTime, MAX_DELTA_TIME);
			totalDeltaTime -= deltaTime;
			i++;
		}

		m_camera.update();

		drawGame();

		m_fps = m_fpsLimiter.end();
	}
}


void MainGame::drawGame()
{
	//Set base depth to 1.0
	glClearDepth(1.0);
	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//draw Image
	m_spriteProgram.useShader();

	GLint samplerLocation = m_spriteProgram.getUniformLocation("mySampler");
	glUniform1i(samplerLocation, 0);

	GLint projloc = m_spriteProgram.getUniformLocation("projection");
	mat4 projection = m_camera.getCameraMatrix();
	glUniformMatrix4fv(projloc, 1, GL_FALSE, value_ptr(projection));

	spritePerson.begin();

	person.draw(spritePerson);
	tembok.draw(spritePerson);

	spritePerson.end();

	spritePerson.renderBatch();

	m_spriteProgram.unuseShader();

	//draw Text
	m_fontProgram.useShader();

	drawSomethingHud();

	m_fontProgram.unuseShader();

	m_window.swapBuffer();
}


void MainGame::processInput()
{
	SDL_Event evnt;
	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type) {
			case SDL_QUIT:
				m_gameState = GameState::EXIT;
				break;
		}
	}
}

void MainGame::drawSomethingHud()
{
	glActiveTexture(GL_TEXTURE0);
	glm::mat4 projection = m_camera.getCameraMatrix();
	GLint projloc = m_fontProgram.getUniformLocation("projection");
	glUniformMatrix4fv(projloc, 1, GL_FALSE, value_ptr(projection));

	GLint samplerLocation = m_spriteProgram.getUniformLocation("text");
	glUniform1i(samplerLocation, 0);

	m_hudSpriteBatch2.begin();

	string s = "abcdefghijklmnopqrstuvwxyz";
	m_fontManager->draw(m_hudSpriteBatch2, s, glm::vec2(0, 64), glm::vec2(1.0), EngineProject2D::RGBA8(255, 255, 255, 255), 0.0f, EngineProject2D::Justification::LEFT);

	m_hudSpriteBatch2.end();

	m_hudSpriteBatch2.renderBatch();
}