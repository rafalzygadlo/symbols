#ifndef __COLOR_H
#define __COLOR_H

#include <wx/wx.h>
#include <wx/hyperlink.h>

class CColorPanel: public wxPanel
{
	wxWindow *m_Parent;
	wxBoxSizer *m_Sizer;
	wxBoxSizer *m_ScrollSizer;
	wxScrolledWindow *m_Scroll;
			
public:

	CColorPanel(wxWindow *parent);
	~CColorPanel();
	void OnAddColor(wxHyperlinkEvent &event);

	DECLARE_EVENT_TABLE();

	enum
	{
		ID_ADD = 8124,
	};

};

class CColor: public wxPanel
{
	wxWindow *m_Parent;
	wxBoxSizer *m_Sizer;
	
	void OnContextMenu(wxContextMenuEvent &event);

public:

	CColor(wxWindow *parent);
	~CColor();
	
	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_DELETE = 8124,
		ID_EDIT,
	};

};


#endif