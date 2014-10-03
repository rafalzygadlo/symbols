#include "new.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "color.h"
#include "picker.h"
#include <wx/choicebk.h>


CNew::CNew(int type)
	:wxDialog(NULL,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize)
{
	
	m_Exclude = _("'\"\\;?");

	m_TextValidator.SetStyle(wxFILTER_EXCLUDE_CHAR_LIST);
	m_TextValidator.SetCharExcludes(m_Exclude);

	GetPanel(type);
	Fit();
	Center();
	
}

CNew::~CNew()
{

}

void CNew::GetPanel(int type)
{
	switch(type)
	{
		case CONTROL_AREA:			
		case CONTROL_COMMUNICATION:	
		case CONTROL_SYMBOL_TYPE:	
		case CONTROL_SEAWAY:		
			EditNamePanel();	
		break;
		
		case CONTROL_FLASH:			
		case CONTROL_LANTERN:		
		case CONTROL_CHANGER:		
		case CONTROL_SOLAR:			
		case CONTROL_REGULATOR:		
		case CONTROL_AC_ADAPTER:	
		case CONTROL_SYNCHRONIZATION:
		case CONTROL_TELEMETRY:
		case CONTROL_COLLECTION:
		case CONTROL_ANTENNA:
		case CONTROL_LIGHTNING:
		case CONTROL_WIND_GENERATOR:
		case CONTROL_NAUTOFON:
			EditTypePanel();	
		break;

		case CONTROL_BATTERY:		BatteryPanel();		break;
		case CONTROL_LIGHT:			LightPanel();		break;
		case CONTROL_BULB:			BulbPanel();		break;

	}
}

wxPanel *CNew::EditTypePanel()
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
			
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Sizer->Add(Panel,1,wxALL|wxEXPAND,5);
	wxFlexGridSizer *FlexGridSizer = new wxFlexGridSizer(3);
	FlexGridSizer->AddGrowableCol(1);
	Panel->SetSizer(FlexGridSizer);
	
	wxStaticText *LabelName = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_TYPE));
	FlexGridSizer->Add(LabelName,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextType = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	m_TextType->SetValidator(m_TextValidator);

	FlexGridSizer->Add(m_TextType,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);
	
	wxStaticText *LabelInfo = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_INFO));
	FlexGridSizer->Add(LabelInfo,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextInfo = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(300,80),wxTE_MULTILINE);
	m_TextInfo->SetValidator(m_TextValidator);
	FlexGridSizer->Add(m_TextInfo,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);
	
	wxPanel *Panel1 = new wxPanel(this);
	Sizer->Add(Panel1,0,wxALL|wxEXPAND,5);
	wxBoxSizer *Panel1Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel1->SetSizer(Panel1Sizer);

	Panel1Sizer->AddStretchSpacer();

	wxButton *ButtonOk = new wxButton(Panel1,wxID_OK,GetMsg(MSG_OK));
	Panel1Sizer->Add(ButtonOk,0,wxALL,5);

	wxButton *ButtonCancel = new wxButton(Panel1,wxID_CANCEL,GetMsg(MSG_CANCEL));
	Panel1Sizer->Add(ButtonCancel,0,wxALL,5);
	
	return Panel;
	
}


wxPanel *CNew::EditNamePanel()
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
			
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Sizer->Add(Panel,1,wxALL|wxEXPAND,5);
	wxFlexGridSizer *FlexGridSizer = new wxFlexGridSizer(3);
	FlexGridSizer->AddGrowableCol(1);
	Panel->SetSizer(FlexGridSizer);
	
	wxStaticText *LabelName = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_NAME));
	FlexGridSizer->Add(LabelName,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextName = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	m_TextName->SetValidator(m_TextValidator);

	FlexGridSizer->Add(m_TextName,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);
	
	wxStaticText *LabelInfo = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_INFO));
	FlexGridSizer->Add(LabelInfo,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextInfo = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(300,80),wxTE_MULTILINE);
	m_TextInfo->SetValidator(m_TextValidator);
	FlexGridSizer->Add(m_TextInfo,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);
	
	wxPanel *Panel1 = new wxPanel(this);
	Sizer->Add(Panel1,0,wxALL|wxEXPAND,5);
	wxBoxSizer *Panel1Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel1->SetSizer(Panel1Sizer);

	Panel1Sizer->AddStretchSpacer();

	wxButton *ButtonOk = new wxButton(Panel1,wxID_OK,GetMsg(MSG_OK));
	Panel1Sizer->Add(ButtonOk,0,wxALL,5);

	wxButton *ButtonCancel = new wxButton(Panel1,wxID_CANCEL,GetMsg(MSG_CANCEL));
	Panel1Sizer->Add(ButtonCancel,0,wxALL,5);
	
	return Panel;
	
}


