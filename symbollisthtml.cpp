#include "symbollisthtml.h"
#include "conf.h"
#include "tools.h"
#include "info.h"
#include "options.h"
#include "control.h"
#include <wx/strconv.h>
#include <algorithm>
#include <wx/mstream.h>

DEFINE_EVENT_TYPE(EVT_SET_ITEM)

BEGIN_EVENT_TABLE(CSymbolListHtml,wxHtmlListBox)
	//EVT_HTML_CELL_CLICKED(ID_HTML,OnCellClicked)
	EVT_LISTBOX(ID_HTML, OnSelect)
	EVT_COMMAND(ID_SET_ITEM,EVT_SET_ITEM,OnSetItem)
	EVT_HTML_LINK_CLICKED(ID_HTML, OnLinkClicked)	
END_EVENT_TABLE()

CSymbolListHtml *HtmlListPtr = NULL;
CSymbolListHtml::CSymbolListHtml( wxWindow *Parent)
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

CSymbolListHtml::~CSymbolListHtml()
{

}

void CSymbolListHtml::OnLinkClicked(wxHtmlLinkEvent &event)
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
		case HREF_ACTION_GRAPH:			ShowGraph(Symbol);			break;
		case HREF_ACTION_MANAGEMENT:	ShowManagement(Symbol);		break;
	}

}

void CSymbolListHtml::ShowGraph(CSymbol *v)
{
	for(int i = 0; i < v->GetDriverCount();i++)
	{
		CDriver *Driver = v->GetDriver(i);
		Driver->ShowGraph();
	}
	
}

void CSymbolListHtml::ShowManagement(CSymbol *v)
{
	for(int i = 0; i < v->GetDriverCount();i++)
	{
		CDriver *Driver = v->GetDriver(i);
		Driver->ShowAction();
	}
	//v->ShowManagement(v);
}


void CSymbolListHtml::OnSetItem(wxCommandEvent &event)
{
	SetItemCount(m_List->size());
	Refresh();
}

void CSymbolListHtml::ClearList()
{
	SetItemCount(0);
}

void CSymbolListHtml::SetMapPlugin(CMapPlugin *v)
{
	m_MapPlugin = v;
}

void CSymbolListHtml::SetList(wxArrayPtrVoid *ptr)
{
	if(ptr == NULL)
		return;

	m_List = ptr;
	
	int count = m_List->size();
	m_Count = count;
	wxCommandEvent evt(EVT_SET_ITEM,ID_SET_ITEM);
	wxPostEvent(this,evt);
	Refresh();
}

void CSymbolListHtml::_SetSelection(CSymbol *ptr)
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

void CSymbolListHtml::OnSelect(wxCommandEvent &event)
{

	RefreshAll();
	if(GetSelection() < 0)
		return;
	
	int a = GetSelection();
	CSymbol *ptr = (CSymbol*)m_List->Item(GetSelection());
	m_MapPlugin->SetSelectedPtr(ptr);

}

void CSymbolListHtml::OnDrawSeparator(wxDC& dc, wxRect& rect, size_t) const
{
	dc.SetPen(*wxGREY_PEN);
	dc.DrawLine(rect.x, rect.y, rect.GetRight(), rect.y);
    dc.DrawLine(rect.x, rect.GetBottom(), rect.GetRight(), rect.GetBottom());
}

wxString CSymbolListHtml::OnGetItem(size_t item) const
{
	if(m_List->size() <= item)
		return wxEmptyString;

	wxString str;
	CSymbol *ptr = (CSymbol*)m_List->Item(item);
	str = ptr->GetHtml(item);
	
	for(int i = 0; i < ptr->GetDriverCount();i++)
	{
		CDriver *Driver = ptr->GetDriver(i);
		str << Driver->GetDriverHtml(item);
	}

	
	return str;

}
