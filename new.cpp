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
#include "GeometryTools.h"
#include "conf.h"

BEGIN_EVENT_TABLE(CNew,wxDialog)
	EVT_COMBOBOX(ID_ITEM_TYPE,OnComboItem)
	EVT_COMBOBOX(ID_FILTER,OnComboFilter)
	EVT_TEXT(ID_LON,OnLon)
	EVT_TEXT(ID_LAT,OnLat)
END_EVENT_TABLE()


CNew::CNew(void *db,int type, int id_type, int item_id, bool edit)
:wxDialog(NULL,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER)
{
	m_DB = db;
	m_DegreeFormat = DEFAULT_DEGREE_FORMAT;
	m_LonValid = m_LatValid = false;
	m_PictureId = -1;
	m_Lon = UNDEFINED_DOUBLE;
	m_Lat = UNDEFINED_DOUBLE;
	m_ControlType = type;
	m_IDType = id_type;
	m_ItemID = item_id;
	m_Edit = edit;
	m_OnPosition = m_InMonitoring = false;
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
		case CONTROL_ITEM:			EditItemPanel();			break;
		case CONTROL_PICTURE:		EditPicturePanel();			break;
		case CONTROL_SYMBOL:		EditSymbolPanel();			break;
		case CONTROL_BASE_STATION:	EditBaseStationPanel();		break;
		case CONTROL_CHARACTERISTIC:EditCharacteristicPanel();	break;
		
		case CONTROL_SYMBOL_TYPE:	
		case CONTROL_AREA:
		case CONTROL_SEAWAY:		EditNamePanel(); break;
		
		

	}
}

void CNew::GetItemFeaturePanel(wxWindow *Parent)
{
	wxString sql = wxString::Format(_("SELECT * FROM `%s`,`%s` WHERE %s.id_type = '%d' AND `%s`.id = `%s`.id_feature ORDER BY name"),TABLE_ITEM_FEATURE, TABLE_ITEM_TYPE_FEATURE ,TABLE_ITEM_TYPE_FEATURE, m_IDType,TABLE_ITEM_FEATURE, TABLE_ITEM_TYPE_FEATURE );
	if(!my_query(m_DB,sql))
		return;
	
	int rows = 0;
	void *result = db_result(m_DB);
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
		sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_item = '%d' AND id_feature = '%d'"),TABLE_ITEM_VALUE,m_ItemID,(int)txt->GetClientData());
		my_query(m_DB,sql);

		void *result = db_result(m_DB);
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
	if(!my_query(m_DB,sql))
		return ptr;
		
	int rows = 0;
	void *result = db_result(m_DB);
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

	m_ItemPanel  = new CItemPanel(m_DB,Panel,Scroll);
	ScrollSizer->Add(m_ItemPanel,1,wxALL|wxEXPAND,0);
	Scroll->SetScrollbars(20, 20, 20, 20);
	
	return Panel;
}

wxPanel *CNew::GetPicturePanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(Parent);
	Panel->SetSizer(Sizer);

	m_PicturePanel = new CPicturePanel(m_DB,Panel,PICTURE_PANEL_PICKER);
	m_PicturePanel->SetPictureId(m_PictureId);
	Sizer->Add(m_PicturePanel,1,wxALL|wxEXPAND,5);

	return Panel;
}

wxPanel *CNew::GetLightPanel(wxWindow *Parent)
{
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(Sizer);

	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	FlexSizer->AddGrowableCol(1);
	wxStaticText *LabelCharacteristic = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_CHARACTERISTIC));
	FlexSizer->Add(LabelCharacteristic,0,wxALL|wxALIGN_CENTER_VERTICAL,1);
	m_CharacteristicText = new wxTextCtrl(Panel,wxID_ANY);
	m_CharacteristicText->SetValue(m_Characteristic);
	m_CharacteristicText->SetValidator(m_TextValidator);
	FlexSizer->Add(m_CharacteristicText,0,wxALL|wxEXPAND,1);
	Sizer->Add(FlexSizer,0,wxALL|wxEXPAND,2);
	
	wxBoxSizer *ScrollSizer = new wxBoxSizer(wxVERTICAL);
	wxScrolledWindow *Scroll = new wxScrolledWindow(Panel, wxID_ANY, wxDefaultPosition, wxSize(400,200));
	Sizer->Add(Scroll,1,wxALL|wxEXPAND,0);
	Scroll->SetFocusIgnoringChildren();
	Scroll->SetSizer(ScrollSizer);
	
	m_LightPanel = new CLightPanel(m_DB,Panel,Scroll);
	ScrollSizer->Add(m_LightPanel,1,wxALL|wxEXPAND,5);
	Scroll->SetScrollbars(20, 20, 20, 20);
	
	return Panel;

}


