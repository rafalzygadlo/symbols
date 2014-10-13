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
	CDialogPanel *m_DialogSlave;
	wxButton *m_ButtonOk;
	wxString m_Id, m_Name;
	bool m_Picker;
	wxPanel *GetButtonPanel(wxWindow *parent);


public:
	CDialog(int control_type, bool picker = false);
	CDialog(int control_master, int control_slave, bool picker = false);
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
	wxString m_Id, m_Name, m_IdMaster;
	wxStaticText *m_TopLabel;
	wxListBox *m_ListBox;
	wxComboBox *m_ComboBox;
	int m_IdType;
	wxArrayString m_FilterArray;
	CDialogPanel *m_Slave;
			
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
	void ReadAll();
	void ReadItems();
	void ReadOthers();
	void ReadLightItems();

	void Clear();
	void Select();
	void SetTable();
	void NewItem(CNew *ptr);
	void NewLightItem();

	void OnListBox(wxCommandEvent &event);
	
	//wxComboBox *GetFilterCombo(wxWindow *Parent);
	//wxListBox *GetFilterList(wxWindow *Parent);
	wxPanel *GetPanel(wxWindow *Parent);
	wxPanel *GetItemPanel(wxWindow *Parent);
	wxPanel *GetLightPanel(wxWindow *Parent);
	wxPanel *GetLightItemPanel(wxWindow *Parent);
	wxPanel *GetPanelList(wxWindow *Parent);

public:
	
	CDialogPanel(int control_type, wxWindow *parent); // taki do pobrania tylko panela
		
	void OnNew();
	void OnEdit(wxString id);
	void OnDelete(wxString id);
	void OnColumnCLick(wxString field, int order);
	void OnSelect(wxString id, wxString name);
	void SetSlave(CDialogPanel *ptr);

	wxString _GetId();
	wxString _GetName();

	void _SetIdMaster(wxString id);
	
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