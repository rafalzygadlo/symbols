#include "new.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "color.h"
#include "dialog.h"
#include <wx/choicebk.h>

BEGIN_EVENT_TABLE(CNew,wxDialog)
	EVT_COMBOBOX(ID_ITEM_TYPE,OnComboItem)
	EVT_COMBOBOX(ID_FILTER,OnComboFilter)
END_EVENT_TABLE()


CNew::CNew(int type, int id_type, wxString item_id, bool edit)
	:wxDialog(NULL,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize)
{
	m_IdType = id_type;
	m_ItemId = item_id;
	m_Edit = edit;
//	m_FeaturePanel = NULL;
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
		case CONTROL_ITEM:			EditItemPanel();	break;
		case CONTROL_LIGHT:
		case CONTROL_AREA:	
		case CONTROL_SEAWAY:
		case CONTROL_SYMBOL_TYPE:
			EditNamePanel();	break;

	}
}

void CNew::GetItemFeaturePanel(wxWindow *Parent)
{
	wxString sql = wxString::Format(_("SELECT * FROM `%s`,`%s` WHERE %s.id_type = '%d' AND `%s`.id = `%s`.id_feature ORDER BY name"),TABLE_ITEM_FEATURE, TABLE_ITEM_TYPE_FEATURE ,TABLE_ITEM_TYPE_FEATURE, m_IdType,TABLE_ITEM_FEATURE, TABLE_ITEM_TYPE_FEATURE );
	if(!my_query(sql))
		return;
	
	int rows = 0;
	void *result = db_result();
	char **row;
		
	int i = 0;
	while(row = (char**)db_fetch_row(result))
	{
		wxStaticText *Label = new wxStaticText(Parent,wxID_ANY,Convert(row[FI_ITEM_FEATURE_NAME]));
		m_FlexGridSizer->Add(Label,0,wxALL,5);
		wxTextCtrl *Text = new wxTextCtrl(Parent,wxID_ANY);
		Text->SetClientData((void*)atoi(row[FI_ITEM_FEATURE_ID]));
		m_FlexGridSizer->Add(Text,0,wxALL|wxEXPAND,5);
		m_Controls.Add(Label);
		m_Controls.Add(Text);
		m_Ids.Add(Text);
	}
	
	db_free_result(result);


	for(size_t i = 0; i < m_Ids.size(); i++)
	{
		wxTextCtrl *txt = (wxTextCtrl*)m_Ids.Item(i);
		sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_item = '%s' AND id_feature = '%d'"),TABLE_ITEM_VALUE,m_ItemId,(int)txt->GetClientData());
		my_query(sql);

		void *result = db_result();
		char **row = (char**)db_fetch_row(result);
		
		if(row)
			txt->SetValue(Convert(row[FI_ITEM_VALUE_VALUE]));

		db_free_result(result);	
	
	}


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
	bool selected = false;

	int counter = 0;
	while(row = (char**)db_fetch_row(result))
	{
		wxString name(row[FI_ITEM_TYPE_NAME],wxConvUTF8);
		int id = ptr->Append(name);
		int rid = atoi(row[FI_ITEM_TYPE_ID]);
		if(m_IdType == rid)
		{
			ptr->SetSelection(id);
			selected = true;
		}
		ptr->SetClientData(id,(int*)rid);
		counter++;
	}
		
	if(!selected && counter > 0)
	{
		m_IdType = (int)ptr->GetClientData(0);
		ptr->SetSelection(0);
		
	}
	
	db_free_result(result);
	return ptr;
}

