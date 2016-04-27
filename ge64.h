#ifndef __GE64
#define __GE64

#include <gl/gl.h>
#include "geometrytools.h"
#include "nvfastfont.h"
#include "driver.h"
#include "navibroker.h"
#include "alarmmodel.h"
#include "list.h"

class CGE64 :public CDriver
{
	CNaviBroker *m_Broker;
	void *m_DB;
	bool m_NightMode;
	bool m_MainLampOn;
	bool m_SecondLampOn;
	bool m_GeneratorOn;
	bool m_ManualOn;
	double m_Scale;
	double m_SmoothScaleFactor;
	double m_VisibleMap[4];
	double m_RectWidth;
	double m_RectHeight;
	double m_TranslationX;
	double m_TranslationY;
	bool m_AlarmOn;
	bool m_Alarm;
	bool m_BusyOn;
	bool m_Busy;
	int m_CommandCount;
	nvFastFont *m_NameFont;
	
	//pozycja referencyjna
	double m_RLon, m_RLat, m_RLonMap, m_RLatMap;
	//pozycja GPS
	double m_GpsLon, m_GpsLat, m_GpsLonMap, m_GpsLatMap;
	//pozycja gps lub referencyjna
	double m_Lon, m_Lat, m_LonMap, m_LatMap;
	
	CList m_AlarmList;
		
	bool CheckAlarm();
	bool CheckCommand();
		
	void SetSmoothScaleFactor(double v);
	void SetValues();
	void SetColor(int id);
	void SetSymbolColor();
	
	void RenderAlarm();
	void RenderBusy();
	void RenderGE64();
	void RenderText(float x, float y, float vx, float vy, const wchar_t *format ...);
	void RenderText();
	void Render() override;
	
public:

	CGE64(void *db,CNaviBroker *broker);
	~CGE64();

	void ShowAction() override;
	void Read() override;
	
	//GET
	bool GetNightMode();
	bool GetMainLampOn();
	bool GetSecondLampOn();
	bool GetGeneratorOn();
	bool GetManualOn();
	int GetAlarmCount();
	bool GetBusy();
	CAlarmModel *GetAlarm(int v);
	wxString GetCommandCountAsString();
	wxString GetDriverHtml(int v) override;
	wxString GetDriverFullHtml() override;
	wxString GetAlarmHtml() override;

	double GetGpsLon() override;
	double GetGpsLat() override;
	double GetGpsLonMap() override;
	double GetGpsLatMap() override;
	//referencyjna lub Gps
	//double GetLon() override;	
	//double GetLat() override;	
	//double GetLonMap() override;	
	//double GetLatMap() override;
	
	
	//SET
	void SetNightMode(bool v);
	void SetMainOn(bool v);
	void SetSecondLampOn(bool v);
	void SetGeneratorOn(bool v);
	void SetManualOn(bool v);
	
	void SetGpsLon(double v) override;
	void SetGpsLat(double v) override;
	void SetGpsLonMap(double v) override;
	void SetGpsLatMap(double v) override;
	
	//referencyjna lub Gps
	void SetLon(double v) override;
	void SetLat(double v) override;
	void SetLonMap(double v) override;
	void SetLatMap(double v) override;
	
	void SetFont(nvFastFont *v) override;

	//akcje
	void LightOn();
	void LightOff();
	
};

#endif