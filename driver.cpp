#include "driver.h"

CDriver::CDriver()
{
	m_Id = 0;
	m_Type;
	m_Exists = false;
	wxString m_Name;
}

CDriver::~CDriver()
{
	
}

void CDriver::Render()					{}
void CDriver::Read()					{}
void CDriver::ShowGraph()				{}
void CDriver::ShowManagement()			{}

//SET
void CDriver::SetId(int v)				{ m_Id = v;}
void CDriver::SetName(wxString v)		{ m_Name = v;}
void CDriver::SetType(int v)			{ m_Type = v;}
void CDriver::SetExists(bool v)			{ m_Exists = v;}
//virtual
void CDriver::SetIdBaseStation(int v)	{}
void CDriver::SetMMSI(int v)			{}
void CDriver::SetForcedOff(int v)		{}
void CDriver::SetLightOn(int v)			{}
void CDriver::SetInputVolt(float v)		{}
void CDriver::SetIdSymbol(int v)		{}
void CDriver::SetFont(nvFastFont *v)	{}
void CDriver::SetDB(void *v)			{}

//pozycja ustalana ze względu na opcje
void CDriver::SetLon(double v)			{}
void CDriver::SetLat(double v)			{}
void CDriver::SetLonMap(double v)		{}
void CDriver::SetLatMap(double v)		{}
//pozycja z gpsa
void CDriver::SetGpsLon(double v)		{}
void CDriver::SetGpsLat(double v)		{}
void CDriver::SetGpsLonMap(double v)	{}
void CDriver::SetGpsLatMap(double v)	{}
//pozycja referencyjna
void CDriver::SetRLon(double v)			{}
void CDriver::SetRLat(double v)			{}
void CDriver::SetRLonMap(double v)		{}
void CDriver::SetRLatMap(double v)		{}


//GET
int CDriver::GetId()					{ return m_Id; }
int CDriver::GetType()					{ return m_Type; }
bool CDriver::GetExists()				{ return m_Exists; }
wxString CDriver::GetName()				{ return m_Name; }

//virtual
int CDriver::GetBaseStationId()			{ return 0; }
wxString  CDriver::GetText()			{ return wxEmptyString; }
wxString CDriver::GetFullText()			{ return wxEmptyString; }
float CDriver::GetInputVolt()			{ return 0; }


double CDriver::GetGpsLon()				{ return 0; }
double CDriver::GetGpsLat()				{ return 0; }
double CDriver::GetGpsLonMap()			{ return 0; }
double CDriver::GetGpsLatMap()			{ return 0; }			
