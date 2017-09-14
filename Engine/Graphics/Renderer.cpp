#include "Renderer.h"

#include <iostream>

// Clear the screen before drawing every draw call
void Renderer::prepare()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.8f, 0.75f, 0.90f, 1.0f);
}
/*	UNCOMMENT WHEN THE PROPER LOADER SYSTEM IS IMPLEMENTED AFTER TUTROIAL
void Renderer::render(RawModel model)
{

	glBindVertexArray(model.getVaoID());
	glEnableVertexAttribArray(0);			// is the one with the data hardcoded 
	glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);			// same attribArray
	glBindVertexArray(0);

}
*/

void Renderer::render(RawModel model)
{

	glBindVertexArray(model.getVaoID());
	glEnableVertexAttribArray(0);			// is the one with the data hardcoded 
	glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
	glDisableVertexAttribArray(0);			// same attribArray
	glBindVertexArray(0);

}