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

wxArrayPtrVoid CItemPanel::GetItems()
{
	return m_Items;
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

BEGIN_EVENT_TABLE(CItem, wxPanel)
	EVT_BUTTON(ID_NEW,CItem::OnNew)
END_EVENT_TABLE()

CItem::CItem(CItemPanel *parent,wxString name)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition)
{
	m_Counter = 1;
	m_ItemPanel = parent;
	wxStaticBoxSizer *Sizer = new wxStaticBoxSizer(wxVERTICAL,this,name);
	SetSizer(Sizer);
	
	wxMemoryInputStream in_1((const unsigned char*)add,add_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);
	
	wxButton *New = new wxBitmapButton(this,ID_NEW,wxBitmap(myImage_1));
	Sizer->Add(New,0,wxALL|wxALIGN_RIGHT,1);
		
}

CItem::~CItem()
{

}

void CItem::AppendCombo()
{
	CComboPanel *ComboPanel = new CComboPanel(this,m_Id);
	this->GetSizer()->Add(ComboPanel,0,wxALL|wxEXPAND,1);
	
	m_ItemPanel->_Layout();
	m_Counter++;

	m_List.Add(ComboPanel);

}

void CItem::OnDelete(CComboPanel *panel)
{
	this->GetSizer()->Detach(panel);
	delete panel;
	m_List.Remove(panel);
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

BEGIN_EVENT_TABLE(CComboPanel, wxPanel)
	EVT_BUTTON(ID_DELETE,CComboPanel::OnDelete)
END_EVENT_TABLE()

CComboPanel::CComboPanel(CItem *parent, wxString id)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition)
{
	m_Parent = parent;
	
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(PanelSizer);
			
	wxComboBox *Combo = new wxComboBox(this,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,NULL,0,wxCB_READONLY);
	PanelSizer->Add(Combo,1,wxALL,1);
	
	wxMemoryInputStream in_1((const unsigned char*)del,del_size);
    wxImage myImage_1(in_1, wxBITMAP_TYPE_PNG);

	wxButton *Delete = new wxBitmapButton(this,ID_DELETE,wxBitmap(myImage_1));
	PanelSizer->Add(Delete,0,wxALL,1);

	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id_type = '%s'"),TABLE_ITEM,id);
	Read(sql,Combo);
		
}

void CComboPanel::OnDelete(wxCommandEvent &event)
{
	m_Parent->OnDelete(this);
}

void CComboPanel::Read(wxString query, wxComboBox *combo)
{
	if(!my_query(query))
		return;
	
	int rows = 0;
	void *result = db_result();
	char **row;
	
	while(row = (char**)db_fetch_row(result))
	{
		wxString name(row[FI_ITEM_NAME],wxConvUTF8);
		wxString type(row[FI_ITEM_TYPE],wxConvUTF8);
		combo->Append(wxString::Format(_("%s %s"),name,type));
	}

	db_free_result(result);
	
}