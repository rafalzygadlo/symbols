#ifndef __SBMS
#define __SBMS

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
#include "sbmsactiondialog.h"
#include "sbmspanel.h"
#include "driver.h"
#include "commandmodel.h"
#include "command.h"
#include "alarm.h"

class CSBMSActionDialog;
class CCommand;
class CSBMS :public CDriver
{
	void *m_DB;
	nvCircle m_Circle;
	CNaviBroker *m_Broker;
	CNaviArray <SOnOff> m_OnList;
	CNaviArray <nvPoint3f> m_PosBuffer;
	CNaviArray <CAlarmModel*> m_AlarmList;
	CNaviArray <CCommandModel*> m_CommandList;
		
	CSBMSActionDialog *m_SBMSActionDialog;
	CCommand *m_Command;
	CAlarm *m_Alarm;
	CGraphDialog *m_GraphDialog;
	TTexture *m_TextureTGA_0;
	GLuint m_TextureID_0;
	bool m_FirstTime;
	bool m_Begin;
	int m_LightOn;
	bool m_BusyOn;
	bool m_Busy;
	bool m_IsAlarm;
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
	int m_ReportCount;
	wxString m_BaseStationName;
	wxString m_AgeString;
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
	bool m_Auto;
	float m_InputVolt;
	int m_Charging;
	int m_ProtocolVersion;
	int m_FlasherType;
	int m_IdSymbol;
	nvFastFont *m_NameFont;
		
	CAlarmModel *AlarmExists(int id);
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
	void SetSymbolColor();
	void RenderText(float x, float y, float vx, float vy, const wchar_t *format ...);
	void RenderSBMS();
	void RenderBusy();
	void RenderRestricted();
	void RenderAlarm();
	void RenderGPS();
	void RenderPositions();
	void RenderNewReport();
	void RenderNoSBMS();
	void RenderText();
	void RenderSelected();
	void RenderHuman();
	void Render() override;
	

public:

	CSBMS(void *db,CNaviBroker *broker);
	~CSBMS();

	void Read();
	void OnTickExit();
	//void ShowGraph();
	void ShowAction();

	//SET
	//pozycja referencyjna
	void SetRLon(double v);		void SetRLat(double v);		void SetRLonMap(double v);		void SetRLatMap(double v);
	//pozycja Gps
	void SetGpsLon(double v);	void SetGpsLat(double v);	void SetGpsLonMap(double v);	void SetGpsLatMap(double v);
	//referencyjna lub Gps
	void SetLon(double v);		void SetLat(double v);		void SetLonMap(double v);		void SetLatMap(double v);

	void SetSBMSID(int v);
	void SetNumber(wxString v);
	void SetMonitoring(int v);
	void SetExists(bool v);
	void SetDB(void *db);
	void SetForcedOff(int v);
	void SetLightOn(int v);
	void SetPhotoCellNightTime(bool v);
	void SetIdBaseStation(int v);
	void SetMMSI(int v);
	void SetNvTime(nvtime_t dt);
	void SetTimestamp(int v);
	void SetAge(int v) override;
	void SetAge(wxString v) override;
	void SetNewReport(bool v) override;
	void SetSBMSName(wxString v);
	void SetAuto(bool v) override;
	void SetInputVolt(float v) override;
	void UnsetNewReport() override;
	void SetFlasherType(int v) override;
	void SetIdSBMS(int v) override;
	void SetIdSymbol(int v) override;

	void SetBaseStationName(wxString v);
	void SetValidGPS(bool v);
	void SetInit(bool v);
	void SetCharging(int v);
	void SetChargingAsString(wxString v);
	void SetProtocolVersion(int v);
	void SetFont(nvFastFont *v);
	void SetBusy(bool v);
	void SetAlarm(bool v);
			

	//GET
	int GetSBMSID();
	wxString GetDriverHtml(int v) override;
	wxString GetDriverFullHtml() override;
	wxString GetAlarmHtml() override;
	wxString GetCommandHtml() override;
	int GetBaseStationId() override;
	int GetIdSymbol() override;
	//pozycja referencyjna
	//double GetRLon();	double GetRLat();	double GetRLonMap();	double GetRLatMap();
	//pozycja GPS
	double GetGpsLon();	double GetGpsLat();	double GetGpsLonMap();	double GetGpsLatMap();
	//referencyjna lub Gps
	double GetLon();	double GetLat();	double GetLonMap();	double GetLatMap();
	bool GetBusy();					//zajêty komendami
	int GetAlarmCount();
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
	int GetProtocolVersion();
	int GetFlasherType();
	CAlarmModel *GetAlarm(int v);
	wxPanel *GetSBMSPanel();
	wxString GetChargingAsString();
	wxString GetAlarmName(int v);
	wxString GetAgeAsString();
	wxString GetReportCountAsString();
	wxString GetCommandCountAsString();
	wxString GetInputVoltAsString();
	wxPanel *GetSBMSPanel(wxWindow *parent);
	
	
	//akcje
	void ShowGraph();
	void LightOn();
	void LightOff();
	void AutoManagement();
	void GetUptime();
	void SetDestinationMMSI(int mmsi);
	void GetTime();
	void Reset();
	void ClearAlarm();
	void ClearCommands();

};

#endif