#include <wx/wx.h>
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
#include "options.h"

BEGIN_EVENT_TABLE(CSymbolPanel,wxPanel)
	EVT_BUTTON(ID_MANAGEMENT,OnManagement)
	EVT_BUTTON(ID_GRAPH,OnGraph)
END_EVENT_TABLE()


CSymbolPanel::CSymbolPanel(wxWindow *parent)
:wxPanel(parent,wxID_ANY)
{
	m_Symbol = NULL;
	m_GraphDialog = NULL;
	GetPage1();
}
CSymbolPanel::~CSymbolPanel()
{
	delete m_GraphDialog;
}

void CSymbolPanel::GetPage1()
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	
	wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);
	Sizer->Add(hSizer);
	
	m_PicturePanel = new CPicturePanel(NULL,this);
	hSizer->Add(m_PicturePanel,0,wxALL,0);
	
	wxBoxSizer * vSizer = new wxBoxSizer(wxVERTICAL);
	hSizer->Add(vSizer,0,wxALL|wxEXPAND,4);

	m_ButtonManagement = new wxButton(this,ID_MANAGEMENT,GetMsg(MSG_MANAGEMENT));
	vSizer->Add(m_ButtonManagement,0,wxALL|wxEXPAND,2);
	m_ButtonManagement->Disable();

	m_ButtonGraph = new wxButton(this,ID_GRAPH,GetMsg(MSG_GRAPH));
	vSizer->Add(m_ButtonGraph,0,wxALL|wxEXPAND,2);
	m_ButtonGraph->Disable();
	
	m_ButtonAlert = new wxButton(this,ID_ALERT,GetMsg(MSG_ALERT));
	vSizer->Add(m_ButtonAlert,0,wxALL|wxEXPAND,2);
	m_ButtonAlert->Disable();

	m_Html = new wxHtmlWindow(this,wxID_ANY);
	m_Html->SetMinSize(wxSize(200,150));
	Sizer->Add(m_Html,1,wxALL|wxEXPAND,2);
	this->SetSizer(Sizer);
			
}

void CSymbolPanel::SetPageEmpty()
{
}

void CSymbolPanel::SetPage1(CSymbol *ptr)
{
	m_Symbol = ptr;
	void *db = DBConnect();
	if(db == NULL)
		return;
	
	if(db_check_right(MODULE_SYMBOL,ACTION_MANAGEMENT,_GetUID()))
		m_ButtonManagement->Enable();
	else
		m_ButtonManagement->Disable();

	if(ptr->GetBusy())
		m_ButtonManagement->Disable();
	else
		m_ButtonManagement->Enable();

	int count = ptr->GetAlertCount();
	if(count > 0)
	{
		m_ButtonAlert->Enable();
		m_ButtonAlert->SetLabel(wxString::Format(_("%s (%d)"),GetMsg(MSG_ALERT),count));

	}else{

		m_ButtonAlert->Disable();
		m_ButtonAlert->SetLabel(GetMsg(MSG_ALERT));
	}

	m_ButtonGraph->Enable();
	m_IdSBMS = ptr->GetIdSBMS();
	m_IdBaseStation = ptr->GetBaseStationId();
	m_SBMSID = ptr->GetSBMSID();
	m_Html->SetPage(wxEmptyString);

	PictureInfo(db,ptr);
	SymbolInfo(db,ptr);
	SBMSInfo(db,m_IdSBMS);
	BaseStationInfo(db,m_IdBaseStation);
	SBMSLastRaport(db,m_SBMSID,m_IdBaseStation);
	//SetGraph(db,m_SBMSID,m_IdBaseStation);
	
	DBClose(db);
}

void CSymbolPanel::SetHeader()
{
	wxString str;
	str.Append(_("<table border=0 cellpadding=2 cellspacing=2 width=100%%>"));
	str.Append(wxString::Format(_("<tr><td colspan=3><b><a href=\"#%d\">%s</a></b></td></tr>"),HTML_ANCHOR_LAST_REPORT,GetMsg(MSG_LAST_REPORT) ));
	str.Append(_("</table>"));
	m_Html->AppendToPage(str);
}

