#include "dialog.h"
#include "conf.h"
#include "tools.h"
#include "listctrl.h"
#include "new.h"
#include "db.h"


SHeader Header[] =
{
	{CONTROL_LIGHT, 80,	{FI_LIGHT_ID , FN_LIGHT_ID, MSG_ID} },
	{CONTROL_LIGHT,100,	{FI_LIGHT_NAME , FN_LIGHT_NAME, MSG_NAME} },
	{CONTROL_LIGHT,250,	{FI_LIGHT_INFO , FN_LIGHT_INFO, MSG_INFO} },

	{CONTROL_ITEM, 80, {FI_ITEM_ID , FN_ITEM_ID, MSG_ID} },
	{CONTROL_ITEM,120, {FI_ITEM_NAME , FN_ITEM_NAME, MSG_NAME} },
	{CONTROL_ITEM,100, {FI_ITEM_TYPE , FN_ITEM_TYPE, MSG_TYPE} },
	{CONTROL_ITEM,250, {FI_ITEM_INFO , FN_ITEM_INFO, MSG_INFO} },
	
	{CONTROL_AREA, 80, {FI_AREA_ID ,	FN_AREA_ID, MSG_ID} },
	{CONTROL_AREA,100, {FI_AREA_NAME , FN_AREA_NAME, MSG_NAME} },
	{CONTROL_AREA,250, {FI_AREA_INFO , FN_AREA_INFO, MSG_INFO} },

	{CONTROL_SEAWAY, 80, {FI_SEAWAY_ID , FN_SEAWAY_ID, MSG_ID} },
	{CONTROL_SEAWAY,100, {FI_SEAWAY_NAME , FN_SEAWAY_NAME, MSG_NAME} },
	{CONTROL_SEAWAY,250, {FI_SEAWAY_INFO , FN_SEAWAY_INFO, MSG_INFO} },

	{CONTROL_SYMBOL_TYPE, 80, {FI_SYMBOL_TYPE_ID , FN_SYMBOL_TYPE_ID, MSG_ID} },
	{CONTROL_SYMBOL_TYPE,100, {FI_SYMBOL_TYPE_NAME , FN_SYMBOL_TYPE_NAME, MSG_NAME} },
	{CONTROL_SYMBOL_TYPE,250, {FI_SYMBOL_TYPE_INFO , FN_SYMBOL_TYPE_INFO, MSG_INFO} },
	
	{CONTROL_LIGHT_ITEM,80, {FI_ITEM_ID  , FN_ITEM_ID, MSG_ID} },
	{CONTROL_LIGHT_ITEM,100, {FI_ITEM_NAME + 1 , FN_ITEM_TYPE, MSG_NAME} },
	{CONTROL_LIGHT_ITEM,100, {FI_ITEM_TYPE + 1, FN_ITEM_TYPE, MSG_TYPE} },
	
	{-1},

};

SIds Id[] =
{
	{CONTROL_LIGHT, COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_LIGHT},
	{CONTROL_ITEM, COLUMN_ITEM_WITH_ID, COLUMN_ITEM_WITH_NAME,MSG_ITEMS},
	{CONTROL_AREA, COLUMN_WITH_ID, COLUMN_WITH_NAME, MSG_AREA},
	{CONTROL_SEAWAY, COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_SEAWAY},
	{CONTROL_SYMBOL_TYPE, COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_SYMBOL_TYPE},
	{CONTROL_LIGHT_ITEM,COLUMN_WITH_ID, COLUMN_WITH_NAME,MSG_LIGHT_ITEM},
	{-1},

};

CDialog::CDialog(int control_type, bool picker)
:wxDialog(NULL,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	m_ButtonOk = NULL;
	m_Picker = picker;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
	
	SetSize(DEFAULT_DIALOG_WIDTH,DEFAULT_DIALOG_HEIGHT);
	m_DialogPanel = new CDialogPanel(control_type,this);
	Sizer->Add(m_DialogPanel,1,wxALL|wxEXPAND,0);
		
	Sizer->Add(GetButtonPanel(this),0,wxALL|wxEXPAND,5);
	
	Center();

}

