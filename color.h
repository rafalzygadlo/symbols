#ifndef __COLOR_H
#define __COLOR_H

#include <wx/wx.h>
#include <wx/wrapsizer.h>

class CColor;
class CColorPanel: public wxPanel
{
	wxWindow *m_Parent, *m_Top;
	wxBoxSizer *m_Sizer;
	wxPanel *m_Panel;
	wxWrapSizer *m_PanelSizer;
	wxArrayPtrVoid m_ColorPanels;
	
	void New(wxColor color);
			
public:

	CColorPanel(wxWindow *parent, wxWindow *top);
	~CColorPanel();
	void OnNew(wxCommandEvent &event);
	void OnEdit();
	void OnDelete(CColor *ptr);
	void OnEdit(CColor *ptr);
	wxArrayPtrVoid GetColorPanels();

	DECLARE_EVENT_TABLE();

	enum
	{
		ID_NEW = 8124,
	
	};

};

class CColor: public wxPanel
{
	wxWindow *m_Parent;
	CColorPanel *m_ColorPanel;
	wxBoxSizer *m_Sizer;
	wxPanel *m_Panel;
	
	void OnContextMenu(wxContextMenuEvent &event);
	void OnDelete(wxCommandEvent &event);
	void OnEdit(wxCommandEvent &event);

public:

	CColor(wxWindow *parent, CColorPanel *panel);
	~CColor();
	void SetColor(wxColor color);
	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_DELETE = 8124,
		ID_NEW,
		ID_EDIT,
	};

};


#endif