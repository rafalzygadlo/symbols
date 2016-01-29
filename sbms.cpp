#include <wx/wx.h>
#include <wx/notebook.h>
#include "sbms.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "images/icon.h"
#include "navidrawer.h"
#include "ais.h"
#include "options.h"
#include "render.h"
#include "commanddialog.h"



CSBMS::CSBMS(CNaviBroker *broker)
{
	m_Broker = broker;
	m_Scale = 1;
	m_SmoothScaleFactor = 1;
	m_RectWidth = 0;
	m_RectHeight = 0;
	m_TranslationX = 0;
	m_TranslationY = 0;
	m_LightOn = LIGHT_NOT_AVAILABLE;
	m_ForcedOff = LIGHT_NOT_AVAILABLE;
	m_FirstTime = true;
	m_CommandTick = CHECK_COMMAND_TICK;
	m_AlarmTick = CHECK_ALARM_TICK;
	m_AlarmTickOn = CHECK_ALARM_TICK_ON;
	m_CollisionTick = CHECK_COLLISION_TICK;
	m_CommandTickOn = CHECK_COMMAND_TICK_ON;
	m_ReadTick = CHECK_READ_TICK;
	m_ReportTick = CHECK_REPORT_TICK;
	m_Busy = false;
	m_BusyOn = false;
	m_Alarm = false;
	m_AlarmOn = false;
	m_SBMSID = 0;
	m_IdBaseStation = 0;
	m_RenderRestricted = false;
	m_Selected = false;
	m_AlarmCount = 0;
	m_TickExit = false;
	m_PhotoCellNightTime = false;
	m_MMSI = 0;
	m_Monitoring = SYMBOL_NOT_IN_MONITORING;
	m_ReportCount = 0;
	m_NewReport = false;
	m_ValidGPS = false;
	m_NoSBMS = true;
	m_AgeString = "N/A";
	m_GraphDialog = NULL;
	m_Charging = false;
	m_NewAlarmCount = 0;
	m_ProtocolVersion = 0;
	m_NameFont = NULL;
	m_SBMSActionDialog = NULL;
	
}

CSBMS::~CSBMS()
{	
	ClearAlarms();
	m_Broker = NULL;
	
	if(m_GraphDialog)
		delete m_GraphDialog;
	//if(m_SBMSActionDialog)
	//	delete m_SBMSActionDialog;
	
}

void CSBMS::SetFont(nvFastFont *v)
{
	m_NameFont = v;
}

void CSBMS::SetDB(void *db)
{
	m_DB = db;
}

bool CSBMS::GetBusy()
{
	return m_Busy;
}

void CSBMS::ClearPositions()
{
	m_PosBuffer.Clear();
}

void CSBMS::ClearAlarms()
{
	for(size_t i = 0; i < m_AlarmList.Length(); i++)
	{
		CAlarm *ptr = (CAlarm*)m_AlarmList.Get(i);
		delete ptr;
		
	}

	m_AlarmList.Clear();

}

CAlarm *CSBMS::AlarmExists(int id)
{
	for(size_t i = 0; i < m_AlarmList.Length(); i++)
	{
		CAlarm *ptr = (CAlarm*)m_AlarmList.Get(i);
		if(id == ptr->GetId())
			return ptr;
	}

	return NULL;
}

void CSBMS::AlarmRemove()
{
	for(size_t i = 0; i < m_AlarmList.Length(); i++)
	{
		CAlarm *ptr = (CAlarm*)m_AlarmList.Get(i);
		
		if(!ptr->GetExists())
		{
			m_AlarmList.Remove(i);
			delete ptr;
			i = 0;
		}
	}

	//fprintf(stderr,"Size:%d\n",m_SymbolList->size());
}

void CSBMS::SetAlarms()
{
	for(size_t i = 0; i < m_AlarmList.Length(); i++)
	{
		CAlarm *ptr = (CAlarm*)m_AlarmList.Get(i);
		ptr->SetExists(false);
	}
}

bool CSBMS::CheckCollision()
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
		c1.Radius = c1.Radius = (double)GetRestrictedArea()/1852/GetMilesPerDegree(m_RLon,m_RLat);
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
		
	
	return false;
}

