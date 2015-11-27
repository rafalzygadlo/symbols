#include <wx/strconv.h>
#include <algorithm>
#include <wx/mstream.h>
#include "grouplist.h"
#include "conf.h"
#include "tools.h"
#include "info.h"
#include "options.h"

DEFINE_EVENT_TYPE(EVT_SET_ITEM)

BEGIN_EVENT_TABLE(CGroupList,wxHtmlListBox)
	//EVT_HTML_CELL_CLICKED(ID_HTML,OnCellClicked)
	EVT_LISTBOX(ID_HTML, OnSelect)
	EVT_COMMAND(ID_SET_ITEM,EVT_SET_ITEM,OnSetItem)
	EVT_HTML_LINK_CLICKED(ID_HTML, OnLinkClicked)
	EVT_CONTEXT_MENU(OnContextMenu)
END_EVENT_TABLE()

CGroupList *HtmlListPtr = NULL;
CGroupList::CGroupList( wxWindow *Parent)
:wxHtmlListBox( Parent,ID_HTML,wxDefaultPosition,wxDefaultSize)
{
	HtmlListPtr = this;
	m_MapPlugin = NULL;
	m_List = NULL;
	SetItemCount(0);
	SetMargins(10,10);
}

CGroupList::~CGroupList()
{

}

void CGroupList::OnLinkClicked(wxHtmlLinkEvent &event)
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
		case HREF_ACTION_DELETE:	DeactivateAlarm(Alarm->GetId());	break;
	}

}

void CGroupList::OnSetItem(wxCommandEvent &event)
{
	SetItemCount(m_List->size());
	Refresh();
}

void CGroupList::OnContextMenu(wxContextMenuEvent &event)
{
	
}

void CGroupList::ClearList()
{
	SetItemCount(0);
}

void CGroupList::SetMapPlugin(CMapPlugin *v)
{
	m_MapPlugin = v;
}

void CGroupList::SetList(wxArrayPtrVoid *v)
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

void CGroupList::_SetSelection(CAlarm *ptr)
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

void CGroupList::OnSelect(wxCommandEvent &event)
{
	RefreshAll();
	if(GetSelection() < 0)
		return;
	
	int a = GetSelection();
	
	CAlarm *ptr = (CAlarm*)m_List->Item(GetSelection());
	ConfirmAlarm(ptr->GetId());
}

void CGroupList::OnDrawSeparator(wxDC& dc, wxRect& rect, size_t) const
{
	dc.SetPen(*wxGREY_PEN);
	dc.DrawLine(rect.x, rect.y, rect.GetRight(), rect.y);
    dc.DrawLine(rect.x, rect.GetBottom(), rect.GetRight(), rect.GetBottom());
}

wxString CGroupList::OnGetItem(size_t item) const
{
	if(m_List->size() <= item)
		return wxEmptyString;

	CGroup *ptr = (CGroup*)m_List->Item(item);
	wxString str;
		
	str.Append(_("<table border=0 cellpadding=2 cellspacing=0 width=100%>"));
	int fsize = 5;
		
	str << wxString::Format(_("<tr><td><font size=%d><b>%s</b></font></td></tr>"),fsize,ptr->GetName());
	
	//str << wxString::Format(_("<tr><td><font size=%d><b>%s %s</b></font></td></tr>"),fsize,ptr->GetUserFirstName(),ptr->GetUserLastName());
	
	if(GetSelection() == item)
	{
		str << wxString::Format(_("<tr><td><a target=%d href='%d'>%s</a></td></tr>"),HREF_ACTION_DELETE,item,GetMsg(MSG_LIGHT_ON));
		str << wxString::Format(_("<tr><td><a target=%d href='%d'>%s</a></td></tr>"),HREF_ACTION_DELETE,item,GetMsg(MSG_LIGHT_OFF));
	}

	str.Append(_("</table>"));
	
	return str;

}
