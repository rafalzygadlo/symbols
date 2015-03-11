#include "sector.h"
#include "conf.h"
#include "tools.h"
#include "geometrytools.h"
#include <wx/valnum.h>
#include "navidrawer.h"

CSector::CSector()
{
			
}

CSector::~CSector()
{

}

void CSector::RenderSelected()
{
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = m_Radius*1.2;
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glColor4ub(m_Color.Red(),m_Color.Green(),m_Color.Blue(),255);
	nvDrawCircleArcFilled(&c,m_SectorFrom,m_SectorTo);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_BLEND);

}

void CSector::Render()
{
	nvCircle c;
	c.Center.x = 0.0;
	c.Center.y = 0.0;
	c.Radius = m_Radius;
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glColor4ub(m_Color.Red(),m_Color.Green(),m_Color.Blue(),100);
	nvDrawCircleArcFilled(&c,m_SectorFrom,m_SectorTo);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_BLEND);
		
}

int CSector::GetId()
{
	return m_Id;
}

void CSector::SetId(int v)
{
	m_Id = v;
}

void CSector::SetColor(wxColor color)
{
	m_Color = color;
}

void CSector::SetCoverage(float v)
{
	m_Coverage = v;
}

void CSector::SetSectorFrom(float v)
{
	m_SectorFrom = v;
}

void CSector::SetSectorTo(float v)
{
	m_SectorTo = v;
}

void CSector::SetRadius(float v)
{
	m_Radius = v;
}

//GET
wxColor CSector::GetColor()
{
	return m_Color;
}

float CSector::GetCoverage()
{
	return m_Coverage;
}

float CSector::GetSectorFrom()
{
	return m_SectorFrom;
}

float CSector::GetSectorTo()
{
	return m_SectorTo;
}
