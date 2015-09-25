#include <wx/wx.h>
#include "conf.h"
#include "export.h"
#include "tools.h"
#include "db.h"

void ExportAlarm(void *db,wxString from, wxString to)
{	
	char **row;
	wxDateTime dt = wxDateTime::Now();
	wxString export_dir = wxString::Format(_("%s\\%s"),GetProgramDir(),DEFAULT_EXPORT_DIRECTORY);
	wxMkDir(export_dir);

	wxString fname = wxString::Format(_("%s\\alarm_%d_%02d_%02d.csv"),export_dir,dt.GetYear(),dt.GetMonth(),dt.GetDay());
	FILE *f = fopen(fname.mb_str(wxConvUTF8),"wb");
	
	if(f == NULL)
	{
		wxMessageBox(_(wxString::Format(_("%s %s"),GetMsg(MSG_ERROR_WRITING_FILE),fname)));
		return;
	}
	
	int counter = 0;
	

	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE set_local_utc_time BETWEEN '%s' AND '%s' ORDER BY symbol_name"),VIEW_ALARM,from,to);
	my_query(db,sql);
	
	void *result = db_result(db);

	while(row = (char**)db_fetch_row(result))
	{
		fprintf(f,"%s,%s,%s,%s,%s\r\n",row[FI_VIEW_ALARM_SYMBOL_NAME],row[FI_VIEW_ALARM_ALARM_NAME],row[FI_VIEW_ALARM_USER_FIRST_NAME],row[FI_VIEW_ALARM_USER_LAST_NAME],row[FI_VIEW_ALARM_SET_LOCAL_UTC_TIME]);
		counter++;
	}

	fclose(f);
	
	if(counter == 0)
	{
		wxMessageBox(GetMsg(MSG_NO_DATA));
		wxRemove(fname);
	
	}else{
	
		wxMessageBox(wxString::Format(_("%s: %s"),GetMsg(MSG_EXPORTED_TO_FILE),fname));
		wxSystem(wxString::Format(_("explorer %s"),fname));
	 
	}
}
