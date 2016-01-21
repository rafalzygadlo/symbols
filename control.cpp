#include "control.h"
#include "conf.h"
#include "db.h"
#include "tools.h"
#include "right.h"

BEGIN_EVENT_TABLE(CMenu,wxMenu)
	EVT_MENU(wxID_ANY,OnMenu)
END_EVENT_TABLE();

//Panel
CPanel::CPanel(wxWindow *parent)
	:wxPanel(parent)
{
	//Hide();
	SetBackgroundColour(*wxRED);
}

bool CPanel::CheckRight(int id_module,int id_action)
{
	return true;
}

//Menu
CMenu::CMenu()
{

}

void CMenu::OnMenu(wxCommandEvent &event)
{
	fprintf(stderr,"ID:%d\n",event.GetId());
	event.Skip();
}

bool CMenu::CheckRight(int id_module,int id_action,wxMenuItem *item)
{
	item->Enable(false);
	
	item->SetText(item->GetText() + "(" + GetMsg(MSG_NO_PERMISSION) + ")");
	return true;
}

//Button
CButton::CButton(wxWindow *parent, int id, wxString name)
	:wxButton(parent,id,name)
{
	//Disable();
	SetMinSize(wxSize(-1,64));
}

bool CButton::CheckRight(int id_module,int id_action)
{
	return true;
}
