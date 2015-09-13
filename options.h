#ifndef __OPTIONS
#define __OPTIONS
#include <wx/wx.h>
#include <stdint.h>
#include <sapi.h>
#include "geometryconfig.h"
#include "nvtime.h"


#define DEFAULT_FG_COLOR wxColor(230,230,230)
#define DEFAULT_BG_COLOR wxColor(50,50,50)

//GET
wxColor GetBGColor();
wxColor GetFGColor();
wxString GetDBHost();
wxString GetDBUser();
wxString GetDBPassword();
wxString GetDBName();
wxString GetSearchText();
wxString GetSortColumn();
int GetDBPort();
float GetUpperThreshold();
float GetLowerThreshold();
bool GetExit();
bool GetSearchTextChanged();
int GetSortColumnId();
bool GetSortOrder();
bool GetSortChanged();
float GetFontSize();
int GetViewFontScale();
bool GetShowFontNames();
int GetCommTimeout();
int GetRestrictedArea();
int GetScaleFactor();
int GetOffPositionArea();
double GetSunLon();
double GetSunLat();
time_t GetNightTimeOn();
time_t GetNightTimeOff();
nvtime_t GetNightNvTimeOn();
nvtime_t GetNightNvTimeOff();
bool GetNight();
bool GetPositionFromGps();
ISpVoice *GetVoice();

//filter............................
int GetSelectedAreaId();
int GetSelectedSeawayId();
int GetSelectedSymbolTypeId();
int GetSelectedGroupId();
int GetInMonitoring();
int GetFilterChanged();
int GetLight();
int GetSelectedBaseStationId();
int GetSelectedAlarmId();
//..................................


//SET
void SetFGColor(wxColor v);
void SetBGColor(wxColor v);
void SetDBHost(wxString v);
void SetDBUser(wxString v);
void SetDBPassword(wxString v);
void SetDBName(wxString v);
void SetDBPort(int v);
void SetUpperThreshold(float v);
void SetLowerThreshold(float v);
void SetExit(bool v);
void SetSearchTextChanged(bool v);
void SetSearchText(wxString v);
void SetSortColumnId(int v);
void SetSortOrder(bool v);
void SetSortColumn(wxString v);
void SetSortChanged(bool v);
void SetShowFontNames(bool v);
void SetRectrictedArea(int v);
void SetScaleFactor(int v);
void SetRestrictedArea(int v);
void SetFontSize(float v);
void SetViewFontScale(int v);
void SetCommTimeout(int v);
void SetOffPositionArea(int v);
void SetSunLat(double v);
void SetSunLon(double v);
void SetNightTimeOn(time_t v);
void SetNightTimeOff(time_t v);
void SetNightNvTimeOn(nvtime_t v);
void SetNightNvTimeOff(nvtime_t v);
void SetNight(bool v);
void SetPositionFromGps(bool v);
void SetVoice(ISpVoice *v);


//filter.................................
void SetSelectedAreaId(int v);
void SetSelectedSeawayId(int v);
void SetSelectedSymbolTypeId(int v);
void SetInMonitoring(int v);
void SetFilterChanged(bool v);
void SetSelectedGroupId(int v);
void SetSelectedBaseStationId(int v);
void SetLight(int v);
void SetSelectedAlarmId(int v);
//........................................

//COLORS
nvRGBA GetDefaultColor(int type);
nvRGBA GetColor(int type);
int GetAlpha(int type);

void SetColor(int type, nvRGBA color);
void SetAlpha(int type, int value);



#endif

