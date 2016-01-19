#ifndef __SYMBOLLIST
#define __SYMBOLLIST

#include <wx/wx.h>
#include <wx/htmllbox.h>
#include "NaviBroker.h"
#include "display.h"

class CMapPlugin;
class CSymbolList: public wxListCtrl
{	
	CMapPlugin *m_MapPlugin;
	int m_Count;
	wxArrayPtrVoid *m_List;
	long m_SelectedItem;
	CSymbol *m_Symbol;

	//void OnLinkClicked(wxHtmlLinkEvent &event);
	void OnSetItem(wxCommandEvent &event);
	void OnSelected(wxListEvent &event);
	void OnContextMenu(wxContextMenuEvent &event);
	void OnGraph(wxCommandEvent &event);
	void OnLightOn(wxCommandEvent &event);
	void OnLightOff(wxCommandEvent &event);
		
	wxString OnGetItemText(long item, long column) const;
	//virtual void OnDrawSeparator(wxDC& dc, wxRect& rect, size_t n) const;
	//virtual wxColour GetSelectedTextColour(const wxColour& colFg) const;
	//virtual void OnDrawItem(wxDC &dc, wxRect & 	rect,size_t n)	const;
	//virtual wxString OnGetItemMarkup(size_t  n) const; 
	//virtual wxColour GetSelectedTextBgColour(const wxColour& colBg) const;

public:
	
	CSymbolList(wxWindow *Parent, int style);
	~CSymbolList();
		
	void SetList(wxArrayPtrVoid *ptr);
	void ClearList();
	//wxString GetItemValue(long item, long column);
	//const char *GetSelectedColumn();
	bool GetSortOrder();
	void _SetSelection(CSymbol *ptr);
	void SetMapPlugin(CMapPlugin *v);
	

	DECLARE_EVENT_TABLE();

	enum
	{
		ID_LIST = 1500,
		ID_PROPERTIES,
		ID_SET_ITEM,
	
	};

};

#endif