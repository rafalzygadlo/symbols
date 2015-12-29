#include "control.h"
#include "conf.h"
#include "db.h"
#include "tools.h"
#include "right.h"

BEGIN_EVENT_TABLE(CMenu,wxMenu)
	EVT_MENU(wxID_ANY,OnMenu)
END_EVENT_TABLE();

//Menu
CMenu::CMenu()
{

}

void CMenu::OnMenu(wxCommandEvent &event)
{
	fprintf(stderr,"ID:%d\n",event.GetId());
	event.Skip();
}

//Panel
CPanel::CPanel(wxWindow *parent)
	:wxPanel(parent)
{
	//Hide();
	SetBackgroundColour(*wxRED);
}

//Control
void CControl::CheckRight(int id_module,int id_action)
{
	//if(db_check_right(module,action,_GetUID()))
	//{
//	Show();
	//Layout();
	//}
}