CDialog::CDialog(int control_master, int control_slave,bool picker)
:wxDialog(NULL,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	m_ButtonOk = NULL;
	m_Picker = picker;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
	
	SetSize(DEFAULT_DIALOG_WIDTH,DEFAULT_DIALOG_HEIGHT);
	
	m_DialogPanel = new CDialogPanel(control_master,this);
	Sizer->Add(m_DialogPanel,0,wxALL|wxEXPAND,0);

	m_DialogSlave = new CDialogPanel(control_slave,this);
	Sizer->Add(m_DialogSlave,1,wxALL|wxEXPAND,0);
	
	m_DialogPanel->SetSlave(m_DialogSlave);
	
	Sizer->Add(GetButtonPanel(this),0,wxALL|wxEXPAND,5);

	Center();

}

wxPanel *CDialog::GetButtonPanel(wxWindow *parent)
{

	wxPanel *Panel = new wxPanel(this);
		
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(PanelSizer);	
	
	if(m_Picker)
	{
		PanelSizer->AddStretchSpacer();
		m_ButtonOk = new wxButton(Panel,wxID_OK,GetMsg(MSG_OK));
		PanelSizer->Add(m_ButtonOk,0,wxALL,5);
		wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CANCEL));
		PanelSizer->Add(ButtonClose,0,wxALL,5);
	}else{
	
		wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CLOSE));
		PanelSizer->AddStretchSpacer();
		PanelSizer->Add(ButtonClose,0,wxALL,2);
	
	}

	return Panel;
}

wxString CDialog::_GetId()
{
	return m_DialogPanel->_GetId();
}

wxString  CDialog::_GetName()
{
	return m_DialogPanel->_GetName();
}

BEGIN_EVENT_TABLE(CDialogPanel,wxPanel)
	EVT_LISTBOX(ID_FILTER,OnListBox)
END_EVENT_TABLE()

CDialogPanel::CDialogPanel(int control_type, wxWindow *parent)
:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	m_IdType = -1;
	m_ListBox = NULL;
	m_Table = wxEmptyString;
	m_IdMaster = wxEmptyString;
	m_ControlType = control_type;
	m_ListBox = NULL;
	m_TopLabel = NULL;
	m_Slave = NULL;
	SetTable();
		
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
	wxPanel *TopPanel = new wxPanel(this);
	Sizer->Add(TopPanel,0,wxALL|wxEXPAND,5);
	wxBoxSizer *TopPanelSizer = new wxBoxSizer(wxHORIZONTAL);
	TopPanel->SetSizer(TopPanelSizer);

	m_TopLabel = new wxStaticText(TopPanel,wxID_ANY,wxEmptyString);
	TopPanelSizer->Add(m_TopLabel,0,wxALL,5);
	
	Sizer->Add(GetPanel(this),1,wxALL|wxEXPAND,0);
			
}

void CDialogPanel::OnListBox(wxCommandEvent &event)
{
	int sel = event.GetSelection() - 1;
	
	if(sel == -1)
	{
		m_IdType = -1;	
	}else{
		
		m_IdType = (int)m_ListBox->GetClientData(event.GetSelection());
	}
		
	Clear();
	Read();
}

void CDialogPanel::SetSlave(CDialogPanel *ptr)
{
	m_Slave = ptr;
}

wxPanel *CDialogPanel::GetPanel(wxWindow *Parent)
{
	switch(m_ControlType)
	{
		case CONTROL_ITEM:			return GetItemPanel(Parent);
		case CONTROL_LIGHT:			return GetLightPanel(Parent);
		case CONTROL_LIGHT_ITEM:	return GetLightItemPanel(Parent);
		case CONTROL_AREA:
		case CONTROL_SEAWAY:
		case CONTROL_SYMBOL_TYPE:
				return GetPanelList(Parent);
	}

}

wxPanel *CDialogPanel::GetLightItemPanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	Panel->SetBackgroundColour(*wxWHITE);
	Panel->SetSizer(Sizer);
	m_ListBox = GetFilterList(Panel,ID_FILTER);
	Sizer->Add(m_ListBox,0,wxALL|wxEXPAND,5);
	Sizer->Add(GetPanelList(Panel),1,wxALL|wxEXPAND,0);
				
	return Panel;
}


wxPanel *CDialogPanel::GetItemPanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	Panel->SetBackgroundColour(*wxWHITE);
	Panel->SetSizer(Sizer);
	m_ListBox = GetFilterList(Panel,ID_FILTER);
	Sizer->Add(m_ListBox,0,wxALL|wxEXPAND,5);
	Sizer->Add(GetPanelList(Panel),1,wxALL|wxEXPAND,0);
				
	return Panel;
}