bool CSBMS::CheckAlarm()
{
	//m_AlarmTick++;
	//m_AlarmTickOn++;

	//if(m_AlarmTickOn >= CHECK_ALARM_TICK_ON)
	//{
		//m_AlertOn = !m_AlertOn;
		//m_AlarmTickOn = 0;
	//}

	//if(m_AlarmTick <= CHECK_ALARM_TICK)
		//return false;
	m_AlarmOn = !m_AlarmOn;
	wxString sql = wxString::Format(_("SELECT * FROM `%s`,`%s` WHERE id_sbms='%d' AND active='%d' AND id_alarm=`%s`.id ORDER BY set_local_utc_time DESC"),TABLE_SBMS_ALARM,TABLE_ALARM,GetId(),ALARM_ACTIVE,TABLE_ALARM);
	my_query(m_DB,sql);
	void *result = db_result(m_DB);
	
    char **row = NULL;
	if(result == NULL)
		return false;
	
	m_NewAlarmCount = 0;
	m_Alarm = false;
	bool exists = false;
	int offset = 9;
	CAlarm *Alarm = NULL;
	
	while(row = (char**)db_fetch_row(result))
	{
		int id = atoi(row[FI_SBMS_ALARM_ID]);
		Alarm = AlarmExists(id);
		
		bool add = false;
		
		if(Alarm == NULL)
		{
			add = true;
			Alarm = new CAlarm();
			Alarm->SetNew(true);
			m_NewAlarmCount++;
		}
				
		Alarm->SetId(atoi(row[FI_SBMS_ALARM_ID]));
		Alarm->SetIdAlarm(atoi(row[FI_SBMS_ALARM_ID_ALARM]));
		Alarm->SetAlarmOnDate(Convert(row[FI_SBMS_ALARM_SET_LOCAL_UTC_TIME]));
		Alarm->SetConfirmed(atoi(row[FI_SBMS_ALARM_CONFIRMED]));
		Alarm->SetName(Convert(row[FI_ALARM_NAME + offset]));
		Alarm->SetType(atoi(row[FI_ALARM_TYPE + offset]));
		
		
		if(add)
		{
			m_AlarmList.Append(Alarm);
		}
		
		Alarm->SetExists(true);

	}	
	
	if(m_AlarmList.Length() > 0)
	{
		m_Alarm = true;
		
	}else{
		m_Alarm = false;
	}
	
	db_free_result(result);
	m_AlarmTick = 1;
	
	return true;
}

bool  CSBMS::CheckCommand()
{
	m_CommandTick++;
	m_CommandTickOn++;
	m_BusyOn = !m_BusyOn;
	
	if(m_CommandTickOn >= CHECK_COMMAND_TICK_ON)
		m_CommandTickOn = 0;
	
	if(m_CommandTick <= CHECK_COMMAND_TICK)
		return false;
	
	wxString sql;
	sql = wxString::Format(_("SELECT count(*) FROM %s WHERE id_sbms='%d' AND status='%d' AND active='%d'"),TABLE_SBMS_COMMAND,GetId(),COMMAND_STATUS_NEW,COMMAND_ACTIVE);
	
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

bool CSBMS::SetPositions()
{
	m_PositionsTick++;
	
	if(m_PositionsTick >= CHECK_POSITIONS_TICK_ON)
	{
		m_PositionsTick = 0;
	}
	
	m_PosBuffer.Clear();
	wxString sql = wxString::Format(_("SELECT lon,lat FROM `%s` WHERE valid_lon_lat='%d' AND id_sbms='%d' ORDER BY local_utc_time_stamp DESC LIMIT 10"),TABLE_SBMS_STANDARD_REPORT,VALID_LON_LAT,GetId());
		
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
		pt.z = 0.0;
		//SetLonMap(pt.x);
		//SetLatMap(pt.y);
		m_PosBuffer.Append(pt);
		counter++;
	}
	
	//fprintf(stderr,"%d\n",counter);
	db_free_result(result);
	
	return true;
}

bool CSBMS::CheckReport()
{
	m_ReportTick++;
	
	if(m_ReportTick <= CHECK_REPORT_TICK)
		return false;
			
	wxString sql = wxString::Format(_("SELECT count(*) FROM %s WHERE id_sbms='%d'"),TABLE_SBMS_STANDARD_REPORT,GetId());

	my_query(m_DB,sql);
	void *result = db_result(m_DB);

    char **row = NULL;
	if(result == NULL)
		return false;
	
	row = (char**)db_fetch_row(result);
	sscanf(row[0],"%d",&m_ReportCount);
	
	
	db_free_result(result);
	return true;
}



