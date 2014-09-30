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
	wxButton *m_ButtonOk;
	int m_ControlType,m_ColumnWithName;
	wxString m_Table;
	wxString m_Id, m_Name;
	bool m_Picker;


	wxPanel *GetPanel(wxWindow *Parent);
	
	void ControlArea();
	void ControlBattery();
	void ControlSeaway();
	void ControlCommunication();
	void ControlLight();
	void ControlBulb();
	void ControlFlash();

	void New();

	void EditArea(wxString id);
	void EditBattery(wxString id);
	void EditCommunication(wxString id);
	void EditSeaway(wxString id);
	void EditLight(wxString id);
	void EditBulb(wxString id);
	
	void Read();
	void Clear();
	void Select();
	void SetTable();

public:
	
	CDialog(int control_type); // taki do pobrania tylko panela
	CDialog(int control_type, bool picker = false);
	~CDialog();
	
	void OnNew();
	void OnEdit(wxString id);
	void OnDelete(wxString id);
	void OnColumnCLick(wxString field, int order);
	void OnSelect(wxString id, wxString name);

	wxString _GetId();
	wxString _GetName();

};

#endif