#include <wx/wx.h>
#include <wx/webviewfshandler.h>
#include <wx/notebook.h>
#include "symbolpanel.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "grid.h"
#include "geometrytools.h"
#include "ais.h"
#include "nvtime.h"
#include "commanddialog.h"
#include "graphdialog.h"
#include "alarmdialog.h"
#include "options.h"


BEGIN_EVENT_TABLE(CSymbolPanel,wxPanel)
	EVT_CONTEXT_MENU(OnMenu)
	EVT_MENU(ID_SHOW_PICTURE,OnShowMenu)
	EVT_BUTTON(ID_MANAGEMENT,OnManagement)
	EVT_BUTTON(ID_GRAPH,OnGraph)
	EVT_HTML_LINK_CLICKED(ID_HTML,OnHtml)
#ifdef WEBVIEW
	EVT_WEBVIEW_NAVIGATING(ID_HTML,OnNavigationRequest)
	EVT_WEBVIEW_LOADED(ID_HTML,OnLoaded)
#endif
END_EVENT_TABLE()


CSymbolPanel::CSymbolPanel(wxWindow *parent)
:wxPanel(parent,wxID_ANY)
{
	m_Symbol = NULL;
	m_GraphDialog = NULL;
	m_HtmlString = wxEmptyString;
	GetPage1();
#ifdef WEBVIEW
	m_Html->LoadURL("about:blank");
#endif
	//m_Html->SetPage("<html><p>test page</p></html>","www.wp.pl");
}

CSymbolPanel::~CSymbolPanel()
{
	if(m_GraphDialog)
		delete m_GraphDialog;
	
}

void CSymbolPanel::GetPage1()
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);

	//wxBoxSizer *ScrollSizer = new wxBoxSizer(wxVERTICAL);
	//wxScrolledWindow *Scroll = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	//Sizer->Add(Scroll,1,wxALL|wxEXPAND,0);
	//Scroll->SetFocusIgnoringChildren();
	//Scroll->SetSizer(ScrollSizer);
	
#ifndef WEBVIEW
	m_PicturePanel = new CPicturePanel(NULL,this);
	Sizer->Add(m_PicturePanel,0,wxALL|wxEXPAND,0);
#endif
	
	//wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
	//ScrollSizer->Add(hSizer,0,wxALL|wxEXPAND,0);
		
#ifndef WEBVIEW
	m_Html = new wxHtmlWindow(this,ID_HTML,wxDefaultPosition,wxDefaultSize);
#else
	m_Html = wxWebView::New(this,ID_HTML,wxEmptyString);
	
#endif
	m_Html->SetMinSize(wxSize(200,300));
	
	Sizer->Add(m_Html,1,wxALL|wxEXPAND,0);
		
	wxWrapSizer *WrapSizer = new wxWrapSizer(wxHORIZONTAL);
	Sizer->Add(WrapSizer,0,wxALL|wxEXPAND,0);

	m_ButtonManagement = new wxButton(this,ID_MANAGEMENT,GetMsg(MSG_MANAGEMENT));
	WrapSizer->Add(m_ButtonManagement,0,wxALL,2);
	m_ButtonManagement->Disable();	
	m_ButtonGraph = new wxButton(this,ID_GRAPH,GetMsg(MSG_GRAPH));
	WrapSizer->Add(m_ButtonGraph,0,wxALL,2);
	m_ButtonGraph->Disable();
	
	//Scroll->SetScrollbars(20, 20, 20, 20);
	SetSizer(Sizer);
			
}

void CSymbolPanel::OnMenu(wxContextMenuEvent &event)
{
	//wxMenu *Menu = new wxMenu();
	//Menu->AppendCheckItem(ID_SHOW_PICTURE,_("Show picture"));

	//PopupMenu(Menu);
	//delete Menu;

}

void CSymbolPanel::OnShowMenu(wxCommandEvent &event)
{
	bool static a = false;
	a =!a;
//	m_PicturePanel->Show(a);
	this->Layout();
}


/*
void CSymbolPanel::ShowManagement(CSymbol *v)
{
	if(v == NULL)
		return;
	
	if(!v->GetNoSBMS())
	{
		CCommandDialog *CommandDialog = new CCommandDialog(NULL,v);
		CCommandPanel *ptr =  CommandDialog->GetCommandPanel();

		ptr->SetForcedOff(v->GetForcedOff());
		ptr->SetAuto(v->GetAuto());
			
		CommandDialog->ShowModal();
		delete CommandDialog;
	
	}else{
			wxMessageBox(GetMsg(MSG_NO_SBMS_RECORD));
	}
}
*/

