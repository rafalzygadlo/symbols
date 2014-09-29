#ifndef __SEAWAY_NEW_H
#define __SEAWAY_NEW_H

#include <wx/wx.h>

class CSeawayNew: public wxDialog
{
	wxTextCtrl *m_TextName;
	wxTextCtrl *m_TextInfo;
		
	bool Validate();
		
public:

	CSeawayNew();
	~CSeawayNew();
	wxString GetName();
	wxString GetInfo();
	
	void SetName(wxString v);
	void SetInfo(wxString v);


};

#endif