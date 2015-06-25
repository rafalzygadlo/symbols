#include "htmlctrl.h"
#include "conf.h"
#include "tools.h"
#include "info.h"
#include <wx/strconv.h>
#include <algorithm>
#include <wx/mstream.h>

DEFINE_EVENT_TYPE(EVT_SET_ITEM)

BEGIN_EVENT_TABLE(CHtmlCtrl,wxListCtrl)
	//EVT_ERASE_BACKGROUND(OnEraseBackground)
	//EVT_HTML_CELL_CLICKED(ID_HTML,OnCellClicked)
	//EVT_LISTBOX(ID_HTML, CHtmlCtrl::OnSelect)
END_EVENT_TABLE()

 
CHtmlCtrl::CHtmlCtrl(wxWindow *Parent, int style )
:wxListCtrl( Parent,ID_HTML,wxDefaultPosition,wxDefaultSize, style)
{
	//SetDoubleBuffered(true);
	SetItemCount(0);
	m_List = NULL;
}

CHtmlCtrl::~CHtmlCtrl()
{

}

void CHtmlCtrl::ClearList()
{
	SetItemCount(0);
}

void CHtmlCtrl::SetList(wxArrayPtrVoid *ptr)
{

	m_List = ptr;
	int count = m_List->size();

	SetItemCount(m_List->size());
	
	//GetMutex()->Unlock();

}

void CHtmlCtrl::OnSelect(wxCommandEvent &event)
{
	//if(GetSelection() < 0)
		//return;
		
	//int a = GetSelection();
	//SMarker *Ship = (SMarker*)ShipList->Item(GetSelection());
	//Plugin->SetSelectedShip(Ship);
	//GetMutex()->Unlock();
	
}

void CHtmlCtrl::OnEraseBackground(wxEraseEvent &event)
{
	// to prevent flickering, erase only content *outside* of the 
   // actual list items stuff

   if(GetItemCount() > 0) {
       wxDC * dc = event.GetDC();
       assert(dc);

       // get some info
       wxCoord width = 0, height = 0;
       GetClientSize(&width, &height);

       wxCoord x, y, w, h;
       dc->SetClippingRegion(0, 0, width, height);
       dc->GetClippingBox(&x, &y, &w, &h); 

       long top_item = GetTopItem();
       long bottom_item = top_item + GetCountPerPage();
       if(bottom_item >= GetItemCount()) {
           bottom_item = GetItemCount() - 1;
       }                

       // trick: we want to exclude a couple pixels
       // on the left side thus use wxLIST_RECT_LABEL
       // for the top rect and wxLIST_RECT_BOUNDS for bottom
       // rect
       wxRect top_rect, bottom_rect;
       GetItemRect(top_item, top_rect, wxLIST_RECT_LABEL);
       GetItemRect(bottom_item, bottom_rect, wxLIST_RECT_BOUNDS);

       // set the new clipping region and do erasing
       wxRect items_rect(top_rect.GetLeftTop(), bottom_rect.GetBottomRight());
       wxRegion reg(wxRegion(x, y, w, h)); 
       reg.Subtract(items_rect);
       dc->DestroyClippingRegion();
       dc->SetClippingRegion(reg);

       // do erasing
       dc->SetBackground(wxBrush(GetBackgroundColour(), wxSOLID));
       dc->Clear();

       // restore old clipping region
       dc->DestroyClippingRegion();
       dc->SetClippingRegion(wxRegion(x, y, w, h));
   } else {
       event.Skip();
  
  }
  
}




wxString CHtmlCtrl::OnGetItemText(long item, long column) const
{
		
	if(m_List->size() <= item)
		return wxEmptyString;
		
	CSymbol *ptr = (CSymbol*)m_List->Item(item);
	wxString str;
		
	switch(column)
	{
		case COLUMN_NUMBER:			str = ptr->GetNumber();		break;
		case COLUMN_NAME:			str = ptr->GetName();		break;
	}
	
	return str;

}


wxColour CHtmlCtrl::GetSelectedTextColour(const wxColour& colFg) const
{
    return wxColor(0,0,0);
}

void CHtmlCtrl::SetSelection(CSymbol *ptr)
{
	if(ptr == NULL)
	{
		//this->SetS (-1);
		return;
	}
	
	if(this->GetItemCount() != m_List->size())
		return;
	
	for(size_t i = 0; i < m_List->size();i++)
	{ 
		CSymbol *Symbol = (CSymbol*)m_List->Item(i);
		if(Symbol != NULL)
		{
		
			if(Symbol == ptr)
			{
				EnsureVisible(i);
				SetItemState(i,wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
				//Refresh();
				
			}else{
				SetItemState(i,0, wxLIST_STATE_SELECTED| wxLIST_STATE_SELECTED);

			}
		}
	}
		
	Refresh();
}
