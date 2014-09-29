#ifndef __COMMUNICATION_NEW_H
#define __COMMUNICATION_NEW_H

#include <wx/wx.h>

class CCommunicationNew: public wxDialog
{
	wxTextCtrl *m_TextName;
	wxTextCtrl *m_TextInfo;
		
	bool Validate();
		
public:

	CCommunicationNew();
	~CCommunicationNew();
	wxString GetName();
	wxString GetInfo();
	
	void SetName(wxString v);
	void SetInfo(wxString v);


};

#endif