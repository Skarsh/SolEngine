
#include "ShaderManager.h"

using namespace Managers;

std::map<std::string, GLuint> ShaderManager::programs;
std::map<GLuint, ShaderManager::Shaders> ShaderManager::programShaders;


ShaderManager::ShaderManager(void)
{

}


ShaderManager::~ShaderManager(void)
{
	std::tuple<GLuint, GLuint> shaders;

	// detach shaders and delete programs
	std::map<std::string, GLuint>::iterator i;
	std::map<GLuint, ShaderManager::Shaders>::iterator j;
	for (i = programs.begin(); i != programs.end(); ++i)
	{
		GLuint program = i->second;
		
		// iterates trough all  Shaders structs related to the program
		for (j = programShaders.begin(); j != programShaders.end(); ++j)
		{
			// There are probably some perfromance enhancments that could be done here.

			ShaderManager::Shaders shaders = j->second;
			// Detaches all the shaders which are attached to the program.
			glDetachShader(program, shaders.vertexShader);	
			
			glDetachShader(program, shaders.fragmentShader);
			
		}
		
		glDeleteProgram(program);
		
	}

	programShaders.clear();
	programs.clear();
}

std::string ShaderManager::readShader(const std::string& fileName)
{
	// use filename.c_str() to convert to const char*

	std::string shaderPath = fileName.c_str();

	std::string shaderCode;
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open file
		shaderFile.open(shaderPath);
		std::stringstream shaderStream;
		// read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		// convert stream into string
		shaderCode = shaderStream.str();


	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	return shaderCode;

}

void ShaderManager::checkCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")		// Assumes it is shader
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{	
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
		}
	}

}

// creates and compiles shader
GLuint ShaderManager::createShader(GLenum shaderType, const std::string& source, const std::string& shaderName)
{
	// use filename.c_str() to convert to const char*

	const char* shaderSource = source.c_str();

	GLuint shader;
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	checkCompileErrors(shader, shaderName);

	return shader;

}


void ShaderManager::createProgram(const std::string& programName, const std::string& vertexPath,
	const std::string& fragmentPath)
{

	std::string vertexShaderCode = readShader(vertexPath);
	std::string fragmentShaderCode = readShader(fragmentPath);

	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderCode, "VERTEX_SHADER");
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderCode, "FRAGMENT_SHADER");

	int success = 0;
	unsigned int program;
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	checkCompileErrors(program, "PROGRAM");


	// SHOULD CHECK IF THE SHADERNAME IS ALREADY IN THE MAP

	if (program != NULL)
	{
		programShaders[program] = Shaders{ vertexShader, fragmentShader };
		std::cout << "ShaderManager::createProgram() - " << "vertexShaderID: " << vertexShader
				  << " fragmentShaderID: " << fragmentShader << std::endl;
	}

	if (programs[programName] == NULL)
	{

		programs[programName] = program;

	}
	else
	{
		std::cout << "ERROR::ShaderManager::createShader(): The shaderName is already in the list" << std::endl;
	}






}

const GLuint ShaderManager::getProgram(const std::string& programName)
{
	//make sure that you check if program exist first
	//before you return it
	if (programs[programName] != NULL)
	{
		return programs.at(programName);
	}
	else
	{
		std::cout << "ERROR::ShaderManager::getShader(): The shader does not exist in the programs map." << std::endl;
	}

	return 0;
}


const GLuint ShaderManager::getShader(const std::string& programName, const GLenum shaderType)
{
	GLuint program = getProgram(programName);

	// Should do this in a for-loop when more shader types are implemented.

	if (programShaders.at(program).vertexShader == NULL || programShaders.at(program).fragmentShader == NULL)
	{
		std::cout << "ShaderManager.cpp::getShader() - the requested shader is NULL" << std::endl;
		return -1;
	}

	switch (shaderType)
	{
	case GL_VERTEX_SHADER:
		return programShaders.at(program).vertexShader;
		break;
	case GL_FRAGMENT_SHADER:
		return programShaders.at(program).fragmentShader;
		break;
	default:
		std::cout << "ShaderManager.cpp::getShader() - the requested shadertype is not supported." << std::endl;
		return -1;
		break;
	}
}


void Managers::ShaderManager::startProgram(GLuint program)
{

	glUseProgram(program);

}

void Managers::ShaderManager::stopProgram()
{
	glUseProgram(0);
}



void Managers::ShaderManager::cleanUp()
{

	

	stopProgram();
	

}

// UTILITY UNIFORM FUNCTIONS

void Managers::ShaderManager::setBool(const std::string & programName, const std::string & uniformName, bool value) const
{
	GLuint program = programs.at(programName);

	glUniform1i(glGetUniformLocation(program, uniformName.c_str()), value);
}

void Managers::ShaderManager::setInt(const std::string & programName, const std::string & uniformName, int value) const
{
	GLuint program = programs.at(programName);

	glUniform1i(glGetUniformLocation(program, uniformName.c_str()), value);

}

void Managers::ShaderManager::setFloat(const std::string & programName, const std::string & uniformName, float value) const
{
	GLuint program = programs.at(programName);

	glUniform1f(glGetUniformLocation(program, uniformName.c_str()), value);

}

void Managers::ShaderManager::setVec2v(const std::string & programName, const std::string & uniformName, const glm::vec2 & value) const
{
	GLuint program = programs.at(programName);

	glUniform2fv(glGetUniformLocation(program, uniformName.c_str()), 1, &value[0]);

}

void Managers::ShaderManager::setVec2f(const std::string & programName, const std::string & uniformName, float x, float y) const
{
	GLuint program = programs.at(programName);

	glUniform2f(glGetUniformLocation(program, uniformName.c_str()), x, y);
}

void Managers::ShaderManager::setVec3v(const std::string & programName, const std::string & uniformName, const glm::vec3 & value) const
{
	GLuint program = programs.at(programName);

	glUniform3fv(glGetUniformLocation(program, uniformName.c_str()), 1, &value[0]);
}

void Managers::ShaderManager::setVec3f(const std::string & programName, const std::string & uniformName, float x, float y, float z) const
{
	GLuint program = programs.at(programName);

	glUniform3f(glGetUniformLocation(program, uniformName.c_str()), x, y, z);
}

void Managers::ShaderManager::setVec4v(const std::string & programName, const std::string & uniformName, const glm::vec4 & value) const
{
	GLuint program = programs.at(programName);

	glUniform4fv(glGetUniformLocation(program, uniformName.c_str()), 1, &value[0]);
}

void Managers::ShaderManager::setVec4f(const std::string & programName, const std::string & uniformName, float x, float y, float z, float w)
{
	GLuint program = programs.at(programName);

	glUniform4f(glGetUniformLocation(program, uniformName.c_str()), x, y, z, w);
}

void Managers::ShaderManager::setMat2(const std::string & programName, const std::string & uniformName, const glm::mat2 & mat) const
{
	GLuint program = programs.at(programName);

	glUniformMatrix2fv(glGetUniformLocation(program, uniformName.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Managers::ShaderManager::setMat3(const std::string & programName, const std::string & uniformName, const glm::mat3 & mat) const
{
	GLuint program = programs.at(programName);

	glUniformMatrix3fv(glGetUniformLocation(program, uniformName.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Managers::ShaderManager::setMat4(const std::string & programName, const std::string & uniformName, const glm::mat4 & mat) const
{
	GLuint program = programs.at(programName);

	glUniformMatrix4fv(glGetUniformLocation(program, uniformName.c_str()), 1, GL_FALSE, &mat[0][0]);
}

