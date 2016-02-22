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
float m_UpperThreshold = DEFAULT_UPPER_THRESHOLD;
float m_LowerThreshold = DEFAULT_LOWER_THRESHOLD;
bool m_Exit = false;
bool m_SearchTextChanged = false;
bool m_SortOrder = false;
bool m_SortChanged = false;
bool m_FilterChanged = false;
int m_SortColumnId = 0;
int m_SelectedAreaId = -1;
int	m_SelectedSeawayId = -1;
int m_SelectedSymbolTypeId = -1;
int m_SelectedBaseStationId = -1;
double m_FontSize = DEFAULT_FONT_SIZE;
int m_ViewFontScale = DEFAULT_VIEW_FONT_SCALE;
int m_CommTimeout = DEFAULT_COMM_TIMEOUT;
int m_Monitoring = -1;
int m_SelectedGroupId = -1;
int m_Light = -1;
int m_AlarmId = -1;
int m_ReportTimeout = DEFAULT_REPORT_TIMEOUT;

bool m_ShowFontNames = false;
int m_RestrictedArea = DEFAULT_RESTRICTED_AREA_RADIUS;
int m_OffPositionArea = DEFAULT_OFF_POSITION_AREA;
int m_ScaleFactor = DEFAULT_SCALE_FACTOR;
double m_SunLon = DEFAULT_SUN_LON;
double m_SunLat = DEFAULT_SUN_LAT;
bool m_Night = false;
bool m_PositionFromGps = false;
time_t m_NightTimeOn;
time_t m_NightTimeOff;
ISpVoice *m_Voice;

nvRGBA SymbolNormalColor = GetDefaultColor(SYMBOL_NORMAL_COLOR);
nvRGBA SymbolNoMonitorColor = GetDefaultColor(SYMBOL_NO_MONITOR_COLOR);
nvRGBA SymbolErrorColor = GetDefaultColor(SYMBOL_ERROR_COLOR);
nvRGBA SymbolLightOnColor = GetDefaultColor(SYMBOL_LIGHT_ON_COLOR);

//SET
void SetFGColor(wxColor v)				{	m_FGColor = v;			}
void SetBGColor(wxColor v)				{	m_BGColor = v;			}
void SetDBHost(wxString v)				{	m_DBHost = v;			}
void SetDBUser(wxString v)				{	m_DBUser = v;			}
void SetDBPassword(wxString v)			{	m_DBPassword = v;		}
void SetDBName(wxString v)				{	m_DBName = v;			}
void SetDBPort(int v)					{	m_DBPort = v;			}
void SetUpperThreshold(float v)			{	m_UpperThreshold = v;	}
void SetLowerThreshold(float v)			{	m_LowerThreshold = v;	}
void SetExit(bool v)					{	m_Exit = v;				}
void SetSearchTextChanged(bool v)		{	m_SearchTextChanged = v;}
void SetSearchText(wxString v)			{	m_SearchText = v;		}
void SetSortColumnId(int v)				{	m_SortColumnId = v;		}
void SetSortOrder(bool v)				{	m_SortOrder = v;		}
void SetSortChanged(bool v)				{	m_SortChanged = v;		}
void SetSortColumn(wxString v)			{	m_SortColumn = v;		}
void SetShowFontNames(bool v)			{	m_ShowFontNames = v;	}
void SetFontSize( float size)			{	m_FontSize = size/10;	}
void SetViewFontScale(int v)			{	m_ViewFontScale = v;	}
void SetCommTimeout(int v)				{	m_CommTimeout = v;		}
void SetScaleFactor(int v)				{	m_ScaleFactor = v;		}
void SetRestrictedArea(int v)			{	m_RestrictedArea = v;	}
void SetOffPositionArea(int v)			{	m_OffPositionArea = v;	}
void SetSunLon(double v)				{	m_SunLon = v;			}
void SetSunLat(double v)				{	m_SunLat = v;			}
void SetNightTimeOn(time_t v)			{	m_NightTimeOn = v;		}
void SetNightTimeOff(time_t v)			{	m_NightTimeOff = v;		}
void SetNight(bool v)					{	m_Night = v;			}
void SetVoice(ISpVoice *v)				{	m_Voice = v;			}
void SetPositionFromGps(bool v)			{	m_PositionFromGps = v;	}
void SetReportTimeout(int v)			{	m_ReportTimeout = v;	}


