#include "battery.h"
#include "conf.h"
#include "tools.h"
#include "listctrl.h"
#include "battery_new.h"
#include "db.h"
#include <wx/mstream.h>


extern unsigned int	add_size;
extern unsigned char add[];

CBatteryDialog::CBatteryDialog(int type)
:wxDialog(NULL,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	SetSize(DEFAULT_DIALOG_WIDTH,DEFAULT_DIALOG_HEIGHT);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(Sizer);
	Sizer->Add(GetPanel(this),1,wxALL|wxEXPAND,0);

	wxPanel *Panel = new wxPanel(this);
	Sizer->Add(Panel,0,wxALL|wxEXPAND,5);
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(PanelSizer);
	ButtonOk = NULL;

	if(type == PICKER)
	{
		PanelSizer->AddStretchSpacer();
		ButtonOk = new wxButton(Panel,wxID_OK,GetMsg(MSG_OK));
		ButtonOk->Disable();
		PanelSizer->Add(ButtonOk,0,wxALL,5);
		wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CANCEL));
		PanelSizer->Add(ButtonClose,0,wxALL,5);
		SetLabel(GetMsg(MSG_BATTERY));
	
	}else{
	
		wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CLOSE));
		PanelSizer->AddStretchSpacer();
		PanelSizer->Add(ButtonClose,0,wxALL,5);
		SetLabel(GetMsg(MSG_BATTERY));
	
	}
		
	Center();
	
}

CBatteryDialog::~CBatteryDialog()
{

}

wxPanel *CBatteryDialog::GetPanel(wxWindow *Parent)
{
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel *Panel = new wxPanel(this,wxID_ANY,wxDefaultPosition);
	Panel->SetSizer(Sizer);
	m_List = new CListCtrl(Panel,wxLC_REPORT |  wxLC_VIRTUAL );
	wxListItem item;
	item.SetWidth(150);	item.SetText(GetMsg(MSG_NAME));		m_List->InsertColumn(0,item);
	item.SetWidth(100);	item.SetText(GetMsg(MSG_TYPE));		m_List->InsertColumn(1,item);
	item.SetWidth(100);	item.SetText(GetMsg(MSG_CAPACITY));	m_List->InsertColumn(2,item);
	item.SetWidth(250);	item.SetText(GetMsg(MSG_INFO));		m_List->InsertColumn(3,item);

	m_List->_AddColumn(FID_BATTERY_NAME,FNAME_BATTERY_NAME);
	m_List->_AddColumn(FID_BATTERY_TYPE,FNAME_BATTERY_TYPE);
	m_List->_AddColumn(FID_BATTERY_CAPACITY,FNAME_BATTERY_CAPACITY);
	m_List->_AddColumn(FID_BATTERY_INFO,FNAME_BATTERY_INFO);
	
	m_List->_AddColumn(FID_AREA_ID,FNAME_AREA_ID);
	m_List->SetColumnWithId(4); // id kolumny z id pól bazy danych
		
	m_List->InitColumns();
	Read();
	
	m_List->SetControlType(CONTROL_BATTERY,this);

	Sizer->Add(m_List,1,wxALL|wxEXPAND,0);

	return Panel;

}

void CBatteryDialog::Read()
{
	wxString sql;

	if(m_Field == wxEmptyString)		
		sql = wxString::Format(_("SELECT * FROM `%s`"),TABLE_BATTERY);
	else
		sql = wxString::Format(_("SELECT * FROM %s ORDER BY %s %s"),TABLE_BATTERY,m_Field,m_Order);

	m_List->Read(sql);
	m_List->Refresh(false);
}

void CBatteryDialog::Clear()
{
	m_List->Clear();
}
	
void CBatteryDialog::Select()
{
	m_List->Select();
}

