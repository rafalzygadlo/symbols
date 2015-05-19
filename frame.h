#ifndef __FRAME
#define __FRAME

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/fileconf.h>
#include <wx/mstream.h>
#include "conf.h"
#include "dll.h"
#include "command.h"
#include <vector>
#include "graph.h"

class CMyIcon;
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
	//wxPanel *PanelIcon;
	//CMyIcon *MarkerIcon;
	
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
	bool IsOnScreen(int x, int y);

					
public:
		
	void ShowWindow(bool show);		
	CMyFrame(void *Parent, wxWindow *ParentPtr);
	~CMyFrame();
		
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_CLOSE = 5312,
		ID_NAME,
		ID_DESCRIPTION,
		ID_DELETE,
		ID_LON,
		ID_LAT,
		ID_COMMAND,
	
	};

};

#endif