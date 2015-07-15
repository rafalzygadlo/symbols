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
	wxCheckBox *m_SeasonControl;
	wxPanel *m_SeasonControlPanel;
	wxStaticText *m_InfoText;
	wxButton *m_ButtonSend;
	wxButton *m_ButtonCancel;
	wxCheckBox *m_StandardReport;

	CSymbol *m_SelectedPtr;
	//values
	int m_DriveCurrentValue;
	int m_PowerOfLightValue;
	bool m_ForcedOffValue;
	bool m_SeasonControlValue;
	bool m_StandardReportValue;

	void OnDriveCurrent(wxCommandEvent &event);
	void OnPowerOfLight(wxCommandEvent &event);
	void OnForcedOff(wxCommandEvent &event);
	void OnSeasonControl(wxCommandEvent &event);
	void OnStandardReport(wxCommandEvent &event);
	
	void OnButtonOk(wxCommandEvent &event);
	void SetButtonState();
	wxPanel *CharacteristicPanel(wxPanel *parent);
	wxPanel *SeasonControlPanel(wxPanel *parent);
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
		ID_FROM_TIME,
		ID_STANDARD_REPORT,
	};

};


#endif