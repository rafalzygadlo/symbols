#include <wx/dateevt.h>
#include <wx/timectrl.h>
#include <wx/datectrl.h>
#include <wx/statline.h>
#include "commandpanel.h"
#include "conf.h"
#include "tools.h"
#include "db.h"

BEGIN_EVENT_TABLE(CCommandPanel, wxPanel)
	EVT_SLIDER(ID_DRIVE_CURRENT,OnDriveCurrent)
	EVT_SLIDER(ID_POWER_OF_LIGHT,OnPowerOfLight)
	EVT_CHECKBOX(ID_SEASON_CONTROL,OnSeasonControl)
	EVT_CHECKBOX(ID_STANDARD_REPORT,OnStandardReport)
	EVT_CHECKBOX(ID_TIME,OnTime)
	EVT_CHECKBOX(ID_UPTIME,OnUptime)
	EVT_BUTTON(ID_BUTTON_OK,OnButtonOk)
	EVT_BUTTON(ID_BUTTON_CANCEL,OnButtonCancel)	
	EVT_RADIOBUTTON(ID_AUTO,OnAuto)
	EVT_RADIOBUTTON(ID_MANUAL,OnManual)
	EVT_BUTTON(ID_LIGHT_ON,OnLightOn)
	EVT_BUTTON(ID_LIGHT_OFF,OnLightOff)
END_EVENT_TABLE()

CCommandPanel::CCommandPanel(wxWindow *parent)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	m_Changed = (bool*)malloc(sizeof(bool) * COMMAND_COUNT);
	memset(m_Changed,0,sizeof(bool) * COMMAND_COUNT);
	//m_Sizer = new wxBoxSizer(wxVERTICAL);
	//m_Sizer = new wxStaticBoxSizer(wxVERTICAL,this,GetMsg(MSG_COMMAND));
	//Sizer->Add(m_Sizer,0,wxALL|wxEXPAND,0);

	m_DriveCurrentValue = 1;
	m_PowerOfLightValue = 1;
	m_LightValue = false;
	m_SeasonControlValue = false;
	m_StandardReportValue = false;
	m_UptimeValue = false;
	m_TimeValue = false;
	m_Busy = false;	
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
	SetTextLog();
	
}

void CCommandPanel::OnPowerOfLight(wxCommandEvent &event)
{
	if(m_PowerOfLightValue != m_PowerOfLight->GetValue())
		m_Changed[COMMAND_POWER_OF_LIGHT] = true;
	else
		m_Changed[COMMAND_POWER_OF_LIGHT] = false;
		
	SetButtonState();
	SetTextLog();
	
}

void CCommandPanel::OnStandardReport(wxCommandEvent &event)
{

	if(m_StandardReportValue != m_StandardReport->GetValue())
		m_Changed[COMMAND_STANDARD_REPORT] = true;
	else
		m_Changed[COMMAND_STANDARD_REPORT] = false;
	
	SetButtonState();
	SetTextLog();
	
}

void CCommandPanel::OnTime(wxCommandEvent &event)
{
	if(m_TimeValue != m_Time->GetValue())
		m_Changed[COMMAND_GET_TIME] = true;
	else
		m_Changed[COMMAND_GET_TIME] = false;
	
	SetButtonState();
	SetTextLog();
	
}

void CCommandPanel::OnUptime(wxCommandEvent &event)
{

	if(m_UptimeValue != m_Uptime->GetValue())
		m_Changed[COMMAND_GET_UPTIME] = true;
	else
		m_Changed[COMMAND_GET_UPTIME] = false;
	
	SetButtonState();
	SetTextLog();
	
}


void CCommandPanel::OnLightOff(wxCommandEvent &event)
{
	m_LightOnValue = false;
	m_LightOn->Enable(true);
	m_LightOff->Enable(false);

	if(m_LightValue)
	{
		m_Changed[COMMAND_LIGHT_ON] = false;
		m_Changed[COMMAND_LIGHT_OFF] = true;
	}else{
		m_Changed[COMMAND_LIGHT_ON] = false;
		m_Changed[COMMAND_LIGHT_OFF] = false;
	}

	//m_LightValue = false;
	SetButtonState();
	SetTextLog();
	
	
}

