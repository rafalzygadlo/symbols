#ifndef __ITEM_H
#define __ITEM_H

#include <wx/wx.h>
#include <wx/wrapsizer.h>
#include <wx/grid.h>
#include "listctrl.h"

class CItem;
class CComboPanel;
class CItemPanel: public wxPanel
{
	wxWindow *m_Top;
	wxBoxSizer *m_Sizer;
	wxArrayPtrVoid m_Items;
				
public:

	CItemPanel(wxWindow *top, wxWindow *parent);
	~CItemPanel();
	void Read(wxString query);
	CItem *GetItem(int id);
	size_t GetCount();
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
	wxArrayPtrVoid m_List;
		
	
	void OnNew(wxCommandEvent &event);
	void AppendCombo();

public:

	CItem(CItemPanel *parent,wxString name);
	~CItem();
	void _SetId(wxString v);
	void _SetName(wxString v);
	wxString _GetId();
	void OnDelete(CComboPanel *panel);
	CComboPanel *GetCombo(int id);
	size_t GetCount();
	
	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_DELETE = 8124,
		ID_NEW,
		ID_EDIT,
	};

};

class CComboPanel: public wxPanel
{
	CItem *m_Parent;
	wxBoxSizer *m_Sizer;
	wxArrayPtrVoid m_Items;
	wxComboBox *m_Combo;

public:

	CComboPanel(CItem *parent, wxString id);
	void OnDelete(wxCommandEvent &event);
	void Read(wxString query);
	int _GetId();
	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_DELETE = 8124,
		
	};

	//void Read(wxString query);
	//wxArrayPtrVoid GetItems();
	//void _Layout();
	
};


#endif