wxPanel *CNew::BatteryPanel()
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
			
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Sizer->Add(Panel,1,wxALL|wxEXPAND,5);
	wxFlexGridSizer *FlexGridSizer = new wxFlexGridSizer(3);
	FlexGridSizer->AddGrowableCol(1);
	Panel->SetSizer(FlexGridSizer);
		
	wxStaticText *LabelType = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_TYPE));
	FlexGridSizer->Add(LabelType,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextType = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	m_TextType->SetValidator(m_TextValidator);

	FlexGridSizer->Add(m_TextType,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);

	wxStaticText *LabelCapacity = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_CAPACITY));
	FlexGridSizer->Add(LabelCapacity,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextCapacity = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	m_TextCapacity->SetValidator(m_TextValidator);
	FlexGridSizer->Add(m_TextCapacity,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);

	
	wxStaticText *LabelInfo = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_INFO));
	FlexGridSizer->Add(LabelInfo,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextInfo = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(300,80),wxTE_MULTILINE);
	m_TextInfo->SetValidator(m_TextValidator);
	FlexGridSizer->Add(m_TextInfo,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);
	
	wxPanel *Panel1 = new wxPanel(this);
	Sizer->Add(Panel1,0,wxALL|wxEXPAND,5);
	wxBoxSizer *Panel1Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel1->SetSizer(Panel1Sizer);

	Panel1Sizer->AddStretchSpacer();

	wxButton *ButtonOk = new wxButton(Panel1,wxID_OK,GetMsg(MSG_OK));
	Panel1Sizer->Add(ButtonOk,0,wxALL,5);

	wxButton *ButtonCancel = new wxButton(Panel1,wxID_CANCEL,GetMsg(MSG_CANCEL));
	Panel1Sizer->Add(ButtonCancel,0,wxALL,5);
	
	return Panel;

}