void CSBMS::OnTickExit()
{
	m_TickExit = true;
}

void CSBMS::CreateSymbol(void *MemoryBlock,long MemoryBlockSize)
{
	TMemoryBlock BlockTGA_0;
	BlockTGA_0.Ptr = MemoryBlock;
	BlockTGA_0.Size = MemoryBlockSize;
	m_TextureTGA_0 = LoadFromMemoryBlockTGA( &BlockTGA_0 );
}

void CSBMS::CreateTexture(TTexture *Texture, GLuint *TextureID)
{
	glGenTextures(1, TextureID );
	glBindTexture(GL_TEXTURE_2D, *TextureID );
	glTexImage2D(GL_TEXTURE_2D, 0, Texture->Bpp / 8, Texture->Width, Texture->Height, 0, Texture->Type, GL_UNSIGNED_BYTE, Texture->Data );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	FreeTexture( Texture );
}

void CSBMS::CreateTextures(void) 
{
	CreateSymbol(icon, icon_size);
	CreateTexture( m_TextureTGA_0,  &m_TextureID_0 );
	
}

void CSBMS::SetSmoothScaleFactor(double v) 
{
	int factor = GetScaleFactor();
	if( m_Scale > factor )
		m_SmoothScaleFactor = m_Scale;
	else
		m_SmoothScaleFactor = factor;
}

void CSBMS::SetValues()
{
	if(m_Broker == NULL)
		return;
	
	m_Scale  = m_Broker->GetMapScale();
	SetSmoothScaleFactor( m_Scale );
	
	m_RectWidth = RECT_WIDTH / m_SmoothScaleFactor;
	m_RectHeight = RECT_HEIGHT / m_SmoothScaleFactor;
	m_TranslationX = 0.0; //(RECT_WIDTH /2)/SmoothScaleFactor; 
	m_TranslationY = -(RECT_HEIGHT /2)/m_SmoothScaleFactor; 
	m_Broker->GetVisibleMap(m_VisibleMap);
	
}

void CSBMS::RenderSelected()
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

#if 0
void CSBMS::RenderLightOn()
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
#endif
void CSBMS::RenderAlarm()
{
		
	if(!m_Alarm)
		return;
		
	glPushMatrix();
	if(m_AlarmOn)
		SetColor(SYMBOL_ERROR_COLOR);
	else
		glColor4f(1.0f,1.0f,1.0f,0.3f);
	
	glTranslatef(m_LonMap,m_LatMap,0.0f);
	//glTranslatef(0.0,th/2,0.0f);
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = m_RectWidth * 1.5;
	nvDrawCircleArcFilled(&c,270,0);
		
	glPopMatrix();
		
}


void CSBMS::SetSymbolColor()
{
	switch(m_LightOn)
	{
		case LIGHT_ON:				SetColor(SYMBOL_LIGHT_ON_COLOR);	break;
		case LIGHT_OFF:				SetColor(SYMBOL_NORMAL_COLOR);		break;
		case LIGHT_NOT_AVAILABLE:	SetColor(SYMBOL_NO_MONITOR_COLOR);	break;
	}

}

void CSBMS::RenderBusy()
{
	if(!m_Busy)
		return;
		
	glPushMatrix();
	
	glTranslatef(m_LonMap,m_LatMap,0.0f);
	//glTranslatef(m_RectWidth/3,- m_RectWidth/3,0.0f);

	//glPointSize(10);
	//glLineWidth(2);
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = m_RectWidth*1.5;
	
		
	if(m_BusyOn)
		SetColor(SYMBOL_ERROR_COLOR);
	else
		glColor4f(1.0f,1.0f,1.0f,0.3f);
	
	nvDrawCircleArcFilled(&c,90,180);
	nvDrawPoint(0.0,0.0);
		
	glPopMatrix();

}

