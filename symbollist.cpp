#include "symbollist.h"
#include "conf.h"
#include "tools.h"
#include "info.h"
#include "options.h"
#include "control.h"
#include <wx/strconv.h>
#include <algorithm>
#include <wx/mstream.h>

DEFINE_EVENT_TYPE(EVT_SET_ITEM)

BEGIN_EVENT_TABLE(CSymbolList,wxListCtrl)
	//EVT_HTML_CELL_CLICKED(ID_HTML,OnCellClicked)
	EVT_LIST_ITEM_SELECTED(ID_LIST,OnSelected)
	EVT_COMMAND(ID_SET_ITEM,EVT_SET_ITEM,OnSetItem)
	EVT_CONTEXT_MENU(OnContextMenu)
	EVT_MENU(ID_GRAPH,OnGraph)
	EVT_MENU(ID_LIGHT_ON,OnLightOn)
	EVT_MENU(ID_LIGHT_OFF,OnLightOff)
END_EVENT_TABLE()

CSymbolList *HtmlListPtr = NULL;
CSymbolList::CSymbolList( wxWindow *Parent, int style)
:wxListCtrl( Parent,ID_LIST,wxDefaultPosition,wxDefaultSize,style)
{
	//Plugin = DspPlugin;
	//SetDoubleBuffered(true);
	HtmlListPtr = this;
	m_MapPlugin = NULL;
	m_List = NULL;
	SetItemCount(0);
		
}

CSymbolList::~CSymbolList()
{

}

void CSymbolList::OnSetItem(wxCommandEvent &event)
{
	SetItemCount(m_List->size());
	//Refresh();
}

void CSymbolList::OnSelected(wxListEvent &event)
{
	long n_item = -1;
	m_SelectedItem = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	m_Symbol = (CSymbol*)m_List->Item(m_SelectedItem);
	m_MapPlugin->SetSelectedPtr(m_Symbol);
}

void CSymbolList::OnContextMenu(wxContextMenuEvent &event)
{
	
	long n_item = -1;
	m_SelectedItem = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		
	m_Symbol = (CSymbol*)m_List->Item(m_SelectedItem);
		
	CMenu *Menu = new CMenu();
	
	for(int i = 0; i < m_Symbol->GetDriverCount(); i++)
	{
		CDriver *Driver = m_Symbol->GetDriver(i);
		Menu->SetTitle(Driver->GetName());
		Menu->Append(ID_GRAPH,GetMsg(MSG_GRAPH));
		Menu->AppendSeparator();
		Menu->Append(ID_LIGHT_ON,GetMsg(MSG_LIGHT_ON));
		Menu->Append(ID_LIGHT_OFF,GetMsg(MSG_LIGHT_OFF));
		Menu->Append(ID_AUTO,GetMsg(MSG_AUTO_MANAGEMENT));
		Menu->Append(ID_TIME,GetMsg(MSG_GET_TIME));
		Menu->Append(ID_UPTIME,GetMsg(MSG_GET_UPTIME));
		Menu->Append(ID_RESET,GetMsg(MSG_RESET));
	}
		
	PopupMenu(Menu);
	delete Menu;
}

void CSymbolList::OnGraph(wxCommandEvent &event)
{
	m_Symbol->ShowGraph();
}

void CSymbolList::OnLightOn(wxCommandEvent &event)
{
	m_Symbol->LightOn();
}

void CSymbolList::OnLightOff(wxCommandEvent &event)
{
	m_Symbol->LightOff();
}

void CSymbolList::ClearList()
{
	SetItemCount(0);
}

void CSymbolList::SetMapPlugin(CMapPlugin *v)
{
	m_MapPlugin = v;
}

void CSymbolList::SetList(wxArrayPtrVoid *ptr)
{
	if(ptr == NULL)
		return;

	m_List = ptr;
	
	int count = m_List->size();
	m_Count = count;
	wxCommandEvent evt(EVT_SET_ITEM,ID_SET_ITEM);
	wxPostEvent(this,evt);
	//Refresh();
}

void CSymbolList::_SetSelection(CSymbol *ptr)
{
	if(ptr == NULL || m_List == NULL)
	{
		Refresh();
		//this->SetSelection(-1);
		//this->
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

				SetItemState(i,wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED, wxLIST_STATE_SELECTED | wxLIST_STATE_FOCUSED);
				EnsureVisible(i);
				Refresh();
				//this->SetSelection(i);
			}
		}
	}
		
	//Refresh();
}

wxString CSymbolList::OnGetItemText(long item, long column) const
{
	if(m_List->size() <= item)
		return wxEmptyString;

	wxString str;
	CSymbol *ptr = (CSymbol*)m_List->Item(item);
	
	wxString input_volt;
	
	for(int i = 0; i < ptr->GetDriverCount();i++)
	{
		CDriver *Driver = ptr->GetDriver(i);
		input_volt << wxString::Format(_("%4.2f"),Driver->GetInputVolt());
	}
		
	switch(column)
	{
		case 0: return input_volt;
		case 1: return ptr->GetName();	
		case 2: return ptr->GetNumber();
	}

	return wxEmptyString;
}