void CCommandPanel::OnLightOn(wxCommandEvent &event)
{
	
	m_LightOnValue = true;
	m_LightOn->Enable(false);
	m_LightOff->Enable(true);
	
	if(m_LightValue)
	{
		m_Changed[COMMAND_LIGHT_ON] = false;
		m_Changed[COMMAND_LIGHT_OFF] = false;
	}else{
	
		m_Changed[COMMAND_LIGHT_ON] = true;
		m_Changed[COMMAND_LIGHT_OFF] = false;
	}

	//m_LightValue = true;
	SetButtonState();
	SetTextLog();
	
}


void CCommandPanel::OnSeasonControl(wxCommandEvent &event)
{
	if(m_SeasonControlValue != m_SeasonControl->GetValue())
	{
		m_Changed[COMMAND_SEASON_CONTROL] = true;
		//m_SeasonControlPanel->Enable();
	}else{
		m_Changed[COMMAND_SEASON_CONTROL] = false;
		//m_SeasonControlPanel->Disable();
	}
		
	SetButtonState();
	SetTextLog();
	
}


void CCommandPanel::OnAuto(wxCommandEvent &event)
{
	
	m_Changed[COMMAND_LIGHT_ON] = false;
	m_Changed[COMMAND_LIGHT_OFF] = false;
	
	if(!m_AutoValue)
		m_Changed[COMMAND_AUTO_MANAGEMENT] = true;
		
	m_LightPanel->Disable();	
	m_AutoValue = true;
	SetButtonState();
	SetTextLog();
	
}

void CCommandPanel::OnManual(wxCommandEvent &event)
{
	m_AutoValue = false;
	m_Changed[COMMAND_AUTO_MANAGEMENT] = false;
	
	m_LightPanel->Enable();
	
	if(m_LightValue)
	{
		m_LightOn->Disable();
		m_LightOff->Enable();
	}else{
		m_LightOn->Enable();
		m_LightOff->Disable();
	}
	
	
	SetButtonState();
	SetTextLog();
	
}


void CCommandPanel::SetTextLog()
{
	m_TextLog->Clear();
	
	for(size_t i = 0; i < COMMAND_COUNT; i++)
	{		
		if(m_Changed[i])
		{
			m_TextLog->AppendText(wxString::Format(_("%s"),GetCommandName(i),GetCommand(i)));
			m_TextLog->AppendText("\r\n");
		}
			
	}

}

void CCommandPanel::SetButtonState()
{
	m_ButtonSend->Disable();
	for(size_t i = 0; i < COMMAND_COUNT; i++)
	{		
		if(m_Changed[i])
			m_ButtonSend->Enable();
	}

}

void CCommandPanel::ButtonDisable()
{
	m_ButtonSend->Disable();
}

void CCommandPanel::OnButtonOk(wxCommandEvent &event)
{
	SetValues();
	
	Disable();
	for(size_t i = 0; i < COMMAND_COUNT; i++)
	{
		if(m_Changed[i])
			SetCommand(i);
	}
}

void CCommandPanel::OnButtonCancel(wxCommandEvent &event)
{
	
}


void CCommandPanel::SetValues()
{
	//m_DriveCurrentValue = m_DriveCurrent->GetValue();
	//m_PowerOfLightValue = m_PowerOfLight->GetValue();
	m_SeasonControlValue = m_SeasonControl->GetValue();
		
}

void CCommandPanel::SetCommand(int id)
{
	wxString sql;
	int SBMSID = m_SelectedPtr->GetSBMSID();
	int id_base_station = m_SelectedPtr->GetBaseStationId();
	int mmsi = m_SelectedPtr->GetMMSI();
	
	switch(id)
	{
		case COMMAND_LIGHT_ON:			_SetCommand(id,mmsi,SBMSID,id_base_station,m_LightOnValue);		break;
		case COMMAND_LIGHT_OFF:			_SetCommand(id,mmsi,SBMSID,id_base_station,m_LightOnValue);		break;
		case COMMAND_AUTO_MANAGEMENT:	_SetCommand(id,mmsi,SBMSID,id_base_station,m_AutoValue);		break;
		case COMMAND_GET_TIME:			_SetCommand(id,mmsi,SBMSID,id_base_station,m_TimeValue);		break;
		case COMMAND_GET_UPTIME:		_SetCommand(id,mmsi,SBMSID,id_base_station,m_UptimeValue);		break;

		//case COMMAND_STANDARD_REPORT:	SetCommandStandardReport(id,mmsi,SBMSID,id_base_station);	break;
	}
	
}

