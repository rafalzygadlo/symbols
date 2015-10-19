#include <wx/wx.h>
#include <wx/checkbox.h>
#include <wx/event.h>
#include <wx/notebook.h>
#include "ais.h"
#include "tools.h"
#include "filterdialog.h"
#include "options.h"



BEGIN_EVENT_TABLE(CFilterDialog,wxDialog)
//	EVT_CHECKBOX(wxID_ANY,OnCheck)
//	EVT_BUTTON(ID_SELECT_ALL,OnSelectAll)
//	EVT_BUTTON(ID_DESELECT_ALL,OnDeSelectAll)
END_EVENT_TABLE()


CFilterDialog::CFilterDialog()
:wxDialog(NULL,wxID_ANY, GetMsg(MSG_FILTER), wxDefaultPosition, wxDefaultSize )
{
	SetGui();
	Center();
}

CFilterDialog::~CFilterDialog(void)
{
	
}

void CFilterDialog::SetGui()
{
	void *db = DBConnect();
	if(db)
	{
		wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
		wxBoxSizer *ScrollSizer = new wxBoxSizer(wxVERTICAL);
		wxScrolledWindow *Scroll = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(-1,400));
		Sizer->Add(Scroll,0,wxALL|wxEXPAND,5);
		Scroll->SetSizer(ScrollSizer);

		ScrollSizer->Add(GetAlarmPanel(db,Scroll),0,wxALL|wxEXPAND,5);
		ScrollSizer->Add(GetGroupPanel(db,Scroll),0,wxALL|wxEXPAND,5);
		ScrollSizer->Add(GetPanel(db,Scroll),0,wxALL|wxEXPAND,5);
		
		Sizer->Add(GetButtonPanel(this),0,wxALL,5);
		Sizer->SetSizeHints(this);
				
		Scroll->SetScrollbars(20, 20, 20, 20);
		//Scroll->SetFocusIgnoringChildren();
		
		this->SetSizer(Sizer);
	}

	DBClose(db);

}

wxPanel *CFilterDialog::GetButtonPanel(wxWindow *parent)
{

	wxPanel *Panel = new wxPanel(parent);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);	

	wxStaticText *LabelProductInfo = new wxStaticText(Panel,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	Sizer->Add(LabelProductInfo,0,wxALL,5);
	Sizer->AddStretchSpacer(1);
		
	wxButton *ButtonOk = new wxButton(Panel,wxID_OK,GetMsg(MSG_OK),wxDefaultPosition,wxDefaultSize);
	Sizer->Add(ButtonOk,0,wxALL|wxALIGN_RIGHT,5);
	
	wxButton *ButtonCancel = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CANCEL),wxDefaultPosition,wxDefaultSize);
	Sizer->Add(ButtonCancel,0,wxALL|wxALIGN_RIGHT,5);

	
	return Panel;
}


wxPanel *CFilterDialog::GetPanel(void *db,wxWindow *Parent)
{

	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
	//wxStaticBoxSizer *Sizer1 = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_FILTER));
	//Sizer->Add(Sizer1,1,wxALL|wxEXPAND,0);

	wxBoxSizer *FlexSizer = new wxBoxSizer(wxVERTICAL);
	Sizer->Add(FlexSizer,1,wxALL|wxEXPAND,0);
		
	//m_CheckInMonitoring = new wxCheckBox(Panel,wxID_ANY,GetMsg(MSG_IN_MONITORING));
	//FlexSizer->AddSpacer(1);
	//FlexSizer->Add(m_CheckInMonitoring,0,wxALL,5);

	//wxStaticText *LabelAlarm = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_ALARM));
	//FlexSizer->Add(LabelAlarm,0,wxALL,5);
	//m_ComboAlarm = GetCombo(db,Panel,TABLE_ALARM,wxEmptyString,FI_ALARM_ID,FI_ALARM_NAME, true);
	//m_ComboAlarm->SetSelection(0);
	//FlexSizer->Add(m_ComboAlarm,0,wxALL|wxEXPAND,5);
	
	/*
	wxStaticText *LabelLight = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_LIGHT));
	FlexSizer->Add(LabelLight,0,wxALL,5);
	m_ComboLight = new wxComboBox(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,NULL,0, wxCB_READONLY );
	m_ComboLight->Append(GetMsg(MSG_ALL));
	m_ComboLight->Append(GetMsg(MSG_LIGHT_OFF));
	m_ComboLight->Append(GetMsg(MSG_LIGHT_ON));
	m_ComboLight->SetSelection(0);
	FlexSizer->Add(m_ComboLight,0,wxALL|wxEXPAND,5);

	wxStaticText *LabelInMonitoring = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_IN_MONITORING));
	FlexSizer->Add(LabelInMonitoring,0,wxALL,5);
	m_ComboInMonitoring = new wxComboBox(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,NULL,0, wxCB_READONLY );
	m_ComboInMonitoring->Append(GetMsg(MSG_ALL));
	m_ComboInMonitoring->Append(GetMsg(MSG_NOT_IN_MONITORING));
	m_ComboInMonitoring->Append(GetMsg(MSG_IN_MONITORING));
	m_ComboInMonitoring->SetSelection(0);
	FlexSizer->Add(m_ComboInMonitoring,0,wxALL|wxEXPAND,5);
	*/
	wxStaticText *LabelBaseStation = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_BASE_STATION));
	FlexSizer->Add(LabelBaseStation,0,wxALL,5);
	m_ComboBaseStation = GetCheckListBox(db,Panel,TABLE_BASE_STATION,wxEmptyString,FI_BASE_STATION_ID,FI_BASE_STATION_NAME);
	FlexSizer->Add(m_ComboBaseStation,0,wxALL|wxEXPAND,5);

	wxStaticText *LabelArea = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_AREA));
	FlexSizer->Add(LabelArea,0,wxALL,5);
	m_ComboArea = GetCheckListBox(db,Panel,TABLE_AREA,wxEmptyString,FI_AREA_ID,FI_AREA_NAME);
	m_ComboArea->SetSelection(0);
	FlexSizer->Add(m_ComboArea,0,wxALL|wxEXPAND,5);
	
	wxStaticText *LabelSeaway = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SEAWAY));
	FlexSizer->Add(LabelSeaway,0,wxALL,5);
	m_ComboSeaway = GetCheckListBox(db,Panel,TABLE_SEAWAY,wxEmptyString,FI_SEAWAY_ID,FI_SEAWAY_NAME);
	m_ComboSeaway->SetSelection(0);
	FlexSizer->Add(m_ComboSeaway,0,wxALL|wxEXPAND,5);
	
	wxStaticText *LabelSymbolType = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SYMBOL_TYPE));
	FlexSizer->Add(LabelSymbolType,0,wxALL,5);
	m_ComboSymbolType = GetCheckListBox(db,Panel,TABLE_SYMBOL_TYPE,wxEmptyString,FI_SYMBOL_TYPE_ID,FI_SYMBOL_TYPE_NAME);
	m_ComboSymbolType->SetSelection(0);
	FlexSizer->Add(m_ComboSymbolType,0,wxALL|wxEXPAND,5);
		
	return Panel;
}

