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
	SetMargins(5,5);
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

	CGroupModel *ptr = (CGroupModel*)m_List->Item(item);

	CCommand *Command = new CCommand();

	switch(action)
	{
		case HREF_ACTION_LIGHT_ON:			Command->SetGroupCommand(COMMAND_LIGHT_ON, ptr->GetCode(),ptr->GetId(),true);				break;
		case HREF_ACTION_LIGHT_OFF:			Command->SetGroupCommand(COMMAND_LIGHT_OFF, ptr->GetCode(),ptr->GetId(),false);				break;
		case HREF_ACTION_AUTO_MANAGEMENT:	Command->SetGroupCommand(COMMAND_AUTO_MANAGEMENT, ptr->GetCode(),ptr->GetId(),false);		break;
	}

	delete Command;

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

void CGroupList::SetList(CList *v)
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

void CGroupList::_SetSelection(CAlarmModel *ptr)
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
		CAlarmModel *Alarm = (CAlarmModel*)m_List->Item(i);
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
	
	//CAlarm *ptr = (CAlarm*)m_List->Item(GetSelection());
	//ConfirmAlarm(ptr->GetId());
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

	CGroupModel *ptr = (CGroupModel*)m_List->Item(item);
	wxString str;
		
	str.Append(_("<table border=0 cellpadding=0 cellspacing=1 width=100%>"));
	int fsize = 3;
		
	str << wxString::Format(_("<tr><td><font size=%d><b>%s (%d)</b></font></td></tr>"),fsize,ptr->GetName(),ptr->GetItemCount());
			
	if((GetSelection() == item) && (ptr->GetItemCount() > 0))
	{
		str << wxString::Format(_("<tr><td><a target=%d href='%d'>%s</a></td></tr>"),HREF_ACTION_LIGHT_ON,item,GetMsg(MSG_LIGHT_ON));
		str << wxString::Format(_("<tr><td><a target=%d href='%d'>%s</a></td></tr>"),HREF_ACTION_LIGHT_OFF,item,GetMsg(MSG_LIGHT_OFF));
		str << wxString::Format(_("<tr><td><a target=%d href='%d'>%s</a></td></tr>"),HREF_ACTION_AUTO_MANAGEMENT,item,GetMsg(MSG_AUTO_MANAGEMENT));	
	}

	str.Append(_("</table>"));
	
	return str;

}
