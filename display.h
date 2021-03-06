#ifndef __DISPLAY
#define __DISPLAY

#include <wx/srchctrl.h>
#include <wx/fileconf.h>
#include <wx/listctrl.h>
#include <wx/hyperlink.h>
#include <wx/fileconf.h>
#include <vector>
#include <wx/wx.h>
#include "dll.h"
#include "listctrl.h"
#include "navimapioapi.h"
#include "navidisplayapi.h"
#include "symbolpanel.h"
#include "symbollisthtml.h"
#include "alarmlist.h"
#include "grouplist.h"
#include "commandlist.h"

#ifdef _WIN32
	#include <windows.h>
	#include <crtdbg.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

class CMapPlugin;
class CAlarmList;
class CSymbolPanel;
class CCommandModelList;
class CGroupList;
class CSymbolListHtml;
class NAVIDISPLAYAPI CDisplayPlugin: public CNaviDiaplayApi 
{
	void *m_DB;
	wxNotebook *m_Notebook;
	CNaviBroker *m_Broker;
	CMapPlugin *m_MapPlugin;
	CSymbolPanel *m_SymbolPanel;
	wxPanel *m_ControlPanel;
	CSymbol *m_Selected;
	CSymbol *m_OldSelected;
	CSymbolListHtml *m_SymbolListHtml;
	CAlarmList *m_AlarmList;
	CCommandModelList *m_CommandList;
	CGroupList *m_GroupList;
	
	wxSearchCtrl *m_SearchText;
	wxStaticText *m_NightTime;
	int m_OldSymbolCount;
	int m_OldAlarmCount;
	int m_OldComandCount;
	int m_OldGroupCount;
	bool m_OldNight;
	wxPanel *m_Page3;
	wxPanel *m_Page4;
	//wxButton *m_ButtonManagement;
	//wxButton *m_ButtonGraph;
	wxButton *m_ButtonAlarm;

	wxString m_ControlName;
	int m_ControlType;
		
	void WriteConfig();
	void ReadConfig();
	void ShowControls();
	void SignalInsert();
	void SignalSelect();
	void SignalClear();
	bool EnableControls();
	void SwitchAction();
	void Signal();
	void SignalSynchro();
	void RemoveControl(int type);
	wxPanel *GetPage1(wxWindow *parent);
	wxPanel *GetPage2(wxWindow *parent);
	wxPanel *GetPage3(wxWindow *parent);
	wxPanel *GetPage4(wxWindow *parent);
	wxPanel *GetPage5(wxWindow *parent);
	wxPanel *GetPage6(wxWindow *parent);
	wxPanel *GetPage7(wxWindow *parent);

	void ShowInfoPanel(bool show);
	void OnMenuRange(wxCommandEvent &event);
	void OnMenu(wxContextMenuEvent &event);
	void OnSearchEnter(wxCommandEvent &event);
	void OnSearchText(wxCommandEvent &event);
	void OnSetNightTime(wxCommandEvent &event);
	void OnFilter(wxCommandEvent &event);
	void OnManagement(wxCommandEvent &event);
	//void OnGraph(wxCommandEvent &event);

public:
	
	CDisplayPlugin(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxT("DisplayApiPanel") );
	~CDisplayPlugin();
	
	CNaviBroker *GetBroker();
	
	virtual bool IsValidSignal(CDisplaySignal *SignalID);
	virtual void OnWork(CDisplaySignal *Signal);
	virtual void BeforeWork(CDisplaySignal *Signal);
	virtual void AfterWork(CDisplaySignal *Signal);
	virtual void OnRender(wxGCDC &dc);

	enum
	{
		ID_SEARCH = 1200,
		ID_FILTER,
		ID_NIGHT_TIME,
		ID_MANAGEMENT,
		ID_ALARM,
	};

	DECLARE_EVENT_TABLE();
};

#ifdef __cplusplus
}
#endif

#endif