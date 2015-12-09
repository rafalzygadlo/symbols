#ifndef __SYMBOL_H
#define __SYMBOL_H

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
#include "alarm.h"
#include "alarmdialog.h"

class CGraphDialog;
class CAlarmDialog;
class CSymbol
{
	void *m_DB;
	nvCircle m_Circle;
	CNaviBroker *m_Broker;
	CNaviArray <SOnOff> m_OnList;
	CNaviArray <nvPoint3f> m_PosBuffer;
	CNaviArray <CAlarm*> m_AlarmList;

	CGraphDialog *m_GraphDialog;
	TTexture *m_TextureTGA_0;
	GLuint m_TextureID_0;
	bool m_FirstTime;
	int m_Step;
	bool m_Begin;
	int m_Id;
	int m_LightOn;
	bool m_BusyOn;
	bool m_Busy;
	bool m_Alarm;
	bool m_AlarmOn;
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
	int m_CommandTick;
	int	m_CommandTickOn;
	int m_PositionsTick;
	int m_ReportTick;
	int m_ReadTick;
	int m_CollisionTick;
	int m_AlarmTick,m_AlarmTickOn;
	int m_IdSBMS;
	int m_SBMSID;
	int m_IdBaseStation;
	bool m_RenderRestricted;
	bool m_Selected;
	int m_AlarmCount;
	int m_NewAlarmCount;
	int m_ReportCount;
	wxString m_Name;
	wxString m_Number;
	wxString m_SBMSName;
	wxString m_BaseStationName;
	wxString m_AgeString;
	wxString m_ChargingString;
	bool m_Exists;
	int m_ForcedOff;
	bool m_PhotoCellNightTime;
	int m_CommandCount;
	int m_MMSI;
	nvtime_t m_nvTime;
	int m_Timestamp;
	int m_Age;
	int m_Monitoring;
	bool m_NewReport;
	bool m_ValidGPS;
	bool m_NoSBMS;
	bool m_Init;
	bool m_Auto;
	float m_InputVolt;
	int m_Charging;
	int m_ProtocolVersion;
	nvFastFont *m_NameFont;
	
	CAlarm *AlarmExists(int id);
	void AlarmRemove();
	void SetAlarms();
	void ShowAlarm();
	void ClearAlarms();
	void ClearPositions();
	void SetColor(int id);
	void CreateSymbol(void *MemoryBlock,long MemoryBlockSize);
	void CreateTexture(TTexture *Texture, GLuint *TextureID);
	void CreateTextures(void);
	bool CheckCommand();
	bool CheckAlarm();
	bool CheckCollision();
	bool CheckReport();
	bool SetPositions();
	void SetValues();
	void SetSmoothScaleFactor(double v);
	//void Read();
	void SetSymbolColor();
	void RenderText(float x, float y, float vx, float vy, const wchar_t *format ...);
	void RenderSymbol();
	//void RenderLightOn();
	void RenderBusy();
	void RenderRestricted();
	void RenderAlarm();
	void RenderGPS();
	void RenderPositions();
	void RenderNewReport();
	void RenderNoSBMS();
	void RenderInfo();
					
public:

	CSymbol(CNaviBroker *broker);
	~CSymbol();

	void OnTick(void *db);
	void OnTickExit();
	void ShowGraph();
	void ShowManagement(CSymbol *v);

	//SET
	void SetId(int v);
	//pozycja referencyjna
	void SetRLon(double v);		void SetRLat(double v);		void SetRLonMap(double v);		void SetRLatMap(double v);
	//pozycja Gps
	void SetGpsLon(double v);	void SetGpsLat(double v);	void SetGpsLonMap(double v);	void SetGpsLatMap(double v);
	//referencyjna lub Gps
	void SetLon(double v);		void SetLat(double v);		void SetLonMap(double v);		void SetLatMap(double v);

	void SetIdSBMS(int v);
	void SetSBMSID(int v);
	void SetNumber(wxString v);
	void SetMonitoring(int v);
	void SetName(wxString v);
	void SetExists(bool v);
	void SetDB(void *db);
	void SetForcedOff(int v);
	void SetLightOn(int v);
	void SetPhotoCellNightTime(bool v);
	void SetMMSI(int v);
	void SetNvTime(nvtime_t dt);
	void SetTimestamp(int v);
	void SetAge(int v);
	void SetAge(wxString v);
	void SetNewReport(bool v);
	void SetSBMSName(wxString v);
	void SetNoSBMS(bool v);
	void SetAuto(bool v);
	void SetInputVolt(float v);
	void SetIdBaseStation(int v);
	void SetBaseStationName(wxString v);
	void SetValidGPS(bool v);
	void SetInit(bool v);
	void SetCharging(int v);
	void SetChargingAsString(wxString v);
	void SetNewAlarmCount(int v);
	void SetProtocolVersion(int v);
	void SetFont(nvFastFont *ptr);
	void SetBusy(bool v);
	void SetAlarm(bool v);
		

	//GET
	int GetId();
	int GetIdSBMS();
	int GetSBMSID();
	int GetBaseStationId();
	//pozycja referencyjna
	double GetRLon();	double GetRLat();	double GetRLonMap();	double GetRLatMap();
	//pozycja GPS
	double GetGpsLon();	double GetGpsLat();	double GetGpsLonMap();	double GetGpsLatMap();
	//referencyjna lub Gps
	double GetLon();	double GetLat();	double GetLonMap();	double GetLatMap();
	bool GetBusy();					//zajêty komendami
	int GetAlarmCount();
	wxString GetName();
	wxString GetNumber();
	wxString GetSBMSName();
	wxString GetBaseStationName();
	bool GetExists();
	int GetLightOn();
	int GetMMSI();
	nvtime_t GetNvTime();
	int GetAge();
	int GetMonitoring();
	bool GetInit();
	bool GetAuto();
	float GetInputVolt();
	int GetForcedOff();
	int GetAlarmId(int v);
	bool GetNoSBMS();
	int GetCharging();
	int GetNewAlarmCount();
	int GetProtocolVersion();
	CAlarm *GetAlarm(int v);
	wxString GetChargingAsString();
	wxString GetAlarmName(int v);
	wxString GetAgeAsString();
	wxString GetReportCountAsString();
	wxString GetCommandCountAsString();
	wxString GetInputVoltAsString();
	
	
	void Render();
	void RenderSelected();

};

#endif