#ifndef __HTMLLIST
#define __HTMLLIST

#include <wx/wx.h>
#include <wx/htmllbox.h>
#include "NaviBroker.h"
#include "display.h"
//#include "frame.h"

class CMapPlugin;
class CHtmlList: public wxHtmlListBox
{	
	CMapPlugin *m_MapPlugin;
	int m_Count;
	wxArrayPtrVoid *m_List;
	void OnLinkClicked(wxHtmlLinkEvent &event);
	void OnSetItem(wxCommandEvent &event);
	void OnSelect(wxCommandEvent &event);
	void OnContextMenu(wxContextMenuEvent &event);
	void ShowManagement(CSymbol *v);
	void ShowGraph(CSymbol *v);
	
	virtual wxString OnGetItem(size_t item) const;
	virtual void OnDrawSeparator(wxDC& dc, wxRect& rect, size_t n) const;
	//virtual wxColour GetSelectedTextColour(const wxColour& colFg) const;
	//virtual void OnDrawItem(wxDC &dc, wxRect & 	rect,size_t n)	const;
	//virtual wxString OnGetItemMarkup(size_t  n) const; 
	//virtual wxColour GetSelectedTextBgColour(const wxColour& colBg) const;

public:
	
	CHtmlList(wxWindow *Parent);
	~CHtmlList();
		
	void SetList(wxArrayPtrVoid *ships);
	void ClearList();
	//wxString GetItemValue(long item, long column);
	const char *GetSelectedColumn();
	bool GetSortOrder();
	void _SetSelection(CSymbol *ptr);
	void SetMapPlugin(CMapPlugin *v);
	

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