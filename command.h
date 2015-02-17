#ifndef __COMMAND_H
#define __COMMAND_H

#include <wx/wx.h>
#include <wx/hyperlink.h>
#include "conf.h"

class CCommandPanel: public wxPanel
{
	void *m_DB;
	wxStaticBoxSizer *m_Sizer;
	wxSlider *m_FlashCode;
	wxSlider *m_DriveCurrent;
	wxSlider *m_PowerOfLight;
	wxCheckBox *m_ForcedOff;
	wxCheckBox *m_SeasonControl;
	wxButton *m_ButtonOk;

	void OnDriveCurrent(wxCommandEvent &event);
	void OnPowerOfLight(wxCommandEvent &event);

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
	};

};


#endif