#include "dialog.h"
#include "conf.h"
#include "tools.h"
#include "listctrl.h"
#include "new.h"
#include "db.h"
#include <wx/rawbmp.h>
#include <string.h>
#include <wx/mstream.h>
#include <wx/statline.h>
#include "wx/laywin.h"
#include "light.h"
#include "conf.h"
#include "symbolgroup.h"
#include "export.h"
#include "datedialog.h"

SHeader Header[] =
{

	{CONTROL_SYMBOL,150, {FI_SYMBOL_NUMBER , FN_SYMBOL_NUMBER, MSG_SYMBOL_NUMBER} },
	{CONTROL_SYMBOL,250, {FI_SYMBOL_NAME , FN_SYMBOL_NAME, MSG_NAME} },
	{CONTROL_SYMBOL,250, {FI_SYMBOL_INFO , FN_SYMBOL_INFO, MSG_INFO} },

	{CONTROL_ITEM,250, {FI_ITEM_NAME , FN_ITEM_NAME, MSG_NAME} },
	{CONTROL_ITEM,100, {FI_ITEM_TYPE , FN_ITEM_TYPE, MSG_TYPE} },
	{CONTROL_ITEM,250, {FI_ITEM_INFO , FN_ITEM_INFO, MSG_INFO} },
	
	{CONTROL_AREA,250, {FI_AREA_NAME , FN_AREA_NAME, MSG_NAME} },
	{CONTROL_AREA,250, {FI_AREA_INFO , FN_AREA_INFO, MSG_INFO} },

	{CONTROL_SEAWAY,250, {FI_SEAWAY_NAME , FN_SEAWAY_NAME, MSG_NAME} },
	{CONTROL_SEAWAY,250, {FI_SEAWAY_INFO , FN_SEAWAY_INFO, MSG_INFO} },

	{CONTROL_SYMBOL_TYPE,250, {FI_SYMBOL_TYPE_NAME , FN_SYMBOL_TYPE_NAME, MSG_NAME} },
	{CONTROL_SYMBOL_TYPE,250, {FI_SYMBOL_TYPE_INFO , FN_SYMBOL_TYPE_INFO, MSG_INFO} },
		
	{CONTROL_PICTURE,250, {FI_PICTURE_NAME  , FN_PICTURE_NAME, MSG_NAME} },
	{CONTROL_PICTURE,100, {FI_PICTURE_INFO  , FN_PICTURE_INFO, MSG_INFO} },

	{CONTROL_SYMBOL_GROUP,250, {FI_SYMBOL_GROUP_NAME  , FN_SYMBOL_GROUP_NAME, MSG_NAME} },
	{CONTROL_SYMBOL_GROUP,100, {FI_SYMBOL_GROUP_INFO  , FN_SYMBOL_GROUP_INFO, MSG_INFO} },
	
	{CONTROL_BASE_STATION,250, {FI_BASE_STATION_NAME  , FN_BASE_STATION_NAME, MSG_NAME} },
	{CONTROL_BASE_STATION,100, {FI_BASE_STATION_IP  , FN_BASE_STATION_IP, MSG_IP} },
	{CONTROL_BASE_STATION,100, {FI_BASE_STATION_LOCAL_UTC_TIME  , FN_BASE_STATION_IP, MSG_TIME} },
	{CONTROL_BASE_STATION,100, {FI_BASE_STATION_INFO  , FN_BASE_STATION_INFO, MSG_INFO } },

	{CONTROL_CHARACTERISTIC,250, {FI_CHARACTERISTIC_NAME  , FN_CHARACTERISTIC_NAME, MSG_NAME} },
	{CONTROL_CHARACTERISTIC,50, {FI_CHARACTERISTIC_CODE  , FN_CHARACTERISTIC_CODE, MSG_CODE} },
	{CONTROL_CHARACTERISTIC,100, {FI_CHARACTERISTIC_IALA  , FN_CHARACTERISTIC_IALA, MSG_IALA} },
	{CONTROL_CHARACTERISTIC,100, {FI_CHARACTERISTIC_TIME  , FN_CHARACTERISTIC_TIME, MSG_TIME} },
	
	{CONTROL_SBMS,80,  {FI_SBMS_SBMSID  , FN_SBMS_SBMSID, MSG_SBMSID} },
	{CONTROL_SBMS,80,  {FI_SBMS_ID_BASE_STATION  , FN_SBMS_ID_BASE_STATION, MSG_BASE_STATION} },
	{CONTROL_SBMS,80,  {FI_SBMS_MMSI  , FN_SBMS_MMSI, MSG_MMSI} },
	{CONTROL_SBMS,180, {FI_SBMS_NAME  , FN_SBMS_NAME, MSG_NAME} },
	{CONTROL_SBMS,100, {FI_SBMS_LOCAL_UTC_TIME  , FN_SBMS_LOCAL_UTC_TIME, MSG_UTC_TIME} },
	
	{CONTROL_GE64,180, {FI_GE64_NAME  , FN_GE64_NAME, MSG_NAME} },
	{CONTROL_GE64,100, {FI_GE64_LOCAL_UTC_TIME  , FN_GE64_LOCAL_UTC_TIME, MSG_UTC_TIME} },
	
	//alarm master/slave
	{CONTROL_SYMBOL_ALARM,150, {0 , TABLE_SYMBOL"."FN_SYMBOL_NAME, MSG_NAME} },
	{CONTROL_SYMBOL_ALARM,250, {1 , TABLE_SYMBOL"."FN_SYMBOL_NUMBER, MSG_SYMBOL_NUMBER } },
	
	{CONTROL_SBMS_ALARM,80,  {0  , TABLE_ALARM"."FN_ALARM_NAME, MSG_ALARM} },
	{CONTROL_SBMS_ALARM,180, {1  , FN_SBMS_ALARM_SET_LOCAL_UTC_TIME, MSG_SET_TIME} },
	{CONTROL_SBMS_ALARM,180, {2  , FN_SBMS_ALARM_UNSET_LOCAL_UTC_TIME, MSG_UNSET_TIME} },

	//komendy master/slave
	{CONTROL_SYMBOL_COMMAND,150, {FI_SYMBOL_NUMBER , FN_SYMBOL_NAME, MSG_SYMBOL_NUMBER} },
	{CONTROL_SYMBOL_COMMAND,250, {FI_SYMBOL_NAME , FN_SYMBOL_NUMBER, MSG_NAME} },
	
	{CONTROL_COMMAND,80,  {FI_COMMAND_ID  , FN_COMMAND_ID, MSG_ID} },
	{CONTROL_COMMAND,80,  {FI_COMMAND_COMMAND  , FN_COMMAND_COMMAND, MSG_COMMAND} },
	{CONTROL_COMMAND,80,  {FI_COMMAND_ID_COMMAND  , FN_COMMAND_ID_COMMAND, MSG_CONFIRMED} },
	
	{-1},

};

SIds Id[] =
{
	{CONTROL_SYMBOL, COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_SYMBOL},
	{CONTROL_ITEM, COLUMN_ITEM_WITH_ID, COLUMN_ITEM_WITH_NAME,MSG_ITEMS},
	{CONTROL_AREA, COLUMN_WITH_ID, COLUMN_WITH_NAME, MSG_AREA},
	{CONTROL_SEAWAY, COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_SEAWAY},
	{CONTROL_SYMBOL_TYPE, COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_SYMBOL_TYPE},
	{CONTROL_PICTURE,COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_PICTURE},
	{CONTROL_SYMBOL_GROUP,COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_SYMBOL_GROUP},
	{CONTROL_BASE_STATION,COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_BASE_STATION},
	{CONTROL_SBMS,COLUMN_WITH_ID, COLUMN_SBMS_WITH_NAME,MSG_DRIVER},
	{CONTROL_SBMS_ALARM,COLUMN_WITH_ID, COLUMN_SBMS_WITH_NAME,MSG_DRIVER},
	{CONTROL_SYMBOL_ALARM, FI_SYMBOL_ID, COLUMN_WITH_NAME,MSG_SYMBOL},
	{CONTROL_GE64, COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_DRIVER},
};

BEGIN_EVENT_TABLE(CDialog,wxDialog)
	EVT_BUTTON(ID_EXPORT,OnExport)
	EVT_CHAR_HOOK(OnCharHook)
END_EVENT_TABLE()

