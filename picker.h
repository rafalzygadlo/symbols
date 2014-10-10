#ifndef __PICKER_H
#define __PICKER_H

#include <wx/wx.h>
#include <wx/wrapsizer.h>
#include <wx/grid.h>
#include "listctrl.h"

class CPicker;
class CPickerPanel: public wxPanel
{
	wxWindow *m_Parent, *m_Top;
	wxBoxSizer *m_Sizer;
	wxPanel *m_Panel;
	wxBoxSizer *m_PanelSizer;
	wxArrayPtrVoid m_Panels;
	int m_ControlType;
	wxWrapSizer *m_WrapSizer;
	//wxGrid *m_Grid;
	CListCtrl *m_List;
	CDialog *m_Dialog;
	void New(wxString id, wxString name);
			
public:

	CPickerPanel(wxWindow *parent, wxWindow *top,int control_type, wxString label);
	~CPickerPanel();
	void OnNew(wxCommandEvent &event);
	void OnDelete(CPicker *ptr);
	void OnEdit(CPicker *ptr);
	void Read(wxString query, int field);
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