//filter
void SetSelectedAreaId(int v)			{	m_SelectedAreaId = v;		}
void SetSelectedSeawayId(int v)			{	m_SelectedSeawayId = v;		}
void SetSelectedSymbolTypeId(int v)		{	m_SelectedSymbolTypeId = v;	}
void SetSelectedBaseStationId(int v)	{	m_SelectedBaseStationId = v;}
void SetFilterChanged(bool v)			{	m_FilterChanged = v;		}
void SetMonitoring(int v)				{	m_Monitoring = v;			}
void SetSelectedGroupId(int v)			{	m_SelectedGroupId = v;		}
void SetLight(int v)					{	m_Light = v;				}
void SetSelectedAlarmId(int v)			{	m_AlarmId = v;				}


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
float GetUpperThreshold()		{	return m_UpperThreshold;	}
float GetLowerThreshold()		{	return m_LowerThreshold;	}
bool GetExit()					{	return m_Exit;				}
bool GetSearchTextChanged()		{	return m_SearchTextChanged;	}
int GetSortColumnId()			{	return m_SortColumnId;		}
bool GetSortOrder()				{	return m_SortOrder;			}
bool GetSortChanged()			{	return m_SortChanged;		}
float GetFontSize()				{	return m_FontSize;			}
int GetViewFontScale()			{	return m_ViewFontScale;		}
int GetCommTimeout()			{	return m_CommTimeout;		}
bool GetShowFontNames()			{	return m_ShowFontNames;		}
int GetRestrictedArea()			{	return m_RestrictedArea;	}
int GetScaleFactor()			{	return m_ScaleFactor;		}
int GetOffPositionArea()		{	return m_OffPositionArea;	}
double GetSunLon()				{	return m_SunLon;			}
double GetSunLat()				{	return m_SunLat;			}
bool GetNight()					{	return m_Night;				}
time_t GetNightTimeOn()			{	return m_NightTimeOn;		}
time_t GetNightTimeOff()		{	return m_NightTimeOff;		}
ISpVoice *GetVoice()			{	return m_Voice;				}
bool GetPositionFromGps()		{	return m_PositionFromGps;	}
int GetReportTimeout()			{	return m_ReportTimeout;		}


//filter
int GetSelectedAreaId()			{	return m_SelectedAreaId;		}
int GetSelectedSeawayId()		{	return m_SelectedSeawayId;		}
int GetSelectedSymbolTypeId()	{	return m_SelectedSymbolTypeId;	}
int GetSelectedBaseStationId()	{	return m_SelectedBaseStationId;	}
int GetFilterChanged()			{	return m_FilterChanged;			}
int GetMonitoring()				{	return m_Monitoring;			}
int GetSelectedGroupId()		{	return m_SelectedGroupId;		}
int GetLight()					{	return m_Light;					}
int GetSelectedAlarmId()		{	return m_AlarmId;				}


nvRGBA GetDefaultColor(int type)
{
	nvRGBA rgba;
	switch(type)
	{
		case SYMBOL_NORMAL_COLOR:			rgba.R = 0;		rgba.G = 0;		rgba.B = 255;	rgba.A = 200;	break;
		case SYMBOL_NO_MONITOR_COLOR:		rgba.R = 150;	rgba.G = 150;	rgba.B = 150;	rgba.A = 50;	break;
		case SYMBOL_ERROR_COLOR:			rgba.R = 255;	rgba.G = 0;		rgba.B = 0;		rgba.A = 100;	break;
		case SYMBOL_LIGHT_ON_COLOR:			rgba.R = 0;		rgba.G = 255;	rgba.B = 0;		rgba.A = 200;	break;
		case ALARM_WARNING_COLOR:			rgba.R = 0;		rgba.G = 0;		rgba.B = 255;	rgba.A = 255;	break;
		case ALARM_ALARM_COLOR:				rgba.R = 255;	rgba.G = 0;		rgba.B = 0;		rgba.A = 255;	break;
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