CDialog::CDialog(void *db,int control_type, bool picker)
	:wxDialog(NULL,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxMINIMIZE_BOX | wxMAXIMIZE_BOX)
{
	
	m_ControlType = control_type;
	m_ButtonOk = NULL;
	m_Picker = picker;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
	
	m_DialogPanel = new CDialogPanel(db,control_type,this);
	Sizer->Add(m_DialogPanel,1,wxALL|wxEXPAND,0);
	
	//wxStaticLine *Line = new wxStaticLine(this);
	//Sizer->Add(Line,0,wxALL|wxEXPAND,5);
	
	Sizer->Add(GetButtonPanel(this),0,wxALL|wxEXPAND,5);
	
	ReadConfig();
	Center();
	
}

CDialog::CDialog(void *db,int control_master, int control_slave,bool picker)
:wxDialog(NULL,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,  wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER |wxMINIMIZE_BOX|wxMAXIMIZE_BOX)
{
	
	m_ControlType = control_master;
	m_ButtonOk = NULL;
	m_Picker = picker;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
	
	wxBoxSizer *HSizer = new wxBoxSizer(wxHORIZONTAL);
	Sizer->Add(HSizer,1,wxALL|wxEXPAND,0);

	m_DialogPanel = new CDialogPanel(db,control_master,this);
	Sizer->Add(m_DialogPanel,1,wxALL|wxEXPAND,0);
	
	m_DialogSlave = new CDialogPanel(db,control_slave,this,true);
	Sizer->Add(m_DialogSlave,1,wxALL|wxEXPAND,0);
		
	m_DialogPanel->SetSlave(m_DialogSlave);
	
	//wxStaticLine *Line = new wxStaticLine(this);
	//Sizer->Add(Line,0,wxALL|wxEXPAND,5);

	Sizer->Add(GetButtonPanel(this),0,wxALL|wxEXPAND,5);

	ReadConfig();
	Center();
	
}

CDialog::~CDialog()
{
	WriteConfig();
}

void CDialog::WriteConfig()
{
	wxFileConfig *FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetConfigFile(),wxEmptyString);
	FileConfig->Write(wxString::Format(_("%s/%d/%s"),KEY_DIALOG,m_ControlType,KEY_DIALOG_WIDTH),this->GetSize().GetWidth());
	FileConfig->Write(wxString::Format(_("%s/%d/%s"),KEY_DIALOG,m_ControlType,KEY_DIALOG_HEIGHT),this->GetSize().GetHeight());
	delete FileConfig;
}

void CDialog::ReadConfig()
{
	wxFileConfig *FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetConfigFile(),wxEmptyString);
    int width, height;
	FileConfig->Read(wxString::Format(_("%s/%d/%s"),KEY_DIALOG,m_ControlType,KEY_DIALOG_WIDTH),&width,DEFAULT_DIALOG_WIDTH );
	FileConfig->Read(wxString::Format(_("%s/%d/%s"),KEY_DIALOG,m_ControlType,KEY_DIALOG_HEIGHT),&height,DEFAULT_DIALOG_HEIGHT);
	
	this->SetSize(width,height);
	delete FileConfig;
}

wxPanel *CDialog::GetButtonPanel(wxWindow *parent)
{

	wxPanel *Panel = new wxPanel(parent);
		
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);	
	
	wxStaticText *LabelProductInfo = new wxStaticText(Panel,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	Sizer->Add(LabelProductInfo,0,wxALL,5);
	Sizer->AddStretchSpacer(1);
	
	if(m_Picker)
	{
		Sizer->AddStretchSpacer();
		m_ButtonOk = new wxButton(Panel,wxID_OK,GetMsg(MSG_OK));
		Sizer->Add(m_ButtonOk,0,wxALL,5);
		wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CANCEL));
		Sizer->Add(ButtonClose,0,wxALL,5);
	
	}else{
	
		Sizer->AddStretchSpacer();
		if(m_ControlType == CONTROL_SYMBOL_ALARM)
		{
			wxButton *ButtonExport = new wxButton(Panel,ID_EXPORT,GetMsg(MSG_EXPORT));
			Sizer->Add(ButtonExport,0,wxALL,2);
		}
		wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CLOSE));
		Sizer->Add(ButtonClose,0,wxALL,2);
	
	}
	
	return Panel;

}

int CDialog::_GetId()
{
	return m_DialogPanel->_GetId();
}

wxString CDialog::_GetName()
{
	return m_DialogPanel->_GetName();
}

void CDialog::OnExport(wxCommandEvent &event)
{
	m_DialogPanel->OnExport();
}

void CDialog::OnCharHook(wxKeyEvent &event)
{
	if(IsModal())
	{
		switch( event.GetKeyCode() ) 
		{
			case WXK_RETURN:	EndModal(wxID_OK);	break;
			case WXK_LEFT:							break;
			case WXK_RIGHT:							break;
			case WXK_UP:							break;
			case WXK_DOWN:							break;
			case 61:								break;
			case 45:								break;
		}
	}

	event.Skip();
}

BEGIN_EVENT_TABLE(CDialogPanel,wxPanel)
	EVT_LISTBOX(ID_FILTER,OnListBox)
	EVT_TIMER(ID_TICK_SEARCH,OnTickSearch)
	EVT_TEXT(ID_SEARCH,OnSearchText)
	EVT_BUTTON(ID_REFRESH,OnRefresh)
	EVT_COMBOBOX(ID_DRIVER,OnComboDriver)
END_EVENT_TABLE()

CDialogPanel::CDialogPanel(void *db,int control_type, wxWindow *parent,bool slave)
:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	m_DB = db;
	m_SearchTextChanged = false;
	m_IsSlave = slave;
	m_Parent = parent;
	m_IDType = -1;
	m_ListBox = NULL;
	m_Table = wxEmptyString;
	m_IDMaster = -1;
	m_ControlType = control_type;
	m_ListBox = NULL;
	m_TopLabel = NULL;
	m_Slave = NULL;
	m_PicturePanel = NULL;
	SetTable();
		
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
	//wxPanel *TopPanel = new wxPanel(this);
	//Sizer->Add(TopPanel,0,wxALL|wxEXPAND,5);
	//wxBoxSizer *TopPanelSizer = new wxBoxSizer(wxHORIZONTAL);
	//TopPanel->SetSizer(TopPanelSizer);

	//m_TopLabel = new wxStaticText(TopPanel,wxID_ANY,wxEmptyString);
	//TopPanelSizer->Add(m_TopLabel,0,wxALL,5);
	if(!slave)
		Sizer->Add(GetSearchPanel(this),0,wxALL|wxEXPAND,2);
	Sizer->Add(GetPanel(this),1,wxALL|wxEXPAND,0);
	
	Sizer->Add(GetStatusPanel(this),0,wxALL|wxEXPAND,0);
	Read();

	m_Ticker = new wxTimer(this,ID_TICK_SEARCH);	//frequency
	m_Ticker->Start(1000);
	

	ReadConfig();
			
}

CDialogPanel::~CDialogPanel()
{
	m_Ticker->Stop();
	delete m_Ticker;
	WriteConfig();
}

void CDialogPanel::WriteConfig()
{
	wxFileConfig *FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetConfigFile(),wxEmptyString);
	wxListItem item;
	wxString col;
	for(int i = 0; i < m_List->GetColumnCount(); i++)
    {
		m_List->GetColumn(i,item);
        col.Append(wxString::Format(wxT("%d"),item.GetWidth()));
        col.Append(_(COLUMN_SEPARATOR));
	}
	
	FileConfig->Write(wxString::Format(_("%s/%d/%s"),KEY_DIALOG,m_ControlType,KEY_COLUMN_WIDTH),col);
	delete FileConfig;

}

void CDialogPanel::ReadConfig()
{
	long _width;
    int i  = 0;
	wxFileConfig *FileConfig = new wxFileConfig(_(PRODUCT_NAME),wxEmptyString,GetConfigFile(),wxEmptyString);
    wxString str = FileConfig->Read(wxString::Format(_("%s/%d/%s"),KEY_DIALOG,m_ControlType,KEY_COLUMN_WIDTH), wxEmptyString );
	
	int pos = str.Find(wxT(COLUMN_SEPARATOR));
	
    while (pos > 0)
    {
        wxString width = str.substr(0,pos);
        width.ToLong(&_width);
		m_List->SetColumnWidth(i,_width);
        str = str.substr(pos + 1,str.Length());
        pos = str.Find(wxT(COLUMN_SEPARATOR));
        i++;
    }

	delete FileConfig;
}

