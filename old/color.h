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
	wxBoxSizer *m_PanelSizer;
	wxArrayPtrVoid m_ColorPanels;
				
public:

	CColorPanel(wxWindow *parent, wxWindow *top);
	~CColorPanel();
	void OnNew(wxCommandEvent &event);
	void OnEdit();
	void OnDelete(CColor *ptr);
	void OnEdit(CColor *ptr);
	void New(wxColor color);
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
		
	void OnDelete(wxCommandEvent &event);
	void OnEdit(wxCommandEvent &event);

public:

	CColor(wxWindow *parent, CColorPanel *panel);
	~CColor();
	void SetColor(wxColor color);
	wxColor GetColor();
	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_DELETE = 8224,
		
	};

};


#endif