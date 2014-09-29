#ifndef __AREA_NEW_H
#define __AREA_NEW_H

#include <wx/wx.h>

class CAreaNew: public wxDialog
{
	wxTextCtrl *m_TextName;
	wxTextCtrl *m_TextInfo;
		
	bool Validate();
		
public:

	CAreaNew();
	~CAreaNew();
	wxString GetName();
	wxString GetInfo();
	
	void SetName(wxString v);
	void SetInfo(wxString v);


};

#endif