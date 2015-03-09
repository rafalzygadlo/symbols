#include "command.h"
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

CCommandPanel::CCommandPanel(void *db,wxWindow *parent)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	m_DB = db;
	m_Changed = (bool*)malloc(sizeof(bool) * COMMAND_COUNT);
	memset(m_Changed,0,sizeof(bool) * COMMAND_COUNT);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	m_Sizer = new wxStaticBoxSizer(wxVERTICAL,this,GetMsg(MSG_COMMAND));
	Sizer->Add(m_Sizer,0,wxALL|wxEXPAND,0);

	m_DriveCurrentValue = 1;
	m_PowerOfLightValue = 1;
	m_ForcedOffValue = false;
	m_SeasonControlValue = false;
	
	SetSizer(Sizer);
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
		m_Changed[COMMAND_SEASON_CONTROL] = true;
	else
		m_Changed[COMMAND_SEASON_CONTROL] = false;

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
	for(size_t i = 0; i < COMMAND_COUNT; i++)
	{
	
	}
}

wxPanel *CCommandPanel::CharacteristicPanel(wxPanel *parent)
{
		
    wxPanel *Panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);
	wxListBox *m_ListBox = new wxListBox(Panel,ID_LISTBOX,wxDefaultPosition,wxSize(200,-1));

	Sizer->Add(m_ListBox,1,wxALL|wxEXPAND,5);
			
	wxBoxSizer *ButtonSizer = new wxBoxSizer(wxVERTICAL);
	Sizer->Add(ButtonSizer,0,wxALL|wxEXPAND,5);

	wxButton *ButtonNew = new wxButton(Panel,ID_NEW,GetMsg(MSG_NEW));
	ButtonSizer->Add(ButtonNew,0,wxALL,5);
	
	wxButton *m_ButtonDelete = new wxButton(Panel,ID_DELETE,GetMsg(MSG_DELETE));
	ButtonSizer->Add(m_ButtonDelete,0,wxALL,5);
	m_ButtonDelete->Disable();
		
	return Panel;

}

void CCommandPanel::SetGui()
{

	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	FlexSizer->AddGrowableCol(1,1);
	m_Sizer->Add(FlexSizer,1,wxALL|wxEXPAND,5);


	//serwisowe wy³¹czenie
	m_ForcedOff = new wxCheckBox(this,ID_FORCED_OFF,GetMsg(MSG_FORCED_OFF));
	FlexSizer->Add(m_ForcedOff,0,wxALL,2);
	FlexSizer->AddSpacer(1);
	
	//sezonowa praca
	m_SeasonControl = new wxCheckBox(this,ID_SEASON_CONTROL,GetMsg(MSG_SEASON_CONTROL));
	FlexSizer->Add(m_SeasonControl,0,wxALL,2);
	FlexSizer->AddSpacer(1);
	
	//charakterystyka
	wxStaticText *LabelFlashCode = new wxStaticText(this,wxID_ANY,GetMsg(MSG_FLASH_CODE));
	FlexSizer->Add(LabelFlashCode,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	//m_FlashCode = new wxSlider(this,wxID_ANY,0,0,1,wxDefaultPosition,wxDefaultSize,wxSL_VALUE_LABEL);
	//FlexSizer->Add(m_FlashCode,0,wxALL|wxEXPAND,2);

	FlexSizer->Add(CharacteristicPanel(this),0,wxALL,5);

	// pr¹d podk³adu
	wxStaticText *LabelDriveCurrent = new wxStaticText(this,wxID_ANY,GetMsg(MSG_DRIVE_CURRENT));
	FlexSizer->Add(LabelDriveCurrent,0,wxALL|wxALIGN_BOTTOM,2);
	m_DriveCurrent = new wxSlider(this,ID_DRIVE_CURRENT,0,0,1,wxDefaultPosition,wxDefaultSize,wxSL_VALUE_LABEL);
	FlexSizer->Add(m_DriveCurrent,0,wxALL|wxEXPAND,2);
	m_DriveCurrent->SetMin(DRIVE_CURRENT_MIN);
	m_DriveCurrent->SetMax(DRIVE_CURRENT_MAX);

	//moc œwiat³a
	wxStaticText *LabelPowerOfLight = new wxStaticText(this,wxID_ANY,GetMsg(MSG_POWER_OF_LIGHT));
	FlexSizer->Add(LabelPowerOfLight,0,wxALL|wxALIGN_BOTTOM,2);
	m_PowerOfLight = new wxSlider(this,ID_POWER_OF_LIGHT,0,0,1,wxDefaultPosition,wxDefaultSize,wxSL_VALUE_LABEL);
	FlexSizer->Add(m_PowerOfLight,0,wxALL|wxEXPAND,2);
	m_PowerOfLight->SetMin(POWER_OF_LIGHT_MIN);
	m_PowerOfLight->SetMax(POWER_OF_LIGHT_MAX);

	

	//czu³oœæ fotorezystora
	
	m_ButtonOk = new wxButton(this,ID_BUTTON_OK,GetMsg(MSG_OK));
	m_Sizer->Add(m_ButtonOk,0,wxALL|wxALIGN_RIGHT,5);
	m_ButtonOk->Disable();
			
}