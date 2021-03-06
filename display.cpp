#include <wx/wx.h>
#include <wx/tglbtn.h>
#include "conf.h"
#include "tools.h"
#include "display.h"
#include "options.h"
#include "filterdialog.h"
#include "db.h"


DEFINE_EVENT_TYPE(EVT_SET_NIGHT_TIME)

BEGIN_EVENT_TABLE(CDisplayPlugin,CNaviDiaplayApi)
//	EVT_HYPERLINK(ID_REPORT,CDisplayPlugin::OnReport)
//	EVT_HYPERLINK(ID_DATA,CDisplayPlugin::OnData)
//	EVT_HYPERLINK(ID_CONFIG,CDisplayPlugin::OnConfig)
//	EVT_BUTTON(ID_ON,CDisplayPlugin::OnPowerOn)
	EVT_BUTTON(ID_FILTER,OnFilter)
	EVT_TEXT(ID_SEARCH,OnSearchText)
	EVT_TEXT_ENTER(ID_SEARCH,OnSearchEnter)
	EVT_MENU_RANGE(ID_MENU_BEGIN,ID_MENU_END,OnMenuRange)
	EVT_CONTEXT_MENU(OnMenu)
	EVT_COMMAND(ID_NIGHT_TIME,EVT_SET_NIGHT_TIME,OnSetNightTime)
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
	m_OldAlarmCount = 0;
	m_OldSymbolCount = 0;
	m_OldComandCount = 0;
	ShowControls();
	ReadConfig();
	SetRenderBackground(false);
}

CDisplayPlugin::~CDisplayPlugin()
{
	WriteConfig();
}

CNaviBroker *CDisplayPlugin::GetBroker()
{
	return m_MapPlugin->GetBroker();
}

void CDisplayPlugin::ReadConfig()
{
	int selected_page;
	wxFileConfig *FileConfig = new wxFileConfig(GetProductName(),wxEmptyString,GetConfigFile(),wxEmptyString);
	FileConfig->Read(wxString::Format(_("%s/%s"),m_ControlName,_(KEY_SELECTED_PAGE)),&selected_page,0);
	m_Notebook->SetSelection(selected_page);
	delete FileConfig;
}

void CDisplayPlugin::WriteConfig()
{
	wxFileConfig *FileConfig = new wxFileConfig(GetProductName(),wxEmptyString,GetConfigFile(),wxEmptyString);
	wxListItem item;
	FileConfig->Write(wxString::Format(_("%s/%s"),m_ControlName,_(KEY_SELECTED_PAGE)),m_Notebook->GetSelection());
	delete FileConfig;
}


void CDisplayPlugin::OnSearchEnter(wxCommandEvent &event)
{
	SetSearchText(m_SearchText->GetValue().char_str());
	SetSearchTextChanged(true);
}

