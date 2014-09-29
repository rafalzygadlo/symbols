#ifndef __DIALOG_H
#define __DIALOG_H

#include <wx/wx.h>
#include "listctrl.h"

class CListCtrl;
class CDialog: public wxDialog
{
	wxString m_Field;	
	wxString m_Order;
	CListCtrl *m_List;	
	wxButton *ButtonOk;
	int m_ControlType;
	wxString m_Table;

	wxPanel *GetPanel(wxWindow *Parent);
	
	void ControlArea();
	void ControlBattery();
	void ControlSeaway();
	void ControlCommunication();
	void ControlLight();

	void New();

	void EditArea(wxString id);
	void EditBattery(wxString id);
	void EditCommunication(wxString id);
	void EditSeaway(wxString id);
	void EditLight(wxString id);
	
	void Read();
	void Clear();
	void Select();
	void SetTable();

public:

	CDialog(int control_type, bool picker = false);
	~CDialog();
	
	void OnNew();
	void OnEdit(wxString id);
	void OnDelete(wxString id);
	void OnColumnCLick(wxString field, int order);
	void OnSelect(wxString id,wxArrayString row);

};

#endif