#include "Loader.h"

#include <iostream>
#include "Loader.h"

// Currently only storing float values intended for vertices. 
RawModel Loader::loadToVao(GLfloat* positions, GLuint positionsLength, GLint* indices, GLuint indicesLength)
{
	/*	Only to check if the positions are right
	for (GLuint i = 0; i < positionsLength; ++i)
	{
		std::cout << positions[i] << std::endl;
	}
	*/
//	std::cout << "Size of positions: " << sizeof(positions) << std::endl;
	
	
	GLuint vaoID = createVAO();
	m_vaos.push_back(vaoID);					// Pushes a vao onto the stack
	
	bindIndicesBuffer(indices, indicesLength);

	storeDataInAttributeList(0, positions, positionsLength);		// Stores data in attribute list 0
	unbindVAO();
	return RawModel{ vaoID, indicesLength};		// number of vertices since the indices are their numeration
}

void Loader::cleanUp()
{
	// Delete all the vaos and vbos

	for (GLuint i = 0; i < m_vaos.size(); ++i)
	{
		if (m_vaos.at(i) != NULL)
			glDeleteVertexArrays(1, &m_vaos.at(i));
		else
			std::cout << "Loader.cpp::cleanUp() - " << "Tried to delete a non-existent VAO" << std::endl;
	}

	for (GLuint i = 0; i < m_vbos.size(); ++i)
	{
		if (m_vbos.at(i) != NULL)
			glDeleteBuffers(1, &m_vbos.at(i));
		else
			std::cout << "Loader.cpp::cleanUp() - " <<"Tried to delete a non-existent VBO" << std::endl;
	}

	// Clear the vector to free up space.

	m_vaos.clear();
	m_vaos.swap(std::vector<GLuint>(m_vaos));		// Not entirely sure about this.

	m_vbos.clear();
	m_vbos.swap(std::vector<GLuint>(m_vbos));

}

void Loader::storeDataInAttributeList(GLint attributeNumber, GLfloat* data, GLuint dataLength)
{

	// Stores all the data in a buffer.


	GLuint vboID;
	glGenBuffers(1, &vboID);
	m_vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	// Need to multiply by dataLength since it is a pointer.
	glBufferData(GL_ARRAY_BUFFER, sizeof(data) * dataLength, data, GL_STATIC_DRAW);		// GL_STATIC_DRAW until more utility is needed. 

	glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 0, 0);		// Need to investigate why this works.

	//glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);	// unbind buffer
}

void Loader::bindIndicesBuffer(GLint* indices, GLuint indicesLength)
{
	GLuint eboID;
	glGenBuffers(1, &eboID);
	m_vbos.push_back(eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * indicesLength, indices, GL_STATIC_DRAW);

}

GLuint Loader::createVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);		// Could possibly use glCreateVertexArrays, 
	glBindVertexArray(vaoID);
	std::cout << "Loader.cpp vaoID after creating new vao: " << vaoID << std::endl;		// Remove after debugging
	return vaoID;
}


void Loader::unbindVAO()
{
	glBindVertexArray(0);	// unbinds because of 0 as argument
}

Loader::Loader()
{
}

Loader::~Loader()
{
}