void CSBMS::RenderSBMS()
{
	SetSymbolColor();
	glPushMatrix();
		
	glTranslatef(m_LonMap,m_LatMap,0.0f);
	
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

void CSBMS::RenderRestricted()
{
	/*
	if(m_RenderRestricted)
	{
		glColor4f(1.0,0.0,0.0,0.1);
		nvCircle c;
		c.Center.x = m_LonMap;
		c.Center.y = m_LatMap;
		c.Radius = (double)GetRestrictedArea()/1852/GetMilesPerDegree(m_RLon,m_RLat);
		nvDrawCircleFilled(&c);
	}
	*/
}

void CSBMS::RenderGPS()
{	
	glColor4f(1.0f,1.0f,1.0f,0.6f);

	glPointSize(2);
	glBegin(GL_LINES);
		glVertex2f(m_GpsLonMap, m_GpsLatMap);
		glVertex2f(m_RLonMap,m_RLatMap);
	glEnd();
	
	glBegin(GL_POINTS);
		glVertex2f(m_GpsLonMap, m_GpsLatMap);
		glVertex2f(m_RLonMap,m_RLatMap);
	glEnd();

	glPointSize(1);
	
}

void CSBMS::RenderPositions()
{
	glEnable(GL_BLEND);
	glPointSize(3);
	glColor4f(0.0f,0.0f,1.0f,0.5f);
	if(m_PosBuffer.Length() > 0)
	{
		RenderGeometry(GL_LINE_STRIP,m_PosBuffer.GetRawData(),m_PosBuffer.Length());
		RenderGeometry(GL_POINTS,m_PosBuffer.GetRawData(),m_PosBuffer.Length());
	}
	
	glPointSize(1);
	glDisable(GL_BLEND);
	
}

void CSBMS::RenderNewReport()
{
	if(!m_NewReport)
		return;
	
	glPushMatrix();
		
	glTranslatef(m_LonMap,m_LatMap,0.0f);
	glTranslatef(-m_RectWidth/1.5,-m_RectWidth/1.5,0.0f);
	
	//nvCircle c;
	//c.Center.x = 0.0;
	//c.Center.y = 0.0;
	//c.Radius = m_RectWidth/4;
	
	//nvDrawCircleFilled(&c);
	
	glColor4f(1.0,1.0,1.0,0.8);
	glLineWidth(1);
	double x1 = m_RectWidth/3;
	double x2 = m_RectWidth/4;
	glBegin(GL_LINES);
		glVertex2f(-x1,x2);
		glVertex2f(x1,x2);

		glVertex2f(x1,x2);
		glVertex2f(x1,-x2);
		
		glVertex2f(x1,-x2);
		glVertex2f(-x1,-x2);
		
		glVertex2f(-x1,-x2);
		glVertex2f(-x1,x2);
			
		
		glVertex2f(-x1,-x2);
		glVertex2f(0,0);

		glVertex2f(x1,-x2);
		glVertex2f(0,0);

		
	glEnd();
	
	glPopMatrix();
	glLineWidth(1);
	
}

void CSBMS::RenderText(float x, float y, float vx, float vy, const wchar_t *format ...)
{	
	wchar_t buffer[128];
	va_list args;
	va_start(args,format);
	//swprintf_s(buffer,format,args);
	vswprintf ( buffer, 128, format, args );
	va_end(args);
	
	m_NameFont->Print(x,y,GetFontSize()/m_SmoothScaleFactor/DEFAULT_FONT_FACTOR,0,buffer,vx,vy);

}

void CSBMS::RenderText()
{
	if(!GetShowFontNames())
		return;
		
	RenderText(GetLonMap(),GetLatMap(),0.5f,-3.3f,GetInputVoltAsString());
	RenderText(GetLonMap(),GetLatMap(),0.5f,6.6f,GetAgeAsString());
					
	if(GetBusy())
		RenderText(GetLonMap(),GetLatMap(),-1.5f,-0.1f,GetCommandCountAsString());

}


void CSBMS::Render()
{

	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);

	SetValues();
	RenderSBMS();
	RenderRestricted();
	RenderBusy();
	RenderGPS();
	RenderNewReport();
	RenderAlarm();
	RenderPositions();
	RenderText();

	glDisable(GL_BLEND);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_SMOOTH);

}

void CSBMS::ShowAction()
{
	//if(m_SBMSActionDialog == NULL)
		m_SBMSActionDialog = new CSBMSActionDialog(this);
	m_SBMSActionDialog->ShowModal();
	delete m_SBMSActionDialog;
}

