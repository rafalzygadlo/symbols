#ifndef __ACTIONDIALOG_H
#define __ACTIONDIALOG_H

#include "conf.h"
#include "sbms.h"

class CSBMS;
class CSBMSActionDialog : public wxDialog
{
	CButton *m_ButtonGraph;
	CButton *m_ButtonOn;
	CButton *m_ButtonOff;
	CButton *m_ButtonAuto;
	CButton *m_ButtonTime;
	CButton *m_ButtonUpTime;
	CButton *m_ButtonReset;
	wxStaticText *m_Title;
		
	CSBMS *m_Symbol;
	
	wxPanel *GetTopPanel(wxWindow *parent);
	wxPanel *GetActionPanel(wxWindow *parent);
	wxPanel *GetButtonPanel(wxWindow *parent);
	
	void SetTitle(wxString str);
	void OnGraph(wxCommandEvent &event);
	void OnLightOn(wxCommandEvent &event);
	void OnLightOff(wxCommandEvent &event);
	void OnAutoManagement(wxCommandEvent &event);
	void OnReset(wxCommandEvent &event);
	void OnGetTime(wxCommandEvent &event);
	void OnGetUptime(wxCommandEvent &event);

public:

	CSBMSActionDialog(CSBMS *ptr);
	~CSBMSActionDialog();
	void SetSBMS(CSBMS *ptr);

	enum
	{
		ID_GRAPH = 1800,
		ID_MANAGEMENT,
		ID_LIGHT_ON,
		ID_LIGHT_OFF,
		ID_AUTO,
		ID_RESET,
		ID_TIME,
		ID_UPTIME,

	};
	
	DECLARE_EVENT_TABLE();
};

#endif