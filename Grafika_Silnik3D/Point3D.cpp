#include"Point3D.h"

void Point3D::draw()
{
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_POINTS, 0, 1);
}