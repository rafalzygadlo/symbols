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
	wxDateTime dt = wxDateTime::Now();
	wxString fname = wxString::Format(_("%s\\%s\\alarm_%d_%d_%d.csv"),GetWorkDir(),DEFAULT_EXPORT_DIRECTORY,dt.GetYear(),dt.GetMonth(),dt.GetDay());
	FILE *f = fopen(fname.mb_str(wxConvUTF8),"wb");
	
	if(f == NULL)
	{
		wxMessageBox(_(wxString::Format(_("%s %s"),GetMsg(MSG_ERROR_WRITING_FILE),fname)));
		return;
	}
	
	while(row = (char**)db_fetch_row(result))
	{
		fprintf(f,"%s,%s,%s,%s,%s\r\n",row[FI_VIEW_ALARM_SYMBOL_NAME],row[FI_VIEW_ALARM_ALARM_NAME],row[FI_VIEW_ALARM_USER_FIRST_NAME],row[FI_VIEW_ALARM_USER_LAST_NAME],row[FI_VIEW_ALARM_SET_LOCAL_UTC_TIME]);
	}

	fclose(f);
	
	wxMessageBox(wxString::Format(_("%s: %s"),GetMsg(MSG_EXPORTED_TO_FILE),fname));

}
