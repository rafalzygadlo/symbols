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
bool m_FilterChanged = false;
int m_SortColumnId = 0;
int m_SelectedAreaId = 0;
int	m_SelectedSeawayId = 0;
int m_SelectedSymbolTypeId = 0;
double m_FontSize = DEFAULT_FONT_SIZE;
int m_ViewFontScale = DEFAULT_VIEW_FONT_SCALE;
int m_CommTimeout = DEFAULT_COMM_TIMEOUT;
bool m_InMonitoring = false;
nvRGBA SymbolNormalColor, SymbolNoMonitorColor, SymbolErrorColor, SymbolLightOnColor;

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
void SetFilterChanged(bool v)			{	m_FilterChanged = v;		}
void SetFontSize( float size)			{	m_FontSize = size/10;		}
void SetViewFontScale(int v)			{	m_ViewFontScale = v;		}
void SetCommTimeout(int v)				{	m_CommTimeout = v;			}

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
float GetFontSize()				{	return m_FontSize;			}
int GetViewFontScale()			{	return m_ViewFontScale;		}
int GetCommTimeout()			{	return m_CommTimeout;		}


//filter
int GetSelectedAreaId()			{	return m_SelectedAreaId;		}
int GetSelectedSeawayId()		{	return m_SelectedSeawayId;		}
int GetSelectedSymbolTypeId()	{	return m_SelectedSymbolTypeId;	}
int GetFilterChanged()			{	return m_FilterChanged;			}
bool GetInMonitoring()			{	return m_InMonitoring;			}


nvRGBA GetDefaultColor(int type)
{
	nvRGBA rgba;
	switch(type)
	{
		case SYMBOL_NORMAL_COLOR:			rgba.R = 0;		rgba.G = 0;		rgba.B = 255;	rgba.A = 200;	break;
		case SYMBOL_NO_MONITOR_COLOR:		rgba.R = 0;		rgba.G = 0;		rgba.B = 255;	rgba.A = 50;	break;
		case SYMBOL_ERROR_COLOR:			rgba.R = 255;	rgba.G = 0;		rgba.B = 0;		rgba.A = 100;	break;
		case SYMBOL_LIGHT_ON_COLOR:			rgba.R = 0;		rgba.G = 255;	rgba.B = 0;		rgba.A = 200;	break;
	}
		
	return rgba;
}

nvRGBA GetColor(int type)
{
	nvRGBA rgba;
	switch(type)
	{
		case SYMBOL_NORMAL_COLOR:		rgba.R = SymbolNormalColor.R;		rgba.G = SymbolNormalColor.G;		rgba.B = SymbolNormalColor.B;		rgba.A = SymbolNormalColor.A;		break;
		case SYMBOL_NO_MONITOR_COLOR:	rgba.R = SymbolNoMonitorColor.R;	rgba.G = SymbolNoMonitorColor.G;	rgba.B = SymbolNoMonitorColor.B;	rgba.A = SymbolNoMonitorColor.A;	break;
		case SYMBOL_ERROR_COLOR:		rgba.R = SymbolErrorColor.R;		rgba.G = SymbolErrorColor.G;		rgba.B = SymbolErrorColor.B;		rgba.A = SymbolErrorColor.A;		break;
		case SYMBOL_LIGHT_ON_COLOR:		rgba.R = SymbolLightOnColor.R;		rgba.G = SymbolLightOnColor.G;		rgba.B = SymbolLightOnColor.B;		rgba.A = SymbolLightOnColor.A;		break;
		
	}
		
	return rgba;
}

void SetColor(int type, nvRGBA color)
{
	switch(type)
	{
		case SYMBOL_NORMAL_COLOR:		SymbolNormalColor.R = color.R;		SymbolNormalColor.G = color.G;		SymbolNormalColor.B = color.B;		SymbolNormalColor.A = color.A;		break;	
		case SYMBOL_NO_MONITOR_COLOR:	SymbolNoMonitorColor.R = color.R;	SymbolNoMonitorColor.G = color.G;	SymbolNoMonitorColor.B = color.B;	SymbolNoMonitorColor.A = color.A;	break;
		case SYMBOL_ERROR_COLOR:		SymbolErrorColor.R = color.R;		SymbolErrorColor.G = color.G;		SymbolErrorColor.B = color.B;		SymbolErrorColor.A = color.A;		break;
		case SYMBOL_LIGHT_ON_COLOR:		SymbolLightOnColor.R = color.R;		SymbolLightOnColor.G = color.G;		SymbolLightOnColor.B = color.B;		SymbolLightOnColor.A = color.A;		break;

		
	}

}

void SetAlpha(int type, int value)
{
	switch(type)
	{
		case SYMBOL_NORMAL_COLOR:			SymbolNormalColor.A = value;	break;
		case SYMBOL_NO_MONITOR_COLOR:		SymbolNoMonitorColor.A = value;	break;
		case SYMBOL_ERROR_COLOR:			SymbolErrorColor.A = value;		break;
		case SYMBOL_LIGHT_ON_COLOR:			SymbolLightOnColor.A = value;	break;
		
	}

}

int GetAlpha(int type)
{
	int alpha = 0;
	switch(type)
	{
		case SYMBOL_NORMAL_COLOR:			alpha = SymbolNormalColor.A;	break;
		case SYMBOL_NO_MONITOR_COLOR:		alpha = SymbolNoMonitorColor.A;	break;
		case SYMBOL_ERROR_COLOR:			alpha = SymbolErrorColor.A;		break;
		case SYMBOL_LIGHT_ON_COLOR:			alpha = SymbolLightOnColor.A;	break;
		
	}

	return alpha;
}