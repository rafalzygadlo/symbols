#include <stdio.h>
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include "conf.h"
#include "tools.h"

#define CONVERTED_DEGREE_LENGTH	15
wxMutex *mutex = NULL;
int GlobalLanguageID;
int GlobalUID;

const wchar_t *nvLanguage[2][30] = 
{ 
	//en
	{
		L"Manager",
		L"New",
		L"Name",
		L"Description",
		L"Longitude",
		L"Latitude",
		L"Close",
		L"Ok",
		L"Cancel",
		L"Click on Chart to put your marker.\nWhen done click Ok to save or Cancel to remove marker.",
		L"Area",
		L"New",
		L"Delete Area ?",
		L"Edit",
		L"Delete",
		L"Seaway",
		L"Type",
		L"Name can not be empty",
		L"Name",
		L"Info",
		L"Delete Seaway ?",
		L"Delete Light ?",
		L"Light",
		L"Bulb",
		L"Add color",
		L"Color",
		L"Delete color",
		L"Battery",
		L"Delete Battery ?",
		L"Capacity",
		
	},
	//pl
	{
		L"Marker",
		L"Dodaj Marker",
		L"Nazwa",
		L"Opis",
		L"Longitude",
		L"Latitude",
		L"Zamknij",
		L"Ok",
		L"Anuluj",
		L"Kliknij na mapie ¿eby ustaliæ pozycjê.",
		L"Akwen",
		L"Nowy",
		L"Usun¹æ akwen ?",
		L"Edycja",
		L"Usuñ",
		L"Tor wodny",
		L"Typ",
		L"Nazwa nie mo¿e byæ pusta",
		L"Nazwa",
		L"Opis",
		L"Usun¹æ tor wodny ?",
		L"Usun¹æ œwiat³o ?",
		L"Œwiat³o",
		L"¯arówka",
		L"Dodaj kolor",
		L"Kolor",
		L"Usuñ kolor",
		L"Akumulator",
		L"Usun¹æ akumulator ?",
		L"Pojemnoœæ",
	}

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
	return nvLanguage[GlobalLanguageID][id];
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
	return wxString::Format(_("%02d° %02d' %02.2f''"),decimal, (int)minutes, second);
      
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
	
	sscanf(buffer,"%d° %d' %f'' %c",&degree,&min,&sec,&dindicator);
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

	sscanf(buffer,"%d° %d' %f'' %c",&degree,&min,&sec,&dindicator);
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