#ifndef __RENDER
#define __RENDER

#include <windows.h>
#include <gl/gl.h>

void RenderGeometry(GLenum Mode,GLvoid* RawData,GLvoid *RawColor,size_t DataLength);
void RenderGeometry(GLenum Mode,GLvoid* RawData,size_t DataLength);
#endif