void CDialogPanel::OnListBox(wxCommandEvent &event)
{
	int sel = event.GetSelection() - 1;
	
	if(sel == -1)
	{
		m_IDType = -1;	
	}else{
		
		m_IDType = (int)m_ListBox->GetClientData(event.GetSelection());
	}
		
	Clear();
	Read();
}

void CDialogPanel::OnTickSearch(wxTimerEvent &event)
{
	if(m_SearchTextChanged)
	{
		m_SearchTextChanged = false;
		Clear();
		Read();
	}
}

void CDialogPanel::OnSearchText(wxCommandEvent &event)
{
	if(m_SearchText->GetValue().CmpNoCase(GetSearchText()) != 0)
	{
		SetSearchText(m_SearchText->GetValue().wc_str());
		m_SearchTextChanged = true;
	}
	
}

void CDialogPanel::OnSearchEnter(wxCommandEvent &event)
{
	SetSearchText(m_SearchText->GetValue().wc_str());
	m_SearchTextChanged = true;
}

void CDialogPanel::OnComboDriver(wxCommandEvent &event)
{
	m_Order = wxEmptyString;
	m_Field = wxEmptyString;
	int id = (int)m_ComboDriver->GetClientData(event.GetSelection());
	SetControlType(id);
	InitList();
	SetTable();
	Clear();
	Read();
}

void CDialogPanel::OnRefresh(wxCommandEvent &event)
{
	Clear();
	Read();
	Select();
}

void CDialogPanel::OnExport()
{
	switch(m_ControlType)
	{
		case CONTROL_SYMBOL_ALARM:	ExportAlarmDialog();	break;
	}
}

void CDialogPanel::ExportAlarmDialog()
{
	CDateDialog *DateDialog = new CDateDialog();
	
	if(DateDialog->ShowModal() == wxID_OK)
	{
		ExportAlarm(m_DB,DateDialog->GetFrom().FormatISODate(),DateDialog->GetTo().FormatISODate());
	}

	delete DateDialog;
}


void CDialogPanel::SetSearchText(const wchar_t *txt)
{
	m_SearchTextValue = txt;
}

const wchar_t *CDialogPanel::GetSearchText()
{
	return m_SearchTextValue;
}

bool CDialogPanel::GetSearchTextChanged()
{
	return m_SearchTextChanged;
}

void CDialogPanel::SetSearchTextChanged(bool value)
{
	m_SearchTextChanged = value;
}

void CDialogPanel::SetSlave(CDialogPanel *ptr)
{
	m_Slave = ptr;
}

void CDialogPanel::SetControlType(int v)
{
	m_ControlType = v;
}

wxPanel *CDialogPanel::GetPanel(wxWindow *Parent)
{
	switch(m_ControlType)
	{
		case CONTROL_ITEM:			return GetItemPanel(Parent);
		case CONTROL_SYMBOL:		return GetSymbolPanel(Parent);
		case CONTROL_PICTURE:		return GetPicturePanel(Parent);
		case CONTROL_SBMS:			return GetSBMSPanel(Parent);
		default:
			return GetPanelList(Parent);
	}
	
	return NULL;
}

wxPanel *CDialogPanel::GetStatusPanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	Panel->SetBackgroundColour(wxColor(200,200,200));
	Panel->SetSizer(Sizer);
	
	m_RecordCount = new wxStaticText(Panel,wxID_ANY,wxEmptyString);
	Sizer->Add(m_RecordCount,0,wxALL|wxEXPAND,5);

	return Panel;
}

wxPanel *CDialogPanel::GetDriverFilterPanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
		
	m_ComboDriver = new wxComboBox(Panel,ID_DRIVER,wxEmptyString,wxDefaultPosition,wxDefaultSize,NULL,0, wxCB_READONLY);
	int id = m_ComboDriver->Append(GetMsg(MSG_SBMS));
	m_ComboDriver->SetClientData(id,(int*)CONTROL_SBMS);
	
	id = m_ComboDriver->Append(GetMsg(MSG_GE64));
	m_ComboDriver->SetClientData(id,(int*)CONTROL_GE64);
	
	m_ComboDriver->SetSelection(0);
	Sizer->Add(m_ComboDriver,0,wxALL|wxEXPAND,0);

	return Panel;
}

wxPanel *CDialogPanel::GetSymbolFilterPanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
	wxStaticBoxSizer *Sizer1 = new wxStaticBoxSizer(wxVERTICAL,Panel,GetMsg(MSG_FILTER));
	Sizer->Add(Sizer1,1,wxALL|wxEXPAND,0);

	wxFlexGridSizer *FlexSizer = new wxFlexGridSizer(2);
	Sizer1->Add(FlexSizer,1,wxALL|wxEXPAND,0);
		
	wxCheckBox *CheckInMOnitoring = new wxCheckBox(Panel,wxID_ANY,GetMsg(MSG_SYMBOL_IN_MONITORING));
	FlexSizer->AddSpacer(1);
	FlexSizer->Add(CheckInMOnitoring,0,wxALL,2);
		
	wxStaticText *LabelArea = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_AREA));
	FlexSizer->Add(LabelArea,0,wxALL,2);
	wxComboBox *ComboArea = GetCombo(m_DB,Panel,TABLE_AREA,wxEmptyString,FI_AREA_ID,FI_AREA_NAME, true);
	ComboArea->SetSelection(0);
	FlexSizer->Add(ComboArea,0,wxALL|wxEXPAND,2);
	
	wxStaticText *LabelSeaway = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SEAWAY));
	FlexSizer->Add(LabelSeaway,0,wxALL,2);
	wxComboBox *ComboSeaway = GetCombo(m_DB,Panel,TABLE_SEAWAY,wxEmptyString,FI_SEAWAY_ID,FI_SEAWAY_NAME, true);
	ComboSeaway->SetSelection(0);
	FlexSizer->Add(ComboSeaway,0,wxALL|wxEXPAND,2);
	
	wxStaticText *LabelSymbolType = new wxStaticText(Panel,wxID_ANY,GetMsg(MSG_SYMBOL_TYPE));
	FlexSizer->Add(LabelSymbolType,0,wxALL,2);
	wxComboBox *ComboSymbolType = GetCombo(m_DB,Panel,TABLE_SYMBOL_TYPE,wxEmptyString,FI_SYMBOL_TYPE_ID,FI_SYMBOL_TYPE_NAME, true);
	ComboSymbolType->SetSelection(0);
	FlexSizer->Add(ComboSymbolType,0,wxALL|wxEXPAND,2);

	return Panel;
}


wxPanel *CDialogPanel::GetSearchPanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	Panel->SetBackgroundColour(wxColor(200,200,200));
	Panel->SetSizer(Sizer);

	wxButton *ButtonRefresh = new wxButton(Panel,ID_REFRESH,GetMsg(MSG_REFRESH));
	Sizer->Add(ButtonRefresh,0,wxALL,1);
	m_SearchText = new wxSearchCtrl(Panel,ID_SEARCH,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER);
	Sizer->AddStretchSpacer(1);
	Sizer->Add(m_SearchText,0,wxALL|wxALIGN_RIGHT,3);

	return Panel;
}

wxPanel *CDialogPanel::GetSBMSPanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
	Sizer->Add(GetDriverFilterPanel(Panel),0,wxALL|wxEXPAND,0);
	Sizer->Add(GetPanelList(Panel),1,wxALL|wxEXPAND,0);
		
	return Panel;
}


wxPanel *CDialogPanel::GetSymbolPanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
	Sizer->Add(GetPanelList(Panel),1,wxALL|wxEXPAND,0);

	//Sizer->Add(GetSymbolFilterPanel(Panel),0,wxALL|wxEXPAND,0);

	m_PicturePanel = new CPicturePanel(m_DB, Panel);
	Sizer->Add(m_PicturePanel,0,wxALL|wxEXPAND,5);

	return Panel;
}


wxPanel *CDialogPanel::GetItemPanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
	Sizer->Add(GetPanelList(Panel),1,wxALL|wxEXPAND,0);
	m_ListBox = GetFilterList(m_DB,Panel,ID_FILTER);
	Sizer->Add(m_ListBox,0,wxALL|wxEXPAND,0);
					
	return Panel;
}

wxPanel *CDialogPanel::GetSymbolItemPanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
	Sizer->Add(GetPanelList(Panel),1,wxALL|wxEXPAND,0);
	return Panel;
}

