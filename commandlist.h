#ifndef __COMMANDLIST
#define __COMMANDLIST

#include <wx/wx.h>
#include <wx/htmllbox.h>
#include "NaviBroker.h"
#include "display.h"
#include "dll.h"
#include "commandmodel.h"
#include "list.h"
#include "command.h"

class CMapPlugin;
class CCommand;
class CCommandModelList: public wxHtmlListBox
{
	CMapPlugin *m_MapPlugin;
	int m_Count;
	wxArrayPtrVoid *m_List;
	CCommand *m_Command;

	void OnLinkClicked(wxHtmlLinkEvent &event);
	void OnSetItem(wxCommandEvent &event);
	void OnSelect(wxCommandEvent &event);
	void OnContextMenu(wxContextMenuEvent &event);
	virtual wxString OnGetItem(size_t item) const;
	//virtual wxString OnGetItemMarkup(size_t  n) const;
	virtual void OnDrawSeparator(wxDC& dc, wxRect& rect, size_t n) const;
	
public:
	
	CCommandModelList(wxWindow *Parent);
	~CCommandModelList();
		
	void SetList(CList *v);
	void ClearList();
	//wxString GetItemValue(long item, long column);
	const char *GetSelectedColumn();
	bool GetSortOrder();
	void _SetSelection(CCommandModel *ptr);
	void SetMapPlugin(CMapPlugin *v);
	
	DECLARE_EVENT_TABLE();

	enum
	{
		ID_SET_ITEM,
		ID_HTML,
	};

};

#endif