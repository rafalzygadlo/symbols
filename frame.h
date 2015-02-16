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

class CMyIcon;
class CMyFrame: public wxDialog
{
	void *m_DB;
	CMapPlugin *m_DLL;	
	SSymbol *SelectedPtr;
	wxTextCtrl *m_TextName;
	wxPanel *m_Panel;
	wxTextCtrl *m_TextInfo;
	
	wxButton *m_ButtonCommand;
	CPicturePanel *m_PicturePanel;
	CCommandPanel *m_CommandPanel;

	
	wxButton *ButtonClose;
	//wxPanel *PanelIcon;
	//CMyIcon *MarkerIcon;
	wxTextCtrl *m_TextLon;
	wxTextCtrl *m_TextLat;
	int ParentX, ParentY;
	wxWindow *_ParentPtr;

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

					
public:

	void ShowIconChanger(bool show);
	//void SetMarkerIcon(int id);
	void ShowWindow(bool show);		
	CMyFrame(void *db,void *Parent, wxWindow *ParentPtr);
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