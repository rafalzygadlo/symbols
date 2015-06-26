#include "conf.h"
#include "tools.h"
#include "display.h"
#include "options.h"
#include <wx/wx.h>
#include <wx/tglbtn.h>

BEGIN_EVENT_TABLE(CDisplayPlugin,CNaviDiaplayApi)
//	EVT_HYPERLINK(ID_REPORT,CDisplayPlugin::OnReport)
//	EVT_HYPERLINK(ID_DATA,CDisplayPlugin::OnData)
//	EVT_HYPERLINK(ID_CONFIG,CDisplayPlugin::OnConfig)
//	EVT_BUTTON(ID_ON,CDisplayPlugin::OnPowerOn)
//	EVT_BUTTON(ID_OFF,CDisplayPlugin::OnPowerOff)
	EVT_TEXT(ID_SEARCH,OnSearchText)
	EVT_TEXT_ENTER(ID_SEARCH,OnSearchEnter)
	EVT_MENU_RANGE(ID_MENU_BEGIN,ID_MENU_END,OnMenuRange)
	EVT_CONTEXT_MENU(OnMenu)
END_EVENT_TABLE()


CDisplayPlugin::CDisplayPlugin(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) 
:CNaviDiaplayApi( parent, id, pos, size, style, name )
{
	m_DB = NULL;
	SetDisplayID(NDS_SYMBOL);
	m_Selected = NULL;
	m_OldSelected = NULL;
	m_MapPlugin = NULL;
	m_Broker = NULL;
	m_ControlName = Parent->GetLabel();
	m_ControlType = DEFAULT_CONTROL_TYPE;
	m_OldCount = 0;
	ReadConfig();
	ShowControls();
}

CDisplayPlugin::~CDisplayPlugin()
{
	WriteConfig();
	delete m_SymbolPanel;
}

CNaviBroker *CDisplayPlugin::GetBroker()
{
	return m_MapPlugin->GetBroker();
}

void CDisplayPlugin::ReadConfig()
{
	wxFileConfig *FileConfig = new wxFileConfig(GetProductName(),wxEmptyString,GetConfigFile(),wxEmptyString);
//	FileConfig->Read(wxString::Format(_("%s/%s"),ControlName.wc_str(),_(KEY_COLUMN_0_WIDTH)),&Column1Width,COLUM_0_WIDTH);
//	FileConfig->Read(wxString::Format(_("%s/%s"),ControlName.wc_str(),_(KEY_COLUMN_1_WIDTH)),&Column2Width,COLUM_1_WIDTH);
//	FileConfig->Read(wxString::Format(_("%s/%s"),ControlName.wc_str(),_(KEY_COLUMN_2_WIDTH)),&Column3Width,COLUM_2_WIDTH);
	delete FileConfig;
}

void CDisplayPlugin::WriteConfig()
{
	wxFileConfig *FileConfig = new wxFileConfig(GetProductName(),wxEmptyString,GetConfigFile(),wxEmptyString);
	wxListItem item;
	
//	ShipList->GetColumn(0,item); FileConfig->Write(wxString::Format(_("%s/%s"),ControlName.wc_str(),_(KEY_COLUMN_0_WIDTH)),item.GetWidth());
//	ShipList->GetColumn(1,item); FileConfig->Write(wxString::Format(_("%s/%s"),ControlName.wc_str(),_(KEY_COLUMN_1_WIDTH)),item.GetWidth());
//	ShipList->GetColumn(2,item); FileConfig->Write(wxString::Format(_("%s/%s"),ControlName.wc_str(),_(KEY_COLUMN_2_WIDTH)),item.GetWidth());
	
	delete FileConfig;
}


void CDisplayPlugin::OnSearchEnter(wxCommandEvent &event)
{
	SetSearchText(m_SearchText->GetValue().char_str());
	SetSearchTextChanged(true);
}

void CDisplayPlugin::OnSearchText(wxCommandEvent &event)
{
	if(m_SearchText->GetValue().CmpNoCase(GetSearchText()) != 0)
	{
		SetSearchText(m_SearchText->GetValue().char_str());
		Signal();
	}
	
	SetSearchTextChanged(true);
}

