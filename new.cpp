#include "new.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "dialog.h"
#include "picture.h"
#include "item.h"
#include <wx/statline.h>
#include "tools.h"
#include "light.h"

BEGIN_EVENT_TABLE(CNew,wxDialog)
	EVT_COMBOBOX(ID_ITEM_TYPE,OnComboItem)
	EVT_COMBOBOX(ID_FILTER,OnComboFilter)
	EVT_TEXT(ID_LON,OnLon)
	EVT_TEXT(ID_LAT,OnLat)
END_EVENT_TABLE()


CNew::CNew(int type, int id_type, wxString item_id, bool edit)
	:wxDialog(NULL,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize)
{
	m_Lon = 0;
	m_Lat = 0;
	m_ControlType = type;
	m_IDType = id_type;
	m_ItemID = item_id;
	m_Edit = edit;
//	m_FeaturePanel = NULL;
	m_TextValidator.SetStyle(wxFILTER_EXCLUDE_CHAR_LIST);
	m_TextValidator.SetCharExcludes(_("'\"\\;?"));
	
}

CNew::~CNew()
{

}

void CNew::Create()
{
	GetPanel(m_ControlType);
	Fit();
	GetSizer()->Layout();
	Center();	
}

void CNew::GetPanel(int type)
{
	switch(type)
	{
		case CONTROL_ITEM:			EditItemPanel();	break;
		case CONTROL_PICTURE:		EditPicturePanel();	break;
		case CONTROL_SYMBOL:		EditSymbolPanel();	break;
		case CONTROL_AREA:
		case CONTROL_SEAWAY:
		case CONTROL_SYMBOL_TYPE:	EditNamePanel();	break;
		

	}
}

void CNew::GetItemFeaturePanel(wxWindow *Parent)
{
	wxString sql = wxString::Format(_("SELECT * FROM `%s`,`%s` WHERE %s.id_type = '%d' AND `%s`.id = `%s`.id_feature ORDER BY name"),TABLE_ITEM_FEATURE, TABLE_ITEM_TYPE_FEATURE ,TABLE_ITEM_TYPE_FEATURE, m_IDType,TABLE_ITEM_FEATURE, TABLE_ITEM_TYPE_FEATURE );
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
		m_IDs.Add(Text);
	}
	
	db_free_result(result);


	for(size_t i = 0; i < m_IDs.size(); i++)
	{
		wxTextCtrl *txt = (wxTextCtrl*)m_IDs.Item(i);
		sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_item = '%s' AND id_feature = '%d'"),TABLE_ITEM_VALUE,m_ItemID,(int)txt->GetClientData());
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
		if(m_IDType == rid)
		{
			ptr->SetSelection(id);
			selected = true;
		}
		ptr->SetClientData(id,(int*)rid);
		counter++;
	}
		
	if(!selected && counter > 0)
	{
		m_IDType = (int)ptr->GetClientData(0);
		ptr->SetSelection(0);
		
	}
	
	db_free_result(result);
	return ptr;
}

wxPanel *CNew::GetItemPanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(Parent);
	Panel->SetSizer(Sizer);

	wxBoxSizer *ScrollSizer = new wxBoxSizer(wxVERTICAL);
	wxScrolledWindow *Scroll = new wxScrolledWindow(Panel, wxID_ANY, wxDefaultPosition, wxSize(400,200));
	Sizer->Add(Scroll,1,wxALL|wxEXPAND,5);
	Scroll->SetFocusIgnoringChildren();
	Scroll->SetSizer(ScrollSizer);

	CItemPanel *Item  = new CItemPanel(Panel,Scroll);
	ScrollSizer->Add(Item,1,wxALL|wxEXPAND,0);
	Scroll->SetScrollbars(20, 20, 20, 20);
	
	return Panel;
}

wxPanel *CNew::GetPicturePanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(Parent);
	Panel->SetSizer(Sizer);

	m_PicturePanel = new CPicturePanel(Panel,PICTURE_PANEL_PICKER);
	m_PicturePanel->SetPictureId(m_PictureId);
	Sizer->Add(m_PicturePanel,0,wxALL|wxEXPAND,5);

	return Panel;
}

void CNew::ClearColors()
{
//	for(size_t i = 0; i < m_Color.size(); i++)
//	{
		//delete m_Color[i];
	//}
	
	//m_Color.Clear();
}

