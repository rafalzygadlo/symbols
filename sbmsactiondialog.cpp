#include <wx/wx.h>
#include <wx/statline.h>
#include "conf.h"
#include "sbmsactiondialog.h"
#include "control.h"
#include "tools.h"
#include "module.h"
#include "action.h"

BEGIN_EVENT_TABLE(CSBMSActionDialog,wxDialog)
	EVT_BUTTON(ID_GRAPH,OnGraph)
	EVT_BUTTON(ID_LIGHT_ON,OnLightOn)
	EVT_BUTTON(ID_LIGHT_OFF,OnLightOff)
	EVT_BUTTON(ID_AUTO,OnAutoManagement)
	EVT_BUTTON(ID_TIME,OnGetTime)
	EVT_BUTTON(ID_UPTIME,OnGetUptime)
	EVT_BUTTON(ID_RESET,OnReset)
END_EVENT_TABLE();

CSBMSActionDialog::CSBMSActionDialog(void *db, CSBMS *ptr)
	:wxDialog(NULL,wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize )
{	
	m_DB = db;

	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(Sizer);
	
	Sizer->Add(GetTopPanel(this),0,wxALL|wxEXPAND,5);
	Sizer->Add(GetActionPanel(this),1,wxALL|wxEXPAND,5);
	Sizer->Add(GetButtonPanel(this),0,wxALL|wxEXPAND,5);
	SetSizer(Sizer);
	SetSBMS(ptr);
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
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	
	m_ButtonGraph = new CButton(m_DB,_GetUID(),Panel,ID_GRAPH,GetMsg(MSG_GRAPH));
	m_ButtonGraph->Right(MODULE_COMMAND,ACTION_GRAPH);
	Sizer->Add(m_ButtonGraph,0,wxALL|wxEXPAND,2);
		
	//m_ClearAlarm = new CButton(m_DB,_GetUID(),Panel,ID_CLEAR_ALARM,GetMsg(MSG_CLEAR_ALARM));
	//Sizer->Add(m_ClearAlarm,0,wxALL|wxEXPAND,2);

	//m_ClearCommand = new CButton(m_DB,_GetUID(),Panel,ID_CLEAR_COMMAND,GetMsg(MSG_CLEAR_COMMAND));
	//Sizer->Add(m_ClearCommand,0,wxALL|wxEXPAND,2);
	
	wxGridSizer *FlexSizer = new wxGridSizer(3);
	Sizer->Add(FlexSizer,1,wxALL|wxEXPAND,0);
	
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

	Panel->SetSizer(Sizer);
	
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

void CSBMSActionDialog::SetSBMS(CSBMS *ptr)
{
	m_Symbol = ptr;
}

void CSBMSActionDialog::OnGraph(wxCommandEvent &event)
{
	m_Symbol->ShowGraph();
}

void CSBMSActionDialog::OnLightOn(wxCommandEvent &event)
{
	m_Symbol->LightOn();
}

void CSBMSActionDialog::OnLightOff(wxCommandEvent &event)
{
	m_Symbol->LightOff();
}

void CSBMSActionDialog::OnAutoManagement(wxCommandEvent &event)
{
	m_Symbol->AutoManagement();
}

void CSBMSActionDialog::OnGetTime(wxCommandEvent &event)
{
	m_Symbol->GetTime();
}

void CSBMSActionDialog::OnGetUptime(wxCommandEvent &event)
{
	m_Symbol->GetUptime();
}

void CSBMSActionDialog::OnReset(wxCommandEvent &event)
{
	m_Symbol->Reset();
}

