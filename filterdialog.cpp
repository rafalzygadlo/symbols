#include "ais.h"
#include "tools.h"
#include "filterdialog.h"
#include "options.h"
#include <wx/wx.h>
#include <wx/checkbox.h>
#include <wx/event.h>


BEGIN_EVENT_TABLE(CFilterDialog,wxDialog)
//	EVT_CHECKBOX(wxID_ANY,OnCheck)
//	EVT_BUTTON(ID_SELECT_ALL,OnSelectAll)
//	EVT_BUTTON(ID_DESELECT_ALL,OnDeSelectAll)
END_EVENT_TABLE()


CFilterDialog::CFilterDialog()
:wxDialog(NULL,wxID_ANY, GetMsg(MSG_FILTER), wxDefaultPosition, wxDefaultSize )
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
	
 	Sizer->Add(GetPanel(this),0,wxALL|wxEXPAND,5);
	Sizer->Add(GetButtonPanel(this),0,wxALL|wxEXPAND,5);
	
	Sizer->SetSizeHints(this);
	Center();
		
}	

CFilterDialog::~CFilterDialog(void)
{
	
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


wxPanel *CFilterDialog::GetPanel(wxWindow *Parent)
{
	void *db = DBConnect();
	
	if(db == NULL)
		return NULL;

	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
	wxStaticBoxSizer *Sizer1 = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_FILTER));
	Sizer->Add(Sizer1,1,wxALL|wxEXPAND,0);

	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	Sizer1->Add(FlexSizer,1,wxALL|wxEXPAND,0);
		
	//m_CheckInMonitoring = new wxCheckBox(Panel,wxID_ANY,GetMsg(MSG_IN_MONITORING));
	//FlexSizer->AddSpacer(1);
	//FlexSizer->Add(m_CheckInMonitoring,0,wxALL,5);

	wxStaticText *LabelAlarm = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_BASE_STATION));
	FlexSizer->Add(LabelAlarm,0,wxALL,5);
	m_ComboAlarm = GetCombo(db,Panel,TABLE_ALARM,wxEmptyString,FI_ALARM_ID,FI_ALARM_NAME, true);
	m_ComboAlarm->SetSelection(0);
	FlexSizer->Add(m_ComboAlarm,0,wxALL|wxEXPAND,5);
	
	wxStaticText *LabelGroup = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SYMBOL_GROUP));
	FlexSizer->Add(LabelGroup,0,wxALL,5);
	m_ComboGroup = GetCombo(db,Panel,TABLE_SYMBOL_GROUP,wxEmptyString,FI_SYMBOL_GROUP_ID,FI_SYMBOL_GROUP_NAME, true);
	m_ComboGroup->SetSelection(0);
	FlexSizer->Add(m_ComboGroup,0,wxALL|wxEXPAND,5);

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
	
	wxStaticText *LabelBaseStation = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_BASE_STATION));
	FlexSizer->Add(LabelBaseStation,0,wxALL,5);
	m_ComboBaseStation = GetCombo(db,Panel,TABLE_BASE_STATION,wxEmptyString,FI_BASE_STATION_ID,FI_BASE_STATION_NAME, true);
	m_ComboBaseStation->SetSelection(0);
	FlexSizer->Add(m_ComboBaseStation,0,wxALL|wxEXPAND,5);

	wxStaticText *LabelArea = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_AREA));
	FlexSizer->Add(LabelArea,0,wxALL,5);
	m_ComboArea = GetCombo(db,Panel,TABLE_AREA,wxEmptyString,FI_AREA_ID,FI_AREA_NAME, true);
	m_ComboArea->SetSelection(0);
	FlexSizer->Add(m_ComboArea,0,wxALL|wxEXPAND,5);
	
	wxStaticText *LabelSeaway = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SEAWAY));
	FlexSizer->Add(LabelSeaway,0,wxALL,5);
	m_ComboSeaway = GetCombo(db,Panel,TABLE_SEAWAY,wxEmptyString,FI_SEAWAY_ID,FI_SEAWAY_NAME, true);
	m_ComboSeaway->SetSelection(0);
	FlexSizer->Add(m_ComboSeaway,0,wxALL|wxEXPAND,5);
	
	wxStaticText *LabelSymbolType = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SYMBOL_TYPE));
	FlexSizer->Add(LabelSymbolType,0,wxALL,5);
	m_ComboSymbolType = GetCombo(db,Panel,TABLE_SYMBOL_TYPE,wxEmptyString,FI_SYMBOL_TYPE_ID,FI_SYMBOL_TYPE_NAME, true);
	m_ComboSymbolType->SetSelection(0);
	FlexSizer->Add(m_ComboSymbolType,0,wxALL|wxEXPAND,5);

	DBClose(db);

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
	ComboSetSelection(m_ComboAlarm,v);
}

void CFilterDialog::SetAreaId(int v)
{
	ComboSetSelection(m_ComboArea,v);
}

void CFilterDialog::SetSymbolTypeId(int v)
{
	ComboSetSelection(m_ComboSymbolType,v);
}

void CFilterDialog::SetBaseStationId(int v)
{
	ComboSetSelection(m_ComboBaseStation,v);
}

void CFilterDialog::SetSeawayId(int v)
{
	ComboSetSelection(m_ComboSeaway,v);
}

void CFilterDialog::SetInMonitoring(int v)
{
	m_ComboInMonitoring->SetSelection(v + 1);
}

void CFilterDialog::SetLight(int v)
{
	m_ComboLight->SetSelection(v + 1);
}

void CFilterDialog::SetGroupId(int v)
{
	ComboSetSelection(m_ComboGroup,v);
}
