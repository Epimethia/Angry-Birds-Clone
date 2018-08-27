#pragma once

//Resource Header that contains includes
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtx\string_cast.hpp"

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <memory>

class ShaderLoader {
private:

	std::string ReadShader(char *filename);
	GLuint CreateShader(GLenum shaderType,
		std::string source,
		char* shaderName);

public:
	ShaderLoader(void);
	~ShaderLoader(void);
	GLuint CreateProgram(char* VertexShaderFilename,
		char* FragmentShaderFilename);

	std::map<std::string, GLuint> Shaders;


};
