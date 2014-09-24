#ifndef __BATTERY_NEW_H
#define __BATTERY_NEW_H

#include <wx/wx.h>

class CBatteryNew: public wxDialog
{
	wxTextCtrl *m_TextName;
	wxTextCtrl *m_TextInfo;
	wxTextCtrl *m_TextType;
	wxTextCtrl *m_TextCapacity;
		
	bool Validate();
		
public:

	CBatteryNew();
	~CBatteryNew();
	wxString GetName();
	wxString GetInfo();
	wxString GetType();
	wxString GetCapacity();
	
	void SetName(wxString v);
	void SetInfo(wxString v);
	void SetType(wxString v);
	void SetCapacity(wxString v);

};

#endif