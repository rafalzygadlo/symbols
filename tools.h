#ifndef __TOOLS_H
#define __TOOLS_H

#include <wx/wx.h>

wxMutex *GetMutex();
void FreeMutex();
const wchar_t *GetMsg(int id);
void SetLangId(int id);
wxString ConvertDegree(float degree);
wxString FormatLongitude(float x); 
wxString FormatLatitude(float y);
double nvDistance(double lon1, double lat1, double lon2, double lat2, int distanceunit);
void nvMidPoint(double lon1, double lat1,double lon2, double lat2, double *v1, double *v2);
double nvToRad( double degree );
void nvPointOfIntersection(double a1, double b1,double a2, double b2, double *x, double *y);
wxString GetDistanceUnit(size_t id);
wxString GetDistanceName(size_t id);
wxString GetProductInfo();
wxString GetProductName();
bool SetLat(char *text, float *val);
bool SetLon(char *text, float *val);
wxString GetWorkDir();
wxString GetConfigFile();
int _GetUID();
void _SetUID(int uid);
void SetLanguageId(int id);
int GetLanguageId();
wxString Convert(char *v);

#endif

