#include "conf.h"
#include "tools.h"
#include "display.h"
#include <wx/wx.h>
#include <wx/tglbtn.h>
//#include "AISCoder.h"

BEGIN_EVENT_TABLE(CDisplayPlugin,CNaviDiaplayApi)
	EVT_HYPERLINK(ID_REPORT,CDisplayPlugin::OnReport)
	EVT_HYPERLINK(ID_DATA,CDisplayPlugin::OnData)
	EVT_HYPERLINK(ID_CONFIG,CDisplayPlugin::OnConfig)
	EVT_BUTTON(ID_ON,CDisplayPlugin::OnPowerOn)
	EVT_BUTTON(ID_OFF,CDisplayPlugin::OnPowerOff)
END_EVENT_TABLE()


CDisplayPlugin::CDisplayPlugin(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) 
:CNaviDiaplayApi( parent, id, pos, size, style, name )
{
	Selected = NULL;
	MapPlugin = NULL;
	Broker = NULL;
	SetDisplayID(NDS_MANAGER);
	ControlName = Parent->GetLabel();
	ReadConfig();
	ShowControls();
};

CDisplayPlugin::~CDisplayPlugin()
{
	WriteConfig();
}

CNaviBroker *CDisplayPlugin::GetBroker()
{
	return MapPlugin->GetBroker();
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
	wxListItem item;
	wxBoxSizer *Main = new wxBoxSizer(wxVERTICAL);
		
	wxNotebook *Notebook = new wxNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Main->Add(Notebook,1,wxALL|wxEXPAND,0);
	
	// Page1
	wxPanel *Page1 = new wxPanel(Notebook,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	Page1Sizer = new wxBoxSizer(wxVERTICAL);
	Page1->SetSizer(Page1Sizer);
	Notebook->AddPage(Page1,GetMsg(MSG_MANAGER));
	
	//ShipList = new CListCtrl(Page1,this, 0 , wxLC_REPORT | wxLC_SORT_ASCENDING | wxLC_HRULES | wxLC_VIRTUAL );
	//item.SetWidth(Column1Width); //item.SetText(GetMsg(MSG_SHIP_ID)); 
	//ShipList->InsertColumn(0,item);	
	//item.SetWidth(Column2Width); //item.SetText(GetMsg(MSG_SHIP_NAME)); 
	//ShipList->InsertColumn(1,item);	
	//item.SetWidth(Column3Width); //item.SetText(GetMsg(MSG_SHIP_NAME)); 
	//ShipList->InsertColumn(2,item);
	//item.SetWidth(Column4Width); //item.SetText(GetMsg(MSG_SHIP_NAME)); 
	//ShipList->InsertColumn(3,item);
	//item.SetWidth(Column5Width); //item.SetText(GetMsg(MSG_SHIP_NAME)); 
	//ShipList->InsertColumn(4,item);
	
	// HTML
	ShipList = new CHtmlCtrl(Page1,this);
	
	Page1Sizer->Add(ShipList,1,wxALL|wxEXPAND,0);

	//InfoPanel = new wxPanel(Page1,wxID_ANY);
	//Page1Sizer->Add(InfoPanel,1,wxALL|wxEXPAND,5);

	//wxBoxSizer *InfoPanelSizer = new wxBoxSizer(wxVERTICAL);
	//InfoPanel->SetSizer(InfoPanelSizer);
	//InfoPanel->Hide();
	
	wxFont font;
	font.SetPointSize(14);
	//ShipName = new wxStaticText(InfoPanel,wxID_ANY,wxEmptyString);
	//ShipName->SetFont(font);
	//InfoPanelSizer->Add(ShipName,0,wxALL,2);
	
	//ShipDesc = new wxTextCtrl(InfoPanel,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE);
	//InfoPanelSizer->Add(ShipDesc,0,wxALL|wxEXPAND,2);
	
	//Lat = new wxStaticText(InfoPanel,wxID_ANY,wxEmptyString);
	//InfoPanelSizer->Add(Lat,0,wxALL,2);
	
	//Lon = new wxStaticText(InfoPanel,wxID_ANY,wxEmptyString);
	//InfoPanelSizer->Add(Lon,0,wxALL,2);
	
	ControlPanel = new wxPanel(Page1,wxID_ANY);
	Page1Sizer->Add(ControlPanel,0,wxALL|wxEXPAND,0);
	wxBoxSizer *ControlPanelSizer = new wxBoxSizer(wxVERTICAL);
	ControlPanel->SetSizer(ControlPanelSizer);
	ControlPanel->Hide();
	//ControlPanel->SetBackgroundColour(wxColor(200,200,200));

	
	//wxBitmapToggleButton *Button = new wxBitmapToggleButton();
	
	//wxHyperlinkCtrl *Data = new wxHyperlinkCtrl(InfoPanel,ID_DATA,GetMsg(MSG_SET_SHIP_DATA_DEFINITION),wxEmptyString);
	//InfoPanelSizer->Add(Data,0,wxALL,2);

	//wxHyperlinkCtrl *Config = new wxHyperlinkCtrl(InfoPanel,ID_CONFIG,GetMsg(MSG_SET_SHIP_CONFIG),wxEmptyString);
	//InfoPanelSizer->Add(Config,0,wxALL,2);
	
	
	this->SetSizer(Main);
	this->Disable();

}

void CDisplayPlugin::OnPowerOn(wxCommandEvent &event)
{
//	CAIDSDevice *a = new CAIDSDevice();
//	if(a->SetDeviceSwitch(1))
	//	wxMessageBox(_("OK"));
	//else
		//wxMessageBox(_("ERROR"));
	
	//delete a;
}

void CDisplayPlugin::OnPowerOff(wxCommandEvent &event)
{
	//CAIDSDevice *a = new CAIDSDevice();
	//if(a->SetDeviceSwitch(0))
		//wxMessageBox(_("OK"));
	//else
		//wxMessageBox(_("ERROR"));
	
	//delete a;
}


bool CDisplayPlugin::IsValidSignal(CDisplaySignal *SignalID) 
{
	
	if(SignalID->GetSignalID() == NDS_BROKER_BROADCAST ) // && Broker == NULL
	{
		Broker = (CNaviBroker*)SignalID->GetData();
		MapPlugin = (CMapPlugin*)Broker->ExecuteFunction(Broker->GetParentPtr(),"manager_GetThisPtr",NULL);
		//fprintf(stdout,"A: %p\n",MapPlugin);
		if(!EnableControls())
			return false;
				
		return false;
	}

	
	if(SignalID->GetSignalID() == NDS_MANAGER)
	{
		MapPlugin = (CMapPlugin*)SignalID->GetData();
		//fprintf(stdout,"B: %p\n",MapPlugin);
		if(!EnableControls())
			return false;
		if(MapPlugin != NULL)
			SwitchAction();	
	}
		
	return false;

}
bool CDisplayPlugin::EnableControls()
{
	if(MapPlugin == NULL)
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

void CDisplayPlugin::OnReport(wxHyperlinkEvent &event)
{
	//ShipReport(Selected);
}	

void CDisplayPlugin::OnData(wxHyperlinkEvent &event)
{
	//ShipData(Selected);
}

void CDisplayPlugin::OnConfig(wxHyperlinkEvent &event)
{
	//ShipConfig(Selected);
}

void CDisplayPlugin::SwitchAction()
{
	switch (MapPlugin->GetDisplaySignal())
	{
		case SIGNAL_INSERT:	SignalInsert();	break;
		case SIGNAL_SELECT:	SignalSelect();	break;
	}

}

void CDisplayPlugin::ShowInfoPanel(bool show, SMarker *ship)
{
	if(ship != NULL)
	{
		//ShipName->SetLabel(ship->name);
		//ShipDesc->SetValue(ship->description);
		double to_x,to_y;
		MapPlugin->GetBroker()->Project(ship->x,ship->y,&to_x,&to_y);
		//Lon->SetLabel(FormatLongitude(to_x));
		//Lat->SetLabel(FormatLatitude(-to_y));
	}
	
	//InfoPanel->Show(show);
	ControlPanel->Show(show);
	Page1Sizer->Layout();
}

void CDisplayPlugin::SignalInsert()
{
	if(MapPlugin == NULL)		
		return;
	
	ShipList->SetList(MapPlugin->GetShipList());
	ShipList->Refresh();
}

bool CDisplayPlugin::ShipIsSelected(SMarker *ship)
{
	return MapPlugin->ShipIsSelected(ship);
}

void CDisplayPlugin::SignalSelect()
{
	Selected = MapPlugin->GetSelectedPtr();
	
	if(Selected == NULL)
		ShowInfoPanel(false,Selected);
	else
		ShowInfoPanel(true,Selected);
	
	ShipList->_SetSelection(Selected);
}

void CDisplayPlugin::SignalClear()
{
	ShipList->ClearList();
}

void CDisplayPlugin::SetSelectedShip(SMarker *ship)
{

	Selected = ship;
	
	if(Broker != NULL)
		Broker->ExecuteFunction(Broker->GetParentPtr(),"manager_SetSelShip",ship);
}

void CDisplayPlugin::ShipProperties(SMarker *ship)
{
	//if(Broker != NULL)
		//Broker->ExecuteFunction(Broker->GetParentPtr(),"tracker2_ShPropert",ship);
}

void CDisplayPlugin::ShipConfig(SMarker *ship)
{
	//if(Broker != NULL)
		//Broker->ExecuteFunction(Broker->GetParentPtr(),"tracker2_ShConfig",ship);
}

void CDisplayPlugin::ShipData(SMarker *ship)
{
	//if(Broker != NULL)
		//Broker->ExecuteFunction(Broker->GetParentPtr(),"tracker2_ShData",ship);
}

void CDisplayPlugin::ShipReport(SMarker *ship)
{
	//if(Broker != NULL)
		//Broker->ExecuteFunction(Broker->GetParentPtr(),"tracker2_ShReport",ship);
}

void CDisplayPlugin::ShipReportConfig(SMarker *ship)
{
	//if(Broker != NULL)
		//Broker->ExecuteFunction(Broker->GetParentPtr(),"tracker2_ShReportConfig",ship);
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
	return NDS_MANAGER;
}

CNaviDiaplayApi *CreateDisplayInstance(wxWindow *Parent, wxWindowID WindowID,int LangID) 
{
	CDisplayPlugin *SimplePlugin = new CDisplayPlugin(Parent, WindowID);
	return SimplePlugin;
}
