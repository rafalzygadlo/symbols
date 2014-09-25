#ifndef __LIGHT_H
#define __LIGHT_H

#include <wx/wx.h>
#include "listctrl.h"

class CLightDialog: public wxDialog
{
	wxString m_Field;	
	wxString m_Order;
	CListCtrl *m_List;	
	wxPanel *GetPanel(wxWindow *Parent);
	void Read();
	void Clear();
	void Select();

public:

	CLightDialog();
	~CLightDialog();
	
	void OnNew();
	void OnEdit(wxString id);
	void OnDelete(wxString id);
	void OnColumnCLick(wxString field, int order);
	
	

};

#endif