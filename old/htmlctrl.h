#ifndef __HTMLCTRL
#define __HTMLCTRL

#include <wx/wx.h>
#include <wx/htmllbox.h>
#include "NaviBroker.h"
#include "display.h"
#include "frame.h"

class CDisplayPlugin;
class CHtmlCtrl: public wxHtmlListBox
{	

	CDisplayPlugin *Plugin;
	wxArrayPtrVoid *ShipList;
		
	void OnSelect(wxCommandEvent &event);
	virtual wxString OnGetItem(size_t item) const;
	virtual wxColour GetSelectedTextColour(const wxColour& colFg) const;
	//virtual wxColour GetSelectedTextBgColour(const wxColour& colBg) const;

public:
	
	CHtmlCtrl(wxWindow *Parent, CDisplayPlugin *DspPlugin);
	~CHtmlCtrl();
		
	void SetList(wxArrayPtrVoid *ships);
	void ClearList();
	wxString GetItemValue(long item, long column);
	const char *GetSelectedColumn();
	bool GetSortOrder();
	void _SetSelection(SMarker *ship);

	DECLARE_EVENT_TABLE();

	enum
	{
		ID_LIST,
		ID_PROPERTIES,
		ID_DELETE_FROM_QUEUE,
		ID_DELETE_FROM_INSTALLED,
		ID_SET_ITEM,
		ID_HTML,
	};

};

#endif