void CSymbolPanel::OnManagement(wxCommandEvent &event)
{
	//m_Symbol->ShowManagement(m_Symbol);
}


void CSymbolPanel::OnGraph(wxCommandEvent &event)
{
	//m_Symbol->ShowGraph();
}


void CSymbolPanel::OnHtml(wxHtmlLinkEvent &event)
{
	//event.GetLinkInfo().GetHtmlCell()
/*	int id =  event.GetSelection();

	id = event.GetId();

	wxHtmlLinkInfo link = event.GetLinkInfo();

	long item;
	link.GetHref().ToLong(&item);
	
	wxString t = link.GetTarget();

	long action = -1;
	t.ToLong(&action);

	switch(action)
	{
		case HREF_ACTION_MANAGEMENT:	ShowManagement(m_Symbol);		break;
		break;
	}*/
}

void CSymbolPanel::SetPageEmpty()
{
}

void CSymbolPanel::SetPage1(CSymbol *ptr)
{
/*	
	m_Symbol = ptr;
	void *db = DBConnect();
	if(db == NULL)
		return;

	m_IdSBMS = ptr->GetIdSBMS();
	m_IdBaseStation = ptr->GetBaseStationId();
	m_SBMSID = ptr->GetSBMSID();

	wxString sql = wxString::Format(_("UPDATE `%s` SET new_report='%d' WHERE id='%d'"),TABLE_SBMS,READED_REPORT_FLAG,m_IdSBMS);
	my_query(db,sql);
	
	if(ptr->GetMonitoring() == SYMBOL_IN_MONITORING)
	{
		//if(db_check_right(MODULE_SYMBOL,ACTION_MANAGEMENT,_GetUID())) 
		//{
			if(ptr->GetBusy()) 
				m_ButtonManagement->Disable();
			else
				m_ButtonManagement->Enable();
		
		//} else {
			//m_ButtonManagement->Disable();
		//}
		
		m_ButtonGraph->Enable();
	}else{
		
		m_ButtonGraph->Disable();
		m_ButtonManagement->Disable();
	}
	
	m_HtmlString.Clear();
	m_HtmlString.Append("<html><body style='font-family:Tahoma'>");

	//SetHeader( m_IdSBMS );
	PictureInfo(db,ptr);
	AlarmInfo(ptr);
	SymbolInfo(db,ptr);
	BaseStationInfo(db,m_IdBaseStation);

	if(ptr->GetMonitoring() == SYMBOL_IN_MONITORING) 
	{
		SBMSInfo(db,m_IdSBMS,ptr);
	}
	
	LightInfo(db,ptr->GetId());

	m_HtmlString.Append("</html>");

#ifdef WEBVIEW	
	m_Html->SetPage(m_HtmlString,wxEmptyString);
#else
	m_Html->SetPage(m_HtmlString);
#endif
	//SBMSLastRaport(db,m_SBMSID,m_IdBaseStation);
	//SetGraph(db,m_SBMSID,m_IdBaseStation);
	DBClose(db);
	*/
}

void CSymbolPanel::SetHeader( int _IdSBMS )
{
	wxString str;
	str.Append(_("<table border=1 cellpadding=2 cellspacing=2 width=100%%>"));
	str.Append(wxString::Format(_("<tr><td colspan=3><a target=1 href='%d'>%s</a></td></tr>"),_IdSBMS,GetMsg(MSG_MANAGEMENT)));
	str.Append(_("</table>"));
	m_HtmlString.Append(str);
	
}

void CSymbolPanel::AlarmInfo(CSymbol *ptr)
{	
	wxString str;
	/*
	for(int i = 0; i < ptr->GetAlarmCount();i++)
	{	
		str.Append(_("<table border=1 cellpadding=2 cellspacing=0 width=100%%>"));
		str.Append(wxString::Format(_("<tr><td><font color=red size=2><b>%s</b></font></td></tr>"),ptr->GetAlarm(i)->GetName()));
		str.Append(_("</table>"));
	}
	m_HtmlString.Append(str);
	*/
}