wxPanel *CNew::GetSymbolPanel(wxWindow *Parent)
{
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	wxFlexGridSizer *FlexGridSizer = new wxFlexGridSizer(2);
	FlexGridSizer->AddGrowableCol(1);
	Panel->SetSizer(FlexGridSizer);
	
	m_CheckOnPosition = new wxCheckBox(Panel,wxID_ANY,GetMsg(MSG_ON_POSITION));
	m_CheckOnPosition->SetValue(m_OnPosition);
	FlexGridSizer->Add(m_CheckOnPosition,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);
	
	m_CheckInMonitoring = new wxCheckBox(Panel,wxID_ANY,GetMsg(MSG_IN_MONITORING));
	m_CheckInMonitoring->SetValue(m_InMonitoring);
	FlexGridSizer->Add(m_CheckInMonitoring,0,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);
		
	wxStaticText *LabelBaseStation = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_BASE_STATION));
	FlexGridSizer->Add(LabelBaseStation,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_BaseStationCombo = GetCombo(m_DB,Panel,TABLE_BASE_STATION,m_BaseStationID,FI_BASE_STATION_ID,FI_BASE_STATION_NAME);
	//m_BaseStationCombo->SetSelection(0);
	FlexGridSizer->Add(m_BaseStationCombo,0,wxALL|wxEXPAND,5);

	wxStaticText *LabelArea = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_AREA));
	FlexGridSizer->Add(LabelArea,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_AreaCombo = GetCombo(m_DB,Panel,TABLE_AREA,m_AreaID,FI_AREA_ID,FI_AREA_NAME);
	//m_AreaCombo->SetSelection(0);
	FlexGridSizer->Add(m_AreaCombo,0,wxALL|wxEXPAND,5);
	
	wxStaticText *LabelSeaway = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SEAWAY));
	FlexGridSizer->Add(LabelSeaway,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_SeawayCombo = GetCombo(m_DB,Panel,TABLE_SEAWAY,m_SeawayID,FI_SEAWAY_ID,FI_SEAWAY_NAME);
	//m_SeawayCombo->SetSelection(0);
	FlexGridSizer->Add(m_SeawayCombo,0,wxALL|wxEXPAND,5);
	
	wxStaticText *LabelSymbolType = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SYMBOL_TYPE));
	FlexGridSizer->Add(LabelSymbolType,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_SymbolTypeCombo = GetCombo(m_DB,Panel,TABLE_SYMBOL_TYPE,m_SymbolTypeID,FI_SYMBOL_TYPE_ID,FI_SYMBOL_TYPE_NAME);
	//m_SymbolTypeCombo->SetSelection(0);
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
	m_TextNumber->SetValidator(m_TextValidator);
	FlexGridSizer->Add(m_TextNumber,0,wxALL,5);
			
	wxStaticText *LabelLat = new wxStaticText(Panel,wxID_ANY,wxString::Format(_("%s\n(%s)"),GetMsg(MSG_LATITUDE),GetDegreeFormat(DEGREE_FORMAT_DDMMSS,DIR_LAT)),wxDefaultPosition,wxDefaultSize);
	FlexGridSizer->Add(LabelLat,0,wxALL,5);
	m_TextLat = new wxTextCtrl(Panel,ID_LAT,wxEmptyString,wxDefaultPosition,wxDefaultSize);
	FlexGridSizer->Add(m_TextLat,0,wxALL,5);
	
	wxStaticText *LabelLon = new wxStaticText(Panel,wxID_ANY,wxString::Format(_("%s\n(%s)"),GetMsg(MSG_LONGITUDE),GetDegreeFormat(DEGREE_FORMAT_DDMMSS,DIR_LON)),wxDefaultPosition,wxDefaultSize);
	FlexGridSizer->Add(LabelLon,0,wxALL,5);
	m_TextLon = new wxTextCtrl(Panel,ID_LON,wxEmptyString, wxDefaultPosition, wxDefaultSize);
	FlexGridSizer->Add(m_TextLon,0,wxALL,5);
	
	if(!UNDEFINED_VAL(m_Lon))
		m_TextLon->SetValue(FormatLongitude(m_Lon,m_DegreeFormat));
	if(!UNDEFINED_VAL(m_Lat))
		m_TextLat->SetValue(FormatLatitude(m_Lat,m_DegreeFormat));
	
	wxStaticText *LabelInfo = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_INFO));
	FlexGridSizer->Add(LabelInfo,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextInfo = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(TEXT_INFO_WIDTH,TEXT_INFO_HEIGHT),wxTE_MULTILINE);
	m_TextInfo->SetValue(m_Info);
	m_TextInfo->SetValidator(m_TextValidator);
	FlexGridSizer->Add(m_TextInfo,1,wxALL|wxEXPAND,5);
	FlexGridSizer->AddSpacer(1);
		
	return Panel;
}

