#ifndef __COMMAND_PANEL_H
#define __COMMAND_PANEL_H

#include <wx/wx.h>
#include <wx/hyperlink.h>
#include "conf.h"
#include "symbol.h"
#include "control.h"

class CCommandPanel: public wxPanel
{
	void *m_DB;
	bool *m_Changed;
	bool m_Busy;
	wxBoxSizer *m_Sizer;
	wxSlider *m_FlashCode;
	wxSlider *m_DriveCurrent;
	wxSlider *m_PowerOfLight;
	wxSlider *m_PhotoCellResistSlider;
	wxSlider *m_LightIntensitySlider;
	//wxCheckBox *m_ForcedOff;
	wxCheckBox *m_Time;
	wxCheckBox *m_Uptime;
	wxCheckBox *m_LightTime;
	wxCheckBox *m_LightIntensity;
	wxCheckBox *m_PhotoCellResistant;
	wxCheckBox *m_RipleDelay;
	wxCheckBox *m_SeasonControl;
	wxCheckBox *m_StandardReport;
	wxCheckBox *m_Reset;
	wxTextCtrl *m_TextLog;
	wxTextCtrl *m_RipleDelayEdit;

	wxRadioButton *m_LightOn;
	wxRadioButton *m_LightOff;
	wxRadioButton *m_LightAuto;
	//wxRadioButton *m_LightManual;
	
	wxPanel *m_TextLogPanel;
	CPanel *m_LightPanel;
	CPanel *m_SeasonControlPanel;
	CPanel *m_TimePanel;
	CPanel *m_UptimePanel;
	CPanel *m_LightTimePanel;
	CPanel *m_LightIntensityPanel;
	CPanel *m_PhotoCellResistantPanel;
	CPanel *m_RipleDelayPanel;
	CPanel *m_ResetPanel;
		
	wxStaticText *m_InfoText;
	wxButton *m_ButtonSend;
	wxButton *m_ButtonCancel;
	
	CSymbol *m_SelectedPtr;
	//values
	int m_DriveCurrentValue;
	int m_PowerOfLightValue;
	bool m_LightValue;
	bool m_SeasonControlValue;
	bool m_StandardReportValue;
	bool m_TimeValue;
	bool m_UptimeValue;
	bool m_AutoValue;
	bool m_LightOnValue;
	bool m_LightTimeValue;
	bool m_LightIntensityValue;
	bool m_PhotoCellResistValue;
	bool m_RipleDelayValue;
	bool m_ResetValue;

	void OnDriveCurrent(wxCommandEvent &event);
	void OnPowerOfLight(wxCommandEvent &event);
	void OnLightOff(wxCommandEvent &event);
	void OnLightOn(wxCommandEvent &event);
	void OnSeasonControl(wxCommandEvent &event);
	void OnStandardReport(wxCommandEvent &event);
	void OnTime(wxCommandEvent &event);
	void OnUptime(wxCommandEvent &event);
	void OnAuto(wxCommandEvent &event);
	void OnManual(wxCommandEvent &event);
	void OnLightTime(wxCommandEvent &event);
	void OnLightIntensity(wxCommandEvent &event);
	void OnPhotoCellResistant(wxCommandEvent &event);
	void OnRipleDelay(wxCommandEvent &event);
	void OnReset(wxCommandEvent &event);

	void OnButtonOk(wxCommandEvent &event);
	void OnButtonCancel(wxCommandEvent &event);
	void SetButtonState();

	CPanel *TimePanel(wxPanel *parent);
	CPanel *StandardReportPanel(wxPanel *parent);
	CPanel *AutoPanel(wxPanel *parent);
	CPanel *LightPanel(wxPanel *parent);
	CPanel *UptimePanel(wxPanel *parent);
	CPanel *DriveCurrentPanel(wxPanel *parent);
	CPanel *PowerOfLightPanel(wxPanel *parent);
	CPanel *CharacteristicPanel(wxPanel *parent);
	CPanel *SeasonControlPanel(wxPanel *parent);
	CPanel *LightTimePanel(wxPanel *parent);
	CPanel *LightIntensityPanel(wxPanel *parent);
	CPanel *PhotoCellResistantPanel(wxPanel *parent);
	CPanel *RipleDelayPanel(wxPanel *parent);
	CPanel *ResetPanel(wxPanel *parent);

	wxPanel *TextLogPanel(wxPanel *parent);
	wxPanel *GetPage1(wxWindow *parent);
	wxPanel *GetPage2(wxWindow *parent);

	void EnableControls(bool v);
	
	void SetTextLog();
	void SetCommand(int id);
	void SetGui();
	void SetBusy(bool v);
	void SetValues();
	void ReadCommands();

public:

	CCommandPanel(void *db,wxWindow *parent);
	~CCommandPanel();
	void ButtonDisable();
	void SetSelectedPtr(CSymbol *ptr);
	void SetNoSBMS(bool v);
	void Set();

	void SetForcedOff(bool v);
	void SetAuto(bool v);		//auto manual management
			

	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_DRIVE_CURRENT = 1000,
		ID_POWER_OF_LIGHT,
		ID_SEASON_CONTROL,
		ID_LIGHT_OFF,
		ID_LIGHT_ON,
		ID_BUTTON_OK,
		ID_BUTTON_CANCEL,
		ID_FROM_TIME,
		ID_STANDARD_REPORT,
		ID_TIME,
		ID_UPTIME,
		ID_AUTO,
		ID_MANUAL,
		ID_LIGHT_TIME,
		ID_LIGHT_INTENSITY,
		ID_PHOTOCELL_RESIST,
		ID_RIPLE_DELAY,
		ID_RIPLE_DELAY_EDIT,
		ID_PHOTOCELL_RESIST_SLIDER,
		ID_LIGHT_INTENSITY_SLIDER,
		ID_RESET
	};

};


#endif