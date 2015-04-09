#include "conf.h"
#include "options.h"

wxColor m_BGColor;
wxColor m_FGColor;
wxString m_DBHost;
wxString m_DBUser;
wxString m_DBPassword;
wxString m_DBName;
int m_DBPort = DEFAULT_MYSQL_PORT;


//SET
void SetFGColor(wxColor v)			{	m_FGColor = v;		}
void SetBGColor(wxColor v)			{	m_BGColor = v;		}
void SetDBHost(wxString v)			{	m_DBHost = v;		}
void SetDBUser(wxString v)			{	m_DBUser = v;		}
void SetDBPassword(wxString v)		{	m_DBPassword = v;	}
void SetDBName(wxString v)			{	m_DBName = v;		}
void SetDBPort(int v)				{	m_DBPort = v;		}


//GET
wxColor GetBGColor()			{	return m_BGColor;		}
wxColor GetFGColor()			{	return m_FGColor;		}
wxString GetDBHost()			{	return m_DBHost;		}
wxString GetDBUser()			{	return m_DBUser;		}
wxString GetDBPassword()		{	return m_DBPassword;	}
wxString GetDBName()			{	return m_DBName;		}
int GetDBPort()					{	return m_DBPort;		}


