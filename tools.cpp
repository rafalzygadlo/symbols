#include <stdio.h>
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include "conf.h"
#include "tools.h"

#define CONVERTED_DEGREE_LENGTH	15
wxMutex *mutex = NULL;
int GlobalLanguageID;
int GlobalUID;

const wchar_t *nvLanguage[45][2] = 
{ 
	//en
	{L"Symbol",	L"Znak"},
	{L"New", L"Nowy  \tCtrl+N"},
	{L"Name", L"Nazwa"},
	{L"Description",L"Opis"},
	{L"Longitude",	L"Longitude"},
	{L"Latitude",L"Latitude"},
	{L"Close",	L"Zamknij"},
	{L"Ok",L"Ok"},
	{L"Cancel",L"Anuluj"},
	{L"Click on Chart to put your marker.\nWhen done click Ok to save or Cancel to remove marker.",L"Kliknij na mapie �eby ustali� pozycj�."},
	{L"Area",L"Akwen"},
	{L"New",L"Nowy"},
	{L"Edit",L"Edycja"},
	{L"Delete",L"Usu�"},
	{L"Seaway",L"Tor wodny"},
	{L"Type",L"Rodzaj znaku"},
	{L"Name can not be empty",L"Nazwa nie mo�e by� pusta"},
	{L"Info",L"Opis"},
	{L"Light",L"�wiat�o"},
	{L"Bulb",L"�ar�wka"},
	{L"Add color",L"Dodaj kolor"},
	{L"Color",	L"Kolor"},
	{L"Delete color", L"Usu� kolor"},
	{L"Battery",L"Akumulator"},
	{L"Capacity",L"Pojemno��"},
	{L"Communication Type",L"Typ ��czno�ci"},
	{L"Delete ?",L"Usun�� ?"},
	{L"Character not allowed",L"Niedozwolony znak"},
	{L"Flash",	L"B�yskacz"},
	{L"Voltage",L"Napi�cie"},
	{L"Power",L"Moc"},
	{L"Type",L"Typ"},
	{L"Lantern",L"Latarnia"},
	{L"Id",	L"Id"},
	{L"Changer",L"Zmieniacz"},
	{L"Solar",L"Solar"},
	{L"Regulator",L"Regulator"},
	{L"AC adapter",L"Zasilacz"},
	{L"Synchronzation",L"Synchronizacja"},
	{L"Telemetry module",L"Modu� telemetryczny"},
	{L"Collection module",L"Modu� zbierania"},
	{L"Antenna",L"Antena"},
	{L"Lightning arrester",L"Odgromnik"},
	{L"Wind generator",L"Generator wiatrowy"},
	{L"Nautofon",L"Nautofon"},
};
				
	
const wxChar *nvDistanceN[2][3] = 
{ 
	//en
	{
		_("Nautic Miles"),
		_("Kilometer"),
		_("Meter"),
	},

	//pl
	{
		_("Mile morskie"),
		_("Kilometry"),
		_("Metry"),
	}

};

wxMutex *GetMutex()
{
	if(mutex == NULL)
		mutex = new wxMutex;
	
	return mutex;
}


void FreeMutex()
{
	if(mutex != NULL)
		delete mutex;
	
	mutex = NULL;
}

wxString GetConfigFile()
{
	return wxString::Format(wxT("%s%s%s"),GetWorkDir().wc_str(),wxT(DIR_SEPARATOR),_(CONFIG_FILE));
}

wxString GetWorkDir()
{
	static wxString buffer;
	wxStandardPaths Paths = wxStandardPaths::Get();
	buffer.Printf(wxT("%s%s%s%s"), Paths.GetUserDataDir().wc_str(wxConvUTF8),  wxT(DIR_SEPARATOR), wxT(DIR_WORKDIR), wxT(DIR_SEPARATOR) );
	return buffer;
}


wxString GetProductInfo()
{
	return wxString::Format(_("%s %s\n%s"),_(PRODUCT_NAME),_(PRODUCT_VERSION),_(PRODUCT_COPYRIGHT));
}
wxString GetProductName()
{
	return wxString::Format(_("%s %s"),_(PRODUCT_NAME),_(PRODUCT_VERSION));
}

wxString GetDistanceName(size_t id)
{
	return nvDistanceN[GlobalLanguageID][id];
}