void CSBMS::ShowGraph()
{
	
	void *db = DBConnect();
	if(db == NULL)
		return;
	
	if(m_GraphDialog == NULL)
		m_GraphDialog = new CGraphDialog(NULL);
	CGraph *Graph = m_GraphDialog->GetGraph();

	wxString sql = wxString::Format(_("SELECT input_volt,local_utc_time_stamp FROM `%s` WHERE id_sbms='%d' ORDER BY local_utc_time_stamp"),TABLE_SBMS_STANDARD_REPORT,GetId());
	my_query(db,sql);
			
	void *result = db_result(db);
		
	char **row = NULL;
	if(result == NULL)
		return;
	
	Graph->Clear();
	int count = 0;
	float value = 0;
	int time = 0;
	int _time = 0;
	int seconds_to = 0;
	int seconds_from = 0;
	float min,max;
	min = max = 0;
	bool set = true;
	while(row = (char**)db_fetch_row(result))
	{
		nvPoint3f pt;
		
		value = atof(row[0]);
		time = atoi(row[1]);
		
		nvRGBA c;

		if(set)			{ min = value;	max = value; _time = time; seconds_from = time; set = false;}
		if(max < value)	{ max = value;}
		if(min > value)	{ min = value;}
		time = abs(time - _time);
		
		pt.x = time;
		pt.y = value;
		pt.z = 0;
		
		seconds_to = time  + _time;
		if(value <= GetLowerThreshold() || value  >= GetUpperThreshold())
		{
			c.A = 200; c.R = 255; c.G = 0; c.B = 0;
		}else{
			c.A = 200; c.R = 0; c.G = 255; c.B = 0;
		}
		
		Graph->AddPoint(pt);
		Graph->AddColor(c);
	}
	
	if(min == max)
		max += 0.1;

	if(seconds_from == seconds_to)
		seconds_to +=1;

	Graph->SetTimeFrom(seconds_from);
	Graph->SetTimeTo(seconds_to);
	Graph->SetMin(min);
	Graph->SetMax(max);
	
	Graph->Refresh();
	db_free_result(result);
	
	m_GraphDialog->SetTitle(wxString::Format(_("%s"),GetSymbolName()));
	m_GraphDialog->Layout();
	m_GraphDialog->Show();

	DBClose(db);
	
}

void CSBMS::Read()
{
	//fprintf(stderr,"SBMS\n");
	
	if(m_Broker == NULL)
		return;
	
	bool result = false;
		
	SetAlarms();		//flaga alarm exists na false
		
	if(CheckCommand())
		result = true;
	if(CheckAlarm())
		result = true;
	if(SetPositions())
		result = true;
			
	AlarmRemove();
	
	//}else{
		
		//m_Alarm = false;
		//m_Busy = false;
		//m_NewReport = false;
		//m_ValidGPS = false;
		//m_LightOn = LIGHT_NOT_AVAILABLE;
		//ClearPositions();
		//ClearAlarms();
	//}
	
	//CheckCollision();
			
}


//SET
void CSBMS::SetColor(int id)
{
	glColor4ub(GetColor(id).R,GetColor(id).G,GetColor(id).B,GetColor(id).A);
}

void CSBMS::SetRLon(double v)		
{	
	m_RLon = v;
}

void CSBMS::SetRLat(double v)		
{	
	m_RLat = v;
}

void CSBMS::SetRLonMap(double v)	
{	
	m_RLonMap = v;
}

void CSBMS::SetRLatMap(double v)	
{	
	m_RLatMap = v;
}

void CSBMS::SetGpsLon(double v)	
{	
	m_GpsLon = v;
}

void CSBMS::SetGpsLat(double v)	
{	
	m_GpsLat = v;
}

void CSBMS::SetGpsLonMap(double v)
{
	m_GpsLonMap = v;
}

void CSBMS::SetGpsLatMap(double v)
{	
	m_GpsLatMap = v;
}

void CSBMS::SetLon(double v)		
{	
	m_Lon = v;
}

void CSBMS::SetLat(double v)		
{	
	m_Lat = v;
}

void CSBMS::SetLonMap(double v)	
{
	m_LonMap = v;
}

void CSBMS::SetLatMap(double v)	
{	
	m_LatMap = v;
}

void CSBMS::SetAuto(bool v)
{
	m_Auto = v;
}

void CSBMS::SetInputVolt(float v)
{
	m_InputVolt = v;
}

void CSBMS::SetExists(bool v)
{
	m_Exists = v;
}

void CSBMS::SetForcedOff(int v)
{
	m_ForcedOff = v;
}

void CSBMS::SetPhotoCellNightTime(bool v)
{
	m_PhotoCellNightTime = v;
}