wxPanel *CDialogPanel::GetLightPanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
	Sizer->Add(GetPanelList(Panel),1,wxALL|wxEXPAND,0);
	return Panel;
}

/*
wxListBox *CDialogPanel::GetFilterList(wxWindow *Parent)
{
	wxListBox *Filter = new wxListBox(Parent,ID_FILTER);
	Filter->Append(GetMsg(MSG_ALL));

	wxArrayString ar;
	wxString sql = wxString::Format(_("SELECT * FROM `%s` ORDER BY name"),TABLE_ITEM_TYPE);
	if(!my_query(sql))
		return Filter;
	
	int rows = 0;
	void *result = db_result();
	char **row;
		
	int i = 0;
	while(row = (char**)db_fetch_row(result))
	{
		wxString name(row[FI_ITEM_TYPE_NAME],wxConvUTF8);
		ar.Add(name);
		int id = Filter->Append(name);
		Filter->SetClientData(id,(int*)atoi(row[FI_ITEM_TYPE_ID]));
	}

	db_free_result(result);
	
	//m_FilterArray = GetItemType();
	//Filter->Append(m_FilterArray);
	return Filter;
}

wxComboBox *CDialogPanel::GetFilterCombo(wxWindow *Parent)
{
	wxComboBox *Filter = new wxComboBox(Parent,ID_FILTER,wxEmptyString,wxDefaultPosition,wxDefaultSize,NULL,0, wxCB_READONLY);
	Filter->Append(GetMsg(MSG_ALL));

	wxArrayString ar;
	wxString sql = wxString::Format(_("SELECT * FROM `%s` ORDER BY name"),TABLE_ITEM_TYPE);
	if(!my_query(sql))
		return Filter;
	
	int rows = 0;
	void *result = db_result();
	char **row;
		
	int i = 0;
	while(row = (char**)db_fetch_row(result))
	{
		wxString name(row[FI_ITEM_TYPE_NAME],wxConvUTF8);
		ar.Add(name);
		int id = Filter->Append(name);
		Filter->SetClientData(id,(int*)atoi(row[FI_ITEM_TYPE_ID]));
	}

	db_free_result(result);
	
//	m_FilterArray = GetItemType();
	//Filter->Append(m_FilterArray);
	return Filter;
}
*/
wxPanel *CDialogPanel::GetPanelList(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel *Panel = new wxPanel(Parent,wxID_ANY,wxDefaultPosition);
	Panel->SetBackgroundColour(*wxWHITE);
	Panel->SetSizer(Sizer);
	m_List = new CListCtrl(Panel,wxLC_REPORT |  wxLC_VIRTUAL | wxLC_SINGLE_SEL | wxLC_ALIGN_LEFT );

	int id = 0;
	wxListItem item;
	int counter = 0;
	SHeader h;

	while(Header[id].id_control != -1)
	{
		h = Header[id];
		
		if(h.id_control == m_ControlType)
		{
			h = Header[id];
			item.SetWidth(h.width);	
			item.SetText(GetMsg(h.column.id_msg));	
			m_List->InsertColumn(counter,item);
			m_List->_AddColumn(h.column.id,h.column.name);
			counter++;
		}
	
		id++;
	}

	id = 0;
	
	while(Id[id].id_control != -1)
	{
		SIds i = Id[id];
		if(i.id_control == m_ControlType)
		{
			m_List->SetColumnWithId(i.col_with_id);
			m_List->SetColumnWithName(i.col_with_name);
			if(m_TopLabel)
				m_TopLabel->SetLabel(GetMsg(i.id_label));
			break;
		} 
	
		id++;
	}

	m_List->SetControlType(m_ControlType,this);
	m_List->InitColumns();
	Read();
		
	Sizer->Add(m_List,1,wxALL|wxEXPAND,0);

	return Panel;

}

void CDialogPanel::SetTable()
{
	switch(m_ControlType)
	{
		case CONTROL_LIGHT:			m_Table = TABLE_LIGHT;			break;
		case CONTROL_LIGHT_ITEM:	m_Table = TABLE_LIGHT_ITEM;		break;
		case CONTROL_ITEM:			m_Table = TABLE_ITEM;			break;
		case CONTROL_AREA:			m_Table = TABLE_AREA;			break;
		case CONTROL_SEAWAY:		m_Table = TABLE_SEAWAY;			break;
		case CONTROL_SYMBOL_TYPE:	m_Table = TABLE_SYMBOL_TYPE;	break;
	
	}
}