const wchar_t *GetMsg(int id)
{
	return nvLanguage[id][GlobalLanguageID];
}
void SetLangId(int id)
{
	GlobalLanguageID = id;
}
//degree = 40.044658660888672
wxString ConvertDegree(float degree) 
{
	int decimal = (int)degree;
    double minutes = (float)(degree - decimal) * 60;
    double second = (float)(minutes - (int)(minutes)) * 60;
	return wxString::Format(_("%02d� %02d' %02.2f''"),decimal, (int)minutes, second);
      
}

wxString FormatLongitude(float x) 
{
      wxString str;

      if(x == 0)
		  return str = wxString::Format(_("%s"), ConvertDegree(0).wc_str());
	  
	  if (x > 0.0f) 
	  {
        if (x <= 180.0f)
			str = wxString::Format(_("%s E"), ConvertDegree(x).wc_str());
        else
			str = wxString::Format(_("%s W"), ConvertDegree(360 - x).wc_str());
      } else {
        if (x >= -180.0f)
			str = wxString::Format(_("%s W"), ConvertDegree(-x).wc_str());
        else
			str = wxString::Format(_("%s E"), ConvertDegree(x+360).wc_str());
            
      }
      return str;
}

wxString FormatLatitude(float y) 
{
	
	wxString str;
	 if(y == 0)
		  return str = wxString::Format(_("%s"), ConvertDegree(0).wc_str());

    if (y > 0)
		str = wxString::Format(_("%s N"), ConvertDegree(y).wc_str());
    else
		str = wxString::Format(_("%s S"), ConvertDegree(-y).wc_str());

    return str;

}

void nvMidPoint(double lon1, double lat1,double lon2, double lat2, double *v1, double *v2)
{
	*v1 = (lon1 + lon2) / 2;
	*v2 = (lat1 + lat2) / 2;
}

void nvPointOfIntersection(double a1, double b1,double a2, double b2, double *x, double *y)
{
	*x = (b1 - b2)/(a2 - a1);
	*y = (a2 * b1 - b2 * a1) / (a2 - a1); 
}

bool SetLat(char *text, float *val)
{
	int degree,min;
	float sec;
	char dindicator;

	char buffer[64];
	sprintf(buffer,"%s",text);
	
	sscanf(buffer,"%d� %d' %f'' %c",&degree,&min,&sec,&dindicator);
	bool result = true;	
	if(degree != 0 && min != 0 && sec != 0)
		if(dindicator != 'S' && dindicator != 'N')
			result = false;
		
	if(degree > 90 || degree < 0)
		result = false;
	if(min >= 60 || min < 0)
		result = false;
	if(sec >= 60 || sec < 0)
		result = false;
	
	double y;
	double _min;

	if(result)
	{
		_min = min + ((float)sec/60);
		y = degree + ((float)_min/60);
				
		if(dindicator == 'N')
		{
			if(y == 0)
				*val = y;
			else
				*val = -y;
		}else{
			*val = y;
		}
	
	}else{
			
		return false;
	}

	return true;
}

bool SetLon(char *text, float *val)
{
	int degree,min;
	float sec;
	char dindicator;

	char buffer[64];
	sprintf(buffer,"%s",text);

	sscanf(buffer,"%d� %d' %f'' %c",&degree,&min,&sec,&dindicator);
	bool result = true;	
	if(degree != 0 && min != 0 && sec != 0)
		if(dindicator != 'W' && dindicator != 'E')
			result = false;
		
	if(degree > 180 || degree < 0)
		result = false;
	if(min >= 60 || min < 0)
		result = false;
	if(sec >= 60 || sec < 0)
		result = false;

	double x;
	double _min;
	
	if(result)
	{
		_min = min + ((float)sec/60);
		x = degree + ((float)_min/60);
				
		if(dindicator == 'W')
		{
			if(x == 0)
				*val = x;
			else
				*val = -x;
			
		}else{
			*val = x;
		}
	
	}else{
	
		return false;
	}

	return true;
}

int _GetUID()
{
	return GlobalUID;
}

void _SetUID(int uid)
{
	GlobalUID = uid;
}

void SetLanguageId(int id)
{
	GlobalLanguageID = id;
}

int GetLanguageId()
{
	return GlobalLanguageID;
}

wxString Convert(char *v)
{
	wxString str(v,wxConvUTF8);
	return str;
}