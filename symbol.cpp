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
#include "commanddialog.h"


CSymbol::CSymbol(CNaviBroker *broker)
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
	m_Step = 0;
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
	m_IdSBMS = 0;
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
	m_Init = false;
	m_AgeString = "N/A";
	m_DB = NULL;
	m_GraphDialog = NULL;
	m_Charging = false;
	m_NewAlarmCount = 0;
	m_ProtocolVersion = 0;
	m_NameFont = NULL;
	
}

CSymbol::~CSymbol()
{	
	ClearAlarms();
	m_Broker = NULL;
	
	if(m_GraphDialog)
		delete m_GraphDialog;
	
}

void CSymbol::SetFont(nvFastFont *ptr)
{
	m_NameFont = ptr;
}

void CSymbol::SetDB(void *db)
{
	m_DB = db;
}

bool CSymbol::GetBusy()
{
	return m_Busy;
}

void CSymbol::ClearPositions()
{
	m_PosBuffer.Clear();
}

void CSymbol::ClearAlarms()
{
	for(size_t i = 0; i < m_AlarmList.Length(); i++)
	{
		CAlarm *ptr = (CAlarm*)m_AlarmList.Get(i);
		delete ptr;
		
	}

	m_AlarmList.Clear();

}

CAlarm *CSymbol::AlarmExists(int id)
{
	for(size_t i = 0; i < m_AlarmList.Length(); i++)
	{
		CAlarm *ptr = (CAlarm*)m_AlarmList.Get(i);
		if(id == ptr->GetId())
			return ptr;
	}

	return NULL;
}

void CSymbol::AlarmRemove()
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

void CSymbol::SetAlarms()
{
	for(size_t i = 0; i < m_AlarmList.Length(); i++)
	{
		CAlarm *ptr = (CAlarm*)m_AlarmList.Get(i);
		ptr->SetExists(false);
	}
		
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
	
	return true;
}

bool CSymbol::CheckAlarm()
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
	wxString sql = wxString::Format(_("SELECT * FROM `%s`,`%s` WHERE id_sbms='%d' AND active='%d' AND id_alarm=`%s`.id"),TABLE_SBMS_ALARM,TABLE_ALARM, m_IdSBMS,ALARM_ACTIVE,TABLE_ALARM);
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
		Alarm->SetName(Convert(row[FI_ALARM_NAME + offset]));
		Alarm->SetConfirmed(atoi(row[FI_SBMS_ALARM_CONFIRMED]));
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

