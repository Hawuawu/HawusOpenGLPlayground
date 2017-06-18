#include "VXLEShaderProgram.h"


VXLEShader::VXLEShader(string shaderFile, int type) : shaderFile(shaderFile), type(type)
{

}

GLuint VXLEShaderProgram::compile(VXLEShader oneshader)
{
	return compile(vector<VXLEShader>{oneshader});
}
GLuint VXLEShaderProgram::compile(vector<VXLEShader> shaders)
{

	GLuint program = glCreateProgram();

	for (int i = 0; i < shaders.size(); i++)
	{
		VXLEShader shader = shaders.at(i);
		GLuint shaderProgram = glCreateShader(shader.type);

		string shaderProgramCode;
		ifstream fileStream(shader.shaderFile, ios::in);

		if (!fileStream.is_open()) {
			cerr << "Cannot read the file" << shader.shaderFile << endl;
			return -1;
		}

		string line = "";
		while (!fileStream.eof()) {
			getline(fileStream, line);
			shaderProgramCode.append(line + "\n");
		}


		cout << "------------------ [Shader code] ------------------" << endl;

		cout << shaderProgramCode << endl;

		cout << "---------------------------------------------------" << endl;

		fileStream.close();

		const char *shaderProgramSrc = shaderProgramCode.c_str();

		GLint shaderCompileResult = GL_FALSE;

		int shaderCompileLogLenght;

		cout << "Compiling shader." << endl;
		glShaderSource(shaderProgram, 1, &shaderProgramSrc, NULL);
		glCompileShader(shaderProgram);

		glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &shaderCompileResult);
		glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &shaderCompileLogLenght);

		vector<GLchar> vertShaderError((shaderCompileLogLenght > 1) ? shaderCompileLogLenght : 1);
		glGetShaderInfoLog(shaderProgram, shaderCompileLogLenght, NULL, &vertShaderError[0]);
		cout << &vertShaderError[0] << endl;

		cout << "Linking program" << endl;
		glAttachShader(program, shaderProgram);

		glGetProgramiv(program, GL_LINK_STATUS, &shaderCompileResult);
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &shaderCompileLogLenght);
		vector<GLchar> programError((shaderCompileLogLenght > 1) ? shaderCompileLogLenght : 1);
		glGetProgramInfoLog(program, shaderCompileLogLenght, NULL, &programError[0]);
		cout << &programError[0] << endl;

		glDeleteShader(shaderProgram);
	}

	glLinkProgram(program);
	return program;
}