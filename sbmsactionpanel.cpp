#include <wx/wx.h>
#include <wx/statline.h>
#include "conf.h"
#include "sbmsactionpanel.h"
#include "control.h"
#include "tools.h"

BEGIN_EVENT_TABLE(CSBMSActionPanel,wxPanel)
	EVT_BUTTON(ID_GRAPH,OnGraph)
	EVT_BUTTON(ID_LIGHT_ON,OnLightOn)
	EVT_BUTTON(ID_LIGHT_OFF,OnLightOff)
	EVT_BUTTON(ID_AUTO,OnAutoManagement)
	EVT_BUTTON(ID_TIME,OnGetTime)
	EVT_BUTTON(ID_UPTIME,OnGetUptime)
	EVT_BUTTON(ID_RESET,OnReset)
END_EVENT_TABLE();

CSBMSActionPanel::CSBMSActionPanel(wxWindow *parent)
:wxPanel(parent,wxID_ANY)
{
	SetGui();
}

void CSBMSActionPanel::SetGui()
{
	wxFlexGridSizer *Sizer = new wxFlexGridSizer(3);
	Sizer->AddGrowableCol(0,1);
	Sizer->AddGrowableCol(1,1);
	Sizer->AddGrowableCol(2,1);

	m_ButtonGraph = new CButton(this,ID_GRAPH,GetMsg(MSG_GRAPH));
	Sizer->Add(m_ButtonGraph,1,wxALL|wxEXPAND,2);
	Sizer->AddSpacer(1);
	Sizer->AddSpacer(1);
	
	m_ButtonOn = new CButton(this,ID_LIGHT_ON,GetMsg(MSG_LIGHT_ON));
	Sizer->Add(m_ButtonOn,1,wxALL|wxEXPAND,2);

	m_ButtonOff = new CButton(this,ID_LIGHT_OFF,GetMsg(MSG_LIGHT_OFF));
	Sizer->Add(m_ButtonOff,1,wxALL|wxEXPAND,2);

	m_ButtonAuto = new CButton(this,ID_AUTO,GetMsg(MSG_AUTO_MANAGEMENT));
	Sizer->Add(m_ButtonAuto,1,wxALL|wxEXPAND,2);

	m_ButtonTime = new CButton(this,ID_TIME,GetMsg(MSG_GET_TIME));
	Sizer->Add(m_ButtonTime,1,wxALL|wxEXPAND,2);

	m_ButtonUpTime = new CButton(this,ID_UPTIME,GetMsg(MSG_GET_UPTIME));
	Sizer->Add(m_ButtonUpTime,1,wxALL|wxEXPAND,2);

	m_ButtonReset = new CButton(this,ID_RESET,GetMsg(MSG_RESET));
	Sizer->Add(m_ButtonReset,1,wxALL|wxEXPAND,2);

	EnableControls(false);
	SetSizer(Sizer);
			
}

void CSBMSActionPanel::EnableControls(bool v)
{
	m_ButtonGraph->Enable(v);
	m_ButtonOn->Enable(v);
	m_ButtonOff->Enable(v);
	m_ButtonAuto->Enable(v);
	m_ButtonTime->Enable(v);
	m_ButtonUpTime->Enable(v);
	m_ButtonReset->Enable(v);
}

void CSBMSActionPanel::SetSymbol(CSymbol *ptr)
{
	if(ptr)
		EnableControls(true);
	else
		EnableControls(false);
	
	m_Symbol = ptr;
}

void CSBMSActionPanel::OnGraph(wxCommandEvent &event)
{
	m_Symbol->ShowGraph();
}

void CSBMSActionPanel::OnLightOn(wxCommandEvent &event)
{
	m_Symbol->LightOn();
}

void CSBMSActionPanel::OnLightOff(wxCommandEvent &event)
{
	m_Symbol->LightOff();
}

void CSBMSActionPanel::OnAutoManagement(wxCommandEvent &event)
{
	m_Symbol->AutoManagement();
}

void CSBMSActionPanel::OnGetTime(wxCommandEvent &event)
{
	m_Symbol->GetTime();
}

void CSBMSActionPanel::OnGetUptime(wxCommandEvent &event)
{
	m_Symbol->GetUptime();
}

void CSBMSActionPanel::OnReset(wxCommandEvent &event)
{
	m_Symbol->Reset();
}