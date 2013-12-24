#pragma once
#include <SDL.h>
#include <Windows.h>
#include "glsl.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glu.h>
#include "GLSLShader.h"
using namespace cwc;
class CWindowSDL
{
public:
		
	CGLSLShader sh;

	

	CWindowSDL(void);
	~CWindowSDL(void);

	SDL_Surface *main_screen;
	SDL_Event event;
	int sdlflags;
	int Width;
	int Height;

	
	void Init( int Width, int Height );
	void Run();
	void End();
	double angle;
	
	GLUquadricObj *quadratic;
	

protected:
	void Resize( int W, int H );
	void Render();
	void ReadLine(FILE * file,char *string);


};
