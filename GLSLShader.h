#pragma once
#include <GL/Glew.h>
#include <stdio.h>
#include <stdlib.h>

enum eShader_Type {VertexShader,FragmentShader};

class CGLSLShader
{
public:
	char *shader_source;
	int status;
	void InitShaders();
	bool compile_shader(eShader_Type shadertype);
	void Load(char* filepath,eShader_Type shadertype);
	
	GLuint f,v,p; // Shaders descriptors 

	void Begin();
	void End();
	CGLSLShader(void);
	~CGLSLShader(void);
};
