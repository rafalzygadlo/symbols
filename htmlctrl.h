#ifndef __HTMLCTRL
#define __HTMLCTRL

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "NaviBroker.h"
#include "display.h"
#include "frame.h"


class CHtmlCtrl: public wxListCtrl
{	

	wxArrayPtrVoid *m_List;
		
	void OnEraseBackground(wxEraseEvent &event);
	void OnSelect(wxCommandEvent &event);
	//virtual wxString OnGetItem(size_t item) const;
	virtual wxColour GetSelectedTextColour(const wxColour& colFg) const;
	//virtual wxColour GetSelectedTextBgColour(const wxColour& colBg) const;

	wxString OnGetItemText(long item, long column) const;
	//wxListItemAttr *OnGetItemAttr(long item) const;


public:
	
	CHtmlCtrl(wxWindow *Parent, int style );
	~CHtmlCtrl();
		
	void SetList(wxArrayPtrVoid *ptr);
	void ClearList();
	wxString GetItemValue(long item, long column);
	const char *GetSelectedColumn();
	bool GetSortOrder();
	void SetSelection(CSymbol *ptr);

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