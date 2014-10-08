#include "new.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "color.h"
#include "picker.h"
#include <wx/choicebk.h>

BEGIN_EVENT_TABLE(CNew,wxDialog)
	EVT_COMBOBOX(ID_ITEM_TYPE,OnComboItem)
END_EVENT_TABLE()


CNew::CNew(int type, int id_type)
	:wxDialog(NULL,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize)
{
	m_IdType = id_type;
	m_FeaturePanel = NULL;
	m_TextValidator.SetStyle(wxFILTER_EXCLUDE_CHAR_LIST);
	m_TextValidator.SetCharExcludes(_("'\"\\;?"));

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
		case CONTROL_ITEM:	EditItemPanel();	break;
		case CONTROL_LIGHT:	LightPanel();		break;
		case CONTROL_AREA:	
		case CONTROL_SEAWAY:
			EditNamePanel();	break;

	}
}

wxPanel *CNew::GetItemFeaturePanel(wxWindow *Parent)
{
	wxFlexGridSizer *Sizer = new wxFlexGridSizer(2);
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	Panel->SetBackgroundColour(*wxWHITE);
	Panel->SetSizer(Sizer);
	
	wxString sql = wxString::Format(_("SELECT * FROM `%s`,`%s` WHERE %s.id_type = '%d' AND `%s`.id = `%s`.id_feature ORDER BY name"),TABLE_ITEM_FEATURE, TABLE_ITEM_TYPE_FEATURE ,TABLE_ITEM_TYPE_FEATURE, m_IdType,TABLE_ITEM_FEATURE, TABLE_ITEM_TYPE_FEATURE );
	if(!my_query(sql))
		return Panel;
	
	int rows = 0;
	void *result = db_result();
	char **row;
		
	int i = 0;
	while(row = (char**)db_fetch_row(result))
	{
		wxStaticText *Label = new wxStaticText(Panel,wxID_ANY,Convert(row[FI_ITEM_FEATURE_NAME]));
		Sizer->Add(Label,0,wxALL,5);
		wxTextCtrl *Text = new wxTextCtrl(Panel,wxID_ANY);
		Sizer->Add(Text,0,wxALL|wxEXPAND,5);
		
	}
	
	return Panel;

}

wxComboBox *CNew::GetComboItemType(wxWindow *Parent)
{
	wxComboBox *ptr = new wxComboBox(Parent,ID_ITEM_TYPE,wxEmptyString,wxDefaultPosition,wxDefaultSize,NULL,0, wxCB_READONLY);
	wxString sql = wxString::Format(_("SELECT * FROM `%s` ORDER BY name"),TABLE_ITEM_TYPE);
	if(!my_query(sql))
		return ptr;
	
	
	int rows = 0;
	void *result = db_result();
	char **row;
		
	int i = 0;
	while(row = (char**)db_fetch_row(result))
	{
		wxString name(row[FI_ITEM_TYPE_NAME],wxConvUTF8);
		int id = ptr->Append(name);
		int rid = atoi(row[FI_ITEM_TYPE_ID]);
		if(m_IdType == rid)
			ptr->SetSelection(id);
		ptr->SetClientData(id,(int*)rid);
	}
		
	db_free_result(result);
	return ptr;
}


wxPanel *CNew::EditItemPanel()
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);

	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Sizer->Add(Panel,1,wxALL|wxEXPAND,5);
	wxFlexGridSizer *FlexGridSizer = new wxFlexGridSizer(3);
	FlexGridSizer->AddGrowableCol(1);
	Panel->SetSizer(FlexGridSizer);
	
	wxStaticText *LabelItemType = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_ITEM_TYPE));
	FlexGridSizer->Add(LabelItemType,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	
	m_ComboItemType =  GetComboItemType(Panel);
	FlexGridSizer->Add(m_ComboItemType,0,wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);

	wxStaticText *LabelName = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_NAME));
	FlexGridSizer->Add(LabelName,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextName = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	FlexGridSizer->Add(m_TextName,0,wxALL|wxEXPAND,5);
	m_TextName->SetValidator(m_TextValidator);
	FlexGridSizer->AddSpacer(1);

	wxStaticText *LabelType = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_TYPE));
	FlexGridSizer->Add(LabelType,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextType = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	FlexGridSizer->Add(m_TextType,0,wxALL|wxEXPAND,5);
	m_TextType->SetValidator(m_TextValidator);
	FlexGridSizer->AddSpacer(1);
	
	wxStaticText *LabelInfo = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_INFO));
	FlexGridSizer->Add(LabelInfo,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextInfo = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(300,80),wxTE_MULTILINE);
	m_TextInfo->SetValidator(m_TextValidator);
	FlexGridSizer->Add(m_TextInfo,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);
	
	// feature
	m_ItemSizer = new wxBoxSizer(wxVERTICAL);
	Sizer->Add(m_ItemSizer,0,wxALL|wxEXPAND,0);
	//m_FeaturePanel = GetItemFeaturePanel(this);
	//m_ItemSizer->Add(m_FeaturePanel);
	

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


wxPanel *CNew::LightPanel()
{

	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
	
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Sizer->Add(Panel,0,wxALL|wxEXPAND,5);
	wxBoxSizer *BoxSizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(BoxSizer);
	
	//wxStaticText *LabelColor = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_COLOR));
	//FlexGridSizer->Add(LabelColor,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	CColorPanel *Color = new CColorPanel(Panel,this);
	BoxSizer->Add(Color,0,wxALL|wxEXPAND,5);
	//FlexGridSizer->AddSpacer(1);

	CPickerPanel *BulbPicker = new CPickerPanel(Panel,this,-1,wxEmptyString);
	BoxSizer->Add(BulbPicker,0,wxALL|wxEXPAND);
		
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


void CNew::OnComboItem(wxCommandEvent &event)
{
	int id = event.GetSelection();

	m_IdType = (int)m_ComboItemType->GetClientData(id);

	if(m_FeaturePanel != NULL)
	{	
		m_ItemSizer->Detach(m_FeaturePanel);
		delete m_FeaturePanel;
	}
	
	m_FeaturePanel = GetItemFeaturePanel(this);
	m_ItemSizer->Add(m_FeaturePanel,0,wxALL|wxEXPAND,5);
	this->Layout();
	this->GetSizer()->SetSizeHints(this);

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

int CNew::GetItemType()
{
	return	(int)m_ComboItemType->GetClientData(m_ComboItemType->GetSelection());
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