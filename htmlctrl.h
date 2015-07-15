#ifndef __HTMLCTRL
#define __HTMLCTRL

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "NaviBroker.h"
#include "display.h"
#include "frame.h"


class CHtmlCtrl: public wxListCtrl
{	
	wxImageList *m_ImageListSmall;
	wxArrayPtrVoid *m_List;
	int m_Count;
	bool m_Order;
		
	void OnEraseBackground(wxEraseEvent &event);
	void OnSelect(wxCommandEvent &event);
	void OnColClick(wxListEvent& event);
	void OnContextMenu(wxContextMenuEvent &event);
	void OnManagement(wxCommandEvent &event);
	//virtual wxString OnGetItem(size_t item) const;
	wxString OnGetItemText(long item, long column) const;
	//wxListItemAttr *OnGetItemAttr(long item) const;
	int OnGetItemImage(long item) const;
	void Sort();

public:
	
	CHtmlCtrl(wxWindow *Parent, int style );
	~CHtmlCtrl();
		
	void SetList(wxArrayPtrVoid *ptr);
	void ClearList();
	wxString GetItemValue(long item, long column);
	const char *GetSelectedColumn();
	void SetSelection(CSymbol *ptr);
	void SetColumnImage(int col, int image);

	DECLARE_EVENT_TABLE();

	enum
	{
		ID_LIST = 1700,
		ID_HTML,
		ID_MANAGEMENT,
	};


};


class myCompareClass 
{
	CHtmlCtrl *Parent;
  
public:
	
	myCompareClass(CHtmlCtrl *parent);
	bool operator() (void *g1, void *g2); 
	  
};



#endif