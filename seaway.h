#ifndef __SEAWAY_H
#define __SEAWAY_H

#include <wx/wx.h>
#include "listctrl.h"

class CSeaway: public wxDialog
{
	wxString m_Field;	
	wxString m_Order;
	CListCtrl *m_List;	
	wxPanel *GetPanel(wxWindow *Parent);
	void Read();
	void Clear();
	void Select();

public:

	CSeaway();
	~CSeaway();
	
	void OnNew();
	void OnEdit(wxString id);
	void OnDelete(wxString id);
	void OnColumnCLick(wxString field, int order);
		
	DECLARE_EVENT_TABLE()

};

#endif