#include "conf.h"
#include "tools.h"
#include "display.h"
#include <wx/wx.h>
#include <wx/tglbtn.h>
//#include "AISCoder.h"

BEGIN_EVENT_TABLE(CDisplayPlugin,CNaviDiaplayApi)
//	EVT_HYPERLINK(ID_REPORT,CDisplayPlugin::OnReport)
//	EVT_HYPERLINK(ID_DATA,CDisplayPlugin::OnData)
//	EVT_HYPERLINK(ID_CONFIG,CDisplayPlugin::OnConfig)
//	EVT_BUTTON(ID_ON,CDisplayPlugin::OnPowerOn)
//	EVT_BUTTON(ID_OFF,CDisplayPlugin::OnPowerOff)
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

void CDisplayPlugin::ShowControls()
{
	wxBoxSizer *Main = new wxBoxSizer(wxVERTICAL);
			
	wxNotebook *Notebook = new wxNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxNB_NOPAGETHEME);
	m_SymbolPanel = new CSymbolPanel();
	Notebook->AddPage(m_SymbolPanel->GetPage1(Notebook),GetMsg(MSG_INFO));
	Main->Add(Notebook,1,wxALL|wxEXPAND,0);		
	SetSizer(Main);
	Disable();

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
		this->Disable();
		SignalClear();
		return false;
	
	}else{
		
		if(!this->IsEnabled())
		{	
			this->Enable();
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
	
	m_DB = m_MapPlugin->GetDB();
	if(m_Selected)
	{	
		this->Show();
		m_SymbolPanel->SetPage1(m_DB,m_Selected);
	}else{
		//this->Hide();
		//ShowInfoPanel(true,Selected);
	}
	//ShipList->_SetSelection(Selected);
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