wxPanel *CNew::GetLightPanel(wxWindow *Parent)
{
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(Sizer);

	wxBoxSizer *ScrollSizer = new wxBoxSizer(wxVERTICAL);
	wxScrolledWindow *Scroll = new wxScrolledWindow(Panel, wxID_ANY, wxDefaultPosition, wxSize(400,200));
	Sizer->Add(Scroll,1,wxALL|wxEXPAND,0);
	Scroll->SetFocusIgnoringChildren();
	Scroll->SetSizer(ScrollSizer);
		
	m_LightPanel = new CLightPanel(Panel,Scroll);
	ScrollSizer->Add(m_LightPanel,1,wxALL|wxEXPAND,5);
	Scroll->SetScrollbars(20, 20, 20, 20);
	
	return Panel;

}

CLightPanel *CNew::GetLightPanel()
{
	return m_LightPanel;
}

wxPanel *CNew::GetSymbolPanel(wxWindow *Parent)
{
	//wxPanel *Main = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	//wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	//wxNotebook *Notebook = new wxNotebook(Main,wxID_ANY);
	//Sizer->Add(Notebook,1,wxALL|wxEXPAND);


	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	wxFlexGridSizer *FlexGridSizer = new wxFlexGridSizer(2);
	FlexGridSizer->AddGrowableCol(1);
	Panel->SetSizer(FlexGridSizer);
	
	

	/*
	m_ColorPanel = new CColorPanel(Panel,this);
	FlexGridSizer->Add(m_ColorPanel,0,wxALL|wxEXPAND,5);
	for(size_t i = 0; i < m_Color.size(); i++)
	{
		wxColor *color = (wxColor*)m_Color.Item(i);
		m_ColorPanel->New(*color);	
	}
	
	ClearColors();
	*/
	
	wxStaticText *LabelArea = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_AREA));
	FlexGridSizer->Add(LabelArea,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_AreaCombo = GetCombo(Panel,TABLE_AREA,m_AreaID);
	FlexGridSizer->Add(m_AreaCombo,0,wxALL|wxEXPAND,5);

	wxStaticText *LabelSeaway = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SEAWAY));
	FlexGridSizer->Add(LabelSeaway,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_SeawayCombo = GetCombo(Panel,TABLE_SEAWAY,m_SeawayID);
	FlexGridSizer->Add(m_SeawayCombo,0,wxALL|wxEXPAND,5);

	wxStaticText *LabelSymbolType = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SYMBOL_TYPE));
	FlexGridSizer->Add(LabelSymbolType,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_SymbolTypeCombo = GetCombo(Panel,TABLE_SYMBOL_TYPE,m_SymbolTypeID);
	FlexGridSizer->Add(m_SymbolTypeCombo,0,wxALL|wxEXPAND,5);
	

	wxStaticText *LabelName = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_NAME));
	FlexGridSizer->Add(LabelName,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextName = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	m_TextName->SetFocus();
	m_TextName->SetValue(m_Name);
	m_TextName->SetValidator(m_TextValidator);
	FlexGridSizer->Add(m_TextName,0,wxALL|wxEXPAND,5);

	wxStaticText *LabelNumber = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SYMBOL_NUMBER),wxDefaultPosition,wxDefaultSize);
	FlexGridSizer->Add(LabelNumber,0,wxALL,5);
	m_TextNumber = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	m_TextNumber->SetValue(m_Number);
	FlexGridSizer->Add(m_TextNumber,0,wxALL,5);
	
	wxStaticText *LabelLat = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_LATITUDE),wxDefaultPosition,wxDefaultSize);
	FlexGridSizer->Add(LabelLat,0,wxALL,5);
	m_TextLat = new wxTextCtrl(Panel,ID_LAT,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	FlexGridSizer->Add(m_TextLat,0,wxALL,5);
	
	wxStaticText *LabelLon = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_LONGITUDE) ,wxDefaultPosition,wxDefaultSize);
	FlexGridSizer->Add(LabelLon,0,wxALL,5);
	m_TextLon = new wxTextCtrl(Panel,ID_LON,wxEmptyString, wxDefaultPosition, wxDefaultSize);
	FlexGridSizer->Add(m_TextLon,0,wxALL,5);
	
	m_TextLon->SetValue(FormatLongitude(m_Lon));
	m_TextLat->SetValue(FormatLatitude(m_Lat));
	
	wxStaticText *LabelInfo = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_INFO));
	FlexGridSizer->Add(LabelInfo,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextInfo = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(300,80),wxTE_MULTILINE);
	m_TextInfo->SetValue(m_Info);
	m_TextInfo->SetValidator(m_TextValidator);
	FlexGridSizer->Add(m_TextInfo,0,wxALL|wxEXPAND,5);

	return Panel;
}

