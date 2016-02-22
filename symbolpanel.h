#ifndef __SYMBOLPANEL
#define __SYMBOLPANEL

#include "conf.h"
#include <wx/html/htmlwin.h>
#ifdef WEBVIEW
#include <wx/webview.h>
#endif
#include "symbolpanel.h"
#include "navibroker.h"
#include "tgamem.h"
#include "picture.h"
#include "grid.h"
#include "graph.h"
#include "light.h"
#include "symbol.h"
#include "graphdialog.h"
#include "icon.h"
#include "sbmsactionpanel.h"

class CGraphDialog;
class CSymbolPanel : public wxPanel
{
	wxButton *m_ButtonAction;
#ifndef WEBVIEW
	CPicturePanel *m_PicturePanel;
#endif
	CSymbol *m_Symbol;	
	
#ifdef WEBVIEW
	wxWebView *m_Html;
#else
	wxHtmlWindow *m_Html;
#endif

	wxString m_HtmlString;
		
	void SetGui();
	void PictureInfo(void *db,CSymbol *ptr);
	void SymbolInfo(void *db,CSymbol *ptr);
	void LightInfo(void *db,CSymbol *ptr);
	void DriverInfo(CSymbol *ptr);
	void OnButtonAction(wxCommandEvent &event);

public:

	CSymbolPanel(wxWindow *parent);
	~CSymbolPanel();
	
	void SetPage(CSymbol *ptr);
	void SetPageEmpty();
	void SetSBMS();
	
	enum
	{
		ID_ACTION	= 3421,
		ID_GRAPH,
	};


	DECLARE_EVENT_TABLE();
	
};

#endif