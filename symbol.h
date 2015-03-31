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

class CSymbol
{
	void *m_DB;
	CTicker *m_Ticker0;
	CTicker *m_Ticker1;
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
	int m_CharacteristicId;
	bool m_LightOn;
	bool m_BusyOn;
	bool m_Busy;
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
	int m_IdSBMS;
	
	void CreateSymbol(void *MemoryBlock,long MemoryBlockSize);
	void CreateTexture(TTexture *Texture, GLuint *TextureID);
	void CreateTextures(void);
	void CheckCommand();
	void SetValues();
	void SetSmoothScaleFactor(double v);
	void Blink();
	void RenderSymbol();
	void RenderLightOn();
	void RenderBusy();
		
public:

	CSymbol(void *db,CNaviBroker *broker);
	~CSymbol();

	void OnTick();
	void SetId(int v);
	void SetLon(double v);
	void SetLat(double v);
	void SetLonMap(double v);
	void SetLatMap(double v);
	void SetIdSBMS(int v);
	void SetCharacteristicId(int v);
	int GetId();
	double GetLon();
	double GetLat();
	double GetLonMap();
	double GetLatMap();
	void Start();
	void OnBlink();
	void OnCommand();
	void Read();
	void Render();

};

class CSymbolPanel
{
	CPicturePanel *m_PicturePanel;
	CGrid *m_Grid;
	wxHtmlWindow *m_Html;

public:

	CSymbolPanel();
	wxPanel *GetPage1(wxWindow *parent);
	void SetPage1(void *db,CSymbol *ptr);

};

#endif