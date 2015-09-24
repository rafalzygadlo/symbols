#ifndef __COMMAND_PANEL_H
#define __COMMAND_PANEL_H

#include <wx/wx.h>
#include <wx/hyperlink.h>
#include "conf.h"
#include "symbol.h"

class CCommandPanel: public wxPanel
{
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
	wxTextCtrl *m_TextLog;
	wxTextCtrl *m_RipleDelayEdit;

	wxButton *m_LightOn;
	wxButton *m_LightOff;
	wxRadioButton *m_LightAuto;
	wxRadioButton *m_LightManual;
	
	wxPanel *m_AutoPanel;
	wxPanel *m_LightPanel;
	//wxPanel *m_DriveCurrentPanel;
	//wxPanel *m_PowerOfLightPanel;
	wxPanel *m_SeasonControlPanel;
	wxPanel *m_TimePanel;
	wxPanel *m_UptimePanel;
	wxPanel *m_TextLogPanel;
	wxPanel *m_LightTimePanel;
	wxPanel *m_LightIntensityPanel;
	wxPanel *m_PhotoCellResistantPanel;
	wxPanel *m_RipleDelayPanel;
	
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

	
	void OnButtonOk(wxCommandEvent &event);
	void OnButtonCancel(wxCommandEvent &event);
	void SetButtonState();

	wxPanel *StandardReportPanel(wxPanel *parent);
	wxPanel *AutoPanel(wxPanel *parent);
	wxPanel *LightPanel(wxPanel *parent);
	wxPanel *GetTimePanel(wxPanel *parent);
	wxPanel *GetUptimePanel(wxPanel *parent);
	wxPanel *DriveCurrentPanel(wxPanel *parent);
	wxPanel *PowerOfLightPanel(wxPanel *parent);
	wxPanel *CharacteristicPanel(wxPanel *parent);
	wxPanel *SeasonControlPanel(wxPanel *parent);
	wxPanel *GetCommandPanel(wxPanel *parent);
	wxPanel *GetAutoPanel(wxPanel *parent);
	wxPanel *TextLogPanel(wxPanel *parent);
	wxPanel *SetLightTimePanel(wxPanel *parent);
	wxPanel *SetLightIntensityPanel(wxPanel *parent);
	wxPanel *SetPhotoCellResistantPanel(wxPanel *parent);
	wxPanel *SetRipleDelayPanel(wxPanel *parent);

	void EnableControls(bool v);
	
	void SetTextLog();
	void SetCommand(int id);
	void SetGui();
	void SetBusy(bool v);
	void SetValues();
	void ReadCommands();

public:

	CCommandPanel(wxWindow *parent);
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
		ID_RIPLE_DELAY_UNIT,
		ID_LIGHT_INTENSITY_SLIDER
	};

};


#endif