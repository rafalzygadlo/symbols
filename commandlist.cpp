#include <wx/strconv.h>
#include <algorithm>
#include <wx/mstream.h>
#include "commandlist.h"
#include "conf.h"
#include "tools.h"
#include "info.h"
#include "options.h"

DEFINE_EVENT_TYPE(EVT_SET_ITEM)

BEGIN_EVENT_TABLE(CCommandList,wxHtmlListBox)
	//EVT_HTML_CELL_CLICKED(ID_HTML,OnCellClicked)
	EVT_LISTBOX(ID_HTML, OnSelect)
	EVT_COMMAND(ID_SET_ITEM,EVT_SET_ITEM,OnSetItem)
	EVT_HTML_LINK_CLICKED(ID_HTML, OnLinkClicked)
	EVT_CONTEXT_MENU(OnContextMenu)
END_EVENT_TABLE()

CCommandList *HtmlListPtr = NULL;
CCommandList::CCommandList( wxWindow *Parent)
:wxHtmlListBox( Parent,ID_HTML,wxDefaultPosition,wxDefaultSize)
{
	//Plugin = DspPlugin;
	//SetDoubleBuffered(true);
	HtmlListPtr = this;
	m_MapPlugin = NULL;
	m_List = NULL;
	SetItemCount(0);
	SetMargins(5,5);
	//SetSelectionBackground(wxColor(200,200,200));
}

CCommandList::~CCommandList()
{

}

void CCommandList::OnLinkClicked(wxHtmlLinkEvent &event)
{
	int id =  event.GetSelection();
	id = event.GetId();

	wxHtmlLinkInfo link = event.GetLinkInfo();

	long item;
	link.GetHref().ToLong(&item);
	
	wxString t = link.GetTarget();

	long action = -1;
	t.ToLong(&action);

	CCommand *ptr = (CCommand*)m_List->Item(item);

	switch(action)
	{
		case HREF_ACTION_DELETE:	DeactivateCommand(ptr->GetId(),ptr->GetDriverType());	break;
		
	}

}

void CCommandList::OnSetItem(wxCommandEvent &event)
{
	SetItemCount(m_List->size());
	Refresh();
}

void CCommandList::OnContextMenu(wxContextMenuEvent &event)
{
	
}

void CCommandList::ClearList()
{
	SetItemCount(0);
}

void CCommandList::SetMapPlugin(CMapPlugin *v)
{
	m_MapPlugin = v;
}

void CCommandList::SetList(CList *v)
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

void CCommandList::_SetSelection(CCommand *ptr)
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
		CCommand *_ptr = (CCommand*)m_List->Item(i);
		if(_ptr != NULL)
		{
			if(_ptr == ptr)
			{
				this->SetSelection(i);
			}
		}
	}
		
	Refresh();
}

void CCommandList::OnSelect(wxCommandEvent &event)
{
	RefreshAll();
	if(GetSelection() < 0)
		return;
	
	int a = GetSelection();
	
	//CAlarm *ptr = (CAlarm*)m_List->Item(GetSelection());
	//ConfirmAlarm(ptr->GetId());
}

void CCommandList::OnDrawSeparator(wxDC& dc, wxRect& rect, size_t) const
{
	dc.SetPen(*wxGREY_PEN);
	dc.DrawLine(rect.x, rect.y, rect.GetRight(), rect.y);
    dc.DrawLine(rect.x, rect.GetBottom(), rect.GetRight(), rect.GetBottom());
}

wxString CCommandList::OnGetItem(size_t item) const
{
	if(m_List->size() <= item)
		return wxEmptyString;

	CCommand *ptr = (CCommand*)m_List->Item(item);
	wxString str;
	
	str.Append(_("<table border=0 cellpadding=0 cellspacing=1 width=100%>"));
	
	if(ptr->GetStatus() == COMMAND_STATUS_NEW)
		str << wxString::Format(_("<tr><td><b>%s</b></font></td></tr>"),ptr->GetSymbolName());
	else
		str << wxString::Format(_("<tr><td>%s</font></td></tr>"),ptr->GetSymbolName());
		
	str << wxString::Format(_("<tr><td>%s</font></td></tr>"),ptr->GetName());
	str << wxString::Format(_("<tr><td>%s</font></td></tr>"),ptr->GetStatusText());
	//str << wxString::Format(_("<tr><td><b>%s</b></font></td></tr>"),ptr->GetAlarmOnDate());
	str << wxString::Format(_("<tr><td>%s %s</font></td></tr>"),ptr->GetUserFirstName(),ptr->GetUserLastName());
	
	if(GetSelection() == item)
		str << wxString::Format(_("<tr><td><a target=%d href='%d'>%s</a></td></tr>"),HREF_ACTION_DELETE,item,GetMsg(MSG_DELETE));
	
	str.Append(_("</table>"));
	
	return str;

}
/*
wxString CCommandList::OnGetItemMarkup(size_t  n) const
{
	CCommand *ptr = (CCommand*)m_List->Item(n);
	
	//wxString str = HtmlListPtr->geti
	//if(ptr->GetAlarmCount() > 0)
	return wxString::Format(_("ABCDEF"),ptr->GetStatus());
}

wxColour CHtmlList::GetSelectedTextColour(const wxColour& colFg) const
{
    return wxColor(255,255,255);
}

*/