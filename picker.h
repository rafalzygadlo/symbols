#ifndef __PICKER_H
#define __PICKER_H

#include <wx/wx.h>

class CPicker;
class CPickerPanel: public wxPanel
{
	wxWindow *m_Parent, *m_Top;
	wxBoxSizer *m_Sizer;
	wxPanel *m_Panel;
	wxBoxSizer *m_PanelSizer;
	wxArrayPtrVoid m_Panels;
	
	void New(wxString id, wxString name);
			
public:

	CPickerPanel(wxWindow *parent, wxWindow *top);
	~CPickerPanel();
	void OnNew(wxCommandEvent &event);
	void OnDelete(CPicker *ptr);
	void OnEdit(CPicker *ptr);
	wxArrayPtrVoid GetPanels();

	
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_NEW = 8124,
	};

};

class CPicker: public wxPanel
{
	wxWindow *m_Parent;
	CPickerPanel *m_PickerPanel;
	wxBoxSizer *m_Sizer;
	wxPanel *m_Panel;
	wxString m_Id;
	wxStaticText *m_Name;
	
	void OnContextMenu(wxContextMenuEvent &event);
	void OnDelete(wxCommandEvent &event);
	void OnEdit(wxCommandEvent &event);

public:

	CPicker(wxWindow *parent, CPickerPanel *panel);
	~CPicker();
	void _SetId(wxString v);
	void _SetName(wxString v);

	
	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_DELETE = 8124,
		ID_EDIT,
	};

};



#endif