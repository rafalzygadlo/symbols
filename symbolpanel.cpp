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
	//EVT_CONTEXT_MENU(OnContextMenu)
END_EVENT_TABLE();

CSymbolPanel::CSymbolPanel(wxWindow *parent)
:wxPanel(parent,wxID_ANY)
{
	m_Symbol = NULL;
	m_HtmlString = wxEmptyString;
	SetGui();
#ifdef WEBVIEW
	m_Html->LoadURL("about:blank");
#endif
}

CSymbolPanel::~CSymbolPanel()
{
		
}

void CSymbolPanel::SetGui()
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
#ifndef WEBVIEW
	m_PicturePanel = new CPicturePanel(NULL,this);
	Sizer->Add(m_PicturePanel,0,wxALL|wxEXPAND,0);
#endif
		
	
#ifndef WEBVIEW
	m_Html = new wxHtmlWindow(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);
#else
	m_Html = wxWebView::New(this,ID_HTML,wxEmptyString);
	
#endif


	m_Html->SetMinSize(wxSize(200,300));
	Sizer->Add(m_Html,1,wxALL|wxEXPAND,0);
		
	SetSizer(Sizer);
			
}


void CSymbolPanel::SetPage(CSymbol *ptr)
{
	m_Symbol = ptr;
	void *db = DBConnect();
	if(db == NULL)
		return;

	m_HtmlString.Clear();
	m_HtmlString.Append("<html><body style='font-family:Tahoma'>");
	PictureInfo(db,ptr);
	SymbolInfo(db,ptr);
	DriverInfo(ptr);
	LightInfo(db,ptr);
	m_HtmlString.Append("</html>");

#ifdef WEBVIEW	
	m_Html->SetPage(m_HtmlString,wxEmptyString);
#else
	m_Html->SetPage(m_HtmlString);
#endif
	
	DBClose(db);

}

void CSymbolPanel::SymbolInfo(void *db,CSymbol *ptr)
{
	m_HtmlString.Append(ptr->GetFullHtml());
}

void CSymbolPanel::DriverInfo(CSymbol *ptr) 
{
	for(int i = 0; i < ptr->GetDriverCount();i++)
	{
		m_HtmlString.Append(ptr->GetDriver(i)->GetAlarmHtml());
		m_HtmlString.Append(ptr->GetDriver(i)->GetDriverFullHtml());
	}
}

void CSymbolPanel::LightInfo(void *db,CSymbol *ptr)
{
	wxString sql = wxString::Format(_("SELECT color,coverage,sector_from,sector_to,code,iala,name FROM `%s`,`%s` WHERE id_symbol ='%d' AND id_characteristic=id"), TABLE_SYMBOL_LIGHT,TABLE_CHARACTERISTIC, ptr->GetId());
	my_query(db,sql);
			
	void *result = db_result(db);	
	char **row = NULL;
	if(result == NULL)
		return;
		
	//row = (char**)db_fetch_row(result);
	while(row = (char**)db_fetch_row(result))
	{
		wxString str;
		wxColor BgColor(atoi(row[0]));
		
		str.Append(_("<hr>"));
		str.Append(wxString::Format(_("<font size=2><b>%s</b></font><br><br>"), GetMsg(MSG_LIGHT) ));
		str.Append(_("<table border=0 cellpadding=0 cellspacing=0 width=100%>"));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td bgcolor=#%02X%02X%02X>"), GetMsg(MSG_COLOR), BgColor.Red(), BgColor.Green(), BgColor.Blue() ));
		str.Append(_("<table border=0 cellpadding=0 cellspacing=0 width=100%%><tr><td><font size=4><b><br></b></font></td></tr></table></td></tr>"));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s [%s]</b></font></td></tr>"),GetMsg(MSG_COVERAGE),Convert(row[1]), GetDistanceName(nvDistanceNauticMile)));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_SECTOR_FROM),Convert(row[2])));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_SECTOR_TO),Convert(row[3])));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_FLASH_CODE),Convert(row[4])));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_IALA),Convert(row[5])));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_CHARACTERISTIC),Convert(row[6])));
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
				
	}else{
		
		m_PicturePanel->SetPictureId(-1);
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
