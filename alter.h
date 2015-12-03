#ifndef __ALTER
#define __ALTER

#include "conf.h"

class CAlter
{	
	wxTextCtrl *m_Log;
	void DoLog(wxString str);
	void ClearLog();

public:

	CAlter();
	
	int GetSQLVersion();
	bool Alter(const char *pwd, const char *db_name);
	void SetLogCtrl(wxTextCtrl *ptr);

};



#endif