#ifndef __DIALOG_H
#define __DIALOG_H

#include <wx/wx.h>
#include "listctrl.h"
#include <wx/listbook.h>
#include "new.h"

class CListCtrl;
class CDialogPanel;
class CMultiDialogPanel;
class CDialog : public wxDialog
{
	CDialogPanel *m_DialogPanel;
	
	int m_ControlType;
	wxStaticText *m_TopLabel;
	wxButton *m_ButtonOk;
	wxString m_Id, m_Name;


public:
	CDialog(int control_type, bool picker);
	wxString _GetId();
	wxString _GetName();
	
};

class CDialogPanel: public wxPanel
{
	wxString m_Field;	
	wxString m_Order;
	CListCtrl *m_List;	
	int m_ControlType,m_ColumnWithName;
	wxString m_Table;
	wxString m_Id, m_Name;
	bool m_Picker;
	wxStaticText *m_TopLabel;
	wxButton *m_ButtonOk;
	wxListBox *m_ListBox;
	int m_IdType;
	wxArrayString m_FilterArray;
			
	void New();
	void EditArea(wxString id);
	void EditSymbolType(wxString id);
	void EditSeaway(wxString id);
	void EditLight(wxString id);
	void EditItem(wxString id);
	int GetItemTypeId(wxString id);
			
	void EditName(wxString id); // wszystkie tabele z polami [type]
	void EditType(wxString id); // wszystkie tabele z polami [type]
	
	void Read();
	void ReadItems();
	void ReadOthers();

	void Clear();
	void Select();
	void SetTable();
	void NewItem(CNew *ptr);

	void OnListBox(wxCommandEvent &event);

	wxComboBox *GetFilterCombo(wxWindow *Parent);
	wxListBox *GetFilterList(wxWindow *Parent);
	wxPanel *GetPanel(wxWindow *Parent);
	wxPanel *GetItemPanel(wxWindow *Parent);
	wxPanel *GetPanelList(wxWindow *Parent);

public:
	
	CDialogPanel(int control_type, wxWindow *parent,bool picker); // taki do pobrania tylko panela
		
	void OnNew();
	void OnEdit(wxString id);
	void OnDelete(wxString id);
	void OnColumnCLick(wxString field, int order);
	void OnSelect(wxString id, wxString name);
	

	wxString _GetId();
	wxString _GetName();
	
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_FILTER = 6214,
	};

};

class CMultiDialog: public wxDialog
{
	CMultiDialogPanel *m_MultiDialogPanel;

public:
	
	CMultiDialog();	
	wxString _GetId();
	wxString _GetName();
};


class CMultiDialogPanel: public wxPanel
{
	wxArrayPtrVoid m_Panels;
	CDialogPanel *m_SelectedPanel;
	void CMultiDialogPanel::OnPageChanged(wxListbookEvent &event);
public:
	
	CMultiDialogPanel(wxWindow *parent);
	CDialogPanel *GetSelectedPanel();
	wxString _GetId();
	wxString _GetName();
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_LISTBOOK = 4632,
	};

};


#endif