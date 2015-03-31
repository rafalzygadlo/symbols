#ifndef __GRAPH_H
#define __GRAPH_H
#include <wx/wx.h>
#include <wx/glcanvas.h>
#include "data.h"
#include "buffer.h"
#include "ticker.h"
#include "station.h"
#include "FTGL/ftgl.h"

class CGraph : public wxGLCanvas
{
	CStation *m_Station;
	int m_Id;
	int m_Col,m_Row;
	bool m_Selected;
	int m_ScreenWidth;
	int m_ScreenHeight;
	int m_GridX,m_GridY;
	float m_MouseX, m_MouseY;
	int m_MouseZoomX, m_MouseZoomY;
	float m_MoveX,m_MoveY;
	float m_OldMoveX,m_OldMoveY;
    float m_OldX,m_OldY;
	float m_Scale;
	int m_ScaleFactor;
	CBuffer *m_Buffer;
	wxGLContext *GLContext;
	float m_Arrow;
	bool m_Rescale;
	const wchar_t *m_Title;
	FTPixmapFont *m_Font;
	int m_Seconds;
	float m_XScale,m_YScale;

	float m_GraphTop;
	float m_GraphBottom;
	float m_GraphLeft;
	float m_GraphRight;

	float m_GridTop;
	float m_GridBottom;
	float m_GridLeft;
	float m_GridRight;
				
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
	
	CGraph(wxWindow *parent, CStation *station);
	~CGraph();		
	void SetPointsBuffer(CBuffer *ptr);
	void SetTitle(const wchar_t *v);	
	
	enum
	{
		ID_TIMER = 2345,
	};
		
	DECLARE_EVENT_TABLE();
};


#endif