void CSymbolPanel::SymbolInfo(void *db,CSymbol *ptr)
{
	wxString sql = wxString::Format(_("SELECT *FROM `%s` WHERE id ='%d'"),TABLE_SYMBOL,ptr->GetId());
	my_query(db,sql);
	
	void *result = db_result(db);
		
	char **row = NULL;
	if(result == NULL)
		return;
		
	row = (char**)db_fetch_row(result);
	if(row)
	{
		wxString str;
		str.Append(_("<hr>"));
		//str.Append(_("<font size=2>symbol info</font>"));
		str.Append(_("<table border=0 cellpadding=2 cellspacing=0 width=100%%>"));
		str.Append(wxString::Format(_("<tr><td><font size=5><b>%s</b></font></td></tr>"),Convert(row[FI_SYMBOL_NAME]).wc_str()));
		str.Append(wxString::Format(_("<tr><td><font size=4><b>%s</b></font></td></tr>"),Convert(row[FI_SYMBOL_NUMBER])));
		str.Append(wxString::Format(_("<tr><td><font size=3><b>%s</b></font></td></tr>"),FormatLatitude(ptr->GetLat(),DEFAULT_DEGREE_FORMAT)));
		str.Append(wxString::Format(_("<tr><td><font size=3><b>%s</b></font></td></tr>"),FormatLongitude(ptr->GetLon(),DEFAULT_DEGREE_FORMAT)));
	
		if(atoi(row[FI_SYMBOL_IN_MONITORING]))
			str.Append(wxString::Format(_("<tr><td><font size=3>%s</td></tr>"),GetMsg(MSG_IN_MONITORING)));
	
		if(atoi(row[FI_SYMBOL_ON_POSITION]))
			str.Append(wxString::Format(_("<tr><td><font size=3>%s</font></td></tr>"),GetMsg(MSG_ON_POSITION)));
			
		if(m_IdSBMS == 0)
			str.Append(wxString::Format(_("<tr><td><font color=red><font size=3>%s</font></td></tr>"),GetMsg(MSG_NO_SBMS)));

		//str.Append(wxString::Format(_("<tr><td>%s</td></tr>"),Convert(row[FI_SYMBOL_INFO])));
		str.Append(_("</table>"));
		m_Html->AppendToPage(str);
	}
	
	db_free_result(result);

}

void CSymbolPanel::SBMSInfo(void *db,int id_sbms)
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
		str.Append(_("<table border=0 cellpadding=2 cellspacing=0 width=100%%>"));
		str.Append(wxString::Format(_("<tr><td><font size=4><b>(%d) - %s</b></font></td></tr>"),atoi(row[FI_SBMS_SBMSID]),Convert(row[FI_SBMS_NAME]).wc_str()));
		int phone = atoi(row[Fi_SBMS_PHONE]);
		if(phone)
			str.Append(wxString::Format(_("<tr><td><font size=4><b>%d</b></font></td></tr>"),phone));

		int mmsi = atoi(row[FI_SBMS_MMSI]);
		if(mmsi)
			str.Append(wxString::Format(_("<tr><td><font size=4><b>%d</b></font></td></tr>"),mmsi));
		
		str.Append(_("</table>"));
			
		m_Html->AppendToPage(str);
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
		str.Append(wxString::Format(_("<tr><td><font size=4><b>%s</b></font></td></tr>"),Convert(row[FI_BASE_STATION_NAME]).wc_str()));
		str.Append(_("</table>"));
		m_Html->AppendToPage(str);
	}

	db_free_result(result);

}