void CSymbolPanel::SymbolInfo(void *db,CSymbol *ptr)
{
	
	wxString str;
	str.Append(_("<table border=0 cellpadding=2 cellspacing=0 width=100%%>"));
	
#ifdef WEBVIEW
	char *b64 = NULL;
	if(GetPictureAsBase64(db,ptr->GetId(),b64))
	{
		str.Append(wxString::Format(_("<tr><td><center><img src=\"data:image/png;base64,%s\"></center></td></tr>"),b64));
		free(b64);
	}
#endif	
/*		
	str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td></tr>"),GetMonitoringAsString(ptr->GetMonitoring())));

	if((ptr->GetMonitoring() == SYMBOL_IN_MONITORING) & (ptr->GetIdSBMS() > 0))
	{
		str.Append(wxString::Format(_("<tr><td><font size=4><b>%s</b></font></td></tr>"),GetLightOnAsString(ptr->GetLightOn())));
		str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td></tr>"),GetAutoAsString(ptr->GetAuto())));
	}
*/	
	str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td></tr>"),ptr->GetName()));
	str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td></tr>"),ptr->GetNumber()));
	str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td></tr>"),FormatLatitude(ptr->GetRLat(),DEFAULT_DEGREE_FORMAT)));
	str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td></tr>"),FormatLongitude(ptr->GetRLon(),DEFAULT_DEGREE_FORMAT)));
	//str.Append(_("<input type='checkbox' name='nazwa' value='wartoœæ'>"));
	
	str.Append(_("</table>"));
	m_HtmlString.Append(str);
	
	
}

void CSymbolPanel::SBMSInfo(void *db,int id_sbms,CSymbol *ptr)
{
	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id ='%d'"),TABLE_SBMS,id_sbms);
	my_query(db,sql);
			
	void *result = db_result(db);
		
	char **row = NULL;
	if(result == NULL)
		return;
		
	row = (char**)db_fetch_row(result);
	if(row)
	{
		wxString str;
		str.Append(_("<table border=0 cellpadding=2 cellspacing=2 width=100%>"));
		str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td></tr>"),Convert(row[FI_SBMS_NAME]).wc_str()));
		
		int phone = atoi(row[FI_SBMS_PHONE]);
		if(phone)
			str.Append(wxString::Format(_("<tr><td><font size=2><b>%d</b></font></td></tr>"),phone));

		int mmsi = atoi(row[FI_SBMS_MMSI]);
		if(mmsi)
			str.Append(wxString::Format(_("<tr><td><font size=2><b>%d</b></font></td></tr>"),mmsi));
		
		//nvtime_t dt;
		//nvdatetime(atoi(row[FI_SBMS_LOCAL_UTC_TIME]),&dt);
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_DATE_TIME_UTC),Convert(row[FI_SBMS_LOCAL_UTC_TIME])));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_LATITUDE),FormatLatitude(atof(row[FI_SBMS_LAT]),DEFAULT_DEGREE_FORMAT)));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_LONGITUDE),FormatLongitude(atof(row[FI_SBMS_LON]),DEFAULT_DEGREE_FORMAT)));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_INPUT_VOLT),row[FI_SBMS_INPUT_VOLT]));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>100%%</b></font></td></tr>"),GetMsg(MSG_POWER_OF_LIGHT)));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_MONITORED_CHANNELS),GetMonitoredChannels(atoi(row[FI_SBMS_MONITORED_CHANNELS]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_OVERLOAD_CHANNELS),GetOverloadChannels(atoi(row[FI_SBMS_OVERLOAD_CHANNELS]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_DOWN_CHANNELS),GetDownChannels(atoi(row[FI_SBMS_DOWN_CHANNELS]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_ANALOG_VALUE),row[FI_SBMS_ANALOG_VALUE]));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_CALIBRATED),GetOnOff(atoi(row[FI_SBMS_MODE_CALIBRATED]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_FORCED_OFF),GetOnOff(atoi(row[FI_SBMS_MODE_FORCED_OFF]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_PHOTOCELL_NIGHT_TIME),GetPhotoCellValue(atoi(row[FI_SBMS_ANALOG_PIN]), atoi(row[FI_SBMS_ANALOG_VALUE]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_FAULT_OUTPUT),GetOnOff(atoi(row[FI_SBMS_MODE_FAULT_OUTPUT]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_SOLAR_CHARGER_ON),GetOnOff(atoi(row[FI_SBMS_MODE_SOLAR_CHARGER_ON]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_SEASON_CONTROL),GetOnOff(atoi(row[FI_SBMS_MODE_SEASON_CONTROL]))));
/*		
		bool alarm = false;
		for(int i = 0; i < ptr->GetAlarmCount();i++)
		{
			if (ptr->GetAlarm(i)->GetIdAlarm() == ALARM_COMMUNICATION_TIMEOUT)
				alarm = true;
		}
		
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_SYNC),GetOnOff(!alarm)));
*/
		str.Append(_("</table>"));

		m_HtmlString.Append(str);
	}
		
	db_free_result(result);

}