void CNew::EditItemPanel()
{
	wxBoxSizer *Main = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Main);
		
	m_Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
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
	m_TextInfo = new wxTextCtrl(m_Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(TEXT_INFO_WIDTH,TEXT_INFO_HEIGHT),wxTE_MULTILINE);
	m_TextInfo->SetValue(m_Info);
	m_TextInfo->SetValidator(m_TextValidator);
	m_FlexGridSizer->Add(m_TextInfo,1,wxALL|wxEXPAND,5);
	

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
	m_TextInfo = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(TEXT_INFO_WIDTH,TEXT_INFO_HEIGHT),wxTE_MULTILINE);
	m_TextInfo->SetValue(m_Info);
	FlexGridSizer->Add(m_TextInfo,1,wxALL|wxEXPAND,5);
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
	m_TextInfo = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(TEXT_INFO_WIDTH,TEXT_INFO_HEIGHT),wxTE_MULTILINE);
	m_TextInfo->SetValue(m_Info);
	m_TextInfo->SetValidator(m_TextValidator);
	FlexGridSizer->Add(m_TextInfo,1,wxALL|wxEXPAND,5);
	
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

void CNew::EditBaseStationPanel()
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
	
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Sizer->Add(Panel,1,wxALL|wxEXPAND,0);
	wxFlexGridSizer *FlexGridSizer = new wxFlexGridSizer(2);
	FlexGridSizer->AddGrowableCol(1);
	Panel->SetSizer(FlexGridSizer);	
	
	wxStaticText *LabelName = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_NAME));
	FlexGridSizer->Add(LabelName,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	
	m_TextName = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	m_TextName->SetFocus();
	m_TextName->SetValue(m_Name);
	FlexGridSizer->Add(m_TextName,0,wxALL|wxEXPAND,5);
	m_TextName->SetValidator(m_TextValidator);
	
	wxStaticText *LabelHost = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_HOST));
	FlexGridSizer->Add(LabelHost,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	
	m_TextHost = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	m_TextHost->SetValue(m_Host);
	FlexGridSizer->Add(m_TextHost,0,wxALL|wxEXPAND,5);
	m_TextHost->SetValidator(m_TextValidator);

	wxStaticText *LabelPort = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_PORT));
	FlexGridSizer->Add(LabelPort,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	
	m_TextPort = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	m_TextPort->SetValue(m_Port);
	FlexGridSizer->Add(m_TextPort,0,wxALL,5);
	m_TextHost->SetValidator(m_TextValidator);
	
	
	wxStaticText *LabelInfo = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_INFO));
	FlexGridSizer->Add(LabelInfo,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	m_TextInfo = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(TEXT_INFO_WIDTH,TEXT_INFO_HEIGHT),wxTE_MULTILINE);
	m_TextInfo->SetValue(m_Info);
	m_TextInfo->SetValidator(m_TextValidator);
	FlexGridSizer->Add(m_TextInfo,1,wxALL|wxEXPAND,5);
	

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