void CSymbolPanel::SBMSLastRaport(void *db, int id_sbms, int id_base_station)
{
	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE SBMSID ='%d' AND id_base_station='%d' ORDER BY local_utc_time DESC LIMIT 0,1"),TABLE_STANDARD_REPORT,id_sbms,id_base_station);
	my_query(db,sql);
			
	void *result = db_result(db);
		
	char **row = NULL;
	if(result == NULL)
		return;
		
	while(row = (char**)db_fetch_row(result))
	{
		wxString str;
		str.Append(_("<hr>"));
		//str.Append(wxString::Format(_("<font size=2><a name=\"%d\"><b>%s</b></a></font>"),HTML_ANCHOR_LAST_REPORT,GetMsg(MSG_LAST_REPORT)));
		str.Append(_("<table border=0 cellpadding=2 cellspacing=0 width=100%%>"));
		
		nvtime_t dt;
		nvdatetime(atoi(row[FI_STANDARD_REPORT_DATE_TIME_STAMP]),&dt);
		
		str.Append(wxString::Format(_("<tr><td>%s</td><td><b>%s</b></td></tr>"),GetMsg(MSG_DATE_TIME_UTC),GetNvDateTime(dt)));

		str.Append(wxString::Format(_("<tr><td>%s</td><td><b>%s</b></td></tr>"),GetMsg(MSG_INPUT_VOLT),row[FI_STANDARD_REPORT_INPUT_VOLT]));
		str.Append(wxString::Format(_("<tr><td>%s</td><td><b>%s</b></td></tr>"),GetMsg(MSG_MONITORED_CHANNELS),GetMonitoredChannels(atoi(row[FI_STANDARD_REPORT_MONITORED_CHANNELS]))));
		str.Append(wxString::Format(_("<tr><td>%s</td><td><b>%s</b></td></tr>"),GetMsg(MSG_OVERLOAD_CHANNELS),GetOverloadChannels(atoi(row[FI_STANDARD_REPORT_OVERLOAD_CHANNELS]))));
		str.Append(wxString::Format(_("<tr><td>%s</td><td><b>%s</b></td></tr>"),GetMsg(MSG_DOWN_CHANNELS),GetDownChannels(atoi(row[FI_STANDARD_REPORT_DOWN_CHANNELS]))));
		str.Append(wxString::Format(_("<tr><td>%s</td><td><b>%s</b></td></tr>"),GetMsg(MSG_ANALOG_PIN),row[FI_STANDARD_REPORT_ANALOG_PIN]));
		str.Append(wxString::Format(_("<tr><td>%s</td><td><b>%s</b></td></tr>"),GetMsg(MSG_DIGITAL_VALUE),row[FI_STANDARD_REPORT_DIGITAL_VALUE]));
		str.Append(wxString::Format(_("<tr><td>%s</td><td><b>%s</b></td></tr>"),GetMsg(MSG_ANALOG_VALUE),row[FI_STANDARD_REPORT_ANALOG_VALUE]));
		str.Append(_("<tr><td><br></td></tr>"));
		str.Append(wxString::Format(_("<tr><td>%s</td><td><b>%s</b></td></tr>"),GetMsg(MSG_CALIBRATED),GetOnOff(atoi(row[FI_STANDARD_REPORT_MODE_CALIBRATED]))));
		str.Append(wxString::Format(_("<tr><td>%s</td><td><b>%s</b></td></tr>"),GetMsg(MSG_FORCED_OFF),GetOnOff(atoi(row[FI_STANDARD_REPORT_MODE_FORCED_OFF]))));
		str.Append(wxString::Format(_("<tr><td>%s</td><td><b>%s</b></td></tr>"),GetMsg(MSG_PHOTOCELL_NIGHT_TIME),GetOnOff(atoi(row[FI_STANDARD_REPORT_MODE_PHOTOCELL_NIGHT_TIME]))));
		str.Append(wxString::Format(_("<tr><td>%s</td><td><b>%s</b></td></tr>"),GetMsg(MSG_RESERVED),GetOnOff(atoi(row[FI_STANDARD_REPORT_MODE_RESERVED]))));
		str.Append(wxString::Format(_("<tr><td>%s</td><td><b>%s</b></td></tr>"),GetMsg(MSG_FAULT_OUTPUT),GetOnOff(atoi(row[FI_STANDARD_REPORT_MODE_FAULT_OUTPUT]))));
		str.Append(wxString::Format(_("<tr><td>%s</td><td><b>%s</b></td></tr>"),GetMsg(MSG_SOLAR_CHARGER_ON),GetOnOff(atoi(row[FI_STANDARD_REPORT_MODE_SOLAR_CHARGER_ON]))));
		str.Append(wxString::Format(_("<tr><td>%s</td><td><b>%s</b></td></tr>"),GetMsg(MSG_SYNC_MASTER),GetOnOff(atoi(row[FI_STANDARD_REPORT_MODE_SYNC_MASTER]))));
		str.Append(wxString::Format(_("<tr><td>%s</td><td><b>%s</b></td></tr>"),GetMsg(MSG_SEASON_CONTROL),GetOnOff(atoi(row[FI_STANDARD_REPORT_MODE_SEASON_CONTROL]))));

		
		
		

		//str.Append(wxString::Format(_("<tr><td><font size=4><b>%s</b></font></td></tr>"),Convert(row[FI_SBMS_])));
		str.Append(_("</table>"));
				
		m_Html->AppendToPage(str);
	}

	db_free_result(result);
}

void CSymbolPanel::PictureInfo(void *db,CSymbol *ptr)
{
	m_PicturePanel->Clear();
	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_symbol='%d'"),TABLE_SYMBOL_PICTURE,ptr->GetId());
	my_query(db,sql);
	char **row = NULL;

	void *result = db_result(db);
	if(result == NULL)
		return;
		
	row = (char**)db_fetch_row(result);
	
	if(row)
	{
		m_PicturePanel->SetDB(db);
		m_PicturePanel->SetPictureId(atoi(row[FI_SYMBOL_PICTURE_ID_PICTURE]));
	}
		
	db_free_result(result);

}