void CDialogPanel::Read()
{
	switch(m_ControlType)
	{
		case CONTROL_ITEM:			ReadItems();		break;
		case CONTROL_LIGHT_ITEM:	ReadLightItems();	break;
		case CONTROL_LIGHT:
		case CONTROL_AREA:
		case CONTROL_SEAWAY:	
		case CONTROL_SYMBOL_TYPE:	ReadOthers();		break;
	}

}

void CDialogPanel::ReadOthers()
{	
	wxString sql;
	if(m_Field == wxEmptyString)		
		sql = wxString::Format(_("SELECT * FROM `%s`"),m_Table);
	else
		sql = wxString::Format(_("SELECT * FROM `%s` ORDER BY %s %s"),m_Table,m_Field,m_Order);
	
	m_List->Read(sql);
	m_List->Refresh(false);

}

void CDialogPanel::ReadItems()
{	
	wxString sql;

	if(m_IdType == -1)
	{
		if(m_Field == wxEmptyString)		
			sql = wxString::Format(_("SELECT * FROM `%s`"),m_Table);
		else
			sql = wxString::Format(_("SELECT * FROM `%s` ORDER BY %s %s"),m_Table,m_Field,m_Order);
	}else{

		if(m_Field == wxEmptyString)		
			sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_type = '%d'"),m_Table,m_IdType);
		else
			sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_type = '%d' ORDER BY %s %s"),m_Table,m_IdType,m_Field,m_Order);
	}

	m_List->Read(sql);
	m_List->Refresh(false);

}

void CDialogPanel::ReadLightItems()
{
	wxString sql;
	if(m_IdMaster == wxEmptyString)
		return;

	if(m_IdType == -1)
	{
		if(m_Field == wxEmptyString)		
			sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_light = '%s'"),VIEW_LIGHT_ITEM ,m_IdMaster);
		else
			sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_light = '%s' ORDER BY %s %s"), VIEW_LIGHT_ITEM,m_IdMaster, m_Field,m_Order);
	}else{
		
		if(m_Field == wxEmptyString)		
			sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_light = '%s' AND id_type = '%d'"),VIEW_LIGHT_ITEM,m_IdMaster, m_IdType);
		else
			sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_light = '%s' AND id_type = '%d' ORDER BY %s %s"),VIEW_LIGHT_ITEM, m_IdMaster, m_IdType, m_Field,m_Order);
	}

	m_List->Read(sql);
	m_List->Refresh(false);

}

void CDialogPanel::Clear()
{
	m_List->Clear();
}
	
void CDialogPanel::Select()
{
	m_List->Select();
}

void CDialogPanel::OnNew()
{
	switch(m_ControlType)
	{
		case CONTROL_ITEM:
		case CONTROL_ITEM_TYPE:
		case CONTROL_LIGHT:
		case CONTROL_AREA:
		case CONTROL_SEAWAY:
		case CONTROL_SYMBOL_TYPE:
			New();	
		break;

		case CONTROL_LIGHT_ITEM:
			NewLightItem();
		break;
	
	}
	
}

void CDialogPanel::New()
{
	CNew *ptr = new CNew(m_ControlType,m_IdType);
	
	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql; 
		bool query = false;
		switch(m_ControlType)
		{
			case CONTROL_ITEM:
				NewItem(ptr);
			break;
			case CONTROL_LIGHT:
				sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s'"),m_Table,ptr->GetName(),ptr->GetInfo());
				query = true;
			break;
			case CONTROL_ITEM_TYPE:
				sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s'"),m_Table,ptr->GetName(),ptr->GetInfo());
				query = true;
			break;
			case CONTROL_AREA:
			case CONTROL_SEAWAY:
			case CONTROL_SYMBOL_TYPE:
				sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s'"),m_Table,ptr->GetName(),ptr->GetInfo());
				query = true;
			break;
		}
		
		if(query)
		{
			if(!my_query(sql))
			{
				delete ptr;
				return;
			}
		}
			
		Clear();
		Read();
		
	}
	
	delete ptr;
	
}

