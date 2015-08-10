#ifndef __COMMAND_PANEL_H
#define __COMMAND_PANEL_H

#include <wx/wx.h>
#include <wx/hyperlink.h>
#include "conf.h"
#include "symbol.h"

class CCommandPanel: public wxPanel
{
	bool *m_Changed;
	wxBoxSizer *m_Sizer;
	wxSlider *m_FlashCode;
	wxSlider *m_DriveCurrent;
	wxSlider *m_PowerOfLight;
	wxCheckBox *m_ForcedOff;
	wxCheckBox *m_Time;
	wxCheckBox *m_Uptime;
	wxCheckBox *m_SeasonControl;
	wxCheckBox *m_StandardReport;

	wxPanel *m_StandardReportPanel;
	wxPanel *m_ForcedOffPanel;
	wxPanel *m_DriveCurrentPanel;
	wxPanel *m_PowerOfLightPanel;
	wxPanel *m_SeasonControlPanel;
	wxPanel *m_TimePanel;
	wxPanel *m_UptimePanel;
	
	wxStaticText *m_InfoText;
	wxButton *m_ButtonSend;
	wxButton *m_ButtonCancel;
	
	CSymbol *m_SelectedPtr;
	//values
	int m_DriveCurrentValue;
	int m_PowerOfLightValue;
	bool m_ForcedOffValue;
	bool m_SeasonControlValue;
	bool m_StandardReportValue;
	bool m_TimeValue;
	bool m_UptimeValue;

	void OnDriveCurrent(wxCommandEvent &event);
	void OnPowerOfLight(wxCommandEvent &event);
	void OnForcedOff(wxCommandEvent &event);
	void OnSeasonControl(wxCommandEvent &event);
	void OnStandardReport(wxCommandEvent &event);
	void OnTime(wxCommandEvent &event);
	void OnUptime(wxCommandEvent &event);
	void OnAuto(wxCommandEvent &event);
	void OnHuman(wxCommandEvent &event);

	
	void OnButtonOk(wxCommandEvent &event);
	void OnButtonCancel(wxCommandEvent &event);
	void SetButtonState();
	wxPanel *StandardReportPanel(wxPanel *parent);
	wxPanel *ForcedOffPanel(wxPanel *parent);
	wxPanel *GetTimePanel(wxPanel *parent);
	wxPanel *GetUptimePanel(wxPanel *parent);
	wxPanel *DriveCurrentPanel(wxPanel *parent);
	wxPanel *PowerOfLightPanel(wxPanel *parent);
	wxPanel *CharacteristicPanel(wxPanel *parent);
	wxPanel *SeasonControlPanel(wxPanel *parent);
	wxPanel *GetCommandPanel(wxPanel *parent);
	wxPanel *GetAutoPanel(wxPanel *parent);
	void EnableControls(bool v);
	
	void SetCommand(int id);
	void SetGui();
	void SetBusy(bool v);
	void SetValues();

public:

	CCommandPanel(wxWindow *parent);
	~CCommandPanel();
	void ButtonDisable();
	void SetSelectedPtr(CSymbol *ptr);
	void SetNoSBMS(bool v);
	void Set();

	void SetForcedOff(bool v);
			

	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_DRIVE_CURRENT = 1000,
		ID_POWER_OF_LIGHT,
		ID_SEASON_CONTROL,
		ID_FORCED_OFF,
		ID_BUTTON_OK,
		ID_BUTTON_CANCEL,
		ID_FROM_TIME,
		ID_STANDARD_REPORT,
		ID_TIME,
		ID_UPTIME,
		ID_AUTO,
		ID_HUMAN,
	};

};


#endif