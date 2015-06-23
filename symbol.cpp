#include <wx/wx.h>
#include <wx/notebook.h>
#include "symbol.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "images/icon.h"
#include "navidrawer.h"
#include "ais.h"
#include "options.h"
//#include "nvtime.h"

CSymbol::CSymbol(CNaviBroker *broker)
{
	m_Broker = broker;
	m_Scale = 1;
	m_Factor = DEFAULT_FACTOR;
	m_SmoothScaleFactor = 1;
	m_RectWidth = 0;
	m_RectHeight = 0;
	m_TranslationX = 0;
	m_TranslationY = 0;
	m_LightOn = true;
	m_FirstTime = true;
	m_Step = 0;
	m_BlinkTick = 0;
	m_CommandTick = CHECK_COMMAND_TICK;
	m_AlertTick = CHECK_ALERT_TICK;
	m_AlertTickOn = CHECK_ALERT_TICK_ON;
	m_CollisionTick = CHECK_COLLISION_TICK;
	m_CommandTickOn = CHECK_COMMAND_TICK_ON;
	m_ReadTick = CHECK_READ_TICK;
	m_BlinkTick = 0;
	m_Busy = false;
	m_BusyOn = false;
	m_Alert = false;
	m_AlertOn = false;
	m_IdSBMS = 0;
	m_SBMSID = 0;
	m_IdBaseStation = 0;
	m_RenderRestricted = false;
	m_Selected = false;
	m_Ticker0 = NULL;
	m_AlertCount = 0;
}

CSymbol::~CSymbol()
{
	//m_Ticker0->Stop();
	
#ifdef THREAD_JOINABLE
	delete m_Ticker0;
#endif
}

void CSymbol::Start()
{
	m_Ticker0 = new CTicker(this,TICK_SYMBOL);
	m_Ticker0->Start(TICK_SYMBOL_TIME);
}

void CSymbol::Stop()
{
	m_Ticker0->Stop();
}

void CSymbol::Read()
{
	m_ReadTick++;
	
	if(m_ReadTick <= CHECK_READ_TICK)
		return;

	void *db = DBConnect();
	if(db == NULL)
		return;
		
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%d'"),TABLE_SBMS,m_IdSBMS);

	my_query(db,sql);
	void *result = db_result(db);

    char **row = NULL;
	if(result == NULL)
	{
		DBClose(db);
		return;
	}
		
	while(row = (char**)db_fetch_row(result))
	{
		m_SBMSID = atoi(row[FI_SBMS_SMBSID]);
		m_IdBaseStation = atoi(row[FI_SBMS_ID_BASE_STATION]);
	}

	db_free_result(result);
		
	DBClose(db);
	m_ReadTick = 0;
	
	/*
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id_characteristic = '%d'"),TABLE_CHARACTERISTIC_ON_OFF,m_CharacteristicId);
	my_query(m_DB,sql);
	void *result = db_result(m_DB);

    char **row = NULL;
	if(result == NULL)
		return;

	while(row = (char**)db_fetch_row(result))
	{
		SOnOff ptr;
		float on,off;
		sscanf(row[FI_CHARACTERISTIC_ON_OFF_ON],"%f",&on);
		sscanf(row[FI_CHARACTERISTIC_ON_OFF_OFF],"%f",&off);
		ptr.on = on * 10;
		ptr.off = off * 10;
		m_OnList.Append(ptr);
	}

	db_free_result(result);
	*/
}

bool CSymbol::GetBusy()
{
	return m_Busy;
}

void CSymbol::Blink()
{
	if(m_OnList.Length() == 0)
		return;
		
	m_BlinkTick++;	
	SOnOff ptr = m_OnList.Get(m_Step);
	
	if(m_LightOn)
	{
		if(ptr.on <= m_BlinkTick)
		{
			m_LightOn = false;
			m_BlinkTick = 0;
		}
	}

	if(!m_LightOn)
	{
		if(ptr.off <= m_BlinkTick)
		{
			m_LightOn = true;
			m_BlinkTick = 0;
			m_Step++;
		}
	}
	
	if(m_Step == m_OnList.Length())
	{
		m_Step = 0;
	}

	m_Broker->Refresh(m_Broker->GetParentPtr());

}

