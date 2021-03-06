#pragma once

#include "../staticDependancies/glad/glad.h"
#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>

//Static stuff
static void sdl_die(const char * message)
{
	fprintf(stderr, "%s: %s\n", message, SDL_GetError());
	exit(2);
}

class AbstractFramework
{
public:
	AbstractFramework();
	virtual ~AbstractFramework();

	void Run();

protected:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	void ClearTarget();

private:
	void InitializeSDL();
	void InitializeWindow();
	void InitializeUtilities();
	void BindOpenGL();
	void InitializeDebug();
	void InitializeGame();

	void GameLoop();

private:
	SDL_GLContext m_GlContext = nullptr;
};

