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
	:wxDialog(NULL,wxID_ANY, _(PRODUCT_NAME), wxDefaultPosition, wxDefaultSize )
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
	
 	Sizer->Add(GetPanel(this),0,wxALL|wxEXPAND,5);
	

	//m_ButtonSelect = new wxButton(this,ID_SELECT_ALL,GetMsg(MSG_SELECT_ALL),wxDefaultPosition,wxDefaultSize);
	//m_MainSizer->Add(m_ButtonSelect,0,wxALL,5);

	wxButton *ButtonClose = new wxButton(this,wxID_OK,GetMsg(MSG_CLOSE),wxDefaultPosition,wxDefaultSize);
	Sizer->Add(ButtonClose,0,wxALL|wxALIGN_RIGHT,5);



	Sizer->SetSizeHints(this);
	Center();
		
}	

CFilterDialog::~CFilterDialog(void)
{
	
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

	wxCheckBox *CheckOnPosition = new wxCheckBox(Panel,wxID_ANY,GetMsg(MSG_ON_POSITION));
	FlexSizer->AddSpacer(1);
	FlexSizer->Add(CheckOnPosition,0,wxALL,2);
	
	wxCheckBox *CheckInMOnitoring = new wxCheckBox(Panel,wxID_ANY,GetMsg(MSG_IN_MONITORING));
	FlexSizer->AddSpacer(1);
	FlexSizer->Add(CheckInMOnitoring,0,wxALL,2);
		
	wxStaticText *LabelArea = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_AREA));
	FlexSizer->Add(LabelArea,0,wxALL,2);
	m_ComboArea = GetCombo(db,Panel,TABLE_AREA,wxEmptyString,FI_AREA_ID,FI_AREA_NAME, true);
	m_ComboArea->SetSelection(0);
	FlexSizer->Add(m_ComboArea,0,wxALL|wxEXPAND,2);
	
	wxStaticText *LabelSeaway = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SEAWAY));
	FlexSizer->Add(LabelSeaway,0,wxALL,2);
	m_ComboSeaway = GetCombo(db,Panel,TABLE_SEAWAY,wxEmptyString,FI_SEAWAY_ID,FI_SEAWAY_NAME, true);
	m_ComboSeaway->SetSelection(0);
	FlexSizer->Add(m_ComboSeaway,0,wxALL|wxEXPAND,2);
	
	wxStaticText *LabelSymbolType = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SYMBOL_TYPE));
	FlexSizer->Add(LabelSymbolType,0,wxALL,2);
	m_ComboSymbolType = GetCombo(db,Panel,TABLE_SYMBOL_TYPE,wxEmptyString,FI_SYMBOL_TYPE_ID,FI_SYMBOL_TYPE_NAME, true);
	m_ComboSymbolType->SetSelection(0);
	FlexSizer->Add(m_ComboSymbolType,0,wxALL|wxEXPAND,2);

	DBClose(db);

	return Panel;
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

void CFilterDialog::Set(int id, bool checked)
{

}

