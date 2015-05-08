#ifndef __TOOLS_H
#define __TOOLS_H

#include <wx/wx.h>
#include "nvtime.h"

wxMutex *GetMutex();
void FreeMutex();
const wchar_t *GetMsg(int id);
void SetLangId(int id);
wxString ConvertDegree(double degree,int type);
wxString FormatLongitude(double x,int type); 
wxString FormatLatitude(double y,int type);
double nvDistance(double lon1, double lat1, double lon2, double lat2, int distanceunit);
void nvMidPoint(double lon1, double lat1,double lon2, double lat2, double *v1, double *v2);
//double nvToRad( double degree );
void nvPointOfIntersection(double a1, double b1,double a2, double b2, double *x, double *y);
wxString GetDistanceUnit(size_t id);
wxString GetDistanceName(size_t id);
wxString GetProductInfo();
wxString GetProductName();
bool _SetLat(char *text, double *val, int type);
bool _SetLon(char *text, double *val, int type);
bool _SetLat(char *text, double *val);
bool _SetLon(char *text, double *val);
bool _SetLatSec(char *text, double *val);
bool _SetLonSec(char *text, double *val);
wxString GetWorkDir();
wxString GetConfigFile();
int _GetUID();
void _SetUID(int uid);
void SetLanguageId(int id);
int GetLanguageId();
wxString Convert(char *v);
wxListBox *GetFilterList(void *db,wxWindow *Parent, int wid);
wxComboBox *GetFilterCombo(wxWindow *Parent, int wid);
wxComboBox *GetCombo(void *db,wxWindow *Parent, wxString table , wxString sel,int field_id, int field_name, bool all = false);
wxString GetFontPath();
const wchar_t *GetDegreeFormat(int id, int dir);
void db_history(int uid, const char *module, const char *action );
bool db_check_right(const char *module, const char *action, int uid);
bool my_query(void *db,wxString sql);
bool my_query(void *db,const char *sql, unsigned long length);
void *DBConnect();
void DBClose(void *db);
double GetMilesPerDegree(double x, double y);
void SetDBCommand(wxString cmd);
const char *GetCommand(int id);
wxString GetOnOff(int v);
wxString GetNvDateTime(nvtime_t v);
wxString GetNvDate(nvtime_t v);
wxString GetNvTime(nvtime_t v);
//COMMANDS
void SetCommandForcedOff(int SBMSID, int id_base_station, bool off);
#endif

