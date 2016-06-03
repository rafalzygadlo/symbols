#include <wx/wx.h>
#include <wx/statline.h>
#include "conf.h"
#include "sbmsactiondialog.h"
#include "control.h"
#include "tools.h"
#include "module.h"
#include "action.h"
#include "symbolgroup.h"

BEGIN_EVENT_TABLE(CSBMSActionDialog,wxDialog)
	EVT_BUTTON(ID_GRAPH,OnGraph)
	EVT_BUTTON(ID_LIGHT_ON,OnLightOn)
	EVT_BUTTON(ID_LIGHT_OFF,OnLightOff)
	EVT_BUTTON(ID_AUTO,OnAutoManagement)
	EVT_BUTTON(ID_TIME,OnGetTime)
	EVT_BUTTON(ID_UPTIME,OnGetUptime)
	EVT_BUTTON(ID_RESET,OnReset)
	EVT_BUTTON(ID_DESTINATION_MMSI,OnDestinationMMSI)
	EVT_BUTTON(ID_CLEAR_ALARM,OnClearAlarm)
	EVT_BUTTON(ID_CLEAR_COMMAND,OnClearCommand)
	EVT_BUTTON(ID_ADD_TO_GROUP,OnAddToGroup)
	EVT_BUTTON(ID_CURRENT_DRIVE,OnCurrentDrive)
END_EVENT_TABLE();

CSBMSActionDialog::CSBMSActionDialog(void *db, CSBMS *ptr)
	:wxDialog(NULL,wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize )
{	
	m_DB = db;
	m_SBMS = ptr;

	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(Sizer);
	
	Sizer->Add(GetTopPanel(this),0,wxALL|wxEXPAND,5);
	Sizer->Add(GetActionPanel(this),1,wxALL|wxEXPAND,5);
	Sizer->Add(GetButtonPanel(this),0,wxALL|wxEXPAND,5);
	SetSizer(Sizer);
	Fit();
	Center();
		
	SetTitle(wxString::Format(_("%s (%s)"),ptr->GetSymbolName(),ptr->GetName()));
}

CSBMSActionDialog::~CSBMSActionDialog()
{

}

void CSBMSActionDialog::SetTitle(wxString str)
{
	m_Title->SetLabel(str);
}

wxPanel *CSBMSActionDialog::GetTopPanel(wxWindow *parent)
{
	wxPanel *Panel = new wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(Sizer);
	wxFont font;
	font.SetPointSize(12);
	font.SetWeight(wxBOLD);
	m_Title = new wxStaticText(Panel,wxID_ANY,wxEmptyString);
	m_Title->SetFont(font);
	Sizer->Add(m_Title,0,wxALL|wxEXPAND,2);
		
	return Panel;
}

wxPanel *CSBMSActionDialog::GetActionPanel(wxWindow *parent)
{
	wxPanel *Panel = new wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	wxGridSizer *FlexSizer = new wxGridSizer(4);
	
		
	m_ButtonGraph = new CButton(m_DB,_GetUID(),Panel,ID_GRAPH,GetMsg(MSG_GRAPH));
	m_ButtonGraph->Right(MODULE_COMMAND,ACTION_GRAPH);
	FlexSizer->Add(m_ButtonGraph,1,wxALL|wxEXPAND,2);

	m_ButtonAddToGroup = new CButton(m_DB,_GetUID(),Panel,ID_ADD_TO_GROUP,GetMsg(MSG_ADD_TO_GROUP));
	m_ButtonAddToGroup->Right(MODULE_SYMBOL,ACTION_GROUP);
	FlexSizer->Add(m_ButtonAddToGroup,1,wxALL|wxEXPAND,2);
	
	FlexSizer->SetItemMinSize(1,-1,50);

	m_ClearAlarm = new CButton(m_DB,_GetUID(),Panel,ID_CLEAR_ALARM,GetMsg(MSG_CLEAR_ALARM));
	m_ClearAlarm->Right(MODULE_COMMAND,ACTION_CLEAR_ALARM);
	FlexSizer->Add(m_ClearAlarm,1,wxALL|wxEXPAND,2);

	m_ClearCommand = new CButton(m_DB,_GetUID(),Panel,ID_CLEAR_COMMAND,GetMsg(MSG_CLEAR_COMMAND));
	m_ClearCommand->Right(MODULE_COMMAND,ACTION_CLEAR_COMMAND);
	FlexSizer->Add(m_ClearCommand,1,wxALL|wxEXPAND,2);
		
	m_ButtonOn = new CButton(m_DB,_GetUID(), Panel,ID_LIGHT_ON,GetMsg(MSG_LIGHT_ON));
	m_ButtonOn->Right(MODULE_COMMAND,ACTION_LIGHT_ON);
	FlexSizer->Add(m_ButtonOn,1,wxALL|wxEXPAND,2);

	m_ButtonOff = new CButton(m_DB,_GetUID(),Panel,ID_LIGHT_OFF,GetMsg(MSG_LIGHT_OFF));
	m_ButtonOff->Right(MODULE_COMMAND,ACTION_LIGHT_OFF);
	FlexSizer->Add(m_ButtonOff,1,wxALL|wxEXPAND,2);

	m_ButtonAuto = new CButton(m_DB,_GetUID(),Panel,ID_AUTO,GetMsg(MSG_AUTO_MANAGEMENT));
	m_ButtonAuto->Right(MODULE_COMMAND,ACTION_AUTO);
	FlexSizer->Add(m_ButtonAuto,1,wxALL|wxEXPAND,2);

	m_ButtonTime = new CButton(m_DB,_GetUID(),Panel,ID_TIME,GetMsg(MSG_GET_TIME));
	m_ButtonTime->Right(MODULE_COMMAND,ACTION_TIME);
	FlexSizer->Add(m_ButtonTime,1,wxALL|wxEXPAND,2);

	m_ButtonUpTime = new CButton(m_DB,_GetUID(),Panel,ID_UPTIME,GetMsg(MSG_GET_UPTIME));
	m_ButtonUpTime->Right(MODULE_COMMAND,ACTION_UPTIME);
	FlexSizer->Add(m_ButtonUpTime,1,wxALL|wxEXPAND,2);

	m_ButtonReset = new CButton(m_DB,_GetUID(),Panel,ID_RESET,GetMsg(MSG_RESET));
	m_ButtonReset->Right(MODULE_COMMAND,ACTION_RESET);
	FlexSizer->Add(m_ButtonReset,1,wxALL|wxEXPAND,2);

	m_CurrentDrive = new CButton(m_DB,_GetUID(),Panel,ID_CURRENT_DRIVE,GetMsg(MSG_CURRENT_DRIVE));
	m_CurrentDrive->Right(MODULE_COMMAND,ACTION_CURRENT_DRIVE);
	FlexSizer->Add(m_CurrentDrive,1,wxALL|wxEXPAND,2);

	if(m_SBMS->GetMMSI())
	{
		m_ButtonDestinationMMSI = new CButton(m_DB,_GetUID(),Panel,ID_DESTINATION_MMSI,GetMsg(MSG_DESTINATION_MMSI));
		m_ButtonDestinationMMSI->Right(MODULE_COMMAND,ACTION_DEST_MMSI);
		FlexSizer->Add(m_ButtonDestinationMMSI,1,wxALL|wxEXPAND,2);
	}

	Panel->SetSizer(FlexSizer);
	
	return Panel;
			
}

