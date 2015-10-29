#ifndef __COMMANDLIST
#define __COMMANDLIST

#include <wx/wx.h>
#include <wx/htmllbox.h>
#include "NaviBroker.h"
#include "display.h"
#include "dll.h"

class CMapPlugin;
class CCommandList: public wxHtmlListBox
{
	CMapPlugin *m_MapPlugin;
	int m_Count;
	wxArrayPtrVoid *m_List;
	void OnLinkClicked(wxHtmlLinkEvent &event);
	void OnSetItem(wxCommandEvent &event);
	void OnSelect(wxCommandEvent &event);
	void OnContextMenu(wxContextMenuEvent &event);
	
	virtual wxString OnGetItem(size_t item) const;
	virtual void OnDrawSeparator(wxDC& dc, wxRect& rect, size_t n) const;
	
public:
	
	CCommandList(wxWindow *Parent);
	~CCommandList();
		
	void SetList(wxArrayPtrVoid *v);
	void ClearList();
	//wxString GetItemValue(long item, long column);
	const char *GetSelectedColumn();
	bool GetSortOrder();
	void _SetSelection(CAlarm *ptr);
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