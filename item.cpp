#include "item.h"
#include "conf.h"
#include "tools.h"
#include "listctrl.h"
#include "db.h"
#include <wx/mstream.h>
#include <wx/dataview.h>
//#include "images/del.img"

extern unsigned int	add_size;
extern unsigned char add[]; 

extern unsigned int	del_size;
extern unsigned char del[]; 

CItemPanel::CItemPanel(wxWindow *top, wxWindow *parent)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	m_Top = top;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
		
	wxString sql = wxString::Format(_("SELECT * FROM `%s` ORDER BY name"),TABLE_ITEM_TYPE);
	Read(sql);
		
	for(size_t i = 0; i < m_Items.size(); i++)
	{
		CItem *ptr = (CItem*)m_Items.Item(i);
		Sizer->Add(ptr,0,wxALL|wxEXPAND,1);
	}
		
	SetSizer(Sizer);
				
}

CItemPanel::~CItemPanel()
{
	
}

void CItemPanel::_Layout()
{
	m_Top->Layout();
}

void CItemPanel::Read(wxString query)
{
	if(!my_query(query))
		return;
	
	int rows = 0;
	void *result = db_result();
	char **row;
	
	while(row = (char**)db_fetch_row(result))
	{
		wxString str(row[0],wxConvUTF8);
		wxString name(row[1],wxConvUTF8);
		CItem *Item = new CItem(this,name);
		Item->_SetId(str);
		m_Items.Add(Item);
	}

	db_free_result(result);
	
}

CItem *CItemPanel::GetItem(int id)
{
	return (CItem*)m_Items.Item(id);
}

size_t CItemPanel::GetCount()
{
	return m_Items.size();
}

void CItemPanel::AppendCombo(int item_id)
{
	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id='%d'"),TABLE_ITEM,item_id);
	my_query(sql);
	
	void *result = db_result();
	char **row =  (char**)db_fetch_row(result);
	
	int id_type = atoi(row[FI_ITEM_ID_TYPE]);
	
	for(size_t i = 0; i < m_Items.size(); i++)
	{
		long _id;
		CItem *Item = (CItem*)m_Items.Item(i);
		Item->_GetId().ToLong(&_id);
		if(_id == id_type)
		{
			CComboPanel *ComboPanel = Item->AppendCombo();
			ComboPanel->SetSelection(item_id);

		}
	}

	db_free_result(result);
}

BEGIN_EVENT_TABLE(CItem, wxPanel)
	EVT_BUTTON(ID_NEW,CItem::OnNew)
END_EVENT_TABLE()

CItem::CItem(CItemPanel *parent,wxString name)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition)
{
	m_Counter = 1;
	m_ItemPanel = parent;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(Sizer);
	
	wxMemoryInputStream in_1((const unsigned char*)add,add_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
	
	wxBoxSizer *HSizer = new wxBoxSizer(wxHORIZONTAL);
	Sizer->Add(HSizer,0,wxALL|wxEXPAND,0);
	
	wxButton *New = new wxBitmapButton(this,ID_NEW,wxBitmap(myImage_1));
	HSizer->Add(New,0,wxALL,1);
	wxStaticText *Text = new wxStaticText(this,wxID_ANY,name);
	HSizer->Add(Text,0,wxALL,1);
		
}

CItem::~CItem()
{

}

CComboPanel *CItem::AppendCombo()
{
	CComboPanel *ComboPanel = new CComboPanel(this,m_Id);
	this->GetSizer()->Add(ComboPanel,0,wxALL|wxEXPAND,1);
	
	m_ItemPanel->_Layout();
	m_Counter++;

	m_List.Add(ComboPanel);

	return ComboPanel;
}

void CItem::OnDelete(CComboPanel *panel)
{
	m_List.Remove(panel);
	this->GetSizer()->Detach(panel);
	delete panel;
	m_ItemPanel->_Layout();
}

void CItem::OnNew(wxCommandEvent &event)
{
	AppendCombo();
}

wxString CItem::_GetId()
{
	return m_Id;
}

void CItem::_SetId(wxString v)
{
	m_Id = v;
}

void CItem::_SetName(wxString v)
{
	m_Name->SetLabel(v);
}

size_t CItem::GetCount()
{
	return m_List.size();
}

CComboPanel *CItem::GetCombo(int id)
{
	return (CComboPanel*)m_List.Item(id);
}


BEGIN_EVENT_TABLE(CComboPanel, wxPanel)
	EVT_BUTTON(ID_DELETE,CComboPanel::OnDelete)
END_EVENT_TABLE()

CComboPanel::CComboPanel(CItem *parent, wxString id)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition)
{
	m_Parent = parent;
	
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(PanelSizer);
			
	m_Combo = new wxComboBox(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,NULL,0,wxCB_READONLY);
	PanelSizer->Add(m_Combo,1,wxALL,1);
	
	wxMemoryInputStream in_1((const unsigned char*)del,del_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);

	wxButton *Delete = new wxBitmapButton(this,ID_DELETE,wxBitmap(myImage_1));
	PanelSizer->Add(Delete,0,wxALL,1);

	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_type = '%s'"),TABLE_ITEM,id);
	Read(sql);
		
}

void CComboPanel::OnDelete(wxCommandEvent &event)
{
	m_Parent->OnDelete(this);
}

void CComboPanel::Read(wxString query)
{
	if(!my_query(query))
		return;
	
	int rows = 0;
	void *result = db_result();
	char **row;
	int counter = 0;
	while(row = (char**)db_fetch_row(result))
	{
		wxString id(row[FI_ITEM_ID],wxConvUTF8);
		wxString name(row[FI_ITEM_NAME],wxConvUTF8);
		wxString type(row[FI_ITEM_TYPE],wxConvUTF8);
		m_Combo->Append(wxString::Format(_("%s %s"),name,type));
		m_Combo->SetSelection(0);
		long _id;
		id.ToLong(&_id);
		m_Combo->SetClientData(counter, (int*)_id);
		counter++;
	}

	db_free_result(result);
	
}

int CComboPanel::_GetId()
{
	return (int)m_Combo->GetClientData(m_Combo->GetSelection());
}

void CComboPanel::SetSelection(int id)
{
	
	for(size_t i = 0; i < m_Combo->GetCount(); i++)
	{
		int _id = (int)m_Combo->GetClientData(i);
		if(_id == id)
			m_Combo->SetSelection(i);
	}
}