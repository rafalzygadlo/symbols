#include "control.h"
#include "conf.h"
#include "db.h"
#include "tools.h"

BEGIN_EVENT_TABLE(CMenu,wxMenu)
	EVT_MENU(wxID_ANY,OnMenu)
END_EVENT_TABLE();

CMenu::CMenu()
	:wxMenu()
{
		
}

void CMenu::CheckRight(const char *module,const char *action, wxMenuItem *item)
{
	item->Enable(false);
	if(db_check_right(module,action,_GetUID()))
		item->Enable(true);
}

void CMenu::CheckRight(int id_module,int id_action, wxMenuItem *item)
{
	item->Enable(true);
	//if(db_check_right(module,action,_GetUID()))
	//{
	//Show();
	//Layout();
	//}
}

void CMenu::OnMenu(wxCommandEvent &event)
{
	fprintf(stderr,"ID:%d\n",event.GetId());
	event.Skip();
}


CPanel::CPanel(wxWindow *parent)
	:wxPanel(parent,wxID_ANY,wxDefaultPosition,wxDefaultSize)
{
	Hide();
}


void CPanel::CheckRight(const char *module,const char *action)
{
	if(db_check_right(module,action,_GetUID()))
	{
		Show();
	}
}


void CPanel::CheckRight(int id_module,int id_action)
{
	//if(db_check_right(module,action,_GetUID()))
	//{
	Show();
		//Layout();
	//}
}
