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

	CAlarm *Alarm = (CAlarm*)m_List->Item(item);

	switch(action)
	{
		case HREF_ACTION_ALARM_DELETE:	DeactivateAlarm(Alarm->GetId());	break;
		
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
		
	m_Count = count;
	wxCommandEvent evt(EVT_SET_ITEM,ID_SET_ITEM);
	wxPostEvent(this,evt);
	Refresh();
	
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
	
	CAlarm *ptr = (CAlarm*)m_List->Item(GetSelection());
	ConfirmAlarm(ptr->GetId());
}

void CAlarmList::OnDrawSeparator(wxDC& dc, wxRect& rect, size_t) const
{
	dc.SetPen(*wxGREY_PEN);
	dc.DrawLine(rect.x, rect.y, rect.GetRight(), rect.y);
    dc.DrawLine(rect.x, rect.GetBottom(), rect.GetRight(), rect.GetBottom());
}

wxString CAlarmList::OnGetItem(size_t item) const
{
	if(m_List->size() <= item)
		return wxEmptyString;

	CAlarm *ptr = (CAlarm*)m_List->Item(item);
	wxString str;
		
	str.Append(_("<table border=0 cellpadding=2 cellspacing=0 width=100%>"));
	int fsize = 0;
	if(ptr->GetConfirmed())
		fsize = 3;
	else
		fsize = 6;
	
	str << wxString::Format(_("<tr><td><font size=%d><b>%s</b></font></td></tr>"),fsize,ptr->GetSymbolName());
	nvRGBA c = GetAlarmTypeColor(ptr->GetType());
	str << wxString::Format(_("<tr><td><font color=#%02X%02X%02X size=4>%s</font></td></tr>"),c.R,c.G,c.B,ptr->GetName());
	str << wxString::Format(_("<tr><td><font size=%d><b>%s</b></font></td></tr>"),fsize,ptr->GetAlarmOnDate());
	str << wxString::Format(_("<tr><td><font size=%d><b>%s %s</b></font></td></tr>"),fsize,ptr->GetUserFirstName(),ptr->GetUserLastName());
	
	if(GetSelection() == item)
		str << wxString::Format(_("<tr><td><a target=0 href='%d'>%s</a></td></tr>"),item,GetMsg(MSG_DELETE));
	
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