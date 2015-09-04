#include "htmllist.h"
#include "conf.h"
#include "tools.h"
#include "info.h"
#include "options.h"
#include <wx/strconv.h>
#include <algorithm>
#include <wx/mstream.h>

DEFINE_EVENT_TYPE(EVT_SET_ITEM)

BEGIN_EVENT_TABLE(CHtmlList,wxHtmlListBox)
	//EVT_HTML_CELL_CLICKED(ID_HTML,OnCellClicked)
	EVT_LISTBOX(ID_HTML, OnSelect)
	EVT_COMMAND(ID_SET_ITEM,EVT_SET_ITEM,OnSetItem)
	EVT_HTML_LINK_CLICKED(ID_HTML, OnLinkClicked)
	EVT_CONTEXT_MENU(OnContextMenu)
END_EVENT_TABLE()

CHtmlList *HtmlListPtr = NULL;
CHtmlList::CHtmlList( wxWindow *Parent)
:wxHtmlListBox( Parent,ID_HTML,wxDefaultPosition,wxDefaultSize)
{
	//Plugin = DspPlugin;
	//SetDoubleBuffered(true);
	HtmlListPtr = this;
	m_MapPlugin = NULL;
	m_List = NULL;
	SetItemCount(0);
	SetMargins(10,10);
	//SetSelectionBackground(wxColor(200,200,200));
}

CHtmlList::~CHtmlList()
{

}

void CHtmlList::OnLinkClicked(wxHtmlLinkEvent &event)
{
	int id =  event.GetSelection();
	id = event.GetId();

	wxHtmlLinkInfo link = event.GetLinkInfo();

	long item;
	link.GetHref().ToLong(&item);
	
	CSymbol *Symbol = (CSymbol*)m_List->Item(item);
	Symbol->ShowGraph();
	
	//switch(action)
	//{
		//case 1: ShowGraph(Symbol); break;
	//}
}

void CHtmlList::OnSetItem(wxCommandEvent &event)
{
	SetItemCount(m_List->size());
	Refresh();
}

void CHtmlList::OnContextMenu(wxContextMenuEvent &event)
{
	//this->GetItemForCell()
	//this->getr
	
	int id = event.GetSelection();
	
	wxMenu *Menu = new wxMenu();
	
	Menu->Append(wxID_ANY,GetMsg(MSG_NEW));
	if(!db_check_right(MODULE_SYMBOL ,ACTION_NEW,_GetUID()))
		Menu->FindItem(wxID_ANY)->Enable(false);
			
	if(id > -1)
	{
		Menu->Append(wxID_ANY,GetMsg(MSG_EDIT));
		if(!db_check_right(MODULE_SYMBOL,ACTION_EDIT,_GetUID()))
			Menu->FindItem(wxID_ANY)->Enable(false);
		
		Menu->Append(wxID_ANY,GetMsg(MSG_DELETE));
		if(!db_check_right(MODULE_SYMBOL,ACTION_DELETE,_GetUID()))
			Menu->FindItem(wxID_ANY)->Enable(false);
	}
		
	PopupMenu(Menu);
	delete Menu;
}

void CHtmlList::ClearList()
{
	SetItemCount(0);
}

void CHtmlList::SetMapPlugin(CMapPlugin *v)
{
	m_MapPlugin = v;
}

void CHtmlList::SetList(wxArrayPtrVoid *ships)
{
	if(ships == NULL)
		return;

	m_List = ships;
	
	int count = m_List->size();

	//if(m_Count != count || GetSortChanged())
	//{
		
		m_Count = count;
		wxCommandEvent evt(EVT_SET_ITEM,ID_SET_ITEM);
		wxPostEvent(this,evt);
		Refresh();
	//}
		
	

}

void CHtmlList::_SetSelection(CSymbol *ptr)
{
	if(ptr == NULL || m_List == NULL)
		return;
		
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
			}
		}
	}
		
	Refresh();
}

void CHtmlList::OnSelect(wxCommandEvent &event)
{
	if(GetSelection() < 0)
		return;
	//if(GetMutex()->TryLock())
		//	return;
	
	int a = GetSelection();
	CSymbol *ptr = (CSymbol*)m_List->Item(GetSelection());
	m_MapPlugin->SetSelectedPtr(ptr);
	
}

void CHtmlList::OnDrawSeparator(wxDC& dc, wxRect& rect, size_t) const
{
	dc.SetPen(*wxBLACK_DASHED_PEN);
    dc.DrawLine(rect.x, rect.y, rect.GetRight(), rect.y);
    dc.DrawLine(rect.x, rect.GetBottom(), rect.GetRight(), rect.GetBottom());
}

