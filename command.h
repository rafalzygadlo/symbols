#ifndef __COMMAND_H
#define __COMMAND_H

#include <wx/wx.h>
#include <wx/hyperlink.h>
#include "conf.h"

class CCommandPanel: public wxPanel
{
	void *m_DB;
	bool *m_Changed;
	wxBoxSizer *m_Sizer;
	wxSlider *m_FlashCode;
	wxSlider *m_DriveCurrent;
	wxSlider *m_PowerOfLight;
	wxCheckBox *m_ForcedOff;
	wxCheckBox *m_SeasonControl;
	wxPanel *m_SeasonControlPanel;
	wxButton *m_ButtonOk;
	
	//values
	int m_DriveCurrentValue;
	int m_PowerOfLightValue;
	bool m_ForcedOffValue;
	bool m_SeasonControlValue;

	void OnDriveCurrent(wxCommandEvent &event);
	void OnPowerOfLight(wxCommandEvent &event);
	void OnForcedOff(wxCommandEvent &event);
	void  OnSeasonControl(wxCommandEvent &event);
	
	void OnButtonOk(wxCommandEvent &event);
	void SetButtonState();
	wxPanel *CharacteristicPanel(wxPanel *parent);
	wxPanel *SeasonControlPanel(wxPanel *parent);
	void SetGui();

public:

	CCommandPanel(void *db, wxWindow *parent);
	~CCommandPanel();
	void ButtonDisable();
		

	DECLARE_EVENT_TABLE();
	
	enum
	{
		ID_DRIVE_CURRENT = 4122,
		ID_POWER_OF_LIGHT,
		ID_SEASON_CONTROL,
		ID_FORCED_OFF,
		ID_BUTTON_OK,
		ID_FROM_TIME,
	};

};


#endif