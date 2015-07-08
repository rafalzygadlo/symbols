#include "htmlctrl.h"
#include "conf.h"
#include "tools.h"
#include "info.h"
#include "options.h"
#include <wx/strconv.h>
#include <algorithm>
#include <wx/mstream.h>

extern unsigned int	up_sort_size;
extern unsigned char up_sort[]; 

extern unsigned int	down_sort_size;
extern unsigned char down_sort[]; 


DEFINE_EVENT_TYPE(EVT_SET_ITEM)

BEGIN_EVENT_TABLE(CHtmlCtrl,wxListCtrl)
	//EVT_ERASE_BACKGROUND(OnEraseBackground)
	//EVT_HTML_CELL_CLICKED(ID_HTML,OnCellClicked)
	//EVT_LISTBOX(ID_HTML, CHtmlCtrl::OnSelect)
	EVT_LIST_COL_CLICK(ID_HTML,CHtmlCtrl::OnColClick)
END_EVENT_TABLE()

 
CHtmlCtrl::CHtmlCtrl(wxWindow *Parent, int style )
:wxListCtrl( Parent,ID_HTML,wxDefaultPosition,wxDefaultSize, style)
{
	m_ImageListSmall = new wxImageList(16,16);
		
	wxMemoryInputStream in_1((const unsigned char*)up_sort,up_sort_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
    m_ImageListSmall->Add(myImage_1);

	wxMemoryInputStream in_2((const unsigned char*)down_sort,down_sort_size);
    wxImage myImage_2(in_2, wxBITMAP_TYPE_PNG);
    m_ImageListSmall->Add(myImage_2);
	
	SetImageList(m_ImageListSmall, wxIMAGE_LIST_SMALL);
	SetItemCount(0);
	m_List = NULL;
	m_Count = 0;

	
}

CHtmlCtrl::~CHtmlCtrl()
{
	delete m_ImageListSmall;
}

void CHtmlCtrl::ClearList()
{
	SetItemCount(0);
}

void CHtmlCtrl::SetList(wxArrayPtrVoid *ptr)
{
	m_List = ptr;
	int count = m_List->size();

	if(m_Count != count || GetSortChanged())
	{
		SetItemCount(count);
		Refresh();
	}
	
	m_Count = count;
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
	/*
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
  */
  
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

void CHtmlCtrl::SetSelection(CSymbol *ptr)
{
	if(ptr == NULL || m_List == NULL)
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

void CHtmlCtrl::OnColClick(wxListEvent& event)
{
	
	static bool x = GetSortOrder();
    	
	int col = -1;
	
	if(event.GetColumn() == 0)
	{
		SetColumnImage(0, x ? 0 : 1);
		SetColumnImage(1,-1);
		col = 0;
		x = !x;
		SetSortColumn(FN_SYMBOL_NUMBER);
	}
		
	if(event.GetColumn() == 1)
	{
		SetColumnImage(0,-1);
		SetColumnImage(1, x ? 0 : 1);
		col = 1;
		x = !x;		
		SetSortColumn(FN_SYMBOL_NAME);
	}
	
	
	SetSortColumnId(col);
	SetSortChanged(true);
	SetSortOrder(x);
	
}

void CHtmlCtrl::SetColumnImage(int col, int image)
{
    wxListItem item;
    item.SetMask(wxLIST_MASK_IMAGE);
    item.SetImage(image);
    SetColumn(col, item);
}

int CHtmlCtrl::OnGetItemImage(long item) const
{
	return -1;
}


void CHtmlCtrl::Sort()
{
	myCompareClass a(this);
	std::sort(m_List->begin(),m_List->end(),a);
	Refresh();
}

myCompareClass::myCompareClass(CHtmlCtrl *parent) 
{
	Parent = parent;
}
  
bool myCompareClass::operator() (void *g1, void *g2) 
{ 
	int a = 0; 
	
	CSymbol *c1 = (CSymbol*)g1;
	CSymbol *c2 = (CSymbol*)g2;

	if(GetSortColumnId() == 0)
	{
		//a = c1->GetNumber().Cmp(c2->Gember());
		a = wcscmp(c1->GetNumber().wc_str(wxConvUTF8), c2->GetNumber().wc_str(wxConvUTF8));
		
		fprintf(stderr,"%Ls %Ls\n",c1->GetNumber().wc_str(),c2->GetNumber().wc_str());
	}

	if(GetSortColumnId() == 1)
	{
		a = wcscmp(c1->GetName().wc_str(wxConvUTF8), c2->GetName().wc_str(wxConvUTF8));
		
	}

	 if(GetSortOrder())
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

  


/*
const char *CHtmlCtrl::GetSelectedColumn()
{
	return SelectedColumn;
}
*/
