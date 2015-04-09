#ifndef __DISPLAY
#define __DISPLAY

#include "dll.h"
#include "listctrl.h"
#include "navimapioapi.h"
#include <wx/fileconf.h>
#include <vector>
#include <wx/wx.h>
#include "navidisplayapi.h"
#include <wx/fileconf.h>
#include <wx/listctrl.h>
#include <wx/hyperlink.h>

#ifdef _WIN32
	#include <windows.h>
	#include <crtdbg.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


class CMapPlugin;
class NAVIDISPLAYAPI CDisplayPlugin: public CNaviDiaplayApi 
{
	void *m_DB;
	CNaviBroker *m_Broker;
	CMapPlugin *m_MapPlugin;
	CSymbolPanel *m_SymbolPanel;
	wxPanel *m_ControlPanel;
	CSymbol *m_Selected;
	CSymbol *m_OldSelected;
	wxString m_ControlName;
	void WriteConfig();
	void ReadConfig();
	void ShowControls();
	void SignalInsert();
	void SignalSelect();
	void SignalClear();
	bool EnableControls();
	void SwitchAction();

public:
	
	CDisplayPlugin(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxT("DisplayApiPanel") );
	~CDisplayPlugin();
	
	CNaviBroker *GetBroker();
	
	virtual bool IsValidSignal(CDisplaySignal *SignalID);
	virtual void OnWork(CDisplaySignal *Signal);
	virtual void BeforeWork(CDisplaySignal *Signal);
	virtual void AfterWork(CDisplaySignal *Signal);
	virtual void OnRender(wxGCDC &dc);
		
	DECLARE_EVENT_TABLE();
};

#ifdef __cplusplus
}
#endif

#endif