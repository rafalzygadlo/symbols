#include <wx/mstream.h>
#include "listctrl.h"
#include "conf.h"
#include "tools.h"
#include "images/up_sort.img"
#include "images/down_sort.img"
#include "images/checkbox01.img"
#include "images/checkbox02.img"
#include "images/file.img"
#include "db.h"
//#include "db_actions.h"

DEFINE_EVENT_TYPE(EVT_SET_ITEM)

BEGIN_EVENT_TABLE(CListCtrl,wxListCtrl)
	EVT_LIST_ITEM_ACTIVATED(ID_LIST,OnActivate)
	EVT_CONTEXT_MENU(OnContextMenu)
	EVT_LIST_ITEM_SELECTED(ID_LIST,OnSelected)
	EVT_LIST_COL_CLICK(ID_LIST,OnColClick)
	EVT_MENU(ID_NEW,OnNew)
	EVT_MENU(ID_EDIT,OnEdit)
	EVT_MENU(ID_DELETE,OnDelete)
	EVT_MENU(ID_ADD_TO_GROUP,OnAddToGroup)
	//EVT_LEFT_DOWN(CListCtrl::OnMouseEvent)
//	EVT_LIST_ITEM_FOCUSED(ID_LIST,CListCtrl::OnFocused)
END_EVENT_TABLE()


