#include "command.h"
#include "conf.h"
#include "tools.h"
#include "db.h"

BEGIN_EVENT_TABLE(CCommandPanel, wxPanel)
	//EVT_HYPERLINK(ID_NEW,CCommandPanel::OnNew)
	//EVT_HYPERLINK(ID_PICK,CCommandPanel::OnPick)
	EVT_SLIDER(ID_DRIVE_CURRENT,OnDriveCurrent)
	EVT_SLIDER(ID_POWER_OF_LIGHT,OnPowerOfLight)
END_EVENT_TABLE()

CCommandPanel::CCommandPanel(void *db,wxWindow *parent)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	m_DB = db;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	m_Sizer = new wxStaticBoxSizer(wxVERTICAL,this,GetMsg(MSG_COMMAND));
	Sizer->Add(m_Sizer,0,wxALL|wxEXPAND,0);
	SetSizer(Sizer);
	SetGui();
}

CCommandPanel::~CCommandPanel()
{

}

void CCommandPanel::OnDriveCurrent(wxCommandEvent &event)
{
	m_ButtonOk->Enable();
}

void CCommandPanel::OnPowerOfLight(wxCommandEvent &event)
{
	m_ButtonOk->Enable();
}

void CCommandPanel::ButtonDisable()
{
	m_ButtonOk->Disable();
}

void CCommandPanel::SetGui()
{
	
	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	FlexSizer->AddGrowableCol(1,1);
	m_Sizer->Add(FlexSizer,1,wxALL|wxEXPAND,5);
	
	//charakterystyka
	//wxStaticText *LabelFlashCode = new wxStaticText(this,wxID_ANY,GetMsg(MSG_FLASH_CODE));
	//FlexSizer->Add(LabelFlashCode,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	//m_FlashCode = new wxSlider(this,wxID_ANY,0,0,1,wxDefaultPosition,wxDefaultSize,wxSL_VALUE_LABEL);
	//FlexSizer->Add(m_FlashCode,0,wxALL|wxEXPAND,2);
	
	// pr¹d podk³adu
	wxStaticText *LabelDriveCurrent = new wxStaticText(this,wxID_ANY,GetMsg(MSG_DRIVE_CURRENT));
	FlexSizer->Add(LabelDriveCurrent,0,wxALL,2);
	m_DriveCurrent = new wxSlider(this,ID_DRIVE_CURRENT,0,0,1,wxDefaultPosition,wxDefaultSize,wxSL_VALUE_LABEL);
	FlexSizer->Add(m_DriveCurrent,0,wxALL|wxEXPAND,2);
	m_DriveCurrent->SetMin(DRIVE_CURRENT_MIN);
	m_DriveCurrent->SetMax(DRIVE_CURRENT_MAX);
		
	//moc œwiat³a
	wxStaticText *LabelPowerOfLight = new wxStaticText(this,wxID_ANY,GetMsg(MSG_POWER_OF_LIGHT));
	FlexSizer->Add(LabelPowerOfLight,0,wxALL,2);
	m_PowerOfLight = new wxSlider(this,ID_POWER_OF_LIGHT,0,0,1,wxDefaultPosition,wxDefaultSize,wxSL_VALUE_LABEL);
	FlexSizer->Add(m_PowerOfLight,0,wxALL|wxEXPAND,2);
	m_PowerOfLight->SetMin(POWER_OF_LIGHT_MIN);
	m_PowerOfLight->SetMax(POWER_OF_LIGHT_MAX);
	
	//serwisowe wy³¹czenie
	m_ForcedOff = new wxCheckBox(this,wxID_ANY,GetMsg(MSG_FORCED_OFF));
	FlexSizer->Add(m_ForcedOff,0,wxALL,2);
	
	//sezonowa praca
	FlexSizer->AddSpacer(1);
	m_SeasonControl = new wxCheckBox(this,wxID_ANY,GetMsg(MSG_SEASON_CONTROL));
	FlexSizer->Add(m_SeasonControl,0,wxALL,2);

	//czu³oœæ fotorezystora
	
	m_ButtonOk = new wxButton(this,wxID_ANY,GetMsg(MSG_OK));
	m_Sizer->Add(m_ButtonOk,0,wxALL|wxALIGN_RIGHT,5);
	m_ButtonOk->Disable();
	
		
}