void CNew::EditItemPanel()
{
	wxBoxSizer *Main = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Main);
	
	m_Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	m_Panel->SetBackgroundColour(*wxWHITE);
	Main->Add(m_Panel,1,wxALL|wxEXPAND,0);
	
		
	m_FlexGridSizer = new wxFlexGridSizer(2);
	m_FlexGridSizer->AddGrowableCol(1);
	m_Panel->SetSizer(m_FlexGridSizer);
	
	/*
	wxStaticText *LabelPicture = new wxStaticText(m_Panel,wxID_ANY,GetMsg(MSG_PICTURE));
	m_FlexGridSizer->Add(LabelPicture,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	
	m_PicturePanel = new CPicturePanel(m_Panel,PICTURE_PANEL_PICKER);
	m_FlexGridSizer->Add(m_PicturePanel,0,wxALL|wxEXPAND,5);
	*/	
	wxStaticText *LabelItemType = new wxStaticText(m_Panel,wxID_ANY,GetMsg(MSG_ITEM_TYPE));
	m_FlexGridSizer->Add(LabelItemType,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	
	m_ComboItemType =  GetComboItemType(m_Panel);
	m_FlexGridSizer->Add(m_ComboItemType,0,wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND,5);
	m_ComboItemType->Enable(!m_Edit);
	
	wxStaticText *LabelName = new wxStaticText(m_Panel,wxID_ANY,GetMsg(MSG_NAME));
	m_FlexGridSizer->Add(LabelName,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextName = new wxTextCtrl(m_Panel,wxID_ANY,wxEmptyString);
	m_TextName->SetFocus();
	m_TextName->SetValue(m_Name);
	m_FlexGridSizer->Add(m_TextName,0,wxALL|wxEXPAND,5);
	m_TextName->SetValidator(m_TextValidator);
	
	wxStaticText *LabelType = new wxStaticText(m_Panel,wxID_ANY,GetMsg(MSG_TYPE));
	m_FlexGridSizer->Add(LabelType,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextType = new wxTextCtrl(m_Panel,wxID_ANY,wxEmptyString);
	m_TextType->SetValue(m_Type);
	m_FlexGridSizer->Add(m_TextType,0,wxALL|wxEXPAND,5);
	m_TextType->SetValidator(m_TextValidator);
		
	wxStaticText *LabelInfo = new wxStaticText(m_Panel,wxID_ANY,GetMsg(MSG_INFO));
	m_FlexGridSizer->Add(LabelInfo,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextInfo = new wxTextCtrl(m_Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(300,80),wxTE_MULTILINE);
	m_TextInfo->SetValue(m_Info);
	m_TextInfo->SetValidator(m_TextValidator);
	m_FlexGridSizer->Add(m_TextInfo,0,wxALL|wxEXPAND,5);
	

	GetItemFeaturePanel(m_Panel);


	wxPanel *Panel1 = new wxPanel(this);
	Main->Add(Panel1,0,wxALL|wxEXPAND,5);
	wxBoxSizer *Panel1Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel1->SetSizer(Panel1Sizer);

	Panel1Sizer->AddStretchSpacer();

	wxButton *ButtonOk = new wxButton(Panel1,wxID_OK,GetMsg(MSG_OK));
	Panel1Sizer->Add(ButtonOk,0,wxALL,5);

	wxButton *ButtonCancel = new wxButton(Panel1,wxID_CANCEL,GetMsg(MSG_CANCEL));
	Panel1Sizer->Add(ButtonCancel,0,wxALL,5);
	
}


void CNew::EditTypePanel()
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
	m_TextType->SetValue(m_Type);
	FlexGridSizer->Add(m_TextType,0,wxALL|wxEXPAND,5);
	m_TextType->SetValidator(m_TextValidator);
		
	wxStaticText *LabelInfo = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_INFO));
	FlexGridSizer->Add(LabelInfo,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextInfo = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(300,80),wxTE_MULTILINE);
	m_TextInfo->SetValue(m_Info);
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
		
}


void CNew::EditNamePanel()
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
	m_TextName->SetFocus();
	m_TextName->SetValue(m_Name);
	m_TextName->SetValidator(m_TextValidator);
	FlexGridSizer->Add(m_TextName,0,wxALL|wxEXPAND,5);
		
	wxStaticText *LabelInfo = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_INFO));
	FlexGridSizer->Add(LabelInfo,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextInfo = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(300,80),wxTE_MULTILINE);
	m_TextInfo->SetValue(m_Info);
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
		
}

