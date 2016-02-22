#ifndef __ACTIONDIALOG
#define __ACTIONDIALOG

#include "conf.h"
#include "sbms.h"
#include "control.h"

class CSBMS;
class CSBMSActionDialog : public wxDialog
{
	void *m_DB;
	CButton *m_ButtonGraph;
	//CButton *m_ClearAlarm;
	//CButton *m_ClearCommand;
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

	CSBMSActionDialog(void *db,CSBMS *ptr);
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
		ID_CLEAR_COMMAND,
		ID_CLEAR_ALARM,

	};
	
	DECLARE_EVENT_TABLE();
};

#endif