void CBatteryDialog::OnNew()
{
	
	CBatteryNew *ptr = new CBatteryNew();
	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format(_("INSERT INTO %s SET name='%s', info='%s', type='%s', capacity='%s'"),TABLE_BATTERY,ptr->GetName(),ptr->GetInfo(),ptr->GetType(),ptr->GetCapacity());
		
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

void CBatteryDialog::OnEdit(wxString id)
{
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%s'"),TABLE_BATTERY,id);
	
	if(!my_query(sql))
		return;
		
	CBatteryNew *ptr = new CBatteryNew();
	
	void *result = db_result();
	char **row = (char**)db_fetch_row(result);
	
	ptr->SetName(Convert(row[FID_BATTERY_NAME]));
	ptr->SetInfo(Convert(row[FID_BATTERY_INFO]));
	ptr->SetCapacity(Convert(row[FID_BATTERY_CAPACITY]));
	ptr->SetType(Convert(row[FID_BATTERY_TYPE]));
	
	db_free_result(result);

	if(ptr->ShowModal() == wxID_OK)
	{
		wxString sql = wxString::Format	(_("UPDATE %s SET name='%s', info ='%s', type ='%s', capacity='%s' WHERE id = '%s'"),TABLE_BATTERY,ptr->GetName(),ptr->GetInfo(),ptr->GetType(),ptr->GetCapacity(),id);
		my_query(sql);
		Clear();
		Read();
		Select();
	}

	delete ptr;
	
}

void CBatteryDialog::OnDelete(wxString id)
{
	wxMessageDialog *MessageDialog = new wxMessageDialog(this,GetMsg(MSG_DELETE_QUESTION),wxString::Format(wxT("%s %s"),wxT(PRODUCT_NAME),wxT(PRODUCT_VERSION)),wxYES_NO|wxICON_QUESTION);
    if(MessageDialog->ShowModal() == wxID_YES)
	{
		wxString sql = wxString::Format(_("DELETE FROM %s WHERE id = '%s'"),TABLE_BATTERY,id);
		my_query(sql);
		Clear();
		Read();
		Select();
	}

	delete MessageDialog;
}


void CBatteryDialog::OnColumnCLick(wxString field, int order)
{
	if(order == ORDER_ASC)
		m_Order = _("ASC");
	else
		m_Order = _("DESC");
	
	m_Field = field;
	Clear();
	Read();
}

void CBatteryDialog::OnSelect(wxArrayString row)
{
	if(ButtonOk)
		ButtonOk->Enable();
	m_Id = row[0];
	m_Name = row[1];
}

void CBatteryDialog::OnDeSelect()
{
	if(ButtonOk)
		ButtonOk->Disable();
}

wxString CBatteryDialog::GetBatteryId()
{
	return m_Id;
}

wxString CBatteryDialog::GetBatteryName()
{
	return m_Name;
}



BEGIN_EVENT_TABLE(CBatteryPanel, wxPanel)
	EVT_BUTTON(ID_NEW,CBatteryPanel::OnNew)
END_EVENT_TABLE()

CBatteryPanel::CBatteryPanel(wxWindow *parent,wxWindow *top)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	m_Parent = parent;
	m_Top = top;
	m_Sizer = new wxBoxSizer(wxVERTICAL);
	
	m_Panel = new wxPanel(this);
	m_Panel->SetWindowStyle(wxBORDER_SIMPLE);
	m_Sizer->Add(m_Panel,1,wxALL|wxEXPAND,0);
	m_PanelSizer = new wxBoxSizer(wxVERTICAL);
	m_Panel->SetSizer(m_PanelSizer);

	wxMemoryInputStream in_1((const unsigned char*)add,add_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);


	wxButton *New = new wxBitmapButton(m_Panel,ID_NEW,wxBitmap(myImage_1));
	m_PanelSizer->Add(New,0,wxALL,3);

	SetSizer(m_Sizer);
			
}

CBatteryPanel::~CBatteryPanel()
{
}

wxArrayPtrVoid CBatteryPanel::GetPanels()
{
	return m_Panels;
}

void CBatteryPanel::New(wxString id, wxString name)
{
	CBattery *ptr = new CBattery(m_Panel,this);
	ptr->SetBatteryId(id);
	ptr->SetBatteryName(name);
	m_PanelSizer->Add(ptr,0,wxALL,1);
	m_Panels.Add(ptr);
}

void CBatteryPanel::OnNew(wxCommandEvent &event)
{
	CBatteryDialog *BatteryDialog = new CBatteryDialog(PICKER);
	
	if(BatteryDialog->ShowModal() == wxID_OK)
	{
		New(BatteryDialog->GetBatteryId(),BatteryDialog->GetBatteryName());
		m_Top->Layout();
		m_Top->GetSizer()->SetSizeHints(m_Top);
	}
	
	delete BatteryDialog;
}

void CBatteryPanel::OnEdit(CBattery *ptr)
{
//	wxColourDialog dialog(this);
//	if (dialog.ShowModal() == wxID_OK)
//	{
	//	wxColor color = dialog.GetColourData().GetColour();
		//ptr->SetColor(color);
		//ptr->Refresh();
//	}

}

void CBatteryPanel::OnDelete(CBattery *ptr)
{
	m_PanelSizer->Detach(ptr);
	m_Top->Layout();
	m_Top->GetSizer()->SetSizeHints(m_Top);
	m_Panels.Remove(ptr);
	delete ptr;
}


BEGIN_EVENT_TABLE(CBattery, wxPanel)
	EVT_CONTEXT_MENU(CBattery::OnContextMenu)
	EVT_MENU(ID_DELETE,CBattery::OnDelete)
	EVT_MENU(ID_EDIT,CBattery::OnEdit)
END_EVENT_TABLE()

CBattery::CBattery(wxWindow *parent, CBatteryPanel *panel)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition)
{
	m_Parent = parent;
	m_BatteryPanel = panel;
	m_Sizer = new wxBoxSizer(wxHORIZONTAL);
	
	m_Panel = new wxPanel(this);
	m_Sizer->Add(m_Panel,0,wxALL|wxEXPAND,2);
	
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxHORIZONTAL);
	m_Panel->SetSizer(PanelSizer);
	
	m_Name = new wxStaticText(m_Panel,wxID_ANY,wxEmptyString);
	PanelSizer->Add(m_Name,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	SetSizer(m_Sizer);
}

CBattery::~CBattery()
{

}

void CBattery::OnContextMenu(wxContextMenuEvent &event)
{
	wxMenu *Menu = new wxMenu();
	Menu->Append(ID_EDIT,GetMsg(MSG_EDIT));
	Menu->Append(ID_DELETE,GetMsg(MSG_DELETE));
	
	PopupMenu(Menu);
	delete Menu;
}

void CBattery::OnDelete(wxCommandEvent &event)
{
	m_BatteryPanel->OnDelete(this);
}

void CBattery::OnEdit(wxCommandEvent &event)
{
	m_BatteryPanel->OnEdit(this);
}

void CBattery::SetBatteryId(wxString v)
{

}

void CBattery::SetBatteryName(wxString v)
{
	m_Name->SetLabel(v);
}