wxPanel *CDialogPanel::GetPicturePanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
	m_PicturePanel = new CPicturePanel(m_DB,Panel);
	Sizer->Add(GetPanelList(Panel),1,wxALL|wxEXPAND,0);
	Sizer->Add(m_PicturePanel,0,wxALL|wxEXPAND,5);
	return Panel;
}

/*
wxListBox *CDialogPanel::GetFilterList(wxWindow *Parent)
{
	wxListBox *Filter = new wxListBox(Parent,ID_FILTER);
	Filter->Append(GetMsg(MSG_ALL));

	wxArrayString ar;
	wxString sql = wxString::Format(_("SELECT * FROM `%s` ORDER BY name"),TABLE_ITEM_TYPE);
	if(!my_query(sql))
		return Filter;
	
	int rows = 0;
	void *result = db_result();
	char **row;
		
	int i = 0;
	while(row = (char**)db_fetch_row(result))
	{
		wxString name(row[FI_ITEM_TYPE_NAME],wxConvUTF8);
		ar.Add(name);
		int id = Filter->Append(name);
		Filter->SetClientData(id,(int*)atoi(row[FI_ITEM_TYPE_ID]));
	}

	db_free_result(result);
	
	//m_FilterArray = GetItemType();
	//Filter->Append(m_FilterArray);
	return Filter;
}

wxComboBox *CDialogPanel::GetFilterCombo(wxWindow *Parent)
{
	wxComboBox *Filter = new wxComboBox(Parent,ID_FILTER,wxEmptyString,wxDefaultPosition,wxDefaultSize,NULL,0, wxCB_READONLY);
	Filter->Append(GetMsg(MSG_ALL));

	wxArrayString ar;
	wxString sql = wxString::Format(_("SELECT * FROM `%s` ORDER BY name"),TABLE_ITEM_TYPE);
	if(!my_query(sql))
		return Filter;
	
	int rows = 0;
	void *result = db_result();
	char **row;
		
	int i = 0;
	while(row = (char**)db_fetch_row(result))
	{
		wxString name(row[FI_ITEM_TYPE_NAME],wxConvUTF8);
		ar.Add(name);
		int id = Filter->Append(name);
		Filter->SetClientData(id,(int*)atoi(row[FI_ITEM_TYPE_ID]));
	}

	db_free_result(result);
	
//	m_FilterArray = GetItemType();
	//Filter->Append(m_FilterArray);
	return Filter;
}
*/
void CDialogPanel::InitList()
{
	int id = 0;
	wxListItem item;
	int counter = 0;
	SHeader h;

	m_List->ClearColumns();
	m_List->DeleteAllColumns();

	while(Header[id].id_control != -1)
	{
		h = Header[id];
		
		if(h.id_control == m_ControlType)
		{
			h = Header[id];
			item.SetWidth(h.width);	
			item.SetText(GetMsg(h.column.id_msg));	
			m_List->InsertColumn(counter,item);
			m_List->_AddColumn(h.column.id,h.column.name);
			counter++;
		}
	
		id++;
	}

	id = 0;
	
	while(Id[id].id_control != -1)
	{
		SIds i = Id[id];
		if(i.id_control == m_ControlType)
		{
			m_List->SetColumnWithId(i.col_with_id);
			m_List->SetColumnWithName(i.col_with_name);
			//if(m_TopLabel)
			//	m_TopLabel->SetLabel(GetMsg(i.id_label));
			if(!m_IsSlave)
				m_Parent->SetLabel(GetMsg(i.id_label));
			break;
		} 
	
		id++;
	}

	m_List->SetControlType(m_ControlType,this);
	m_List->InitColumns();
	m_List->SetFocus();
	//m_List->SetItemState(3,wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);

}

wxPanel *CDialogPanel::GetPanelList(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
	m_List = new CListCtrl(m_DB, Panel,wxLC_REPORT |  wxLC_VIRTUAL | wxLC_SINGLE_SEL | wxLC_ALIGN_LEFT );
	Sizer->Add(m_List,1,wxALL|wxEXPAND,0);
	InitList();
	
	return Panel;

}

void CDialogPanel::SetTable()
{
	switch(m_ControlType)
	{
		case CONTROL_SYMBOL:			m_Table = TABLE_SYMBOL;			break;
		case CONTROL_SYMBOL_ITEM:		m_Table = TABLE_SYMBOL_ITEM;	break;
		case CONTROL_ITEM:				m_Table = TABLE_ITEM;			break;
		case CONTROL_AREA:				m_Table = TABLE_AREA;			break;
		case CONTROL_SEAWAY:			m_Table = TABLE_SEAWAY;			break;
		case CONTROL_SYMBOL_TYPE:		m_Table = TABLE_SYMBOL_TYPE;	break;
		case CONTROL_PICTURE:			m_Table = TABLE_PICTURE;		break;
		case CONTROL_SYMBOL_GROUP:		m_Table = TABLE_SYMBOL_GROUP;	break;
		case CONTROL_BASE_STATION:		m_Table = TABLE_BASE_STATION;	break;
		case CONTROL_CHARACTERISTIC:	m_Table = TABLE_CHARACTERISTIC; break;
		case CONTROL_SBMS:				m_Table = TABLE_SBMS;			break;
		case CONTROL_GE64:				m_Table = TABLE_GE64;			break;
		case CONTROL_SBMS_ALARM:		m_Table = TABLE_ALARM;			break;
		case CONTROL_SYMBOL_ALARM:		m_Table = TABLE_SYMBOL;			break;
		case CONTROL_SYMBOL_COMMAND:	m_Table = TABLE_SYMBOL;			break;
		//case CONTROL_COMMAND:			m_Table = TABLE_COMMAND;		break;
	}
}


void CDialogPanel::Read()
{
	ReadData();
	SetStatus();
}

void CDialogPanel::SetStatus()
{
	m_RecordCount->SetLabel(wxString::Format(_("%d"),m_List->GetItemCount()));
}

void CDialogPanel::ReadData()
{
	wxString sql;
	switch(m_ControlType)
	{
		case CONTROL_PICTURE:
			sql = wxString::Format(_("SELECT %s,%s,%s FROM `%s` WHERE"),FN_PICTURE_ID,FN_PICTURE_NAME,FN_PICTURE_INFO,m_Table); //sql dla zdj�cia bez selektu bloba kt�ry spowalnia bo jest du�ym polem danych
		break;
		case CONTROL_ITEM:
			sql = ReadItems();
		break;
		
		case CONTROL_SBMS_ALARM:
			sql = wxString::Format(_("SELECT `"TABLE_ALARM"`.name,`"TABLE_SBMS_ALARM"`.set_local_utc_time,`"TABLE_SBMS_ALARM"`.unset_local_utc_time FROM `%s`,`%s`,`%s` WHERE `"TABLE_SBMS"`.id=`"TABLE_SBMS_ALARM"`.id_sbms AND `"TABLE_ALARM"`.id=`"TABLE_SBMS_ALARM"`.id_alarm AND id_symbol='%d' AND "),TABLE_SBMS_ALARM,TABLE_SBMS,TABLE_ALARM,m_IDMaster);
		break;
		case CONTROL_SYMBOL_ALARM:

			//sql = wxString::Format(_("SELECT * FROM `%s`,`%s`,`%s` WHERE `%s`.id=`%s`.id_symbol AND `%s`.id_sbms > 0 AND"),TABLE_SYMBOL,TABLE_SBMS_ALARM,TABLE_SYMBOL,TABLE_SBMS_ALARM,TABLE_SYMBOL);
			sql = wxString::Format(_("SELECT * FROM `%s` WHERE"),TABLE_SYMBOL);
			//sql =_("SELECT symbol.name,alarm.name,concat(IFNULL(sbms.id,''),IFNULL(ge64.id,'')) as id from symbol left join sbms ON symbol.id = sbms.id_symbol left join sbms_alarm ON sbms_alarm.id_sbms = sbms.id left join ge64 ON symbol.id = ge64.id_symbol left join ge64_alarm ON ge64_alarm.id_ge64 = ge64.id left join alarm ON alarm.id = sbms_alarm.id_alarm OR alarm.id = ge64_alarm.id_alarm WHERE (sbms_alarm.active=0 OR ge64_alarm.active=0) AND ");
		break;

		//case CONTROL_SYMBOL_COMMAND:
			//sql = wxString::Format(_("SELECT * FROM `%s`,`%s` WHERE `%s`.id_driver=`%s`.id_sbms AND"),TABLE_SYMBOL,TABLE_COMMAND,TABLE_SYMBOL,TABLE_COMMAND);
		//break;

		default:
			sql = wxString::Format(_("SELECT * FROM `%s` WHERE"),m_Table);
		break;
	}

	SHeader h;
	int id = 0;
	int counter = 0;
	
	while(Header[id].id_control != -1)
	{
		h = Header[id];
		if(h.id_control == m_ControlType)
			counter++;
		id++;
	}

	id = 0;

	int lcount = 1;
	sql << " (";
	
	while(Header[id].id_control != -1)
	{
		h = Header[id];
		
		if(h.id_control == m_ControlType)
		{
			sql << wxString::Format(_("%s LIKE '%%%s%%'"),h.column.name,m_SearchTextValue);
			if(counter > lcount)
				sql << " OR ";
			lcount++;
		}

		id++;
	}
	
	sql << ")";	


	//group BY
	switch(m_ControlType)
	{
		//case CONTROL_SYMBOL_ALARM:
		case CONTROL_SYMBOL_COMMAND:
			sql << wxString::Format(_(" GROUP BY `%s`.name"),TABLE_SYMBOL);
		break;
	}


	if(m_Field != wxEmptyString)		
		sql <<	wxString::Format(_(" ORDER BY %s %s"),m_Field,m_Order);
		

	m_List->Read(sql);
	m_List->Refresh();
	
}

