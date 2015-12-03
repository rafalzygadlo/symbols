#include <wx/wx.h>
#include "alter.h"
#include "db.h"
#include "options.h"
#include "tools.h"
#include "conf.h"

SAlter AlterSQL[] =
{
	#include DB_ALTER
	{-1,""},

};

CAlter::CAlter()
{
	m_Log = NULL;
}

void CAlter::SetLogCtrl(wxTextCtrl *ptr)
{
	m_Log = ptr;
}

void CAlter::DoLog(wxString str)
{
	m_Log->AppendText(str);
}

void CAlter::ClearLog()
{
	m_Log->Clear();
}

int CAlter::GetSQLVersion()
{
	int version = 0;
	int i = 0;
	
	while(AlterSQL[i].version != -1)
	{
		int _version = AlterSQL[i].version;
		if(_version > version)
			version = _version;
		i++;
	}

	return version;
}

bool CAlter::Alter(const char *pwd, const char *db_name)
{
	ClearLog();
	void *db = NULL;
	db = db_init(db);

	if(!db_connect(db,GetDBHost(),"root",pwd,GetDBName(),GetDBPort()))
	{
		DoLog(GetMsg(MSG_DB_CONNECT_ERROR));
		return false;
	}
	
	db_select(db,db_name);
	int err = db_errno(db);
	if(err !=0)
		return false;
    
	db_query(db,"SET NAMES utf8  COLLATE utf_polish_ci");
	
	int i = 0;
	int _version = GetDBVersion(db);
	int _errno = 0;
	bool result = true;
	
	while( AlterSQL[i].version != -1 )
	{
		if(AlterSQL[i].version > _version)
		{
			if(db_query(db,AlterSQL[i].sql) == 0)
			{
				DoLog(wxString::Format(_("[OK]\t%s\r\n"),AlterSQL[i].sql));
			}else{
		
				DoLog(wxString::Format(_("[ERROR]\t%s %s\r\n"),AlterSQL[i].sql,db_error(db)));
				result = false;
			}

		}
		
		i++;
	}
		
	db_close(db);
	return result;
}
