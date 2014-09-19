#include "listctrl.h"
#include "conf.h"
#include "tools.h"
#include "info.h"
#include <wx/strconv.h>
#include <algorithm>
#include <wx/mstream.h>

DEFINE_EVENT_TYPE(EVT_SET_ITEM)

BEGIN_EVENT_TABLE(CListCtrl,wxListCtrl)
	EVT_LIST_ITEM_ACTIVATED(ID_LIST,CListCtrl::OnActivate)
	EVT_CONTEXT_MENU(CListCtrl::OnContextMenu)
	EVT_MENU(ID_SHIP_CONFIG ,CListCtrl::OnShipConfig)
	EVT_MENU(ID_SHIP_DATA ,CListCtrl::OnShipData)
	EVT_MENU(ID_SHIP_REPORT,CListCtrl::OnShipReport)
	EVT_MENU(ID_SHIP_SHOW_TRACK,CListCtrl::OnShipShowTrack)

	EVT_LIST_ITEM_SELECTED(ID_LIST,CListCtrl::OnSelected)
	EVT_LIST_ITEM_ACTIVATED(ID_LIST,CListCtrl::OnActivate)
	EVT_PAINT(CListCtrl::OnPaint)
	//EVT_COMMAND(ID_SET_ITEM,EVT_SET_ITEM,CListCtrl::OnSetItem)
	EVT_LIST_COL_CLICK(ID_LIST,CListCtrl::OnColClick)
END_EVENT_TABLE()


CListCtrl::CListCtrl( wxWindow *Parent,CDisplayPlugin *DspPlugin, int type, long style )
:wxListCtrl( Parent,ID_LIST,wxDefaultPosition,wxDefaultSize, style )
{
	ThisPtr = this;
	Menu = NULL;
	Plugin = DspPlugin;
		
	selected.SetTextColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));
	selected.SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
		
	deselected.SetTextColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	deselected.SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));

	SetDoubleBuffered(true);
	Type = type;
	ImageListSmall = new wxImageList(24, 24, true);
	
	//this->SetImageList(ImageListSmall,1);
	//wxMemoryInputStream in_1((const unsigned char*)ship,ship_size);
    //wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
    //ImageListSmall->Add(myImage_1);

	//wxMemoryInputStream in_2((const unsigned char*)down_sort,down_sort_size);
    //wxImage myImage_2(in_2, wxBITMAP_TYPE_PNG);
    //ImageListSmall->Add(myImage_2);

}

CListCtrl::~CListCtrl()
{
	delete ImageListSmall;
}

void CListCtrl::OnEraseBackground(wxEraseEvent &event)
{

}

void CListCtrl::OnPaint(wxPaintEvent &event)
{
	event.Skip();
}

void CListCtrl::OnSetItem(wxCommandEvent &event)
{
	int i = event.GetInt();
	wxString str = event.GetString();
		
	long item = InsertItem(i,str);
	SetItemPtrData(item,(wxUIntPtr)event.GetClientData());
}

void CListCtrl::OnContextMenu(wxContextMenuEvent &event)
{
	MenuAll();
}

void CListCtrl::MenuAll()
{
		
	long n_item = -1;
	n_item = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if(n_item == -1)
		return;
	SMarker *Ship = (SMarker*)ShipList->Item(n_item);
	wxMenu *Menu = new wxMenu(Ship->name);
	
//	Menu->AppendCheckItem(ID_SHIP_SHOW_TRACK,GetMsg(MSG_SHOW_SHIP_TRACK));
	//Menu->Check(ID_SHIP_SHOW_TRACK,Ship->GetShowTrack());
	Menu->AppendSeparator();
//	Menu->Append(ID_SHIP_REPORT,GetMsg(MSG_GET_SHIP_REPORT));
//	Menu->Append(ID_SHIP_CHART,GetMsg(MSG_GET_SHIP_CHART));
	//Menu->Append(ID_SHIP_TRACK,GetMsg(MSG_GET_SHIP_TRACK));
	Menu->AppendSeparator();
//	Menu->Append(ID_SHIP_NAME,GetMsg(MSG_SET_SHIP_NAME));
//	Menu->Append(ID_SHIP_CONFIG,GetMsg(MSG_SET_SHIP_CONFIG));
//	Menu->Append(ID_SHIP_DATA,GetMsg(MSG_SET_SHIP_DATA_DEFINITION));
	
		
	PopupMenu(Menu);
	
	delete Menu;
	
}

void CListCtrl::OnShipData(wxCommandEvent  &event)
{
	long n_item = -1;
	n_item = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	SMarker *Ship = (SMarker*)ShipList->Item(n_item);
	Plugin->ShipData(Ship);	
}