wxString CDialogPanel::ReadItems()
{	
	wxString sql;

	if(m_IDType == -1)
	{
		return sql = wxString::Format(_("SELECT * FROM `%s` WHERE"),m_Table);

	}else{
		return 	sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_type = '%d' AND"),m_Table ,m_IDType);
	}
}

/*
void CDialogPanel::ReadPicture()
{	
xString sql;
	
}


void CDialogPanel::ReadOthers()
{	
	wxString sql;
	if(m_Field == wxEmptyString)		
		sql = wxString::Format(_("SELECT * FROM `%s`"),m_Table);
	else
		sql = wxString::Format(_("SELECT * FROM `%s` ORDER BY %s %s"),m_Table,m_Field,m_Order);
	
	m_List->Read(sql);
	m_List->Refresh();

}

void CDialogPanel::ReadItems()
{	
	wxString sql;

	if(m_IDType == -1)
	{
		if(m_Field == wxEmptyString)		
			sql = wxString::Format(_("SELECT * FROM `%s`"),m_Table);
		else
			sql = wxString::Format(_("SELECT * FROM `%s` ORDER BY %s %s"),m_Table,m_Field,m_Order);
	}else{

		if(m_Field == wxEmptyString)		
			sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_type = '%d'"),m_Table,m_IDType);
		else
			sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_type = '%d' ORDER BY %s %s"),m_Table,m_IDType,m_Field,m_Order);
	}

	m_List->Read(sql);
	m_List->Refresh();

}

void CDialogPanel::ReadSymbolItems()
{
	wxString sql;
	if(m_IDMaster == -1)
		return;

	if(m_IDType == -1)
	{
		if(m_Field == wxEmptyString)		
			sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_symbol = '%d'"),VIEW_SYMBOL_ITEM ,m_IDMaster);
		else
			sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_symbol = '%d' ORDER BY %s %s"), VIEW_SYMBOL_ITEM,m_IDMaster, m_Field,m_Order);
	}else{
		
		if(m_Field == wxEmptyString)		
			sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_symbol = '%d' AND id_type = '%d'"),VIEW_SYMBOL_ITEM,m_IDMaster, m_IDType);
		else
			sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_symbol = '%d' AND id_type = '%d' ORDER BY %s %s"),VIEW_SYMBOL_ITEM, m_IDMaster, m_IDType, m_Field,m_Order);
	}

	m_List->Read(sql);
	m_List->Refresh();

}
*/

void CDialogPanel::Clear()
{
	if(m_PicturePanel)
		m_PicturePanel->Clear();
	m_List->Clear();
}
	
void CDialogPanel::Select()
{
	m_List->Select();
}

void CDialogPanel::OnNew()
{
	switch(m_ControlType)
	{
		case CONTROL_ITEM:
		case CONTROL_ITEM_TYPE:
		case CONTROL_SYMBOL:
		case CONTROL_AREA:
		case CONTROL_SEAWAY:
		case CONTROL_SYMBOL_TYPE:
		case CONTROL_SYMBOL_GROUP:
		case CONTROL_BASE_STATION:
		case CONTROL_CHARACTERISTIC:
		case CONTROL_SBMS:
			New();	
		break;
				
		case CONTROL_PICTURE:
			NewPicture();
		break;
	}
	
}

void CDialogPanel::New()
{
	CNew *ptr = new CNew(m_DB,m_ControlType,m_IDType);
	ptr->Create();
	
	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql; 
		bool query = false;
		switch(m_ControlType)
		{
			case CONTROL_CHARACTERISTIC:
				NewCharacteristic(ptr);
			break;
			case CONTROL_ITEM:
				NewItem(ptr);
			break;
			case CONTROL_SYMBOL:
				NewSymbol(ptr);
			break;
			case CONTROL_ITEM_TYPE:
				sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s'"),m_Table,ptr->GetName(),ptr->GetInfo());
				query = true;
			break;
			case CONTROL_AREA:
			case CONTROL_SEAWAY:
			case CONTROL_SYMBOL_TYPE:
				sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s'"),m_Table,ptr->GetName(),ptr->GetInfo());
				query = true;
			break;
			case CONTROL_SYMBOL_GROUP:
				sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s', code='%s'"),m_Table,ptr->GetName(),ptr->GetInfo(),ptr->GetCode());
				query = true;
			break;
		}
		
		if(query)
		{
			if(!my_query(m_DB,sql))
			{
				delete ptr;
				return;
			}
		}
			
		Clear();
		Read();
		
	}
	
	delete ptr;
	
}

void CDialogPanel::NewSymbol(CNew *ptr)
{
	wxString sql;
	sql = wxString::Format(_("INSERT INTO %s SET id_area='%d', id_seaway='%d', id_symbol_type='%d', number='%s', lon ='%3.14f',lat='%3.14f',in_monitoring='%d',name='%s', info='%s'"),
		TABLE_SYMBOL, ptr->GetAreaId(), ptr->GetSeawayId(),ptr->GetSymbolTypeId(), ptr->GetNumber(),ptr->GetLon(),ptr->GetLat(),ptr->GetMonitoring(),ptr->GetName(),ptr->GetInfo());
	my_query(m_DB,sql);
	
	int id = db_last_insert_id(m_DB);
	
	//SBMS in use
	//sql = wxString::Format(_("UPDATE %s SET in_use='%d' WHERE id='%d'"),TABLE_SBMS,SBMS_IN_USE,ptr->GetSBMSId());
	//my_query(m_DB,sql);
	
	//light
	CLightPanel *LightPanel = ptr->GetLightPanel();

	for(size_t i = 0; i <LightPanel->GetCount(); i++)
	{
		CSector *Sector = LightPanel->GetSector(i);
		sql = wxString::Format(_("INSERT INTO %s SET id_symbol='%d' ,id_characteristic='%s', color='%d' ,coverage='%4.2f' ,sector_from='%4.2f' ,sector_to='%4.2f'"),
			TABLE_SYMBOL_LIGHT,id,Sector->GetIdCharacteristic(),Sector->GetColor().GetRGB(),Sector->GetCoverage(),Sector->GetSectorFrom(),Sector->GetSectorTo());
		my_query(m_DB,sql);
	}
	
	//item
	CItemPanel *ItemPanel = ptr->GetItemPanel();

	for(size_t i = 0; i < ItemPanel->GetCount(); i++)
	{
		CItem *Item = ItemPanel->GetItem(i);
		for(size_t j = 0 ;j < Item->GetCount(); j++)
		{
			CComboPanel *Combo = Item->GetCombo(j);
			sql = wxString::Format	(_("INSERT INTO `%s` SET id_item='%d',id_symbol ='%d'"),TABLE_SYMBOL_ITEM,Combo->_GetId(),id);
			my_query(m_DB,sql);
		}
	
	}
	
	//picture
	sql = wxString::Format	(_("DELETE FROM `%s` WHERE id_symbol ='%d'"),TABLE_SYMBOL_PICTURE,id);
	my_query(m_DB,sql);
	int pid = ptr->GetPictureId();
	if(pid > 0)
	{	sql = wxString::Format(_("INSERT INTO %s SET id_symbol='%d', id_picture='%d'"),TABLE_SYMBOL_PICTURE,id,pid);
		my_query(m_DB,sql);
	}

}

