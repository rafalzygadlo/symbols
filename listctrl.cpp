#include <wx/mstream.h>
#include "listctrl.h"
#include "conf.h"
#include "tools.h"
#include "images/up_sort.img"
#include "images/down_sort.img"
#include "db.h"
#include "db_actions.h"
#include "db_right.h"


DEFINE_EVENT_TYPE(EVT_SET_ITEM)

BEGIN_EVENT_TABLE(CListCtrl,wxListCtrl)
	EVT_LIST_ITEM_ACTIVATED(ID_LIST,CListCtrl::OnActivate)
	EVT_CONTEXT_MENU(CListCtrl::OnContextMenu)
	EVT_LIST_ITEM_SELECTED(ID_LIST,CListCtrl::OnSelected)
	EVT_LIST_COL_CLICK(ID_LIST,CListCtrl::OnColClick)
	EVT_MENU(ID_NEW,CListCtrl::OnNew)
	EVT_MENU(ID_EDIT,CListCtrl::OnEdit)
	EVT_MENU(ID_DELETE,CListCtrl::OnDelete)
//	EVT_LIST_ITEM_FOCUSED(ID_LIST,CListCtrl::OnFocused)
	
END_EVENT_TABLE()
 
CListCtrl::CListCtrl( wxWindow *Parent, int style )
:wxListCtrl( Parent, ID_LIST, wxDefaultPosition, wxDefaultSize, style )
{
	
	//SetBackgroundStyle(wxBG_STYLE_SYSTEM);
	//SetDoubleBuffered(true);
	m_FieldCount = 0;
	m_SelectedItem = -1;
	SetItemCount(0);
	m_Control = NULL;
	m_ColumnWithId = 0;
	
	m_ImageListSmall = new wxImageList(10, 10, true);

	wxMemoryInputStream in_1((const unsigned char*)up_sort,up_sort_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
    m_ImageListSmall->Add(myImage_1);

	wxMemoryInputStream in_2((const unsigned char*)down_sort,down_sort_size);
    wxImage myImage_2(in_2, wxBITMAP_TYPE_PNG);
    m_ImageListSmall->Add(myImage_2);
		
	SetImageList(m_ImageListSmall, wxIMAGE_LIST_SMALL);
	
}

CListCtrl::~CListCtrl()
{
	delete m_ImageListSmall;

	for(size_t i = 0; i < m_ColumnArray.size(); i++)
	{	
		wxArrayString *ptr = (wxArrayString*)m_ColumnArray.Item(i);
		ptr->Clear();
		delete ptr;
	}

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

void CListCtrl::SetControlType(int id, CDialog *control)
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

}

void CListCtrl::Select()
{
	EnsureVisible(m_SelectedItem);
	SetItemState( m_SelectedItem, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

void CListCtrl::Read(wxString query)
{
	if(!my_query(query))
		return;
	
	m_FieldCount = db_field_count();
	int rows = 0;
	void *result = db_result();
	char **row;
		

	while(row = (char**)db_fetch_row(result))
	{
		for(int i = 0; i < m_FieldCount; i++)
		{
			for(size_t j = 0; j < m_ColumnIds.size(); j++)
			{
				if(i == m_ColumnIds.Item(j))
				{
					wxArrayString *ptr = (wxArrayString*)m_ColumnArray.Item(j);
					wxString str(row[i],wxConvUTF8);
					ptr->Add(str);
				}
			}
		}
		
		rows++;
	}

	db_free_result(result);
	SetItemCount(rows);
}

void CListCtrl::OnContextMenu(wxContextMenuEvent &event)
{
		
	long n_item = -1;
	m_SelectedItem = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	
	wxMenu *_Menu = NULL;

	switch(m_ControlType)
	{	
		case CONTROL_AREA:				_Menu = Menu(m_SelectedItem,MODULE_AREA);				break;
		case CONTROL_SEAWAY:			_Menu = Menu(m_SelectedItem,MODULE_SEAWAY);				break;
		case CONTROL_LIGHT:				_Menu = Menu(m_SelectedItem,MODULE_LIGHT);				break;
		case CONTROL_BATTERY:			_Menu = Menu(m_SelectedItem,MODULE_BATTERY);			break;
		case CONTROL_COMMUNICATION:		_Menu = Menu(m_SelectedItem,MODULE_COMMUNICATION );		break;
		case CONTROL_FLASH:				_Menu = Menu(m_SelectedItem,MODULE_FLASH);				break;
		case CONTROL_BULB:				_Menu = Menu(m_SelectedItem,MODULE_BULB);				break;
		case CONTROL_SYMBOL_TYPE:		_Menu = Menu(m_SelectedItem,MODULE_SYMBOL_TYPE);		break;
		case CONTROL_LANTERN:			_Menu = Menu(m_SelectedItem,MODULE_LANTERN);			break;
		case CONTROL_CHANGER:			_Menu = Menu(m_SelectedItem,MODULE_CHANGER);			break;
		case CONTROL_SOLAR:				_Menu = Menu(m_SelectedItem,MODULE_SOLAR);				break;
		case CONTROL_REGULATOR:			_Menu = Menu(m_SelectedItem,MODULE_REGULATOR);			break;
		case CONTROL_AC_ADAPTER:		_Menu = Menu(m_SelectedItem,MODULE_AC_ADAPTER);			break;
		case CONTROL_SYNCHRONIZATION:	_Menu = Menu(m_SelectedItem,MODULE_SYNCHRONIZATION);	break;
		case CONTROL_TELEMETRY:			_Menu = Menu(m_SelectedItem,MODULE_TELEMETRY);			break;
		case CONTROL_COLLECTION:		_Menu = Menu(m_SelectedItem,MODULE_COLLECTION);			break;
		case CONTROL_ANTENNA:			_Menu = Menu(m_SelectedItem,MODULE_ANTENNA);			break;
		case CONTROL_LIGHTNING:			_Menu = Menu(m_SelectedItem,MODULE_LIGHTNING);			break;
		case CONTROL_WIND_GENERATOR:	_Menu = Menu(m_SelectedItem,MODULE_WIND_GENERATOR);		break;
		case CONTROL_NAUTOFON:			_Menu = Menu(m_SelectedItem,MODULE_NAUTOFON);			break;
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

void CListCtrl::OnSelected(wxListEvent &event)
{
	
	long n_item = -1;
	m_SelectedItem = GetNextItem(n_item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	wxArrayString row = GetRow(m_SelectedItem);	
	wxString id = row[m_ColumnWithId];
	wxString name = row[m_ColumnWithName];
	m_Control->OnSelect(id,name);

}


void CListCtrl::OnActivate(wxListEvent &event)
{

}

void CListCtrl::OnEdit(wxCommandEvent &event)
{
	m_Control->OnEdit(GetValue(GetColumn(m_ColumnWithId),m_SelectedItem));
}

void CListCtrl::OnNew(wxCommandEvent &event)
{
	m_Control->OnNew();
}

void CListCtrl::OnDelete(wxCommandEvent &event)
{
	m_Control->OnDelete(GetValue(GetColumn(m_ColumnWithId),m_SelectedItem));
}

wxArrayString *CListCtrl::GetColumn(int column)
{
	return (wxArrayString*)m_ColumnArray.Item(column);
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
	wxArrayString *ptr = (wxArrayString*)m_ColumnArray.Item(column);
	return ptr->Item(item);
}

/*
wxListItemAttr *CListCtrl::OnGetItemAttr(long item) const
{
	
	//if(Plugin->IsLoading())
		return NULL;
	
	//if(GetMutex()->TryLock())
//		return NULL;
	
	//if(CatalogGeometryGroup->Length() == 0 || CatalogGeometryGroup->Length() < item )
		//return NULL;
	
	//CNaviGeometry *Geometry = CatalogGeometryGroup->GetGeometry(item);
	
	 //je�eli geometria zainstalowana to sprawdz czy plik geometri istnieje 
	//CNaviGeometry *Installed = Plugin->IsInstalled(Geometry); 
	//GetMutex()->Unlock();
	
	//if(Installed != NULL)
	//{
		//if(!wxFileExists(Installed->GetAttributes()->GetValueAsString(GEOMETRY_ATTRIBUTE_9)))
			//return (wxListItemAttr *)&error;
	//}
		

//	if(Installed && Plugin->ChartCheckUpdate(Installed) != NULL)				// geometria potrzebuje update
		//return (wxListItemAttr *)&error;
	
	//if (last_selected_item == item && Installed)								// zainstalowana
		//return (wxListItemAttr *)&selected_and_installed;				
		
	if (last_selected_item == item)
		return (wxListItemAttr *)&selected;
		
	//if(Installed && Type == LIST_TYPE_ALL)
		//return (wxListItemAttr *)&installed;
		    

    return NULL;
}
*/

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
	//CNaviGeometry *Geometry = CatalogGeometryGroup->GetGeometry(item);
	//CNaviGeometry *Installed = Plugin->IsInstalled(Geometry);
	//if(Installed && column == 0)
	//{
		//if(!wxFileExists(Installed->GetAttributes()->GetValueAsString(GEOMETRY_ATTRIBUTE_9)))
			//return 0;
	//}
	
	return -1;
}
*/

int CListCtrl::OnGetItemImage(long item) const
{
	return -1;
}