void CDisplayPlugin::Signal()
{
	if(m_Broker != NULL)
		m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"symbol_OnSynchro",NULL);
}

wxPanel *CDisplayPlugin::GetPage1(wxWindow *parent)
{

	wxPanel *Panel = new wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(Sizer);
		
	m_SearchText = new wxSearchCtrl(Panel,ID_SEARCH,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER);
	Sizer->Add(m_SearchText,0,wxALL|wxEXPAND,0);
	m_SearchText->SetValue(GetSearchText());
	
	//wxButton *BFilter = new wxButton(Panel,ID_FILTER,GetMsg(MSG_FILTER),wxDefaultPosition,wxSize(20,-1));
	//hSizer->Add(BFilter,0,wxALL,0);

	//m_SearchText->SetValue(m_SearchText);
	
	m_HtmlCtrl = new CHtmlCtrl(Panel,wxLC_REPORT |  wxLC_VIRTUAL |wxLC_VRULES | wxLC_HRULES );
	wxListItem item;
	item.SetWidth(80);	item.SetText(GetMsg(MSG_NUMBER));	m_HtmlCtrl->InsertColumn(0,item);
	item.SetWidth(200);	item.SetText(GetMsg(MSG_NAME));		m_HtmlCtrl->InsertColumn(1,item);
	
	Sizer->Add(m_HtmlCtrl,1,wxALL|wxEXPAND,0);
	
	//m_List->SetColumnImage(ais_get_sort_column(), ais_get_sort_order());

	//m_Html = new wxHtmlWindow(Panel,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	//m_Page1Sizer->Add(m_Html,1,wxALL|wxEXPAND,0);
	//m_Html->Hide();
	
	return Panel;
}

wxPanel *CDisplayPlugin::GetPage2(wxWindow *parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	
	m_SymbolPanel = new CSymbolPanel(Panel);
	Sizer->Add(m_SymbolPanel,1,wxALL|wxEXPAND,5);
	Panel->SetSizer(Sizer);

	return Panel;
}


wxPanel *CDisplayPlugin::GetPage3(wxWindow *parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	
	Panel->SetSizer(Sizer);

	return Panel;
}

void CDisplayPlugin::ShowControls()
{
	wxBoxSizer *Main = new wxBoxSizer(wxHORIZONTAL);
			
	m_Notebook = new wxNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxNB_NOPAGETHEME);
	
	m_Notebook->AddPage(GetPage1(m_Notebook),GetMsg(MSG_ALL));
	m_Notebook->AddPage(GetPage2(m_Notebook),GetMsg(MSG_INFO));
	m_Notebook->AddPage(GetPage3(m_Notebook),GetMsg(MSG_OPTIONS));
	
	Main->Add(m_Notebook,1,wxALL|wxEXPAND,0);		
	SetSizer(Main);

}



void CDisplayPlugin::OnMenu(wxContextMenuEvent &event)
{
#if 0	
	if(m_ControlType != -1)
		m_Menu->Check(m_ControlType, true);
	
	PopupMenu(m_Menu);
	//delete Menu;
#endif	
}


void CDisplayPlugin::OnMenuRange(wxCommandEvent &event)
{
	if(m_ControlType == event.GetId())
	{
		wxMessageBox(_("The same type of control ?"));
		return;
	}
		
	//m_GUI = false;
	RemoveControl(m_ControlType);
		
//	switch(event.GetId())
//	{
//		case CONTROL_SYMBOL_LIST:	GetSymbolList();	break;
//		case CONTROL_SYMBOL:		GetAisList();		break;
		
//	}
	
	m_ControlType = event.GetId(); // ustawiamy po zbudowaniu gui
	
}

void CDisplayPlugin::RemoveControl(int type)
{
//	switch(type)
	//{
		//case CONTROL_SYMBOL_LIST:	FreeDevicesList();	break;
		//case CONTROL_AIS_LIST:		FreeAisList();		break;
		//case CONTROL_AIS_MONITOR:	FreeAisMonitor();	break;
	//}
}