void CSymbolPanel::BaseStationInfo(void *db, int id_base_station)
{
	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id ='%d'"),TABLE_BASE_STATION,id_base_station);
	my_query(db,sql);
			
	void *result = db_result(db);
		
	char **row = NULL;
	if(result == NULL)
		return;
		
	row = (char**)db_fetch_row(result);
	if(row)
	{
		wxString str;
		str.Append(_("<table border=0 cellpadding=2 cellspacing=0 width=100%%>"));
		str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td></tr>"),Convert(row[FI_BASE_STATION_NAME]).wc_str()));
		str.Append(_("</table>"));
		m_HtmlString.Append(str);
	}
	db_free_result(result);

}


void CSymbolPanel::LightInfo(void *db,int id_symbol)
{
	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_symbol ='%d'"), VIEW_LIGHT, id_symbol);
	my_query(db,sql);
			
	void *result = db_result(db);	
	char **row = NULL;
	if(result == NULL)
		return;
		
	//row = (char**)db_fetch_row(result);
	while(row = (char**)db_fetch_row(result))
	{
		wxString str;
		wxColor BgColor(atoi(row[FI_VIEW_LIGHT_COLOR]));
		
		str.Append(_("<hr>"));
		str.Append(wxString::Format(_("<font size=2><b>%s</b></font><br><br>"), GetMsg(MSG_LIGHT) ));
		str.Append(_("<table border=0 cellpadding=2 cellspacing=2 width=100%>"));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td bgcolor=#%02X%02X%02X></td></tr>"), GetMsg(MSG_COLOR), BgColor.Red(), BgColor.Green(), BgColor.Blue() ));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s [%s]</b></font></td></tr>"),GetMsg(MSG_COVERAGE),Convert(row[FI_VIEW_LIGHT_COVERAGE]), GetDistanceName(nvDistanceNauticMile)));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_SECTOR_FROM),Convert(row[FI_VIEW_LIGHT_SECTOR_FROM])));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_SECTOR_TO),Convert(row[FI_VIEW_LIGHT_SECTOR_TO])));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_FLASH_CODE),Convert(row[FI_VIEW_LIGHT_CHARACTERISTIC_CODE])));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_IALA),Convert(row[FI_VIEW_LIGHT_CHARACTERISTIC_IALA])));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_CHARACTERISTIC),Convert(row[FI_VIEW_LIGHT_CHARACTERISTIC])));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>0.00 [%s]</b></font></td></tr>"),GetMsg(MSG_LIGHT_RIPLE_DELAY),GetMsg(MSG_SECONDS)));
		str.Append(_("</table>"));
		
		m_HtmlString.Append(str);

	}

	db_free_result(result);

}

void CSymbolPanel::PictureInfo(void *db,CSymbol *ptr)
{
#ifndef WEBVIEW
	m_PicturePanel->Clear();

	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_symbol='%d'"),TABLE_SYMBOL_PICTURE,ptr->GetId());
	my_query(db,sql);
	char **row = NULL;

	void *result = db_result(db);
	if(result == NULL)
		return;
		
	row = (char**)db_fetch_row(result);
	m_PicturePanel->SetDB(db);
	
	if(row)
	{
		m_PicturePanel->SetPictureId(atoi(row[FI_SYMBOL_PICTURE_ID_PICTURE]));
		//m_PicturePanel->Show();
		
	}else{
		
		m_PicturePanel->SetPictureId(-1);
		//m_PicturePanel->Hide();
	}
	
	this->Layout();
	db_free_result(result);
#endif
}

#ifdef WEBVIEW
void CSymbolPanel::OnNavigationRequest(wxWebViewEvent& event)
{
    
    //wxLogMessage("%s", "Navigation request to '" + event.GetURL() + "' (target='" + event.GetTarget() + "')");

	int id = event.GetId();

    //wxASSERT(m_browser->IsBusy());

    //If we don't want to handle navigation then veto the event and navigation
    //will not take place, we also need to stop the loading animation
    //if(!m_tools_handle_navigation->IsChecked())
    //{
       // evt.Veto();
        //m_toolbar->EnableTool( m_toolbar_stop->GetId(), false );
    //}
    //else
    //{
      //  UpdateState();
    //}
	event.Skip();
}

void CSymbolPanel::OnLoaded(wxWebViewEvent& event)
{
	event.Skip();
}
#endif

void CSymbolPanel::SetSBMS()
{

}

void CSymbolPanel::OnAlarm(wxCommandEvent &event)
{
	//CAlarmDialog *AlarmDialog = new CAlarmDialog(NULL,_("test"));
	//AlarmDialog->ShowModal();
	//delete AlarmDialog;
}

