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

void CSymbolPanel::SetPageEmpty()
{
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
	m_HtmlString.Append("</html>");
	
	for(int i = 0; i < ptr->GetDriverCount();i++)
	{
		m_HtmlString.Append(ptr->GetDriver(i)->GetFullText());
		//this->GetSizer()->Add(Panel,0,wxALL|wxEXPAND,5);
	}

#ifdef WEBVIEW	
	m_Html->SetPage(m_HtmlString,wxEmptyString);
#else
	m_Html->SetPage(m_HtmlString);
#endif


	DBClose(db);

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

	str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td></tr>"),GetMonitoringAsString(ptr->GetMonitoring())));
	str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td></tr>"),ptr->GetName()));
	str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td></tr>"),ptr->GetNumber()));
	str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td></tr>"),FormatLatitude(ptr->GetRLat(),DEFAULT_DEGREE_FORMAT)));
	str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td></tr>"),FormatLongitude(ptr->GetRLon(),DEFAULT_DEGREE_FORMAT)));
	
	str.Append(_("</table>"));
	m_HtmlString.Append(str);
	
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