void CSBMS::SetLightOn(int v)
{
	m_LightOn = v;
}

void CSBMS::SetMMSI(int v)
{
	m_MMSI = v;
}

void CSBMS::SetMonitoring(int v)
{
	m_Monitoring = v;
}

void CSBMS::SetNvTime(nvtime_t dt)
{
	m_nvTime = dt;
}	

void CSBMS::SetTimestamp(int v)
{
	m_Timestamp = v;
}

void CSBMS::SetAge(int v)
{
	m_Age = v;
}

void CSBMS::SetAge(wxString v)
{
	m_AgeString = v;
}

void CSBMS::SetNewReport(bool v)
{
	m_NewReport = v;
}

void CSBMS::SetNoSBMS(bool v)
{
	m_NoSBMS = v;
}

void CSBMS::SetIdBaseStation(int v)
{
	m_IdBaseStation = v;
}

void CSBMS::SetBaseStationName(wxString v)
{
	m_BaseStationName = v;
}

void CSBMS::SetValidGPS(bool v)
{
	m_ValidGPS = v;
}

void CSBMS::SetSBMSID(int v)
{
	m_SBMSID = v;
}
void CSBMS::SetCharging(int v)
{
	m_Charging = v;
}

void CSBMS::SetNewAlarmCount(int v)
{
	m_NewAlarmCount = v;
}

//GET
int CSBMS::GetSBMSID()
{
	return m_SBMSID;
}

int CSBMS::GetBaseStationId() 
{
	return m_IdBaseStation;
}
/*
double CSBMS::GetRLon()
{		
	return m_RLon;
}

double CSBMS::GetRLat()
{		
	return m_RLat;
}

double CSBMS::GetRLonMap()
{	
	return m_RLonMap;
}

double CSBMS::GetRLatMap()
{	
	return m_RLatMap;
}
*/
double CSBMS::GetGpsLon()
{	
	return m_GpsLon;
}

double CSBMS::GetGpsLat()
{	
	return m_GpsLat;
}

double CSBMS::GetGpsLonMap()
{	
	return m_GpsLonMap;
}

double CSBMS::GetGpsLatMap()
{	
	return m_GpsLatMap;
}

double CSBMS::GetLon()
{		
	return m_Lon;
}

double CSBMS::GetLat()
{		
	return m_Lat;
}

double CSBMS::GetLonMap()
{	
	return m_LonMap;
}

double CSBMS::GetLatMap()
{	
	return m_LatMap;
}

int CSBMS::GetAlarmCount()
{
	return m_AlarmList.Length();
}

CAlarm *CSBMS::GetAlarm(int v)
{
	return m_AlarmList.Get(v);
}

int CSBMS::GetAlarmId(int v)
{
	return m_AlarmList.Get(v)->GetId();
}

wxString CSBMS::GetAlarmName(int v)
{
	return m_AlarmList.Get(v)->GetName();
}

bool CSBMS::GetExists()
{
	return m_Exists;
}

int CSBMS::GetLightOn()
{
	return m_LightOn;
}

wxString CSBMS::GetCommandCountAsString()
{
	return wxString::Format(_("%d"),m_CommandCount);

}

wxString CSBMS::GetReportCountAsString()
{
	return wxString::Format(_("%d"),m_ReportCount);
}

wxString CSBMS::GetInputVoltAsString()
{
	return wxString::Format(_("%4.2f V"),m_InputVolt);
}

int CSBMS::GetMMSI()
{
	return m_MMSI;
}

nvtime_t CSBMS::GetNvTime()
{
	return m_nvTime;
}

wxString CSBMS::GetAgeAsString()
{
	return m_AgeString;
}

int CSBMS::GetMonitoring()
{
	return m_Monitoring;
}

bool CSBMS::GetAuto()
{
	return m_Auto;
}

float CSBMS::GetInputVolt()
{
	return m_InputVolt;
}

int CSBMS::GetForcedOff()
{
	return m_ForcedOff;
}

bool CSBMS::GetNoSBMS()
{
	return m_NoSBMS;
}

int CSBMS::GetCharging()
{
	return m_Charging;
}

wxString CSBMS::GetBaseStationName()
{
	return m_BaseStationName;
}

wxString CSBMS::GetChargingAsString()
{
	switch(m_Charging)
	{
		case CHARGING_TRUE:			return  GetMsg(MSG_CHARGING);
		case CHARGING_FALSE:		return	GetMsg(MSG_DISCHARGING);
		case CHARGING_NOT_AVAILABLE:return  GetMsg(MSG_NA);
	}
	
	return GetMsg(MSG_NA);
}

