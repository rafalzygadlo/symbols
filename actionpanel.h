#ifndef __ACTIONPANEL_H
#define __ACTIONPANEL_H

#include "conf.h"
#include "symbol.h"
#include "control.h"

class CActionPanel : public wxPanel
{
	CButton *m_ButtonGraph;
	CButton *m_ButtonOn;
	CButton *m_ButtonOff;
	CButton *m_ButtonAuto;
	CButton *m_ButtonTime;
	CButton *m_ButtonUpTime;
	CButton *m_ButtonReset;
		
	CSymbol *m_Symbol;
	void SetGui();
	void EnableControls(bool v);
	void OnGraph(wxCommandEvent &event);
	void OnLightOn(wxCommandEvent &event);
	void OnLightOff(wxCommandEvent &event);
	void OnAutoManagement(wxCommandEvent &event);
	void OnReset(wxCommandEvent &event);
	void OnGetTime(wxCommandEvent &event);
	void OnGetUptime(wxCommandEvent &event);
	

public:

	CActionPanel(wxWindow *parent);
	void SetSymbol(CSymbol *ptr);
	

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