bool  CSymbol::CheckCommand()
{
	m_CommandTick++;
	m_CommandTickOn++;
	m_BusyOn = !m_BusyOn;
	
	if(m_CommandTickOn >= CHECK_COMMAND_TICK_ON)
		m_CommandTickOn = 0;
	
	if(m_CommandTick <= CHECK_COMMAND_TICK)
		return false;
	
	wxString sql;
	sql = wxString::Format(_("SELECT count(*) FROM %s WHERE id_sbms='%d' AND status='%d' AND active='%d'"),TABLE_COMMAND,m_IdSBMS,COMMAND_STATUS_NEW,COMMAND_ACTIVE);
	
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
	wxString sql = wxString::Format(_("SELECT lon,lat FROM `%s` WHERE valid_lon_lat='%d' AND id_sbms='%d' ORDER BY local_utc_time_stamp DESC LIMIT 10"),TABLE_SBMS_STANDARD_REPORT,VALID_LON_LAT,m_IdSBMS);
		
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

bool CSymbol::CheckReport()
{
	m_ReportTick++;
	
	if(m_ReportTick <= CHECK_REPORT_TICK)
		return false;
			
	wxString sql = wxString::Format(_("SELECT count(*) FROM %s WHERE id_sbms='%d'"),TABLE_SBMS_STANDARD_REPORT,m_IdSBMS);

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
	int factor = GetScaleFactor();
	if( m_Scale > factor )
		m_SmoothScaleFactor = m_Scale;
	else
		m_SmoothScaleFactor = factor;
}

void CSymbol::SetValues()
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

#if 0
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
#endif
void CSymbol::RenderAlarm()
{
	if(m_NoSBMS)
		return; 
	
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


void CSymbol::SetSymbolColor()
{
	if(m_Monitoring == SYMBOL_NOT_IN_MONITORING || m_NoSBMS)
	{
		SetColor(SYMBOL_NO_MONITOR_COLOR);
		return;
	}
	
	switch(m_LightOn)
	{
		case LIGHT_ON:				SetColor(SYMBOL_LIGHT_ON_COLOR);	break;
		case LIGHT_OFF:				SetColor(SYMBOL_NORMAL_COLOR);		break;
		case LIGHT_NOT_AVAILABLE:	SetColor(SYMBOL_NO_MONITOR_COLOR);	break;
	}

}

void CSymbol::RenderBusy()
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

void CSymbol::RenderSymbol()
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

void CSymbol::RenderRestricted()
{
	if(m_RenderRestricted)
	{
		glColor4f(1.0,0.0,0.0,0.1);
		nvCircle c;
		c.Center.x = m_LonMap;
		c.Center.y = m_LatMap;
		c.Radius = (double)GetRestrictedArea()/1852/GetMilesPerDegree(m_RLon,m_RLat);
		nvDrawCircleFilled(&c);
	}
}

void CSymbol::RenderGPS()
{
	if(!m_ValidGPS)
		return;

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

void CSymbol::RenderPositions()
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

void CSymbol::RenderNewReport()
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

void CSymbol::RenderNoSBMS()
{
	if(!m_NoSBMS)
		return;
	
	glPushMatrix();
		
	glTranslatef(m_LonMap,m_LatMap,0.0f);
	glColor4f(1.0,0.0,0.0,0.5);
	glLineWidth(5);
	glBegin(GL_LINES);
		glVertex2f(m_RectWidth/2,m_RectWidth/2);
		glVertex2f(-m_RectWidth/2,-m_RectWidth/2);
		glVertex2f(m_RectWidth/2,-m_RectWidth/2);
		glVertex2f(-m_RectWidth/2,m_RectWidth/2);
	glEnd();

	glPopMatrix();

}

void CSymbol::RenderText(float x, float y, float vx, float vy, const wchar_t *format ...)
{	
	wchar_t buffer[128];
	va_list args;
	va_start(args,format);
	//swprintf_s(buffer,format,args);
	vswprintf ( buffer, 128, format, args );
	va_end(args);
	
	m_NameFont->Print(x,y,GetFontSize()/m_SmoothScaleFactor/DEFAULT_FONT_FACTOR,0,buffer,vx,vy);

}

void CSymbol::RenderInfo()
{
	if(!GetShowFontNames())
		return;

	RenderText(GetLonMap(),GetLatMap(),0.5f,3.0f,GetName());
	RenderText(GetLonMap(),GetLatMap(),0.5f,4.1f,GetSBMSName());
	if(GetMonitoring() == SYMBOL_IN_MONITORING)
	{
		RenderText(GetLonMap(),GetLatMap(),0.5f,-3.3f,GetInputVoltAsString());
		RenderText(GetLonMap(),GetLatMap(),0.5f,5.3f,GetAgeAsString());
		RenderText(GetLonMap(),GetLatMap(),0.5f,6.4f,GetMonitoringAsString(GetMonitoring()));
	}else{
		RenderText(GetLonMap(),GetLatMap(),0.5f,-3.0f,GetMonitoringAsString(GetMonitoring()));
	}
			
	if(GetBusy())
		RenderText(GetLonMap(),GetLatMap(),-1.5f,-0.1f,GetCommandCountAsString());

}


void CSymbol::Render()
{
	if(!m_Init)
		return;

	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);

	SetValues();
		
	RenderNoSBMS();
	RenderSymbol();
//	RenderIce();
	RenderRestricted();
	RenderBusy();
	RenderGPS();
	RenderNewReport();
	RenderAlarm();
	RenderPositions();
	RenderInfo();

	glDisable(GL_BLEND);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_SMOOTH);

}

void CSymbol::ShowManagement(CSymbol *v)
{
	if(v == NULL)
		return;
	
	if(!v->GetNoSBMS())
	{
		CCommandDialog *CommandDialog = new CCommandDialog(m_DB,NULL,v);
		CCommandPanel *ptr =  CommandDialog->GetCommandPanel();

		//ptr->SetForcedOff(v->GetForcedOff());
		//ptr->SetAuto(v->GetAuto());
			
		CommandDialog->ShowModal();
		delete CommandDialog;
	
	}else{
			wxMessageBox(GetMsg(MSG_NO_SBMS_RECORD));
	}
}

void CSymbol::ShowGraph()
{
	void *db = DBConnect();
	if(db == NULL)
		return;
	
	if(m_GraphDialog == NULL)
		m_GraphDialog = new CGraphDialog(NULL,this);
	CGraph *Graph = m_GraphDialog->GetGraph();

	wxString sql = wxString::Format(_("SELECT input_volt,local_utc_time_stamp FROM `%s` WHERE id_sbms='%d' ORDER BY local_utc_time_stamp"),TABLE_SBMS_STANDARD_REPORT,GetIdSBMS());
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
	
	m_GraphDialog->SetTitle(wxString::Format(_("%s"),GetName()));
	m_GraphDialog->Layout();
	m_GraphDialog->Show();

	DBClose(db);
}

void CSymbol::OnTick(void *db)
{
	m_DB = db;
	if(m_Broker == NULL)
		return;
	
	bool result = false;
		
	if(m_NoSBMS)
		return;
	
	SetAlarms();		//flaga alarm exists na false
	
	if(m_Monitoring == SYMBOL_IN_MONITORING)
	{
		if(CheckCommand())
			result = true;
		if(CheckAlarm())
			result = true;
		if(SetPositions())
			result = true;
			
		AlarmRemove();
	
	}else{
		
		m_Alarm = false;
		m_Busy = false;
		m_NewReport = false;
		m_ValidGPS = false;
		m_LightOn = LIGHT_NOT_AVAILABLE;
		ClearPositions();
		ClearAlarms();
	}
	
	CheckCollision();
			
}


//SET
void CSymbol::SetColor(int id)
{
	glColor4ub(GetColor(id).R,GetColor(id).G,GetColor(id).B,GetColor(id).A);
}

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

void CSymbol::SetGpsLon(double v)	
{	
	m_GpsLon = v;
}

void CSymbol::SetGpsLat(double v)	
{	
	m_GpsLat = v;
}

void CSymbol::SetGpsLonMap(double v)
{
	m_GpsLonMap = v;
}

void CSymbol::SetGpsLatMap(double v)
{	
	m_GpsLatMap = v;
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

void CSymbol::SetSBMSName(wxString v)
{
	m_SBMSName = v;
}

void CSymbol::SetAuto(bool v)
{
	m_Auto = v;
}

void CSymbol::SetInputVolt(float v)
{
	m_InputVolt = v;
}

void CSymbol::SetExists(bool v)
{
	m_Exists = v;
}

void CSymbol::SetForcedOff(int v)
{
	m_ForcedOff = v;
}

void CSymbol::SetPhotoCellNightTime(bool v)
{
	m_PhotoCellNightTime = v;
}

void CSymbol::SetLightOn(int v)
{
	m_LightOn = v;
}

void CSymbol::SetMMSI(int v)
{
	m_MMSI = v;
}

void CSymbol::SetMonitoring(int v)
{
	m_Monitoring = v;
}

void CSymbol::SetNvTime(nvtime_t dt)
{
	m_nvTime = dt;
}	

void CSymbol::SetTimestamp(int v)
{
	m_Timestamp = v;
}

void CSymbol::SetAge(int v)
{
	m_Age = v;
}

void CSymbol::SetAge(wxString v)
{
	m_AgeString = v;
}

void CSymbol::SetNewReport(bool v)
{
	m_NewReport = v;
}

void CSymbol::SetNoSBMS(bool v)
{
	m_NoSBMS = v;
}

void CSymbol::SetIdBaseStation(int v)
{
	m_IdBaseStation = v;
}

void CSymbol::SetBaseStationName(wxString v)
{
	m_BaseStationName = v;
}

void CSymbol::SetValidGPS(bool v)
{
	m_ValidGPS = v;
}

void CSymbol::SetInit(bool v)
{
	m_Init = v;
}

void CSymbol::SetSBMSID(int v)
{
	m_SBMSID = v;
}
void CSymbol::SetCharging(int v)
{
	m_Charging = v;
}

void CSymbol::SetChargingAsString(wxString v)
{
	m_ChargingString = v;
}

void CSymbol::SetNewAlarmCount(int v)
{
	m_NewAlarmCount = v;
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

double CSymbol::GetGpsLon()
{	
	return m_GpsLon;
}

double CSymbol::GetGpsLat()
{	
	return m_GpsLat;
}

double CSymbol::GetGpsLonMap()
{	
	return m_GpsLonMap;
}

double CSymbol::GetGpsLatMap()
{	
	return m_GpsLatMap;
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

int CSymbol::GetAlarmCount()
{
	return m_AlarmList.Length();
}
CAlarm *CSymbol::GetAlarm(int v)
{
	return m_AlarmList.Get(v);
}

int CSymbol::GetAlarmId(int v)
{
	return m_AlarmList.Get(v)->GetId();
}

wxString CSymbol::GetAlarmName(int v)
{
	return m_AlarmList.Get(v)->GetName();
}

wxString CSymbol::GetName()
{
	return m_Name;
}

wxString CSymbol::GetNumber()
{
	return m_Number;
}

wxString CSymbol::GetSBMSName()
{
	return m_SBMSName;
}

bool CSymbol::GetExists()
{
	return m_Exists;
}

int CSymbol::GetLightOn()
{
	return m_LightOn;
}

wxString CSymbol::GetCommandCountAsString()
{
	return wxString::Format(_("%d"),m_CommandCount);

}

wxString CSymbol::GetReportCountAsString()
{
	return wxString::Format(_("%d"),m_ReportCount);
}

wxString CSymbol::GetInputVoltAsString()
{
	return wxString::Format(_("%4.2f V"),m_InputVolt);
}

int CSymbol::GetMMSI()
{
	return m_MMSI;
}

nvtime_t CSymbol::GetNvTime()
{
	return m_nvTime;
}

wxString CSymbol::GetAgeAsString()
{
	return m_AgeString;
}

int CSymbol::GetMonitoring()
{
	return m_Monitoring;
}

bool CSymbol::GetInit()
{
	return m_Init;
}

bool CSymbol::GetAuto()
{
	return m_Auto;
}

float CSymbol::GetInputVolt()
{
	return m_InputVolt;
}

int CSymbol::GetForcedOff()
{
	return m_ForcedOff;
}

bool CSymbol::GetNoSBMS()
{
	return m_NoSBMS;
}

int CSymbol::GetCharging()
{
	return m_Charging;
}

wxString CSymbol::GetBaseStationName()
{
	return m_BaseStationName;
}

wxString CSymbol::GetChargingAsString()
{
	return m_ChargingString;
}

int CSymbol::GetNewAlarmCount()
{
	return m_NewAlarmCount;
}

int CSymbol::GetProtocolVersion()
{
	return m_ProtocolVersion;
}

void CSymbol::SetBusy(bool v)
{
	m_Busy = v;
}

void CSymbol::SetAlarm(bool v)
{
	m_Alarm = v;
}