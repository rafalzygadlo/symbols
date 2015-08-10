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
#include "render.h"
//#include "nvtime.h"

CSymbol::CSymbol(CNaviBroker *broker,nvFastFont *font )
{
	m_Font = font;
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
	m_CommandTick = CHECK_COMMAND_TICK;
	m_AlarmTick = CHECK_ALARM_TICK;
	m_AlarmTickOn = CHECK_ALARM_TICK_ON;
	m_CollisionTick = CHECK_COLLISION_TICK;
	m_CommandTickOn = CHECK_COMMAND_TICK_ON;
	m_ReadTick = CHECK_READ_TICK;
	m_Busy = false;
	m_BusyOn = false;
	m_Alarm = false;
	m_AlarmOn = false;
	m_IdSBMS = 0;
	m_SBMSID = 0;
	m_IdBaseStation = 0;
	m_RenderRestricted = false;
	m_Selected = false;
	m_AlarmCount = 0;
	m_TickExit = false;
	m_PhotoCellNightTime = false;
	m_ForcedOff = false;
	m_MMSI = 0;
	m_InMonitoring = false;
}

CSymbol::~CSymbol()
{

}

void CSymbol::SetDB(void *db)
{
	m_DB = db;
}

void CSymbol::Read()
{
	m_ReadTick++;
	
	if(m_ReadTick <= CHECK_READ_TICK)
		return;
			
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id = '%d'"),TABLE_SBMS,m_IdSBMS);

	my_query(m_DB,sql);
	void *result = db_result(m_DB);

    char **row = NULL;
	if(result == NULL)
		return;
	
	double lon,lat,to_x,to_y;
	
	while(row = (char**)db_fetch_row(result))
	{
		m_SBMSID = atoi(row[FI_SBMS_SBMSID]);
		m_IdBaseStation = atoi(row[FI_SBMS_ID_BASE_STATION]);
		SetForcedOff(atoi(row[FI_SBMS_MODE_FORCED_OFF]));
		SetPhotoCellNightTime(atoi(row[FI_SBMS_MODE_PHOTOCELL_NIGHT_TIME]));
		SetMMSI(atoi(row[FI_SBMS_MMSI]));

		sscanf(row[FI_SYMBOL_LON],"%lf",&lon);
		sscanf(row[FI_SYMBOL_LAT],"%lf",&lat);
		double to_x,to_y;
		m_Broker->Unproject(lon,lat,&to_x,&to_y);

		SetLon(lon);
		SetLat(lat);

		SetLonMap(to_x);
		SetLatMap(-to_y);

		nvtime_t dt;
		nvdatetime(atoi(row[FI_SBMS_DATE_TIME_STAMP]),&dt);
		SetNvTime(dt);
	}

	if(!m_ForcedOff & m_PhotoCellNightTime)
		SetLightOn(true);
	else
		SetLightOn(false);
	
	db_free_result(result);
	
	m_ReadTick = 0;

}

bool CSymbol::GetBusy()
{
	return m_Busy;
}



