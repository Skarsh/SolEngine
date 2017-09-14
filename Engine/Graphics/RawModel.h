#pragma once

#include <glad\glad.h>
#include <iostream>

class RawModel
{
private: 
	GLuint m_vaoID;
	GLuint m_vertexCount;

public:
	RawModel(GLuint vaoID, GLuint vertexCount)
		: m_vaoID{vaoID}, m_vertexCount{vertexCount}
	{
	}

	GLuint& getVaoID();

	GLuint& getVertexCount();

};