void CSymbol::OnTick()
{
	
	bool result = false;

	Read();
	
	if(CheckCommand())
		result = true;
	if(CheckAlert())
		result = true;
	
	CheckCollision();

	if(result)
		m_Broker->Refresh(m_Broker->GetParentPtr());
}

bool CSymbol::CheckCollision()
{
	m_CollisionTick++;
	
	if(m_CollisionTick <= CHECK_COLLISION_TICK)
		return false;
	
	m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_MutexLock",NULL);
	int count = 0;
	m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_GetAisCount",&count);
	
	m_RenderRestricted = false;
		
	for(size_t i = 0; i < count; i++)
	{
		SAisData *ptr = (SAisData*)m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_GetAisItem",&i);
			
		nvCircle c1,c2;
		c1.Center.x = m_Lon;
		c1.Center.y = m_Lat;
		c1.Radius = c1.Radius = (double)RESTRICTED_AREA_RADIUS/1852/GetMilesPerDegree(m_Lon,m_Lat);
		c2.Center.x = ptr->lon;
		c2.Center.y = ptr->lat;
		c2.Radius = (double)ptr->length/1852/GetMilesPerDegree(ptr->lon,ptr->lat);
			
		if(nvIsCircleColision(&c1, &c2))
		{
			m_RenderRestricted = true;
			//fprintf(stderr,"COLLISION\n");
		}else{
			
			//fprintf(stderr,"NO Collision\n");
		}
			
			//fprintf(stderr,"%d\n",ptr->mmsi);
	}

	m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_MutexUnlock",NULL);
	m_CollisionTick = 1;
	
	return true;
}

bool  CSymbol::CheckCommand()
{
	m_CommandTick++;
	m_CommandTickOn++;
	
	if(m_CommandTickOn >= CHECK_COMMAND_TICK_ON)
	{
		m_BusyOn = !m_BusyOn;
		m_CommandTickOn = 0;
	}

	if(m_CommandTick <= CHECK_COMMAND_TICK)
		return false;
		
	void *db = DBConnect();
	if(db == NULL)
		return false;
	
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE SBMSID='%d' AND id_base_station='%d' AND status='%d'"),TABLE_COMMAND,m_SBMSID,m_IdBaseStation,COMMAND_STATUS_NEW);
	my_query(db,sql);
	void *result = db_result(db);
	
    char **row = NULL;
	if(result == NULL)
	{
		DBClose(db);
		return false;
	}
	
	m_Busy = false;
	while(row = (char**)db_fetch_row(result))
	{
		int cmd;
		sscanf(row[FI_COMMAND_ID],"%d",&cmd);
		m_Busy = true;
	}
	
	db_free_result(result);
	DBClose(db);
	m_CommandTick = 1;
	
	return true;
}

bool CSymbol::CheckAlert()
{
	m_AlertTick++;
	m_AlertTickOn++;

	if(m_AlertTickOn >= CHECK_ALERT_TICK_ON)
	{
		//m_AlertOn = !m_AlertOn;
		m_AlertTickOn = 0;
	}


	if(m_AlertTick <= CHECK_ALERT_TICK)
		return false;
	
	void *db = DBConnect();
	if(db == NULL)
		return false;
	
	wxString sql = wxString::Format(_("SELECT count(*) FROM %s WHERE id_sbms='%d' AND confirmed ='%d'"),TABLE_ALERT,m_IdSBMS,ALERT_NOT_CONFIRMED);
	my_query(db,sql);
	void *result = db_result(db);
	
    char **row = NULL;
	if(result == NULL)
	{
		DBClose(db);
		return false;
	}
	
	m_Alert = false;
	row = (char**)db_fetch_row(result);
	sscanf(row[0],"%d",&m_AlertCount);
	
	if(m_AlertCount > 0)
	{
		m_Alert = true;
		m_AlertOn = true;
	}else{
		m_Alert = false;
	}
	
	db_free_result(result);
	DBClose(db);	
	m_AlertTick = 1;
	
	return true;
}

void CSymbol::CreateSymbol(void *MemoryBlock,long MemoryBlockSize)
{
	TMemoryBlock BlockTGA_0;
	BlockTGA_0.Ptr = MemoryBlock;
	BlockTGA_0.Size = MemoryBlockSize;
	m_TextureTGA_0 = LoadFromMemoryBlockTGA( &BlockTGA_0 );
}