void CDialogPanel::NewCharacteristic(CNew *ptr)
{
	wxString sql;
	
	sql = wxString::Format(_("INSERT INTO %s SET name='%s',code ='%s', iala='%s', time='%s'"),m_Table,ptr->GetName(),ptr->GetCode(),ptr->GetIala(),ptr->GetTime());
	if(!my_query(m_DB,sql))
		return;
	
	int id = db_last_insert_id(m_DB);
	//time panel
	CTimePanel *TimePanel = ptr->GetTimePanel();

	for(size_t i = 0; i < TimePanel->GetCount(); i++)
	{
		CTime *ptr = TimePanel->GetTime(i);
		sql = wxString::Format	(_("INSERT INTO `%s` SET id_characteristic ='%d', _on='%s',_off='%s'"),TABLE_CHARACTERISTIC_ON_OFF,id,ptr->GetOn(),ptr->GetOff());
		my_query(m_DB,sql);
	}
	
}

void CDialogPanel::NewSymbolItem()
{
	if(m_IDMaster == -1)
		return;
	/*
	CDialog *ptr = new CDialog(CONTROL_ITEM,true);
	if(ptr->ShowModal() == wxID_OK)
	{
	
		wxTextEntryDialog dlg(this, GetMsg(MSG_QUANTITY),GetMsg(MSG_QUANTITY));
		dlg.SetValue(_("1"));
		dlg.SetValidator(wxTextValidator(wxFILTER_ALPHA));
		if (dlg.ShowModal() == wxID_OK)
		{
        
			wxString sql;
			sql = wxString::Format(_("INSERT INTO %s SET id_symbol='%s', id_item='%d'"),m_Table,m_IDMaster,ptr->_GetId());
			long counter;
			dlg.GetValue().ToLong(&counter);
			if(counter > MAX_ITEMS)
				counter = MAX_ITEMS;
			
			for(size_t i = 0; i < counter; i++)
			{
				my_query(sql);
			}
						
			Clear();
			Read();



		}
		dlg.Close();
	}
	
	delete ptr;
	*/
}

void CDialogPanel::NewItem(CNew *ptr)
{
	
	wxString sql;
	
	sql = wxString::Format(_("INSERT INTO %s SET id_type ='%d', name='%s', type='%s', info='%s'"),m_Table,ptr->GetItemType(),ptr->GetName(),ptr->GetType(),ptr->GetInfo());
	if(!my_query(m_DB,sql))
		return;

	int id = db_last_insert_id(m_DB);
	wxArrayPtrVoid controls = ptr->GetFeatureControls();

	for(size_t i = 0; i < controls.size(); i++)
	{
		wxTextCtrl *txt = (wxTextCtrl*)controls.Item(i);
		int id_feature = (int)txt->GetClientData();
		sql = wxString::Format	(_("DELETE FROM `%s` WHERE id_item ='%d' AND id_feature ='%d'"),TABLE_ITEM_VALUE,id,id_feature);
		my_query(m_DB,sql);
		sql = wxString::Format	(_("INSERT INTO `%s` SET id_item ='%d', id_feature ='%d',value='%s'"),TABLE_ITEM_VALUE,id,id_feature,txt->GetValue());
		my_query(m_DB,sql);
	}

		
}

void CDialogPanel::NewPicture()
{
	CNew *ptr = new CNew(m_DB,CONTROL_PICTURE,true); 
	ptr->Create();
	
	if(ptr->ShowModal() == wxID_OK)
	{
		wxString _sql;
		_sql = wxString::Format(_("INSERT INTO %s SET name ='%s', info='%s'"),m_Table,ptr->GetName(),ptr->GetInfo());
		if(!my_query(m_DB,_sql))
			return;
		
		int id = db_last_insert_id(m_DB);
		wxImage img =  ptr->GetPicture();
		UpdatePicture(img,id,img.GetType());
		Clear();
		Read();
	}
	
	delete ptr;

}
void CDialogPanel::UpdatePicture(wxImage image,int id, int type)
{	
						
	if(!image.IsOk())
		return;
	
	const char *sql = "UPDATE `%s` SET data='%s' WHERE id = '%d'";
	wxMemoryOutputStream stream;
	if(!image.SaveFile(stream,type))
		return;
	wxStreamBuffer *st = stream.GetOutputStreamBuffer();
	
	char *chunk = (char*)malloc(st->GetBufferSize() * 2);
	int data_size = db_escape_string( chunk, (const char*)st->GetBufferStart(), st->GetBufferSize());
	int table_len = strlen(TABLE_PICTURE);
	int new_sql_size = (strlen(sql) + table_len + data_size)*2;
	char *new_sql = (char*)malloc(new_sql_size);
	memset(new_sql,0,new_sql_size);
		
	int len = sprintf( new_sql,sql,TABLE_PICTURE,chunk,id);
	my_query(m_DB,new_sql,len);
	free(chunk);		
	free(new_sql);
	
}

void CDialogPanel::OnEdit(int id)
{
	switch(m_ControlType)
	{
		case CONTROL_PICTURE:			EditPicture(id);		break;
		case CONTROL_SYMBOL:			EditSymbol(id);			break;
		case CONTROL_ITEM:				EditItem(id);			break;
		case CONTROL_BASE_STATION:		EditBaseStation(id);	break;
		case CONTROL_CHARACTERISTIC:	EditCharacteristic(id);	break;
		case CONTROL_SBMS:				EditSBMS(id);			break;
		case CONTROL_GE64:				EditGE64(id);			break;
		case CONTROL_SYMBOL_GROUP:		EditGroup(id);			break;
		case CONTROL_AREA:
		case CONTROL_SEAWAY:
		
		case CONTROL_SYMBOL_TYPE:		EditName(id);			break;
	}

}

int CDialogPanel::GetItemTypeId(int id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%d'"),m_Table,id);

	if(!my_query(m_DB,sql))
		return 0;
		
	void *result = db_result(m_DB);
	char **row = (char**)db_fetch_row(result);
	int value = (atoi(row[FI_ITEM_ID_TYPE]));

	db_free_result(result);
	return value;

}

void CDialogPanel::EditItem(int id)
{

	int type = GetItemTypeId(id);
	CNew *ptr = new CNew(m_DB, m_ControlType,type,id,true);
	
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%d'"),m_Table,id);
	
	if(!my_query(m_DB,sql))
		return;
		
	void *result = db_result(m_DB);
	char **row = (char**)db_fetch_row(result);
	//ptr->SetItemTypeID(atoi(row[FI_ITEM_ID_ITEM_TYPE]));
	ptr->SetName(Convert(row[FI_ITEM_NAME]));
	ptr->SetType(Convert(row[FI_ITEM_TYPE]));
	ptr->SetInfo(Convert(row[FI_ITEM_INFO]));
	db_free_result(result);	

	ptr->Create();
	
	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET id_type = '%d', name = '%s', type = '%s', info ='%s' WHERE id = '%d'"),m_Table,ptr->GetItemType(),ptr->GetName(),ptr->GetType(),ptr->GetInfo(),id);
		my_query(m_DB,sql);

		wxArrayPtrVoid controls = ptr->GetFeatureControls();

		for(size_t i = 0; i < controls.size(); i++)
		{
			wxTextCtrl *txt = (wxTextCtrl*)controls.Item(i);
			int id_feature = (int)txt->GetClientData();
			sql = wxString::Format	(_("DELETE FROM `%s` WHERE id_item ='%d' AND id_feature ='%d'"),TABLE_ITEM_VALUE,id,id_feature);
			my_query(m_DB,sql);
			sql = wxString::Format	(_("INSERT INTO `%s` SET id_item ='%d', id_feature ='%d',value='%s'"),TABLE_ITEM_VALUE,id,id_feature,txt->GetValue());
			my_query(m_DB,sql);
		}

		Clear();
		Read();
		Select();
	}

	delete ptr;
}