void CNew::EditCharacteristicPanel()
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
	
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Sizer->Add(Panel,0,wxALL|wxEXPAND,0);
	wxFlexGridSizer *FlexGridSizer = new wxFlexGridSizer(2);
	FlexGridSizer->AddGrowableCol(1);
	Panel->SetSizer(FlexGridSizer);	
	
	wxStaticText *LabelCode = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_CODE));
	FlexGridSizer->Add(LabelCode,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	
	m_TextCode = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	m_TextCode->SetFocus();
	m_TextCode->SetValue(m_Code);
	FlexGridSizer->Add(m_TextCode,0,wxALL|wxEXPAND,5);
	m_TextCode->SetValidator(m_TextValidator);
	
	wxStaticText *LabelIala = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_IALA));
	FlexGridSizer->Add(LabelIala,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	
	m_TextIala = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	m_TextIala->SetValue(m_Iala);
	FlexGridSizer->Add(m_TextIala,0,wxALL|wxEXPAND,5);
	m_TextIala->SetValidator(m_TextValidator);

	wxStaticText *LabelTime = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_TIME));
	FlexGridSizer->Add(LabelTime,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
	
	m_TextTime = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString);
	m_TextTime->SetValue(m_Time);
	FlexGridSizer->Add(m_TextTime,0,wxALL,5);
	m_TextTime->SetValidator(m_TextValidator);
	
	wxBoxSizer *ScrollSizer = new wxBoxSizer(wxVERTICAL);
	wxScrolledWindow *Scroll = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(400,200));
	Sizer->Add(Scroll,1,wxALL|wxEXPAND,0);
	Scroll->SetFocusIgnoringChildren();
	Scroll->SetSizer(ScrollSizer);
		
	m_TimePanel = new CTimePanel(m_DB,this,Scroll);
	ScrollSizer->Add(m_TimePanel,0,wxALL|wxEXPAND,5);
	Scroll->SetScrollbars(20, 20, 20, 20);
	
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
	Main->Add(Panel,1,wxALL|wxEXPAND,0);
	
	wxFlexGridSizer *FlexGridSizer = new wxFlexGridSizer(2);
	FlexGridSizer->AddGrowableCol(1);
	Panel->SetSizer(FlexGridSizer);
	
	m_PicturePanel = new CPicturePanel(m_DB,Panel,PICTURE_PANEL_NEW);
	m_PicturePanel->SetPictureId(m_PictureId);
	FlexGridSizer->AddSpacer(1);
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
	m_TextInfo = new wxTextCtrl(Panel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxSize(TEXT_INFO_WIDTH,TEXT_INFO_HEIGHT),wxTE_MULTILINE);
	m_TextInfo->SetValue(m_Info);
	m_TextInfo->SetValidator(m_TextValidator);
	FlexGridSizer->AddGrowableRow(2);
	FlexGridSizer->Add(m_TextInfo,1,wxALL|wxEXPAND,5);

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
	if(m_TextLon->GetValue().empty())
	{
		m_LonValid = false;
		return;
	}
		
	if(_SetLon(m_TextLon->GetValue().char_str(),&m_Lon,m_DegreeFormat))
	{
		m_LonValid = true;
		m_TextLon->SetForegroundColour(wxSYS_COLOUR_WINDOWTEXT);
		m_TextLon->Refresh();

	}else{
		
		m_LonValid = false;
		m_TextLon->SetForegroundColour(*wxRED);
		m_TextLon->Refresh();
	
	}

}

void CNew::OnLat(wxCommandEvent &event)
{
	if(m_TextLat->GetValue().empty())
	{
		m_LatValid = false;
		return;
	}
			
	if(_SetLat(m_TextLat->GetValue().char_str(),&m_Lat,m_DegreeFormat))
	{
		m_LatValid = true;
		m_TextLat->SetForegroundColour(wxSYS_COLOUR_WINDOWTEXT);
		m_TextLat->Refresh();

	}else{
		
		m_LatValid = false;
		m_TextLat->SetForegroundColour(*wxRED);
		m_TextLat->Refresh();
	}

}


