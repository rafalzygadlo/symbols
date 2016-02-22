#ifndef __FRAME
#define __FRAME

#include <wx/wx.h>
#include <wx/notebook.h>
#include "conf.h"
#include "dll.h"
#include "symbolpanel.h"
#include "sbmsactionpanel.h"

class CMyFrame: public wxDialog
{
	int m_FrameWidth;
	int	m_FrameHeight;
	CMapPlugin *m_DLL;	
	CSymbol *SelectedPtr;
	wxPanel *m_Panel;
		
	CSymbolPanel *m_SymbolPanel;
	wxNotebook *m_Notebook;
	
	wxButton *ButtonClose;

	int ParentX, ParentY;
	wxWindow *_ParentPtr;

	void WriteConfig();
	void ReadConfig();
	wxPanel *GetPage1(wxWindow *parent);
	wxPanel *GetPage2(wxWindow *parent);
	void OnCloseButton(wxCommandEvent &event);
	void OnCommandButton(wxCommandEvent &event);
	void OnClose(wxCloseEvent &event);
	void OnTextChanged(wxCommandEvent &event);
	void OnLeftClick(wxCommandEvent &event);
	void OnPaint(wxPaintEvent &event);
	void OnLon(wxCommandEvent &event);
	void OnLat(wxCommandEvent &event);
	void OnMouseMove(wxMouseEvent& event);
	bool IsOnScreen(int x, int y);

					
public:
		
	void ShowWindow(bool show);		
	CMyFrame(void *Parent, wxWindow *ParentPtr);
	~CMyFrame();
		
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_CLOSE = 1400,
		ID_NAME,
		ID_DESCRIPTION,
		ID_DELETE,
		ID_LON,
		ID_LAT,
		ID_COMMAND,
	
	};

};

#endif