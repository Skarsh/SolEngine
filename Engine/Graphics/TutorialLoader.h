#pragma once

#include <glad\glad.h>
#include "RawModel.h"
#include <vector>
#include <assert.h>
#include <iostream>

class TutorialLoader
{

private: 
	// Could probably use allocated arrays to decrease overhead and increase performance.
	std::vector<GLuint> m_vaos;
	std::vector<GLuint> m_vbos;

	GLuint createVAO();

	void storeDataInAttributeList(GLint attributeNumber, GLfloat* data, GLuint dataLength, GLint stride);


	void unbindVAO();

public:

	RawModel loadToVao(GLfloat* vertices, GLuint verticesLength, GLint stride);

	void cleanUp();

};