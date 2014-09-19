#ifndef __AREA_H
#define __AREA_H

#include <wx/wx.h>
#include "listctrl.h"

class CArea: public wxDialog
{
	wxString m_Field;	
	wxString m_Order;
	CListCtrl *m_List;	
	wxPanel *GetPanel(wxWindow *Parent);
	void Read();
	void Clear();
	void Select();

public:

	CArea();
	~CArea();
	
	void OnNew();
	void OnEdit(wxString id);
	void OnDelete(wxString id);
	void OnColumnCLick(wxString field, int order);
		
	DECLARE_EVENT_TABLE()

};

#endif