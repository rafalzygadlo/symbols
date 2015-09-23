#include <wx/wx.h>
#include "conf.h"
#include "export.h"
#include "tools.h"
#include "db.h"

void ExportAlarm(void *db)
{
	wxString sql = wxString::Format(_("SELECT * FROM `%s` ORDER BY symbol_name"),VIEW_ALARM);
	my_query(db,sql);
	
	void *result = db_result(db);
			
	char **row;
	wxString fname = wxString::Format(_("%s/alarm.csv"),GetWorkDir());
	FILE *f = fopen(fname.mb_str(wxConvUTF8),"wb");
	
	if(f == NULL)
		wxMessageBox(_("errr"));
	
	while(row = (char**)db_fetch_row(result))
	{
		fprintf(f,"%s,%s,%s,%s,%s\r\n",row[FI_VIEW_ALARM_SYMBOL_NAME],row[FI_VIEW_ALARM_ALARM_NAME],row[FI_VIEW_ALARM_USER_FIRST_NAME],row[FI_VIEW_ALARM_USER_LAST_NAME],row[FI_VIEW_ALARM_SET_LOCAL_UTC_TIME]);	
	}

	fclose(f);
	wxMessageBox("Wyeksportowano");
}