void CDialogPanel::NewLightItem()
{
	CDialog *ptr = new CDialog(CONTROL_ITEM,true);
	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql;
		sql = wxString::Format(_("INSERT INTO %s SET id_light='%s', id_item='%s'"),m_Table,m_IdMaster,ptr->_GetId());
				
		if(!my_query(sql))
		{
			delete ptr;
			return;
		}
			
		Clear();
		Read();
	}
	
	delete ptr;
}

void CDialogPanel::NewItem(CNew *ptr)
{
	
	wxString sql;
	
	sql = wxString::Format(_("INSERT INTO %s SET id_type ='%d', name='%s', type='%s', info='%s'"),m_Table,ptr->GetItemType(),ptr->GetName(),ptr->GetType(),ptr->GetInfo());
	if(!my_query(sql))
		return;
	int id = db_last_insert_id();
	wxArrayPtrVoid controls = ptr->GetFeatureControls();

	for(size_t i = 0; i < controls.size(); i++)
	{
		wxTextCtrl *txt = (wxTextCtrl*)controls.Item(i);
		int id_feature = (int)txt->GetClientData();
		sql = wxString::Format	(_("DELETE FROM `%s` WHERE id_item ='%d' AND id_feature ='%d'"),TABLE_ITEM_VALUE,id,id_feature);
		my_query(sql);
		sql = wxString::Format	(_("INSERT INTO `%s` SET id_item ='%d', id_feature ='%d',value='%s'"),TABLE_ITEM_VALUE,id,id_feature,txt->GetValue());
		my_query(sql);
	}

		
}

void CDialogPanel::OnEdit(wxString id)
{
	switch(m_ControlType)
	{
		case CONTROL_LIGHT:	EditLight(id);	break;
		case CONTROL_ITEM:	EditItem(id);	break;
		case CONTROL_AREA:
		case CONTROL_SEAWAY:
		case CONTROL_SYMBOL_TYPE:
				EditName(id);
			break;
	}

}

int CDialogPanel::GetItemTypeId(wxString id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),m_Table,id);

	if(!my_query(sql))
		return 0;
		
	void *result = db_result();
	char **row = (char**)db_fetch_row(result);
	int value = (atoi(row[FI_ITEM_ID_TYPE]));

	db_free_result(result);
	return value;

}

void CDialogPanel::EditItem(wxString id)
{

	int type = GetItemTypeId(id);
	CNew *ptr = new CNew(m_ControlType,type,id,true);

	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),m_Table,id);
	
	if(!my_query(sql))
		return;
		
	void *result = db_result();
	char **row = (char**)db_fetch_row(result);
	//ptr->SetItemTypeID(atoi(row[FI_ITEM_ID_ITEM_TYPE]));
	ptr->SetName(Convert(row[FI_ITEM_NAME]));
	ptr->SetType(Convert(row[FI_ITEM_TYPE]));
	ptr->SetInfo(Convert(row[FI_ITEM_INFO]));
	db_free_result(result);	

	
	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET id_type = '%d', name = '%s', type = '%s', info ='%s' WHERE id = '%s'"),m_Table,ptr->GetItemType(),ptr->GetName(),ptr->GetType(),ptr->GetInfo(),id);
		my_query(sql);

		wxArrayPtrVoid controls = ptr->GetFeatureControls();

		for(size_t i = 0; i < controls.size(); i++)
		{
			wxTextCtrl *txt = (wxTextCtrl*)controls.Item(i);
			int id_feature = (int)txt->GetClientData();
			sql = wxString::Format	(_("DELETE FROM `%s` WHERE id_item ='%s' AND id_feature ='%d'"),TABLE_ITEM_VALUE,id,id_feature);
			my_query(sql);
			sql = wxString::Format	(_("INSERT INTO `%s` SET id_item ='%s', id_feature ='%d',value='%s'"),TABLE_ITEM_VALUE,id,id_feature,txt->GetValue());
			my_query(sql);
		}

		Clear();
		Read();
		Select();
	}

	delete ptr;
}

void CDialogPanel::EditLight(wxString id)
{
	CNew *ptr = new CNew(m_ControlType);
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),m_Table,id);
	
	if(!my_query(sql))
		return;
				
	void *result = db_result();
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetName(Convert(row[FID_NAME]));
	ptr->SetInfo(Convert(row[FID_INFO]));
	db_free_result(result);	

	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET name='%s', info ='%s' WHERE id = '%s'"),m_Table,ptr->GetName(),ptr->GetInfo(),id);
		my_query(sql);
		Clear();
		Read();
		Select();
	}

	delete ptr;
}

