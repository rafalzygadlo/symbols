#include "light_new.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "color.h"
#include "picker.h"

CLightNew::CLightNew()
	:wxDialog(NULL,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
			
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Sizer->Add(Panel,1,wxALL|wxEXPAND,5);
	wxFlexGridSizer *FlexGridSizer = new wxFlexGridSizer(3);
	FlexGridSizer->AddGrowableCol(1);
	Panel->SetSizer(FlexGridSizer);
	
	wxStaticText *LabelColor = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_COLOR));
	FlexGridSizer->Add(LabelColor,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	CColorPanel *Color = new CColorPanel(Panel,this);
	FlexGridSizer->Add(Color,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);
			
	wxStaticText *LabelBattery = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_BATTERY));
	FlexGridSizer->Add(LabelBattery,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	CPickerPanel *Battery = new CPickerPanel(Panel,this);
	FlexGridSizer->Add(Battery,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);
	
	wxStaticText *LabelCommunication = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_COMMUNICATION_TYPE));
	FlexGridSizer->Add(LabelCommunication,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	CPickerPanel *Communication = new CPickerPanel(Panel,this);
	FlexGridSizer->Add(Communication,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);
		
	wxStaticText *LabelName = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_NAME));
	FlexGridSizer->Add(LabelName,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextName = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	FlexGridSizer->Add(m_TextName,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);
	
	wxStaticText *LabelFlash = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_NAME));	//b�yskacz
	FlexGridSizer->Add(LabelFlash,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextFlash = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	FlexGridSizer->Add(m_TextFlash,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);
		
	
	
	wxStaticText *LabelInfo = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_INFO));
	FlexGridSizer->Add(LabelInfo,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextInfo = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(310,80),wxTE_MULTILINE);
	FlexGridSizer->Add(m_TextInfo,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);
	



	FlexGridSizer->AddSpacer(1);
	//FlexGridSizer->AddSpacer(1);
	
	wxPanel *Panel1 = new wxPanel(this);
	Sizer->Add(Panel1,0,wxALL|wxEXPAND,5);
	wxBoxSizer *Panel1Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel1->SetSizer(Panel1Sizer);

	Panel1Sizer->AddStretchSpacer();

	wxButton *ButtonOk = new wxButton(Panel1,wxID_OK,GetMsg(MSG_OK));
	Panel1Sizer->Add(ButtonOk,0,wxALL,5);

	wxButton *ButtonCancel = new wxButton(Panel1,wxID_CANCEL,GetMsg(MSG_CANCEL));
	Panel1Sizer->Add(ButtonCancel,0,wxALL,5);
	

	this->Fit();
	Center();
	
}

CLightNew::~CLightNew()
{

}

bool CLightNew::Validate()
{
	wxString err;
	bool result = true;
		
	if(m_TextName->GetValue().empty())
	{
		result = false;
		err << GetMsg(MSG_NAME_EMPTY) << "\n";
	}
	
	if(!result)
	{
		wxMessageBox(err);
		return false;
	}
	
	
	return true;
}


wxString CLightNew::GetName()
{
	return m_TextName->GetValue();
}

wxString CLightNew::GetInfo()
{
	return m_TextInfo->GetValue();
}

//SET
void CLightNew::SetName(wxString v)
{
	m_TextName->SetValue(v);
}

void CLightNew::SetInfo(wxString v)
{
	m_TextInfo->SetValue(v);
}