bool CNew::Validate()
{
		
	wxString err;
	bool result = true;
	
	switch(m_ControlType)
	{
		case CONTROL_SYMBOL:			result = ValidateSymbol();			break;
		case CONTROL_CHARACTERISTIC:	result = ValidateCharacteristic();	break;
		default:				result = ValidateOthers();
	}
	
	return result;
	
}

bool CNew::ValidateSymbol()
{
	bool result = true;
	wxString err;
	
	if(m_TextName->GetValue().empty())
	{
		result = false;
		err << GetMsg(MSG_NAME_EMPTY) << "\n";
	}
	
	
	if(!m_LonValid)
	{
		result = false;
		err << GetMsg(MSG_LONGITUDE_INVALID_VALUE) << "\n";
	}

	if(!m_LatValid)
	{
		result = false;
		err << GetMsg(MSG_LATITUDE_INVALID_VALUE) << "\n";
	}
	
	if(!result)
	{
		wxMessageBox(err);
		return false;
	}
	
	return true;
}

bool CNew::ValidateCharacteristic()
{
	bool result = true;
	wxString err;
	
	if(m_TextCode->GetValue().empty())
	{
		result = false;
		err << GetMsg(MSG_CODE_EMPTY) << "\n";
	}
	
	if(m_TextIala->GetValue().empty())
	{
		result = false;
		err << GetMsg(MSG_IALA_EMPTY) << "\n";
	}
	
	if(m_TextTime->GetValue().empty())
	{
		result = false;
		err << GetMsg(MSG_TIME_EMPTY) << "\n";
	}
	
	if(!result)
	{
		wxMessageBox(err);
		return false;
	}
	
	return true;
}

bool CNew::ValidateOthers()
{
	bool result = true;
	wxString err;
	
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
	if(!my_query(m_DB,sql))
		return;
	
	int rows = 0;
	void *result = db_result(m_DB);
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

void CNew::SetItemId(int v)
{
	m_ItemID = v;
}

void CNew::SetPictureId(int id)
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

void CNew::SetCharacteristic(wxString v)
{
	m_Characteristic = v;
}

void CNew::SetOnPosition(bool v)
{
	m_OnPosition = v;
}

void CNew::SetInMonitoring(bool v)
{
	m_InMonitoring = v;
}

void CNew::SetHost(wxString v)
{
	m_Host = v;
}

void CNew::SetPort(wxString v)
{
	m_Port = v;
}

void CNew::SetBaseStation(wxString id)
{
	m_BaseStationID = id;
}

void CNew::SetTime(wxString v)
{
	m_Time = v;
}

void CNew::SetIala(wxString v)
{
	m_Iala = v;
}

void CNew::SetCode(wxString v)
{
	m_Code = v;
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

int CNew::GetPictureId()
{
	return m_PicturePanel->GetPictureId();
}

wxString CNew::GetCharacteristic()
{
	return m_CharacteristicText->GetValue();
}

CItemPanel *CNew::GetItemPanel()
{
	return m_ItemPanel;
} 

CLightPanel *CNew::GetLightPanel()
{
	return m_LightPanel;
}

CTimePanel *CNew::GetTimePanel()
{
	return m_TimePanel;
}

bool CNew::GetOnPosition()
{
	return m_CheckOnPosition->GetValue();
}

bool CNew::GetInMonitoring()
{
	return m_CheckInMonitoring->GetValue();
}

wxString CNew::GetHost()
{
	return m_TextHost->GetValue();
}

wxString CNew::GetPort()
{
	return m_TextPort->GetValue();
}

int CNew::GetBaseStationId()
{
	return (int)m_BaseStationCombo->GetClientData(m_BaseStationCombo->GetSelection());
}

wxString CNew::GetCode()
{
	return m_TextCode->GetValue();
}

wxString CNew::GetIala()
{
	return m_TextIala->GetValue();
}

wxString CNew::GetTime()
{
	return m_TextTime->GetValue();
}