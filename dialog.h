#ifndef __DIALOG_H
#define __DIALOG_H

#include <wx/wx.h>
#include "listctrl.h"
#include <wx/listbook.h>
#include <wx/fileconf.h>
#include <wx/srchctrl.h>
#include <wx/timer.h>
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
	void OnRefresh(wxCommandEvent &event);
	void OnExport(wxCommandEvent &event);
	
public:
	CDialog(void *db, int control_type, bool picker = false);
	CDialog(void *db, int control_master, int control_slave, bool picker = false);
	~CDialog();
	int _GetId();
	
	DECLARE_EVENT_TABLE();
	enum
	{
		ID_EXPORT = 1100,
				
	};

	
};

class CDialogPanel: public wxPanel
{
	void *m_DB;
	CListCtrl *m_List;	
	wxStaticText *m_TopLabel;
	wxStaticText *m_RecordCount;
	wxListBox *m_ListBox;
	wxComboBox *m_ComboBox;
	wxSearchCtrl *m_SearchText;
	CDialogPanel *m_Slave;
	CPicturePanel *m_PicturePanel;
	wxTimer *m_Ticker;

	wxString m_Name;
	int	m_IDMaster;
	int m_ID;
	wxString m_Table;
	int m_ControlType;
	int	m_ColumnWithName;
	wxString m_Field;
	wxString m_Order;
	int m_IDType;
	wxArrayString m_FilterArray;
	int m_IsSlave;
	wxWindow *m_Parent;
	wxString m_SearchTextValue;
	bool m_SearchTextChanged;

				
	void New();
	void EditArea(int id);
	void EditSymbolType(int id);
	void EditSeaway(int id);
	void EditSymbol(int id);
	void EditCharacteristic(int id);
	void EditItem(int id);
	void EditBaseStation(int id);
	void EditSBMS(int id);
			
	void EditName(int id); // wszystkie tabele z polami [type]
	void EditType(int id); // wszystkie tabele z polami [type]
	void EditPicture(int id);
	void ExportAlarmDialog();

	void Read();
	void ReadData();
	void SetStatus();
	wxString ReadItems();
	int GetItemTypeId(int id);

	void Clear();
	void Select();
	void SetTable();
	void NewItem(CNew *ptr);
	void NewSymbol(CNew *ptr);
	void NewCharacteristic(CNew *ptr);
	void NewSymbolItem();
	void NewPicture();
	void UpdatePicture(wxImage image, int id,int type);
	void SetSymbolLight(CNew *ptr,int id);
	void SetSymbolPicture(CNew *ptr,int id);
	void SetSymbolItem(CNew *ptr,int id);
	void SetCharacteristicTime(CNew *ptr,int id);

	void OnListBox(wxCommandEvent &event);
	void OnTickSearch(wxTimerEvent &event);
	void OnSearchText(wxCommandEvent &event);
	void OnSearchEnter(wxCommandEvent &event);
	void OnRefresh(wxCommandEvent &event);
	
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
	wxPanel *GetSearchPanel(wxWindow *Parent);
	wxPanel *GetSymbolFilterPanel(wxWindow *Parent);
	wxPanel *GetStatusPanel(wxWindow *Parent);
	
	void SetSearchText(const wchar_t *txt);
	const wchar_t *GetSearchText();
	bool GetSearchTextChanged();
	void SetSearchTextChanged(bool value);
	

public:
	
	CDialogPanel(void *db,int control_type, wxWindow *parent, bool slave = false); // taki do pobrania tylko panela
	~CDialogPanel();	
	void OnNew();
	void OnEdit(int id);
	void OnDelete(int id);
	void OnAddToGroup(int id);
	void OnColumnCLick(wxString field, int order);
	void OnSelect(int id);
	void OnExport();
	void SetSlave(CDialogPanel *ptr);

	int _GetId();
	wxString _GetName();

	void _SetIdMaster(int id);
	
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_FILTER = 1100,
		ID_SEARCH,
		ID_TICK_SEARCH,
		ID_REFRESH,
	};

};


#endif