void CDisplayPlugin::OnFilter(wxCommandEvent &event)
{
	CFilterDialog *FilterDialog = new CFilterDialog();
	FilterDialog->SetAreaId(GetSelectedAreaId());
	FilterDialog->SetSeawayId(GetSelectedSeawayId());
	FilterDialog->SetSymbolTypeId(GetSelectedSymbolTypeId());
	FilterDialog->SetMonitoring(GetMonitoring());
	FilterDialog->SetLight(GetLight());
//	FilterDialog->SetGroupId(GetSelectedGroupId());
	FilterDialog->SetBaseStationId(GetSelectedBaseStationId());
	FilterDialog->SetAlarmId(GetSelectedAlarmId());

	if(FilterDialog->ShowModal()== wxID_OK)
	{
		SetSelectedAreaId(FilterDialog->GetAreaId());
		SetSelectedSeawayId(FilterDialog->GetSeawayId());
		SetSelectedSymbolTypeId(FilterDialog->GetSymbolTypeId());
		SetMonitoring(FilterDialog->GetMonitoring());
	//	SetSelectedGroupId(FilterDialog->GetGroupId());
		SetLight(FilterDialog->GetLight());
		SetSelectedBaseStationId(FilterDialog->GetBaseStationId());
		SetSelectedAlarmId(FilterDialog->GetAlarmId());
		SetFilterChanged(true);
	}
	
	delete FilterDialog;
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

void CDisplayPlugin::OnSetNightTime(wxCommandEvent &event)
{
	time_t on = GetNightTimeOn();
	time_t off = GetNightTimeOff();
	time_t local = GetLocalTimestamp();

	tm _on = *gmtime(&on);
	tm _off = *gmtime(&off);
	tm _local = *gmtime(&local);
	
	if(m_OldNight != GetNight())
	{
		wxString str;
		if(GetNight())
			str << GetMsg(MSG_NIGHT_TIME);
		else
			str << GetMsg(MSG_DAY_TIME);
		
		str << wxString::Format(_("(%02d:%02d %02d:%02d)"),_on.tm_hour,_on.tm_min, _off.tm_hour,_off.tm_min);
		m_NightTime->SetLabel(str);
		this->Layout();
	}
	
	m_OldNight = GetNight();
	
}


void CDisplayPlugin::OnManagement(wxCommandEvent &event)
{
	if(m_Selected == NULL)
		return;
/*	
	if(!m_Selected->GetNoSBMS())
	{
		CCommandModelDialog *CommandDialog = new CCommandModelDialog(m_DB,this,m_Selected); 
		CCommandModelPanel *ptr =  CommandDialog->GetCommandPanel();

		ptr->SetForcedOff(m_Selected->GetForcedOff());
		ptr->SetAuto(m_Selected->GetAuto());
			
		CommandDialog->ShowModal();
		delete CommandDialog;
	
	}else{
			wxMessageBox(GetMsg(MSG_NO_SBMS_RECORD));
	}
*/
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
		
	wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
	Sizer->Add(hSizer,0,wxALL|wxEXPAND,0);

	m_SearchText = new wxSearchCtrl(Panel,ID_SEARCH,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxTE_PROCESS_ENTER);
	hSizer->Add(m_SearchText,1,wxALL|wxEXPAND,0);
	m_SearchText->SetValue(GetSearchText());
	
	wxButton *BFilter = new wxButton(Panel,ID_FILTER,GetMsg(MSG_FILTER_DOT),wxDefaultPosition,wxSize(20,-1));
	hSizer->Add(BFilter,0,wxALL,0);
	
	m_SymbolListHtml = new CSymbolListHtml(Panel);
	Sizer->Add(m_SymbolListHtml,1,wxALL|wxEXPAND,0);

	//item.SetWidth(80); item.SetText(GetMsg(MSG_NUMBER)); m_HtmlCtrl->InsertColumn(0,item);
	//item.SetWidth(280); item.SetText(GetMsg(MSG_NAME)); m_HtmlCtrl->InsertColumn(1,item);
	
	//m_HtmlCtrl->SetColumnImage(GetSortColumnId(),GetSortOrder());
		
	/*
	m_SymbolList = new  CSymbolList(Panel, wxLC_REPORT | wxLC_VIRTUAL | wxLC_SINGLE_SEL);
	wxListItem item;
	item.SetWidth(80);	item.SetText(GetMsg(MSG_INPUT_VOLT));	m_SymbolList->InsertColumn(0,item);
	item.SetWidth(280); item.SetText(GetMsg(MSG_NAME));			m_SymbolList->InsertColumn(1,item);
	item.SetWidth(100); item.SetText(GetMsg(MSG_NUMBER));		m_SymbolList->InsertColumn(2,item);
	Sizer->Add(m_SymbolList,1,wxALL|wxEXPAND,0);
	*/

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
	Sizer->Add(m_SymbolPanel,1,wxALL|wxEXPAND,0);
	Panel->SetSizer(Sizer);

	return Panel;
}


wxPanel *CDisplayPlugin::GetPage3(wxWindow *parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	m_Page3 = new wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	
	m_NightTime = new wxStaticText(m_Page3,wxID_ANY,wxEmptyString);
	m_NightTime->SetLabel(wxEmptyString);
	Sizer->Add(m_NightTime,0,wxALL|wxALIGN_RIGHT,5);
	
	m_Page3->SetSizer(Sizer);

	return m_Page3;
}


wxPanel *CDisplayPlugin::GetPage4(wxWindow *parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	m_Page4 = new wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	
	m_AlarmList = new CAlarmList(m_Page4);
	Sizer->Add(m_AlarmList,1,wxALL|wxEXPAND,0);

	m_Page4->SetSizer(Sizer);

	return m_Page4;
}

wxPanel *CDisplayPlugin::GetPage5(wxWindow *parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	
	m_CommandList = new CCommandModelList(Panel);
	Sizer->Add(m_CommandList,1,wxALL|wxEXPAND,0);

	Panel->SetSizer(Sizer);

	return Panel;
}


wxPanel *CDisplayPlugin::GetPage6(wxWindow *parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	
	m_GroupList = new CGroupList(Panel);
	Sizer->Add(m_GroupList,1,wxALL|wxEXPAND,0);

	Panel->SetSizer(Sizer);

	return Panel;
}

wxPanel *CDisplayPlugin::GetPage7(wxWindow *parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	
//	m_ActionPanel = new CActionPanel(Panel);
//	Sizer->Add(m_ActionPanel,1,wxALL|wxEXPAND,0);

	Panel->SetSizer(Sizer);

	return Panel;
}

void CDisplayPlugin::ShowControls()
{
	wxBoxSizer *Main = new wxBoxSizer(wxVERTICAL);
	
	
	m_Notebook = new wxNotebook(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxNB_NOPAGETHEME);
	
	m_Notebook->AddPage(GetPage2(m_Notebook),GetMsg(MSG_SYMBOL));
	m_Notebook->AddPage(GetPage1(m_Notebook),GetMsg(MSG_ALL));
	m_Notebook->AddPage(GetPage4(m_Notebook),GetMsg(MSG_ALARM));
	m_Notebook->AddPage(GetPage5(m_Notebook),GetMsg(MSG_COMMAND));
	m_Notebook->AddPage(GetPage6(m_Notebook),GetMsg(MSG_SYMBOL_GROUP));
	
	Main->Add(m_Notebook,1,wxALL|wxEXPAND,0);		

	Main->Add(GetPage3(this),0,wxALL|wxEXPAND,0);

	SetSizer(Main);
	Layout();
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
		//m_MapPlugin = (CMapPlugin*)m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"manager_GetThisPtr",NULL);

		//if(!EnableControls())
			//return false;
				
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
		
	//fprintf(stderr,"SignalInsert NOT NULL\n");
	wxArrayPtrVoid *ptr = m_MapPlugin->GetSymbolListPtr();
	int count = ptr->size();

	if(m_OldSymbolCount != count)
		m_Notebook->SetPageText(PAGE_ALL,wxString::Format(GetMsg(MSG_SYMBOLS),count));
	m_OldSymbolCount = count;

	m_SymbolListHtml->SetList(ptr);
	m_SymbolListHtml->SetMapPlugin(m_MapPlugin);
	
	//ALARM LIST
	ptr = m_MapPlugin->GetAlarmListPtr();
	count = ptr->size();

	if(m_OldAlarmCount != count)
		m_Notebook->SetPageText(PAGE_ALARM,wxString::Format(GetMsg(MSG_ALARMS),count));
	m_OldAlarmCount = count;

	m_AlarmList->SetList(ptr);
	
	//COMMAND LIST
	CList *lptr;
	lptr = m_MapPlugin->GetCommandListPtr();
	count = lptr->_Length();

	if(m_OldComandCount != count)
		m_Notebook->SetPageText(PAGE_COMMAND,wxString::Format(GetMsg(MSG_COMMANDS),count));
	m_OldComandCount = count;

	m_CommandList->SetList(lptr);
	
	//GROUP LIST
	lptr = (CList*)m_MapPlugin->GetGroupListPtr();
	count = lptr->_Length();

	if(m_OldGroupCount != count)
		m_Notebook->SetPageText(PAGE_GROUP,wxString::Format(GetMsg(MSG_GROUPS),count));
	m_OldGroupCount = count;

	m_GroupList->SetList(lptr);

	


	wxCommandEvent evt(EVT_SET_NIGHT_TIME,ID_NIGHT_TIME);
	wxPostEvent(this,evt);
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
	m_SymbolListHtml->_SetSelection(m_Selected);
//	m_ActionPanel->SetSymbol(m_Selected);
	
	if(m_Selected)
	{	
		m_SymbolPanel->SetPage(m_Selected);

	//	if(db_check_right(MODULE_SYMBOL,ACTION_MANAGEMENT,_GetUID()))
	//		m_ButtonManagement->Enable();
	//	else
	//		m_ButtonManagement->Disable();

			
	}else{
		//m_ButtonManagement->Disable();
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