void CCommandPanel::SetSelectedPtr(CSymbol *ptr)
{
	m_SelectedPtr = ptr;
}

void CCommandPanel::ReadCommands()
{
	void *db = DBConnect();
	if(db == NULL)
		return;

	int sbmsid = m_SelectedPtr->GetSBMSID();
	int mmsi = m_SelectedPtr->GetMMSI();
	int id_base_station = m_SelectedPtr->GetBaseStationId();
	
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE SBMSID='%d' AND mmsi='%d' AND id_base_station='%d' AND status='%d'"),TABLE_COMMAND,sbmsid,mmsi,id_base_station,COMMAND_STATUS_NEW);
	
	my_query(db,sql);
	void *result = db_result(db);
	
    char **row = NULL;
	if(result == NULL)
		return;
		
	while(row = (char**)db_fetch_row(result))
	{
		m_TextLog->AppendText(GetCommandName(atoi(row[FI_COMMAND_ID_COMMAND])));
		m_TextLog->AppendText("\r\n");
	}
}


void CCommandPanel::Set()
{
	if((m_SelectedPtr->GetSBMSID() == 0) && (m_SelectedPtr->GetMMSI() == 0))
	{
		Disable();
		SetNoSBMS(true);
		return;
	}

	SetNoSBMS(false);
	
	ReadCommands();


	if(m_SelectedPtr->GetBusy())
		EnableControls(false);
	else
		EnableControls(true);
			
}

void CCommandPanel::EnableControls(bool v)
{
	SetBusy(!v);
	m_ButtonCancel->Enable(!v);
	//m_StandardReportPanel->Enable(v);
	m_LightPanel->Enable(v);
	m_TimePanel->Enable(v);
	m_UptimePanel->Enable(v);
	m_AutoPanel->Enable(v);
	m_LightOn->Enable(v);
	m_LightOff->Enable(v);
	
	//m_DriveCurrentPanel->Enable(v);
	//m_PowerOfLightPanel->Enable(v);
	m_SeasonControlPanel->Enable(v);

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
	m_Busy = v;
	if(v)
		m_InfoText->SetLabel(GetMsg(MSG_BUSY));
	else
		m_InfoText->SetLabel(GetMsg(MSG_READY));
	
	Refresh(false);
}

wxPanel *CCommandPanel::StandardReportPanel(wxPanel *parent)
{
    wxPanel *Panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);
	
	m_StandardReport = new wxCheckBox(Panel,ID_STANDARD_REPORT,GetMsg(MSG_STANDARD_REPORT));
	Sizer->Add(m_StandardReport,0,wxALL,5);
		
	return Panel;

}

wxPanel *CCommandPanel::AutoPanel(wxPanel *parent)
{
    wxPanel *Panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(Sizer);

	m_LightAuto = new wxRadioButton(Panel,ID_AUTO,GetMsg(MSG_AUTO_MANAGEMENT));
	Sizer->Add(m_LightAuto,0,wxALL|wxEXPAND,5);
	
	m_LightManual = new wxRadioButton(Panel,ID_MANUAL,GetMsg(MSG_MANUAL_MANAGEMENT));
	Sizer->Add(m_LightManual,0,wxALL|wxEXPAND,5);
		
	return Panel;
}

wxPanel *CCommandPanel::LightPanel(wxPanel *parent)
{
    wxPanel *Panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);
		
	m_LightOn = new wxButton(Panel,ID_LIGHT_ON,GetMsg(MSG_LIGHT_ON));
	Sizer->Add(m_LightOn,0,wxALL,5);

	m_LightOff = new wxButton(Panel,ID_LIGHT_OFF,GetMsg(MSG_LIGHT_OFF));
	Sizer->Add(m_LightOff,0,wxALL,5);

		
	return Panel;
}

/*
wxPanel *CCommandPanel::GetTimePanel(wxPanel *parent)
{
		
    wxPanel *Panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);
	
	m_Auto = new wxCheckBox(Panel,ID_TIME,GetMsg(MSG_));
	Sizer->Add(m_Time,0,wxALL,5);
		
	return Panel;

}
*/

