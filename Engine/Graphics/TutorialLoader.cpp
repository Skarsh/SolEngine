#include "TutorialLoader.h"

GLuint TutorialLoader::createVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);		// Could possibly use glCreateVertexArrays, 
	glBindVertexArray(vaoID);
	std::cout << "TutorialLoader.cpp vaoID after creating new vao: " << vaoID << std::endl;		// Remove after debugging
	return vaoID;
}

void TutorialLoader::storeDataInAttributeList(GLint attributeNumber, GLfloat * data, GLuint dataLength, GLint stride)
{

	GLuint vboID;
	glGenBuffers(1, &vboID);
	m_vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	// Need to multiply by dataLength since it is a pointer.
	glBufferData(GL_ARRAY_BUFFER, sizeof(data) * dataLength, data, GL_STATIC_DRAW);		// GL_STATIC_DRAW until more utility is needed. 

	glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GL_FLOAT), (void*)0);		

																				//glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);	// unbind buffer

}

void TutorialLoader::unbindVAO()
{
}

RawModel TutorialLoader::loadToVao(GLfloat* vertices, GLuint verticesLength, GLint stride)
{
	
	GLuint vaoID = createVAO();
	m_vaos.push_back(vaoID);					// Pushes a vao onto the stack


	storeDataInAttributeList(0, vertices, verticesLength, stride);		// Stores data in attribute list 0
	unbindVAO();
	return RawModel{vaoID, verticesLength};		// number of vertices since the indices are their numeration


}

void TutorialLoader::cleanUp()
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
			std::cout << "Loader.cpp::cleanUp() - " << "Tried to delete a non-existent VBO" << std::endl;
	}

	// Clear the vector to free up space.

	m_vaos.clear();
	m_vaos.swap(std::vector<GLuint>(m_vaos));		// Not entirely sure about this.

	m_vbos.clear();
	m_vbos.swap(std::vector<GLuint>(m_vbos));

}
