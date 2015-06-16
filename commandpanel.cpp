#include <wx/dateevt.h>
#include <wx/timectrl.h>
#include <wx/datectrl.h>
#include "commandpanel.h"
#include "conf.h"
#include "tools.h"
#include "db.h"

BEGIN_EVENT_TABLE(CCommandPanel, wxPanel)
	EVT_SLIDER(ID_DRIVE_CURRENT,OnDriveCurrent)
	EVT_SLIDER(ID_POWER_OF_LIGHT,OnPowerOfLight)
	EVT_CHECKBOX(ID_FORCED_OFF,OnForcedOff)
	EVT_CHECKBOX(ID_SEASON_CONTROL,OnSeasonControl)
	
	EVT_BUTTON(ID_BUTTON_OK,OnButtonOk)
END_EVENT_TABLE()

CCommandPanel::CCommandPanel(wxWindow *parent)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	m_Changed = (bool*)malloc(sizeof(bool) * COMMAND_COUNT);
	memset(m_Changed,0,sizeof(bool) * COMMAND_COUNT);
	m_Sizer = new wxBoxSizer(wxVERTICAL);
	//m_Sizer = new wxStaticBoxSizer(wxVERTICAL,this,GetMsg(MSG_COMMAND));
	//Sizer->Add(m_Sizer,0,wxALL|wxEXPAND,0);

	m_DriveCurrentValue = 1;
	m_PowerOfLightValue = 1;
	m_ForcedOffValue = false;
	m_SeasonControlValue = false;
		
	SetSizer(m_Sizer);
	SetGui();
	
}

CCommandPanel::~CCommandPanel()
{
	free(m_Changed);
}

void CCommandPanel::OnDriveCurrent(wxCommandEvent &event)
{
	if(m_DriveCurrentValue != m_DriveCurrent->GetValue())
		m_Changed[COMMAND_DRIVE_CURRENT] = true;
	else
		m_Changed[COMMAND_DRIVE_CURRENT] = false;
	
	SetButtonState();
}

void CCommandPanel::OnPowerOfLight(wxCommandEvent &event)
{
	if(m_PowerOfLightValue != m_PowerOfLight->GetValue())
		m_Changed[COMMAND_POWER_OF_LIGHT] = true;
	else
		m_Changed[COMMAND_POWER_OF_LIGHT] = false;
		
	SetButtonState();
}

void CCommandPanel::OnForcedOff(wxCommandEvent &event)
{

	if(m_ForcedOffValue != m_ForcedOff->GetValue())
		m_Changed[COMMAND_FORCED_OFF] = true;
	else
		m_Changed[COMMAND_FORCED_OFF] = false;
	
	SetButtonState();
}

void CCommandPanel::OnSeasonControl(wxCommandEvent &event)
{
	if(m_SeasonControlValue != m_SeasonControl->GetValue())
	{
		m_Changed[COMMAND_SEASON_CONTROL] = true;
		m_SeasonControlPanel->Enable();
	}else{
		m_Changed[COMMAND_SEASON_CONTROL] = false;
		m_SeasonControlPanel->Disable();
	}
		
	SetButtonState();
	
}

void CCommandPanel::SetButtonState()
{
	m_ButtonOk->Disable();
	for(size_t i = 0; i < COMMAND_COUNT; i++)
	{		
		if(m_Changed[i])
			m_ButtonOk->Enable();
	}

}

void CCommandPanel::ButtonDisable()
{
	m_ButtonOk->Disable();
}

void CCommandPanel::OnButtonOk(wxCommandEvent &event)
{
	Disable();
	SetValues();
	for(size_t i = 0; i < COMMAND_COUNT; i++)
	{
		if(m_Changed[i])
			SetCommand(i);
	}
}

void CCommandPanel::SetValues()
{
	m_DriveCurrentValue = m_DriveCurrent->GetValue();
	m_PowerOfLightValue = m_PowerOfLight->GetValue();
	m_SeasonControlValue = m_SeasonControl->GetValue();
	m_ForcedOffValue = m_ForcedOff->GetValue();

}

void CCommandPanel::SetCommand(int id)
{
	wxString sql;
	int SBMSID = m_SelectedPtr->GetSBMSID();
	int id_base_station = m_SelectedPtr->GetBaseStationId();
	switch(id)
	{
		//case COMMAND_DRIVE_CURRENT:	SetDriveCurrent(m_SBMSID,m_DriveCurrentValue);
		case COMMAND_FORCED_OFF:	SetCommandForcedOff(SBMSID,id_base_station,m_ForcedOffValue); break;
		//case COMMAND_FLASH_CODE:	SetFlashCode(m_IdSBMS,m_FlashCode

	}
	
}

void CCommandPanel::SetSelectedPtr(CSymbol *ptr)
{
	m_SelectedPtr = ptr;
}

void CCommandPanel::Set()
{
	if(m_SelectedPtr->GetSBMSID() == 0)
	{
		Disable();
		SetNoSBMS(true);
		return;
	}

	SetNoSBMS(false);
	
	if(m_SelectedPtr->GetBusy())
	{
		Disable();
		SetBusy(true);

	}else{

		Enable();
		SetBusy(false);
	}
}

void CCommandPanel::SetNoSBMS(bool v)
{
	if(v)
		m_InfoText->SetLabel(GetMsg(MSG_NO_SBMS));
	else
		m_InfoText->SetLabel(wxEmptyString);
	
	Refresh(false);
}


