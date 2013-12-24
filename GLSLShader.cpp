#include "GLSLShader.h"

CGLSLShader::CGLSLShader(void)
{
	status = 0;
}

CGLSLShader::~CGLSLShader(void)
{
}
void CGLSLShader::InitShaders()
{
	int Error;
	Error = glewInit();
	printf("%i \n",Error);
}
void CGLSLShader::Load(char* filepath,eShader_Type shadertype)
{
	FILE *file;
	

	if (shader_source != NULL)
		delete[] shader_source;

	if (filepath != NULL) 
	{
		file = fopen(filepath,"rt");	
	} else printf("incorrect path! \n");

	int count = 0;

	if (file != NULL) 
	{
		fseek(file,0,SEEK_END);
		count = ftell(file);
		rewind(file);

		if (count > 0)
		{
			shader_source = new char[count + 1];
			count = fread(shader_source,sizeof(char),count,file);
			shader_source[count] = 0;
		}
		fclose(file);
	}
	this->compile_shader(shadertype);
	//printf("%s \n",shader_source);
}
void printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s \n",infoLog);
        free(infoLog);
    }
}

void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s \n",infoLog);
        free(infoLog);
    }
}

bool CGLSLShader::compile_shader(eShader_Type shadertype)
{
	//InitShaders();

	
	if (shadertype == VertexShader)
	{
		v = glCreateShader(GL_VERTEX_SHADER);
		const char *ch = shader_source;
		glShaderSource(v,1,&ch,NULL);
		glCompileShader(v);
		printf("VERTEX_SHADER \n");
		printShaderInfoLog(v);
		status++;
	}
	if (shadertype == FragmentShader)
	{
		f = glCreateShader(GL_FRAGMENT_SHADER);
		const char *ch = shader_source;
		glShaderSource(f,1,&ch,NULL);
		glCompileShader(f);
		printf("FRAGMENT_SHADER \n");
		printShaderInfoLog(f);
		status++;

	}

	if (status == 2) 
	{
		p = glCreateProgram();
		glAttachShader(p,v);
		glAttachShader(p,f);
		glLinkProgram(p);
		//glUseProgram(p);
		printf("Programm \n");
		printProgramInfoLog(p);
		printf("shader compilated! \n");
	}

	return false;
}
void CGLSLShader::Begin()
{
	//glLinkProgram(p);
	if (status == 2)
		glUseProgram(p);
}
void CGLSLShader::End()
{
	glUseProgram(0);
}