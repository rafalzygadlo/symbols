#ifndef __BATTERY_H
#define __BATTERY_H

#include <wx/wx.h>
#include "listctrl.h"
#include <wx/wrapsizer.h>

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
	void OnSelect(wxString id,wxArrayString row);
	void OnDeSelect();
	void OnColumnCLick(wxString field, int order);
	wxString GetBatteryId();
	wxString GetBatteryName();


};

#endif