int CSBMS::GetNewAlarmCount()
{
	return m_NewAlarmCount;
}

int CSBMS::GetProtocolVersion()
{
	return m_ProtocolVersion;
}

void CSBMS::SetBusy(bool v)
{
	m_Busy = v;
}

void CSBMS::SetAlarm(bool v)
{
	m_Alarm = v;
}

wxString CSBMS::GetDriverHtml(int v)
{

	wxString str;
	//str.Append(_("<table border=0 cellpadding=0 cellspacing=0 width=100%>"));
	//str << wxString::Format(_("<tr><td><font size=3><b>%s</b></font></td></tr>"),GetName());
	//str << wxString::Format(_("<tr><td><font size=3>%4.2f V</font></td></tr>"), GetInputVolt());
	//str.Append(_("</table>"));
	
	str.Append(_("<table border=0 cellpadding=0 cellspacing=0 width=100%>"));
	
	for(int i = 0; i < GetAlarmCount();i++)
	{
		CAlarm *alarm = GetAlarm(i);
		nvRGBA c = GetAlarmTypeColor(alarm->GetType());
		str << wxString::Format(_("<tr><td><font color=#%02X%02X%02X size=3>%s</font></td></tr>"),c.R,c.G,c.B,alarm->GetName());
	}
		
	str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td>"),GetLightOnAsString(GetLightOn())));
	str.Append(_("<td rowspan=2 align=right width=80>"));
	if(GetInputVolt() > GetUpperThreshold() || GetInputVolt() < GetLowerThreshold())
		str.Append(wxString::Format(_("<a target=0 href='%d'><font size=4 color=red>%s</font></a>"),v,GetInputVoltAsString()));
	else
		str.Append(wxString::Format(_("<a target=0 href='%d'><font size=4>%s</font></a>"),v, GetInputVoltAsString()));
		
	str.Append(_("</td>"));
	str.Append(wxString::Format(_("<tr><td><font size=3>%s</font></td></tr>"),GetAutoAsString(GetAuto())));
	str << wxString::Format(_("<tr><td><font size=3>%s</font></td></tr>"),GetChargingAsString());
	str << wxString::Format(_("<tr><td><font size=3>%s</font></td></tr>"),GetAgeAsString());
	//str << wxString::Format(_("<tr><td> </td></tr>"),GetBaseStationName());
	str.Append(_("</table>"));
	return str;

}

wxString CSBMS::GetAlarmHtml()
{
	wxString str;
	
	if(m_AlarmList.Length() > 0)
	{
		str.Append(_("<hr>"));
		str.Append(wxString::Format(_("<font size=2><b>%s(%d)</b></font><br><br>"), GetMsg(MSG_ALARM),m_AlarmList.Length()));
		str.Append(_("<table border=0 cellpadding=0 cellspacing=0 width=100%>"));
		
		for(int i = 0; i < m_AlarmList.Length();i++)
		{
			CAlarm *Alarm = m_AlarmList.Get(i);
			nvRGBA c = GetAlarmTypeColor(Alarm->GetType());
			str << wxString::Format(_("<tr><td><font color=#%02X%02X%02X size=2>%s</font></td><td><font size=2>%s</font></td></tr>"),c.R,c.G,c.B,Alarm->GetName(),Alarm->GetAlarmOnDate());
		}
	
		str.Append(_("</table>"));
	}
	
	return str;
}

