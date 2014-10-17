#ifndef __ITEM_H
#define __ITEM_H

#include <wx/wx.h>
#include <wx/wrapsizer.h>
#include <wx/grid.h>
#include "listctrl.h"

class CItem;
class CItemPanel: public wxPanel
{
	wxWindow *m_Top;
	wxBoxSizer *m_Sizer;
	wxArrayPtrVoid m_Items;
				
public:

	CItemPanel(wxWindow *top, wxWindow *parent);
	~CItemPanel();
	void Read(wxString query);
	wxArrayPtrVoid GetItems();
	void _Layout();
	
};

class CItem: public wxPanel
{
	int m_Counter;
	CItemPanel *m_ItemPanel;
	wxString m_Id;
	wxStaticText *m_Name;
	wxComboBox *m_Combo;
	wxBoxSizer *m_ComboSizer;
	wxScrolledWindow *m_Scroll;
		
	void OnDelete(wxCommandEvent &event);
	void OnNew(wxCommandEvent &event);
	void AppendCombo();

public:

	CItem(CItemPanel *parent,wxString name);
	~CItem();
	void _SetId(wxString v);
	void _SetName(wxString v);
	wxString _GetId();
	void Read(wxString query, int field, wxComboBox *combo);

	
	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_DELETE = 8124,
		ID_NEW,
		ID_EDIT,
	};

};



#endif