void CListCtrl::OnShipReport(wxCommandEvent  &event)
{
	long n_item = -1;
	n_item = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	SMarker *Ship = (SMarker*)ShipList->Item(n_item);
	Plugin->ShipReport(Ship);	
}

void CListCtrl::OnShipConfig(wxCommandEvent  &event)
{
	long n_item = -1;
	n_item = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	SMarker *Ship = (SMarker*)ShipList->Item(n_item);
	Plugin->ShipConfig(Ship);	
}

void CListCtrl::OnShipShowTrack(wxCommandEvent  &event)
{
	long n_item = -1;
	n_item = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	SMarker *Ship = (SMarker*)ShipList->Item(n_item);
	//Ship->SetShowTrack(event.IsChecked());

}

void CListCtrl::OnSelected(wxListEvent &event)
{
	
	long n_item = -1;
	for(;;)
	{
		n_item = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);

        if (n_item < 0)	break;
		
		if(GetMutex()->TryLock())
			return;
		
		SMarker *Ship = (SMarker*)ShipList->Item(n_item);
		Plugin->SetSelectedShip(Ship);
		GetMutex()->Unlock();
	}
	
		
}

void CListCtrl::OnActivate(wxListEvent &event)
{
	long n_item = -1;
	n_item = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	//CNaviGeometry *Geometry = CatalogGeometryGroup->GetGeometry(n_item);
	
//	Plugin->ShowProperties(Geometry);
}

void CListCtrl::ClearList()
{
	SetItemCount(0);
}


void CListCtrl::SetList(wxArrayPtrVoid *ships)
{	
	if(ships == NULL)
		return;
	
	ShipList = ships;
	SetItemCount(ships->size());
		
	
}

void CListCtrl::SetSelection(SMarker *ship)
{
	
	for(size_t i = 0; i < ShipList->size(); i++)
	{
		SMarker *Ship = (SMarker*)ShipList->Item(i);
		
		if(Ship == ship)
		{
			EnsureVisible(i);
			break;
		}
	}
	

	Refresh();
	return;
}

wxString CListCtrl::OnGetItemText(long item, long column) const
{
	if(ShipList->size() <= item)
	{
		GetMutex()->Unlock();
		return wxEmptyString;
	}
	
	SMarker *Ship = (SMarker*)ShipList->Item(item);
	wxString str;
		
	switch (column)
	{
		case 0:	str = wxString::Format(_("%s"),Ship->name);		break;
		case 1:	str = wxString::Format(_("%4.2f"),Ship->x);		break;
		case 2:	str = wxString::Format(_("%4.2f"),Ship->y);		break;
		
	}
	
	return str;
}

wxListItemAttr *CListCtrl::OnGetItemAttr(long item) const
{
	
	SMarker *ship = (SMarker*)ShipList->Item(item);
	if(Plugin->ShipIsSelected(ship))
		return (wxListItemAttr *)&selected;
	else
		return (wxListItemAttr *)&deselected;
			
    return NULL;
}

void CListCtrl::OnColClick(wxListEvent& event)
{
	
	static bool x = false;
    x = !x;

	for(size_t i = 0; i < GetColumnCount(); i++)
	{
		int col = event.GetColumn();
		
		//if(event.GetColumn() == i)
			//SetColumnImage(i, x ? 0 : 1);
		//else
			//SetColumnImage(i, -1 );
	}			
	
	Order = x;
	SelectedColumn = event.GetColumn();
	Sort();

}

void CListCtrl::SetColumnImage(int col, int image)
{
    wxListItem item;
    item.SetMask(wxLIST_MASK_IMAGE);
    item.SetImage(image);
    SetColumn(col, item);
}

bool CListCtrl::GetSortOrder()
{
	return Order;
}

int CListCtrl::GetSelectedColumn()
{
	return SelectedColumn;
}


void CListCtrl::Sort()
{
	myCompareClass a(this);
	std::sort(ShipList->begin(),ShipList->end(),a);
	Refresh();
}

int CListCtrl::OnGetItemImage(long item) const
{
	return 0;
}

 myCompareClass::myCompareClass(CListCtrl *parent) 
{
	Parent = parent;
}
  
bool myCompareClass::operator() (void *g1, void *g2) 
{ 
	int a = 0;
	
	switch(Parent->GetSelectedColumn())
	{
		//case 0:	 a = ((CShip*)g1)->GetId() - ((CShip*)g2)->GetId();				break;
		//case 1:	 a = wcscmp(((CShip*)g1)->GetName(), ((CShip*)g2)->GetName());	break;
		//case 2:	 a = wcscmp(((CShip*)g1)->date, ((SShip*)g2)->date);	break;
	}	
	
	if(Parent->GetSortOrder())
	{
		if(a < 0)
			return true;
		else
			return false;
	 
	}else{
	 	
		if(a > 0)
			return true;
		else
			return false;
	 }


}

  
