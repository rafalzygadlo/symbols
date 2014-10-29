#ifndef __DIALOG_H
#define __DIALOG_H

#include <wx/wx.h>
#include "listctrl.h"
#include <wx/listbook.h>
#include <wx/fileconf.h>
#include "new.h"

class CListCtrl;
class CDialogPanel;
class CMultiDialogPanel;
class CNew;
class CDialog : public wxDialog
{
	CDialogPanel *m_DialogPanel;
	CDialogPanel *m_DialogSlave;
	wxButton *m_ButtonOk;
	int m_ID;
	int m_ControlType;
	bool m_Picker;
	wxPanel *GetButtonPanel(wxWindow *parent);
	void ReadConfig();
	void WriteConfig();


public:
	CDialog(int control_type, bool picker = false);
	CDialog(int control_master, int control_slave, bool picker = false);
	~CDialog();
	int _GetId();
	//wxString _GetName();
	
};

class CDialogPanel: public wxPanel
{
	wxString m_Field;	
	wxString m_Order;
	CListCtrl *m_List;	
	int m_ControlType,m_ColumnWithName;
	wxString m_Table;
	int m_ID;
	wxString m_Name;
	int	m_IDMaster;
	wxStaticText *m_TopLabel;
	wxListBox *m_ListBox;
	wxComboBox *m_ComboBox;
	int m_IDType;
	wxArrayString m_FilterArray;
	CDialogPanel *m_Slave;
	CPicturePanel *m_PicturePanel;
	int m_IsSlave;
	wxWindow *m_Parent;
				
	void New();
	void EditArea(int id);
	void EditSymbolType(int id);
	void EditSeaway(int id);
	void EditSymbol(int id);
	void EditItem(int id);
	int GetItemTypeId(int id);
			
	void EditName(int id); // wszystkie tabele z polami [type]
	void EditType(int id); // wszystkie tabele z polami [type]
	void EditPicture(int id);
	
	void Read();
	void ReadAll();
	void ReadItems();
	void ReadOthers();
	void ReadSymbolItems();
	void ReadPicture();

	void Clear();
	void Select();
	void SetTable();
	void NewItem(CNew *ptr);
	void NewSymbol(CNew *ptr);
	void NewSymbolItem();
	void NewPicture();
	void UpdatePicture(wxImage image, int id);
	void SetSymbolLight(CNew *ptr,int id);
	void SetSymbolPicture(CNew *ptr,int id);
	void SetSymbolItem(CNew *ptr,int id);

	void OnListBox(wxCommandEvent &event);

	void ReadConfig();
	void WriteConfig();
	
	//wxComboBox *GetFilterCombo(wxWindow *Parent);
	//wxListBox *GetFilterList(wxWindow *Parent);
	wxPanel *GetPanel(wxWindow *Parent);
	wxPanel *GetItemPanel(wxWindow *Parent);
	wxPanel *GetSymbolPanel(wxWindow *Parent);
	wxPanel *GetSymbolItemPanel(wxWindow *Parent);
	wxPanel *GetPanelList(wxWindow *Parent);
	wxPanel *GetPicturePanel(wxWindow *Parent);

public:
	
	CDialogPanel(int control_type, wxWindow *parent, bool slave = false); // taki do pobrania tylko panela
	~CDialogPanel();	
	void OnNew();
	void OnEdit(int id);
	void OnDelete(int id);
	void OnColumnCLick(wxString field, int order);
	void OnSelect(int id, wxString name);
	void SetSlave(CDialogPanel *ptr);

	int _GetId();
	wxString _GetName();

	void _SetIdMaster(int id);
	
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_FILTER = 6214,
	};

};


#endif