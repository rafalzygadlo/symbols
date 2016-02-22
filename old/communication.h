#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#include <wx/wx.h>
#include "listctrl.h"

class CCommunicationDialog: public wxDialog
{
	wxString m_Field;	
	wxString m_Order;
	CListCtrl *m_List;	
	wxString m_Id,m_Name;
	wxButton *ButtonOk;
	
	wxPanel *GetPanel(wxWindow *Parent);
	void Read();
	void Clear();
	void Select();

public:

	CCommunicationDialog(int type = -1);
	~CCommunicationDialog();
	
	void OnNew();
	void OnEdit(wxString id);
	void OnDelete(wxString id);
	void OnColumnCLick(wxString field, int order);
	void OnSelect(wxString id, wxArrayString row);
	wxString GetCommunicationId();
	wxString GetCommunicationName();
		
	
};


#endif