void CHtmlList::OnDrawItem(wxDC& dc, wxRect& rect, size_t) const
{
	dc.DrawText(_("TEST"),10,10);

	//dc.DrawBitmap
}

wxString CHtmlList::OnGetItem(size_t item) const
{
	if(m_List->size() <= item)
		return wxEmptyString;

	CSymbol *ptr = (CSymbol*)m_List->Item(item);
	wxString str;
	
	for(int i = 0; i < ptr->GetAlarmCount();i++)
	{
		str << wxString::Format(_("<font size=4 color=red>%s</font><br>"),ptr->GetAlarmName(i));
	}
	
	str.Append(_("<table border=0 cellpadding=2 cellspacing=0 width=100%>"));
	if(ptr->GetIdSBMS() == 0)
		str.Append(wxString::Format(_("<tr><td><font color=red size=2>%s</font></td></tr>"),GetMsg(MSG_NO_SBMS)));	
	
	if(ptr->GetInMonitoring())
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td></tr>"),GetMsg(MSG_IN_MONITORING)));
	else
		str.Append(wxString::Format(_("<tr><td><font color=red><font size=2>%s</font></td></tr>"),GetMsg(MSG_NOT_IN_MONITORING)));	

	if(ptr->GetInMonitoring() & (ptr->GetIdSBMS() > 0))
	{
		
		if(ptr->GetLightOn())
		{
			nvRGBA rgba = GetColor(SYMBOL_LIGHT_ON_COLOR);
			str.Append(wxString::Format(_("<tr><td><font size=5 color='#%02X%02X%02X'><b>%s</b></font></td>"),rgba.R,rgba.G,rgba.B,GetLightOnAsString(ptr->GetLightOn())));
		}else{
			//nvRGBA rgba = GetColor(SYMBOL_NORMAL_COLOR);
			str.Append(wxString::Format(_("<tr><td><font size=5><b>%s</b></font></td>"),GetLightOnAsString(ptr->GetLightOn())));
		}

		//str.Append(_("<tr>"));
		str.Append(_("<td rowspan=3 align=right width=80>"));
		if(ptr->GetInputVolt() > GetUpperThreshold() || ptr->GetInputVolt() < GetLowerThreshold())
			str.Append(wxString::Format(_("<a href='%d'><font size=7 color=red>%4.2fV</font></a>"),item,ptr->GetInputVolt()));
		else
			str.Append(wxString::Format(_("<a href='%d'><font size=7>%4.2fV</font></a>"),item, ptr->GetInputVolt()));
		
		str.Append(_("</td>"));

		str.Append(wxString::Format(_("<tr><td><font size=3><b>%s</b></font></td></tr>"),GetAutoAsString(ptr->GetAuto())));

	}
	
	str << wxString::Format(_("<tr><td><font size=3><b>%s</b></font></td></tr>"),ptr->GetNumber());
	str << wxString::Format(_("<tr><td><font size=3>%s</font></td></tr>"),ptr->GetName());
	str << wxString::Format(_("<tr><td><font size=3>%s</font></td></tr>"),ptr->GetBaseStationName());
	str << wxString::Format(_("<tr><td><font size=3>%s</font></td></tr>"),ptr->GetAgeAsString());
	str.Append(_("</table>"));
	
	//str << wxString::Format(_("<a href='1'>%s</a><br>"),GetMsg(MSG_MANAGEMENT));
	//str << wxString::Format(_("<a href='2'>%s</a>"),GetMsg(MSG_GRAPH));
	
	//str << _("<table celpadding=2 border=1 cellspacing=0>");
	
		//str << wxString::Format(_("<tr><td><font size='4' color=red><b>ALARM</b></td></tr>"));
	
	//str << wxString::Format(_("<tr><td><font size='4'><b>%s</b></td></tr>"),ptr->GetName());
	//str <<_("</table>");
		
	//ptr->GetName(),ptr->GetNumber(),ptr->GetAgeAsString());

	//else
	
	//	str = wxString::Format(_("<table celpadding=4><td><font size='4'>%s</font></td></table>"),Ship->name,Ship->description);

	return str;

}
/*
wxString CHtmlList::OnGetItemMarkup(size_t  n) const
{
	CSymbol *ptr = (CSymbol*)m_List->Item(n);
	
	//wxString str = HtmlListPtr->geti
	//if(ptr->GetAlarmCount() > 0)
	return wxString::Format(_("ABCDEF"),ptr->GetAgeAsString());
}
*/
/*
wxColour CHtmlList::GetSelectedTextColour(const wxColour& colFg) const
{
    return wxColor(255,255,255);
}

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