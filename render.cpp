#include "render.h"

void RenderGeometry(GLenum Mode, GLvoid* RawData,GLvoid *RawColor, size_t DataLength)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_UNSIGNED_BYTE,  0, RawColor);
    glVertexPointer(3, GL_DOUBLE, 0, RawData);
    glDrawArrays(Mode, 0, DataLength);
    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
