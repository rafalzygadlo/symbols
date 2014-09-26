#ifndef __BATTERY_H
#define __BATTERY_H

#include <wx/wx.h>
#include "listctrl.h"
#include <wx/wrapsizer.h>

class CBattery;
class CBatteryDialog: public wxDialog
{
	wxString m_Field;
	wxString m_Order;
	wxString m_Id,m_Name;
	CListCtrl *m_List;
	wxButton *ButtonOk;

	wxPanel *GetPanel(wxWindow *Parent);
	void Read();
	void Clear();
	void Select();

public:

	CBatteryDialog(int type = -1);
	~CBatteryDialog();
	
	void OnNew();
	void OnEdit(wxString id);
	void OnDelete(wxString id);
	void OnSelect(wxArrayString row);
	void OnDeSelect();
	void OnColumnCLick(wxString field, int order);
	wxString GetBatteryId();
	wxString GetBatteryName();


};

class CBatteryPanel: public wxPanel
{
	wxWindow *m_Parent, *m_Top;
	wxBoxSizer *m_Sizer;
	wxPanel *m_Panel;
	wxBoxSizer *m_PanelSizer;
	wxArrayPtrVoid m_Panels;
	
	void New(wxString id, wxString name);
			
public:

	CBatteryPanel(wxWindow *parent, wxWindow *top);
	~CBatteryPanel();
	void OnNew(wxCommandEvent &event);
	void OnDelete(CBattery *ptr);
	void OnEdit(CBattery *ptr);
	wxArrayPtrVoid GetPanels();

	
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_NEW = 8124,
	};

};

class CBattery: public wxPanel
{
	wxWindow *m_Parent;
	CBatteryPanel *m_BatteryPanel;
	wxBoxSizer *m_Sizer;
	wxPanel *m_Panel;
	wxStaticText *m_Name;
	
	void OnContextMenu(wxContextMenuEvent &event);
	void OnDelete(wxCommandEvent &event);
	void OnEdit(wxCommandEvent &event);

public:

	CBattery(wxWindow *parent, CBatteryPanel *panel);
	~CBattery();
	void SetBatteryId(wxString v);
	void SetBatteryName(wxString v);

	
	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_DELETE = 8124,
		ID_EDIT,
	};

};


#endif