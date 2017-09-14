#pragma once

#include <glad\glad.h>

#include <fstream>
#include <sstream>
#include <string>

#include <iostream>
#include <map>

// GLM includes
#include "../Dependencies\glm\glm.hpp"
#include "../Dependencies\glm\gtc\matrix_transform.hpp"
#include "../Dependencies\glm\gtc\type_ptr.hpp"


namespace Managers {
	class ShaderManager
	{
	
	private:
		
		struct Shaders
		{
			GLuint vertexShader;
			GLuint fragmentShader;
		};
		
		static std::map<std::string, GLuint> programs;
		static std::map<GLuint, Shaders> programShaders;
		
		// modify char* to string
		std::string readShader(const std::string& filename);

		GLuint createShader(GLenum shaderType, const std::string& source, const std::string& shaderName);


		void checkCompileErrors(GLuint shader, std::string type);


	public:
		
		ShaderManager(void);
		~ShaderManager(void);

		void createProgram(const std::string& programName, const std::string& vertexPath, const std::string& fragmentPath);

		static const GLuint getProgram(const std::string& programName);

		static const GLuint getShader(const std::string& programName, const GLenum shaderType);

		void startProgram(GLuint program);

		void stopProgram();

		void cleanUp();

		// Utility uniform functions, might be better with uniform blocks, but I dont know how to properly use them

		void setBool(const std::string &programName, const std::string &uniformName, bool value) const;
		// ------------------------------------------------------------------------
		void setInt(const std::string &programName, const std::string &uniformName, int value) const;
		
		// ------------------------------------------------------------------------
		void setFloat(const std::string &programName, const std::string &uniformName, float value) const;
		
		// ------------------------------------------------------------------------
		void setVec2v(const std::string &programName, const std::string &uniformName, const glm::vec2 &value) const;
	
		
		void setVec2f(const std::string &programName, const std::string &uniformName, float x, float y) const;
		
		// ------------------------------------------------------------------------
		void setVec3v(const std::string &programName, const std::string &uniformName, const glm::vec3 &value) const;
		

		void setVec3f(const std::string &programName, const std::string &uniformName, float x, float y, float z) const;
		
		// ------------------------------------------------------------------------
		void setVec4v(const std::string &programName, const std::string &uniformName, const glm::vec4 &value) const;
		
		void setVec4f(const std::string &programName, const std::string &uniformName, float x, float y, float z, float w);
		
		// ------------------------------------------------------------------------
		void setMat2(const std::string &programName, const std::string &uniformName, const glm::mat2 &mat) const;
	
		// ------------------------------------------------------------------------
		void setMat3(const std::string &programName, const std::string &uniformName, const glm::mat3 &mat) const;
	
		// ------------------------------------------------------------------------
		void setMat4(const std::string &programName, const std::string &uniformName, const glm::mat4 &mat) const;
	




	};


}
