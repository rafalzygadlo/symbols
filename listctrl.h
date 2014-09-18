#ifndef __LISTCTRL
#define __LISTCTRL

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "NaviBroker.h"
#include "display.h"
#include "frame.h"

class CDisplayPlugin;
class CListCtrl: public wxListCtrl
{
	wxImageList *ImageListSmall;
	bool Order;
	int SelectedColumn;
	CListCtrl *ThisPtr;
	int VisibleChartType;
	int Type;
	wxMutex mutex;
	int item_count;
	wxMenu *Menu;
	wxListItemAttr selected, deselected;
	CDisplayPlugin *Plugin;
	wxArrayPtrVoid *ShipList;
	wxArrayPtrVoid *SelectedShipList;
		
	wxString CatalogPath;
	//static bool SortFunction(CNaviGeometry *a, CNaviGeometry *b);
	//int IsInstalled(CNaviGeometry *geometry,CNaviGeometryGroup *installed); // -1 nie ma na liscie zainstalowanych (0/1 jest zainstalowany 0 nie pobrany do koñca 1 pobrany)
	void MenuInstalled();
	void MenuVisible();
	void MenuAll();
	void MenuQueue();
	//void ShowProperties();
	void OnActivate(wxListEvent &event);
	void OnEraseBackground(wxEraseEvent &event);
	void OnShipProperties(wxCommandEvent &event);
	void OnShipConfig(wxCommandEvent  &event);
	void OnShipData(wxCommandEvent  &event);
	void OnShipReport(wxCommandEvent  &event);
	void OnContextMenu(wxContextMenuEvent &event);
	void OnSelected(wxListEvent &event);
	void OnPaint(wxPaintEvent &event);
	void OnSetItem(wxCommandEvent &event);
	void OnColClick(wxListEvent& event);
	void OnShipShowTrack(wxCommandEvent  &event);
	long GetLastSelectedItem();
	//int Compare(SShip *g1, SShip *g2);
	void SetColumnImage(int col, int image);
		
	void Sort();
	
	wxString OnGetItemText(long item, long column) const;
	wxListItemAttr *OnGetItemAttr(long item) const;
	int OnGetItemImage(long item) const;

public:
	
	
	CListCtrl(wxWindow *Parent, CDisplayPlugin *DspPlugin, int type, long style);
	~CListCtrl();
		
	void SetList(wxArrayPtrVoid *ships);
	void SetSelection(SMarker *ship);
	void ClearList();
	void Insert();
	wxString GetItemValue(long item, long column);
	int GetSelectedColumn();
	bool GetSortOrder();
	
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_LIST = 1334,
		ID_SHIP_NAME,
		ID_SHIP_CONFIG,
		ID_SHIP_DATA,
		ID_SHIP_REPORT,
		ID_SHIP_REPORT_CONFIG,
		ID_SHIP_CHART,
		ID_SHIP_SHOW_TRACK
	};

};

class myCompareClass 
{
	CListCtrl *Parent;
  
public:
	
	myCompareClass(CListCtrl *parent);
	bool operator() (void *g1, void *g2); 
	//bool operator();

  
};


#endif