wxPanel *CNew::EditItemPanel()
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);

	m_Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	m_Panel->SetBackgroundColour(*wxWHITE);
	Sizer->Add(m_Panel,1,wxALL|wxEXPAND,0);
	m_FlexGridSizer = new wxFlexGridSizer(2);
	m_FlexGridSizer->AddGrowableCol(1);
	m_Panel->SetSizer(m_FlexGridSizer);
	
	wxStaticText *LabelItemType = new wxStaticText(m_Panel,wxID_ANY,GetMsg(MSG_ITEM_TYPE));
	m_FlexGridSizer->Add(LabelItemType,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	
	m_ComboItemType =  GetComboItemType(m_Panel);
	m_FlexGridSizer->Add(m_ComboItemType,0,wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND,5);
	m_ComboItemType->Enable(!m_Edit);
	
	wxStaticText *LabelName = new wxStaticText(m_Panel,wxID_ANY,GetMsg(MSG_NAME));
	m_FlexGridSizer->Add(LabelName,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextName = new wxTextCtrl(m_Panel,wxID_ANY,wxEmptyString);
	m_FlexGridSizer->Add(m_TextName,0,wxALL|wxEXPAND,5);
	m_TextName->SetValidator(m_TextValidator);
	
	wxStaticText *LabelType = new wxStaticText(m_Panel,wxID_ANY,GetMsg(MSG_TYPE));
	m_FlexGridSizer->Add(LabelType,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextType = new wxTextCtrl(m_Panel,wxID_ANY,wxEmptyString);
	m_FlexGridSizer->Add(m_TextType,0,wxALL|wxEXPAND,5);
	m_TextType->SetValidator(m_TextValidator);
		
	wxStaticText *LabelInfo = new wxStaticText(m_Panel,wxID_ANY,GetMsg(MSG_INFO));
	m_FlexGridSizer->Add(LabelInfo,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextInfo = new wxTextCtrl(m_Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(300,80),wxTE_MULTILINE);
	m_TextInfo->SetValidator(m_TextValidator);
	m_FlexGridSizer->Add(m_TextInfo,0,wxALL|wxEXPAND,5);
	

	GetItemFeaturePanel(m_Panel);


	wxPanel *Panel1 = new wxPanel(this);
	Sizer->Add(Panel1,0,wxALL|wxEXPAND,5);
	wxBoxSizer *Panel1Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel1->SetSizer(Panel1Sizer);

	Panel1Sizer->AddStretchSpacer();

	wxButton *ButtonOk = new wxButton(Panel1,wxID_OK,GetMsg(MSG_OK));
	Panel1Sizer->Add(ButtonOk,0,wxALL,5);

	wxButton *ButtonCancel = new wxButton(Panel1,wxID_CANCEL,GetMsg(MSG_CANCEL));
	Panel1Sizer->Add(ButtonCancel,0,wxALL,5);
	
	return m_Panel;
	
}


wxPanel *CNew::EditTypePanel()
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
			
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Panel->SetBackgroundColour(*wxWHITE);
	Sizer->Add(Panel,1,wxALL|wxEXPAND,0);
	wxFlexGridSizer *FlexGridSizer = new wxFlexGridSizer(2);
	FlexGridSizer->AddGrowableCol(1);
	Panel->SetSizer(FlexGridSizer);
	
	wxStaticText *LabelName = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_TYPE));
	FlexGridSizer->Add(LabelName,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextType = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	FlexGridSizer->Add(m_TextType,0,wxALL|wxEXPAND,5);
	m_TextType->SetValidator(m_TextValidator);
		
	wxStaticText *LabelInfo = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_INFO));
	FlexGridSizer->Add(LabelInfo,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextInfo = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(300,80),wxTE_MULTILINE);
	FlexGridSizer->Add(m_TextInfo,0,wxALL|wxEXPAND,5);
	m_TextInfo->SetValidator(m_TextValidator);
		
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
	Panel->SetBackgroundColour(*wxWHITE);
	Sizer->Add(Panel,1,wxALL|wxEXPAND,0);
	wxFlexGridSizer *FlexGridSizer = new wxFlexGridSizer(2);
	FlexGridSizer->AddGrowableCol(1);
	Panel->SetSizer(FlexGridSizer);
	
	wxStaticText *LabelName = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_NAME));
	FlexGridSizer->Add(LabelName,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextName = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	m_TextName->SetValidator(m_TextValidator);
	FlexGridSizer->Add(m_TextName,0,wxALL|wxEXPAND,5);
		
	wxStaticText *LabelInfo = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_INFO));
	FlexGridSizer->Add(LabelInfo,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextInfo = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(300,80),wxTE_MULTILINE);
	m_TextInfo->SetValidator(m_TextValidator);
	FlexGridSizer->Add(m_TextInfo,0,wxALL|wxEXPAND,5);
		
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

	for(size_t i = 0; i < m_Controls.size(); i++)
	{
		wxWindow *wnd = (wxWindow*)m_Controls.Item(i);
		m_FlexGridSizer->Detach(wnd);
		
		delete wnd;
	}
	
	m_Controls.Clear();
	m_Ids.Clear();
	GetItemFeaturePanel(m_Panel);
	this->Layout();
	this->GetSizer()->SetSizeHints(this);

}

void CNew::OnComboFilter(wxCommandEvent &event)
{
	int id = event.GetSelection();
	m_ListBox->Clear();

	m_IdType = (int)m_ComboFilterType->GetClientData(id);
	
	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_type = '%d'"),TABLE_ITEM,m_IdType);
	if(!my_query(sql))
		return;
	
	int rows = 0;
	void *result = db_result();
	char **row;

	while(row = (char**)db_fetch_row(result))
	{
		wxString name(row[FI_ITEM_NAME],wxConvUTF8);
		m_ListBox->Append(name);
	}

	db_free_result(result);
		
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

void CNew::SetItemTypeID(int v)
{
	m_IdType = v;

}

wxArrayPtrVoid CNew::GetFeatureControls()
{
	return m_Ids;
}

void CNew::SetItemId(wxString v)
{
	m_ItemId = v;
}