void CDialogPanel::EditSymbol(int id)
{
	CNew *ptr = new CNew(m_DB,m_ControlType);
	
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%d'"),m_Table,id);
	
	if(!my_query(m_DB,sql))
		return;
				
	void *result = db_result(m_DB);
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetSeaway(Convert(row[FI_SYMBOL_ID_SEAWAY]));
	ptr->SetArea(Convert(row[FI_SYMBOL_ID_AREA]));
	ptr->SetSymbolType(Convert(row[FI_SYMBOL_ID_SYMBOL_TYPE]));
	ptr->SetLon(strtod(row[FI_SYMBOL_LON],NULL));
	ptr->SetLat(strtod(row[FI_SYMBOL_LAT],NULL));
	ptr->SetName(Convert(row[FI_SYMBOL_NAME]));
	ptr->SetInfo(Convert(row[FI_SYMBOL_INFO]));
	ptr->SetNumber(Convert(row[FI_SYMBOL_NUMBER]));
	ptr->SetMonitoring(atoi(row[FI_SYMBOL_IN_MONITORING]));
	//ptr->SetSBMS(Convert(row[FI_SYMBOL_ID_SBMS]));

	db_free_result(result);	
	SetSymbolPicture(ptr,id);

	ptr->Create();
	
	SetSymbolLight(ptr,id);
	SetSymbolItem(ptr,id);

	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET id_area='%d', id_seaway='%d',id_symbol_type='%d',number='%s',lon='%3.14f', lat='%3.14f',in_monitoring='%d', name='%s', info ='%s' WHERE id = '%d'"),
			m_Table,ptr->GetAreaId(),ptr->GetSeawayId(),ptr->GetSymbolTypeId(), ptr->GetNumber(),ptr->GetLon(),ptr->GetLat(),ptr->GetMonitoring(), ptr->GetName(),ptr->GetInfo(),id);
		my_query(m_DB,sql);
		
		//light
		CLightPanel *pan = ptr->GetLightPanel();
		
		sql = wxString::Format(_("DELETE FROM `%s` WHERE id_symbol='%d'"),TABLE_SYMBOL_LIGHT,id);
		my_query(m_DB,sql);

		for(size_t i = 0; i < pan->GetCount(); i++)
		{
			CSector *Sector = pan->GetSector(i);
			sql = wxString::Format(_("INSERT INTO %s SET id_symbol='%d',id_characteristic='%d', color='%d',coverage='%4.2f',sector_from='%4.2f',sector_to='%4.2f'"),
				TABLE_SYMBOL_LIGHT,id,Sector->GetIdCharacteristic(), Sector->GetColor().GetRGB(),Sector->GetCoverage(),Sector->GetSectorFrom(),Sector->GetSectorTo());
			my_query(m_DB,sql);
		}
		

		// itemy
		sql = wxString::Format(_("DELETE FROM `%s` WHERE id_symbol='%d'"),TABLE_SYMBOL_ITEM,id);
		my_query(m_DB,sql);
		
		CItemPanel *ItemPanel = ptr->GetItemPanel();
		for(size_t i = 0; i < ItemPanel->GetCount(); i++)
		{
			CItem *Item = ItemPanel->GetItem(i);
			for(size_t j = 0 ;j < Item->GetCount(); j++)
			{
				CComboPanel *Combo = Item->GetCombo(j);
				int _cid = Combo->_GetId();
				if(_cid > 0)
				{
					sql = wxString::Format	(_("INSERT INTO `%s` SET id_item='%d', id_symbol ='%d'"),TABLE_SYMBOL_ITEM,_cid,id);
					my_query(m_DB,sql);
				}
			}
		}

		//picture
		sql = wxString::Format	(_("DELETE FROM `%s` WHERE id_symbol ='%d'"),TABLE_SYMBOL_PICTURE,id);
		my_query(m_DB,sql);
		int pid = ptr->GetPictureId();
		if(pid > 0)
		{
			sql = wxString::Format(_("INSERT INTO %s SET id_symbol='%d', id_picture='%d'"),TABLE_SYMBOL_PICTURE,id,pid);
			my_query(m_DB,sql);
		}

		Clear();
		Read();
		Select();
	}

	delete ptr;
}


void CDialogPanel::EditCharacteristic(int id)
{
	CNew *ptr = new CNew(m_DB,m_ControlType);
	
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%d'"),m_Table,id);
	
	if(!my_query(m_DB,sql))
		return;
				
	void *result = db_result(m_DB);
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetName(Convert(row[FI_CHARACTERISTIC_NAME]));
	ptr->SetCode(Convert(row[FI_CHARACTERISTIC_CODE]));
	ptr->SetIala(Convert(row[FI_CHARACTERISTIC_IALA]));
	ptr->SetTime(Convert(row[FI_CHARACTERISTIC_TIME]));
	

	db_free_result(result);	
	ptr->Create();
	SetCharacteristicTime(ptr,id);
			
	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET name='%s',code='%s',iala='%s',time='%s' WHERE id = '%d'"),m_Table,ptr->GetName(),ptr->GetCode(),ptr->GetIala(),ptr->GetTime(),id);
		my_query(m_DB,sql);
		
		//time
		CTimePanel *pan = ptr->GetTimePanel();
		
		sql = wxString::Format(_("DELETE FROM `%s` WHERE id_characteristic='%d'"),TABLE_CHARACTERISTIC_ON_OFF,id);
		my_query(m_DB,sql);

		for(size_t i = 0; i < pan->GetCount(); i++)
		{
			CTime *Time = pan->GetTime(i);
			sql = wxString::Format(_("INSERT INTO %s SET id_characteristic='%d', _on='%4.2f',_off='%4.2f'"),TABLE_CHARACTERISTIC_ON_OFF,id,Time->GetOn(),Time->GetOff());
			my_query(m_DB,sql);
		}
		
		Clear();
		Read();
		Select();
	}

	delete ptr;
}



void CDialogPanel::EditName(int id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%d'"),m_Table,id);
	
	if(!my_query(m_DB,sql))
		return;
		
	CNew *ptr = new CNew(m_DB,m_ControlType);
		
	void *result = db_result(m_DB);
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetName(Convert(row[FI_NAME]));
	ptr->SetInfo(Convert(row[FI_INFO]));
	db_free_result(result);	
	
	ptr->Create();	
	
	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET name='%s', info ='%s' WHERE id = '%d'"),m_Table,ptr->GetName(),ptr->GetInfo(),id);
		my_query(m_DB,sql);
		Clear();
		Read();
		Select();
	}

	delete ptr;
}

void CDialogPanel::EditBaseStation(int id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%d'"),m_Table,id);
	
	if(!my_query(m_DB,sql))
		return;
		
	CNew *ptr = new CNew(m_DB,m_ControlType);
		
	void *result = db_result(m_DB);
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetName(Convert(row[FI_BASE_STATION_NAME]));
	ptr->SetInfo(Convert(row[FI_BASE_STATION_INFO]));
	db_free_result(result);	
	
	ptr->Create();	
	
	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET name='%s', info ='%s' WHERE id = '%d'"),m_Table,ptr->GetName(),ptr->GetInfo(),id);
		my_query(m_DB,sql);
		Clear();
		Read();
		Select();
	}

	delete ptr;
}


void CDialogPanel::EditSBMS(int id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%d'"),m_Table,id);
	
	if(!my_query(m_DB,sql))
		return;
		
	CNew *ptr = new CNew(m_DB,m_ControlType);
		
	void *result = db_result(m_DB);
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetName(Convert(row[FI_SBMS_NAME]));
	ptr->SetIdSymbol(Convert(row[FI_SBMS_ID_SYMBOL]));
	ptr->SetInfo(Convert(row[FI_SBMS_INFO]));
	db_free_result(result);	
	
	ptr->Create();	
	
	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET id_symbol='%d', name='%s', info ='%s' WHERE id = '%d'"),m_Table,ptr->GetIdSymbol(),ptr->GetName(),ptr->GetInfo(),id);
		my_query(m_DB,sql);
		Clear();
		Read();
		Select();
	}

	delete ptr;
}


void CDialogPanel::EditGE64(int id)
{
	wxString sql = wxString::Format(_("SELECT name,id_symbol,info FROM %s WHERE id = '%d'"),m_Table,id);
	
	if(!my_query(m_DB,sql))
		return;
		
	CNew *ptr = new CNew(m_DB,m_ControlType);
		
	void *result = db_result(m_DB);
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetName(Convert(row[0]));
	ptr->SetIdSymbol(Convert(row[1]));
	ptr->SetInfo(Convert(row[2]));
	db_free_result(result);	
	
	ptr->Create();	
	
	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET id_symbol='%d', name='%s', info ='%s' WHERE id = '%d'"),m_Table,ptr->GetIdSymbol(),ptr->GetName(),ptr->GetInfo(),id);
		my_query(m_DB,sql);
		Clear();
		Read();
		Select();
	}

	delete ptr;
}