CListCtrl::CListCtrl(void *db, wxWindow *Parent, int style)
:wxListCtrl( Parent, ID_LIST, wxDefaultPosition, wxDefaultSize, style )
{
	//SetBackgroundStyle(wxBG_STYLE_SYSTEM);
	//SetDoubleBuffered(true);
	m_Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
	m_ThisPtr = this;
	m_DB = db;
	m_ThisPtr = this;
	m_FieldCount = 0;
	m_SelectedItem = -1;
	SetItemCount(0);
	m_Control = NULL;
	m_ColumnWithId = 0;
	m_Count = 0;
	m_ListAttr = new wxListItemAttr();
	
	m_ImageListSmall = new wxImageList(16,16);
		
	wxMemoryInputStream in_1((const unsigned char*)up_sort,up_sort_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
    m_ImageListSmall->Add(myImage_1);

	wxMemoryInputStream in_2((const unsigned char*)down_sort,down_sort_size);
    wxImage myImage_2(in_2, wxBITMAP_TYPE_PNG);
    m_ImageListSmall->Add(myImage_2);
		
	wxMemoryInputStream in_3((const unsigned char*)checkbox01,checkbox01_size);
    wxImage myImage_3(in_3, wxBITMAP_TYPE_PNG);
    m_ImageListSmall->Add(myImage_3);

	wxMemoryInputStream in_4((const unsigned char*)checkbox02,checkbox02_size);
    wxImage myImage_4(in_4, wxBITMAP_TYPE_PNG);
    m_ImageListSmall->Add(myImage_4);

	wxMemoryInputStream in_5((const unsigned char*)file,file_size);
    wxImage myImage_5(in_5, wxBITMAP_TYPE_PNG);
    m_ImageListSmall->Add(myImage_5);

	 	
	SetImageList(m_ImageListSmall, wxIMAGE_LIST_SMALL);
	
	
}

CListCtrl::~CListCtrl()
{
	delete m_ImageListSmall;
	delete m_ListAttr;
	
	for(size_t i = 0; i < m_ColumnArray.size(); i++)
	{	
		wxArrayString *ptr = (wxArrayString*)m_ColumnArray.Item(i);
		ptr->Clear();
		delete ptr;
	}

	for(size_t i = 0; i < m_DataArray.size(); i++)
	{	
		wxArrayString *ptr = (wxArrayString*)m_DataArray.Item(i);
		ptr->Clear();
		delete ptr;
	}

}

void CListCtrl::SetList(wxArrayPtrVoid *ptr)
{
	m_List = ptr;
	int count = m_List->size();

	if(m_Count != count)
	{
		SetItemCount(count);
		Refresh();
	}
	
	m_Count = count;
}

void CListCtrl::SetSelection(CSymbol *ptr)
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


void CListCtrl::SetColumnWithId(int id)
{
	m_ColumnWithId = id;
}

void CListCtrl::SetColumnWithName(int id)
{
	m_ColumnWithName = id;
}

void CListCtrl::_AddColumn(int id,wxString field_name)
{
	m_ColumnIds.Add(id);
	m_ColumnFields.Add(field_name);
}

void CListCtrl::SetControlType(int id, CDialogPanel *control)
{
	m_ControlType = id;
	m_Control = control;
}

void CListCtrl::InitColumns()
{
	if(m_ColumnArray.size() == 0)
	{
		for(size_t i = 0; i < m_ColumnIds.size(); i++)
		{
			wxArrayString *Data = new wxArrayString();
			m_ColumnArray.Add(Data);
		}
	
	}
}

void CListCtrl::Clear()
{
	SetItemCount(0);
	for(size_t i = 0; i < m_ColumnArray.size(); i++)
	{
		wxArrayString *ptr = (wxArrayString*)m_ColumnArray.Item(i);
		ptr->Clear();
	}

	for(size_t i = 0; i < m_DataArray.size(); i++)
	{	
		wxArrayString *ptr = (wxArrayString*)m_DataArray.Item(i);
		ptr->Clear();
	}
	
	m_Ids.Clear();
}

void CListCtrl::Select()
{
	EnsureVisible(m_SelectedItem);
	SetItemState( m_SelectedItem, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

void CListCtrl::Read(wxString query)
{
	if(!my_query(m_DB,query))
		return;
	
	m_FieldCount = db_field_count(m_DB);
	int rows = 0;
	void *result = db_result(m_DB);
	char **row;
	
	if(result == NULL)
		return;

	for(int i = 0; i < m_FieldCount; i++)
	{
		wxArrayString *data = new wxArrayString();
		m_DataArray.Add(data);
	}
	
	while(row = (char**)db_fetch_row(result))
	{
		for(int i = 0; i < m_FieldCount; i++)
		{
			wxString str(row[i],wxConvUTF8);
		
			for(size_t j = 0; j < m_ColumnIds.size(); j++)
			{
				if(i == m_ColumnIds.Item(j))
				{
					wxArrayString *ptr = (wxArrayString*)m_ColumnArray.Item(j); //j
					ptr->Add(str);
				}
			}
						
			wxArrayString *ptr = (wxArrayString*)m_DataArray.Item(i); //j
			ptr->Add(str);

		}
		
		m_Ids.Add(atoi(row[m_ColumnWithId]));
		//m_Checked.Add(0);
		rows++;
	}

	db_free_result(result);
	SetItemCount(rows);
	Refresh();
}

void CListCtrl::OnContextMenu(wxContextMenuEvent &event)
{
		
	long n_item = -1;
	m_SelectedItem = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	
	wxMenu *_Menu = NULL;

	switch(m_ControlType)
	{	
		case CONTROL_SYMBOL:		_Menu = MenuSymbol(m_SelectedItem,MODULE_SYMBOL);				break;
		//case CONTROL_SYMBOL_ITEM:	_Menu = MenuSymbolItem(m_SelectedItem,MODULE_SYMBOL);			break;
		case CONTROL_ITEM:			_Menu = Menu(m_SelectedItem,MODULE_ITEM);						break;
		case CONTROL_AREA:			_Menu = Menu(m_SelectedItem,MODULE_AREA);						break;
		case CONTROL_SEAWAY:		_Menu = Menu(m_SelectedItem,MODULE_SEAWAY);						break;
		case CONTROL_SYMBOL_TYPE:	_Menu = Menu(m_SelectedItem,MODULE_SYMBOL_TYPE);				break;
		case CONTROL_PICTURE:		_Menu = Menu(m_SelectedItem,MODULE_PICTURE);					break;
		case CONTROL_SYMBOL_GROUP:	_Menu = Menu(m_SelectedItem,MODULE_SYMBOL_GROUP);				break;
		case CONTROL_BASE_STATION:	_Menu = MenuBaseStation(m_SelectedItem,MODULE_BASE_STATION);	break;
		case CONTROL_CHARACTERISTIC:_Menu = Menu(m_SelectedItem,MODULE_CHARACTERISTIC);				break;
		case CONTROL_SBMS:			_Menu = Menu(m_SelectedItem,MODULE_SBMS);						break;
	}
	
	if(_Menu)
	{
		PopupMenu(_Menu);
		delete _Menu;
	}

}

wxMenu *CListCtrl::Menu(int id, const char *module)
{
	wxMenu *Menu = new wxMenu();
	
	Menu->Append(ID_NEW,GetMsg(MSG_NEW));
	if(!db_check_right(module ,ACTION_NEW,_GetUID()))
		Menu->FindItem(ID_NEW)->Enable(false);
			
	if(id > -1)
	{
		Menu->Append(ID_EDIT,GetMsg(MSG_EDIT));
		if(!db_check_right(module,ACTION_EDIT,_GetUID()))
			Menu->FindItem(ID_EDIT)->Enable(false);
		
		Menu->Append(ID_DELETE,GetMsg(MSG_DELETE));
		if(!db_check_right(module,ACTION_DELETE,_GetUID()))
			Menu->FindItem(ID_DELETE)->Enable(false);
	}
		
	return Menu;
	
}

wxMenu *CListCtrl::MenuBaseStation(int id, const char *module)
{
	wxMenu *Menu = new wxMenu();
				
	if(id > -1)
	{
		Menu->Append(ID_EDIT,GetMsg(MSG_EDIT));
		if(!db_check_right(module,ACTION_EDIT,_GetUID()))
			Menu->FindItem(ID_EDIT)->Enable(false);
		
		Menu->Append(ID_DELETE,GetMsg(MSG_DELETE));
		if(!db_check_right(module,ACTION_DELETE,_GetUID()))
			Menu->FindItem(ID_DELETE)->Enable(false);
		
	}
		
	return Menu;
	
}

wxMenu *CListCtrl::MenuSymbol(int id, const char *module)
{
	wxMenu *Menu = new wxMenu();
	
	if(id > -1)
	{
		Menu->Append(ID_ADD_TO_GROUP,GetMsg(MSG_ADD_TO_GROUP));
		if(!db_check_right(module ,ACTION_ADD_TO_GROUP,_GetUID()))
		Menu->FindItem(ID_NEW)->Enable(false);

		Menu->AppendSeparator();
	}


	Menu->Append(ID_NEW,GetMsg(MSG_NEW));
	if(!db_check_right(module ,ACTION_NEW,_GetUID()))
		Menu->FindItem(ID_NEW)->Enable(false);
			
	if(id > -1)
	{
		Menu->Append(ID_EDIT,GetMsg(MSG_EDIT));
		if(!db_check_right(module,ACTION_EDIT,_GetUID()))
			Menu->FindItem(ID_EDIT)->Enable(false);
		
		Menu->Append(ID_DELETE,GetMsg(MSG_DELETE));
		if(!db_check_right(module,ACTION_DELETE,_GetUID()))
			Menu->FindItem(ID_DELETE)->Enable(false);
#if 0		
		Menu->AppendSeparator();
		Menu->Append(ID_PROPERTIES,GetMsg(MSG_PROPERTIES));
		if(!db_check_right(module,ACTION_PROPERTIES,_GetUID()))
			Menu->FindItem(ID_PROPERTIES)->Enable(false);
#endif
	}
		
	return Menu;
	
}

wxMenu *CListCtrl::MenuSymbolItem(int id, const char *module)
{
	wxMenu *Menu = new wxMenu();
	
	Menu->Append(ID_NEW,GetMsg(MSG_NEW));
	if(!db_check_right(module ,ACTION_NEW,_GetUID()))
		Menu->FindItem(ID_NEW)->Enable(false);
			
	if(id > -1)
	{
		Menu->Append(ID_DELETE,GetMsg(MSG_DELETE));
		if(!db_check_right(module,ACTION_DELETE,_GetUID()))
			Menu->FindItem(ID_DELETE)->Enable(false);
		
	}
		
	return Menu;
	
}

void CListCtrl::OnSelected(wxListEvent &event)
{
	long n_item = -1;
	m_SelectedItem = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	//wxArrayString row = GetRow(m_SelectedItem);	
	//long id;
	//row[m_ColumnWithId].ToLong(&id);
	//wxString name = row[m_ColumnWithName];
	int id = m_Ids.Item(m_SelectedItem);
	
	m_Control->OnSelect(id);

}


void CListCtrl::OnActivate(wxListEvent &event)
{

}

void CListCtrl::OnEdit(wxCommandEvent &event)
{
	//long id;
	//GetValue(_GetColumn(m_ColumnWithId),m_SelectedItem).ToLong(&id);
	int id = m_Ids.Item(m_SelectedItem);
	m_Control->OnEdit(id);
}

void CListCtrl::OnNew(wxCommandEvent &event)
{
	m_Control->OnNew();
}

void CListCtrl::OnDelete(wxCommandEvent &event)
{
	int id = m_Ids.Item(m_SelectedItem);
	m_Control->OnDelete(id);
}

void CListCtrl::OnAddToGroup(wxCommandEvent &event)
{
	int id = m_Ids.Item(m_SelectedItem);
	m_Control->OnAddToGroup(id);
}

wxArrayString *CListCtrl::_GetColumn(int column)
{
	return (wxArrayString*)m_ColumnArray.Item(column);
}

wxArrayString *CListCtrl::_GetDataColumn(int column)
{
	return (wxArrayString*)m_DataArray.Item(column);
}


wxArrayString CListCtrl::GetRow(int row)
{
	wxArrayString _row;
	
	for(size_t i = 0;  i < m_ColumnArray.size(); i++)
	{
		_row.Add(((wxArrayString*)m_ColumnArray.Item(i))->Item(row));
	}
	
	return _row;
}


wxString CListCtrl::GetValue(wxArrayString *ptr, int record)
{
	return ptr->Item(record);
}

wxString CListCtrl::OnGetItemText(long item, long column) const
{	
	if(column >= m_ColumnArray.size())
		return wxEmptyString;

	wxArrayString *ptr = (wxArrayString*)m_ColumnArray.Item(column);
	return ptr->Item(item);
}

 void CListCtrl::OnMouseEvent(wxMouseEvent& event)
 {

	 if (event.LeftDown())
	 {
		int flags;
		long item = HitTest(event.GetPosition(), flags);
		if (item > -1 && (flags & wxLIST_HITTEST_ONITEMICON))
		{
			long id;
			GetValue(_GetColumn(m_ColumnWithId),item).ToLong(&id);
			SetChecked(id, !IsChecked(item));
			Refresh();
		
		}else{
     	
			event.Skip();
		
		}
		      
	 }else{
         event.Skip();
     }
}
 
bool CListCtrl::IsChecked(long item)
{
	long id;
	GetValue(_GetColumn(m_ColumnWithId),item).ToLong(&id);
	for(size_t i = 0; i < m_Checked.size(); i++)
	{
		if(m_Checked.Item(i) == id)
			return true;
	}

	return false;
}
 
void CListCtrl::SetChecked(long id, bool checked)
{
	if(checked)
		m_Checked.Add(id);
	else
		m_Checked.Remove(id);
}


wxListItemAttr *CListCtrl::OnGetItemAttr(long item) const
{	
	switch(m_ControlType)
	{
		case CONTROL_SBMS:			m_ThisPtr->SetSBMSAttr(item,m_ListAttr); break;
		case CONTROL_SYMBOL:		m_ThisPtr->SetSymbolAttr(item,m_ListAttr); break;
		default: 
			return NULL;
	}
	
    return m_ListAttr;
}

void CListCtrl::SetSBMSAttr(long item, wxListItemAttr *v)
{
	wxString v1 = GetValue(_GetDataColumn(FI_SBMS_IN_USE),item);
	long _v;
	v1.ToLong(&_v);
	
	SetFontBold(_v);
	v->SetFont(m_Font);
}

void CListCtrl::SetSymbolAttr(long item, wxListItemAttr *v)
{
	wxString v1 = GetValue(_GetDataColumn(FI_SYMBOL_ID_SBMS),item);
	long _v;
	v1.ToLong(&_v);
	
	SetFontBold(_v);
	v->SetFont(m_Font);
}

void CListCtrl::SetFontBold(bool v)
{
	if(v)
		m_Font.SetWeight(wxFONTWEIGHT_NORMAL);
	else
		m_Font.SetWeight(wxFONTWEIGHT_BOLD);
}

int wxCALLBACK
MyCompareFunction(wxIntPtr item1, wxIntPtr item2, wxIntPtr WXUNUSED(sortData))
{
    // inverse the order
    if (item1 < item2)
        return 1;
    if (item1 > item2)
        return -1;

    return 0;
}

void CListCtrl::OnColClick(wxListEvent& event)
{
	static bool x = false;
    	
	static int col = -1;
	static int old_col;
	
	for(int i = 0; i < this->GetColumnCount(); i++)
	{
		SetColumnImage(i,-1);
	}
	
	col = event.GetColumn();
	
	if(old_col == col)
		x = !x;
	else
		x = false;

	SetColumnImage(col, x ? 0 : 1);
	
	old_col = col;
	m_Control->OnColumnCLick(m_ColumnFields.Item(col),x);


}

void CListCtrl::SetColumnImage(int col, int image)
{
    wxListItem item;
    item.SetMask(wxLIST_MASK_IMAGE);
    item.SetImage(image);
    SetColumn(col, item);
}

void CListCtrl::Sort()
{
//	CatalogGeometryGroup->First();	
//	std::vector<CNaviGeometry*> *it = (std::vector<CNaviGeometry*>*)CatalogGeometryGroup;
//	myCompareClass a(this);
//	std::sort(it->begin(),it->end(),a);
	Refresh();
}

/*
int CListCtrl::OnGetItemColumnImage(long item, long column) const
{
	
	if(column == 0)
	{
		if(m_ThisPtr->IsChecked(item))
			return 3;
		else
			return 2;
	}else{
	
		return -1;
	}
	
	return 1;
}
*/

int CListCtrl::OnGetItemImage(long item) const
{
	return -1;
}