void CSymbol::CreateTexture(TTexture *Texture, GLuint *TextureID)
{
	glGenTextures(1, TextureID );
	glBindTexture(GL_TEXTURE_2D, *TextureID );
	glTexImage2D(GL_TEXTURE_2D, 0, Texture->Bpp / 8, Texture->Width, Texture->Height, 0, Texture->Type, GL_UNSIGNED_BYTE, Texture->Data );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	FreeTexture( Texture );
}

void CSymbol::CreateTextures(void) 
{
	CreateSymbol(icon, icon_size);
	CreateTexture( m_TextureTGA_0,  &m_TextureID_0 );
	
}

void CSymbol::SetSmoothScaleFactor(double v) 
{
	if( m_Scale > m_Factor )
		m_SmoothScaleFactor = m_Scale;
	else
		m_SmoothScaleFactor = m_Factor;
}

void CSymbol::SetValues()
{
	m_Scale  = m_Broker->GetMapScale();
	SetSmoothScaleFactor( m_Scale );
	
	m_RectWidth = RECT_WIDTH / m_SmoothScaleFactor;
	m_RectHeight = RECT_HEIGHT / m_SmoothScaleFactor;
	m_TranslationX = 0.0; //(RECT_WIDTH /2)/SmoothScaleFactor; 
	m_TranslationY = -(RECT_HEIGHT /2)/m_SmoothScaleFactor; 
	m_Broker->GetVisibleMap(m_VisibleMap);
	
}
#if 0
void CSymbol::RenderSelected()
{
	if(!m_Selected)
		return;

	glPushMatrix();
	
	glColor4f(1.0f,1.0f,1.0f,0.5f);	
	glTranslatef(m_LonMap, m_LatMap ,0.0f);
	glTranslatef(0.0, -m_RectWidth/2 ,0.0f);
	glLineWidth(2);
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = m_RectWidth/1.5;
	nvDrawCircleFilled(&c);
	glPopMatrix();

}
#endif

void CSymbol::RenderLightOn()
{
	if(!m_LightOn)
		return;
		
	glPushMatrix();
	glColor4f(1.0f,1.0f,1.0f,0.9f);
	glTranslatef(m_LonMap,m_LatMap,0.0f);

	glPointSize(10);

	glBegin(GL_QUADS);
		glVertex2f(  m_RectWidth/2 + m_TranslationX,  -m_RectHeight/2 + m_TranslationY);
		glVertex2f(  m_RectWidth/2 + m_TranslationX,   m_RectHeight/2 + m_TranslationY);
		glVertex2f( -m_RectWidth/2 + m_TranslationX,   m_RectHeight/2 + m_TranslationY);
		glVertex2f( -m_RectWidth/2 + m_TranslationX,  -m_RectHeight/2 + m_TranslationY);
	glEnd();

	nvDrawPoint(0.0,0.0);
	glPopMatrix();
		
}

void CSymbol::RenderAlert()
{
	if(!m_Alert)
		return;
		
	glPushMatrix();
	glColor4f(1.0f,0.0f,0.0f,0.9f);
	glTranslatef(m_LonMap,m_LatMap,0.0f);
	glTranslatef(0.0,-m_RectWidth/2,0.0f);

	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = m_RectWidth;
	nvDrawCircle(&c);
		
	glPopMatrix();
		
}

void CSymbol::RenderBusy()
{
	if(!m_Busy)
		return;

	float angle = (float)(360.0/CHECK_COMMAND_TICK) * m_CommandTick;

	float x = 0.0;
	float y = 0.0;

	glPushMatrix();
	glColor4f(1.0f,0.0f,0.0f,0.8f);
	glTranslatef(m_LonMap + m_RectWidth/2,m_LatMap - m_RectWidth,0.0f);

	glPointSize(10);
	glLineWidth(2);
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = m_RectWidth/4;
	nvDrawCircle(&c);
		
	if(m_BusyOn)
		glColor4f(1.0f,0.0f,0.0f,0.8f);
	else
		glColor4f(1.0f,1.0f,1.0f,0.8f);
	
	nvDrawPoint(x,y);
	glPopMatrix();
	
}

