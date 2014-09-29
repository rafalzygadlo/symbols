#ifndef __LIGHT_NEW_H
#define __LIGHT_NEW_H

#include <wx/wx.h>

class CLightNew: public wxDialog
{
	wxTextCtrl *m_TextName;
	wxTextCtrl *m_TextFlash; //b³yskacz
	wxTextCtrl *m_TextInfo;
		
	bool Validate();
		
public:

	CLightNew();
	~CLightNew();
	wxString GetName();
	wxString GetInfo();
	
	void SetName(wxString v);
	void SetInfo(wxString v);


};

#endif