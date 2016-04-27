#include <wx/wx.h>
#include "alarm.h"
#include "tools.h"
#include "db.h"


CAlarm::CAlarm()
{
	
}

//SET
void CAlarm::ClearAll(int id_sbms)
{
	wxString sql = wxString::Format(_("UPDATE `%s` SET active='%d' WHERE id_sbms='%d'"),TABLE_SBMS_ALARM,ALARM_NOT_ACTIVE,id_sbms);
	void *db = DBConnect();
	my_query(db,sql);
	DBClose(db);
}
