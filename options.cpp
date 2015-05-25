#include "conf.h"
#include "options.h"

wxColor m_BGColor;
wxColor m_FGColor;
wxString m_DBHost;
wxString m_DBUser;
wxString m_DBPassword;
wxString m_DBName;
int m_DBPort = DEFAULT_MYSQL_PORT;
float m_UpperTreshold = DEFAULT_UPPER_TRESHOLD;
float m_LowerTreshold = DEFAULT_LOWER_TRESHOLD;

//SET
void SetFGColor(wxColor v)			{	m_FGColor = v;		}
void SetBGColor(wxColor v)			{	m_BGColor = v;		}
void SetDBHost(wxString v)			{	m_DBHost = v;		}
void SetDBUser(wxString v)			{	m_DBUser = v;		}
void SetDBPassword(wxString v)		{	m_DBPassword = v;	}
void SetDBName(wxString v)			{	m_DBName = v;		}
void SetDBPort(int v)				{	m_DBPort = v;		}
void SetUpperTreshold(float v)		{	m_UpperTreshold = v;}
void SetLowerTreshold(float v)		{	m_LowerTreshold = v;}

//GET
wxColor GetBGColor()			{	return m_BGColor;		}
wxColor GetFGColor()			{	return m_FGColor;		}
wxString GetDBHost()			{	return m_DBHost;		}
wxString GetDBUser()			{	return m_DBUser;		}
wxString GetDBPassword()		{	return m_DBPassword;	}
wxString GetDBName()			{	return m_DBName;		}
int GetDBPort()					{	return m_DBPort;		}
float GetUpperTreshold()		{	return m_UpperTreshold;	}
float GetLowerTreshold()		{	return m_LowerTreshold;	}