void CNew::EditSymbolPanel()
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
	
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Sizer->Add(Panel,1,wxALL|wxEXPAND,0);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(PanelSizer);
	
	wxNotebook *Notebook = new wxNotebook(Panel,wxID_ANY);
	PanelSizer->Add(Notebook,1,wxALL|wxEXPAND,0);
	Notebook->AddPage(GetSymbolPanel(Notebook),GetMsg(MSG_SYMBOL));
	Notebook->AddPage(GetLightPanel(Notebook),GetMsg(MSG_LIGHT));
	Notebook->AddPage(GetPicturePanel(Notebook),GetMsg(MSG_PICTURE));
	Notebook->AddPage(GetItemPanel(Notebook),GetMsg(MSG_ITEMS));
		
	wxPanel *Panel1 = new wxPanel(this);
	Sizer->Add(Panel1,0,wxALL|wxEXPAND,5);
	wxBoxSizer *Panel1Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel1->SetSizer(Panel1Sizer);

	Panel1Sizer->AddStretchSpacer();

	wxButton *ButtonOk = new wxButton(Panel1,wxID_OK,GetMsg(MSG_OK));
	Panel1Sizer->Add(ButtonOk,0,wxALL,5);

	wxButton *ButtonCancel = new wxButton(Panel1,wxID_CANCEL,GetMsg(MSG_CANCEL));
	Panel1Sizer->Add(ButtonCancel,0,wxALL,5);

	GetSizer()->SetSizeHints(this);
	
}


void CNew::EditPicturePanel()
{
	wxBoxSizer *Main = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Main);
	
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Panel->SetBackgroundColour(*wxWHITE);
	Main->Add(Panel,1,wxALL|wxEXPAND,0);
	
	wxFlexGridSizer *FlexGridSizer = new wxFlexGridSizer(2);
	FlexGridSizer->AddGrowableCol(1);
	Panel->SetSizer(FlexGridSizer);
	
	wxStaticText *LabelPicture = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_PICTURE));
	FlexGridSizer->Add(LabelPicture,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	
	m_PicturePanel = new CPicturePanel(Panel,PICTURE_PANEL_NEW);
	m_PicturePanel->SetPictureId(m_PictureId);
	FlexGridSizer->Add(m_PicturePanel,0,wxALL|wxEXPAND,5);
		
	wxStaticText *LabelName = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_NAME));
	FlexGridSizer->Add(LabelName,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextName = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	m_TextName->SetFocus();
	m_TextName->SetValue(m_Name);
	FlexGridSizer->Add(m_TextName,0,wxALL|wxEXPAND,5);
	m_TextName->SetValidator(m_TextValidator);
			
	wxStaticText *LabelInfo = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_INFO));
	FlexGridSizer->Add(LabelInfo,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextInfo = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(300,80),wxTE_MULTILINE);
	m_TextInfo->SetValue(m_Info);
	m_TextInfo->SetValidator(m_TextValidator);
	FlexGridSizer->Add(m_TextInfo,0,wxALL|wxEXPAND,5);

	wxPanel *Panel1 = new wxPanel(this);
	Main->Add(Panel1,0,wxALL|wxEXPAND,5);
	wxBoxSizer *Panel1Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel1->SetSizer(Panel1Sizer);

	Panel1Sizer->AddStretchSpacer();

	wxButton *ButtonOk = new wxButton(Panel1,wxID_OK,GetMsg(MSG_OK));
	Panel1Sizer->Add(ButtonOk,0,wxALL,5);

	wxButton *ButtonCancel = new wxButton(Panel1,wxID_CANCEL,GetMsg(MSG_CANCEL));
	Panel1Sizer->Add(ButtonCancel,0,wxALL,5);
		
}

void CNew::OnLon(wxCommandEvent &event)
{	
	
	if(_SetLon(m_TextLon->GetValue().char_str(),&m_Lon))
	{
		
		//double y,to_x,to_y;
		//y = MarkerSelectedPtr->y;
		//_Parent->GetBroker()->Unproject(value,y,&to_x,&to_y);
		//MarkerSelectedPtr->x = (float)to_x;
					
		//_Parent->GetBroker()->Refresh(_Parent->GetBroker()->GetParentPtr());
		m_TextLon->SetForegroundColour(wxSYS_COLOUR_WINDOWTEXT);
		m_TextLon->Refresh();

	}else{
		
		m_TextLon->SetForegroundColour(*wxRED);
		m_TextLon->Refresh();
	
	}

}

