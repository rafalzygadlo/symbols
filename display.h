#ifndef __DISPLAY
#define __DISPLAY

#include "dll.h"
#include "listctrl.h"
#include "NaviMapIOApi.h"
#include <wx/fileconf.h>
#include <vector>
#include <wx/wx.h>
#include "NaviDisplayApi.h"
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

class CListCtrl;
class CMapPlugin;

class NAVIDISPLAYAPI CDisplayPlugin: public CNaviDiaplayApi 
{
	CNaviBroker *Broker;
	CMapPlugin *MapPlugin;
	//CListCtrl *ShipList;
	wxPanel *ControlPanel;
		//*InfoPanel, 
	wxBoxSizer *Page1Sizer;
	//wxStaticText *ShipName, *Lon, *Lat;
	//wxTextCtrl *ShipDesc;
	CSymbol *Selected;
	wxString ControlName;
	wxButton *ButtonOn,*ButtonOff;
	int Column1Width,Column2Width,Column3Width,Column4Width,Column5Width;
	void WriteConfig();
	void ReadConfig();
	void OnReport(wxHyperlinkEvent &event);
	void OnData(wxHyperlinkEvent &event);
	void OnConfig(wxHyperlinkEvent &event);
	void OnPowerOn(wxCommandEvent &event);
	void OnPowerOff(wxCommandEvent &event);
	void ShowControls();
	void SignalInsert();
	void SignalSelect();
	void SignalClear();
	bool EnableControls();
	void SwitchAction();

public:
	
	CDisplayPlugin(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL, const wxString& name = wxT("DisplayApiPanel") );
	~CDisplayPlugin();
	
	//void SetSelectedShip(SSymbol *ship);
	//void ShipProperties(SSymbol *ship);
	//void ShipConfig(SSymbol *ship);
	//void ShipData(SSymbol *ship);
	//void ShipReport(SSymbol *ship);
	//void ShipReportConfig(SSymbol *ship);
	//bool ShipIsSelected(SSymbol *ship);
	//void ShowInfoPanel(bool show, SSymbol *ship);
	CNaviBroker *GetBroker();
	

	virtual bool IsValidSignal(CDisplaySignal *SignalID);
	virtual void OnWork(CDisplaySignal *Signal);
	virtual void BeforeWork(CDisplaySignal *Signal);
	virtual void AfterWork(CDisplaySignal *Signal);
	virtual void OnRender(wxGCDC &dc);

	enum 
	{
		ID_BEGIN_THREAD = 2345,
		ID_END_THREAD,
		ID_REPORT = 3342,
		ID_DATA,
		ID_CONFIG,
		ID_ON,
		ID_OFF
	};
	
	DECLARE_EVENT_TABLE();
};

#ifdef __cplusplus
}
#endif

#endif