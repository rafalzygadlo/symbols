#include "conf.h"
#include "options.h"

wxColor m_BGColor;
wxColor m_FGColor;
wxString m_DBHost;
wxString m_DBUser;
wxString m_DBPassword;
wxString m_DBName;
wxString m_SearchText;
wxString m_SortColumn = FN_SYMBOL_NAME;
int m_DBPort = DEFAULT_MYSQL_PORT;
float m_UpperTreshold = DEFAULT_UPPER_TRESHOLD;
float m_LowerTreshold = DEFAULT_LOWER_TRESHOLD;
bool m_Exit = false;
bool m_SearchTextChanged = false;
bool m_SortOrder = false;
bool m_SortChanged = false;
int m_SortColumnId = 0;

int m_SelectedAreaId = 0;
int	m_SelectedSeawayId = 0;
int m_SelectedSymbolTypeId = 0;

//SET
void SetFGColor(wxColor v)				{	m_FGColor = v;			}
void SetBGColor(wxColor v)				{	m_BGColor = v;			}
void SetDBHost(wxString v)				{	m_DBHost = v;			}
void SetDBUser(wxString v)				{	m_DBUser = v;			}
void SetDBPassword(wxString v)			{	m_DBPassword = v;		}
void SetDBName(wxString v)				{	m_DBName = v;			}
void SetDBPort(int v)					{	m_DBPort = v;			}
void SetUpperTreshold(float v)			{	m_UpperTreshold = v;	}
void SetLowerTreshold(float v)			{	m_LowerTreshold = v;	}
void SetExit(bool v)					{	m_Exit = v;				}
void SetSearchTextChanged(bool v)		{	m_SearchTextChanged = v;}
void SetSearchText(wxString v)			{	m_SearchText = v;		}
void SetSortColumnId(int v)				{	m_SortColumnId = v;		}
void SetSortOrder(bool v)				{	m_SortOrder = v;		}
void SetSortChanged(bool v)				{	m_SortChanged = v;		}
void SetSortColumn(wxString v)			{	m_SortColumn = v;		}
//filter
void SetSelectedAreaId(int v)			{	m_SelectedAreaId = v;		}
void SetSelectedSeawayId(int v)			{	m_SelectedSeawayId = v;		}
void SetSelectedSymbolTypeId(int v)		{	m_SelectedSymbolTypeId = v;	}


//GET
wxColor GetBGColor()			{	return m_BGColor;			}
wxColor GetFGColor()			{	return m_FGColor;			}
wxString GetDBHost()			{	return m_DBHost;			}
wxString GetDBUser()			{	return m_DBUser;			}
wxString GetDBPassword()		{	return m_DBPassword;		}
wxString GetDBName()			{	return m_DBName;			}
wxString GetSearchText()		{	return m_SearchText;		}
wxString GetSortColumn()		{	return m_SortColumn;		}
int GetDBPort()					{	return m_DBPort;			}
float GetUpperTreshold()		{	return m_UpperTreshold;		}
float GetLowerTreshold()		{	return m_LowerTreshold;		}
bool GetExit()					{	return m_Exit;				}
bool GetSearchTextChanged()		{	return m_SearchTextChanged;	}
int GetSortColumnId()			{	return m_SortColumnId;		}
bool GetSortOrder()				{	return m_SortOrder;			}
bool GetSortChanged()			{	return m_SortChanged;		}
//filter
int GetSelectedAreaId()			{	return m_SelectedAreaId;		}
int GetSelectedSeawayId()		{	return m_SelectedSeawayId;		}
int GetSelectedSymbolTypeId()	{	return m_SelectedSymbolTypeId;	}