wxPanel *CSBMSActionDialog::GetButtonPanel(wxWindow *parent)
{

	wxPanel *Panel = new wxPanel(this);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);

	wxStaticText *LabelProductInfo = new wxStaticText(Panel,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	Sizer->Add(LabelProductInfo,0,wxALL,5);
	Sizer->AddStretchSpacer(1);

	wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CLOSE));
	Sizer->AddStretchSpacer();
	Sizer->Add(ButtonClose,0,wxALL,2);
	
	return Panel;
}

void CSBMSActionDialog::OnGraph(wxCommandEvent &event)
{
	m_SBMS->ShowGraph();
}

void CSBMSActionDialog::OnClearAlarm(wxCommandEvent &event)
{
	wxMessageDialog dlg(this, GetMsg(MSG_CLEAR_ALARMS),wxString::Format(wxT("%s %s"),wxT(PRODUCT_NAME),wxT(PRODUCT_VERSION)),wxYES_NO|wxICON_QUESTION);
	
	if (dlg.ShowModal() == wxID_YES)
	{
		m_SBMS->ClearAlarm();	
	}
}

void CSBMSActionDialog::OnClearCommand(wxCommandEvent &event)
{
	wxMessageDialog dlg(this, GetMsg(MSG_CLEAR_COMMANDS),wxString::Format(wxT("%s %s"),wxT(PRODUCT_NAME),wxT(PRODUCT_VERSION)),wxYES_NO|wxICON_QUESTION);
	
	if (dlg.ShowModal() == wxID_YES)
	{
		m_SBMS->ClearCommands();
	}
}
void CSBMSActionDialog::OnAddToGroup(wxCommandEvent &event)
{
	int v = m_SBMS->GetIdSymbol();
	CSymbolGroup *SymbolGroup = new CSymbolGroup(m_DB,v);
	SymbolGroup->ShowModal();
	delete SymbolGroup;
}



void CSBMSActionDialog::OnLightOn(wxCommandEvent &event)
{
	m_SBMS->LightOn();
}

void CSBMSActionDialog::OnLightOff(wxCommandEvent &event)
{
	m_SBMS->LightOff();
}

void CSBMSActionDialog::OnAutoManagement(wxCommandEvent &event)
{
	m_SBMS->AutoManagement();
}

void CSBMSActionDialog::OnGetTime(wxCommandEvent &event)
{
	m_SBMS->GetTime();
}

void CSBMSActionDialog::OnGetUptime(wxCommandEvent &event)
{
	m_SBMS->GetUptime();
}

void CSBMSActionDialog::OnReset(wxCommandEvent &event)
{
	m_SBMS->Reset();
}

void CSBMSActionDialog::OnCurrentDrive(wxCommandEvent &event)
{
	wxTextEntryDialog dlg(this, GetMsg(MSG_CURRENT_DRIVE),GetMsg(MSG_CURRENT_DRIVE));
	dlg.SetTextValidator(wxTextValidator(wxFILTER_NUMERIC));
	if (dlg.ShowModal() == wxID_OK)
	{
		long v;
		dlg.GetValue().ToLong(&v);

		m_SBMS->CurrentDrive(v);
	}
	dlg.Close();
}

void CSBMSActionDialog::OnDestinationMMSI(wxCommandEvent &event)
{
	wxTextEntryDialog dlg(this, GetMsg(MSG_DESTINATION_MMSI),GetMsg(MSG_DESTINATION_MMSI));
	dlg.SetTextValidator(wxTextValidator(wxFILTER_NUMERIC));
	if (dlg.ShowModal() == wxID_OK)
	{
		long mmsi;
		dlg.GetValue().ToLong(&mmsi);

		m_SBMS->DestinationMMSI(mmsi);
	}
    dlg.Close();

}