void CDialogPanel::EditGroup(int id)
{
	wxString sql = wxString::Format(_("SELECT name,code,info FROM %s WHERE id = '%d'"),m_Table,id);
	
	if(!my_query(m_DB,sql))
		return;
		
	CNew *ptr = new CNew(m_DB,m_ControlType);
		
	void *result = db_result(m_DB);
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetName(Convert(row[0]));
	ptr->SetCode(Convert(row[1]));
	ptr->SetInfo(Convert(row[2]));
	db_free_result(result);	
	
	ptr->Create();	
	
	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET code='%s', name='%s', info ='%s' WHERE id = '%d'"),m_Table,ptr->GetCode(),ptr->GetName(),ptr->GetInfo(),id);
		my_query(m_DB,sql);
		Clear();
		Read();
		Select();
	}

	delete ptr;
}



void CDialogPanel::EditType(int id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%d'"),m_Table,id);
	
	if(!my_query(m_DB,sql))
		return;
		
	CNew *ptr = new CNew(m_DB,m_ControlType);
	void *result = db_result(m_DB);
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetType(Convert(row[FI_TYPE]));
	ptr->SetInfo(Convert(row[FI_INFO]));
	
	db_free_result(result);

	ptr->Create();

	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET type= '%s', info ='%s' WHERE id = '%d'"),m_Table,ptr->GetType(),ptr->GetInfo(),id);
		my_query(m_DB,sql);
		Clear();
		Read();
		Select();
	}

	delete ptr;
	
}

void CDialogPanel::EditPicture(int id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%d'"),m_Table,id);
	
	if(!my_query(m_DB,sql))
		return;
		
	CNew *ptr = new CNew(m_DB,m_ControlType);
		
	void *result = db_result(m_DB);
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetName(Convert(row[FI_NAME]));
	ptr->SetInfo(Convert(row[FI_INFO]));
	ptr->SetPictureId(id);	
	db_free_result(result);

	ptr->Create();
	
	
	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET name= '%s', info ='%s' WHERE id = '%d'"),m_Table,ptr->GetName(),ptr->GetInfo(),id);
		my_query(m_DB,sql);
		
		wxImage img = ptr->GetPicture();
		UpdatePicture(img,ptr->GetPictureId(),img.GetType());
		Clear();
		Read();
		Select();
	}

	delete ptr;
	
}

void CDialogPanel::OnDelete(int id)
{

	wxMessageDialog *MessageDialog = new wxMessageDialog(this,GetMsg(MSG_DELETE_QUESTION),wxString::Format(wxT("%s %s"),wxT(PRODUCT_NAME),wxT(PRODUCT_VERSION)),wxYES_NO|wxICON_QUESTION);
    if(MessageDialog->ShowModal() == wxID_YES)
	{
		wxString sql = wxString::Format(_("DELETE FROM %s WHERE id = '%d'"),m_Table,id);
		my_query(m_DB,sql);
		Clear();
		Read();
	
	}

	delete MessageDialog;
}

void CDialogPanel::OnAddToGroup(int id)
{
	CSymbolGroup *SymbolGroup = new CSymbolGroup(m_DB,id);
	SymbolGroup->ShowModal();
	delete SymbolGroup;
}

void CDialogPanel::OnColumnCLick(wxString field, int order)
{
	if(order == ORDER_ASC)
		m_Order = _("ASC");
	else
		m_Order = _("DESC");
	
	m_Field = field;
	Clear();
	Read();
}

void CDialogPanel::OnSelect(int id)
{
	m_ID = id;
	
	if(m_Slave)
	{
		m_Slave->_SetIdMaster(id);
		m_Slave->Clear();
		m_Slave->Read();
	}

	switch(m_ControlType)
	{
		case CONTROL_SYMBOL:	SelectSymbol();		break;
		case CONTROL_SBMS:		SelectSBMS();		break;
	}
	
	if(m_PicturePanel)
	{
		m_PicturePanel->_SetId(m_ID);
		m_PicturePanel->Read();
		//m_PicturePanel->Show();
		//m_PicturePanel->Layout();
	}
	
}

void CDialogPanel::SelectSymbol()
{
	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_symbol='%d'"),TABLE_SYMBOL_PICTURE,m_ID);
	my_query(m_DB,sql);

	void *result = db_result(m_DB);
	if(result == NULL)
		return;
	char** row = (char**)db_fetch_row(result);
	if(row)
		m_ID = atoi(row[FI_SYMBOL_PICTURE_ID_PICTURE]);
	else
		m_ID = -1;
		
	db_free_result(result);
}

void CDialogPanel::SelectSBMS()
{
	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id='%d'"),TABLE_SBMS,m_ID);
	my_query(m_DB,sql);

	void *result = db_result(m_DB);
	if(result == NULL)
		return;
	
	char** row = (char**)db_fetch_row(result);
	if(row)
	{
		m_ID = atoi(row[FI_SBMS_ID]);
		m_Name = Convert(row[FI_SBMS_NAME]);
	}

	db_free_result(result);

}

int CDialogPanel::_GetId()
{
	return m_ID;
}

wxString  CDialogPanel::_GetName()
{
	return m_Name;
}

void CDialogPanel::_SetIdMaster(int id)
{
	m_IDMaster = id;
}

void CDialogPanel::SetCharacteristicTime(CNew *ptr,int id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id_characteristic='%d'"),TABLE_CHARACTERISTIC_ON_OFF,id);
	
	if(!my_query(m_DB,sql))
		return;
			
	void *result = db_result(m_DB);
	char **row;
	
	CTimePanel *TimePanel = ptr->GetTimePanel();
	wxString str;
	while(row = (char**)db_fetch_row(result))
	{
		CTime *Time = new CTime(TimePanel);
		Time->SetOn(atof(row[FI_CHARACTERISTIC_ON_OFF_ON]));
		Time->SetOff(atof(row[FI_CHARACTERISTIC_ON_OFF_OFF]));
		
		TimePanel->AppendPanel(Time);
	}
		
	db_free_result(result);
}

void CDialogPanel::SetSymbolLight(CNew *ptr,int id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id_symbol = '%d'"),TABLE_SYMBOL_LIGHT,id);
	
	if(!my_query(m_DB,sql))
		return;
			
	void *result = db_result(m_DB);
	char **row;
	
	CLightPanel *LightPanel = ptr->GetLightPanel();

	while(row = (char**)db_fetch_row(result))
	{
		CSector *Sector = new CSector();
		wxColor color;
		color.SetRGB(atoi(row[FI_SYMBOL_LIGHT_COLOR]));
		Sector->SetColor(color);
		Sector->SetCoverage(atof(row[FI_SYMBOL_LIGHT_COVERAGE]));
		Sector->SetSectorFrom(atof(row[FI_SYMBOL_LIGHT_SECTOR_FROM]));
		Sector->SetSectorTo(atof(row[FI_SYMBOL_LIGHT_SECTOR_TO]));
		Sector->SetIdCharacteristic(atoi(row[FI_SYMBOL_LIGHT_ID_CHARACTERISTIC]));
		LightPanel->Append(Sector);
	}
		
	db_free_result(result);
}



void CDialogPanel::SetSymbolItem(CNew *ptr,int id)
{
	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_symbol = '%d'"),TABLE_SYMBOL_ITEM ,id);

	if(!my_query(m_DB,sql))
		return;
			
	void *result = db_result(m_DB);
	char **row;
	
	CItemPanel *ItemPanel = ptr->GetItemPanel();

	while(row = (char**)db_fetch_row(result))
	{
		ItemPanel->AppendCombo(atoi((row[FI_SYMBOL_ITEM_ID_ITEM])));
	}
	
	db_free_result(result);
}


void CDialogPanel::SetSymbolPicture(CNew *ptr,int id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id_symbol = '%d'"),TABLE_SYMBOL_PICTURE,id);
	
	if(!my_query(m_DB,sql))
		return;
			
	void *result = db_result(m_DB);
	char **row;
	
	while(row = (char**)db_fetch_row(result))
		ptr->SetPictureId(atoi(row[FI_SYMBOL_PICTURE_ID_PICTURE]));
			
	db_free_result(result);
}