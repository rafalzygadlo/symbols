#include "driver.h"

CDriver::CDriver()
{
	m_Id = 0;
	m_Type;
	wxString m_Name;	
}

CDriver::~CDriver()
{
	
}

//SET
void CDriver::SetId(int v)
{
	m_Id = v;
}

void CDriver::SetName(wxString v)
{
	m_Name = v;
}

void CDriver::SetType(int v)
{
	m_Type = v;
}

void CDriver::SetIdBaseStation(int v)
{
	int v1 = 0;
}

void CDriver::SetMMSI(int v)
{

}

void CDriver::SetForcedOff(int v)
{

}

void CDriver::SetInputVolt(float v)
{

}


//GET
int CDriver::GetId()
{
	return m_Id;
}

int CDriver::GetType()
{
	return m_Type;
}

wxString CDriver::GetName()
{
	return m_Name;
}

int CDriver::GetBaseStationId()
{
	return 0;
}

wxString  CDriver::GetText()
{
	return wxEmptyString;
}

float CDriver::GetInputVolt()
{
	return 0;
}