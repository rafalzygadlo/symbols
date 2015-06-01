#ifndef __SYMBOL_H
#define __SYMBOL_H

#include <wx/html/htmlwin.h>
#include "ticker.h"
#include <gl/gl.h>
#include "navibroker.h"
#include "naviarray.h"
#include "tgamem.h"
#include "picture.h"

class CSymbol
{
	CTicker *m_Ticker0;
	CNaviBroker *m_Broker;
	CNaviArray <SOnOff> m_OnList;
	TTexture *m_TextureTGA_0;
	GLuint m_TextureID_0;
	bool m_FirstTime;
	int m_Step;
	bool m_Begin;
	int m_BlinkTick;
	int m_Id;
	bool m_LightOn;
	bool m_BusyOn;
	bool m_Busy;
	bool m_Alert;
	bool m_AlertOn;
	double m_Lon;
	double m_Lat;
	double m_LonMap;
	double m_LatMap;
	double m_Scale;
	double m_Factor; 
	double m_SmoothScaleFactor;
	double m_RectWidth;
	double m_RectHeight;
	double m_TranslationX;
	double m_TranslationY;
	double m_VisibleMap[4];
	int m_CommandTick,m_CommandTickOn;
	int m_ReadTick;
	int m_CollisionTick;
	int m_AlertTick,m_AlertTickOn;
	int m_IdSBMS;
	int m_SBMSID;
	int m_IdBaseStation;
	wxString m_Number;
	bool m_RenderRestricted;
	
		
	
	void CreateSymbol(void *MemoryBlock,long MemoryBlockSize);
	void CreateTexture(TTexture *Texture, GLuint *TextureID);
	void CreateTextures(void);
	bool CheckCommand();
	bool CheckAlert();
	bool CheckCollision();
	void SetValues();
	void SetSmoothScaleFactor(double v);
	void Blink(); 
	void RenderSymbol();
	void RenderLightOn();
	void RenderBusy();
	void RenderRestricted();
	void RenderAlert();
	void RenderGPS();		//real position
			
public:

	CSymbol(CNaviBroker *broker);
	~CSymbol();

	void OnTick();
	void SetId(int v);
	void SetLon(double v);
	void SetLat(double v);
	void SetLonMap(double v);
	void SetLatMap(double v);
	void SetIdSBMS(int v);
	void SetSBMSID(int v);
	//void SetBaseStationId();
	void SetNumber(wxString v);
	void SetOnPosition(bool v);
	void SetInMonitoring(bool v);
		
	int GetId();
	int GetIdSBMS();
	int GetSBMSID();
	int GetBaseStationId();
	double GetLon();
	double GetLat();
	double GetLonMap();
	double GetLatMap();
	bool GetBusy();					//zajêty komendami

	void Start();
	void Stop();
	void Read();
	void Render();

};

#endif