wxPanel *CCommandPanel::GetTimePanel(wxPanel *parent)
{
		
    wxPanel *Panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	//Panel->SetBackgroundColour(COMMAND_PANEL_BG_COLOR);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);
	
	m_Time = new wxCheckBox(Panel,ID_TIME,GetMsg(MSG_GET_TIME));
	Sizer->Add(m_Time,0,wxALL,5);
		
	return Panel;

}

wxPanel *CCommandPanel::GetUptimePanel(wxPanel *parent)
{
		
    wxPanel *Panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	//Panel->SetBackgroundColour(COMMAND_PANEL_BG_COLOR);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);
	
	m_Uptime = new wxCheckBox(Panel,ID_UPTIME,GetMsg(MSG_GET_UPTIME));
	Sizer->Add(m_Uptime,0,wxALL,5);
		
	return Panel;

}


wxPanel *CCommandPanel::SeasonControlPanel(wxPanel *parent)
{
		
    wxPanel *Panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	//Panel->SetBackgroundColour(COMMAND_PANEL_BG_COLOR);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(Sizer);

	m_SeasonControl = new wxCheckBox(Panel,ID_SEASON_CONTROL,GetMsg(MSG_SEASON_CONTROL));
	Sizer->Add(m_SeasonControl,0,wxALL,5);
	
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
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);
	
	wxTextCtrl *aa = new wxTextCtrl(Panel,wxID_ANY);
	Sizer->Add(aa,0,wxALL|wxEXPAND,5);
	
	//m_ButtonDelete->Disable();
		
	return Panel;

}

wxPanel *CCommandPanel::DriveCurrentPanel(wxPanel *parent)
{
		
    wxPanel *Panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	//Panel->SetBackgroundColour(COMMAND_PANEL_BG_COLOR);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);
	
	wxStaticText *LabelDriveCurrent = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_DRIVE_CURRENT));
	Sizer->Add(LabelDriveCurrent,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_DriveCurrent = new wxSlider(Panel,ID_DRIVE_CURRENT,0,0,1,wxDefaultPosition,wxDefaultSize,wxSL_VALUE_LABEL);
	Sizer->Add(m_DriveCurrent,1,wxALL|wxEXPAND,5);
	m_DriveCurrent->SetMin(DRIVE_CURRENT_MIN);
	m_DriveCurrent->SetMax(DRIVE_CURRENT_MAX);
		
	return Panel;

}

wxPanel *CCommandPanel::PowerOfLightPanel(wxPanel *parent)
{
		
    wxPanel *Panel = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	//Panel->SetBackgroundColour(COMMAND_PANEL_BG_COLOR);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);

	wxStaticText *LabelPowerOfLight = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_POWER_OF_LIGHT));
	Sizer->Add(LabelPowerOfLight,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_PowerOfLight = new wxSlider(Panel,ID_POWER_OF_LIGHT,0,0,1,wxDefaultPosition,wxSize(150,-1),wxSL_VALUE_LABEL);
	Sizer->Add(m_PowerOfLight,1,wxALL|wxEXPAND,5);
	m_PowerOfLight->SetMin(POWER_OF_LIGHT_MIN);
	m_PowerOfLight->SetMax(POWER_OF_LIGHT_MAX);
			
	return Panel;

}

wxPanel *CCommandPanel::TextLogPanel(wxPanel *parent)
{
	wxPanel *Panel = new wxPanel(parent, wxID_ANY);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(Sizer);
	
	m_TextLog = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(-1,150),wxTE_MULTILINE);
	Sizer->Add(m_TextLog,0,wxALL|wxEXPAND,5);

	return Panel;
}