wxString CSBMS::GetDriverFullHtml()
{
	void *db = DBConnect();

	if(db == NULL)
		return wxEmptyString;

	wxString str;
	wxString sql = wxString::Format(_("SELECT * FROM `%s` WHERE id ='%d'"),TABLE_SBMS,GetId());
	my_query(db,sql);
			
	void *result = db_result(db);
		
	char **row = NULL;
	if(result == NULL)
		return wxEmptyString;
		
	row = (char**)db_fetch_row(result);
	if(row)
	{
		str.Append(_("<hr>"));
		str.Append(wxString::Format(_("<font size=2><b>%s</b></font><br><br>"), GetMsg(MSG_DRIVER)));
		str.Append(_("<table border=0 cellpadding=0 cellspacing=0 width=100%>"));
		str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td></tr>"),GetLightOnAsString(GetLightOn())));
		str.Append(wxString::Format(_("<tr><td><font size=2><b>%s</b></font></td></tr>"),Convert(row[FI_SBMS_NAME])));
						
		int phone = atoi(row[FI_SBMS_PHONE]);
		if(phone)
			str.Append(wxString::Format(_("<tr><td><font size=2><b>%d</b></font></td></tr>"),phone));

		int mmsi = atoi(row[FI_SBMS_MMSI]);
		if(mmsi)
			str.Append(wxString::Format(_("<tr><td><font size=2><b>%d</b></font></td></tr>"),mmsi));
		
		//nvtime_t dt;
		//nvdatetime(atoi(row[FI_SBMS_LOCAL_UTC_TIME]),&dt);
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_DATE_TIME_UTC),Convert(row[FI_SBMS_LOCAL_UTC_TIME])));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_LATITUDE),FormatLatitude(atof(row[FI_SBMS_LAT]),DEFAULT_DEGREE_FORMAT)));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_LONGITUDE),FormatLongitude(atof(row[FI_SBMS_LON]),DEFAULT_DEGREE_FORMAT)));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_INPUT_VOLT),row[FI_SBMS_INPUT_VOLT]));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>100%%</b></font></td></tr>"),GetMsg(MSG_POWER_OF_LIGHT)));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_MONITORED_CHANNELS),GetMonitoredChannels(atoi(row[FI_SBMS_MONITORED_CHANNELS]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_OVERLOAD_CHANNELS),GetOverloadChannels(atoi(row[FI_SBMS_OVERLOAD_CHANNELS]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_DOWN_CHANNELS),GetDownChannels(atoi(row[FI_SBMS_DOWN_CHANNELS]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_ANALOG_VALUE),row[FI_SBMS_ANALOG_VALUE]));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_CALIBRATED),GetOnOff(atoi(row[FI_SBMS_MODE_CALIBRATED]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_FORCED_OFF),GetOnOff(atoi(row[FI_SBMS_MODE_FORCED_OFF]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_PHOTOCELL_NIGHT_TIME),GetPhotoCellValue(atoi(row[FI_SBMS_ANALOG_PIN]), atoi(row[FI_SBMS_ANALOG_VALUE]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_FAULT_OUTPUT),GetOnOff(atoi(row[FI_SBMS_MODE_FAULT_OUTPUT]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_SOLAR_CHARGER_ON),GetOnOff(atoi(row[FI_SBMS_MODE_SOLAR_CHARGER_ON]))));
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_SEASON_CONTROL),GetOnOff(atoi(row[FI_SBMS_MODE_SEASON_CONTROL]))));
		
		bool alarm = false;
		for(int i = 0; i < GetAlarmCount();i++)
		{
			if (GetAlarm(i)->GetIdAlarm() == ALARM_COMMUNICATION_TIMEOUT)
				alarm = true;
		}
		
		str.Append(wxString::Format(_("<tr><td><font size=2>%s</font></td><td><font size=2><b>%s</b></font></td></tr>"),GetMsg(MSG_SYNC),GetOnOff(!alarm)));

		str.Append(_("</table>"));
		
	}
		
	db_free_result(result);

	DBClose(db);

	return str;

}

void CSBMS::LightOn()
{
	_SetCommand(COMMAND_LIGHT_ON,GetId(),GetMMSI(),GetSBMSID(),GetBaseStationId(), true);
}

void CSBMS::LightOff()
{
	_SetCommand(COMMAND_LIGHT_OFF,GetId(),GetMMSI(),GetSBMSID(),GetBaseStationId(), false);
}

void CSBMS::AutoManagement()
{
	_SetCommand(COMMAND_AUTO_MANAGEMENT,GetId(),GetMMSI(),GetSBMSID(),GetBaseStationId(), false);
}

void CSBMS::Reset()
{
	_SetCommand(COMMAND_RESET,GetId(),GetMMSI(),GetSBMSID(),GetBaseStationId(), false);
}

void CSBMS::GetTime()
{
	_SetCommand(COMMAND_GET_TIME,GetId(),GetMMSI(),GetSBMSID(),GetBaseStationId(), true);
}

void CSBMS::GetUptime()
{
	_SetCommand(COMMAND_GET_UPTIME,GetId(),GetMMSI(),GetSBMSID(),GetBaseStationId(), true);
}