bool CSymbol::CheckCollision()
{
	if(m_Broker == NULL)
		return false;
	
	m_CollisionTick++;
	
	if(m_CollisionTick <= CHECK_COLLISION_TICK)
		return false;
	
	m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_MutexLock",NULL);
	int count = 0;
	m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_GetAisCount",&count);
	
	m_RenderRestricted = false;
		
	double to_x,to_y;
	for(size_t i = 0; i < count; i++)
	{
		SAisData *ptr = (SAisData*)m_Broker->ExecuteFunction(m_Broker->GetParentPtr(),"devmgr_GetAisItem",&i);
			
		nvCircle c1,c2;
		c1.Center.x = m_RLonMap;
		c1.Center.y = m_RLatMap;
		c1.Radius = c1.Radius = (double)RESTRICTED_AREA_RADIUS/1852/GetMilesPerDegree(m_RLon,m_RLat);
		m_Broker->Unproject(ptr->lon,ptr->lat,&to_x,&to_y);
		c2.Center.x =  to_x;
		c2.Center.y = -to_y;
		c2.Radius = (double)ptr->length/1852/GetMilesPerDegree(ptr->lon,ptr->lat);
			
		if(nvIsCircleColision(&c1, &c2) || nvIsCircleInCircle(&c1,&c2))
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

bool CSymbol::CheckAlarm()
{
	m_AlarmTick++;
	m_AlarmTickOn++;

	if(m_AlarmTickOn >= CHECK_ALARM_TICK_ON)
	{
		//m_AlertOn = !m_AlertOn;
		m_AlarmTickOn = 0;
	}

	if(m_AlarmTick <= CHECK_ALARM_TICK)
		return false;
	
	wxString sql = wxString::Format(_("SELECT count(*) FROM %s WHERE id_sbms='%d'"),TABLE_ALARM,m_IdSBMS,ALARM_NOT_CONFIRMED);
	my_query(m_DB,sql);
	void *result = db_result(m_DB);
	
    char **row = NULL;
	if(result == NULL)
		return false;
	
	m_Alarm = false;
	row = (char**)db_fetch_row(result);
	sscanf(row[0],"%d",&m_AlarmCount);
	
	if(m_AlarmCount > 0)
	{
		m_Alarm = true;
		m_AlarmOn = true;
	}else{
		m_Alarm = false;
	}
	
	db_free_result(result);
	m_AlarmTick = 1;
	
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
	
	wxString sql;
	if(m_MMSI == 0)
		sql = wxString::Format(_("SELECT count(*) FROM %s WHERE SBMSID='%d' AND id_base_station='%d' AND status='%d'"),TABLE_COMMAND,m_SBMSID,m_IdBaseStation,COMMAND_STATUS_NEW);
	else
		sql = wxString::Format(_("SELECT count(*) FROM %s WHERE mmsi='%d' AND id_base_station='%d' AND status='%d'"),TABLE_COMMAND,m_MMSI,m_IdBaseStation,COMMAND_STATUS_NEW);

	my_query(m_DB,sql);
	void *result = db_result(m_DB);
	
    char **row = NULL;
	if(result == NULL)
		return false;
	
	
	while(row = (char**)db_fetch_row(result))
		sscanf(row[0],"%d",&m_CommandCount);
		
	if(m_CommandCount > 0)
		m_Busy = true;
	else
		m_Busy = false;
	
	db_free_result(result);
	m_CommandTick = 1;
	
	return true;
}

bool CSymbol::SetPositions()
{	
	m_PositionsTick++;
	
	if(m_PositionsTick >= CHECK_POSITIONS_TICK_ON)
	{
		m_PositionsTick = 0;
	}
	
	m_PosBuffer.Clear();
	wxString sql = wxString::Format(_("SELECT lon,lat FROM `%s` WHERE valid_lon_lat='%d' AND id_sbms='%d' ORDER BY local_utc_time_stamp LIMIT 50"),TABLE_STANDARD_REPORT,VALID_LON_LAT,m_IdSBMS);
		
	my_query(m_DB,sql);

	void *result = db_result(m_DB);
    char **row = NULL;
	
	if(result == NULL)
		return false;
	
	int counter = 0;
	nvPoint3f pt;
	double to_x,to_y;
	while(row = (char**)db_fetch_row(result))
	{
		sscanf(row[0],"%lf",&pt.x);
		sscanf(row[1],"%lf",&pt.y);
		m_Broker->Unproject(pt.x,pt.y,&to_x,&to_y);
		pt.x = to_x;
		pt.y = -to_y;
		m_PosBuffer.Append(pt);
		counter++;
	}
	
	//fprintf(stderr,"%d\n",counter);
	db_free_result(result);
	
	return true;
}


void CSymbol::OnTick(void *db)
{
	m_DB = db;
	if(m_Broker == NULL)
		return;
	
	bool result = false;

	Read();
	
	if(CheckCommand())
		result = true;
	if(CheckAlarm())
		result = true;
	
	if(SetPositions())
		result = true;
	
	CheckCollision();
	
}

void CSymbol::OnTickExit()
{
	m_TickExit = true;
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
	glTranslatef(m_RLonMap,m_RLatMap,0.0f);

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

void CSymbol::RenderAlarm()
{
	if(!m_Alarm)
		return;
		
	glPushMatrix();
	glColor4f(1.0f,0.0f,0.0f,0.9f);
	glTranslatef(m_RLonMap,m_RLatMap,0.0f);
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
		
	glPushMatrix();
	
	glTranslatef(m_RLonMap,m_RLatMap,0.0f);
	//glTranslatef(m_RectWidth/3,- m_RectWidth/3,0.0f);

	//glPointSize(10);
	//glLineWidth(2);
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = m_RectWidth*1.2;
	
		
	if(m_BusyOn)
		glColor4f(1.0f,0.0f,0.0f,0.3f);
	else
		glColor4f(1.0f,1.0f,1.0f,0.3f);
	
	nvDrawCircleArcFilled(&c,90,180);
	nvDrawPoint(0.0,0.0);
		
	glPopMatrix();

}

void CSymbol::RenderSymbol()
{

	SetColor(SYMBOL_NORMAL_COLOR);
	if(m_LightOn)
		SetColor(SYMBOL_LIGHT_ON_COLOR);
	
	if(m_InMonitoring)
	{
		if(m_Alarm)
		{
			if(m_AlarmOn)
				SetColor(SYMBOL_ERROR_COLOR);
		}
	
	}else{
		
		SetColor(SYMBOL_NO_MONITOR_COLOR);
	}

/*
	glEnable(GL_TEXTURE_2D);
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
*/
		
	glPushMatrix();
	glTranslatef(m_RLonMap,m_RLatMap,0.0f);
	
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = m_RectWidth/2;
	
	nvDrawCircleFilled(&c);
	
	glColor4f(0.0,0.0,0.0,0.5);
	glLineWidth(1);
	glBegin(GL_LINES);
		glVertex2f(0.0f,m_RectWidth);
		glVertex2f(0.0f,-m_RectWidth);
		glVertex2f(m_RectWidth,0.0);
		glVertex2f(-m_RectWidth,0.0);
	glEnd();
	nvDrawCircle(&c);

	glPopMatrix();
	
	
}

void CSymbol::RenderRestricted()
{
	
	if(m_RenderRestricted)
		glColor4f(1.0,0.0,0.0,0.1);
	else
		glColor4f(0.0,1.0,0.0,0.1);
	
	nvCircle c;
	c.Center.x = m_RLonMap;
	c.Center.y = m_RLatMap;
	c.Radius = (double)RESTRICTED_AREA_RADIUS/1852/GetMilesPerDegree(m_RLon,m_RLat);
	nvDrawCircleFilled(&c);
}

void CSymbol::RenderGPS()
{
	glPushMatrix();
	glColor4f(1.0f,1.0f,1.0f,0.9f);
	glTranslatef(m_RLonMap,m_RLatMap,0.0f);

	glPointSize(10);
	nvDrawPoint(0.0,0.0);
	glPopMatrix();

}

void CSymbol::RenderPositions()
{
	glEnable(GL_BLEND);
	glPointSize(20);
	glColor3f(0.0f,1.0f,0.0f);
	if(m_PosBuffer.Length() > 0)
		RenderGeometry(GL_POINTS,m_PosBuffer.GetRawData(),m_PosBuffer.Length());
	
	glPointSize(1);
	glDisable(GL_BLEND);
	
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
	RenderAlarm();
#endif
	//RenderGPS();

	RenderSymbol();
	RenderPositions();
		
	glDisable(GL_BLEND);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_SMOOTH);

}

void CSymbol::SetColor(int id)
{
	glColor4ub(GetColor(id).R,GetColor(id).G,GetColor(id).B,GetColor(id).A);
}

//SET
void CSymbol::SetId(int v)
{
	m_Id = v;
}

void CSymbol::SetRLon(double v)
{
	m_RLon = v;
}

void CSymbol::SetRLat(double v)
{
	m_RLat = v;
}

void CSymbol::SetRLonMap(double v)
{
	m_RLonMap = v;
}

void CSymbol::SetRLatMap(double v)
{
	m_RLatMap = v;
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

void CSymbol::SetRemove(bool v)
{
	m_Exists = v;
}

void CSymbol::SetForcedOff(bool v)
{
	m_ForcedOff = v;
}

void CSymbol::SetPhotoCellNightTime(bool v)
{
	m_PhotoCellNightTime = v;
}

void CSymbol::SetLightOn(bool v)
{
	m_LightOn = v;
}

void CSymbol::SetMMSI(int v)
{
	m_MMSI = v;
}

void CSymbol::SetInMonitoring(bool v)
{
	m_InMonitoring = v;
}


void CSymbol::SetNvTime(nvtime_t dt)
{
	m_nvTime = dt;
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

double CSymbol::GetRLon()
{
	return m_RLon;
}

double CSymbol::GetRLat()
{
	return m_RLat;
}

double CSymbol::GetRLonMap()
{
	return m_RLonMap;
}

double CSymbol::GetRLatMap()
{
	return m_RLatMap;
}

int CSymbol::GetAlarmCount()
{
	return m_AlarmCount;
}

wxString CSymbol::GetName()
{
	return m_Name;
}

wxString CSymbol::GetNumber()
{
	return m_Number;
}

bool CSymbol::GetExists()
{
	return m_Exists;
}

bool CSymbol::GetLightOn()
{
	return m_LightOn;
}

wxString CSymbol::GetCommandCount()
{
	return wxString::Format(_("%d"),m_CommandCount);
	
}

int CSymbol::GetMMSI()
{
	return m_MMSI;
}

nvtime_t CSymbol::GetNvTime()
{
	return m_nvTime;
}