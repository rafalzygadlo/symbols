#ifndef __SYMBOL_H
#define __SYMBOL_H

#include <wx/html/htmlwin.h>
#include "ticker.h"
#include <gl/gl.h>
#include "navibroker.h"
#include "naviarray.h"
#include "tgamem.h"
#include "picture.h"
#include "grid.h"
#include "graph.h"
#include "light.h"

class CSymbol
{
	CTicker *m_Ticker0;
	CNaviBroker *m_Broker;
	CNaviArray <SOnOff> m_OnList;
	CGrid *m_Grid;
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
	int m_CommandTick;
	int m_CollisionTick;
	int m_AlertTick;
	int m_IdSBMS;
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
	void SetNumber(wxString v);
	void SetOnPosition(bool v);
	void SetInMonitoring(bool v);
		
	int GetId();
	int GetIdSBMS();
	double GetLon();
	double GetLat();
	double GetLonMap();
	double GetLatMap();
	
	void Start();
	void Read();
	void Render();

};

class CSymbolPanel
{
	CPicturePanel *m_PicturePanel;
	CGrid *m_Grid;
	CGraph *m_Graph;
	CLightPanel *m_LightPanel;
	wxHtmlWindow *m_Html;
	int m_IdSBMS;
	int m_IdBaseStation;
	void SymbolInfo(void *db,CSymbol *ptr);
	void SBMSInfo(void *db,int id_sbms);
	void PictureInfo(void *db,CSymbol *ptr);
	void BaseStationInfo(void *db, int id_base_station);

public:

	CSymbolPanel();
	wxPanel *GetPage1(wxWindow *parent);	
	wxPanel *GetPage2(wxWindow *parent);	//Report
	wxPanel *GetPage3(wxWindow *parent);	//Alerts
	void SetPage1(void *db,CSymbol *ptr);
	void SetPageEmpty();
	void SetSBMS();

};

#endif