#ifndef __OPTIONS
#define __OPTIONS
#include <wx/wx.h>
#include "geometryconfig.h"

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
//filter
int GetSelectedAreaId();
int GetSelectedSeawayId();
int GetSelectedSymbolTypeId();
int GetSelectedGroupId();
//
int GetInMonitoring();
int GetFilterChanged();
float GetFontSize();
int GetViewFontScale();
bool GetShowFontNames();
int GetCommTimeout();
int GetRestrictedArea();
int GetScaleFactor();
int GetOffPositionArea();

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


//filter
void SetSelectedAreaId(int v);
void SetSelectedSeawayId(int v);
void SetSelectedSymbolTypeId(int v);
void SetInMonitoring(int v);
void SetFilterChanged(bool v);
void SetSelectedGroupId(int v);



//COLORS
nvRGBA GetDefaultColor(int type);
nvRGBA GetColor(int type);
int GetAlpha(int type);

void SetColor(int type, nvRGBA color);
void SetAlpha(int type, int value);



#endif