wxPanel *CNew::LightPanel()
{

	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
	
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Sizer->Add(Panel,0,wxALL|wxEXPAND,5);
	wxGridSizer *FlexGridSizer = new wxGridSizer(2);
	Panel->SetSizer(FlexGridSizer);
	
	//wxStaticText *LabelColor = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_COLOR));
	//FlexGridSizer->Add(LabelColor,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	CColorPanel *Color = new CColorPanel(Panel,this);
	FlexGridSizer->Add(Color,0,wxALL|wxEXPAND,5);
	//FlexGridSizer->AddSpacer(1);

	wxChoicebook *Book = new wxChoicebook(this,wxID_ANY);
	Sizer->Add(Book,0,wxALL|wxEXPAND,5);

	CPickerPanel *Battery = new CPickerPanel(Book,this,CONTROL_BATTERY,GetMsg(MSG_BATTERY));
	Book->AddPage(Battery,GetMsg(MSG_BATTERY));
	
	CPickerPanel *Bulb = new CPickerPanel(Book,this,CONTROL_BULB,GetMsg(MSG_BULB));
	Book->AddPage(Bulb,GetMsg(MSG_BULB));
		
	CPickerPanel *Flash = new CPickerPanel(Book,this,CONTROL_FLASH,GetMsg(MSG_FLASH));
	Book->AddPage(Flash,GetMsg(MSG_FLASH));
	
	CPickerPanel *Lantern = new CPickerPanel(Book,this,CONTROL_LANTERN,GetMsg(MSG_LANTERN));
	Book->AddPage(Lantern,GetMsg(MSG_LANTERN));
	
	CPickerPanel *Changer = new CPickerPanel(Book,this,CONTROL_CHANGER,GetMsg(MSG_CHANGER));
	Book->AddPage(Changer,GetMsg(MSG_CHANGER));

	CPickerPanel *Solar = new CPickerPanel(Book,this,CONTROL_SOLAR,GetMsg(MSG_SOLAR));
	Book->AddPage(Solar,GetMsg(MSG_SOLAR));

	CPickerPanel *ACAdapter = new CPickerPanel(Book,this,CONTROL_AC_ADAPTER,GetMsg(MSG_AC_ADAPTER));
	Book->AddPage(ACAdapter,GetMsg(MSG_AC_ADAPTER));

	CPickerPanel *Regulator = new CPickerPanel(Book,this,CONTROL_REGULATOR,GetMsg(MSG_REGULATOR));
	Book->AddPage(Regulator,GetMsg(MSG_REGULATOR));

	CPickerPanel *Telemetry = new CPickerPanel(Book,this,CONTROL_TELEMETRY,GetMsg(MSG_TELEMETRY_MODULE));
	Book->AddPage(Telemetry,GetMsg(MSG_TELEMETRY_MODULE));
	
	CPickerPanel *Collection = new CPickerPanel(Book,this,CONTROL_COLLECTION,GetMsg(MSG_COLLECTION_MODULE));
	Book->AddPage(Collection,GetMsg(MSG_COLLECTION_MODULE));
	
	CPickerPanel *Communication = new CPickerPanel(Book,this,CONTROL_COMMUNICATION,GetMsg(MSG_COMMUNICATION_TYPE));
	Book->AddPage(Communication,GetMsg(MSG_COMMUNICATION_TYPE));

	CPickerPanel *Synchronization = new CPickerPanel(Book,this,CONTROL_SYNCHRONIZATION,GetMsg(MSG_SYNCHRONIZATION));
	Book->AddPage(Synchronization,GetMsg(MSG_SYNCHRONIZATION));

	CPickerPanel *Antenna = new CPickerPanel(Book,this,CONTROL_ANTENNA,GetMsg(MSG_ANTENNA));
	Book->AddPage(Antenna,GetMsg(MSG_ANTENNA));
	
	wxBoxSizer *s = new wxBoxSizer(wxVERTICAL);
	Sizer->Add(s);

	wxStaticText *LabelName = new wxStaticText(this,wxID_ANY,GetMsg(MSG_NAME));
	s->Add(LabelName,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextName = new wxTextCtrl(this,wxID_ANY,wxEmptyString);
	m_TextName->SetValidator(m_TextValidator);
	s->Add(m_TextName,0,wxALL|wxEXPAND,5);
	//FlexGridSizer->AddSpacer(1);
			
	wxStaticText *LabelInfo = new wxStaticText(this,wxID_ANY,GetMsg(MSG_INFO));
	s->Add(LabelInfo,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextInfo = new wxTextCtrl(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(310,80),wxTE_MULTILINE);
	m_TextInfo->SetValidator(m_TextValidator);
	s->Add(m_TextInfo,0,wxALL|wxEXPAND,5);
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
	
	return Panel;
}

wxPanel *CNew::BulbPanel()
{
	
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
			
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Sizer->Add(Panel,1,wxALL|wxEXPAND,5);
	wxFlexGridSizer *FlexGridSizer = new wxFlexGridSizer(3);
	FlexGridSizer->AddGrowableCol(1);
	Panel->SetSizer(FlexGridSizer);
	
	wxStaticText *LabelType = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_TYPE));
	FlexGridSizer->Add(LabelType,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextType = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	m_TextType->SetValidator(m_TextValidator);
	FlexGridSizer->Add(m_TextType,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);

	wxStaticText *LabelVoltage = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_VOLTAGE));
	FlexGridSizer->Add(LabelVoltage,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextVoltage = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	m_TextVoltage->SetValidator(m_TextValidator);
	FlexGridSizer->Add(m_TextVoltage,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);

	wxStaticText *LabelPower = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_POWER));
	FlexGridSizer->Add(LabelPower,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextPower = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	m_TextPower->SetValidator(m_TextValidator);
	FlexGridSizer->Add(m_TextPower,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);

	
	wxStaticText *LabelInfo = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_INFO));
	FlexGridSizer->Add(LabelInfo,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextInfo = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(300,80),wxTE_MULTILINE);
	m_TextInfo->SetValidator(m_TextValidator);
	FlexGridSizer->Add(m_TextInfo,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);
			
	
	wxPanel *Panel1 = new wxPanel(this);
	Sizer->Add(Panel1,0,wxALL|wxEXPAND,5);
	wxBoxSizer *Panel1Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel1->SetSizer(Panel1Sizer);

	Panel1Sizer->AddStretchSpacer();

	wxButton *ButtonOk = new wxButton(Panel1,wxID_OK,GetMsg(MSG_OK));
	Panel1Sizer->Add(ButtonOk,0,wxALL,5);

	wxButton *ButtonCancel = new wxButton(Panel1,wxID_CANCEL,GetMsg(MSG_CANCEL));
	Panel1Sizer->Add(ButtonCancel,0,wxALL,5);
	
	return Panel;
	
}



bool CNew::Validate()
{

	return true;
	
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


wxString CNew::GetName()
{
	return m_TextName->GetValue();
}

wxString CNew::GetInfo()
{
	return m_TextInfo->GetValue();
}

wxString CNew::GetType()
{
	return m_TextType->GetValue();
}

wxString CNew::GetCapacity()
{
	return m_TextCapacity->GetValue();
}

wxString CNew::GetVoltage()
{
	return m_TextVoltage->GetValue();
}

wxString CNew::GetPower()
{
	return m_TextPower->GetValue();
}


//SET
void CNew::SetName(wxString v)
{
	m_TextName->SetValue(v);
}

void CNew::SetInfo(wxString v)
{
	m_TextInfo->SetValue(v);
}

void CNew::SetType(wxString v)
{
	m_TextType->SetValue(v);
}

void CNew::SetCapacity(wxString v)
{
	m_TextCapacity->SetValue(v);
}

void CNew::SetVoltage(wxString v)
{
	m_TextVoltage->SetValue(v);
}

void CNew::SetPower(wxString v)
{
	m_TextPower->SetValue(v);
}