wxPanel *CCommandPanel::GetCommandPanel(wxPanel *parent)
{

	wxPanel *Panel = new wxPanel(parent);
	
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(Sizer);

	m_InfoText = new wxStaticText(Panel,wxID_ANY,wxEmptyString);
	Sizer->Add(m_InfoText,0,wxALL,2);

	//pobranie czasu
	m_TimePanel = GetTimePanel(Panel);
	Sizer->Add(m_TimePanel,0,wxALL|wxEXPAND,2);
	
	//pobranie czasu (uptime)
	m_UptimePanel = GetUptimePanel(Panel);
	Sizer->Add(m_UptimePanel,0,wxALL|wxEXPAND,2);

	//standardowy raport
	//m_StandardReportPanel = StandardReportPanel(Panel);
	//Sizer->Add(m_StandardReportPanel,0,wxALL|wxEXPAND,2);
	
	wxStaticBoxSizer *BoxSizer = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_LIGHT));
	Sizer->Add(BoxSizer,0,wxALL|wxEXPAND,5);

	//serwisowe wy³¹czenie
	m_AutoPanel = AutoPanel(Panel);
	BoxSizer->Add(m_AutoPanel,0,wxALL|wxEXPAND,2);
	m_LightPanel = LightPanel(Panel);
	BoxSizer->Add(m_LightPanel,0,wxALL|wxEXPAND,2);
		
	//sezonowa praca
	wxStaticBoxSizer *BoxSizer1 = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_SEASON_CONTROL));
	Sizer->Add(BoxSizer1,0,wxALL|wxEXPAND,5);

	m_SeasonControlPanel = SeasonControlPanel(Panel);
	BoxSizer1->Add(m_SeasonControlPanel,0,wxALL|wxEXPAND,2);
	
	
	// pr¹d podk³adu
	//m_DriveCurrentPanel = DriveCurrentPanel(Panel);
	//Sizer->Add(m_DriveCurrentPanel,0,wxALL|wxEXPAND,2);
	
	//moc œwiat³a
	//m_PowerOfLightPanel = PowerOfLightPanel(Panel);
	//Sizer->Add(m_PowerOfLightPanel,0,wxALL|wxEXPAND,2);

	//text log
	m_TextLogPanel = TextLogPanel(Panel);
	Sizer->Add(m_TextLogPanel,0,wxALL|wxEXPAND,2);
	

	wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
	Sizer->Add(hSizer,0,wxALL|wxEXPAND,0);
	
	m_ButtonSend = new wxButton(Panel,ID_BUTTON_OK,GetMsg(MSG_SEND_COMMAND));
	hSizer->Add(m_ButtonSend,0,wxALL|wxEXPAND,5);
	m_ButtonSend->Disable();
	
	m_ButtonCancel = new wxButton(Panel,ID_BUTTON_CANCEL,GetMsg(MSG_CANCEL));
	hSizer->Add(m_ButtonCancel,0,wxALL|wxEXPAND,5);
	
	return Panel;
}

wxPanel *CCommandPanel::GetAutoPanel(wxPanel *parent)
{
	
	wxPanel *Panel = new wxPanel(parent);
	/*
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(Sizer);

	wxRadioButton *m_Auto = new wxRadioButton(Panel,ID_AUTO,GetMsg(MSG_AUTO_MANAGEMENT));
	Sizer->Add(m_Auto,0,wxALL|wxEXPAND,5);
	
	wxRadioButton *m_Human = new wxRadioButton(Panel,ID_HUMAN,GetMsg(MSG_HUMAN_MANAGEMENT));
	Sizer->Add(m_Human,0,wxALL|wxEXPAND,5);
	*/
	return Panel;
}

void CCommandPanel::SetGui()
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(Sizer);
	//Sizer->Add(GetAutoPanel(this),0,wxALL|wxEXPAND,2);
	//wxStaticLine *line = new wxStaticLine(this,wxID_ANY);
	//Sizer->Add(line,0,wxALL|wxEXPAND,0);
	Sizer->Add(GetCommandPanel(this),1,wxALL|wxEXPAND,2);
}

//VALUES. . . . . . . . . . .  . . . . . .
void CCommandPanel::SetForcedOff(bool v)
{
	if(m_Busy)
		return;
	
	m_LightValue = !v; // forced off neguje
	
	if(m_LightValue)
	{
		m_LightOn->Disable();
		m_LightOff->Enable();
	}else{
		m_LightOn->Enable();
		m_LightOff->Disable();
	}

}

void CCommandPanel::SetAuto(bool v)
{
	m_AutoValue = v;
	m_LightAuto->SetValue(v);
	m_LightManual->SetValue(!v);
	
	m_LightPanel->Enable(!v);
}