#include <wx/strconv.h>
#include <algorithm>
#include <wx/mstream.h>
#include "alarmlist.h"
#include "conf.h"
#include "tools.h"
#include "info.h"
#include "options.h"

DEFINE_EVENT_TYPE(EVT_SET_ITEM)

BEGIN_EVENT_TABLE(CAlarmList,wxHtmlListBox)
	//EVT_HTML_CELL_CLICKED(ID_HTML,OnCellClicked)
	EVT_LISTBOX(ID_HTML, OnSelect)
	EVT_COMMAND(ID_SET_ITEM,EVT_SET_ITEM,OnSetItem)
	EVT_HTML_LINK_CLICKED(ID_HTML, OnLinkClicked)
	EVT_CONTEXT_MENU(OnContextMenu)
END_EVENT_TABLE()

CAlarmList *HtmlListPtr = NULL;
CAlarmList::CAlarmList( wxWindow *Parent)
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

CAlarmList::~CAlarmList()
{

}

void CAlarmList::OnLinkClicked(wxHtmlLinkEvent &event)
{
	int id =  event.GetSelection();
	id = event.GetId();

	wxHtmlLinkInfo link = event.GetLinkInfo();

	long item;
	link.GetHref().ToLong(&item);
	
	wxString t = link.GetTarget();

	long action = -1;
	t.ToLong(&action);

	CSymbol *Symbol = (CSymbol*)m_List->Item(item);

	switch(action)
	{
//		case HREF_ACTION_GRAPH:			ShowGraph(Symbol);			break;
		//case HREF_ACTION_MANAGEMENT:	ShowManagement(Symbol);		break;
		break;
	}

}

void CAlarmList::OnSetItem(wxCommandEvent &event)
{
	SetItemCount(m_List->size());
	Refresh();
}

void CAlarmList::OnContextMenu(wxContextMenuEvent &event)
{
	
}

void CAlarmList::ClearList()
{
	SetItemCount(0);
}

void CAlarmList::SetMapPlugin(CMapPlugin *v)
{
	m_MapPlugin = v;
}

void CAlarmList::SetList(wxArrayPtrVoid *v)
{
	if(v == NULL)
		return;

	m_List = v;
	
	int count = m_List->size();

	//if(m_Count != count || GetSortChanged())
	//{
		
		m_Count = count;
		wxCommandEvent evt(EVT_SET_ITEM,ID_SET_ITEM);
		wxPostEvent(this,evt);
		Refresh();
	//}
		
	

}

void CAlarmList::_SetSelection(CAlarm *ptr)
{
	if(ptr == NULL || m_List == NULL)
	{
		Refresh();
		this->SetSelection(-1);
		return;
	}
			
	if(this->GetItemCount() != m_List->size())
		return;
	
	for(size_t i = 0; i < m_List->size();i++)
	{ 
		CAlarm *Alarm = (CAlarm*)m_List->Item(i);
		if(Alarm != NULL)
		{
			if(Alarm == ptr)
			{
				this->SetSelection(i);
			}
		}
	}
		
	Refresh();
}

void CAlarmList::OnSelect(wxCommandEvent &event)
{
	RefreshAll();
	if(GetSelection() < 0)
		return;
	
	int a = GetSelection();
	CSymbol *ptr = (CSymbol*)m_List->Item(GetSelection());
	m_MapPlugin->SetSelectedPtr(ptr);

}

void CAlarmList::OnDrawSeparator(wxDC& dc, wxRect& rect, size_t) const
{
	dc.SetPen(*wxBLACK_DASHED_PEN);
    dc.DrawLine(rect.x, rect.y, rect.GetRight(), rect.y);
    dc.DrawLine(rect.x, rect.GetBottom(), rect.GetRight(), rect.GetBottom());
}

void CAlarmList::OnDrawItem(wxDC& dc, wxRect& rect, size_t) const
{
	//dc.DrawText(_("TEST"),10,10);

	//dc.DrawBitmap
}

wxString CAlarmList::OnGetItem(size_t item) const
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
		if(GetSelection() == item)
		{
			if(db_check_right(MODULE_SYMBOL,ACTION_MANAGEMENT,_GetUID()))
				str << wxString::Format(_("<hr><a target=1 href='%d'>%s</a><hr>"),item,GetMsg(MSG_MANAGEMENT));
		}
		
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
			str.Append(wxString::Format(_("<a target=0 href='%d'><font size=7 color=red>%4.2fV</font></a>"),item,ptr->GetInputVolt()));
		else
			str.Append(wxString::Format(_("<a target=0 href='%d'><font size=7>%4.2fV</font></a>"),item, ptr->GetInputVolt()));
		
		str.Append(_("</td>"));

		str.Append(wxString::Format(_("<tr><td><font size=3><b>%s</b></font></td></tr>"),GetAutoAsString(ptr->GetAuto())));

	}
	
	str << wxString::Format(_("<tr><td><font size=3><b>%s</b></font></td></tr>"),ptr->GetNumber());
	str << wxString::Format(_("<tr><td><font size=3>%s</font></td></tr>"),ptr->GetName());
	str << wxString::Format(_("<tr><td><font size=3>%s</font></td></tr>"),ptr->GetBaseStationName());
	str << wxString::Format(_("<tr><td><font size=3>%s</font></td></tr>"),ptr->GetAgeAsString());
	str << wxString::Format(_("<tr><td><font size=3>%s</font></td></tr>"),ptr->GetChargingAsString());
	str.Append(_("</table>"));


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