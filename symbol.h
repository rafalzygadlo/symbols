#ifndef __SYMBOL
#define __SYMBOL

#include <wx/html/htmlwin.h>
#include "ticker.h"
#include <gl/gl.h>
#include "navibroker.h"
#include "tgamem.h"
#include "picture.h"
#include "geometrytools.h"
#include "nvfastfont.h"
#include "nvtime.h"
#include "graphdialog.h"
#include "alarmmodel.h"
#include "alarmdialog.h"
#include "driver.h"

class CGraphDialog;
class CAlarmDialog;
class CSymbol
{
	void *m_DB;
	nvCircle m_Circle;
	CNaviBroker *m_Broker;
	CNaviArray <CDriver*> m_DriverList;
	
	bool m_Exists;
	bool m_Render;
	int m_Id;
	//pozycja referencyjna
	double m_RLon, m_RLat, m_RLonMap, m_RLatMap;
	//pozycja GPS
	double m_GpsLon, m_GpsLat, m_GpsLonMap, m_GpsLatMap;
	//pozycja gps lub referencyjna
	double m_Lon, m_Lat, m_LonMap, m_LatMap;

	double m_Scale;
	double m_SmoothScaleFactor;
	double m_RectWidth;
	double m_RectHeight;
	double m_TranslationX;
	double m_TranslationY;
	double m_VisibleMap[4];
	bool m_TickExit;
	
	bool m_Selected;
	wxString m_Name;
	wxString m_Number;
	int m_Monitoring;
	nvFastFont *m_NameFont;
	
	
	void SetColor(int id);
	void SetValues();
	void SetSmoothScaleFactor(double v);
	//void SetSymbolColor();
	void RenderSymbol();
	void RenderRestricted();
	void RenderDriver();
	void RenderText();
	void RenderText(float x, float y, float vx, float vy, const wchar_t *format ...);	


public:

	CSymbol(CNaviBroker *broker);
	~CSymbol();

	void OnTick(void *db);
	void OnTickExit();
	void AddDriver(CDriver *ptr);
	CDriver *ExistsDriver(int id,int type);
	void RenderSelected();
	void Render();
	void Read(void *db);
	
	//SET
	void SetId(int v);
	//pozycja referencyjna
	void SetRLon(double v);
	void SetRLat(double v);
	void SetRLonMap(double v);
	void SetRLatMap(double v);
	void UnsetNewReport();
	
	//pozycja Gps
	void SetGpsLon(double v);
	void SetGpsLat(double v);
	void SetGpsLonMap(double v);
	void SetGpsLatMap(double v);
	
	//referencyjna lub Gps
	void SetLon(double v);
	void SetLat(double v);
	void SetLonMap(double v);
	void SetLatMap(double v);
		
	void SetNumber(wxString v);
	void SetName(wxString v);
	void SetDB(void *db);
	void SetFont(nvFastFont *ptr);
	void SetExists(bool v);
	void SetMonitoring(int v);
				
	//GET
	//pozycja referencyjna
	double GetRLon();
	double GetRLat();
	double GetRLonMap();
	double GetRLatMap();
	
	//pozycja GPS
	double GetGpsLon();
	double GetGpsLat();
	double GetGpsLonMap();
	double GetGpsLatMap();
	
	//referencyjna lub Gps
	double GetLon();
	double GetLat();
	double GetLonMap();
	double GetLatMap();
	
	int GetId();
	wxString GetName();
	wxString GetNumber();
	wxString GetHtml(int v);
	wxString GetFullHtml();
	int GetMonitoring();
	int GetDriverCount();
	bool GetExists();
	CDriver *GetDriver(int v);
		
	void RemoveDriver(CDriver *ptr);
	
	
	
};

#endif