void CCommandPanel::SetBusy(bool v)
{
	if(v)
		m_InfoText->SetLabel(GetMsg(MSG_BUSY));
	else
		m_InfoText->SetLabel(GetMsg(MSG_READY));
	
	Refresh(false);
}


wxPanel *CCommandPanel::SeasonControlPanel(wxPanel *parent)
{
		
    wxPanel *Panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	Panel->SetBackgroundColour(*wxRED);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(Sizer);

	wxBoxSizer *Sizer1 = new wxBoxSizer(wxHORIZONTAL);
	Sizer->Add(Sizer1);

	wxDatePickerCtrl *m_FromDate = new wxDatePickerCtrl(Panel,wxID_ANY);
	Sizer1->Add(m_FromDate,0,wxALL,5);
	wxTimePickerCtrl *m_FromTime = new wxTimePickerCtrl(Panel,ID_FROM_TIME);
	Sizer1->Add(m_FromTime,0,wxALL,5);
	
	wxBoxSizer *Sizer2 = new wxBoxSizer(wxHORIZONTAL);
	Sizer->Add(Sizer2);

	wxDatePickerCtrl *m_ToDate = new wxDatePickerCtrl(Panel,wxID_ANY);
	Sizer2->Add(m_ToDate,0,wxALL,5);
	wxTimePickerCtrl *m_ToTime = new wxTimePickerCtrl(Panel,ID_FROM_TIME);
	Sizer2->Add(m_ToTime,0,wxALL,5);

	Panel->Disable();	
	return Panel;

}


wxPanel *CCommandPanel::CharacteristicPanel(wxPanel *parent)
{
		
    wxPanel *Panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	Panel->SetBackgroundColour(*wxRED);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);
	
	wxTextCtrl *aa = new wxTextCtrl(Panel,wxID_ANY);	
	Sizer->Add(aa,0,wxALL|wxEXPAND,5);	
	
	//m_ButtonDelete->Disable();
		
	return Panel;

}

void CCommandPanel::SetGui()
{
	wxPanel *Panel = new wxPanel(this);
	m_Sizer->Add(Panel,0,wxALL|wxEXPAND,20);

	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(PanelSizer);

	m_InfoText = new wxStaticText(Panel,wxID_ANY,wxEmptyString);
	PanelSizer->Add(m_InfoText,0,wxALL,5);

	//serwisowe wy��czenie
	m_ForcedOff = new wxCheckBox(Panel,ID_FORCED_OFF,GetMsg(MSG_FORCED_OFF));
	PanelSizer->Add(m_ForcedOff,0,wxALL,5);
		
	//sezonowa praca
	m_SeasonControl = new wxCheckBox(Panel,ID_SEASON_CONTROL,GetMsg(MSG_SEASON_CONTROL));
	PanelSizer->Add(m_SeasonControl,0,wxALL,5);
	m_SeasonControlPanel = SeasonControlPanel(Panel);
	PanelSizer->Add(m_SeasonControlPanel,0,wxALL,0);
		
	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	FlexSizer->AddGrowableCol(1,1);
	PanelSizer->Add(FlexSizer,1,wxALL|wxEXPAND,0);
		
	//charakterystyka
	wxStaticText *LabelFlashCode = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_FLASH_CODE));
	FlexSizer->Add(LabelFlashCode,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	FlexSizer->Add(CharacteristicPanel(Panel),0,wxALL|wxEXPAND,5);
		
	// pr�d podk�adu
	wxStaticText *LabelDriveCurrent = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_DRIVE_CURRENT));
	FlexSizer->Add(LabelDriveCurrent,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_DriveCurrent = new wxSlider(Panel,ID_DRIVE_CURRENT,0,0,1,wxDefaultPosition,wxDefaultSize,wxSL_VALUE_LABEL);
	FlexSizer->Add(m_DriveCurrent,0,wxALL|wxEXPAND,5);
	m_DriveCurrent->SetMin(DRIVE_CURRENT_MIN);
	m_DriveCurrent->SetMax(DRIVE_CURRENT_MAX);

	//moc �wiat�a
	wxStaticText *LabelPowerOfLight = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_POWER_OF_LIGHT));
	FlexSizer->Add(LabelPowerOfLight,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_PowerOfLight = new wxSlider(Panel,ID_POWER_OF_LIGHT,0,0,1,wxDefaultPosition,wxSize(150,-1),wxSL_VALUE_LABEL);
	FlexSizer->Add(m_PowerOfLight,0,wxALL|wxEXPAND,5);
	m_PowerOfLight->SetMin(POWER_OF_LIGHT_MIN);
	m_PowerOfLight->SetMax(POWER_OF_LIGHT_MAX);

	//czu�o�� fotorezystora
	m_ButtonOk = new wxButton(Panel,ID_BUTTON_OK,GetMsg(MSG_OK));
	PanelSizer->Add(m_ButtonOk,0,wxALL|wxALIGN_RIGHT,5);
	m_ButtonOk->Disable();
	
}

//VALUES. . . . . . . . . . .  . . . . . .
void CCommandPanel::SetForcedOff(bool v)
{
	m_ForcedOff->SetValue(v);
	m_ForcedOffValue = v;

}