void CSymbolPanel::SetGraph(void *db, int id_sbms, int id_base_station)
{
	/*
	wxString sql = wxString::Format(_("SELECT input_volt FROM `%s` WHERE SBMSID ='%d' AND id_base_station='%d' ORDER BY local_utc_time DESC"),TABLE_STANDARD_REPORT,id_sbms,id_base_station);
	my_query(db,sql);
			
	void *result = db_result(db);
		
	char **row = NULL;
	if(result == NULL)
		return;
	
	m_Graph->Clear();
	int count = 0;
	while(row = (char**)db_fetch_row(result))
	{
		nvPoint3f pt;
		
		pt.x = count++;
		pt.y = atof(row[0]);
		m_Graph->AddPoint(pt);
		nvRGBA c;
		c.A = 255; c.R = 0; c.G = 255; c.B = 0;
		m_Graph->AddColor(c);
	}
	
	m_Graph->SetMin(11);
	m_Graph->SetMax(14);
	m_Graph->SetTitle(GetMsg(MSG_INPUT_VOLT));
	m_Graph->Refresh();
	db_free_result(result);
	*/
}

void CSymbolPanel::SetSBMS()
{

}

void CSymbolPanel::OnManagement(wxCommandEvent &event)
{
	void *db = DBConnect();
	if(db == NULL)
		return;
	
	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id ='%d'"),TABLE_SBMS,m_IdSBMS);
	my_query(db,sql);

	void *result = db_result(db);
		
	char **row = NULL;
	if(result)
	{
	
		if(row = (char**)db_fetch_row(result))
		{

			CCommandDialog *CommandDialog = new CCommandDialog(this,m_Symbol);
			CCommandPanel *ptr =  CommandDialog->GetCommandPanel();

			ptr->SetForcedOff(atoi(row[FI_SBMS_MODE_FORCED_OFF]));
			
			CommandDialog->ShowModal();
			delete CommandDialog;
	
		}else{
			wxMessageBox(GetMsg(MSG_NO_SBMS_RECORD));
		}
	}
	
	DBClose(db);
}

void CSymbolPanel::OnGraph(wxCommandEvent &event)
{
	void *db = DBConnect();
	if(db == NULL)
		return;
	
	if(m_GraphDialog == NULL)
		m_GraphDialog = new CGraphDialog(this,m_Symbol);
	CGraph *Graph = m_GraphDialog->GetGraph();
	
	wxString sql = wxString::Format(_("SELECT input_volt,local_utc_time_stamp FROM `%s` WHERE SBMSID ='%d' AND id_base_station='%d' ORDER BY local_utc_time_stamp"),TABLE_STANDARD_REPORT,m_SBMSID,m_IdBaseStation);
	my_query(db,sql);
			
	void *result = db_result(db);
		
	char **row = NULL;
	if(result == NULL)
		return;
	
	Graph->Clear();
	int count = 0;
	float value = 0;
	int time = 0;
	int _time = 0;
	int seconds_to = 0;
	int seconds_from = 0;
	float min,max;
	min = max = 0;
	bool set = true;
	while(row = (char**)db_fetch_row(result))
	{
		nvPoint3f pt;
		
		value = atof(row[0]);
		time = atoi(row[1]);
		
		nvRGBA c;

		if(set)			{ min = value;	max = value; _time = time; seconds_from = time; set = false;}
		if(max < value)	{ max = value;}
		if(min > value)	{ min = value;}
		time = abs(time - _time);
		
		pt.x = time;
		pt.y = value;
		pt.z = 0;
		
		seconds_to = time  + _time;
		if(value <= GetLowerTreshold() || value  >= GetUpperTreshold())
		{
			c.A = 200; c.R = 255; c.G = 0; c.B = 0;
		}else{
			c.A = 200; c.R = 0; c.G = 255; c.B = 0;
		}
		
		Graph->AddPoint(pt);
		Graph->AddColor(c);
	}
	
	Graph->SetTimeFrom(seconds_from);
	Graph->SetTimeTo(seconds_to);
	Graph->SetMin(min);
	Graph->SetMax(max);
	Graph->SetTitle(GetMsg(MSG_INPUT_VOLT));
	Graph->Refresh();
	db_free_result(result);
	
	DBClose(db);
	m_GraphDialog->SetTitle(GetMsg(MSG_INPUT_VOLT));
	m_GraphDialog->ShowModal();

}