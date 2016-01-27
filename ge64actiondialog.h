#ifndef _GE64ACTIONDIALOG_H
#define _GE64ACTIONDIALOG_H

#include "conf.h"
#include "ge64.h"

class CGE64;
class CGE64ActionDialog : public wxDialog
{
	CButton *m_ButtonOn;
	CButton *m_ButtonOff;
	wxStaticText *m_Title;
		
	CGE64 *m_Driver;
	
	wxPanel *GetTopPanel(wxWindow *parent);
	wxPanel *GetActionPanel(wxWindow *parent);
	wxPanel *GetButtonPanel(wxWindow *parent);
	
	void SetTitle(wxString str);
	void EnableControls(bool v);
	void OnLightOn(wxCommandEvent &event);
	void OnLightOff(wxCommandEvent &event);
	
public:

	CGE64ActionDialog(CGE64 *ptr);
	~CGE64ActionDialog();
	void SetDriver(CGE64 *ptr);

	enum
	{
		ID_LIGHT_ON = 1900,
		ID_LIGHT_OFF,
		
	};
	
	DECLARE_EVENT_TABLE();
};

#endif