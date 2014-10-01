#include "picker.h"
#include "conf.h"
#include "tools.h"
#include "listctrl.h"
#include "db.h"
#include <wx/mstream.h>


extern unsigned int	add_size;
extern unsigned char add[]; 

BEGIN_EVENT_TABLE(CPickerPanel, wxPanel)
	EVT_BUTTON(ID_NEW,CPickerPanel::OnNew)
END_EVENT_TABLE()

CPickerPanel::CPickerPanel(wxWindow *parent,wxWindow *top, int control_type)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	m_Parent = parent;
	m_Top = top;
	m_ControlType = control_type;
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

CPickerPanel::~CPickerPanel()
{
}

wxArrayPtrVoid CPickerPanel::GetPanels()
{
	return m_Panels;
}

void CPickerPanel::New(wxString id, wxString name)
{
	CPicker *ptr = new CPicker(m_Panel,this);
	ptr->_SetId(id);
	ptr->_SetName(name);
	m_PanelSizer->Add(ptr,0,wxALL,1);
	m_Panels.Add(ptr);
}

void CPickerPanel::OnNew(wxCommandEvent &event)
{
	CDialog *Dialog = new CDialog(m_ControlType,true);
	
	if(Dialog->ShowModal() == wxID_OK)
	{
		New(Dialog->_GetId(),Dialog->_GetName());
		m_Top->Layout();
		m_Top->GetSizer()->SetSizeHints(m_Top);
	}
	
	delete Dialog;
	
}

void CPickerPanel::OnEdit(CPicker *ptr)
{
	CDialog *Dialog = new CDialog(m_ControlType,true);
	
	if(Dialog->ShowModal() == wxID_OK)
	{
		ptr->_SetId(Dialog->_GetId());
		ptr->_SetName(Dialog->_GetName());

	}
	
	delete Dialog;
}

void CPickerPanel::OnDelete(CPicker *ptr)
{
	m_PanelSizer->Detach(ptr);
	m_Top->Layout();
	m_Top->GetSizer()->SetSizeHints(m_Top);
	m_Panels.Remove(ptr);
	delete ptr;
}


BEGIN_EVENT_TABLE(CPicker, wxPanel)
	EVT_CONTEXT_MENU(CPicker::OnContextMenu)
	EVT_MENU(ID_DELETE,CPicker::OnDelete)
	EVT_MENU(ID_EDIT,CPicker::OnEdit)
END_EVENT_TABLE()

CPicker::CPicker(wxWindow *parent, CPickerPanel *panel)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition)
{
	m_Parent = parent;
	m_PickerPanel = panel;
	m_Sizer = new wxBoxSizer(wxHORIZONTAL);
	
	m_Panel = new wxPanel(this);
	m_Sizer->Add(m_Panel,0,wxALL|wxEXPAND,2);
	
	wxBoxSizer *PanelSizer = new wxBoxSizer(wxHORIZONTAL);
	m_Panel->SetSizer(PanelSizer);
	
	m_Name = new wxStaticText(m_Panel,wxID_ANY,wxEmptyString);
	PanelSizer->Add(m_Name,0,wxALL|wxALIGN_CENTER_VERTICAL,2);
	
	SetSizer(m_Sizer);
}

CPicker::~CPicker()
{

}

void CPicker::OnContextMenu(wxContextMenuEvent &event)
{
	wxMenu *Menu = new wxMenu();
	Menu->Append(ID_EDIT,GetMsg(MSG_EDIT));
	Menu->Append(ID_DELETE,GetMsg(MSG_DELETE));
	
	PopupMenu(Menu);
	delete Menu;
}

void CPicker::OnDelete(wxCommandEvent &event)
{
	m_PickerPanel->OnDelete(this);
}

void CPicker::OnEdit(wxCommandEvent &event)
{
	m_PickerPanel->OnEdit(this);
}

void CPicker::_SetId(wxString v)
{
	m_Id = v;
}

void CPicker::_SetName(wxString v)
{
	m_Name->SetLabel(v);
}
