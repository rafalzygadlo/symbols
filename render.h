#ifndef __RENDER_H
#define __RENDER_H

#include <windows.h>
#include <gl/gl.h>

void RenderGeometry(GLenum Mode,GLvoid* RawData,GLvoid *RawColor, size_t DataLength);

#endif

