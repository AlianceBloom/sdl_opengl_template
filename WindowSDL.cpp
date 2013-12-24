#include "WindowSDL.h"
#include <math.h>

CWindowSDL::CWindowSDL(void)
{
	angle = 0.0f;
}

CWindowSDL::~CWindowSDL(void)
{
	SDL_Quit();
}



void CWindowSDL::Init( int W, int H)
{
	sdlflags = SDL_HWSURFACE |SDL_OPENGL | SDL_DOUBLEBUF;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Error: %s \n",SDL_GetError());
		exit(0);
		SDL_Quit();
	}else
	{
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
		main_screen = SDL_SetVideoMode(W,H,32,sdlflags);
	}
	Width = W;
	Height = H;
	glewInit();
	quadratic=gluNewQuadric();          
	gluQuadricNormals(quadratic, GLU_SMOOTH);   

	glewInit();
	sh.Load("vshader.txt",VertexShader);
	sh.Load("fshader.txt",FragmentShader);

}

void CWindowSDL::Run()
{
	bool quit = false;
	while (quit == false)
	{
		SDL_Delay(16);

		while(SDL_PollEvent(&event) )
		{
			switch(event.type)
			{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						quit = true;
					}
					
					
				case SDL_MOUSEMOTION: 
						int x,y;
						SDL_GetMouseState(&x,&y);


					break;
						
	
				
				case SDL_MOUSEBUTTONDOWN: 

					

					break;



				case SDL_VIDEORESIZE:
					int Width = event.resize.w;
					int Height = event.resize.h;

					if (!SDL_SetVideoMode(Width , Height,0,sdlflags))
					{
						printf("Resize failed! \n");
					}
					Resize(Width,Height);
					break;

			}
		}
		Resize(Width,Height);
		
		
		Render();
		
	}
}

void CWindowSDL::End()
{
	SDL_Quit();
}


void CWindowSDL::Resize(int Width, int Height)
{
	glViewport(0,0,Width,Height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-10, 10,-10, 10, -100.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	gluLookAt(20.0,20.0,20.0,0.0,0.0,0.0,0.0,100.0,0.0);
	
	
}




void CWindowSDL::Render()
{	
	angle += 0.5;
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	
		glPushMatrix();
		glRotatef(angle,1,1,0);
		glTranslatef(0.0,.0,0.0);
		//glColor3f(0.0,0.0,0.7);
		sh.Begin();
			gluSphere(quadratic,3,15,15);
		sh.End();
		glPopMatrix();
	



	SDL_GL_SwapBuffers();
}