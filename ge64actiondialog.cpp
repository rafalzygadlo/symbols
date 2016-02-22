#include <wx/wx.h>
#include <wx/statline.h>
#include "conf.h"
#include "ge64actiondialog.h"
#include "control.h"
#include "tools.h"
#include "module.h"
#include "action.h"

BEGIN_EVENT_TABLE(CGE64ActionDialog,wxDialog)
	EVT_BUTTON(ID_LIGHT_ON,OnLightOn)
	EVT_BUTTON(ID_LIGHT_OFF,OnLightOff)
END_EVENT_TABLE();

CGE64ActionDialog::CGE64ActionDialog(void *db,CGE64 *ptr)
	:wxDialog(NULL,wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize )
{	
	m_DB = db;
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(Sizer);
	
	Sizer->Add(GetTopPanel(this),0,wxALL|wxEXPAND,5);
	Sizer->Add(GetActionPanel(this),1,wxALL|wxEXPAND,5);
	Sizer->Add(GetButtonPanel(this),0,wxALL|wxEXPAND,5);
	SetSizer(Sizer);		
	Center();
	SetDriver(ptr);

	SetTitle(wxString::Format(_("%s (%s)"),ptr->GetSymbolName(),ptr->GetName()));
}

CGE64ActionDialog::~CGE64ActionDialog()
{

}

void CGE64ActionDialog::SetTitle(wxString str)
{
	m_Title->SetLabel(str);
}

wxPanel *CGE64ActionDialog::GetTopPanel(wxWindow *parent)
{
	wxPanel *Panel = new wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize);
	wxBoxSizer *Sizer = new wxBoxSizer(wxVERTICAL);
	Panel->SetSizer(Sizer);
	wxFont font;
	font.SetPointSize(12);
	font.SetWeight(wxBOLD);
	m_Title = new wxStaticText(Panel,wxID_ANY,wxEmptyString);
	m_Title->SetFont(font);
	Sizer->Add(m_Title,0,wxALL|wxEXPAND,2);
		
	return Panel;
}

wxPanel *CGE64ActionDialog::GetActionPanel(wxWindow *parent)
{
	wxPanel *Panel = new wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize);
		
	wxFlexGridSizer *Sizer = new wxFlexGridSizer(3);
	Sizer->AddGrowableCol(0,1);
	Sizer->AddGrowableCol(1,1);
	Sizer->AddGrowableCol(2,1);
	
	m_ButtonOn = new CButton(m_DB,_GetUID(),Panel,ID_LIGHT_ON,GetMsg(MSG_LIGHT_ON));
	m_ButtonOn->Right(MODULE_GE64,ACTION_LIGHT_ON);
	Sizer->Add(m_ButtonOn,1,wxALL|wxEXPAND,2);

	m_ButtonOff = new CButton(m_DB,_GetUID(),Panel,ID_LIGHT_OFF,GetMsg(MSG_LIGHT_OFF));
	m_ButtonOff->Right(MODULE_GE64,ACTION_LIGHT_OFF);
	Sizer->Add(m_ButtonOff,1,wxALL|wxEXPAND,2);

	Panel->SetSizer(Sizer);
	
	return Panel;
			
}

wxPanel *CGE64ActionDialog::GetButtonPanel(wxWindow *parent)
{

	wxPanel *Panel = new wxPanel(this);
	wxBoxSizer *Sizer = new wxBoxSizer(wxHORIZONTAL);
	Panel->SetSizer(Sizer);

	wxStaticText *LabelProductInfo = new wxStaticText(Panel,wxID_ANY,GetProductInfo() ,wxDefaultPosition,wxDefaultSize);
	Sizer->Add(LabelProductInfo,0,wxALL,5);
	Sizer->AddStretchSpacer(1);

	wxButton *ButtonClose = new wxButton(Panel,wxID_CANCEL,GetMsg(MSG_CLOSE));
	Sizer->AddStretchSpacer();
	Sizer->Add(ButtonClose,0,wxALL,2);
	
	return Panel;
}


void CGE64ActionDialog::EnableControls(bool v)
{
	m_ButtonOn->Enable(v);
	m_ButtonOff->Enable(v);
}

void CGE64ActionDialog::SetDriver(CGE64 *ptr)
{
	if(ptr)
		EnableControls(true);
	else
		EnableControls(false);
	
	m_Driver = ptr;
}

void CGE64ActionDialog::OnLightOn(wxCommandEvent &event)
{
	//m_Driver->LightOn();
}

void CGE64ActionDialog::OnLightOff(wxCommandEvent &event)
{
	//m_Driver->LightOff();
}
