#ifndef __NEW_H
#define __NEW_H

#include <wx/wx.h>

class CNew: public wxDialog
{
	wxTextValidator m_TextValidator;
	wxTextCtrl *m_TextName;
	wxTextCtrl *m_TextInfo;
	wxTextCtrl *m_TextType;
	wxTextCtrl *m_TextCapacity;
	wxTextCtrl *m_TextFlash;
	wxString m_Exclude;

	void GetPanel(int type);

	wxPanel *AreaPanel();
	wxPanel *BatteryPanel();
	wxPanel *CommunicationPanel();
	wxPanel *SeawayPanel();
	wxPanel *LightPanel();
	
	bool Validate();
		
public:

	CNew(int type);
	~CNew();
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