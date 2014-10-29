#include <stdio.h>
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include "conf.h"
#include "tools.h"
#include "db.h"
#include "NaviToolsLib.h"
#include "stdio.h"

#define CONVERTED_DEGREE_LENGTH	15
wxMutex *mutex = NULL;
int GlobalLanguageID;
int GlobalUID;

const wchar_t *nvLanguage[46][2] = 
{ 
	//en
	{L"Manager",L"Manager"},
	{L"New", L"Nowy  \tCtrl+N"},
	{L"Name", L"Nazwa"},
	{L"Description",L"Opis"},
	{L"Longitude",	L"Longitude"},
	{L"Latitude",L"Latitude"},
	{L"Close",	L"Zamknij"},
	{L"OK",L"OK"},
	{L"Cancel",L"Anuluj"},
	{L"Click on Chart to put your marker.\nWhen done click Ok to save or Cancel to remove marker.",L"Kliknij na mapie ¿eby ustaliæ pozycjê."},
	{L"Area",L"Akwen"},
	{L"New",L"Nowy"},
	{L"Edit",L"Edycja"},
	{L"Delete",L"Usuñ"},
	{L"Seaway",L"Tor wodny"},
	{L"Name can not be empty",L"Nazwa nie mo¿e byæ pusta"},
	{L"Info",L"Opis"},
	{L"Light",L"Œwiat³o"},
	{L"Add color",L"Dodaj kolor"},
	{L"Color",	L"Kolor"},
	{L"Delete color", L"Usuñ kolor"},
	{L"Delete ?",L"Usun¹æ ?"},
	{L"Character not allowed",L"Niedozwolony znak"},
	{L"Type",L"Typ"},
	{L"Devices",L"Urz¹dzenie"},
	{L"Id",L"Id"},
	{L"All",L"Wszystko"},
	{L"Symbol type",L"Typ znaku"},
	{L"Item type",L"Typ urz¹dzenia"},
	{L"Light item",L"Sk³adowe œwiat³a"},
	{L"Picture",L"Zdjêcie"},
	{L"Add picture",L"Dodaj zdjêcie"},
	{L"Bad picture",L"Nie mo¿na za³adowaæ zdjêcia"},
	{L"Picture too big max %dkB",L"Za du¿e zdjêcie max %dkB"},
	{L"Size: %d x %d",L"Wymiary: %d x %d"},
	{L"Choose picture",L"Wybierz zdjêcie"},
	{L"Symbol",L"Znak"},
	{L"Quantity",L"Iloœæ"},
	{L"Symbol number",L"Numer znaku"},
	{L"Coverage",L"Zasiêg"},
	{L"Sector",L"Sektor"},
	{L"Sector from",L"Sektor od"},
	{L"Sector to",L"Sektor do"},
	{L"Characteristic",L"Charakterystyka"},
	{L"No picture",L"Brak zdjêcia"},
	{L"Properties",L"W³aœciwoœci"},
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
wxString ConvertDegree(double degree,int type) 
{
	int decimal = (int)degree;
	double minutes;
	if(type)
		minutes = (double)(degree - decimal) * 60;
	else
		minutes = (double)(degree - decimal) * 100;
    
	double second = (double)(minutes - (int)(minutes)) * 60;
	
	switch(type)
	{
		case DEGREE_FORMAT_DDMMSS:
			return wxString::Format(_("%02d° %02d' %02.4f''"),decimal, (int)minutes, second);
		case DEGREE_FORMAT_DDMMMM:
			return wxString::Format(_("%02d° %02.4f'"),decimal, minutes);
	}  
}

wxString FormatLongitude(double x, int type) 
{
      wxString str;

      if(x == 0)
		  return str = wxString::Format(_("%s"), ConvertDegree(0,type).wc_str());
	  
	  if (x > 0.0f) 
	  {
        if (x <= 180.0f)
			str = wxString::Format(_("%s E"), ConvertDegree(x,type).wc_str());
        else
			str = wxString::Format(_("%s W"), ConvertDegree(360 - x,type).wc_str());
      } else {
        if (x >= -180.0f)
			str = wxString::Format(_("%s W"), ConvertDegree(-x,type).wc_str());
        else
			str = wxString::Format(_("%s E"), ConvertDegree(x+360,type).wc_str());
            
      }
      return str;
}

wxString FormatLatitude(double y,int type) 
{
	
	wxString str;
	 if(y == 0)
		  return str = wxString::Format(_("%s"), ConvertDegree(0,type).wc_str());

    if (y > 0)
		str = wxString::Format(_("%s N"), ConvertDegree(y,type).wc_str());
    else
		str = wxString::Format(_("%s S"), ConvertDegree(-y,type).wc_str());

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

bool _SetLat(char *text, double *val,int type)
{
	switch(type)
	{
		case DEGREE_FORMAT_DDMMMM :return _SetLat(text,val);
		case DEGREE_FORMAT_DDMMSS :return _SetLatSec(text,val);
	}
}

bool _SetLon(char *text, double *val,int type)
{
	switch(type)
	{
		case DEGREE_FORMAT_DDMMMM :return _SetLon(text,val);
		case DEGREE_FORMAT_DDMMSS :return _SetLonSec(text,val);
	}
}

bool _SetLat(char *text, double *val)
{
	int degree;
	float min;
	char dindicator;

	char buffer[64];
	sprintf(buffer,"%s",text);
	
	sscanf(buffer,"%d° %f' %c",&degree,&min,&dindicator);
	bool result = true;	
	if(degree != 0 || min != 0)
		if(dindicator != 'S' && dindicator != 'N')
			result = false;
		
	if(degree > 90 || degree < 0)
		result = false;
	if(min >= 60 || min < 0)
		result = false;
	
	double y;
	
	if(result)
	{
		y = degree + ((double)min/100);
		
		if(y > 90)
			return false;

		if(dindicator == 'S')  //by³o N w naszym g³upim navi
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

bool _SetLon(char *text, double *val)
{
	int degree;
	float min;
	char dindicator;

	char buffer[64];
	sprintf(buffer,"%s",text);

	sscanf(buffer,"%d° %f' %c",&degree,&min,&dindicator);
	bool result = true;	
	if(degree != 0 || min != 0 )
		if(dindicator != 'W' && dindicator != 'E')
			result = false;
		
	if(degree > 180 || degree < 0)
		result = false;
	if(min >= 60 || min < 0)
		result = false;
	
	double x;
		
	if(result)
	{
		//_min = min;
		x = degree + ((double)min/100);
		
		if(x > 180)
			return false;
	
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

bool _SetLatSec(char *text, double *val)
{
	int degree,min;
	float sec;
	char dindicator;

	char buffer[64];
	sprintf(buffer,"%s",text);
	
	sscanf(buffer,"%d° %d' %f'' %c",&degree,&min,&sec,&dindicator);
	bool result = true;	
	if(degree != 0 || min != 0 || sec != 0)
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
		_min = min + ((double)sec/60);
		y = degree + ((double)_min/60);
		
		if(y > 90)
			return false;

		if(dindicator == 'S')  //by³o N w naszym g³upim navi
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

bool _SetLonSec(char *text, double *val)
{
	int degree,min;
	float sec;
	char dindicator;

	char buffer[64];
	sprintf(buffer,"%s",text);

	sscanf(buffer,"%d° %d' %f'' %c",&degree,&min,&sec,&dindicator);
	bool result = true;	
	if(degree != 0 || min != 0 || sec != 0)
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
		_min = min + ((double)sec/60);
		x = degree + ((double)_min/60);
		
		if(x > 180)
			return false;
	
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

//wxArrayString GetItemType()
//{

	//return 0;
//}
/*
int GetItemTypeId(wxString name)
{


}
*/


wxListBox *GetFilterList(wxWindow *Parent, int wid)
{
	wxListBox *Filter = new wxListBox(Parent,wid);
	Filter->Append(GetMsg(MSG_ALL));

	wxArrayString ar;
	wxString sql = wxString::Format(_("SELECT * FROM `%s` ORDER BY name"),TABLE_ITEM_TYPE);
	if(!my_query(sql))
		return Filter;
	
	int rows = 0;
	void *result = db_result();
	char **row;
		
	int i = 0;
	while(row = (char**)db_fetch_row(result))
	{
		wxString name(row[FI_ITEM_TYPE_NAME],wxConvUTF8);
		ar.Add(name);
		int id = Filter->Append(name);
		Filter->SetClientData(id,(int*)atoi(row[FI_ITEM_TYPE_ID]));
	}

	db_free_result(result);
		
	return Filter;
}

wxComboBox *GetFilterCombo(wxWindow *Parent, int wid)
{
	wxComboBox *Filter = new wxComboBox(Parent,wid,wxEmptyString,wxDefaultPosition,wxDefaultSize,NULL,0, wxCB_READONLY);
	Filter->Append(GetMsg(MSG_ALL));

	wxArrayString ar;
	wxString sql = wxString::Format(_("SELECT * FROM `%s` ORDER BY name"),TABLE_ITEM_TYPE);
	if(!my_query(sql))
		return Filter;
	
	int rows = 0;
	void *result = db_result();
	char **row;
		
	int i = 0;
	while(row = (char**)db_fetch_row(result))
	{
		wxString name(row[FI_ITEM_TYPE_NAME],wxConvUTF8);
		ar.Add(name);
		int id = Filter->Append(name);
		Filter->SetClientData(id,(int*)atoi(row[FI_ITEM_TYPE_ID]));
	}

	db_free_result(result);

	return Filter;
}


wxComboBox *GetCombo(wxWindow *Parent, wxString table, wxString sel)
{
	wxComboBox *ptr = new wxComboBox(Parent,wxID_ANY,wxEmptyString,wxDefaultPosition,wxDefaultSize,NULL,0, wxCB_READONLY);
		
	wxString sql = wxString::Format(_("SELECT * FROM `%s` ORDER BY name"),table);
	if(!my_query(sql))
		return ptr;
	
	int rows = 0;
	void *result = db_result();
	char **row;
		
	int i = 0;
	while(row = (char**)db_fetch_row(result))
	{
		wxString name(row[FID_NAME],wxConvUTF8);
		int id = ptr->Append(name);
		int row_id = atoi(row[FID_ID]);

		long sid;
		sel.ToLong(&sid);

		if(sid == row_id)
			ptr->SetSelection(id);

		ptr->SetClientData(id,(int*)row_id);
	}

	db_free_result(result);

	return ptr;
}