wxPanel *CFilterDialog::GetAlarmPanel(void *db,wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
	//wxStaticBoxSizer *Sizer1 = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_ALARM));
	//Sizer->Add(Sizer1,1,wxALL|wxEXPAND,0);

	wxBoxSizer *FlexSizer = new wxBoxSizer(wxVERTICAL);
	Sizer->Add(FlexSizer,0,wxALL|wxEXPAND,0);
	
	//wxStaticText *LabelAlarm = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_ALARM));
	//FlexSizer->Add(LabelAlarm,0,wxALL,5);
	m_ComboAlarm = GetCheckListBox(db,Panel,TABLE_ALARM,wxEmptyString,FI_ALARM_ID,FI_ALARM_NAME, true);
	m_ComboAlarm->SetSelection(0);
	FlexSizer->Add(m_ComboAlarm,0,wxALL|wxEXPAND,5);
	
	return Panel;
}

wxPanel *CFilterDialog::GetGroupPanel(void *db,wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
	//wxStaticBoxSizer *Sizer1 = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_SYMBOL_GROUP));
	//Sizer->Add(Sizer1,1,wxALL|wxEXPAND,0);

	wxBoxSizer *FlexSizer = new wxBoxSizer(wxVERTICAL);
	Sizer->Add(FlexSizer,0,wxALL|wxEXPAND,0);
	
	wxStaticText *LabelGroup = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SYMBOL_GROUP));
	FlexSizer->Add(LabelGroup,0,wxALL,5);
	m_ComboGroup = GetCheckListBox(db,Panel,TABLE_SYMBOL_GROUP,wxEmptyString,FI_SYMBOL_GROUP_ID,FI_SYMBOL_GROUP_NAME);
	m_ComboGroup->SetSelection(0);
	FlexSizer->Add(m_ComboGroup,0,wxALL|wxEXPAND,5);
	
	return Panel;
}


//GET
int CFilterDialog::GetAlarmId()
{
	return (int)m_ComboAlarm->GetClientData(m_ComboAlarm->GetSelection());
}

int CFilterDialog::GetAreaId()
{
	return (int)m_ComboArea->GetClientData(m_ComboArea->GetSelection());
}

int CFilterDialog::GetSymbolTypeId()
{
	return (int)m_ComboSymbolType->GetClientData(m_ComboSymbolType->GetSelection());
}

int CFilterDialog::GetSeawayId()
{
	return (int)m_ComboSeaway->GetClientData(m_ComboSeaway->GetSelection());
}

int CFilterDialog::GetBaseStationId()
{
	return (int)m_ComboBaseStation->GetClientData(m_ComboBaseStation->GetSelection());
}

int CFilterDialog::GetInMonitoring()
{
	return m_ComboInMonitoring->GetSelection() - 1; 
}

int CFilterDialog::GetLight()
{
	return m_ComboLight->GetSelection() - 1; 
}

int CFilterDialog::GetGroupId()
{
	return (int)m_ComboGroup->GetClientData(m_ComboGroup->GetSelection());
}

//SET

void CFilterDialog::SetAlarmId(int v)
{
	CheckListBoxSetSelection(m_ComboAlarm,v);
}

void CFilterDialog::SetAreaId(int v)
{
	CheckListBoxSetSelection(m_ComboArea,v);
}

void CFilterDialog::SetSymbolTypeId(int v)
{
	CheckListBoxSetSelection(m_ComboSymbolType,v);
}

void CFilterDialog::SetBaseStationId(int v)
{
	CheckListBoxSetSelection(m_ComboBaseStation,v);
	//ComboSetSelection(m_ComboBaseStation,v);
}

void CFilterDialog::SetSeawayId(int v)
{
	CheckListBoxSetSelection(m_ComboSeaway,v);
}

void CFilterDialog::SetInMonitoring(int v)
{
	//m_ComboInMonitoring->SetSelection(v + 1);
}

void CFilterDialog::SetLight(int v)
{
	//m_ComboLight->SetSelection(v + 1);
}

void CFilterDialog::SetGroupId(int v)
{
	CheckListBoxSetSelection(m_ComboGroup,v);
}
