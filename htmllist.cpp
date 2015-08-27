#include "htmllist.h"
#include "conf.h"
#include "tools.h"
#include "info.h"
#include <wx/strconv.h>
#include <algorithm>
#include <wx/mstream.h>

DEFINE_EVENT_TYPE(EVT_SET_ITEM)

BEGIN_EVENT_TABLE(CHtmlList,wxHtmlListBox)
	//EVT_HTML_CELL_CLICKED(ID_HTML,OnCellClicked)
	EVT_LISTBOX(ID_HTML, OnSelect)
END_EVENT_TABLE()

 
CHtmlList::CHtmlList( wxWindow *Parent,CDisplayPlugin *DspPlugin )
:wxHtmlListBox( Parent,ID_HTML,wxDefaultPosition,wxDefaultSize)
{
	//Plugin = DspPlugin;
	//SetDoubleBuffered(true);
	m_List = NULL;
	SetSelectionBackground(wxColor(200,200,200));
}

CHtmlList::~CHtmlList()
{

}

void CHtmlList::ClearList()
{
	SetItemCount(0);
}

void CHtmlList::SetList(wxArrayPtrVoid *ships)
{
	if(ships == NULL)
		return;

	m_List = ships;
	GetMutex()->Lock();
	SetItemCount(ships->size());
	GetMutex()->Unlock();
	Refresh();
	//wxMutexGuiLeave();

}

void CHtmlList::_SetSelection(CSymbol *ptr)
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
				this->SetSelection(i);
				//EnsureVisible(i);
				//SetItemState(i,wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
				//Refresh();
				
			//}else{
				//SetItemState(i,0, wxLIST_STATE_SELECTED| wxLIST_STATE_SELECTED);

			}
		}
	}
		
	Refresh();
}

void CHtmlList::OnSelect(wxCommandEvent &event)
{
	//if(GetSelection() < 0)
		//return;
	//if(GetMutex()->TryLock())
		//	return;
	
	//int a = GetSelection();
	//SMarker *Ship = (SMarker*)ShipList->Item(GetSelection());
	//Plugin->SetSelectedShip(Ship);
	//GetMutex()->Unlock();
	
}

void CHtmlList::OnDrawSeparator(wxDC& dc, wxRect& rect, size_t) const
{
    //if ( ((MyFrame *)GetParent())->
      //      GetMenuBar()->IsChecked(HtmlLbox_DrawSeparator) )
    //{
        dc.SetPen(*wxBLACK_DASHED_PEN);
        dc.DrawLine(rect.x, rect.y, rect.GetRight(), rect.y);
        dc.DrawLine(rect.x, rect.GetBottom(), rect.GetRight(), rect.GetBottom());
    //}
}
wxString CHtmlList::OnGetItem(size_t item) const
{
			
	if(m_List->size() <= item)
		return wxEmptyString;

	GetMutex()->Lock();

	CSymbol *ptr = (CSymbol*)m_List->Item(item);
	wxString str;
	
	//double to_x, to_y;
	//Plugin->GetBroker()->Project(Ship->x,Ship->y,&to_x,&to_y);
	
	//if(Plugin->GetS ShipIsSelected(Ship))
	str << wxString::Format(_("<h2>%s</h2>"),ptr->GetNumber());
	str << _("<table celpadding=4 border=1 cellspacing=0>");
	if(ptr->GetAlarmCount() > 0)
		str << wxString::Format(_("<tr><td><font size='4' color=red><b>ALARM</b></td></tr>"));
	
	str << wxString::Format(_("<tr><td><font size='4'><b>%s</b></td></tr>"),ptr->GetName());

	str <<_("</table>");
		
		//ptr->GetName(),ptr->GetNumber(),ptr->GetAgeAsString());

	//else
	
	//	str = wxString::Format(_("<table celpadding=4><td><font size='4'>%s</font></td></table>"),Ship->name,Ship->description);

	GetMutex()->Unlock();

	return str;

}


wxColour CHtmlList::GetSelectedTextColour(const wxColour& colFg) const
{
    return wxColor(0,0,0);
}
/*
void CHtmlList::_SetSelection(SMarker *ship)
{
	if(ship == NULL)
	{
		this->SetSelection(-1);
		return;
	}
	
	if(this->GetItemCount() != ShipList->size())
		return;
	
	//SetItemCount(ShipList->size());
	for(size_t i = 0; i < ShipList->size();i++)
	{ 
		SMarker *Ship = (SMarker*)ShipList->Item(i);
		if(Ship != NULL)
		{
		
			if(Ship == ship)
			{
				this->SetSelection(i);
				//this->
				Refresh();
				return;
			}
		}
	}
		
	Refresh();
}
*/