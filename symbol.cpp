#include <wx/wx.h>
#include "symbol.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "images/icon.h"
#include "navidrawer.h"
#include "geometrytools.h"

CSymbol::CSymbol(void *db, CNaviBroker *broker)
{
	m_Broker = broker;
	m_DB = db;
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
	m_CharacteristicId = 0;	
	m_CommandTick = CHECK_COMMAND_TICK;
	m_BlinkTick = 0;
	m_Busy = false;
	m_Ticker0 = NULL;
	m_Ticker1 = NULL;
	
}

CSymbol::~CSymbol()
{
	m_Ticker0->Stop();
	delete m_Ticker0;
	m_Ticker1->Stop();
	delete m_Ticker1;
}

void CSymbol::Start()
{
	m_Ticker0 = new CTicker(this,TICK_SYMBOL_BLINK);
	m_Ticker0->Start(100);

	m_Ticker1 = new CTicker(this,TICK_SYMBOL_COMMAND);
	m_Ticker1->Start(500);

}

void CSymbol::Read()
{
	return;
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

}

void CSymbol::OnBlink()
{
	Blink();
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

void CSymbol::OnCommand()
{
	GetMutex()->Lock();
	CheckCommand();
	GetMutex()->Unlock();
	m_Broker->Refresh(m_Broker->GetParentPtr());
}

void  CSymbol::CheckCommand()
{
	m_CommandTick++;
	m_BusyOn = !m_BusyOn;
	if(m_CommandTick <= CHECK_COMMAND_TICK)
		return;
		
	wxString sql = wxString::Format(_("SELECT * FROM %s WHERE id_symbol='%d'"),TABLE_COMMAND,m_Id);
	my_query(m_DB,sql);
	void *result = db_result(m_DB);
	
    char **row = NULL;
	if(result == NULL)
		return;
	
	m_Busy = false;
	while(row = (char**)db_fetch_row(result))
	{
		int cmd;
		sscanf(row[FI_COMMAND_ID],"%d",&cmd);
		m_Busy = true;
	}
	
	db_free_result(result);
		
	m_CommandTick = 1;
	
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


void CSymbol::RenderLightOn()
{
	if(!m_LightOn)
		return;
		
	glPushMatrix();
	glColor4f(1.0f,1.0f,1.0f,0.9f);
	glTranslatef(m_Lon,m_Lat,0.0f);

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

void CSymbol::RenderBusy()
{
	if(!m_Busy)
		return;

	float angle = (float)(360.0/CHECK_COMMAND_TICK) * m_CommandTick;

	float x = 0.0; //m_RectWidth/4 * cos(nvToRad(angle));
	float y = 0.0; //m_RectWidth/4 * sin(nvToRad(angle));

	glPushMatrix();
	glColor4f(1.0,0.0f,0.0f,0.8);
	glTranslatef(m_Lon + m_RectWidth/2,m_Lat - m_RectWidth,0.0f);

	glPointSize(10);
	glLineWidth(2);
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = m_RectWidth/4;
	nvDrawCircle(&c);
	
	if(m_BusyOn)
		glColor4f(1.0,0.0f,0.0f,0.8);
	else
		glColor4f(1.0,1.0f,1.0f,0.8);
	
	nvDrawPoint(x,y);
	glPopMatrix();
	
}

void CSymbol::RenderSymbol()
{
	glEnable(GL_TEXTURE_2D);
	
	if(m_LightOn)
		glColor4f(1.0f,1.0f,1.0f,0.8f);
	else
		glColor4f(0.0f,0.0f,0.0f,0.8f);
	
	glBindTexture( GL_TEXTURE_2D, m_TextureID_0);
	glPushMatrix();
	glTranslatef(m_Lon,m_Lat,0.0f);
		
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,1.0f); glVertex2f(  m_RectWidth/2 + m_TranslationX,  -m_RectHeight/2 + m_TranslationY);
		glTexCoord2f(1.0f,0.0f); glVertex2f(  m_RectWidth/2 + m_TranslationX,   m_RectHeight/2 + m_TranslationY);
		glTexCoord2f(0.0f,0.0f); glVertex2f( -m_RectWidth/2 + m_TranslationX,   m_RectHeight/2 + m_TranslationY);
		glTexCoord2f(0.0f,1.0f); glVertex2f( -m_RectWidth/2 + m_TranslationX,  -m_RectHeight/2 + m_TranslationY);
	glEnd();
	
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

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
	//RenderLightOn();
	RenderSymbol();
	RenderBusy();
		
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

//GET
int CSymbol::GetId()
{
	return m_Id;
}

double CSymbol::GetLon()
{
	return m_Lon;
}

double CSymbol::GetLat()
{
	return m_Lat;
}