void CSymbol::RenderSymbol()
{
	glEnable(GL_TEXTURE_2D);
#if 0	
	if(m_LightOn)
		glColor4f(1.0f,1.0f,1.0f,0.5f);
	else
		glColor4f(0.0f,0.0f,0.0f,0.5f);
#endif
	if(m_IdSBMS > 0)
	{
		if(m_Alert)
		{
			if(m_AlertOn)
				glColor4f(1.0f,0.0f,0.0f,0.8f);
			else
				glColor4f(1.0f,1.0f,1.0f,0.8f);
		}
	}else{
		
		glColor4f(0.0f,0.0f,0.0f,0.8f);
	}

	glBindTexture( GL_TEXTURE_2D, m_TextureID_0);
	glPushMatrix();
	glTranslatef(m_LonMap,m_LatMap,0.0f);
		
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,1.0f); glVertex2f(  m_RectWidth/2 + m_TranslationX,  -m_RectHeight/2 + m_TranslationY);
		glTexCoord2f(1.0f,0.0f); glVertex2f(  m_RectWidth/2 + m_TranslationX,   m_RectHeight/2 + m_TranslationY);
		glTexCoord2f(0.0f,0.0f); glVertex2f( -m_RectWidth/2 + m_TranslationX,   m_RectHeight/2 + m_TranslationY);
		glTexCoord2f(0.0f,1.0f); glVertex2f( -m_RectWidth/2 + m_TranslationX,  -m_RectHeight/2 + m_TranslationY);
	glEnd();
	
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

}

void CSymbol::RenderRestricted()
{
	if(!m_RenderRestricted)
		return;
	
	nvCircle c;
	c.Center.x = m_LonMap;
	c.Center.y = m_LatMap;
	c.Radius = (double)RESTRICTED_AREA_RADIUS/1852/GetMilesPerDegree(m_LonMap,m_LatMap);
	glColor4f(1.0f,0.0f,0.0f,0.6f);
	nvDrawCircle(&c);
	glColor4f(1.0f,0.0f,0.0f,0.1f);
	nvDrawCircleFilled(&c);
}

void CSymbol::RenderGPS()
{
	glPushMatrix();
	glColor4f(1.0f,1.0f,1.0f,0.9f);
	glTranslatef(m_LonMap,m_LatMap,0.0f);

	glPointSize(10);
	nvDrawPoint(0.0,0.0);
	glPopMatrix();

}

void CSymbol::Render()
{
	if(m_FirstTime)
	{
		CreateTextures();
		m_FirstTime = false;
	}
	
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);

	SetValues();
#if 0
	RenderSelected();
#endif
	RenderRestricted();
	RenderBusy();
#if 0
	RenderAlert();
#endif
	RenderGPS();
	RenderSymbol();
		
	glDisable(GL_BLEND);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_SMOOTH);

}

//SET
void CSymbol::SetId(int v)
{
	m_Id = v;
}

void CSymbol::SetLon(double v)
{
	m_Lon = v;
}

void CSymbol::SetLat(double v)
{
	m_Lat = v;
}

void CSymbol::SetLonMap(double v)
{
	m_LonMap = v;
}

void CSymbol::SetLatMap(double v)
{
	m_LatMap = v;
}


void CSymbol::SetIdSBMS(int v)
{
	m_IdSBMS = v;
}

void CSymbol::SetNumber(wxString v)
{
	m_Number = v;
}

void CSymbol::SetName(wxString v)
{
	m_Name = v;
}

//GET
int CSymbol::GetId()
{
	return m_Id;
}

int CSymbol::GetIdSBMS()
{
	return m_IdSBMS;
}

int CSymbol::GetSBMSID()
{
	return m_SBMSID;
}

int CSymbol::GetBaseStationId()
{
	return m_IdBaseStation;
}

double CSymbol::GetLon()
{
	return m_Lon;
}

double CSymbol::GetLat()
{
	return m_Lat;
}

double CSymbol::GetLonMap()
{
	return m_LonMap;
}

double CSymbol::GetLatMap()
{
	return m_LatMap;
}

int CSymbol::GetAlertCount()
{
	return m_AlertCount;
}

wxString CSymbol::GetName()
{
	return m_Name;
}