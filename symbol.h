#ifndef __SYMBOL_H
#define __SYMBOL_H

#include "ticker.h"
#include <GL/gl.h>
#include "navibroker.h"

class CSymbol
{
	void *m_DB;
	CTicker *m_Ticker;
	CNaviBroker *m_Broker;
	int m_Id;
	int m_TextureId;
	double m_Lon;
	double m_Lat;
	double m_Scale;
	double m_Factor; 
	double m_SmoothScaleFactor;
	double m_RectWidth;
	double m_RectHeight;
	double m_TranslationX;
	double m_TranslationY;
	double m_VisibleMap[4];
	
	void SetValues();
	void SetSmoothScaleFactor(double v);
	
public:

	CSymbol(void *db,CNaviBroker *broker);
	~CSymbol();

	void SetId(int v);
	void SetLon(double v);
	void SetLat(double v);
	int GetId();
	double GetLon();
	double GetLat();
	void Render();

};

#endif