#include "conf.h"
#include "tools.h"
#include "display.h"
#include <wx/wx.h>
#include <wx/tglbtn.h>

BEGIN_EVENT_TABLE(CDisplayPlugin,CNaviDiaplayApi)
//	EVT_HYPERLINK(ID_REPORT,CDisplayPlugin::OnReport)
//	EVT_HYPERLINK(ID_DATA,CDisplayPlugin::OnData)
//	EVT_HYPERLINK(ID_CONFIG,CDisplayPlugin::OnConfig)
//	EVT_BUTTON(ID_ON,CDisplayPlugin::OnPowerOn)
//	EVT_BUTTON(ID_OFF,CDisplayPlugin::OnPowerOff)
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

wxPanel *CDisplayPlugin::GetPage1(wxWindow *parent)
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
	m_SymbolPanel = new CSymbolPanel(m_Notebook);
	m_Notebook->AddPage(m_SymbolPanel,GetMsg(MSG_INFO));
	//m_Notebook->AddPage(m_SymbolPanel->GetPage2(m_Notebook),GetMsg(MSG_REPORT));
	//m_Notebook->AddPage(m_SymbolPanel->GetPage3(m_Notebook),GetMsg(MSG_ALERT));
	m_Notebook->AddPage(GetPage1(m_Notebook),GetMsg(MSG_OPTIONS));
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
		case SIGNAL_INSERT:	SignalInsert();	break;
		case SIGNAL_SELECT:	SignalSelect();	break;
	}

}

void CDisplayPlugin::SignalInsert()
{
	if(m_MapPlugin == NULL)
		return;

//	ShipList->SetList(MapPlugin->GetShipList());
//	ShipList->Refresh();
}

/*
bool CDisplayPlugin::ShipIsSelected(SSymbol *ship)
{
//	return MapPlugin->ShipIsSelected(ship);
}
*/

void CDisplayPlugin::SignalSelect()
{
	m_Selected = m_MapPlugin->GetSelectedPtr();

	if(m_OldSelected == m_Selected)
		return;

	m_OldSelected = m_Selected;
		
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