void CDialogPanel::EditName(wxString id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),m_Table,id);
	
	if(!my_query(sql))
		return;
		
	CNew *ptr = new CNew(m_ControlType);
		
	void *result = db_result();
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetName(Convert(row[FID_NAME]));
	ptr->SetInfo(Convert(row[FID_INFO]));
	db_free_result(result);	

	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET name='%s', info ='%s' WHERE id = '%s'"),m_Table,ptr->GetName(),ptr->GetInfo(),id);
		my_query(sql);
		Clear();
		Read();
		Select();
	}

	delete ptr;
}

void CDialogPanel::EditType(wxString id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),m_Table,id);
	
	if(!my_query(sql))
		return;
		
	CNew *ptr = new CNew(m_ControlType);
	
	void *result = db_result();
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetType(Convert(row[FID_TYPE]));
	ptr->SetInfo(Convert(row[FID_INFO]));
	
	db_free_result(result);

	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET type= '%s', info ='%s' WHERE id = '%s'"),m_Table,ptr->GetType(),ptr->GetInfo(),id);
		my_query(sql);
		Clear();
		Read();
		Select();
	}

	delete ptr;
	
}

void CDialogPanel::OnDelete(wxString id)
{

	wxMessageDialog *MessageDialog = new wxMessageDialog(this,GetMsg(MSG_DELETE_QUESTION),wxString::Format(wxT("%s %s"),wxT(PRODUCT_NAME),wxT(PRODUCT_VERSION)),wxYES_NO|wxICON_QUESTION);
    if(MessageDialog->ShowModal() == wxID_YES)
	{
		wxString sql = wxString::Format(_("DELETE FROM %s WHERE id = '%s'"),m_Table,id);
		my_query(sql);
		Clear();
		Read();
	
	}

	delete MessageDialog;
}

void CDialogPanel::OnColumnCLick(wxString field, int order)
{
	if(order == ORDER_ASC)
		m_Order = _("ASC");
	else
		m_Order = _("DESC");
	
	m_Field = field;
	Clear();
	Read();
}

void CDialogPanel::OnSelect(wxString id, wxString name)
{
	m_Id = id;
	m_Name = name;
	
	if(m_Slave)
	{
		m_Slave->_SetIdMaster(id);
		m_Slave->Read();
	}
	
}

wxString CDialogPanel::_GetId()
{
	return m_Id;
}

wxString  CDialogPanel::_GetName()
{
	return m_Name;
}

void CDialogPanel::_SetIdMaster(wxString id)
{
	m_IdMaster = id;
}


CMultiDialog::CMultiDialog()
:wxDialog(NULL,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	SetSize(DEFAULT_DIALOG_WIDTH,DEFAULT_DIALOG_HEIGHT);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
	m_MultiDialogPanel = new CMultiDialogPanel(this);
	Sizer->Add(m_MultiDialogPanel,1,wxALL|wxEXPAND,5);

}

wxString CMultiDialog::_GetId()
{
	return m_MultiDialogPanel->GetSelectedPanel()->_GetId();
}

wxString CMultiDialog::_GetName()
{
	return m_MultiDialogPanel->GetSelectedPanel()->_GetName();
}

BEGIN_EVENT_TABLE(CMultiDialogPanel,wxPanel)
	EVT_LISTBOOK_PAGE_CHANGED(ID_LISTBOOK,OnPageChanged)
END_EVENT_TABLE()

CMultiDialogPanel::CMultiDialogPanel(wxWindow *parent)
:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	m_SelectedPanel = NULL;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
			
	wxListbook *Book = new wxListbook(this,ID_LISTBOOK);
	Sizer->Add(Book,1,wxALL|wxEXPAND,0);

	int i = 0;
	while(Id[i].id_control !=-1)
	{
		CDialogPanel *DialogPanel = new CDialogPanel(Id[i].id_control,Book);
		m_Panels.Add(DialogPanel);
		Book->AddPage(DialogPanel, GetMsg(Id[i].id_label) );
		i++;
	}
	
}

void CMultiDialogPanel::OnPageChanged(wxListbookEvent &event)
{
	m_SelectedPanel = (CDialogPanel*)m_Panels.Item(event.GetSelection());
}

CDialogPanel *CMultiDialogPanel::GetSelectedPanel()
{
	return m_SelectedPanel;

}