#include <wx/wx.h>
#include "symbol.h"
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "images/icon.h"
#include "navidrawer.h"

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
	m_On = true;
	m_FirstTime = true;
	m_Step = 0;
	m_Tick = 0;
	m_CharacteristicId = 0;	
}

CSymbol::~CSymbol()
{
	m_Ticker->Stop();
	delete m_Ticker;
}

void CSymbol::Start()
{
	m_Ticker = new CTicker(this,TICK_SYMBOL);
	m_Ticker->Start(100);
}

void CSymbol::Read()
{

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

void CSymbol::OnTick()
{
	if(m_OnList.Length() == 0)
		return;
		
	m_Tick++;	
	SOnOff ptr = m_OnList.Get(m_Step);
	
	if(m_On)
	{
		if(ptr.on <= m_Tick)
		{
			m_On = false;
			m_Tick = 0;
		}
	}

	if(!m_On)
	{
		if(ptr.off <= m_Tick)
		{
			m_On = true;
			m_Tick = 0;
			m_Step++;
		}
	}
	
	if(m_Step == m_OnList.Length())
	{
		m_Step = 0;
	}
	
		
	m_Broker->Refresh(m_Broker->GetParentPtr());
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

void CSymbol::RenderOn()
{
	if(!m_On)
		return;
		
	glEnable(GL_POINT_SMOOTH);
	glColor4f(1.0f,1.0f,1.0f,0.9f);
	
	glPushMatrix();
	glTranslatef(m_Lon,m_Lat,0.0f);

	glPointSize(10);
	glBegin(GL_POINTS);
		glVertex2f(  0.0,  0.0);
	glEnd();

	glPopMatrix();

	glDisable(GL_POINT_SMOOTH);
}

void CSymbol::RenderSymbol()
{
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	
	glColor4f(1.0f,1.0f,1.0f,0.8f);
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
	glDisable(GL_TEXTURE_2D);

}


void CSymbol::Render()
{
	if(m_FirstTime)
	{
		CreateTextures();
		m_FirstTime = false;
	}
	
	SetValues();
	RenderOn();
	RenderSymbol();
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

void CSymbol::SetCharacteristicId(int v)
{
	m_CharacteristicId = v;
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
