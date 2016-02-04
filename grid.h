#ifndef __GRID
#define __GRID

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include "ticker.h"
#include "FTGL/ftgl.h"

#define MIN_SCALE 1
#define MAX_SCALE 1000
#define DEFAULT_GRID_WIDTH		500
#define DEFAULT_GRID_HEIGHT		500
#define DEFAULT_CIRCLE_DEGREE	30

class CGrid : public wxGLCanvas
{
	FTPixmapFont *m_Font;
	int m_Id;
	int m_Col,m_Row;
	bool m_Selected;
	float m_ScreenWidth;
	float m_ScreenHeight;
	int m_GridX,m_GridY;
	int m_MouseX, m_MouseY;
	int m_MouseZoomX, m_MouseZoomY;
	double m_MoveX,m_MoveY;
	double m_OldMoveX,m_OldMoveY;
    int m_OldX,m_OldY;
	float m_Scale;
	float m_Camera;
	double m_CenterX, m_CenterY;
	float m_ScaleFactor;
	//CBuffer *m_Buffer;
	wxGLContext *GLContext;
	int m_GridWidth, m_GridHeight;
	int m_GridStep;
	int m_X,m_Y;
				
	void OnPaint(wxPaintEvent &event);
	void OnSize(wxSizeEvent &event);
	void OnMouse(wxMouseEvent &event);
	void OnMouseLeave(wxMouseEvent &event);
	void OnKeyDown(wxKeyEvent &event);
		
	
	void UpdateViewPort();
	void Update3DViewPort();
	void PrepareBuffer();

	void SetScaleUp();
	void SetScaleDown();

	void RenderText( float x, float y, const char *text );
	void RenderGrid();
	void RenderGridText();
	void RenderData();
	void RenderReferencePoint();
	void RenderLastPoint();
	void RenderAccuracyCircle();
	void Render2Circle();
	void Render2CircleDegrees();
	void RenderCube();
	void RenderDirection();

	void RenderDebug();
	void Render();
	
	void SetColor(int mid,wxPaintDC &dc);
	void SetValues();

public:
	
	CGrid(wxWindow *parent);
	~CGrid();		
	//void SetPointsBuffer(CBuffer *ptr);
		
	enum
	{
		ID_TIMER = 1600,
	};
		
	DECLARE_EVENT_TABLE();
};


#endif