void CNew::OnLat(wxCommandEvent &event)
{
	//SMarker *MarkerSelectedPtr =_Parent->GetNewMarkerPtr();
	//if(MarkerSelectedPtr == NULL)
		//return;
			
	if(_SetLat(m_TextLat->GetValue().char_str(),&m_Lat))
	{
		///double x,to_x,to_y;
		//x = MarkerSelectedPtr->x;
		//_Parent->GetBroker()->Unproject(x,value,&to_x,&to_y);
		//MarkerSelectedPtr->y = (float)to_y;
							
		//_Parent->GetBroker()->Refresh(_Parent->GetBroker()->GetParentPtr());
		m_TextLat->SetForegroundColour(wxSYS_COLOUR_WINDOWTEXT);
		m_TextLat->Refresh();

	}else{
		
		m_TextLat->SetForegroundColour(*wxRED);
		m_TextLat->Refresh();
	}

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

	m_IDType = (int)m_ComboItemType->GetClientData(id);

	for(size_t i = 0; i < m_Controls.size(); i++)
	{
		wxWindow *wnd = (wxWindow*)m_Controls.Item(i);
		m_FlexGridSizer->Detach(wnd);
		
		delete wnd;
	}
	
	m_Controls.Clear();
	m_IDs.Clear();
	GetItemFeaturePanel(m_Panel);
	this->Layout();
	this->GetSizer()->SetSizeHints(this);

}

void CNew::OnComboFilter(wxCommandEvent &event)
{
	int id = event.GetSelection();
	m_ListBox->Clear();

	m_IDType = (int)m_ComboFilterType->GetClientData(id);
	
	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_type = '%d'"),TABLE_ITEM,m_IDType);
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




//SET
void CNew::SetName(wxString v)
{
	m_Name = v;
	
}

void CNew::SetInfo(wxString v)
{
	m_Info = v;
	
}

void CNew::SetType(wxString v)
{
	m_Type = v;

}

void CNew::SetItemTypeID(int v)
{
	m_IDType = v;

}

void CNew::SetItemId(wxString v)
{
	m_ItemID = v;
}

void CNew::SetPictureId(wxString id)
{
	m_PictureId = id;

}

void CNew::SetSeaway(wxString id)
{
	m_SeawayID = id;
}

void CNew::SetArea(wxString id)
{
	m_AreaID = id;
}

void CNew::SetSymbolType(wxString id)
{
	m_SymbolTypeID = id;
}

void CNew::SetColor(wxString v)
{	
	m_Color;
}

/*
void CNew::SetColor(wxColor *color)
{	
	m_Color.Add(color);
}
*/

void CNew::SetLon(double v)
{
	m_Lon = v;
}

void CNew::SetLat(double v)
{
	m_Lat = v;
}

void CNew::_SetPosition(double lon, double lat)
{
	m_Lon = lon;
	m_Lat = lat;
}

void CNew::SetNumber(wxString v)
{
	m_Number = v;
}

void CNew::SetCoverage(wxString v)
{
	m_Coverage = v;
}

//GET
wxArrayPtrVoid CNew::GetFeatureControls()
{
	return m_IDs;
}

wxImage CNew::GetPicture()
{	
	return m_PicturePanel->GetPicture();
}

int CNew::GetAreaId()
{
	return (int)m_AreaCombo->GetClientData(m_AreaCombo->GetSelection());
	
}

int CNew::GetSeawayId()
{
	return (int)m_SeawayCombo->GetClientData(m_SeawayCombo->GetSelection());
	
}

int CNew::GetSymbolTypeId()
{
	return (int)m_SymbolTypeCombo->GetClientData(m_SymbolTypeCombo->GetSelection());
	
}

double CNew::GetLon()
{
	return m_Lon;
}

double CNew::GetLat()
{
	return m_Lat;
}

wxString CNew::GetNumber()
{
	return m_TextNumber->GetValue();
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

wxString CNew::GetPictureId()
{
	return m_PicturePanel->GetPictureId();
}

//wxString CNew::GetColor()
//{
	//return m_TextColor->GetValue();
//}

wxString CNew::GetCoverage()
{
	return m_TextCoverage->GetValue();
	
}