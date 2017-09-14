#pragma once


#include <glad\glad.h>
#include "RawModel.h"
#include <vector>
#include <assert.h>
#include <iostream>

class Loader
{
private:

	// Could probably use allocated arrays to decrease overhead and increase performance.
	std::vector<GLuint> m_vaos; 
	std::vector<GLuint> m_vbos;

	GLuint createVAO();

	void storeDataInAttributeList(GLint attributeNumber, GLfloat* data, GLuint dataLength);

	void bindIndicesBuffer(GLint* indices, GLuint indicesLength);

	void unbindVAO();

public:

	Loader();

	~Loader();

	RawModel loadToVao(GLfloat* positions, GLuint positionsLength, GLint* indices, GLuint indicesLength);

	void cleanUp();

};