bool CDisplayPlugin::IsValidSignal(CDisplaySignal *SignalID) 
{
	
	if(SignalID->GetSignalID() == NDS_BROKER_BROADCAST ) // && Broker == NULL
	{
		m_Broker = (CNaviBroker*)SignalID->GetData();
		m_MapPlugin = (CMapPlugin*)m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"manager_GetThisPtr",NULL);
		if(!EnableControls())
			return false;
				
		return false;
	}
		
	if(SignalID->GetSignalID() == NDS_SYMBOL)
	{
		m_MapPlugin = (CMapPlugin*)SignalID->GetData();
		if(!EnableControls())
			return false;
		if(m_MapPlugin != NULL)
			SwitchAction();	
	}
		
	return false;

}
bool CDisplayPlugin::EnableControls()
{
	if(m_MapPlugin == NULL)
	{
		//this->Disable();
		SignalClear();
		return false;
	
	}else{
		
		if(!this->IsEnabled())
		{	
			//this->Enable();
			SignalInsert();
		}
	}
	
	return true;
}

void CDisplayPlugin::SwitchAction()
{
	switch (m_MapPlugin->GetDisplaySignal())
	{
		case SIGNAL_INSERT:		SignalInsert();		break;
		case SIGNAL_SELECT:		SignalSelect();		break;
		case SIGNAL_SYNCHRO:	SignalSynchro();	break;
	}

}

void CDisplayPlugin::SignalInsert()
{
	if(m_MapPlugin == NULL)
		return;

	//fprintf(stderr,"Update\n");
	//m_HtmlCtrl->ClearList();

	wxArrayPtrVoid *ptr = m_MapPlugin->GetSymbolListPtr();

	m_HtmlCtrl->SetList(ptr);
	int count = ptr->size();

	if(m_OldCount != count)
			m_Notebook->SetPageText(PAGE_0,wxString::Format(GetMsg(MSG_SYMBOLS),count));
		m_OldCount = count;


//	ShipList->SetList(MapPlugin->GetShipList());
//	ShipList->Refresh();
}

void CDisplayPlugin::SignalSynchro()
{
	m_SearchText->SetValue(GetSearchText());
}

void CDisplayPlugin::SignalSelect()
{
	m_Selected = m_MapPlugin->GetSelectedPtr();
		
	if(m_OldSelected == m_Selected)
		return;

	m_OldSelected = m_Selected;

	m_HtmlCtrl->SetSelection(m_Selected);
		
	if(m_Selected)
	{	
		//m_Notebook->Show();
		//m_Notebook->Enable();
		m_SymbolPanel->SetPage1(m_Selected);
	}else{
		//m_Notebook->Hide();
	}

}

void CDisplayPlugin::ShowInfoPanel(bool show)
{
	
	//Page1Sizer->Layout();
}

void CDisplayPlugin::SignalClear()
{
	//ShipList->ClearList();
}

void CDisplayPlugin::OnRender(wxGCDC &dc) 
{
	
}

void CDisplayPlugin::OnWork(CDisplaySignal *Signal)
{
	Refresh();
	wxMilliSleep(300);
}

void CDisplayPlugin::AfterWork(CDisplaySignal *Signal)
{

}

void CDisplayPlugin::BeforeWork(CDisplaySignal *Signal)
{
	
}

const wchar_t *NaviDisplayIntroduce(int LanguageID) 
{
	switch( LanguageID ) 
	{
		case 0:		return _(PRODUCT_NAME);	break;
		default:	return _(PRODUCT_NAME); break;
	}

}

const int NaviDisplayID()
{
	return NDS_SYMBOL;
}

CNaviDiaplayApi *CreateDisplayInstance(wxWindow *Parent, wxWindowID WindowID,int LangID) 
{
	CDisplayPlugin *SimplePlugin = new CDisplayPlugin(Parent, WindowID);
	return SimplePlugin;
}
