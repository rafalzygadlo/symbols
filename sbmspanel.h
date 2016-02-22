#ifndef __SBMSPANEL_H
#define __SBMSPANEL_H

#include "conf.h"
#include <wx/html/htmlwin.h>
#ifdef WEBVIEW
#include <wx/webview.h>
#endif
#include "navibroker.h"
#include "tgamem.h"
#include "picture.h"
#include "grid.h"
#include "graph.h"
#include "light.h"
#include "sbms.h"
#include "graphdialog.h"
#include "icon.h"
#include "sbms.h"

class CGraphDialog;
class CSBMS;
class CSBMSPanel : public wxPanel
{
#ifndef WEBVIEW
	CPicturePanel *m_PicturePanel;
#endif
	//CSymbol *m_Symbol;	
	CGraphDialog *m_GraphDialog;
#ifdef WEBVIEW
	wxWebView *m_Html;
#else
	wxHtmlWindow *m_Html;
#endif
	int m_IdSBMS;
	int m_IdBaseStation;
	int m_SBMSID;
	wxButton *m_ButtonManagement;
	wxButton *m_ButtonGraph;
	wxString m_HtmlString;
	
	void SetGui();
	void AlarmInfo(CSBMS *ptr);
	void SymbolInfo(void *db,CSymbol *ptr);
	void SBMSInfo(void *db,int id_symbol);
	void PictureInfo(void *db,CSymbol *ptr);
	void BaseStationInfo(void *db, int id_base_station);
	void LightInfo(void *db,int id_symbol);
	void SBMSLastRaport(void *db, int id_sbms, int id_base_station);
	void SetGraph(void *db, int id_sbms, int id_base_station);
	void OnManagement(wxCommandEvent &event);
	void OnGraph(wxCommandEvent &event);
	void OnAlarm(wxCommandEvent &event);
	void OnMenu(wxContextMenuEvent &event);
	void OnShowMenu(wxCommandEvent &event);
	void OnHtml(wxHtmlLinkEvent &event);
#ifdef WEBVIEW
	void OnNavigationRequest(wxWebViewEvent& event);
	void OnLoaded(wxWebViewEvent& event);
#endif
	

public:

	CSBMSPanel(wxWindow *parent);
	~CSBMSPanel();
	
	//SET
	void SetPage(CSBMS *ptr);
	void SetPageEmpty();
	void SetSBMS();
	
	
	enum
	{
		ID_MANAGEMENT = 2600,
		ID_GRAPH,
		ID_ALARM,
		ID_SHOW_PICTURE,
		ID_CALIBRATED,
		ID_FORCED_OFF,
		ID_PHOTOCELL_NIGHT_TIME,
		ID_FAULT_OUTPUT,
		ID_SOLAR_CHARGER,
		ID_SYNC_MASTER,
		ID_SEASON_CONTROL,
		ID_HTML,

	};

	DECLARE_EVENT_TABLE();
	
};

#endif