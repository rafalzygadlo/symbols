#ifndef __GRAPH_H
#define __GRAPH_H
#include <wx/wx.h>
#include <wx/glcanvas.h>
#include "ticker.h"
#include "ftgl/ftgl.h"
#include "naviarray.h"
#include "geometryconfig.h"

#define MIN_SCALE 1
#define MAX_SCALE 1000

class CGraph : public wxGLCanvas
{
	FTPixmapFont *m_Font;
	CNaviArray <nvPoint3f> m_Buffer;
	CNaviArray <nvRGBA> m_Color;
	int m_Speed;
	int m_OldKey;
	int m_Id;
	int m_ScreenWidth;
	int m_ScreenHeight;
	float m_MouseX, m_MouseY;
	float m_MoveX,m_MoveY;
	float m_OldMoveX,m_OldMoveY;
    float m_OldX,m_OldY;
	float m_Scale;
	int m_ScaleFactor;
	wxGLContext *GLContext;
	float m_Arrow;
	bool m_Rescale;
	const wchar_t *m_Title;
	float m_XScale,m_YScale;

	float m_GraphTop;
	float m_GraphBottom;
	float m_GraphLeft;
	float m_GraphRight;

	float m_GridTop;
	float m_GridBottom;
	float m_GridLeft;
	float m_GridRight;
	
	int m_Type;
	float m_Min;
	float m_Max;
	int m_TimeTo;

	void OnPaint(wxPaintEvent &event);
	void OnSize(wxSizeEvent &event);
	void OnMouse(wxMouseEvent &event);
	void OnMouseLeave(wxMouseEvent &event);
	void OnMouseEnter(wxMouseEvent &event);
	void OnKeyUp(wxKeyEvent &event);
		
#ifdef GLSL
	int LoadShader(GLenum type, const char *filename);
	char *ReadShader( const char* filename );
#endif
	
	void SetScaleUp();
	void SetScaleDown();
	void UpdateViewPort();
	void PrepareBuffer();
	void RenderText( float x, float y, const char *text );
	void RenderText( float x, float y, const wchar_t *text );
	void RenderGrid();
	void RenderData();
	//void RenderReferencePoint();
	void RenderDebug();
	void RenderCube();
	void RenderTitle();
	void Render();
	void SetValues();

public:
	
	CGraph(wxWindow *parent);
	~CGraph();		
	void SetTitle(const wchar_t *v);	
	void AddPoint(nvPoint3f v);
	void AddColor(nvRGBA v);
	void SetMin(float v);
	void SetMax(float v);
	void SetTimeTo(int v);
	void Clear();


	enum
	{
		ID_TIMER = 2000,
	};
		
	DECLARE_EVENT_TABLE();
};


#endif
